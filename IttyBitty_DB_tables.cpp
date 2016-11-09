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

DbTable::DbTable(CSIZE rowSize, PCCHAR tableName, CDWORD addrOffset)
{
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
	//if (_TableDefs == NULL)
	//	return;

	//if (_Dispose)
	//{
	//	for (BYTE i = 0; i < this->TableDefCount(); i++)
	//	{
	//		if (_TableDefs[i] != NULL)
	//		{
	//			delete _TableDefs[i];
	//			_TableDefs[i] = NULL;
	//		}
	//	}
	//}

	//delete[] _TableDefs;
	//_TableDefs = NULL;
}


// [IDbTable] IMPLEMENTATION
		
CDWORD DbTable::Size() const
{
}

CDWORD DbTable::Capacity() const
{
}

CSIZE DbTable::RowCount() const
{
}

CSIZE DbTable::RowsAvailable() const
{
}

CDBRESULT DbTable::Grow(RCFLOAT growthFactor, CBOOL)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Shrink(RCFLOAT shrinkFactor, CBOOL)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::SelectAll(PBYTE & resultRows, RSIZE resultCount)
{
	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Find(CSIZE rowIndex, PBYTE resultRow, PSIZE resultSize)
{
	return DbResult::SUCCESS;
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
}

DWORD DbTable::GetAddrOffset() const
{
}

PCCHAR DbTable::GetTableName() const
{
}
		
VOID DbTable::SetAddrOffset(CDWORD)
{
}

VOID DbTable::SetTableName(PCCHAR)
{
}
				

// [IStorable] IMPLEMENTATION

CSTORAGERESULT DbTable::SaveAsBinary(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::SaveAsString(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::LoadFromBinary(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTable::LoadFromString(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTable::BinarySize() const
{
}

CSIZE DbTable::StringSize() const
{
}

PCBYTE DbTable::ToBinary() const
{
}

PCCHAR DbTable::ToString() const
{
}

VOID DbTable::FromBinary(PCBYTE data)
{
}

VOID DbTable::FromString(PCCHAR data)
{
}
		
#ifdef ARDUINO

SIZE DbTable::printTo(Print & printer) const
{
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
	return _TableDef->RowSize();
}

CDWORD DbTable::RowsStringSize() const
{
	return 2 * _TableDef->RowSize() + 1;
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

CSTORAGERESULT DbTable::LoadFromString(RCISTORAGE storage, CSIZE rowIndex)
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

PCBYTE DbTable::RowToBinary(CSIZE rowIndex) const
{
}

PCCHAR DbTable::RowToString(CSIZE rowIndex) const
{
}

VOID DbTable::RowFromBinary(PCBYTE data, CSIZE rowIndex)
{
}

VOID DbTable::RowFromString(PCCHAR data, CSIZE rowIndex)
{
}


// [IDbTableDef] IHELPER METHODS

CBYTE DbTable::TableNameLength() const
{
	return _TableDef->TableNameLength();
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_TABLES
