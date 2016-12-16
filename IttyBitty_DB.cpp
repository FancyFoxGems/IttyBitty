/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_STORAGE) || \
		defined(NO_ITTYBITTY_TABLE_DEFS) || defined(NO_ITTYBITTY_TABLES)
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

	result = (CDBRESULT)database->Load();

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


// CONSTRUCTORS/DESTRUCTOR

Database::Database(RISTORAGE storage) : _Storage(storage) { }

Database::Database(PCBYTE data, RISTORAGE storage) : Database(storage)
{
	this->FromBinary(data);
}

Database::Database(PCCHAR data, RISTORAGE storage) : Database(storage)
{
	this->FromString(data);
}

Database::~Database()
{
	this->Dispose();
}


// PROTECTED DISPOSAL METHOD

VOID Database::Dispose(CBOOL forceDispose)
{
	if (!_Tables)
		return;

	if (_Dispose OR forceDispose)
	{
		for (BYTE i = 0; i < _TableCount; i++)
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

	for (BYTE i = 0; i < _TableCount; i++)
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

	for (BYTE i = 0; i < _TableCount; i++)
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
	return _Storage;
}


// MUTATORS

VOID Database::SetStorage(RISTORAGE storage)
{
	_Storage = storage;
}


// USER METHODS

CDBRESULT Database::Create()
{
	if (_TableCount > 0)
		return DbResult::ERROR_OPERATION_ALREADY_CREATED;

	return (CDBRESULT)this->Save();
}

CDBRESULT Database::Delete()
{
	return (CDBRESULT)_Storage.Erase();
}


// [IDbTableSet] IMPLEMENTATION

CDWORD Database::Size() const
{
	return this->TablesSize();
}

CWORD Database::Capacity() const
{
	return this->TablesCapacity();
}

CDBRESULT Database::TruncateAllTables()
{
	DBRESULT result = DbResult::SUCCESS;

	for (BYTE i = 0; i < _TableCount; i ++)
	{
		result = _Tables[i]->Truncate();
		if ((BYTE)result)
			return result;
	}

	return (CDBRESULT)this->Save();
}

CDBRESULT Database::DropAllTables()
{
	DBRESULT result = this->TruncateAllTables();
	if ((BYTE)result)
		return result;

	this->Dispose(TRUE);

	return (CDBRESULT)this->Save();
}

CBYTE Database::TableCount() const
{
	return _TableCount;
}

RCIDBTABLE Database::Table(CBYTE tableIdx) const
{
	PCIDBTABLE tablePtr = _Tables[tableIdx];

	if (!tablePtr)
		return DbTable::NULL_OBJECT();

	return *tablePtr;
}

RIDBTABLE Database::Table(CBYTE tableIdx)
{
	PIDBTABLE tablePtr = _Tables[tableIdx];

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

	if (!table)
		return 0;

	return table->Size();
}

CDWORD Database::SizeOf(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	if (!table)
		return 0;

	return table->Size();
}

CDWORD Database::CapacityOf(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return 0;

	return table->Capacity();
}

CDWORD Database::CapacityOf(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	if (!table)
		return 0;

	return table->Capacity();
}

CSIZE Database::RowCountFor(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return 0;

	return table->RowCount();
}

CSIZE Database::RowCountFor(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	if (!table)
		return 0;

	return table->RowCount();
}

CSIZE Database::RowsAvailableFor(CBYTE tableIdx) const
{
	PCIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return 0;

	return table->RowsAvailable();
}

CSIZE Database::RowsAvailableFor(PCCHAR tableName) const
{
	PCIDBTABLE table = this->operator[](tableName);

	if (!table)
		return 0;

	return table->RowsAvailable();
}

CDBRESULT Database::CreateTable(CSIZE rowSize, PCCHAR tableName, CSIZE dataAllocationRows, CBYTE newTableIdx)
{
	PIDBTABLE table = NULL;
	WORD nextTableHeaderAddr = 0;
	DWORD nextTableDataAddr = 0;

	if (_TableCount > 0)
	{
		table = _Tables[_TableCount - 1];

		nextTableHeaderAddr = table->GetAddrOffset() + 1;
		nextTableDataAddr = table->GetDataAddrOffset() + 1;
	}

	table = new DbTable(_Storage, rowSize, tableName, nextTableHeaderAddr, nextTableDataAddr, dataAllocationRows * rowSize);

	DBRESULT result = table->Create(*this);
	if ((BYTE)result)
		return result;

	PPIDBTABLE newTables = new PIDBTABLE[++_TableCount];

	for (BYTE i = 0; i < _TableCount - 1; i++)
		newTables[i] = _Tables[i];

	this->Dispose();

	_Tables = newTables;

	return (CDBRESULT)this->Save();
}

CDBRESULT Database::DropTable(CBYTE tableIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	table->Drop(*this);

	PPIDBTABLE newTables = new PIDBTABLE[--_TableCount];
	BYTE currIdx = 0;

	for (BYTE i = 0; i < _TableCount; i++)
	{
		if (currIdx != tableIdx)
			newTables[currIdx++] = _Tables[i];
	}

	this->Dispose();

	_Tables = newTables;

	return (CDBRESULT)this->Save();
}

CDBRESULT Database::DropTable(PCCHAR tableName)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	table->Drop(*this);

	return (CDBRESULT)this->Save();
}

CDBRESULT Database::GrowTable(CBYTE tableIdx, RCFLOAT growthFactor)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Grow(*this, growthFactor);
}

CDBRESULT Database::GrowTable(PCCHAR tableName, RCFLOAT growthFactor)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Grow(*this, growthFactor);
}

CDBRESULT Database::CompressTable(CBYTE tableIdx, RCFLOAT compressionFactor)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Compress(*this, compressionFactor);
}

CDBRESULT Database::CompressTable(PCCHAR tableName, RCFLOAT compressionFactor)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Compress(*this, compressionFactor);
}

CDBRESULT Database::SelectAllFrom(CBYTE tableIdx, PBYTE & recordSet, RSIZE recordCount, PSIZE rowSize)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->SelectAll(recordSet, recordCount, rowSize);
}

CDBRESULT Database::SelectAllFrom(PCCHAR tableName, PBYTE & recordSet, RSIZE recordCount, PSIZE rowSize)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->SelectAll(recordSet, recordCount, rowSize);
}

CDBRESULT Database::FindFrom(CBYTE tableIdx, CSIZE rowIdx, PBYTE & record, PSIZE rowSize)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Find(rowIdx, record, rowSize);
}

CDBRESULT Database::FindFrom(PCCHAR tableName, CSIZE rowIdx, PBYTE & record, PSIZE rowSize)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Find(rowIdx, record, rowSize);
}

CDBRESULT Database::InsertInto(CBYTE tableIdx, PCBYTE rowData, CSIZE insertIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Insert(*this, rowData, insertIdx);
}

CDBRESULT Database::InsertInto(PCCHAR tableName, PCBYTE rowData, CSIZE insertIdx)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Insert(*this, rowData, insertIdx);
}


CDBRESULT Database::UpdateTo(CBYTE tableIdx, PCBYTE rowData, CSIZE rowIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Update(rowData, rowIdx);
}

CDBRESULT Database::UpdateTo(PCCHAR tableName, PCBYTE rowData, CSIZE rowIdx)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Update(rowData, rowIdx);
}

CDBRESULT Database::DeleteFrom(CBYTE tableIdx, CSIZE rowIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Delete(rowIdx);
}

CDBRESULT Database::DeleteFrom(PCCHAR tableName, CSIZE rowIdx)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Delete(rowIdx);
}

CDBRESULT Database::TruncateTable(CBYTE tableIdx)
{
	PIDBTABLE table = this->operator[](tableIdx);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Truncate();
}

CDBRESULT Database::TruncateTable(PCCHAR tableName)
{
	PIDBTABLE table = this->operator[](tableName);

	if (!table)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return table->Truncate();
}


// [IStorable] IMPLEMENTATION

CSTORAGERESULT Database::Save()
{
#ifdef _DEBUG
	return this->SaveAsString();
#else
	return this->SaveAsBinary();
#endif
}

CSTORAGERESULT Database::Load()
{
#ifdef _DEBUG
	return this->LoadFromString();
#else
	return this->LoadFromBinary();
#endif
}

CSTORAGERESULT Database::SaveAsBinary() const
{
	return this->GetStorage().Save(this->ToBinary(), this->BinarySize());
}

CSTORAGERESULT Database::SaveAsString() const
{
	return this->GetStorage().Save(reinterpret_cast<PCBYTE>(this->ToString()), this->StringSize());
}

CSTORAGERESULT Database::LoadFromBinary()
{
	SIZE size = this->BinarySize();
	PBYTE buffer = new byte[size];

	STORAGERESULT result = this->GetStorage().Load(buffer, size);
	if ((BYTE)result)
		return result;

	this->FromBinary(buffer);

	return result;
}

CSTORAGERESULT Database::LoadFromString()
{
	SIZE size = this->StringSize();
	PBYTE buffer = new byte[size];

	STORAGERESULT result = this->GetStorage().Load(buffer, size);
	if ((BYTE)result)
		return result;

	this->FromString(reinterpret_cast<PCCHAR>(buffer));

	return result;
}


// [ISerializable] IMPLEMENTATION

CSIZE Database::BinarySize() const
{
	return SIZEOF(CSIZE) + SIZEOF(CBYTE) + this->BinarySize() + 1;
}

CSIZE Database::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(CBYTE) + this->TablesStringSize() + 1;
}

PCBYTE Database::ToBinary() const
{
	CSIZE size = this->BinarySize();

	this->FreeBuffer();

	__database_buffer = new byte[size];

	PBYTE bufferPtr = __database_buffer;

	memcpy(bufferPtr, &size, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	memcpy(bufferPtr, &_TableCount, SIZEOF(CBYTE));
	bufferPtr += SIZEOF(CBYTE);

	PIDBTABLE table = NULL;
	PCBYTE tableBytes = NULL;
	SIZE tableSize = 0;

	for (SIZE i = 0; i < _TableCount; i++)
	{
		table = _Tables[i];
		tableBytes = table->ToBinary();
		tableSize = table->BinarySize();

		memcpy(bufferPtr, tableBytes, tableSize);

		table->FreeBuffer();

		bufferPtr += tableSize;
	}

	return __database_buffer;
}

PCCHAR Database::ToString() const
{
	CSIZE size = this->StringSize();

	this->FreeBuffer();

	__database_buffer = new byte[size];
	__database_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__database_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(_TableCount, bufferPtr);

	PIDBTABLE table = NULL;
	PCCHAR tableStr = NULL;
	SIZE tableSize = 0;

	for (SIZE i = 0; i < _TableCount; i++)
	{
		table = _Tables[i];
		tableStr = table->ToString();
		tableSize = table->StringSize() - 1;

		memcpy(bufferPtr, tableStr, tableSize);

		table->FreeBuffer();

		bufferPtr += tableSize;
	}

	return reinterpret_cast<PCCHAR>(__database_buffer);
}

VOID Database::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_TableCount = *bufferPtr++;

	this->Dispose();

	if (_TableCount > 0)
		_Tables = new PIDBTABLE[_TableCount];

	_Dispose = TRUE;

	for (SIZE i = 0; i < _TableCount; i++)
	{
		_Tables[i] = new DbTable(bufferPtr, this->GetStorage());

		bufferPtr += _Tables[i]->BinarySize();
	}
}

VOID Database::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<BYTE>(_TableCount, bufferPtr);

	this->Dispose();

	if (_TableCount > 0)
		_Tables = new PIDBTABLE[_TableCount];

	_Dispose = TRUE;

	for (BYTE i = 0; i < _TableCount; i++)
	{
		_Tables[i] = new DbTable(bufferPtr, this->GetStorage());

		bufferPtr += _Tables[i]->StringSize() - 1;
	}
}

VOID Database::FreeBuffer() const
{
	if (!__database_buffer)
		return;

	delete[] __database_buffer;
	__database_buffer = NULL;
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

CDBRESULT Database::MoveTableData(RCDWORD startDataAddrOffset, RCLONG dataAddrOffsetDelta, CBOOL eraseNewOrExcessAllocation)
{
	PIDBTABLE table = NULL;
	DBRESULT result = DbResult::SUCCESS;

	for (BYTE i = 0; i < _TableCount; i++)
	{
		if (dataAddrOffsetDelta < 0)
			table = _Tables[i];
		else
			table = _Tables[_TableCount - i - 1];

		if (table->GetDataAddrOffset() <= startDataAddrOffset)
			return (CDBRESULT)result;

		result = (CDBRESULT)table->MoveData(dataAddrOffsetDelta, 0,
			dataAddrOffsetDelta > 0 ? DB_ERASE_NEW_ALLOCATION : DB_ERASE_EXCESS_ALLOCATION);
		if ((BYTE)result)
			return result;
	}

	return (CDBRESULT)result;
}

CDBRESULT Database::MoveTableDefinition(CWORD startAddrOffset, CSHORT addrOffsetDelta, CBOOL eraseNewOrExcessAllocation)
{
	PIDBTABLE table = NULL;
	DBRESULT result = DbResult::SUCCESS;

	for (BYTE i = 0; i < _TableCount; i++)
	{
		if (addrOffsetDelta < 0)
			table = _Tables[i];
		else
			table = _Tables[_TableCount - i - 1];

		if (table->GetAddrOffset() <= startAddrOffset)
			return (CDBRESULT)result;

		result = (CDBRESULT)table->MoveDefinition(addrOffsetDelta,
			addrOffsetDelta > 0 ? DB_ERASE_NEW_ALLOCATION : DB_ERASE_EXCESS_ALLOCATION);
		if ((BYTE)result)
			return result;
	}

	return (CDBRESULT)result;
}

CDWORD Database::TablesCapacity() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _TableCount; i++)
		size += _Tables[i]->Capacity();

	return size;
}

CDWORD Database::TablesSize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _TableCount; i++)
		size += _Tables[i]->Size() - 1;

	return size;
}

CSIZE Database::TablesBinarySize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _TableCount; i++)
		size += _Tables[i]->BinarySize();

	return size;
}

CSIZE Database::TablesStringSize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _TableCount; i++)
		size += _Tables[i]->StringSize() - 1;

	return size;
}


// [IDbTableDefSet] IMPLEMENTATION

CBYTE Database::TableDefCount() const
{
	return _TableCount;
}

RCIDBTABLEDEF Database::TableDef(CBYTE tableDefIdx) const
{
	return this->Table(tableDefIdx).TableDef();
}

RIDBTABLEDEF Database::TableDef(CBYTE tableDefIdx)
{
	return this->Table(tableDefIdx).TableDef();
}

RCIDBTABLEDEF Database::TableDef(PCCHAR tableName) const
{
	return this->Table(tableName).TableDef();
}

RIDBTABLEDEF Database::TableDef(PCCHAR tableName)
{
	return this->Table(tableName).TableDef();
}


// [IDbTableDefSet] HELPER METHODS

CSIZE Database::TableDefsBinarySize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _TableCount; i++)
		size += _Tables[i]->TableDef().BinarySize();

	return size;
}

CSIZE Database::TableDefsStringSize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _TableCount; i++)
		size += _Tables[i]->TableDef().StringSize() - 1;

	return size;
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DB
