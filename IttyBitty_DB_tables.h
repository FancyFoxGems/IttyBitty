/***********************************************************************************************
* [IttyBitty_DB_tables.h]: TABLE DATA STRUCTURES FOR STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_DB_TABLES_H
#define _ITTYBITTY_DB_TABLES_H


#include "IttyBitty_DB_defs.h"


#pragma region DEFINES

#define DB_DEFAULT_GROWTH_FACTOR		2.0F
#define DB_ERASE_GROWTH_ALLOCATION		TRUE
#define DB_ERASE_DELETED_ROWS			TRUE

#pragma endregion


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __db_table_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IDbTable;
	TYPEDEF_CLASS_ALIASES(IDbTable, IDBTABLE);

	TYPEDEF_CLASS_ALIASES(DbTable, DBTABLE);

	TEMPLATE_CLASS_USING_ALIASES(DEFAULT_T_CLAUSE, DEFAULT_T_ARGS, TypedDbTable, TYPEDDBTABLE);

	// TODO: Not yet implemented.
	class FieldedDbTable;
	TYPEDEF_CLASS_ALIASES(FieldedDbTable, FIELDEDDBTABLE);

	class IDbTableSet;
	TYPEDEF_CLASS_ALIASES(IDbTableSet, IDBTABLESET);

#pragma endregion


#pragma region [IDbTable] DEFINITION

	CLASS IDbTable : public IDbTableDef
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTable() { }


		// INTERFACE METHODS

		VIRTUAL CDWORD Size() const = 0;
		VIRTUAL CDWORD Capacity() const = 0;

		VIRTUAL CSIZE RowCount() const = 0;
		VIRTUAL CSIZE RowsAvailable() const = 0;

		VIRTUAL CDBRESULT SelectAll(PBYTE &, RSIZE);

		template DEFAULT_T_CLAUSE
		CDBRESULT SelectAll(T *& recordSet, RSIZE recordCount)
		{
			return this->SelectAll(reinterpret_cast<PBYTE &>(recordSet), recordCount);
		}

		VIRTUAL CDBRESULT Find(CSIZE, PBYTE, PSIZE = NULL) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT Find(CSIZE rowIdx, T * result)
		{
			return this->Find(rowIdx, reinterpret_cast<PBYTE>(result));
		}

		VIRTUAL CDBRESULT Insert(PCBYTE, CSIZE = MAX_OF(SIZE)) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT Insert(CONST T & rowData, CSIZE insertIdx = MAX_OF(SIZE))
		{
			return this->Insert(reinterpret_cast<PCBYTE>(rowData), insertIdx);
		}

		VIRTUAL CDBRESULT Update(CSIZE, PCBYTE) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT Update(CSIZE rowIdx, CONST T & rowData)
		{
			return this->Update(rowIdx, reinterpret_cast<PCBYTE>(rowData));
		}

		VIRTUAL CDBRESULT Delete(CSIZE) = 0;
		VIRTUAL CDBRESULT Truncate() = 0;


	protected:

		friend class Database;


		// HELPER METHODS

		VIRTUAL CDBRESULT Grow(RIDBTABLESET, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR) = 0;
		VIRTUAL CDBRESULT Compress(RIDBTABLESET, RCFLOAT = 0.0F) = 0;

		VIRTUAL CDWORD RowsBinarySize() const = 0;
		VIRTUAL CDWORD RowsStringSize() const = 0;

		VIRTUAL CSTORAGERESULT SaveRowAsBinary(CSIZE) const = 0;
		VIRTUAL CSTORAGERESULT SaveRowAsString(CSIZE) const = 0;

		VIRTUAL CSTORAGERESULT LoadRowFromBinary(CSIZE) = 0;
		VIRTUAL CSTORAGERESULT LoadRowFromString(CSIZE) = 0;

		VIRTUAL CSIZE RowBinarySize() const = 0;
		VIRTUAL CSIZE RowStringSize() const = 0;

		VIRTUAL PCBYTE RowToBinary(PCBYTE) const = 0;
		VIRTUAL PCCHAR RowToString(PCBYTE) const = 0;

		VIRTUAL PBYTE RowFromBinary(PCBYTE) = 0;
		VIRTUAL PBYTE RowFromString(PCCHAR) = 0;


		IDbTable() { }
	};

#pragma endregion


#pragma region [DbTable] DEFINITION

	CLASS DbTable : public IDbTable
	{
	protected:

		// CONSTRUCTORS/DESTRUCTOR

		DbTable(CSIZE = 0, PCCHAR = NULL, RCDWORD = 0, RCDWORD = 0);

		EXPLICIT DbTable(PCBYTE);
		EXPLICIT DbTable(PCCHAR);


		// STATIC FUNCTIONS

		STATIC RDBTABLE NULL_OBJECT();


	public:

		// DESTRUCTOR

		VIRTUAL ~DbTable();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IDbTable] IMPLEMENTATION

		VIRTUAL CDWORD Size() const;
		VIRTUAL CDWORD Capacity() const;

		VIRTUAL CSIZE RowCount() const;
		VIRTUAL CSIZE RowsAvailable() const;

		VIRTUAL CDBRESULT SelectAll(PBYTE &, RSIZE);
		VIRTUAL CDBRESULT Find(CSIZE, PBYTE, PSIZE = NULL);

		VIRTUAL CDBRESULT Insert(PCBYTE, CSIZE = MAX_OF(SIZE));
		VIRTUAL CDBRESULT Update(CSIZE, PCBYTE);

		VIRTUAL CDBRESULT Delete(CSIZE);
		VIRTUAL CDBRESULT Truncate();


		// [IDbTableDef] IMPLEMENTATION

		VIRTUAL CSIZE RowSize() const;

		VIRTUAL DWORD GetAddrOffset() const;
		VIRTUAL PCCHAR GetTableName() const;

		VIRTUAL VOID SetAddrOffset(RCDWORD);
		VIRTUAL VOID SetTableName(PCCHAR);


		// [IStorable] IMPLEMENTATION

		VIRTUAL CSTORAGERESULT SaveAsBinary() const;
		VIRTUAL CSTORAGERESULT SaveAsString() const;

		VIRTUAL CSTORAGERESULT LoadFromBinary();
		VIRTUAL CSTORAGERESULT LoadFromString();


		// [ISerializable] IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


	protected:

		friend class Database;


		// INSTANCE VARIABLES

		BOOL _CapacityChanged = FALSE;

		DWORD _Capacity = 0;
		SIZE _RowCount = 0;

		PIDBTABLEDEF _TableDef = NULL;


		// [IDbTable] HELPER METHODS

		VIRTUAL CDBRESULT Grow(RIDBTABLESET, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);
		VIRTUAL CDBRESULT Compress(RIDBTABLESET, RCFLOAT = 0.0F);

		VIRTUAL CDWORD RowsBinarySize() const;
		VIRTUAL CDWORD RowsStringSize() const;

		VIRTUAL CSTORAGERESULT SaveRowAsBinary(CSIZE) const;
		VIRTUAL CSTORAGERESULT SaveRowAsString(CSIZE) const;

		VIRTUAL CSTORAGERESULT LoadRowFromBinary(CSIZE);
		VIRTUAL CSTORAGERESULT LoadRowFromString(CSIZE);

		VIRTUAL CSIZE RowBinarySize() const;
		VIRTUAL CSIZE RowStringSize() const;

		VIRTUAL PCBYTE RowToBinary(PCBYTE) const;
		VIRTUAL PCCHAR RowToString(PCBYTE) const;

		VIRTUAL PBYTE RowFromBinary(PCBYTE);
		VIRTUAL PBYTE RowFromString(PCCHAR);


		// [IDbTableDef] IHELPER METHODS

		VIRTUAL CBYTE TableNameLength() const;
	};

#pragma endregion


#pragma region [TypedDbTable] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS TypedDbTable : public DbTable
	{
	public:

		// TYPEDEF ALIASES

		typedef T ROW_TYPE;


		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CSIZE ROW_SIZE()
		{
			return T_SIZE;
		}


	protected:

		// CONSTRUCTORS

		TypedDbTable(PCCHAR tableName = NULL, RCDWORD addrOffset = 0)
			: DbTable(ROW_SIZE(), tableName, addrOffset) { }


	public:

		// [DbTable] OVERRIDES

		CSIZE RowSize() const
		{
			return ROW_SIZE();
		}


		// USER METHODS

		CDBRESULT SelectAll(T *& recordSet, RSIZE recordCount)
		{
			return IDbTable::SelectAll<T>(recordSet, recordCount);
		}

		CDBRESULT Find(RCSIZE rowIdx, T & result)
		{
			return IDbTable::Find<T>(rowIdx, result);
		}

		CDBRESULT Insert(CONST T & rowData, CSIZE insertIdx = MAX_OF(SIZE))
		{
			return IDbTable::Insert<T>(rowData, insertIdx);
		}

		CDBRESULT Update(CSIZE rowIdx, CONST T & rowData)
		{
			return IDbTable::Update<T>(rowIdx, rowData);
		}


	protected:

		friend class IDbTableSet;
	};

#pragma endregion


#pragma region [IDbTableSet] DEFINITION

	CLASS IDbTableSet : protected IDbTableDefSet
	{
	public:

		// DESTRUCTOR

		~IDbTableSet() { }


		// OPERATORS

		VIRTUAL PCIDBTABLE operator[](CBYTE) const = 0;
		VIRTUAL PIDBTABLE operator[](CBYTE) = 0;

		VIRTUAL PCIDBTABLE operator[](PCCHAR) const = 0;
		VIRTUAL PIDBTABLE operator[](PCCHAR) = 0;


		// INTERFACE METHODS

		VIRTUAL CDWORD Size() const = 0;
		VIRTUAL CWORD Capacity() const = 0;

		VIRTUAL CBYTE TableCount() const = 0;

		VIRTUAL CDBRESULT TruncateAllTables() = 0;
		VIRTUAL CDBRESULT DropAllTables() = 0;

		VIRTUAL RCIDBTABLE Table(CBYTE = 0) const = 0;
		VIRTUAL RIDBTABLE Table(CBYTE = 0) = 0;

		VIRTUAL RCIDBTABLE Table(PCCHAR) const = 0;
		VIRTUAL RIDBTABLE Table(PCCHAR) = 0;

		VIRTUAL CDWORD SizeOf(CBYTE) const = 0;
		VIRTUAL CDWORD SizeOf(PCCHAR) const = 0;

		VIRTUAL CDWORD CapacityOf(CBYTE) const = 0;
		VIRTUAL CDWORD CapacityOf(PCCHAR) const = 0;

		VIRTUAL CSIZE RowCountFor(CBYTE) const = 0;
		VIRTUAL CSIZE RowCountFor(PCCHAR) const = 0;

		VIRTUAL CSIZE RowsAvailableFor(CBYTE) const = 0;
		VIRTUAL CSIZE RowsAvailableFor(PCCHAR) const = 0;

		VIRTUAL CDBRESULT CreateTable(CSIZE, PCCHAR = NULL, CBYTE = MAX_OF(BYTE)) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT CreateTable(PCCHAR tableName = NULL, CBYTE newTableIdx = MAX_OF(BYTE))
		{
			return DbResult::SUCCESS;
		}

		VIRTUAL CDBRESULT DropTable(CBYTE) = 0;
		VIRTUAL CDBRESULT DropTable(PCCHAR) = 0;

		VIRTUAL CDBRESULT GrowTable(CBYTE, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR) = 0;
		VIRTUAL CDBRESULT GrowTable(PCCHAR, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR) = 0;

		VIRTUAL CDBRESULT CompressTable(CBYTE, RCFLOAT = 0.0F) = 0;
		VIRTUAL CDBRESULT CompressTable(PCCHAR, RCFLOAT = 0.0F) = 0;

		VIRTUAL CDBRESULT SelectAllFrom(CBYTE, PBYTE &, RSIZE) = 0;
		VIRTUAL CDBRESULT SelectAllFrom(PCCHAR, PBYTE &, RSIZE) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT SelectAllFrom(CBYTE tableIdx, T *& recordSet, RSIZE recordCount)
		{
			PIDBTABLE table = this->operator[](tableIdx);

			return table->SelectAll(reinterpret_cast<PBYTE &>(recordSet), recordCount);
		}

		template DEFAULT_T_CLAUSE
		CDBRESULT SelectAllFrom(PCCHAR tableName, T *& recordSet, RSIZE recordCount)
		{
			PIDBTABLE table = this->operator[](tableName);

			return table->SelectAll(reinterpret_cast<PBYTE &>(recordSet), recordCount);
		}

		VIRTUAL CDBRESULT FindFrom(CBYTE, CSIZE, PBYTE, PSIZE) = 0;
		VIRTUAL CDBRESULT FindFrom(PCCHAR, CSIZE, PBYTE, PSIZE) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT FindFrom(CBYTE tableIdx, CSIZE rowIdx, T * record)
		{
			PIDBTABLE table = this->operator[](tableIdx);

			return table->Find(rowIdx, reinterpret_cast<PBYTE>(record));
		}

		template DEFAULT_T_CLAUSE
		CDBRESULT FindFrom(PCCHAR tableName, CSIZE rowIdx, T * record)
		{
			PIDBTABLE table = this->operator[](tableName);

			return table->Find(rowIdx, reinterpret_cast<PBYTE>(record));
		}

		VIRTUAL CDBRESULT InsertInto(CBYTE, PCBYTE, CSIZE = MAX_OF(SIZE)) = 0;
		VIRTUAL CDBRESULT InsertInto(PCCHAR, PCBYTE, CSIZE = MAX_OF(SIZE)) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT InsertInto(CBYTE tableIdx, CONST T & rowData, CSIZE insertIdx = MAX_OF(SIZE))
		{
			PIDBTABLE table = this->operator[](tableIdx);

			return table->Insert(reinterpret_cast<PCBYTE>(rowData), insertIdx);
		}

		template DEFAULT_T_CLAUSE
		CDBRESULT InsertInto(PCCHAR tableName, CONST T & rowData, CSIZE insertIdx = MAX_OF(SIZE))
		{
			PIDBTABLE table = this->operator[](tableName);

			return table->Insert(reinterpret_cast<PCBYTE>(rowData), insertIdx);
		}

		VIRTUAL CDBRESULT UpdateTo(CBYTE, CSIZE, PCBYTE) = 0;
		VIRTUAL CDBRESULT UpdateTo(PCCHAR, CSIZE, PCBYTE) = 0;

		template DEFAULT_T_CLAUSE
		CDBRESULT UpdateTo(CBYTE tableIdx, CSIZE rowIdx, CONST T & rowData)
		{
			PIDBTABLE table = this->operator[](tableIdx);

			return table->Update(rowIdx, reinterpret_cast<PCBYTE>(rowData));
		}

		template DEFAULT_T_CLAUSE
		CDBRESULT UpdateTo(PCCHAR tableName, CSIZE rowIdx, CONST T & rowData)
		{
			PIDBTABLE table = this->operator[](tableName);

			return table->Update(rowIdx, reinterpret_cast<PCBYTE>(rowData));
		}

		VIRTUAL CDBRESULT DeleteFrom(CBYTE, CSIZE) = 0;
		VIRTUAL CDBRESULT DeleteFrom(PCCHAR, CSIZE) = 0;

		VIRTUAL CDBRESULT TruncateTable(CBYTE) = 0;
		VIRTUAL CDBRESULT TruncateTable(PCCHAR) = 0;


	protected:

		// HELPER METHODS

		VIRTUAL CDBRESULT MoveTables(CSIZE, RCLONG) = 0;

		VIRTUAL CSIZE TablesByteSize() const = 0;
		VIRTUAL CSIZE TablesStringSize() const = 0;


		IDbTableSet() {}
	};

#pragma endregion
}

#endif
