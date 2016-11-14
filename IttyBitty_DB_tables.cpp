/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_DB)) && !defined(NO_ITTYBITTY_DB_TABLES)
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

DbTable::DbTable(RISTORAGE storage, CSIZE rowSize, PCCHAR tableName, RCDWORD capacity, CSIZE addrOffset, RCDWORD dataAddrOffset)
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
	// TODO

	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Update(PCBYTE rowData, CSIZE rowIdx)
{
	if (rowIdx > this->RowCount() - 1)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	// TODO

	return DbResult::SUCCESS;
}

CDBRESULT DbTable::Delete(CSIZE rowIdx, CBOOL writeEraseValue)
{
	if (rowIdx > this->RowCount() - 1)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	// TODO

	--_RowCount;

	return (CDBRESULT)this->Save();;
}

CDBRESULT DbTable::Truncate(CBOOL writeEraseValue)
{
	if (this->RowCount() == 0)
		return DbResult::SUCCESS;

	// TODO

	_RowCount = 0;

	return (CDBRESULT)this->Save();;
}


// [IDbTableDef] IMPLEMENTATION

CSIZE DbTable::RowSize() const
{
	return _TableDef->RowSize();
}

CSIZE DbTable::GetAddrOffset() const
{
	return _TableDef->GetAddrOffset();
}

PCCHAR DbTable::GetTableName() const
{
	return _TableDef->GetTableName();
}

VOID DbTable::SetAddrOffset(CSIZE addrOffset)
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
	return this->GetStorage().SaveData(this->ToBinary(),
		this->BinarySize(), this->GetAddrOffset() + _TableDef->BinarySize());
}

CSTORAGERESULT DbTable::SaveAsString() const
{
	return this->GetStorage().SaveData(reinterpret_cast<PCBYTE>(this->ToString()),
		this->StringSize(), this->GetAddrOffset() + _TableDef->StringSize());
}

CSTORAGERESULT DbTable::LoadFromBinary()
{
	SIZE size = this->BinarySize();
	PBYTE buffer = new byte[size];

	STORAGERESULT result = this->GetStorage().LoadData(buffer, size,
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

	STORAGERESULT result = this->GetStorage().LoadData(buffer, size,
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


// [IDbTable] HELPER METHODS

CDBRESULT DbTable::Grow(RIDBTABLESET tableSet, RCFLOAT growthFactor)
{
	if (growthFactor == 1.0F)
		return DbResult::SUCCESS;

	if (growthFactor < 1.0F)
		return DbResult::ERROR_ARGUMENT_OUT_OF_RANGE;

	 DWORD newCapacity = _Capacity * growthFactor;

	tableSet.MoveTables(this->GetDataAddrOffset(), newCapacity - _Capacity);

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
		return DbResult::SUCCESS;

	if (newCapacity < this->Size())
		return DbResult::ERROR_ARGUMENT_DATABASE_TOO_LARGE;

	tableSet.MoveTables(this->GetDataAddrOffset(), newCapacity - _Capacity);

	_Capacity = newCapacity;

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

	return this->GetStorage().SaveData(data, rowSize,_DataAddrOffset + rowIdx * rowSize);
}

CSTORAGERESULT DbTable::LoadAllRows(PBYTE & recordSet, RSIZE recordCount, PSIZE rowSize)
{
#ifdef _DEBUG
	SIZE _rowSize = this->RowStringSize();
	DWORD rowsSize = this->RowsStringSize();

#else
	SIZE _rowSize = this->RowBinarySize();
	DWORD rowsSize = this->RowsBinarySize();
#endif

	recordCount = _RowCount;

	if (rowSize)
		*rowSize = this->RowSize();

	PBYTE rowsBuffer = new byte[rowsSize];

	STORAGERESULT result = this->GetStorage().LoadData(recordSet, rowsSize, _DataAddrOffset);
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

	STORAGERESULT result = this->GetStorage().LoadData(rowBuffer, _rowSize, _DataAddrOffset + rowIdx * _rowSize);
	if ((BYTE)result)
		return result;

#ifdef _DEBUG
	resultRow = this->RowFromString(reinterpret_cast<PCHAR>(rowBuffer), _rowSize);
	delete[] rowBuffer;
#endif

	return result;
}

CSTORAGERESULT DbTable::EraseData(RCDWORD size, CBOOL writeEraseValue)
{
	RISTORAGE storage = this->GetStorage();

	STORAGERESULT result = storage.Open(TRUE);
	if ((BYTE)result)
		return result;

	result = storage.Erase(size, writeEraseValue);
	if ((BYTE)result)
		return result;

	return storage.Close();
}

CSTORAGERESULT DbTable::MoveData(RCLONG dataAddrOffsetDelta)
{
	RISTORAGE storage = this->GetStorage();

	STORAGERESULT result = storage.Open(TRUE);
	if ((BYTE)result)
		return result;

#ifdef _DEBUG
	DWORD oldDataAddr = _DataAddrOffset + this->RowsStringSize() - 1;
#else
	DWORD oldDataAddr = _DataAddrOffset + this->RowsBinarySize() - 1;
#endif

	BYTE datum = 0;
	DWORD newDataAddr = 0;

	while (oldDataAddr >= _DataAddrOffset)
	{
		result = storage.Seek(oldDataAddr);
		if ((BYTE)result)
			return result;

		result = storage.Read(&datum, 1);
		if ((BYTE)result)
			return result;

		result = storage.Seek(oldDataAddr-- + dataAddrOffsetDelta);
		if ((BYTE)result)
			return result;

		result = storage.Write(&datum, 1);
		if ((BYTE)result)
			return result;
	}

	result = storage.Close();
	if ((BYTE)result)
		return result;


	this->SetDataAddrOffset(_DataAddrOffset + dataAddrOffsetDelta);

	result = this->Save();
	if ((BYTE)result)
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
