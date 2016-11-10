/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(EXCLUDE_ITTYBITTY_DB)) && !defined(EXCLUDE_ITTYBITTY_DB_TABLES)
	#define EXCLUDE_ITTYBITTY_DB_TABLES
#endif

#ifndef EXCLUDE_ITTYBITTY_DB_TABLES


#include "IttyBitty_DB_tables.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE DEFINITION

PBYTE IttyBitty::__db_table_buffer = NULL;

#pragma endregion


#pragma region [DbTable] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

DbTable::DbTable(CSIZE rowSize, PCCHAR tableName, RCDWORD addrOffset, RCDWORD capacity) : _Capacity(capacity)
{
	_TableDef = new DbTableDef(rowSize, tableName, addrOffset);
}

DbTable::DbTable(PCBYTE data)
{
	this->FromBinary(data);
}

DbTable::DbTable(PCCHAR data)
{
	this->FromString(data);
}

DbTable::~DbTable()
{
	this->Dispose();
}


// STATIC FUNCTIONS

RDBTABLE DbTable::NULL_OBJECT()
{
	STATIC DbTable NULL_DBTABLE;
	return NULL_DBTABLE;
}


// PROTECTED DISPOSAL METHOD

VOID DbTable::Dispose()
{
	delete _TableDef;
	_TableDef = NULL;
}


// [IDbTable] IMPLEMENTATION

CDWORD DbTable::Size() const
{
	return this->RowCount() * this->RowSize();
}

CDWORD DbTable::Capacity() const
{
	return _Capacity;
}

CSIZE DbTable::RowCount() const
{
	return _RowCount;
}

CSIZE DbTable::RowsAvailable() const
{
	return (CSIZE)(this->Capacity() - this->Size()) / this->RowSize();
}

CDBRESULT DbTable::Grow(RCFLOAT growthFactor)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Shrink(RCFLOAT shrinkFactor)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::SelectAll(PBYTE & resultRows, RSIZE resultCount)
{
	return this->SelectAllRows(resultRows, resultCount);
}

CDBRESULT DbTable::Find(CSIZE rowIndex, PBYTE resultRow, PSIZE resultSize)
{
	return this->FindRow(rowIndex, resultRow, resultSize);
}

CDBRESULT DbTable::Insert(PCBYTE rowData, CSIZE rowIndex)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Update(PCBYTE rowData, CSIZE rowIndex, PSIZE rowsAffected)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Delete(CSIZE rowIndex)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Truncate()
{
	return DbResult::SUCCESS;
}


// [IDbTableDef] IMPLEMENTATION

CSIZE DbTable::RowSize() const
{
	return _TableDef->RowSize();
}

DWORD DbTable::GetAddrOffset() const
{
	return _TableDef->GetAddrOffset();
}

PCCHAR DbTable::GetTableName() const
{
	return _TableDef->GetTableName();
}

VOID DbTable::SetAddrOffset(RCDWORD addrOffset)
{
	_TableDef->SetAddrOffset(addrOffset);
}

VOID DbTable::SetTableName(PCCHAR tableName)
{
	_TableDef->SetTableName(tableName);
}


// [IStorable] IMPLEMENTATION

CSTORAGERESULT DbTable::SaveAsBinary(RCISTORAGE storage) const
{
	STORAGERESULT result = _TableDef->SaveAsBinary(storage);
	if ((BOOL)result)
		return result;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::SaveAsString(RCISTORAGE storage) const
{
	STORAGERESULT result = _TableDef->SaveAsString(storage);
	if ((BOOL)result)
		return result;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::LoadFromBinary(RCISTORAGE storage)
{
	STORAGERESULT result = _TableDef->LoadFromBinary(storage);
	if ((BOOL)result)
		return result;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::LoadFromString(RCISTORAGE storage)
{
	STORAGERESULT result = _TableDef->LoadFromString(storage);
	if ((BOOL)result)
		return result;

	return StorageResult::SUCCESS;
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTable::BinarySize() const
{
	return SIZEOF(CSIZE) + SIZEOF(CDWORD) + _TableDef->BinarySize();
}

CSIZE DbTable::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(CDWORD) + _TableDef->StringSize();
}

PCBYTE DbTable::ToBinary() const
{
	CSIZE size = this->BinarySize();

	if (__db_table_buffer)
		delete[] __db_table_buffer;

	__db_table_buffer = new byte[size];

	PBYTE bufferPtr = __db_table_buffer;

	memcpy(bufferPtr, &size, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	CDWORD capacity = this->Capacity();
	memcpy(bufferPtr, &capacity, SIZEOF(CDWORD));
	bufferPtr += SIZEOF(CDWORD);

	CSIZE rowCount = this->RowCount();
	memcpy(bufferPtr, &rowCount, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	PCBYTE tableDefBytes = _TableDef->ToBinary();
	SIZE tableDefSize = _TableDef->BinarySize();

	memcpy(bufferPtr, tableDefBytes, tableDefSize);
	bufferPtr += tableDefSize;

	return __db_table_buffer;
}

PCCHAR DbTable::ToString() const
{
	CSIZE size = this->StringSize();

	if (__db_table_buffer)
		delete[] __db_table_buffer;

	__db_table_buffer = new byte[size];
	__db_table_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__db_table_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CDWORD>(this->Capacity(), bufferPtr);
	bufferPtr = StringInsertValue<CSIZE>(this->RowCount(), bufferPtr);

	PCCHAR tableDefStr = _TableDef->ToString();
	SIZE tableDefSize = _TableDef->StringSize() - 1;

	memcpy(bufferPtr, tableDefStr, tableDefSize);
	bufferPtr += tableDefSize;

	return reinterpret_cast<PCCHAR>(__db_table_buffer);
}

VOID DbTable::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	bufferPtr += SIZEOF(CSIZE);

	_Capacity = static_cast<DWORD>(*bufferPtr);
	bufferPtr += SIZEOF(DWORD);

	_RowCount = static_cast<SIZE>(*bufferPtr);
	bufferPtr += SIZEOF(SIZE);

	this->Dispose();

	_TableDef = new DbTableDef(bufferPtr);
}

VOID DbTable::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);

	bufferPtr = StringReadValue<DWORD>(_Capacity, bufferPtr);
	bufferPtr = StringReadValue<SIZE>(_RowCount, bufferPtr);

	this->Dispose();

	_TableDef = new DbTableDef(bufferPtr);
}

#ifdef ARDUINO

SIZE DbTable::printTo(Print & printer) const
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

	delete[] __db_table_buffer;
	__db_table_buffer = NULL;

	return size;
}

#endif


// [IDbTable] HELPER METHODS

CDBRESULT DbTable::SelectAllRows(PBYTE & resultRows, RSIZE resultCount)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::FindRow(CSIZE rowIndex, PBYTE resultRow, PSIZE resultSize)
{
	return DbResult::SUCCESS;
}

CDWORD DbTable::RowsBinarySize() const
{
	return this->RowCount() * this->RowBinarySize();
}

CDWORD DbTable::RowsStringSize() const
{
	return this->RowCount() * (this->RowStringSize() - 1);
}

CSTORAGERESULT DbTable::SaveRowAsBinary(RCISTORAGE storage, CSIZE rowIndex) const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::SaveRowAsString(RCISTORAGE storage, CSIZE rowIndex) const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::LoadRowFromBinary(RCISTORAGE storage, CSIZE rowIndex)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::LoadRowFromString(RCISTORAGE storage, CSIZE rowIndex)
{
	return StorageResult::SUCCESS;
}

CSIZE DbTable::RowBinarySize() const
{
	return _TableDef->RowSize();
}

CSIZE DbTable::RowStringSize() const
{
	return 2 * _TableDef->RowSize() + 1;
}

PCBYTE DbTable::RowToBinary(PCBYTE data) const
{
	return data;
}

PCCHAR DbTable::RowToString(PCBYTE data) const
{

	return reinterpret_cast<PCCHAR>(data);
}

PBYTE DbTable::RowFromBinary(PCBYTE data)
{
	return UNCONST(data);
}

PBYTE DbTable::RowFromString(PCCHAR data)
{
	return reinterpret_cast<PBYTE>(UNCONST(data));
}


// [IDbTableDef] IHELPER METHODS

CBYTE DbTable::TableNameLength() const
{
	return _TableDef->TableNameLength();
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_TABLES
