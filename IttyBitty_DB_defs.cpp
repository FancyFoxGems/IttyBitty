/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(EXCLUDE_ITTYBITTY_DB)) && !defined(EXCLUDE_ITTYBITTY_DB_DEFS)
	#define EXCLUDE_ITTYBITTY_DB_DEFS
#endif

#ifndef EXCLUDE_ITTYBITTY_DB_DEFS


#include "IttyBitty_DB_defs.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE DEFINITIONS

PBYTE IttyBitty::__db_table_set_buffer = NULL;
PBYTE IttyBitty::__db_table_def_buffer = NULL;

#pragma endregion


#pragma region [DbTableSet] IMPLEMENTATION
/*
DbTableSet::DbTableSet(CBYTE)
{
}

DbTableSet::DbTableSet(PCBYTE)
{
}

DbTableSet::DbTableSet(PCCHAR)
{
}

DbTableSet::DbTableSet(RCIDBTABLEDEF)
{
}

DbTableSet::DbTableSet(CBYTE, PPIDBTABLEDEF)
{
}

DbTableSet::~DbTableSet()
{
}

		
// PROTECTED DISPOSAL METHOD

VOID DbTableSet::Dispose()
{
}

PCIDBTABLEDEF operator[]DbTableSet::(CBYTE) const
{
}

PIDBTABLEDEF operator[]DbTableSet::(CBYTE)
{
}
				

// [IDbTableSet] IMPLEMENTATION
		
CBYTE DbTableSet::TableDefCount() const
{
}
		
RCIDBTABLEDEF DbTableSet::TableDef(CBYTE) const
{
}

RIDBTABLEDEF DbTableSet::TableDef(CBYTE)
{
}

RCIDBTABLEDEF DbTableSet::TableDef(PCCHAR) const
{
}

RIDBTABLEDEF DbTableSet::TableDef(PCCHAR)
{
}
				

// [IStorable] IMPLEMENTATION

MEDIARESULT DbTableSet::SaveAsBinary(RCISTORAGE) const
{
}

MEDIARESULT DbTableSet::SaveAstring(RCISTORAGE) const
{
}

MEDIARESULT DbTableSet::LoadFromBinary(RCISTORAGE)
{
}

MEDIARESULT DbTableSet::LoadFromString(RCISTORAGE)
{
}
		

// [ISerializable] IMPLEMENTATION

CSIZE DbTableSet::BinarySize() const
{
}

CSIZE DbTableSet::StringSize() const
{
}

PCBYTE DbTableSet::ToBinary() const
{
}

PCCHAR DbTableSet::ToString() const
{
}

VOID DbTableSet::FromBinary(PCBYTE)
{
}

VOID DbTableSet::FromString(PCCHAR)
{
}
		
#ifdef ARDUINO		

SIZE DbTableSet::printTo(Print &) const
{
}

#endif

		
// [IDbTableSet] HELPER METHODS

CSIZE DbTableSet::TableDefsByteSize() const
{
}

CSIZE DbTableSet::TableDefsStringSize() const
{
}
*/
#pragma endregion


#pragma region [DbTableDef] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

DbTableDef::DbTableDef(CSIZE rowSize, PCCHAR tableName, CDWORD addrOffset) 
	: _RowSize(rowSize), _TableName(tableName), _AddrOffset(addrOffset) { }

DbTableDef::DbTableDef(PCBYTE data)
{
	this->FromBinary(data);
}
DbTableDef::DbTableDef(PCCHAR data)
{
	this->FromString(data);
}

DbTableDef::~DbTableDef()
{
	this->Dispose();
}
		

// PROTECTED DISPOSAL METHOD

VOID DbTableDef::Dispose()
{
	delete _TableName;
	_TableName = NULL;
}
		

// [IDbTableDef] IMPLEMENTATION
		
CSIZE DbTableDef::RowSize() const
{
	return _RowSize;
}

DWORD DbTableDef::GetAddrOffset() const
{
	return _AddrOffset;
}

PCCHAR DbTableDef::GetTableName() const
{
	return _TableName;
}
		
VOID DbTableDef::SetAddrOffset(CDWORD addrOffset)
{
	_AddrOffset = addrOffset;
}

VOID DbTableDef::SetTableName(PCCHAR tableName)
{
	_TableName = tableName;
}
				

// [IStorable] IMPLEMENTATION

MEDIARESULT DbTableDef::SaveAsBinary(RCISTORAGE storage) const
{
}

MEDIARESULT DbTableDef::SaveAstring(RCISTORAGE storage) const
{
}

MEDIARESULT DbTableDef::LoadFromBinary(RCISTORAGE storage)
{
}

MEDIARESULT DbTableDef::LoadFromString(RCISTORAGE storage)
{
}

//
//// [ISerializable] IMPLEMENTATION
//
//CSIZE DbTableDef::BinarySize() const
//{
//	return SIZEOF(CSIZE) + SIZEOF(DataType) + this->ByteWidth();
//}
//
//CSIZE DbTableDef::StringSize() const
//{
//	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(DataType) + this->StringLength() + 1;
//}
//
//PCBYTE DbTableDef::ToBinary() const
//{
//	CSIZE size = this->BinarySize();
//
//	if (__datum_buffer)
//		delete[] __datum_buffer;
//
//	__datum_buffer = new BYTE[size];
//
//	this->MetadataToBinary();
//
//	return this->ValueToBinary();
//}
//
//PCCHAR DbTableDef::ToString() const
//{
//	CSIZE size = this->StringSize();
//	CSIZE byteWidth = this->ByteWidth();
//	
//	if (__datum_buffer)
//		delete[] __datum_buffer;
//
//	__datum_buffer = new BYTE[size];
//	__datum_buffer[size - 1] = '\0';
//
//	this->MetadataToString();
//	
//	return this->ValueToString();
//}
//
//VOID DbTableDef::FromBinary(PCBYTE)
//{
//	PCBYTE bufferPtr = data;
//
//	bufferPtr += SIZEOF(CSIZE);
//
//	_DataType = static_cast<DataType>(*bufferPtr++);
//
//	switch (_DataType)
//	{
//	case DataType::BYTE_DATUM:
//	case DataType::CHAR_DATUM:
//	case DataType::BOOL_DATUM:
//
//		_Value = *((PBYTE)bufferPtr);
//		break;
//		
//	case DataType::WORD_DATUM:
//	case DataType::SHORT_DATUM:
//		
//
//		_Value = *((PWORD)bufferPtr);
//		break;
//		
//	case DataType::DWORD_DATUM:
//	case DataType::LONG_DATUM:		
//	case DataType::FLOAT_DATUM:
//
//		_Value = *((PDWORD)bufferPtr);
//		break;
//
//	default:
//
//		_Value = (PBYTE)data;
//	}
//}
//
//VOID DbTableDef::FromString(PCCHAR)
//{
//	PCCHAR bufferPtr = data;
//
//	bufferPtr += 2 * SIZEOF(CSIZE);
//
//	bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
//
//	CBYTE byteWidth = this->ByteWidth();
//
//	PBYTE bytes = NULL;
//	
//	switch (_DataType)
//	{
//	case DataType::BYTE_DATUM:
//	case DataType::CHAR_DATUM:
//	case DataType::BOOL_DATUM:
//
//		bytes = (PBYTE)_Value.ByteRef;
//		break;
//		
//	case DataType::WORD_DATUM:
//	case DataType::SHORT_DATUM:		
//
//		bytes = (PBYTE)_Value.WordRef;
//		break;
//		
//	case DataType::DWORD_DATUM:
//	case DataType::LONG_DATUM:		
//	case DataType::FLOAT_DATUM:
//
//		bytes = (PBYTE)_Value.DWordRef;
//		break;
//
//	default:
//		
//		for (BYTE i = 0; i < byteWidth; i++)
//			bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);
//
//		_Value = bytes;
//
//		return;
//	}
//	
//	for (SIZE i = 0 ; i < byteWidth; i++)
//		bufferPtr = StringReadValue<BYTE>(bytes[byteWidth - i - 1], bufferPtr);
//}
//		
//#ifdef ARDUINO		
//
//SIZE DbTableDef::printTo(Print &) const
//{
//#ifdef _DEBUG
//	SIZE size = this->StringSize();
//	PCCHAR buffer = this->ToString();
//#else
//	SIZE size = this->BinarySize();
//	PCBYTE buffer = this->ToBinary();
//#endif
//
//	for (SIZE i = 0; i < size; i++)
//		printer.print(buffer[i]);
//
//	delete[] __datum_buffer;
//	__datum_buffer = NULL;
//
//	return size;
//}
//
//#endif

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_DEFS
