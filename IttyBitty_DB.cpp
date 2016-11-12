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

// STATIC FUNCTIONS

PDATABASE Database::Load(RISTORAGE storage, RDBRESULT result)
{
	PDATABASE database = new Database(storage);

	result = database->Load();

	return database;
}

PDATABASE Database::Create(RISTORAGE storage, RDBRESULT result)
{
	PDATABASE database = new Database(storage);

	result = database->Create();

	return database;
}

CDBRESULT Database::Delete(RISTORAGE storage)
{
	return Database(storage).Delete();
}


// CONSTRUCTOR

Database::Database(RISTORAGE storage) : _Storage(&storage)
{
}


// PROTECTED DISPOSAL METHOD

VOID Database::Dispose()
{
	delete _DatabaseDef;
	_DatabaseDef = NULL;

	if (!_Tables)
		return;

	if (_Dispose)
	{
		CBYTE tableCount = this->TableCount();

		for (BYTE i = 0; i < tableCount; i++)
		{
			if (_Tables[i])
			{
				delete _Tables[i];
				_Tables[i] = NULL;
			}
		}
	}

	delete[] _Tables;
	_Tables = NULL;
}


// OPERATORS

PCIDBTABLE Database::operator[](CBYTE tableIdx) const
{
	if (!_Tables)
		return NULL;

	return _Tables[tableIdx];
}

PIDBTABLE Database::operator[](CBYTE tableIdx)
{
	if (!_Tables)
		return NULL;

	return _Tables[tableIdx];
}

PCIDBTABLE Database::operator[](PCCHAR tableName) const
{
	PCIDBTABLE tablePtr = NULL;

	for (BYTE i = 0; i < this->TableDefCount(); i++)
	{
		tablePtr = this->operator[](i);

		if (strcmp(tablePtr->GetTableName(), tableName))
			break;
	}

	return tablePtr;
}

PIDBTABLE Database::operator[](PCCHAR tableName)
{
	PIDBTABLE tablePtr = NULL;

	for (BYTE i = 0; i < this->TableDefCount(); i++)
	{
		tablePtr = this->operator[](i);

		if (strcmp(tablePtr->GetTableName(), tableName))
			break;
	}

	return tablePtr;
}


// ACCESSORS

RISTORAGE Database::GetStorage() const
{
	return *_Storage;
}


// MUTATORS

VOID Database::SetStorage(RISTORAGE storage)
{
	_Storage = &storage;
}


// USER METHODS

CDBRESULT Database::Create()
{
	return DbResult::SUCCESS;
}

CDBRESULT Database::Delete()
{
	return DbResult::SUCCESS;
}

CDBRESULT Database::Load()
{
#ifdef _DEBUG
	return (CDBRESULT)this->LoadFromString();
#else
	return (CDBRESULT)this->LoadFromBinary();
#endif
}

CDBRESULT Database::Save()
{
#ifdef _DEBUG
	return (CDBRESULT)this->SaveAsString();
#else
	return (CDBRESULT)this->SaveAsBinary();
#endif
}


// [IDbTableSet] IMPLEMENTATION

CDWORD Database::Size() const
{
	return 0;
}

CWORD Database::Capacity() const
{
	return 0;
}

CDBRESULT Database::TruncateAllTables()
{
	return DbResult::SUCCESS;
}

CDBRESULT Database::DropAllTables()
{
	return DbResult::SUCCESS;
}

CBYTE Database::TableCount() const
{
	return this->TableDefCount();
}

RCIDBTABLE Database::Table(CBYTE tableIdx) const
{
	PCIDBTABLE tablePtr = this->operator[](tableIdx);

	if (!tablePtr)
		return DbTable::NULL_OBJECT();

	return *tablePtr;
}

RIDBTABLE Database::Table(CBYTE tableIdx)
{
	PIDBTABLE tablePtr = this->operator[](tableIdx);

	if (!tablePtr)
		return DbTable::NULL_OBJECT();

	return *tablePtr;
}

RCIDBTABLE Database::Table(PCCHAR tableName) const
{
	PCIDBTABLE tablePtr = this->operator[](tableName);

	if (!tablePtr)
		return DbTable::NULL_OBJECT();

	return *tablePtr;
}

RIDBTABLE Database::Table(PCCHAR tableName)
{
	PIDBTABLE tablePtr = this->operator[](tableName);

	if (!tablePtr)
		return DbTable::NULL_OBJECT();

	return *tablePtr;
}

CDWORD Database::SizeOf(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	return table->Size();
}

CDWORD Database::SizeOf(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	return table->Size();
}

CDWORD Database::CapacityOf(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	return table->Capacity();
}

CDWORD Database::CapacityOf(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	return table->Capacity();
}

CSIZE Database::RowCountFor(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	return table->RowCount();
}

CSIZE Database::RowCountFor(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	return table->RowCount();
}

CSIZE Database::RowsAvailableFor(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	return table->RowsAvailable();
}

CSIZE Database::RowsAvailableFor(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	return table->RowsAvailable();
}

CDBRESULT Database::CreateTable(CSIZE, PCCHAR tableName, CBYTE newTableIdx)
{
	return DbResult::SUCCESS;
}

CDBRESULT Database::DropTable(CBYTE tableIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return DbResult::SUCCESS;
}

CDBRESULT Database::DropTable(PCCHAR tableName)
{
	PIDBTABLE table = this->operator[](tableName);

	return DbResult::SUCCESS;
}

CDBRESULT Database::GrowTable(CBYTE tableIdx, RCFLOAT growthFactor)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Grow(*this, growthFactor);
}

CDBRESULT Database::GrowTable(PCCHAR tableName, RCFLOAT growthFactor)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Grow(*this, growthFactor);
}

CDBRESULT Database::CompressTable(CBYTE tableIdx, RCFLOAT compressionFactor)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Compress(*this, compressionFactor);
}

CDBRESULT Database::CompressTable(PCCHAR tableName, RCFLOAT compressionFactor)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Compress(*this, compressionFactor);
}

CDBRESULT Database::SelectAllFrom(CBYTE tableIdx, PBYTE & recordSet, RSIZE recordCount)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->SelectAll(recordSet, recordCount);
}

CDBRESULT Database::SelectAllFrom(PCCHAR tableName, PBYTE & recordSet, RSIZE recordCount)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->SelectAll(recordSet, recordCount);
}

CDBRESULT Database::FindFrom(CBYTE tableIdx, CSIZE rowIdx, PBYTE record, PSIZE recordSize)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Find(rowIdx, record, recordSize);
}

CDBRESULT Database::FindFrom(PCCHAR tableName, CSIZE rowIdx, PBYTE record, PSIZE recordSize)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Find(rowIdx, record, recordSize);
}

CDBRESULT Database::InsertInto(CBYTE tableIdx, PCBYTE rowData, CSIZE insertIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Insert(rowData, insertIdx);
}

CDBRESULT Database::InsertInto(PCCHAR tableName, PCBYTE rowData, CSIZE insertIdx)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Insert(rowData, insertIdx);
}


CDBRESULT Database::UpdateTo(CBYTE tableIdx, CSIZE rowIdx, PCBYTE rowData)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Update(rowIdx, rowData);
}

CDBRESULT Database::UpdateTo(PCCHAR tableName, CSIZE rowIdx, PCBYTE rowData)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Update(rowIdx, rowData);
}

CDBRESULT Database::DeleteFrom(CBYTE tableIdx, CSIZE rowIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Delete(rowIdx);
}

CDBRESULT Database::DeleteFrom(PCCHAR tableName, CSIZE rowIdx)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Delete(rowIdx);
}

CDBRESULT Database::TruncateTable(CBYTE tableIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	return table->Truncate();
}

CDBRESULT Database::TruncateTable(PCCHAR tableName)
{
	PIDBTABLE table = this->operator[](tableName);

	return table->Truncate();
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
	return _DatabaseDef->BinarySize();
}

CSIZE Database::StringSize() const
{
	return 0;
}

PCBYTE Database::ToBinary() const
{
	return NULL;
}

PCCHAR Database::ToString() const
{
	return NULL;
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
#ifdef _DEBUG
	SIZE size = this->StringSize();
	PCCHAR buffer = this->ToString();
#else
	SIZE size = this->BinarySize();
	PCBYTE buffer = this->ToBinary();
#endif

	for (SIZE i = 0; i < size; i++)
		printer.print(buffer[i]);

	this->FreeBuffer();

	return size;
}

#endif


// [IDbTableSet] HELPER METHODS

CDBRESULT Database::MoveTables(CSIZE startAddrOffset, RCLONG addrOffsetDelta)
{
	return DbResult::SUCCESS;
}

CSIZE Database::TablesBinarySize() const
{
	return 0;
}

CSIZE Database::TablesStringSize() const
{
	return 0;
}


// [IDbTableDefSet] IMPLEMENTATION

CBYTE Database::TableDefCount() const
{
	return _DatabaseDef->TableDefCount();
}

RCIDBTABLEDEF Database::TableDef(CBYTE tableDefIdx) const
{
	return _DatabaseDef->TableDef(tableDefIdx);
}

RIDBTABLEDEF Database::TableDef(CBYTE tableDefIdx)
{
	return _DatabaseDef->TableDef(tableDefIdx);
}

RCIDBTABLEDEF Database::TableDef(PCCHAR tableName) const
{
	return _DatabaseDef->TableDef(tableName);
}

RIDBTABLEDEF Database::TableDef(PCCHAR tableName)
{
	return _DatabaseDef->TableDef(tableName);
}


// [IDbTableDefSet] HELPER METHODS

CSIZE Database::TableDefsBinarySize() const
{
	return _DatabaseDef->TableDefsBinarySize();
}

CSIZE Database::TableDefsStringSize() const
{
	return _DatabaseDef->TableDefsStringSize();
}


// [ISerializable] HELPER METHODS

VOID Database::FreeBuffer() const
{
	if (!__database_buffer)
		return;

	delete[] __database_buffer;
	__database_buffer = NULL;
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DB
