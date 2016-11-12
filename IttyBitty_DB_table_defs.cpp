/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_DB)) && !defined(NO_ITTYBITTY_DB_DEFS)
	#define NO_ITTYBITTY_DB_DEFS
#endif

#ifndef NO_ITTYBITTY_DB_DEFS


#include "IttyBitty_DB_table_defs.h"

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
	return 2 * this->BinarySize() + 1;
}

PCBYTE DbTableDef::ToBinary() const
{
	CSIZE size = this->BinarySize();

	this->FreeBuffer();

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

	this->FreeBuffer();

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

VOID DbTableDef::FreeBuffer() const
{
	if (!__db_table_def_buffer)
		return;

	delete[] __db_table_def_buffer;
	__db_table_def_buffer = NULL;
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

	this->FreeBuffer();

	return size;
}

#endif


// [IDbTableDef] IHELPER METHODS

CBYTE DbTableDef::TableNameLength() const
{
	if (!_TableName)
		return (CBYTE)0;

	return (CBYTE)strlen(_TableName);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DB_DEFS