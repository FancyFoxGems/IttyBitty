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
/*
// CONSTRUCTORS/DESTRUCTOR

DbTable::DbTable(CSIZE rowSize, PCCHAR tableName, CDWORD addrOffset)
{
}

DbTable::DbTable(PCBYTE)
{
}

DbTable::DbTable(PCCHAR)
{
}

DbTable::~DbTable()
{
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

CDBRESULT DbTable::Grow(CDWORD, CBOOL)
{
}

CDBRESULT DbTable::Shrink(CDWORD, CBOOL)
{
}

CDBRESULT DbTable::SelectAll(PBYTE &, RSIZE)
{
}

CDBRESULT DbTable::Find(CSIZE, PBYTE, PSIZE)
{
}

CDBRESULT DbTable::Insert(PCBYTE, CSIZE)
{
}

CDBRESULT DbTable::Update(PCBYTE, CSIZE, PSIZE)
{
}

CDBRESULT DbTable::Delete(CSIZE)
{
}

CDBRESULT DbTable::Truncate()
{
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

STORAGERESULT DbTable::SaveAsBinary(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTable::SaveAsString(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTable::LoadFromBinary(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}

STORAGERESULT DbTable::LoadFromString(RCISTORAGE storage)
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
		
#ifdef ARDUIN

SIZE DbTable::printTo(Print & printer) const
{
}

#endif
*/
#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_TABLES
