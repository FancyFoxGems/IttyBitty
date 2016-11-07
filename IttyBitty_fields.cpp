/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(EXCLUDE_ITTYBITTY_DB) && !defined(EXCLUDE_ITTYBITTY_FIELDS)
	#define EXCLUDE_ITTYBITTY_FIELDS
#endif

#ifndef EXCLUDE_ITTYBITTY_FIELDS


#include "IttyBitty_fields.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLE DEFINITIONS

PBYTE IttyBitty::__field_buffer = NULL;

#pragma endregion
	

#pragma region FIELD PARSING GLOBAL FUNCTION DEFINITIONS
	
	PIFIELD FieldFromBytes(PCBYTE data)
	{
		PIFIELD datum = NULL;

		SIZE length = static_cast<SIZE>(*data);

		if (length == 0 || length > 4)
			datum = new VarLengthField();
		else
			datum = new Field();

		datum->FromBinary(data);

		return datum;
	}
	
	PIFIELD FieldFromString(PCCHAR data)
	{
		PIFIELD datum = NULL;
		SIZE length = 0;

		StringReadValue<SIZE>(length, data);

		if (length == 0 || length > 4)
			datum = new VarLengthField();
		else
			datum = new Field();

		datum->FromString(data);

		return datum;
	}

#pragma endregion


#pragma region [FieldBase] IMPLEMENTATION

// DESTRUCTOR

FieldBase::~FieldBase()
{
	if (!_Dispose)
		return;

	if (_DataType == DataType::BYTES_DATUM || _DataType == DataType::STRING_DATUM || _DataType == DataType::BIT_DATUM)
		_Value.FreeData();
}
				

// ISerializable IMPLEMENTATION

PCBYTE FieldBase::ToBinary() const
{
	CSIZE size = this->BinarySize();

	if (__field_buffer)
		delete[] __field_buffer;

	__field_buffer = new BYTE[size];

	PBYTE bufferPtr = __field_buffer;
	
	CSIZE byteWidth = this->ByteWidth();
	memcpy(bufferPtr, &byteWidth, SIZEOF(byteWidth));
	bufferPtr += SIZEOF(byteWidth);

	memcpy(bufferPtr, &_DataType, SIZEOF(DataType));
	bufferPtr += SIZEOF(DataType);

	if (byteWidth > 0)
		memcpy(bufferPtr, _Value.Bytes, this->ByteWidth());

	return __field_buffer;
}

PCCHAR FieldBase::ToString() const
{
	CSIZE size = this->StringSize();
	CSIZE byteWidth = this->ByteWidth();
	
	if (__field_buffer)
		delete[] __field_buffer;

	__field_buffer = new BYTE[size];
	__field_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__field_buffer);

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

		return reinterpret_cast<PCCHAR>(__field_buffer);
	}
	
	for (SIZE i = 0; i < 4 - byteWidth; i++)
		bufferPtr = StringInsertValue<CBYTE>(bytes[byteWidth - i - 1], bufferPtr);
	
	return reinterpret_cast<PCCHAR>(__field_buffer);
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

		_Value = data;
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



#pragma region [Field] IMPLEMENTATION

// CONSTRUCTORS

Field::Field(CONST DataType dataType)
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

Field::Field(RCCONSTVALUE value, CONST DataType dataType)
{
	_Value = value;
	_DataType = dataType;
}

Field::Field(RCCHAR value)
{
	_Value = value;
	_DataType = DataType::CHAR_DATUM;
}

Field::Field(RCBYTE value)
{
	_Value = value;
	_DataType = DataType::BYTE_DATUM;
}

Field::Field(RCBOOL value)
{
	_Value = value;
	_DataType = DataType::BOOL_DATUM;
}

Field::Field(RCSHORT value)
{
	_Value = value;
	_DataType = DataType::SHORT_DATUM;
}

Field::Field(RCWORD value)
{
	_Value = value;
	_DataType = DataType::WORD_DATUM;
}

Field::Field(RCLONG value)
{
	_Value = value;
	_DataType = DataType::LONG_DATUM;
}

Field::Field(RCDWORD value)
{
	_Value = value;
	_DataType = DataType::DWORD_DATUM;
}

Field::Field(RCFLOAT value)
{
	_Value = value;
	_DataType = DataType::FLOAT_DATUM;
}


// STATIC FUNCTIONS

RFIELD Field::NULL_OBJECT()
{
	STATIC Field NULL_DATUM;
	return NULL_DATUM;
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

RFIELD Field::operator =(RCCONSTVALUE rValue)
{
	_Value = rValue;
	return *this;
}


Field::operator RCCHAR() const
{
	return _Value;
}

Field::operator RCBYTE() const
{
	return _Value;
}

Field::operator RCBOOL() const
{
	return _Value;
}
Field::operator RCSHORT() const
{
	return _Value;
}

Field::operator RCWORD() const
{
	return _Value;
}

Field::operator RCLONG() const
{
	return _Value;
}

Field::operator RCDWORD() const
{
	return _Value;
}

Field::operator RCFLOAT() const
{
	return _Value;
}

#pragma endregion


#pragma region [VarLengthField] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

VarLengthField::VarLengthField(CONST DataType dataType, CSIZE length) 
	: Field(dataType), _Length(length)
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

VarLengthField::VarLengthField(RCCONSTVALUE value, CONST DataType dataType, CSIZE length) 
	: Field(value, dataType)
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

VarLengthField::VarLengthField(PCBYTE value, CSIZE length) 
	: Field(DataType::BYTES_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthField::VarLengthField(PCCHAR value) 
	: Field(DataType::STRING_DATUM)
{
	_Dispose = FALSE;
	
	_Value = value;

	if (value == NULL)
		_Length = 0;
	else
		_Length = strlen(value);
}

VarLengthField::VarLengthField(PCBITPACK value, CSIZE length) 
	: Field(DataType::BIT_DATUM), _Length(length)
{
	_Dispose = FALSE;

	_Value = value;
}

VarLengthField::~VarLengthField()
{
	if (!_Dispose)
		return;
	
	//if (_Length > 0 || _DataType == DataType::STRING_DATUM)
	//	_Value.FreeData();
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


VarLengthField::operator PCBYTE() const
{
	return _Value;
}

VarLengthField::operator PCCHAR() const
{
	return _Value;
}

VarLengthField::operator PCBITPACK() const
{
	return _Value;
}


// Field OVERRIDES

CSIZE VarLengthField::ByteWidth() const
{
	if (_Length > 0)
		return _Length;

	return DatumBase<ConstValue>::ByteWidth();
}

VOID VarLengthField::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
	FieldBase::FromBinary(data);
}

VOID VarLengthField::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

	FieldBase::FromString(data);
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_FIELDS
