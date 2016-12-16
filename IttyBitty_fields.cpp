/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_VALUES) || defined(NO_ITTYBITTY_DATUM) || \
		defined(NO_ITTYBITTY_DB) && defined(NO_ITTYBITTY_SETTINGS)
	#define NO_ITTYBITTY_FIELDS
#endif

#ifndef NO_ITTYBITTY_FIELDS


#include "IttyBitty_fields.h"

using namespace IttyBitty;


#pragma region [FieldBase] IMPLEMENTATION

// [ISerializable] IMPLEMENTATION

PCBYTE FieldBase::ToBinary() const
{
	CSIZE size = this->BinarySize();

	this->FreeBuffer();

	__datum_buffer = new byte[size];

	this->MetadataToBinary();

	return this->ValueToBinary();
}

PCCHAR FieldBase::ToString() const
{
	CSIZE size = this->StringSize();

	this->FreeBuffer();

	__datum_buffer = new byte[size];
	__datum_buffer[size - 1] = '\0';

	this->MetadataToString();

	return this->ValueToString();
}

VOID FieldBase::FromBinary(PCBYTE data)
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

		_Value = (PBYTE)data;
	}
}

VOID FieldBase::FromString(PCCHAR data)
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

		bytes = (PBYTE)_Value.ByteRef;
		break;

	case DataType::WORD_DATUM:
	case DataType::SHORT_DATUM:

		bytes = (PBYTE)_Value.WordRef;
		break;

	case DataType::DWORD_DATUM:
	case DataType::LONG_DATUM:
	case DataType::FLOAT_DATUM:

		bytes = (PBYTE)_Value.DWordRef;
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

PCBYTE FieldBase::MetadataToBinary() const
{
	PBYTE bufferPtr = __datum_buffer;

	CSIZE byteWidth = this->ByteWidth();
	memcpy(bufferPtr, &byteWidth, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	memcpy(bufferPtr, &_DataType, SIZEOF(DataType));
	bufferPtr += SIZEOF(DataType);

	return __datum_buffer;
}

PCBYTE FieldBase::ValueToBinary() const
{
	PBYTE bufferPtr = __datum_buffer;

	bufferPtr += SIZEOF(CSIZE);
	bufferPtr += SIZEOF(DataType);

	CSIZE byteWidth = this->ByteWidth();

	if (byteWidth > 0)
		memcpy(bufferPtr, *_Value.BytesRef, byteWidth);

	return __datum_buffer;
}

PCCHAR FieldBase::MetadataToString() const
{
	CSIZE byteWidth = this->ByteWidth();

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__datum_buffer);

	bufferPtr = StringInsertValue<CSIZE>(byteWidth, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(static_cast<CBYTE>(this->GetDataType()), bufferPtr);

	return reinterpret_cast<PCCHAR>(__datum_buffer);
}

PCCHAR FieldBase::ValueToString() const
{
	CSIZE byteWidth = this->ByteWidth();

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__datum_buffer);

	bufferPtr += 2 * SIZEOF(CSIZE);
	bufferPtr += 2 * SIZEOF(DataType);

	PCBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_DATUM:
	case DataType::CHAR_DATUM:
	case DataType::BOOL_DATUM:

		bytes = (PBYTE)_Value.ByteRef;
		break;

	case DataType::WORD_DATUM:
	case DataType::SHORT_DATUM:


		bytes = (PBYTE)_Value.WordRef;
		break;

	case DataType::DWORD_DATUM:
	case DataType::LONG_DATUM:
	case DataType::FLOAT_DATUM:

		bytes = (PBYTE)_Value.DWordRef;
		break;

	default:

		bytes = *_Value.BytesRef;

		for (SIZE i = 0; i < byteWidth; i++)
			bufferPtr = StringInsertValue<CBYTE>(bytes[i], bufferPtr);

		return reinterpret_cast<PCCHAR>(__datum_buffer);
	}

	for (SIZE i = 0; i < 4 - byteWidth; i++)
		bufferPtr = StringInsertValue<CBYTE>(bytes[byteWidth - i - 1], bufferPtr);

	return reinterpret_cast<PCCHAR>(__datum_buffer);
}

VOID FieldBase::MetadataFromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	bufferPtr += SIZEOF(CSIZE);

	_DataType = static_cast<DataType>(*bufferPtr++);
}

VOID FieldBase::ValueFromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	bufferPtr += SIZEOF(CSIZE);
	bufferPtr += SIZEOF(DataType);

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

		_Value = (PBYTE)data;
	}
}

VOID FieldBase::MetadataFromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);

	bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
}

VOID FieldBase::ValueFromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);
	bufferPtr += 2 * SIZEOF(DataType);

	CBYTE byteWidth = this->ByteWidth();

	PBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_DATUM:
	case DataType::CHAR_DATUM:
	case DataType::BOOL_DATUM:

		bytes = (PBYTE)_Value.ByteRef;
		break;

	case DataType::WORD_DATUM:
	case DataType::SHORT_DATUM:

		bytes = (PBYTE)_Value.WordRef;
		break;

	case DataType::DWORD_DATUM:
	case DataType::LONG_DATUM:
	case DataType::FLOAT_DATUM:

		bytes = (PBYTE)_Value.DWordRef;
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



#pragma region [Field] IMPLEMENTATION

// CONSTRUCTORS

Field::Field(CDATATYPE dataType)
{
	_Dispose = TRUE;

	_DataType = dataType;
}

Field::Field(RCFIELD other)
{
	_Dispose = other._Dispose;

	_Value = other._Value;
	_DataType = other._DataType;
}

Field::Field(RRFIELD other)
{
	this->~FieldBase();
	new (this) Field(other._Value, other._DataType);
}

Field::Field(RVALUE value, CDATATYPE dataType)
{
	_Value = value;
	_DataType = dataType;
}

Field::Field(RCHAR value)
{
	_Value = value;
	_DataType = DataType::CHAR_DATUM;
}

Field::Field(RBYTE value)
{
	_Value = value;
	_DataType = DataType::BYTE_DATUM;
}

Field::Field(RBOOL value)
{
	_Value = value;
	_DataType = DataType::BOOL_DATUM;
}

Field::Field(RSHORT value)
{
	_Value = value;
	_DataType = DataType::SHORT_DATUM;
}

Field::Field(RWORD value)
{
	_Value = value;
	_DataType = DataType::WORD_DATUM;
}

Field::Field(RLONG value)
{
	_Value = value;
	_DataType = DataType::LONG_DATUM;
}

Field::Field(RDWORD value)
{
	_Value = value;
	_DataType = DataType::DWORD_DATUM;
}

Field::Field(RFLOAT value)
{
	_Value = value;
	_DataType = DataType::FLOAT_DATUM;
}


// STATIC FUNCTIONS

RFIELD Field::NULL_OBJECT()
{
	STATIC Field NULL_FIELD;
	return NULL_FIELD;
}


// OPERATORS

RFIELD Field::operator =(RCFIELD rValue)
{
	*this = Field(rValue);
	return *this;
}

RFIELD Field::operator =(RRFIELD rValue)
{
	*this = Field(rValue);
	return *this;
}

RFIELD Field::operator =(RCVALUE rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCCHAR rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCBYTE rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCBOOL rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCSHORT rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCWORD rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCLONG rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCDWORD rValue)
{
	_Value = rValue;
	return *this;
}

RFIELD Field::operator =(RCFLOAT rValue)
{
	_Value = rValue;
	return *this;
}


Field::operator RCCHAR() const
{
	return _Value;
}

Field::operator RCHAR()
{
	return _Value;
}

Field::operator RCBYTE() const
{
	return _Value;
}

Field::operator RBYTE()
{
	return _Value;
}

Field::operator RCBOOL() const
{
	return _Value;
}

Field::operator RBOOL()
{
	return _Value;
}

Field::operator RCSHORT() const
{
	return _Value;
}

Field::operator RSHORT()
{
	return _Value;
}

Field::operator RCWORD() const
{
	return _Value;
}

Field::operator RWORD()
{
	return _Value;
}

Field::operator RCLONG() const
{
	return _Value;
}

Field::operator RLONG()
{
	return _Value;
}

Field::operator RCDWORD() const
{
	return _Value;
}

Field::operator RDWORD()
{
	return _Value;
}

Field::operator RCFLOAT() const
{
	return _Value;
}

Field::operator RFLOAT()
{
	return _Value;
}

#pragma endregion


#pragma region [VarLengthField] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

VarLengthField::VarLengthField(CDATATYPE dataType, CSIZE length)
	: Field(dataType), _Length(length)
{
	switch (dataType)
	{
	case DataType::BYTES_DATUM:

		_Value = Value(new byte[length]);
		break;

	case DataType::STRING_DATUM:

		_Value = Value(new char[length]);
		break;

	case DataType::BIT_DATUM:

		_Value = Value(new BITPACK[length]);
		break;

	default:
		break;
	}
}

VarLengthField::VarLengthField(RCVARLENGTHFIELD other)
{
	_Dispose = other._Dispose;

	_Value = other._Value;
	_DataType = other._DataType;
	_Length = other._Length;
}

VarLengthField::VarLengthField(RRVARLENGTHFIELD other)
{
	this->~VarLengthField();
	new (this) VarLengthField(other._Value, other._DataType, other._Length);
}

VarLengthField::VarLengthField(RVALUE value, CDATATYPE dataType, CSIZE length)
	: Field(value, dataType)
{
	if (_DataType == DataType::STRING_DATUM)
	{
		if (!value.StringRef)
			_Length = 0;
		else
			_Length = strlen((PCCHAR)_Value);
	}
	else
	{
		_Length = length;
	}
}

VarLengthField::VarLengthField(PBYTE value, CSIZE length)
	: Field(DataType::BYTES_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthField::VarLengthField(PCHAR value)
	: Field(DataType::STRING_DATUM)
{
	_Dispose = FALSE;

	_Value = value;

	if (!value)
		_Length = 0;
	else
		_Length = strlen(value);
}

VarLengthField::VarLengthField(PBITPACK value, CSIZE length)
	: Field(DataType::BIT_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}


// OPERATORS

RVARLENGTHFIELD VarLengthField::operator =(RCVARLENGTHFIELD rValue)
{
	*this = VarLengthField(rValue);
	return *this;
}

RVARLENGTHFIELD VarLengthField::operator =(RRVARLENGTHFIELD rValue)
{
	*this = VarLengthField(rValue);
	return *this;
}

RVARLENGTHFIELD VarLengthField::operator =(PBYTE rValue)
{
	_Value = rValue;
	return *this;
}

RVARLENGTHFIELD VarLengthField::operator =(PCHAR rValue)
{
	_Value = rValue;
	return *this;
}

RVARLENGTHFIELD VarLengthField::operator =(PBITPACK rValue)
{
	_Value = rValue;
	return *this;
}


VarLengthField::operator PCBYTE() const
{
	return _Value;
}

VarLengthField::operator PBYTE()
{
	return _Value;
}

VarLengthField::operator PCCHAR() const
{
	return _Value;
}

VarLengthField::operator PCHAR()
{
	return _Value;
}

VarLengthField::operator PCBITPACK() const
{
	return _Value;
}

VarLengthField::operator PBITPACK()
{
	return _Value;
}



// [Field] OVERRIDES

CSIZE VarLengthField::ByteWidth() const
{
	if (_Length > 0)
		return _Length;

	return DatumBase<Value>::ByteWidth();
}

VOID VarLengthField::MetadataFromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_Length = *reinterpret_cast<PCSIZE>(bufferPtr);

	FieldBase::MetadataFromBinary(data);
}

VOID VarLengthField::MetadataFromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

	FieldBase::MetadataFromString(data);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_FIELDS
