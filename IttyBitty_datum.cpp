/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef EXCLUDE_ITTYBITTY_DATUM


#include "IttyBitty_datum.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

#ifdef ARDUINO
CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;
#endif

CBYTE IttyBitty::DATA_SIZE_MASK = 0xF0;

PBYTE IttyBitty::__datum_buffer = NULL;

#pragma endregion


#pragma region [DatumBase] IMPLEMENTATION

// DESTRUCTOR

#include "IttyBitty_print.h"
DatumBase::~DatumBase()
{
	if (!_Dispose)
		return;

	// TODO
	PrintLine(F("~DatumBase"));

	if (_DataType == DataType::BYTES_DATUM || _DataType == DataType::STRING_DATUM || _DataType == DataType::BIT_DATUM)
		_Value.FreeData();
}
				

// ISerializable IMPLEMENTATION

CSIZE DatumBase::BinarySize() const
{
	return SIZEOF(CSIZE) + SIZEOF(DataType) + this->ByteWidth();
}

CSIZE DatumBase::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(DataType) + this->StringLength() + 1;
}

CSIZE DatumBase::ByteWidth() const
{
	return TRAILING_ZERO_BITS(static_cast<BYTE>(this->GetDataSize())) - 0x3;
}

CSIZE DatumBase::StringLength() const
{
	return 2 * this->ByteWidth();
}

PCBYTE DatumBase::ToBinary() const
{
	CSIZE size = this->BinarySize();

	if (__datum_buffer)
		delete[] __datum_buffer;

	__datum_buffer = new BYTE[size];

	PBYTE bufferPtr = __datum_buffer;
	
	CSIZE byteWidth = this->ByteWidth();
	memcpy(bufferPtr, &byteWidth, SIZEOF(byteWidth));
	bufferPtr += SIZEOF(byteWidth);

	memcpy(bufferPtr, &_DataType, SIZEOF(DataType));
	bufferPtr += SIZEOF(DataType);

	if (byteWidth > 0)
		memcpy(bufferPtr, _Value.Bytes, this->ByteWidth());

	return __datum_buffer;
}

PCCHAR DatumBase::ToString() const
{
	CSIZE size = this->StringSize();
	CSIZE byteWidth = this->ByteWidth();
	
	if (__datum_buffer)
		delete[] __datum_buffer;

	__datum_buffer = new BYTE[size];
	__datum_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__datum_buffer);

	bufferPtr = StringInsertValue<CSIZE>(byteWidth, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(static_cast<CBYTE>(this->GetDataType()), bufferPtr);

	PCBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_DATUM:
	case DataType::CHAR_DATUM:
	case DataType::BOOL_DATUM:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_DATUM:
	case DataType::SHORT_DATUM:
		

		bytes = (PBYTE)&(_Value.Word);
		break;
			
	case DataType::DWORD_DATUM:
	case DataType::LONG_DATUM:	
	case DataType::FLOAT_DATUM:

		bytes = (PBYTE)&(_Value.DWord);
		break;

	default:

		bytes = _Value.Bytes;

		for (SIZE i = 0; i < byteWidth; i++)
			bufferPtr = StringInsertValue<CBYTE>(bytes[i], bufferPtr);

		return reinterpret_cast<PCCHAR>(__datum_buffer);
	}
	
	for (SIZE i = 0; i < 4 - byteWidth; i++)
		bufferPtr = StringInsertValue<CBYTE>(bytes[byteWidth - i - 1], bufferPtr);
	
	return reinterpret_cast<PCCHAR>(__datum_buffer);
}

VOID DatumBase::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	bufferPtr += SIZEOF(CSIZE);

	_DataType = static_cast<DataType>(*bufferPtr++);

	switch (_DataType)
	{
	case DataType::BYTE_DATUM:
	case DataType::CHAR_DATUM:
	case DataType::BOOL_DATUM:

		_Value = *((PBYTE)bufferPtr);
		break;
		
	case DataType::WORD_DATUM:
	case DataType::SHORT_DATUM:
		

		_Value = *((PWORD)bufferPtr);
		break;
		
	case DataType::DWORD_DATUM:
	case DataType::LONG_DATUM:		
	case DataType::FLOAT_DATUM:

		_Value = *((PDWORD)bufferPtr);
		break;

	default:

		_Value = data;
	}
}

VOID DatumBase::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);

	bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);

	CBYTE byteWidth = this->ByteWidth();

	PBYTE bytes = NULL;
	
	switch (_DataType)
	{
	case DataType::BYTE_DATUM:
	case DataType::CHAR_DATUM:
	case DataType::BOOL_DATUM:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_DATUM:
	case DataType::SHORT_DATUM:		

		bytes = (PBYTE)&(_Value.Word);
		break;
		
	case DataType::DWORD_DATUM:
	case DataType::LONG_DATUM:		
	case DataType::FLOAT_DATUM:

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

BOOL DatumBase::Transmit(HardwareSerial & serial)
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

BOOL DatumBase::Transmit(BYTE i2cAddr, TwoWire & twi)
{
	twi.beginTransmission(i2cAddr);

	if (!this->printTo(twi))
		return FALSE;

	twi.flush();	

	if (twi.endTransmission())
		return FALSE;

	return TRUE;
}

SIZE DatumBase::printTo(Print & printer) const
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

	delete[] __datum_buffer;
	__datum_buffer = NULL;

	return size;
}

#endif	// #ifdef ARDUINO


// IDatum IMPLEMENTATION

CONST DataSize DatumBase::GetDataSize() const
{
	return DataTypeToDataSize(_DataType);
}

CONST DataType DatumBase::GetDataType() const
{
	return _DataType;
}

#pragma endregion



#pragma region [Datum] IMPLEMENTATION

// CONSTRUCTORS

Datum::Datum(CONST DataType dataType)
{
	_Dispose = TRUE;
	
	_DataType = dataType;
}

Datum::Datum(RCDATUM other)
{
	_Dispose = other._Dispose;

	_Value = other._Value;
	_DataType = other._DataType;
}

Datum::Datum(RRDATUM other)
{
	this->~DatumBase();
	new (this) Datum(other._Value, other._DataType);
}

Datum::Datum(RCCONSTVALUE value, CONST DataType dataType)
{
	_Value = value;
	_DataType = dataType;
}

Datum::Datum(RCCHAR value)
{
	_Value = value;
	_DataType = DataType::CHAR_DATUM;
}

Datum::Datum(RCBYTE value)
{
	_Value = value;
	_DataType = DataType::BYTE_DATUM;
}

Datum::Datum(RCBOOL value)
{
	_Value = value;
	_DataType = DataType::BOOL_DATUM;
}

Datum::Datum(RCSHORT value)
{
	_Value = value;
	_DataType = DataType::SHORT_DATUM;
}

Datum::Datum(RCWORD value)
{
	_Value = value;
	_DataType = DataType::WORD_DATUM;
}

Datum::Datum(RCLONG value)
{
	_Value = value;
	_DataType = DataType::LONG_DATUM;
}

Datum::Datum(RCDWORD value)
{
	_Value = value;
	_DataType = DataType::DWORD_DATUM;
}

Datum::Datum(RCFLOAT value)
{
	_Value = value;
	_DataType = DataType::FLOAT_DATUM;
}


// STATIC FUNCTIONS

RDATUM Datum::NULL_OBJECT()
{
	STATIC Datum NULL_DATUM;
	return NULL_DATUM;
}


// OPERATORS

RDATUM Datum::operator =(RCDATUM rValue)
{
	*this = Datum(rValue);
	return *this;
}

RDATUM Datum::operator =(RRDATUM rValue)
{
	*this = Datum(rValue);
	return *this;
}

RDATUM Datum::operator =(RCCONSTVALUE rValue)
{
	_Value = rValue;
	return *this;
}


Datum::operator RCCHAR() const
{
	return _Value;
}

Datum::operator RCBYTE() const
{
	return _Value;
}

Datum::operator RCBOOL() const
{
	return _Value;
}
Datum::operator RCSHORT() const
{
	return _Value;
}

Datum::operator RCWORD() const
{
	return _Value;
}

Datum::operator RCLONG() const
{
	return _Value;
}

Datum::operator RCDWORD() const
{
	return _Value;
}

Datum::operator RCFLOAT() const
{
	return _Value;
}

#pragma endregion


#pragma region [VarLengthDatum] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

VarLengthDatum::VarLengthDatum(CONST DataType dataType, CSIZE length) 
	: Datum(dataType), _Length(length)
{
	switch (dataType)
	{
	case DataType::BYTES_DATUM:

		_Value = new BYTE[length];
		break;

	case DataType::STRING_DATUM:

		_Value = new CHAR[length];
		break;

	case DataType::BIT_DATUM:

		_Value = new BITPACK[length];
		break;

	default:
		break;
	}
}

VarLengthDatum::VarLengthDatum(RCVARLENGTHDATUM other)
{
	_Dispose = other._Dispose;

	_Value = other._Value;
	_DataType = other._DataType;
	_Length = other._Length;
}

VarLengthDatum::VarLengthDatum(RRVARLENGTHDATUM other)
{
	this->~VarLengthDatum();
	new (this) VarLengthDatum(other._Value, other._DataType, other._Length);
}

VarLengthDatum::VarLengthDatum(RCCONSTVALUE value, CONST DataType dataType, CSIZE length) 
	: Datum(value, dataType)
{
	if (_DataType == DataType::STRING_DATUM)
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

VarLengthDatum::VarLengthDatum(PCBYTE value, CSIZE length) 
	: Datum(DataType::BYTES_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthDatum::VarLengthDatum(PCCHAR value) 
	: Datum(DataType::STRING_DATUM)
{
	_Dispose = FALSE;
	
	_Value = value;

	if (value == NULL)
		_Length = 0;
	else
		_Length = strlen(value);
}

VarLengthDatum::VarLengthDatum(PCBITPACK value, CSIZE length) 
	: Datum(DataType::BIT_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthDatum::~VarLengthDatum()
{
	if (!_Dispose)
		return;
	
	//if (_Length > 0 || _DataType == DataType::STRING_DATUM)
	//	_Value.FreeData();
}


// OPERATORS

RVARLENGTHDATUM VarLengthDatum::operator =(RCVARLENGTHDATUM rValue)
{
	*this = VarLengthDatum(rValue);
	return *this;
}

RVARLENGTHDATUM VarLengthDatum::operator =(RRVARLENGTHDATUM rValue)
{
	*this = VarLengthDatum(rValue);
	return *this;
}


VarLengthDatum::operator PCBYTE() const
{
	return _Value;
}

VarLengthDatum::operator PCCHAR() const
{
	return _Value;
}

VarLengthDatum::operator PCBITPACK() const
{
	return _Value;
}


// Datum OVERRIDES

CSIZE VarLengthDatum::ByteWidth() const
{
	if (_Length > 0)
		return _Length;

	return DatumBase::ByteWidth();
}

VOID VarLengthDatum::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
	DatumBase::FromBinary(data);
}

VOID VarLengthDatum::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

	DatumBase::FromString(data);

	// TODO
	//PCCHAR bufferPtr = data;

	//bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

	//CBYTE byteWidth = this->ByteWidth();

	//PBYTE bytes = NULL;

	//switch (_DataType)
	//{
	//case DataType::BYTE_DATUM:
	//case DataType::CHAR_DATUM:
	//case DataType::BOOL_DATUM:

	//	bytes = (PBYTE)&(_Value.Byte);
	//	break;
	//	
	//case DataType::WORD_DATUM:
	//case DataType::SHORT_DATUM:
	//	

	//	bytes = (PBYTE)&(_Value.Word);
	//	break;
	//	
	//case DataType::FLOAT_DATUM:
	//case DataType::LONG_DATUM:		
	//case DataType::DWORD_DATUM:

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

#endif	// #ifndef EXCLUDE_ITTYBITTY_DATUM
