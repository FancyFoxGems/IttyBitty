/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/


#include "IttyBitty_fields.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

CBYTE IttyBitty::DATA_SIZE_MASK = 0xF0;

PBYTE IttyBitty::__field_buffer;

#pragma endregion


#pragma region FieldBase DEFINITION

// DESTRUCTOR

FieldBase::~FieldBase()
{
	if (_Dispose)
		_Value.FreePtr();
}
				

// ISerializable IMPLEMENTATION

CSIZE FieldBase::ByteSize() const
{
	return SIZEOF(CSIZE) + SIZEOF(DataType) + this->ByteWidth();
}

CSIZE FieldBase::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(DataType) + this->StringLength() + 1;
}

CSIZE FieldBase::ByteWidth() const
{
	return TRAILING_ZERO_BITS(static_cast<BYTE>(this->GetDataSize())) - 0x3;
}

CSIZE FieldBase::StringLength() const
{
	return 2 * this->ByteWidth();
}

PCBYTE FieldBase::ToBytes() const
{
	CSIZE size = this->ByteSize();

	if (__field_buffer)
		delete[] __field_buffer;

	__field_buffer = new BYTE[size];

	PBYTE bufferPtr = __field_buffer;
	
	CSIZE byteWidth = this->ByteWidth();
	memcpy(bufferPtr, &byteWidth, SIZEOF(byteWidth));
	bufferPtr += SIZEOF(byteWidth);

	memcpy(bufferPtr, &_DataType, SIZEOF(_DataType));
	bufferPtr += SIZEOF(_DataType);

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

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__field_buffer);

	bufferPtr = StringInsertValue<CSIZE>(byteWidth, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(static_cast<CBYTE>(this->GetDataType()), bufferPtr);

	PCBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_FIELD:
	case DataType::CHAR_FIELD:
	case DataType::BOOL_FIELD:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_FIELD:
	case DataType::SHORT_FIELD:
		

		bytes = (PBYTE)&(_Value.Word);
		break;
			
	case DataType::DWORD_FIELD:
	case DataType::LONG_FIELD:	
	case DataType::FLOAT_FIELD:

		bytes = (PBYTE)&(_Value.DWord);
		break;

	default:

		bytes = _Value.Bytes;

		for (SIZE i = 0; i < byteWidth; i++)
			bufferPtr = StringInsertValue<CBYTE>(bytes[i], bufferPtr);
	
		__field_buffer[size - 1] = '\0';

		return reinterpret_cast<PCCHAR>(__field_buffer);
	}

	for (SIZE i = 4 - byteWidth; i < byteWidth; i++)
		bufferPtr = StringInsertValue<CBYTE>(bytes[i], bufferPtr);
	
	__field_buffer[size - 1] = '\0';

	return reinterpret_cast<PCCHAR>(__field_buffer);
}

VOID FieldBase::FromBytes(PCBYTE data)
{
	data += SIZEOF(CSIZE);

	_DataType = static_cast<DataType>(*data++);

	switch (_DataType)
	{
	case DataType::BYTE_FIELD:
	case DataType::CHAR_FIELD:
	case DataType::BOOL_FIELD:

		_Value = *((PBYTE)data);
		break;
		
	case DataType::WORD_FIELD:
	case DataType::SHORT_FIELD:
		

		_Value = *((PWORD)data);
		break;
		
	case DataType::DWORD_FIELD:
	case DataType::LONG_FIELD:		
	case DataType::FLOAT_FIELD:

		_Value = *((PDWORD)data);
		break;

	default:

		_Value = data;
	}
}

VOID FieldBase::FromString(PCCHAR data)
{
	data += 2 * SIZEOF(CSIZE);

	data = StringReadValue<DataType>(_DataType, data);

	CBYTE byteWidth = this->ByteWidth();

	PBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_FIELD:
	case DataType::CHAR_FIELD:
	case DataType::BOOL_FIELD:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_FIELD:
	case DataType::SHORT_FIELD:
		

		bytes = (PBYTE)&(_Value.Word);
		break;
		
	case DataType::DWORD_FIELD:
	case DataType::LONG_FIELD:		
	case DataType::FLOAT_FIELD:

		bytes = (PBYTE)&(_Value.DWord);
		break;

	default:

		for (BYTE i = 0; i < byteWidth; i++)
			data = StringReadValue<BYTE>(bytes[i], data);

		_Value = bytes;

		return;
	}
	
	for (SIZE i = 0 ; i < byteWidth; i++)
		data = StringReadValue<BYTE>(bytes[byteWidth - i - 1], data);
}

SIZE FieldBase::printTo(Print & printer) const
{
#ifdef _DEBUG
	SIZE size = this->StringSize();
	PCCHAR buffer = this->ToString();
#else
	SIZE size = this->ByteSize();
	PCBYTE buffer = this->ToBytes();
#endif

	for (SIZE i = 0; i < size; i++)
		size += printer.print(buffer[i]);

	return size;
}


// IField IMPLEMENTATION

CONST DataSize FieldBase::GetDataSize() const
{
	return DataTypeToDataSize(_DataType);
}

CONST DataType FieldBase::GetDataType() const
{
	return _DataType;
}

#pragma endregion



#pragma region Field DEFINITION

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
	new (this) Field(other._Value, other._DataType);
}

Field::Field(RCVALUE value, CONST DataType dataType)
{
	_Value = value;
	_DataType = dataType;
}

Field::Field(RCCHAR value)
{
	_Value = value;
	_DataType = DataType::CHAR_FIELD;
}

Field::Field(RCBYTE value)
{
	_Value = value;
	_DataType = DataType::BYTE_FIELD;
}

Field::Field(RCBOOL value)
{
	_Value = value;
	_DataType = DataType::BOOL_FIELD;
}

Field::Field(RCSHORT value)
{
	_Value = value;
	_DataType = DataType::SHORT_FIELD;
}

Field::Field(RCWORD value)
{
	_Value = value;
	_DataType = DataType::WORD_FIELD;
}

Field::Field(RCLONG value)
{
	_Value = value;
	_DataType = DataType::LONG_FIELD;
}

Field::Field(RCDWORD value)
{
	_Value = value;
	_DataType = DataType::DWORD_FIELD;
}

Field::Field(RCFLOAT value)
{
	_Value = value;
	_DataType = DataType::FLOAT_FIELD;
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


#pragma region VarLengthField DEFINITION

// CONSTRUCTORS/DESTRUCTOR

VarLengthField::VarLengthField(CONST DataType dataType, CSIZE length) 
	: Field(dataType), _Length(length)
{
	switch (dataType)
	{
	case DataType::BYTES_FIELD:
		_Dispose = TRUE;
		_Value = new BYTE[length];
		break;

	case DataType::STRING_FIELD:
		_Dispose = TRUE;
		_Value = new CHAR[length];
		break;

	case DataType::BIT_FIELD:
		_Dispose = TRUE;
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
	new (this) VarLengthField(other._Value, other._DataType, other._Length);
}

VarLengthField::VarLengthField(RCVALUE value, CONST DataType dataType, CSIZE length) 
	: Field(value, dataType), _Length(length) { }

VarLengthField::VarLengthField(PCBYTE value, CSIZE length) 
	: Field(DataType::BYTES_FIELD), _Length(length) { }

VarLengthField::VarLengthField(PCCHAR value) 
	: Field(DataType::STRING_FIELD)
{
	if (value == NULL)
		_Length = 0;
	else
		_Length = strlen(MAKE_CONST(value));
}

VarLengthField::VarLengthField(PCBITPACK value, CSIZE length) 
	: Field(DataType::BIT_FIELD), _Length(length) { }

VarLengthField::~VarLengthField()
{
	if (_Dispose)
	{
		if (_Length > 0)
			_Value.FreeData();
		else
			_Value.FreePtr();
	}
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

CSIZE VarLengthField::ByteSize() const
{
	return sizeof(_Length) + Field::ByteSize();
}

CSIZE VarLengthField::StringSize() const
{
	return 2 * sizeof(_Length) + Field::StringSize();
}

CSIZE VarLengthField::ByteWidth() const
{
	if (_Length > 0)
		return _Length;

	return Field::ByteWidth();
}

CSIZE VarLengthField::StringLength() const
{
	if (_DataType == DataType::STRING_FIELD)
		return _Length;
			
	return Field::StringLength();
}

VOID VarLengthField::FromBytes(PCBYTE data)
{
	_Length = static_cast<DataType>(*reinterpret_cast<PCSIZE>(data));
	data += SIZEOF(CSIZE);

	_DataType = static_cast<DataType>(*data++);

	_Value = data;
}

VOID VarLengthField::FromString(PCCHAR data)
{
	CBYTE byteWidth = this->ByteWidth();
	
	data = StringReadValue<SIZE>(_Length, data);

	PBYTE bytes = NULL;

	switch (_DataType)
	{
	case DataType::BYTE_FIELD:
	case DataType::CHAR_FIELD:
	case DataType::BOOL_FIELD:

		bytes = (PBYTE)&(_Value.Byte);
		break;
		
	case DataType::WORD_FIELD:
	case DataType::SHORT_FIELD:
		

		bytes = (PBYTE)&(_Value.Word);
		break;
		
	case DataType::FLOAT_FIELD:
	case DataType::LONG_FIELD:		
	case DataType::DWORD_FIELD:

		bytes = (PBYTE)&(_Value.DWord);
		break;

	default:

		for (BYTE i = 0; i < byteWidth; i++)
			data = StringReadValue<BYTE>(bytes[i], data);

		_Value = bytes;

		return;
	}

	for (SIZE i = 4 - byteWidth; i < byteWidth; i++)
		data = StringReadValue<BYTE>(bytes[i], data);
}

#pragma endregion