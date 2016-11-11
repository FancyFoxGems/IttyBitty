/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) && !defined(NO_ITTYBITTY_DB)
	#define NO_ITTYBITTY_DB
#endif

#ifndef NO_ITTYBITTY_DB


#include "IttyBitty_DB.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE DEFINITION

PBYTE IttyBitty::__database_buffer = NULL;

#pragma endregion


#pragma region [DataBase] IMPLEMENTATION
/*
// STATIC FUNCTIONS

STATIC PDATABASE Database::Load(RCISTORAGE storage, RDBRESULT result)
{
	database = new Database(storage);

	result = database.Load();

	return database;
}

STATIC PDATABASE Database::Create(RCISTORAGE storage, RDBRESULT result)
{
	database = new Database(storage);

	result = database.CreateDatabase();

	return database;
}

STATIC CDBRESULT Database::Delete(RCISTORAGE storage)
{
	PDATABASE database = new Database(storage);

	DBRESULT result = database.DeleteDatabase();

	delete database;

	return result;
}


// CONSTRUCTOR

Database::Database(RCISTORAGE storage) : _Storage(&storage)
{
}


// PROTECTED DISPOSAL METHOD

VOID Database::Dispose()
{
}


// OPERATORS

PCIDBTABLE Database::operator[](CBYTE) const
{
}

PIDBTABLE Database::operator[](CBYTE)
{
}


// ACCESSORS

RCISTORAGE Database::GetStorage() const
{
	return *_Storage;
}


// MUTATORS

VOID Database::SetStorage(RCISTORAGE storage)
{
	_Storage = &storage;
}


// USER METHODS

CDBRESULT Database::Create()
{
}

CDBRESULT Database::Delete()
{
}

CDBRESULT Database::Load()
{
}

CDBRESULT Database::Save()
{
}


// [IDbTableSet] IMPLEMENTATION

CDWORD Database::Size() const
{
}

CWORD Database::Capacity() const
{
}

CDBRESULT Database::Grow(RCFLOAT growthFactor)
{
}

CDBRESULT Database::Compress(RCFLOAT compressionFactor)
{
}

CDBRESULT Database::TruncateAllTables()
{
}

CDBRESULT Database::DropAllTables()
{
}

CBYTE Database::TableCount() const
{
	return this->TableDefCount();
}

RCIDBTABLE Database::Table(CBYTE tableIdx) const
{
}

RIDBTABLE Database::Table(CBYTE tableIdx)
{
}

RCIDBTABLE Database::Table(PCCHAR) const
{
}

RIDBTABLE Database::Table(PCCHAR tableName)
{
}

CDWORD Database::SizeOf(CBYTE tableIdx) const
{
}

CDWORD Database::SizeOf(PCCHAR tableName) const
{
}

CDWORD Database::CapacityOf(CBYTE tableIdx) const
{
}

CDWORD Database::CapacityOf(PCCHAR tableName) const
{
}

CSIZE Database::RowCountFor(CBYTE tableIdx) const
{
}

CSIZE Database::RowCountFor(PCCHAR tableName) const
{
}

CSIZE Database::RowsAvailableFor(CBYTE tableIdx) const
{
}

CSIZE Database::RowsAvailableFor(PCCHAR tableName) const
{
}

CDBRESULT Database::CreateTable(CSIZE, PCCHAR tableName, CBYTE createIdx)
{
}

CDBRESULT Database::GrowTable(CBYTE tableIdx, RCFLOAT growthFactor)
{
}

CDBRESULT Database::GrowTable(PCCHAR tableName, RCFLOAT growthFactor)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::CompressTable(CBYTE tableIdx, RCFLOAT compressionFactor)
{
}

CDBRESULT Database::CompressTable(PCCHAR tableName, RCFLOAT compressionFactor)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::DropTable(CBYTE tableIdx)
{
}

CDBRESULT Database::DropTable(PCCHAR tableName)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::SelectAllFrom(CBYTE tableIdx, PBYTE & recordSet, RSIZE recordCount)
{
}

CDBRESULT Database::SelectAllFrom(PCCHAR tableName, PBYTE & recordSet, RSIZE recordCount)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::FindFrom(CBYTE tableIdx, CSIZE rowIdx, PBYTE record, PSIZE recordSize)
{
}

CDBRESULT Database::FindFrom(PCCHAR, CSIZE rowIdx, PBYTE record, PSIZE recordSize)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::InsertInto(CBYTE tableIdx, PCBYTE rowData, CSIZE insertIdx)
{
}

CDBRESULT Database::InsertInto(PCCHAR tableName, PCBYTE rowData, CSIZE insertIdx)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}


CDBRESULT Database::UpdateTo(CBYTE tableIdx, CSIZE rowIdx, PCBYTE rowData)
{
}

CDBRESULT Database::UpdateTo(PCCHAR tableName, CSIZE rowIdx, PCBYTE rowData)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::DeleteFrom(CBYTE tableIdx, CSIZE rowIdx)
{
}

CDBRESULT Database::DeleteFrom(PCCHAR tableName, CSIZE rowIdx)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}

CDBRESULT Database::TruncateTable(CBYTE tableIdx)
{
}

CDBRESULT Database::TruncateTable(PCCHAR tableName)
{
	PIDBTABLE table = this->Table(tableName);

	return table->SelectAllRows(reinterpret_cast<PBYTE &>(recordSet), recordCount);
}


// [IStorable] IMPLEMENTATION

CSTORAGERESULT Database::SaveAsBinary() const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT Database::SaveAsString() const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT Database::LoadFromBinary()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT Database::LoadFromString()
{
	return StorageResult::SUCCESS;
}


// [ISerializable] IMPLEMENTATION

CSIZE Database::BinarySize() const
{
}

CSIZE Database::StringSize() const
{
}

PCBYTE Database::ToBinary() const
{
}

PCCHAR Database::ToString() const
{
}

VOID Database::FromBinary(PCBYTE data)
{
}

VOID Database::FromString(PCCHAR data)
{
}

#ifdef ARDUINO

SIZE Database::printTo(Print & printer) const
{
}

#endif


// [IDbTableSet] HELPER METHODS

CSTORAGERESULT Database::MoveTables(CSIZE startAddrOffset, RCLONG addrOffsetDelta)
{
}


// [IDbTableDefSet] IMPLEMENTATION

CBYTE Database::TableDefCount() const
{
}

RCIDBTABLEDEF Database::TableDef(CBYTE) const
{
}

RIDBTABLEDEF Database::TableDef(CBYTE)
{
}

RCIDBTABLEDEF Database::TableDef(PCCHAR) const
{
}

RIDBTABLEDEF Database::TableDef(PCCHAR)
{
}


// [IDbTableDefSet] HELPER METHODS

CSIZE Database::TableDefsByteSize() const
{
}

CSIZE Database::TableDefsStringSize() const
{
}
*/
#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DB
