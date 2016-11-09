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
	

#pragma region [DbTableSet]/[DbTableDef] PARSING GLOBAL FUNCTION DEFINITIONS
	
	//PIDBTABLESET DbTableSetFromBytes(PCBYTE data)
	//{
	//	PIDBTABLESET dbTableSet = new DbTableSet();

	//	dbTableSet->FromBinary(data);

	//	return dbTableSet;
	//}
	//
	//PIDBTABLESET DbTableSetFromString(PCCHAR data)
	//{
	//	PIDBTABLESET dbTableSet = new DbTableSet();

	//	dbTableSet->FromString(data);

	//	return dbTableSet;
	//}
	
	//PIDBTABLEDEF DbTableDefFromBytes(PCBYTE data)
	//{
	//	PIDBTABLEDEF dbTableDef = new DbTableDef();

	//	dbTableDef->FromBinary(data);

	//	return dbTableDef;
	//}
	//
	//PIDBTABLEDEF DbTableDefFromString(PCCHAR data)
	//{
	//	PIDBTABLEDEF dbTableDef = new DbTableDef();

	//	dbTableDef->FromString(data);

	//	return dbTableDef;
	//}

#pragma endregion


#pragma region [DbTableDef] IMPLEMENTATION
/*
DbTableDef::DbTableDef(CBYTE)
{
}

DbTableDef::DbTableDef(PCBYTE)
{
}

DbTableDef::DbTableDef(PCCHAR)
{
}

DbTableDef::DbTableDef(RCIDBTABLEDEF)
{
}

DbTableDef::DbTableDef(CBYTE, PPIDBTABLEDEF)
{
}

DbTableDef::~DbTableDef()
{
}

		
// PROTECTED DISPOSAL METHOD

VOID DbTableDef::Dispose()
{
}

PCIDBTABLEDEF operator[]DbTableDef::(CBYTE) const
{
}

PIDBTABLEDEF operator[]DbTableDef::(CBYTE)
{
}
				

// [IDbTableDef] IMPLEMENTATION
		
CBYTE DbTableDef::TableDefCount() const
{
}
		
RCIDBTABLEDEF DbTableDef::TableDef(CBYTE) const
{
}

RIDBTABLEDEF DbTableDef::TableDef(CBYTE)
{
}

RCIDBTABLEDEF DbTableDef::TableDef(PCCHAR) const
{
}

RIDBTABLEDEF DbTableDef::TableDef(PCCHAR)
{
}
				

// [IStorable] IMPLEMENTATION

STORAGERESULT DbTableDef::SaveAsBinary(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTableDef::SaveAsString(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTableDef::LoadFromBinary(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTableDef::LoadFromString(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}
		

// [ISerializable] IMPLEMENTATION

CSIZE DbTableDef::BinarySize() const
{
}

CSIZE DbTableDef::StringSize() const
{
}

PCBYTE DbTableDef::ToBinary() const
{
}

PCCHAR DbTableDef::ToString() const
{
}

VOID DbTableDef::FromBinary(PCBYTE data)
{
}

VOID DbTableDef::FromString(PCCHAR data)
{
}
		
#ifdef ARDUINO		

SIZE DbTableDef::printTo(Print & printer) const
{
}

#endif

		
// [IDbTableDef] HELPER METHODS

CSIZE DbTableDef::TableDefsByteSize() const
{
}

CSIZE DbTableDef::TableDefsStringSize() const
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

STORAGERESULT DbTableDef::SaveAsBinary(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTableDef::SaveAsString(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTableDef::LoadFromBinary(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTableDef::LoadFromString(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTableDef::BinarySize() const
{
	return SIZEOF(CSIZE) + SIZEOF(CBYTE) + this->TableNameLength() + SIZEOF(CDWORD);
}

CSIZE DbTableDef::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(CBYTE) + this->TableNameLength() + 2 * SIZEOF(CDWORD) + 1;
}

PCBYTE DbTableDef::ToBinary() const
{
	CSIZE size = this->BinarySize();

	if (__db_table_def_buffer)
		delete[] __db_table_def_buffer;

	__db_table_def_buffer = new byte[size];

	PBYTE bufferPtr = __db_table_def_buffer;
	
	memcpy(bufferPtr, &size, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	CSIZE rowSize = this->RowSize();
	memcpy(bufferPtr, &rowSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	CBYTE tableNameLength = this->TableNameLength();
	memcpy(bufferPtr, &tableNameLength, SIZEOF(CBYTE));
	bufferPtr += SIZEOF(CBYTE);

	if (tableNameLength > 0)
	{
		memcpy(bufferPtr, _TableName, tableNameLength);
		bufferPtr += tableNameLength;
	}
	
	CDWORD addrOffset = this->GetAddrOffset();
	memcpy(bufferPtr, &addrOffset, SIZEOF(CDWORD));
	bufferPtr += SIZEOF(CDWORD);

	return __db_table_def_buffer;
}

PCCHAR DbTableDef::ToString() const
{	
	CSIZE size = this->StringSize();
	
	if (__db_table_def_buffer)
		delete[] __db_table_def_buffer;

	__db_table_def_buffer = new byte[size];
	__db_table_def_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__db_table_def_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(this->RowSize(), bufferPtr);

	CBYTE tableNameLength = this->TableNameLength();
	bufferPtr = StringInsertValue<CBYTE>(tableNameLength, bufferPtr);

	if (tableNameLength > 0)
	{
		memcpy(bufferPtr, _TableName, tableNameLength);
		bufferPtr += tableNameLength;
	}

	bufferPtr = StringInsertValue<CDWORD>(this->GetAddrOffset(), bufferPtr);
	
	return reinterpret_cast<PCCHAR>(__db_table_def_buffer);
}

VOID DbTableDef::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;
	
	bufferPtr += SIZEOF(CSIZE);

	_RowSize = static_cast<SIZE>(*bufferPtr);
	bufferPtr += SIZEOF(SIZE);

	CBYTE tableNameLength = static_cast<CBYTE>(*bufferPtr++);

	if (tableNameLength > 0)
	{
		PCHAR tableName = new char[tableNameLength + 1];
		tableName[tableNameLength] = '\0';

		memcpy(tableName, bufferPtr, tableNameLength);

		_TableName = MAKE_CONST(tableName);

		bufferPtr += tableNameLength;
	}

	_AddrOffset = static_cast<DWORD>(*bufferPtr);
}

VOID DbTableDef::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);

	bufferPtr = StringReadValue<SIZE>(_RowSize, bufferPtr);
	

	BYTE tableNameLength = 0;
	bufferPtr = StringReadValue<BYTE>(tableNameLength, bufferPtr);

	if (tableNameLength > 0)
	{
		PCHAR tableName = new char[tableNameLength + 1];
		tableName[tableNameLength] = '\0';

		memcpy(tableName, bufferPtr, tableNameLength);

		_TableName = MAKE_CONST(tableName);

		bufferPtr += tableNameLength;
	}

	bufferPtr = StringReadValue<DWORD>(_AddrOffset, bufferPtr);
}
		
#ifdef ARDUINO		

SIZE DbTableDef::printTo(Print & printer) const
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

	delete[] __db_table_def_buffer;
	__db_table_def_buffer = NULL;

	return size;
}

#endif


// [IDbTableDef] IHELPER METHODS

CBYTE DbTableDef::TableNameLength() const
{
	if (_TableName == NULL)
		return (CBYTE)0;

	return (CBYTE)strlen(_TableName);
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_DEFS
