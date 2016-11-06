/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(EXCLUDE_ITTYBITTY_MESSAGES) && defined(EXCLUDE_ITTYBITTY_STORAGE) && !defined(EXCLUDE_ITTYBITTY_PARAMS)
	#define EXCLUDE_ITTYBITTY_PARAMS
#endif

#ifndef EXCLUDE_ITTYBITTY_PARAMS


#include "IttyBitty_params.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

#ifdef ARDUINO
CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;
#endif

CBYTE IttyBitty::DATA_SIZE_MASK = 0xF0;

PBYTE IttyBitty::__param_buffer = NULL;

#pragma endregion


#pragma region [ParamBase] IMPLEMENTATION

// DESTRUCTOR

#include "IttyBitty_print.h"
ParamBase::~ParamBase()
{
	if (!_Dispose)
		return;

	// TODO
	PrintLine(F("~ParamBase"));

	if (_DataType == DataType::BYTES_PARAM || _DataType == DataType::STRING_PARAM || _DataType == DataType::BIT_PARAM)
		_Value.FreeData();
}
				

// ISerializable IMPLEMENTATION

CSIZE ParamBase::BinarySize() const
{
	return SIZEOF(CSIZE) + SIZEOF(DataType) + this->ByteWidth();
}

CSIZE ParamBase::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(DataType) + this->StringLength() + 1;
}

CSIZE ParamBase::ByteWidth() const
{
	return TRAILING_ZERO_BITS(static_cast<BYTE>(this->GetDataSize())) - 0x3;
}

CSIZE ParamBase::StringLength() const
{
	return 2 * this->ByteWidth();
}

PCBYTE ParamBase::ToBinary() const
{
	CSIZE size = this->BinarySize();

	if (__param_buffer)
		delete[] __param_buffer;

	__param_buffer = new BYTE[size];

	PBYTE bufferPtr = __param_buffer;
	
	CSIZE byteWidth = this->ByteWidth();
	memcpy(bufferPtr, &byteWidth, SIZEOF(byteWidth));
	bufferPtr += SIZEOF(byteWidth);

	memcpy(bufferPtr, &_DataType, SIZEOF(DataType));
	bufferPtr += SIZEOF(DataType);

	if (byteWidth > 0)
		memcpy(bufferPtr, _Value.Bytes, this->ByteWidth());

	return __param_buffer;
}

PCCHAR ParamBase::ToString() const
{
	CSIZE size = this->StringSize();
	CSIZE byteWidth = this->ByteWidth();
	
	if (__param_buffer)
		delete[] __param_buffer;

	__param_buffer = new BYTE[size];
	__param_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__param_buffer);

	bufferPtr = StringInsertValue<CSIZE>(byteWidth, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(static_cast<CBYTE>(this->GetDataType()), bufferPtr);

	PCBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_PARAM:
	case DataType::CHAR_PARAM:
	case DataType::BOOL_PARAM:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_PARAM:
	case DataType::SHORT_PARAM:
		

		bytes = (PBYTE)&(_Value.Word);
		break;
			
	case DataType::DWORD_PARAM:
	case DataType::LONG_PARAM:	
	case DataType::FLOAT_PARAM:

		bytes = (PBYTE)&(_Value.DWord);
		break;

	default:

		bytes = _Value.Bytes;

		for (SIZE i = 0; i < byteWidth; i++)
			bufferPtr = StringInsertValue<CBYTE>(bytes[i], bufferPtr);

		return reinterpret_cast<PCCHAR>(__param_buffer);
	}
	
	for (SIZE i = 0; i < 4 - byteWidth; i++)
		bufferPtr = StringInsertValue<CBYTE>(bytes[byteWidth - i - 1], bufferPtr);
	
	return reinterpret_cast<PCCHAR>(__param_buffer);
}

VOID ParamBase::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	bufferPtr += SIZEOF(CSIZE);

	_DataType = static_cast<DataType>(*bufferPtr++);

	switch (_DataType)
	{
	case DataType::BYTE_PARAM:
	case DataType::CHAR_PARAM:
	case DataType::BOOL_PARAM:

		_Value = *((PBYTE)bufferPtr);
		break;
		
	case DataType::WORD_PARAM:
	case DataType::SHORT_PARAM:
		

		_Value = *((PWORD)bufferPtr);
		break;
		
	case DataType::DWORD_PARAM:
	case DataType::LONG_PARAM:		
	case DataType::FLOAT_PARAM:

		_Value = *((PDWORD)bufferPtr);
		break;

	default:

		_Value = data;
	}
}

VOID ParamBase::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);

	bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);

	CBYTE byteWidth = this->ByteWidth();

	PBYTE bytes = NULL;
	
	switch (_DataType)
	{
	case DataType::BYTE_PARAM:
	case DataType::CHAR_PARAM:
	case DataType::BOOL_PARAM:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_PARAM:
	case DataType::SHORT_PARAM:		

		bytes = (PBYTE)&(_Value.Word);
		break;
		
	case DataType::DWORD_PARAM:
	case DataType::LONG_PARAM:		
	case DataType::FLOAT_PARAM:

		bytes = (PBYTE)&(_Value.DWord);
		break;

	default:
		
		for (BYTE i = 0; i < byteWidth; i++)
			bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);

		_Value = bytes;

		return;
	}
	
	for (SIZE i = 0 ; i < byteWidth; i++)
		bufferPtr = StringReadValue<BYTE>(bytes[byteWidth - i - 1], bufferPtr);
}

#ifdef ARDUINO

BOOL ParamBase::Transmit(HardwareSerial & serial)
{
	if (!serial.availableForWrite())
		delay(SERIAL_DEFAULT_TIMEOUT_MS);
	if (!serial.availableForWrite())
		return FALSE;

	if (!this->printTo(serial))
		return FALSE;

	serial.flush();

	return TRUE;
}

BOOL ParamBase::Transmit(BYTE i2cAddr, TwoWire & twi)
{
	twi.beginTransmission(i2cAddr);

	if (!this->printTo(twi))
		return FALSE;

	twi.flush();	

	if (twi.endTransmission())
		return FALSE;

	return TRUE;
}

SIZE ParamBase::printTo(Print & printer) const
{
#ifdef _DEBUG
	SIZE size = this->StringSize();
	PCCHAR buffer = this->ToString();
#else
	SIZE size = this->BinarySize();
	PCBYTE buffer = this->ToBinary();
#endif

	for (SIZE i = 0; i < size; i++)
		printer.print(buffer[i]);

	delete[] __param_buffer;
	__param_buffer = NULL;

	return size;
}

#endif	// #ifdef ARDUINO


// IParam IMPLEMENTATION

CONST DataSize ParamBase::GetDataSize() const
{
	return DataTypeToDataSize(_DataType);
}

CONST DataType ParamBase::GetDataType() const
{
	return _DataType;
}

#pragma endregion



#pragma region [Param] IMPLEMENTATION

// CONSTRUCTORS

Param::Param(CONST DataType dataType)
{
	_Dispose = TRUE;
	
	_DataType = dataType;
}

Param::Param(RCPARAM other)
{
	_Dispose = other._Dispose;

	_Value = other._Value;
	_DataType = other._DataType;
}

Param::Param(RRPARAM other)
{
	this->~ParamBase();
	new (this) Param(other._Value, other._DataType);
}

Param::Param(RCVALUE value, CONST DataType dataType)
{
	_Value = value;
	_DataType = dataType;
}

Param::Param(RCCHAR value)
{
	_Value = value;
	_DataType = DataType::CHAR_PARAM;
}

Param::Param(RCBYTE value)
{
	_Value = value;
	_DataType = DataType::BYTE_PARAM;
}

Param::Param(RCBOOL value)
{
	_Value = value;
	_DataType = DataType::BOOL_PARAM;
}

Param::Param(RCSHORT value)
{
	_Value = value;
	_DataType = DataType::SHORT_PARAM;
}

Param::Param(RCWORD value)
{
	_Value = value;
	_DataType = DataType::WORD_PARAM;
}

Param::Param(RCLONG value)
{
	_Value = value;
	_DataType = DataType::LONG_PARAM;
}

Param::Param(RCDWORD value)
{
	_Value = value;
	_DataType = DataType::DWORD_PARAM;
}

Param::Param(RCFLOAT value)
{
	_Value = value;
	_DataType = DataType::FLOAT_PARAM;
}


// STATIC FUNCTIONS

RPARAM Param::NULL_OBJECT()
{
	STATIC Param NULL_PARAM;
	return NULL_PARAM;
}


// OPERATORS

RPARAM Param::operator =(RCPARAM rValue)
{
	*this = Param(rValue);
	return *this;
}

RPARAM Param::operator =(RRPARAM rValue)
{
	*this = Param(rValue);
	return *this;
}

RPARAM Param::operator =(RCVALUE rValue)
{
	_Value = rValue;
	return *this;
}


Param::operator RCCHAR() const
{
	return _Value;
}

Param::operator RCBYTE() const
{
	return _Value;
}

Param::operator RCBOOL() const
{
	return _Value;
}
Param::operator RCSHORT() const
{
	return _Value;
}

Param::operator RCWORD() const
{
	return _Value;
}

Param::operator RCLONG() const
{
	return _Value;
}

Param::operator RCDWORD() const
{
	return _Value;
}

Param::operator RCFLOAT() const
{
	return _Value;
}

#pragma endregion


#pragma region [VarLengthParam] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

VarLengthParam::VarLengthParam(CONST DataType dataType, CSIZE length) 
	: Param(dataType), _Length(length)
{
	switch (dataType)
	{
	case DataType::BYTES_PARAM:

		_Value = new BYTE[length];
		break;

	case DataType::STRING_PARAM:

		_Value = new CHAR[length];
		break;

	case DataType::BIT_PARAM:

		_Value = new BITPACK[length];
		break;

	default:
		break;
	}
}

VarLengthParam::VarLengthParam(RCVARLENGTHPARAM other)
{
	_Dispose = other._Dispose;

	_Value = other._Value;
	_DataType = other._DataType;
	_Length = other._Length;
}

VarLengthParam::VarLengthParam(RRVARLENGTHPARAM other)
{
	this->~VarLengthParam();
	new (this) VarLengthParam(other._Value, other._DataType, other._Length);
}

VarLengthParam::VarLengthParam(RCVALUE value, CONST DataType dataType, CSIZE length) 
	: Param(value, dataType)
{
	if (_DataType == DataType::STRING_PARAM)
	{
		if (value.String == NULL)
			_Length = 0;
		else
			_Length = strlen((PCCHAR)_Value);
	}
	else
	{
		_Length = length;
	}
}

VarLengthParam::VarLengthParam(PCBYTE value, CSIZE length) 
	: Param(DataType::BYTES_PARAM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthParam::VarLengthParam(PCCHAR value) 
	: Param(DataType::STRING_PARAM)
{
	_Dispose = FALSE;
	
	_Value = value;

	if (value == NULL)
		_Length = 0;
	else
		_Length = strlen(value);
}

VarLengthParam::VarLengthParam(PCBITPACK value, CSIZE length) 
	: Param(DataType::BIT_PARAM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthParam::~VarLengthParam()
{
	if (!_Dispose)
		return;
	
	//if (_Length > 0 || _DataType == DataType::STRING_PARAM)
	//	_Value.FreeData();
}


// OPERATORS

RVARLENGTHPARAM VarLengthParam::operator =(RCVARLENGTHPARAM rValue)
{
	*this = VarLengthParam(rValue);
	return *this;
}

RVARLENGTHPARAM VarLengthParam::operator =(RRVARLENGTHPARAM rValue)
{
	*this = VarLengthParam(rValue);
	return *this;
}


VarLengthParam::operator PCBYTE() const
{
	return _Value;
}

VarLengthParam::operator PCCHAR() const
{
	return _Value;
}

VarLengthParam::operator PCBITPACK() const
{
	return _Value;
}


// Param OVERRIDES

CSIZE VarLengthParam::ByteWidth() const
{
	if (_Length > 0)
		return _Length;

	return ParamBase::ByteWidth();
}

VOID VarLengthParam::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
	ParamBase::FromBinary(data);
}

VOID VarLengthParam::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

	ParamBase::FromString(data);

	// TODO
	//PCCHAR bufferPtr = data;

	//bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

	//CBYTE byteWidth = this->ByteWidth();

	//PBYTE bytes = NULL;

	//switch (_DataType)
	//{
	//case DataType::BYTE_PARAM:
	//case DataType::CHAR_PARAM:
	//case DataType::BOOL_PARAM:

	//	bytes = (PBYTE)&(_Value.Byte);
	//	break;
	//	
	//case DataType::WORD_PARAM:
	//case DataType::SHORT_PARAM:
	//	

	//	bytes = (PBYTE)&(_Value.Word);
	//	break;
	//	
	//case DataType::FLOAT_PARAM:
	//case DataType::LONG_PARAM:		
	//case DataType::DWORD_PARAM:

	//	bytes = (PBYTE)&(_Value.DWord);
	//	break;

	//default:

	//	for (BYTE i = 0; i < byteWidth; i++)
	//		bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);

	//	_Value = bytes;

	//	return;
	//}
	//
	//for (SIZE i = 0 ; i < byteWidth; i++)
	//	bufferPtr = StringReadValue<BYTE>(bytes[byteWidth - i - 1], bufferPtr);
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_PARAMS
