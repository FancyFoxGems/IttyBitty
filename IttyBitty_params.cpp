/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_VALUES) || \
		defined(NO_ITTYBITTY_DATUM) || defined(NO_ITTYBITTY_MESSAGES)
	#define NO_ITTYBITTY_PARAMS
#endif

#ifndef NO_ITTYBITTY_PARAMS


#include "IttyBitty_params.h"

using namespace IttyBitty;


#pragma region [ParamBase] IMPLEMENTATION

// [ISerializable] IMPLEMENTATION

PCBYTE ParamBase::ToBinary() const
{
	CSIZE size = this->BinarySize();

	this->FreeBuffer();

	__datum_buffer = new byte[size];

	PBYTE bufferPtr = __datum_buffer;

	CSIZE byteWidth = this->ByteWidth();
	memcpy(bufferPtr, &byteWidth, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	memcpy(bufferPtr, &_DataType, SIZEOF(DataType));
	bufferPtr += SIZEOF(DataType);

	if (byteWidth > 0)
		memcpy(bufferPtr, _Value.Bytes, this->ByteWidth());

	return __datum_buffer;
}

PCCHAR ParamBase::ToString() const
{
	CSIZE size = this->StringSize();
	CSIZE byteWidth = this->ByteWidth();

	this->FreeBuffer();

	__datum_buffer = new byte[size];
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

VOID ParamBase::FromBinary(PCBYTE data)
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

VOID ParamBase::FromString(PCCHAR data)
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

#pragma endregion



#pragma region [Param] IMPLEMENTATION

// CONSTRUCTORS

Param::Param(CDATATYPE dataType)
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

Param::Param(RCCONSTVALUE value, CDATATYPE dataType)
{
	_Value = value;
	_DataType = dataType;
}

Param::Param(RCCHAR value)
{
	_Value = value;
	_DataType = DataType::CHAR_DATUM;
}

Param::Param(RCBYTE value)
{
	_Value = value;
	_DataType = DataType::BYTE_DATUM;
}

Param::Param(RCBOOL value)
{
	_Value = value;
	_DataType = DataType::BOOL_DATUM;
}

Param::Param(RCSHORT value)
{
	_Value = value;
	_DataType = DataType::SHORT_DATUM;
}

Param::Param(RCWORD value)
{
	_Value = value;
	_DataType = DataType::WORD_DATUM;
}

Param::Param(RCLONG value)
{
	_Value = value;
	_DataType = DataType::LONG_DATUM;
}

Param::Param(RCDWORD value)
{
	_Value = value;
	_DataType = DataType::DWORD_DATUM;
}

Param::Param(RCFLOAT value)
{
	_Value = value;
	_DataType = DataType::FLOAT_DATUM;
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

RPARAM Param::operator =(RCCONSTVALUE rValue)
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

VarLengthParam::VarLengthParam(CDATATYPE dataType, CSIZE length)
	: Param(dataType), _Length(length)
{
	switch (dataType)
	{
	case DataType::BYTES_DATUM:

		_Value = new byte[length];
		break;

	case DataType::STRING_DATUM:

		_Value = new char[length];
		break;

	case DataType::BIT_DATUM:

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

VarLengthParam::VarLengthParam(RCCONSTVALUE value, CDATATYPE dataType, CSIZE length)
	: Param(value, dataType)
{
	if (_DataType == DataType::STRING_DATUM)
	{
		if (!value.String)
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
	: Param(DataType::BYTES_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthParam::VarLengthParam(PCCHAR value)
	: Param(DataType::STRING_DATUM)
{
	_Dispose = FALSE;

	_Value = value;

	if (!value)
		_Length = 0;
	else
		_Length = strlen(value);
}

VarLengthParam::VarLengthParam(PCBITPACK value, CSIZE length)
	: Param(DataType::BIT_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
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


// [Param] OVERRIDES

CSIZE VarLengthParam::ByteWidth() const
{
	if (_Length > 0)
		return _Length;

	return DatumBase<ConstValue>::ByteWidth();
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
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_PARAMS
