/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_STORAGE) || \
		defined(NO_ITTYBITTY_DB) || defined(NO_ITTYBITTY_TABLE_DEFS)
	#define NO_ITTYBITTY_DB_TABLES
#endif

#ifndef NO_ITTYBITTY_DB_TABLES


#include "IttyBitty_DB_tables.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE DEFINITION

PBYTE IttyBitty::__db_table_buffer = NULL;

#pragma endregion


#pragma region [DbTable] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

DbTable::DbTable(RISTORAGE storage, CSIZE rowSize, PCCHAR tableName, CWORD addrOffset, RCDWORD dataAddrOffset, RCDWORD capacity)
	: _Capacity(capacity), _DataAddrOffset(dataAddrOffset)
{
	_TableDef = new DbTableDef(storage, rowSize, tableName, addrOffset);
}

DbTable::DbTable(PCBYTE data, RISTORAGE storage) : DbTable(storage)
{
	this->FromBinary(data);
}

DbTable::DbTable(PCCHAR data, RISTORAGE storage) : DbTable(storage)
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
	if (_TableDef)
	{
		delete _TableDef;
		_TableDef = NULL;
	}
}


// ACCESSORS

RISTORAGE DbTable::GetStorage() const
{
	return _TableDef->GetStorage();
}

RCIDBTABLEDEF DbTable::TableDef() const
{
	if (!_TableDef)
		return DbTableDef::NULL_OBJECT();

	return *_TableDef;
}

RIDBTABLEDEF DbTable::TableDef()
{
	if (!_TableDef)
		return DbTableDef::NULL_OBJECT();

	return *_TableDef;
}

DWORD DbTable::GetDataAddrOffset() const
{
	return _DataAddrOffset;
}


// MUTATORS

VOID DbTable::SetStorage(RISTORAGE storage)
{
	return _TableDef->SetStorage(storage);
}

VOID DbTable::SetDataAddrOffset(RCDWORD dataAddrOffset)
{
	_DataAddrOffset = dataAddrOffset;
}


// [IDbTable] IMPLEMENTATION

CDWORD DbTable::Size() const
{
#ifdef _DEBUG
	return this->RowsStringSize();
#else
	return this->RowsBinarySize();
#endif
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
#ifdef _DEBUG
	CSIZE rowSize = this->RowStringSize();
#else
	CSIZE rowSize = this->RowBinarySize();
#endif

	return (CSIZE)((this->Capacity() - this->Size()) / (CDWORD)rowSize);
}

CDBRESULT DbTable::SelectAll(PBYTE & recordSet, RSIZE recordCount, PSIZE rowSize)
{
	return (CDBRESULT)this->LoadAllRows(recordSet, recordCount, rowSize);
}

CDBRESULT DbTable::Find(CSIZE rowIdx, PBYTE & resultRow, PSIZE rowSize)
{
	return (CDBRESULT)this->LoadRow(rowIdx, resultRow, rowSize);
}

CDBRESULT DbTable::Insert(PCBYTE rowData, CSIZE rowIdx)
{
	return this->InsertRow(NULL, rowData, rowIdx);
}

CDBRESULT DbTable::Insert(RIDBTABLESET tableSet, PCBYTE rowData, CSIZE rowIdx)
{
	return this->InsertRow(&tableSet, rowData, rowIdx);
}

CDBRESULT DbTable::Update(PCBYTE rowData, CSIZE rowIdx)
{
	if (rowIdx > this->RowCount() - 1)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	return (CDBRESULT)this->SaveRow(rowData, rowIdx);
}

CDBRESULT DbTable::Delete(CSIZE rowIdx)
{
	if (rowIdx > this->RowCount() - 1)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

#ifdef _DEBUG
	CSIZE rowSize = this->RowStringSize();
#else
	CSIZE rowSize = this->RowBinarySize();
#endif

	STORAGERESULT result = StorageResult::SUCCESS;

	if (rowIdx < _RowCount - 1)
	{
		result = this->MoveData(-1 * (LONG)rowSize, rowIdx * rowSize);
		if ((BYTE)result)
			return (CDBRESULT)result;
	}

	if (DB_ERASE_EXCESS_ALLOCATION)
	{
		result = this->EraseData(rowSize, rowIdx * rowSize);
		if ((BYTE)result)
			return (CDBRESULT)result;
	}

	--_RowCount;

	return (CDBRESULT)this->Save();
}

CDBRESULT DbTable::Truncate()
{
	if (this->RowCount() == 0)
		return DbResult::SUCCESS;

	if (DB_ERASE_EXCESS_ALLOCATION)
	{
		STORAGERESULT result = this->EraseData(this->Size(), 0);
		if ((BYTE)result)
			return (CDBRESULT)result;
	}

	_RowCount = 0;

	return (CDBRESULT)this->Save();
}


// [IDbTableDef] IMPLEMENTATION

CSIZE DbTable::RowSize() const
{
	return _TableDef->RowSize();
}

CWORD DbTable::GetAddrOffset() const
{
	return _TableDef->GetAddrOffset();
}

PCCHAR DbTable::GetTableName() const
{
	return _TableDef->GetTableName();
}

VOID DbTable::SetAddrOffset(CWORD addrOffset)
{
	_TableDef->SetAddrOffset(addrOffset);
}

VOID DbTable::SetTableName(PCCHAR tableName)
{
	_TableDef->SetTableName(tableName);
}


// [IStorable] IMPLEMENTATION

CSTORAGERESULT DbTable::Save()
{
#ifdef _DEBUG
	return this->SaveAsString();
#else
	return this->SaveAsBinary();
#endif
}

CSTORAGERESULT DbTable::Load()
{
#ifdef _DEBUG
	return this->LoadFromString();
#else
	return this->LoadFromBinary();
#endif
}

CSTORAGERESULT DbTable::SaveAsBinary() const
{
	return this->GetStorage().Save(this->ToBinary(),
		this->BinarySize(), this->GetAddrOffset() + _TableDef->BinarySize());
}

CSTORAGERESULT DbTable::SaveAsString() const
{
	return this->GetStorage().Save(reinterpret_cast<PCBYTE>(this->ToString()),
		this->StringSize(), this->GetAddrOffset() + _TableDef->StringSize());
}

CSTORAGERESULT DbTable::LoadFromBinary()
{
	SIZE size = this->BinarySize();
	PBYTE buffer = new byte[size];

	STORAGERESULT result = this->GetStorage().Load(buffer, size,
		this->GetAddrOffset() + _TableDef->BinarySize());
	if ((BYTE)result)
		return result;

	this->FromBinary(buffer);

	return result;
}

CSTORAGERESULT DbTable::LoadFromString()
{
	SIZE size = this->StringSize();
	PBYTE buffer = new byte[size];

	STORAGERESULT result = this->GetStorage().Load(buffer, size,
		this->GetAddrOffset() + _TableDef->StringSize());
	if ((BYTE)result)
		return result;

	this->FromString(reinterpret_cast<PCCHAR>(buffer));

	return result;
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTable::BinarySize() const
{
	return SIZEOF(CSIZE) +  2 * SIZEOF(CDWORD) + _TableDef->BinarySize();
}

CSIZE DbTable::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 4 * SIZEOF(CDWORD) + _TableDef->StringSize();
}

PCBYTE DbTable::ToBinary() const
{
	CSIZE size = this->BinarySize();

	this->FreeBuffer();

	__db_table_buffer = new byte[size];

	PBYTE bufferPtr = __db_table_buffer;

	memcpy(bufferPtr, &size, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	CDWORD capacity = this->Capacity();
	memcpy(bufferPtr, &capacity, SIZEOF(CDWORD));
	bufferPtr += SIZEOF(CDWORD);

	CSIZE recordCount = this->RowCount();
	memcpy(bufferPtr, &recordCount, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	CDWORD dataAddrOffset = this->GetDataAddrOffset();
	memcpy(bufferPtr, &dataAddrOffset, SIZEOF(CDWORD));
	bufferPtr += SIZEOF(CDWORD);

	PCBYTE tableDefBytes = _TableDef->ToBinary();
	SIZE tableDefSize = _TableDef->BinarySize();

	memcpy(bufferPtr, tableDefBytes, tableDefSize);
	bufferPtr += tableDefSize;

	return __db_table_buffer;
}

PCCHAR DbTable::ToString() const
{
	CSIZE size = this->StringSize();

	this->FreeBuffer();

	__db_table_buffer = new byte[size];
	__db_table_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__db_table_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CDWORD>(this->Capacity(), bufferPtr);
	bufferPtr = StringInsertValue<CSIZE>(this->RowCount(), bufferPtr);
	bufferPtr = StringInsertValue<CDWORD>(this->GetDataAddrOffset(), bufferPtr);

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

	_DataAddrOffset = static_cast<DWORD>(*bufferPtr);
	bufferPtr += SIZEOF(DWORD);

	this->Dispose();

	_TableDef = new DbTableDef(bufferPtr, this->GetStorage());
}

VOID DbTable::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr += 2 * SIZEOF(CSIZE);

	bufferPtr = StringReadValue<DWORD>(_Capacity, bufferPtr);
	bufferPtr = StringReadValue<SIZE>(_RowCount, bufferPtr);
	bufferPtr = StringReadValue<DWORD>(_DataAddrOffset, bufferPtr);

	this->Dispose();

	_TableDef = new DbTableDef(bufferPtr, this->GetStorage());
}

VOID DbTable::FreeBuffer() const
{
	if (!__db_table_buffer)
		return;

	delete[] __db_table_buffer;
	__db_table_buffer = NULL;
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

	this->FreeBuffer();

	return size;
}

#endif


// HELPER METHODS

CDBRESULT DbTable::InsertRow(PIDBTABLESET tableSet, PCBYTE rowData, CSIZE rowIdx)
{
	DBRESULT result = DbResult::SUCCESS;

	if (this->RowsAvailable() == 0)
	{
		if (tableSet)
		{
			result = this->Grow(*tableSet);
			if ((BYTE)result)
				return (CDBRESULT)result;
		}
		else
		{
			return DbResult::ERROR_OPERATION_TABLE_FULL;
		}
	}

#ifdef _DEBUG
	CSIZE rowSize = this->RowStringSize();
#else
	CSIZE rowSize = this->RowBinarySize();
#endif

	if (rowIdx < MAX_VALUE(SIZE))
	{
		result = (CDBRESULT)this->MoveData(rowSize, rowIdx * rowSize);
		if ((BYTE)result)
			return result;
	}

	result = (CDBRESULT)this->SaveRow(rowData, rowIdx);
	if ((BYTE)result)
		return result;

	++_RowCount;

	return (CDBRESULT)this->Save();
}


// [IDbTable] HELPER METHODS

CDBRESULT DbTable::Create(RIDBTABLESET tableSet)
{
#ifdef _DEBUG
	RCLONG tableDefSize = _TableDef->StringSize();
#else
	RCLONG tableDefSize = _TableDef->StringSize();
#endif

	DBRESULT result = tableSet.MoveTableData(_DataAddrOffset, _Capacity, DB_ERASE_NEW_ALLOCATION);
	if ((BYTE)result)
		return result;

	result = tableSet.MoveTableDefinition(this->GetDataAddrOffset(), tableDefSize, DB_ERASE_EXCESS_ALLOCATION);

	return (CDBRESULT)this->Save();
}

CDBRESULT DbTable::Drop(RIDBTABLESET tableSet)
{
#ifdef _DEBUG
	RCLONG tableDefSize = _TableDef->StringSize();
#else
	RCLONG tableDefSize = _TableDef->BinarySize();
#endif

	DBRESULT result = tableSet.MoveTableData(_DataAddrOffset + 1, -1 * _Capacity, DB_ERASE_EXCESS_ALLOCATION);
	if ((BYTE)result)
		return result;

	result = tableSet.MoveTableDefinition(this->GetDataAddrOffset() + 1, tableDefSize, DB_ERASE_EXCESS_ALLOCATION);

	return result;
}

CDBRESULT DbTable::Grow(RIDBTABLESET tableSet, RCFLOAT growthFactor)
{
	if (growthFactor == 1.0F)
		return DbResult::SUCCESS;

	if (growthFactor < 1.0F)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	 DWORD newCapacity = _Capacity * growthFactor;

#ifdef _DEBUG
	SIZE rowSize = this->RowStringSize();
#else
	SIZE rowSize = this->RowBinarySize();
#endif

	 newCapacity -= newCapacity % rowSize;

	tableSet.MoveTableData(this->GetDataAddrOffset(), newCapacity - _Capacity);

	_Capacity = newCapacity;

	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Compress(RIDBTABLESET tableSet, RCFLOAT compressionFactor)
{
	if (compressionFactor == 1.0F)
		return DbResult::SUCCESS;

	if (compressionFactor < 1.0F)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	DWORD newCapacity = (1.0F / compressionFactor) * _Capacity;

	if (newCapacity < this->Size())
	{
		newCapacity = this->Size();
	}
	else
	{
	#ifdef _DEBUG
		SIZE rowSize = this->RowStringSize();
	#else
		SIZE rowSize = this->RowBinarySize();
	#endif

		newCapacity -= newCapacity % rowSize;
	}

	tableSet.MoveTableData(this->GetDataAddrOffset(), newCapacity - _Capacity);

	_Capacity = newCapacity;

	return DbResult::SUCCESS;
}

CSTORAGERESULT DbTable::EraseData(RCDWORD size, RCDWORD startDataAddr)
{
	RISTORAGE storage = this->GetStorage();

	STORAGERESULT result = storage.Open(TRUE);
	if ((BYTE)result)
		return result;

	if (startDataAddr > 0)
	{
		result = storage.Seek(_DataAddrOffset + startDataAddr);
		if ((BYTE)result)
			return result;
	}

	result = storage.Erase(size);
	if ((BYTE)result)
		return result;

	return storage.Close();
}

CSTORAGERESULT DbTable::MoveData(RCLONG dataAddrOffsetDelta, RCDWORD startDataAddr, CBOOL eraseNewOrExcessAllocation)
{
	if (dataAddrOffsetDelta == 0)
		return StorageResult::SUCCESS;

	RISTORAGE storage = this->GetStorage();

	STORAGERESULT result = storage.Open(TRUE);
	if ((BYTE)result)
		return result;

	CLONGLONG relativeAddrOffset = (RCLONGLONG)_DataAddrOffset + (RCLONGLONG)startDataAddr;

	LONGLONG endAddr = this->Size();
	LONGLONG relativeAddrIter = 0;
	LONGLONG targetAddr = 0;
	BYTE datum = 0;

	while (relativeAddrIter < endAddr)
	{
		if (dataAddrOffsetDelta < 0)
			targetAddr = relativeAddrOffset + relativeAddrIter - dataAddrOffsetDelta;
		else
			targetAddr = relativeAddrOffset + endAddr - relativeAddrIter - 1;
		result = storage.Seek(targetAddr);
		if ((BYTE)result)
			return result;

		result = storage.Read(&datum, 1);
		if ((BYTE)result)
			return result;

		if (dataAddrOffsetDelta < 0)
			targetAddr += dataAddrOffsetDelta;
		else
			targetAddr -= dataAddrOffsetDelta;
		result = storage.Seek(targetAddr + dataAddrOffsetDelta);
		if ((BYTE)result)
			return result;

		result = storage.Write(&datum, 1);
		if ((BYTE)result)
			return result;

		++relativeAddrIter;
	}

	if (eraseNewOrExcessAllocation AND dataAddrOffsetDelta > 0)
	{
		endAddr = (RCLONGLONG)_DataAddrOffset + (RCLONGLONG)startDataAddr;
		targetAddr = endAddr - dataAddrOffsetDelta + 1;

		while (targetAddr < endAddr)
		{
			result = storage.Seek(targetAddr++);
			if ((BYTE)result)
				return result;

			result = storage.Erase(1);
			if ((BYTE)result)
				return result;
		}
	}

	result = storage.Close();
	if ((BYTE)result)
		return result;

	if (startDataAddr > 0)
		return result;

	this->SetDataAddrOffset((RCLONGLONG)_DataAddrOffset + dataAddrOffsetDelta);

	return this->Save();
}

CSTORAGERESULT DbTable::MoveDefinition(CSHORT addrOffsetDelta, CBOOL eraseNewOrExcessAllocation)
{
	if (addrOffsetDelta == 0)
		return StorageResult::SUCCESS;

	RISTORAGE storage = this->GetStorage();

	STORAGERESULT result = storage.Open(TRUE);
	if ((BYTE)result)
		return result;

	CSHORT headerAddrOffset = this->GetAddrOffset();

#ifdef _DEBUG
	LONG endAddr = headerAddrOffset + _TableDef->StringSize();
#else
	LONG endAddr = headerAddrOffset + _TableDef->BinarySize();
#endif

	LONG relativeAddrIter = 0;
	LONG targetAddr = 0;
	BYTE datum = 0;

	while (relativeAddrIter < endAddr)
	{
		if (addrOffsetDelta < 0)
			targetAddr = headerAddrOffset + relativeAddrIter - addrOffsetDelta;
		else
			targetAddr = headerAddrOffset + endAddr - relativeAddrIter - 1;
		result = storage.Seek(targetAddr);
		if ((BYTE)result)
			return result;

		result = storage.Read(&datum, 1);
		if ((BYTE)result)
			return result;

		if (addrOffsetDelta < 0)
			targetAddr += addrOffsetDelta;
		else
			targetAddr -= addrOffsetDelta;
		result = storage.Seek(targetAddr + addrOffsetDelta);
		if ((BYTE)result)
			return result;

		result = storage.Write(&datum, 1);
		if ((BYTE)result)
			return result;

		++relativeAddrIter;
	}

	if (eraseNewOrExcessAllocation AND addrOffsetDelta > 0)
	{
		endAddr = headerAddrOffset;
		targetAddr = endAddr - addrOffsetDelta + 1;

		while (targetAddr < endAddr)
		{
			result = storage.Seek(targetAddr++);
			if ((BYTE)result)
				return result;

			result = storage.Erase(1);
			if ((BYTE)result)
				return result;
		}
	}

	result = storage.Close();
	if ((BYTE)result)
		return result;

	_TableDef->SetAddrOffset(headerAddrOffset + addrOffsetDelta);

	return _TableDef->Save();
}

CDWORD DbTable::RowsBinarySize() const
{
	return this->RowCount() * this->RowBinarySize();
}

CDWORD DbTable::RowsStringSize() const
{
	return this->RowCount() * (this->RowStringSize() - 1);
}

CSIZE DbTable::RowBinarySize() const
{
	return this->RowSize();
}

CSIZE DbTable::RowStringSize() const
{
	return 2 * this->RowSize() + 1;
}

CSTORAGERESULT DbTable::SaveRow(PCBYTE rowData, CSIZE rowIdx) const
{
#ifdef _DEBUG

	SIZE rowSize = this->RowStringSize();

	PCBYTE data = reinterpret_cast<PCBYTE>(this->RowToString(rowData, rowSize));
	delete[] rowData;

#else

	SIZE rowSize = this->RowBinarySize();

	PCBYTE data = rowData;

#endif

	return this->GetStorage().Save(data, rowSize,_DataAddrOffset + rowIdx * rowSize);
}

CSTORAGERESULT DbTable::LoadAllRows(PBYTE & recordSet, RSIZE recordCount, PSIZE rowSize)
{
#ifdef _DEBUG
	SIZE _rowSize = this->RowStringSize();
#else
	SIZE _rowSize = this->RowBinarySize();
#endif

	recordCount = _RowCount;

	if (rowSize)
		*rowSize = this->RowSize();

	DWORD rowsSize = this->Size();

	PBYTE rowsBuffer = new byte[rowsSize];

	STORAGERESULT result = this->GetStorage().Load(recordSet, rowsSize, _DataAddrOffset);
	if ((BYTE)result)
		return result;

#ifdef _DEBUG
	recordSet = this->RowsFromString(reinterpret_cast<PCHAR>(rowsBuffer), rowsSize, _rowSize);
	delete[] rowsBuffer;
#endif

	return result;
}

CSTORAGERESULT DbTable::LoadRow(CSIZE rowIdx, PBYTE & resultRow, PSIZE rowSize)
{
#ifdef _DEBUG
	SIZE _rowSize = this->RowStringSize();
#else
	SIZE _rowSize = this->RowBinarySize();
#endif

	if (rowSize)
		*rowSize = this->RowSize();

	PBYTE rowBuffer = new byte[_rowSize];

	STORAGERESULT result = this->GetStorage().Load(rowBuffer, _rowSize, _DataAddrOffset + rowIdx * _rowSize);
	if ((BYTE)result)
		return result;

#ifdef _DEBUG
	resultRow = this->RowFromString(reinterpret_cast<PCHAR>(rowBuffer), _rowSize);
	delete[] rowBuffer;
#endif

	return result;
}

PCCHAR DbTable::RowToString(PCBYTE data, CSIZE rowSize) const
{
	PCHAR rowData = new char[rowSize];
	rowData[rowSize - 1] = '\0';

	PCHAR bufferPtr = rowData;

	for (SIZE i = 0; i < rowSize; i++)
		bufferPtr = StringInsertValue<BYTE>(data[i], bufferPtr);

	return reinterpret_cast<PCCHAR>(rowData);
}

PBYTE DbTable::RowsFromString(PCCHAR buffer, RCDWORD rowsSize, CSIZE rowSize)
{
	PBYTE rowsBuffer = new byte[rowsSize];
	rowsBuffer[rowsSize - 1] = '\0';

	PCCHAR bufferPtr = buffer;

	for (SIZE rowIdx = 0; rowIdx < _RowCount; rowIdx++)
	{
		for (SIZE i = 0; i < rowSize; i++)
			bufferPtr = StringReadValue<BYTE>(rowsBuffer[rowIdx * rowSize + i], bufferPtr);
	}

	return reinterpret_cast<PBYTE &>(rowsBuffer);
}

PBYTE DbTable::RowFromString(PCCHAR buffer, CSIZE rowSize)
{
	PBYTE rowBuffer = new byte[rowSize];
	rowBuffer[rowSize - 1] = '\0';

	PCCHAR bufferPtr = buffer;

	for (SIZE i = 0; i < rowSize; i++)
		bufferPtr = StringReadValue<BYTE>(rowBuffer[i], bufferPtr);

	return reinterpret_cast<PBYTE &>(rowBuffer);
}


// [IDbTableDef] IHELPER METHODS

CBYTE DbTable::TableNameLength() const
{
	return _TableDef->TableNameLength();
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DB_TABLES
