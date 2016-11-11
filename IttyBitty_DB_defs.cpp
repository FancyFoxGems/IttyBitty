/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_DB)) && !defined(NO_ITTYBITTY_DB_DEFS)
	#define NO_ITTYBITTY_DB_DEFS
#endif

#ifndef NO_ITTYBITTY_DB_DEFS


#include "IttyBitty_DB_defs.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE DEFINITIONS

PBYTE IttyBitty::__db_table_def_set_buffer = NULL;
PBYTE IttyBitty::__db_table_def_buffer = NULL;

#pragma endregion


#pragma region [DbTableDef] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

DbTableDef::DbTableDef(CSIZE rowSize, PCCHAR tableName, RCDWORD addrOffset)
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


// STATIC FUNCTIONS

RDBTABLEDEF DbTableDef::NULL_OBJECT()
{
	STATIC DbTableDef NULL_DBTABLEDEF;
	return NULL_DBTABLEDEF;
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

VOID DbTableDef::SetAddrOffset(RCDWORD addrOffset)
{
	_AddrOffset = addrOffset;
}

VOID DbTableDef::SetTableName(PCCHAR tableName)
{
	_TableName = tableName;
}


// [IStorable] IMPLEMENTATION

CSTORAGERESULT DbTableDef::SaveAsBinary() const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTableDef::SaveAsString() const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTableDef::LoadFromBinary()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTableDef::LoadFromString()
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


#pragma region [DbTableDefSet] IMPLEMENTATION

DbTableDefSet::DbTableDefSet(CBYTE tableDefCount)
	: _Dispose(TRUE), _TableDefCount(tableDefCount), _TableDefs(NULL)
{
	if (_TableDefCount > 0)
		_TableDefs = new PIDBTABLEDEF[_TableDefCount];
}

DbTableDefSet::DbTableDefSet(PCBYTE data)
{
	this->FromBinary(data);
}

DbTableDefSet::DbTableDefSet(PCCHAR data)
{
	this->FromString(data);
}

DbTableDefSet::DbTableDefSet(RCIDBTABLEDEF tableDef)
	: _Dispose(TRUE), _TableDefCount(1), _TableDefs(NULL)
{
	_TableDefs = new PIDBTABLEDEF[_TableDefCount];

#ifdef _DEBUG
	_TableDefs[0] = new DbTableDef(tableDef.ToString());
#else
	_TableDefs[0] = new DbTableDef(tableDef.ToBinary());
#endif
}

DbTableDefSet::DbTableDefSet(CBYTE tableDefCount, PPIDBTABLEDEF tableDefs)
	: _TableDefCount(tableDefCount), _TableDefs(tableDefs)
{
	if (_TableDefs == NULL)
		_TableDefs = new PIDBTABLEDEF[_TableDefCount];
}

DbTableDefSet::~DbTableDefSet()
{
	this->Dispose();
}


// PROTECTED DISPOSAL METHOD

VOID DbTableDefSet::Dispose()
{
	if (_TableDefs == NULL)
		return;

	if (_Dispose)
	{
		for (BYTE i = 0; i < this->TableDefCount(); i++)
		{
			if (_TableDefs[i] != NULL)
			{
				delete _TableDefs[i];
				_TableDefs[i] = NULL;
			}
		}
	}

	delete[] _TableDefs;
	_TableDefs = NULL;
}

PCIDBTABLEDEF DbTableDefSet::operator[](CBYTE tableDefIdx) const
{
	if (_TableDefs == NULL)
		return NULL;

	return _TableDefs[tableDefIdx];
}

PIDBTABLEDEF DbTableDefSet::operator[](CBYTE tableDefIdx)
{
	if (_TableDefs == NULL)
		return NULL;

	return _TableDefs[tableDefIdx];
}

PCIDBTABLEDEF DbTableDefSet::operator[](PCCHAR tableName) const
{
	PCIDBTABLEDEF tableDefPtr = NULL;

	for (BYTE i = 0; i < this->TableDefCount(); i++)
	{
		tableDefPtr = this->operator[](i);

		if (strcmp(tableDefPtr->GetTableName(), tableName))
			break;
	}

	return tableDefPtr;
}

PIDBTABLEDEF DbTableDefSet::operator[](PCCHAR tableName)
{
	PIDBTABLEDEF tableDefPtr = NULL;

	for (BYTE i = 0; i < this->TableDefCount(); i++)
	{
		tableDefPtr = this->operator[](i);

		if (strcmp(tableDefPtr->GetTableName(), tableName))
			break;
	}

	return tableDefPtr;
}


// [IDbTableDefSet] IMPLEMENTATION

CBYTE DbTableDefSet::TableDefCount() const
{
	return _TableDefCount;
}

RCIDBTABLEDEF DbTableDefSet::TableDef(CBYTE tableDefIdx) const
{
	PCIDBTABLEDEF tableDefPtr = this->operator[](tableDefIdx);

	if (!tableDefPtr)
		return DbTableDef::NULL_OBJECT();

	return *tableDefPtr;
}

RIDBTABLEDEF DbTableDefSet::TableDef(CBYTE tableDefIdx)
{
	PIDBTABLEDEF tableDefPtr = this->operator[](tableDefIdx);

	if (!tableDefPtr)
		return DbTableDef::NULL_OBJECT();

	return *tableDefPtr;
}

RCIDBTABLEDEF DbTableDefSet::TableDef(PCCHAR tableName) const
{
	PCIDBTABLEDEF tableDefPtr = this->operator[](tableName);

	if (!tableDefPtr)
		return DbTableDef::NULL_OBJECT();

	return *tableDefPtr;
}

RIDBTABLEDEF DbTableDefSet::TableDef(PCCHAR tableName)
{
	PIDBTABLEDEF tableDefPtr = this->operator[](tableName);

	if (!tableDefPtr)
		return DbTableDef::NULL_OBJECT();

	return *tableDefPtr;
}


// [IStorable] IMPLEMENTATION

CSTORAGERESULT DbTableDefSet::SaveAsBinary() const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTableDefSet::SaveAsString() const
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTableDefSet::LoadFromBinary()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT DbTableDefSet::LoadFromString()
{
	return StorageResult::SUCCESS;
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTableDefSet::BinarySize() const
{
	return SIZEOF(CSIZE) + SIZEOF(CBYTE) + this->TableDefsByteSize();
}

CSIZE DbTableDefSet::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(CBYTE) + this->TableDefsStringSize() + 1;
}

PCBYTE DbTableDefSet::ToBinary() const
{
	CSIZE size = this->BinarySize();

	if (__db_table_def_set_buffer)
		delete[] __db_table_def_set_buffer;

	__db_table_def_set_buffer = new byte[size];

	PBYTE bufferPtr = __db_table_def_set_buffer;

	memcpy(bufferPtr, &size, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	CBYTE tableDefCount = this->TableDefCount();
	memcpy(bufferPtr, &tableDefCount, SIZEOF(CBYTE));
	bufferPtr += SIZEOF(CBYTE);

	PIDBTABLEDEF tableDef = NULL;
	PCBYTE tableDefBytes = NULL;
	SIZE tableDefSize = 0;

	for (SIZE i = 0; i < tableDefCount; i++)
	{
		tableDef = _TableDefs[i];
		tableDefBytes = tableDef->ToBinary();
		tableDefSize = tableDef->BinarySize();

		memcpy(bufferPtr, tableDefBytes, tableDefSize);

		bufferPtr += tableDefSize;
	}

	return __db_table_def_set_buffer;
}

PCCHAR DbTableDefSet::ToString() const
{
	CSIZE size = this->StringSize();
	CBYTE tableDefCount = this->TableDefCount();

	if (__db_table_def_set_buffer)
		delete[] __db_table_def_set_buffer;

	__db_table_def_set_buffer = new byte[size];
	__db_table_def_set_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__db_table_def_set_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(tableDefCount, bufferPtr);

	PIDBTABLEDEF tableDef = NULL;
	PCCHAR tableDefStr = NULL;
	SIZE tableDefSize = 0;

	for (SIZE i = 0; i < tableDefCount; i++)
	{
		tableDef = _TableDefs[i];
		tableDefStr = tableDef->ToString();
		tableDefSize = tableDef->StringSize() - 1;

		memcpy(bufferPtr, tableDefStr, tableDefSize);

		if (i == 0)
			bufferPtr = StringInsertValue<CBYTE>(tableDefCount, bufferPtr - 2);

		bufferPtr += tableDefSize;
	}

	return reinterpret_cast<PCCHAR>(__db_table_def_set_buffer);
}

VOID DbTableDefSet::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_TableDefCount = *bufferPtr++;

	this->Dispose();

	if (_TableDefCount > 0)
		_TableDefs = new PIDBTABLEDEF[_TableDefCount];

	_Dispose = TRUE;

	for (SIZE i = 0; i < _TableDefCount; i++)
	{
		_TableDefs[i] = new DbTableDef(bufferPtr);

		bufferPtr += _TableDefs[i]->BinarySize();
	}
}

VOID DbTableDefSet::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<BYTE>(_TableDefCount, bufferPtr);

	this->Dispose();

	if (_TableDefCount > 0)
		_TableDefs = new PIDBTABLEDEF[_TableDefCount];

	_Dispose = TRUE;

	for (BYTE i = 0; i < _TableDefCount; i++)
	{
		_TableDefs[i] = new DbTableDef(bufferPtr);

		bufferPtr += _TableDefs[i]->StringSize() - 1;
	}
}

#ifdef ARDUINO

SIZE DbTableDefSet::printTo(Print & printer) const
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

	delete[] __db_table_def_set_buffer;
	__db_table_def_set_buffer = NULL;

	return size;
}

#endif


// [IDbTableDef] HELPER METHODS

CSIZE DbTableDefSet::TableDefsByteSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->TableDefCount(); i++)
		size += _TableDefs[i]->BinarySize();

	return size;
}

CSIZE DbTableDefSet::TableDefsStringSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->TableDefCount(); i++)
		size += _TableDefs[i]->StringSize();

	return size;
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DB_DEFS
