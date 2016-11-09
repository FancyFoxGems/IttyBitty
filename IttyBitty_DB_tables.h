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

#pragma endregion


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS
		
	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __db_table_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IDbTable;
	typedef IDbTable IDBTABLE, * PIDBTABLE, & RIDBTABLE, ** PPIDBTABLE, && RRIDBTABLE;
	typedef const IDbTable CIDBTABLE, * PCIDBTABLE, & RCIDBTABLE, ** PPCIDBTABLE;

	typedef DbTable DBTABLE, * PDBTABLE, & RDBTABLE, ** PPDBTABLE, && RRDBTABLE;
	typedef const DbTable CDBTABLE, * PCDBTABLE, & RCDBTABLE, ** PPCDBTABLE;

	template<typename T>
	using TYPEDDBTABLE = TypedDbTable<T>;
	template<typename T>
	using PTYPEDDBTABLE = TypedDbTable<T> *;
	template<typename T>
	using RTYPEDDBTABLE = TypedDbTable<T> &;
	template<typename T>
	using PPTYPEDDBTABLE = TypedDbTable<T> **;
	template<typename T>
	using RRTYPEDDBTABLE = TypedDbTable<T> &&;
	template<typename T>
	using CTYPEDDBTABLE = const TypedDbTable<T>;
	template<typename T>
	using PCTYPEDDBTABLE = const TypedDbTable<T> *;
	template<typename T>
	using RCTYPEDDBTABLE = const TypedDbTable<T> &;
	template<typename T>
	using PPCTYPEDDBTABLE = const TypedDbTable<T> **;

	// TODO: Not yet implemented.
	class FieldedDbTable;
	typedef FieldedDbTable FIELDEDDBTABLE, * PFIELDEDDBTABLE, & RFIELDEDDBTABLE, ** PPFIELDEDDBTABLE, && RRFIELDEDDBTABLE;
	typedef const FieldedDbTable CFIELDEDDBTABLE, * PCFIELDEDDBTABLE, & RCFIELDEDDBTABLE, ** PPCFIELDEDDBTABLE;

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

		VIRTUAL CDBRESULT Grow(RCFLOAT, CBOOL = FALSE) = 0;
		VIRTUAL CDBRESULT Shrink(RCFLOAT, CBOOL = FALSE);

		VIRTUAL CDBRESULT SelectAll(PBYTE &, RSIZE);
		VIRTUAL CDBRESULT Find(CSIZE, PBYTE, PSIZE = NULL) = 0;

		VIRTUAL CDBRESULT Insert(PCBYTE, CSIZE = MAX_T(SIZE)) = 0;
		VIRTUAL CDBRESULT Update(PCBYTE, CSIZE, PSIZE = NULL) = 0;
		VIRTUAL CDBRESULT Delete(CSIZE) = 0;
		VIRTUAL CDBRESULT Truncate() = 0;
		

	protected:

		friend class Database;


		// HELPER METHODS

		VIRTUAL CDBRESULT SelectAllRows(PBYTE &, RSIZE) = 0;

		VIRTUAL CDBRESULT FindRow(CSIZE, PBYTE, PSIZE = NULL) = 0;

		VIRTUAL CDWORD RowsBinarySize() const = 0;
		VIRTUAL CDWORD RowsStringSize() const = 0;

		VIRTUAL CSTORAGERESULT SaveRowAsBinary(RCISTORAGE, CSIZE) const = 0;
		VIRTUAL CSTORAGERESULT SaveRowAsString(RCISTORAGE, CSIZE) const = 0;

		VIRTUAL CSTORAGERESULT LoadRowFromBinary(RCISTORAGE, CSIZE) = 0;
		VIRTUAL CSTORAGERESULT LoadFromString(RCISTORAGE, CSIZE) = 0;

		VIRTUAL CSIZE RowBinarySize() const = 0;
		VIRTUAL CSIZE RowStringSize() const = 0;

		VIRTUAL PCBYTE RowToBinary(CSIZE) const = 0;
		VIRTUAL PCCHAR RowToString(CSIZE) const = 0;

		VIRTUAL VOID RowFromBinary(PCBYTE, CSIZE) = 0;
		VIRTUAL VOID RowFromString(PCCHAR, CSIZE) = 0;


		IDbTable() { }
	};

#pragma endregion

	
#pragma region [DbTable] DEFINITION

	CLASS DbTable : public IDbTable
	{
	protected:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTable(CSIZE = 0, PCCHAR = NULL, CDWORD = 0);

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

		VIRTUAL CDBRESULT Grow(RCFLOAT, CBOOL = FALSE);
		VIRTUAL CDBRESULT Shrink(RCFLOAT, CBOOL = FALSE);

		VIRTUAL CDBRESULT SelectAll(PBYTE &, RSIZE);

		template<typename T>
		CDBRESULT SelectAll(T *& resultSet, RSIZE resultCount)
		{
			return this->SelectAllRows(reinterpret_cast<PBYTE &>(resultSet), resultCount);
		}

		VIRTUAL CDBRESULT Find(CSIZE, PBYTE, PSIZE = NULL);

		template<typename T>
		CDBRESULT Find(CSIZE rowIndex, T * result)
		{
			return this->FindRow(rowIndex, reinterpret_cast<PBYTE>(result));
		}

		VIRTUAL CDBRESULT Insert(PCBYTE, CSIZE = MAX_T(SIZE));
		VIRTUAL CDBRESULT Update(PCBYTE, CSIZE, PSIZE = NULL);
		VIRTUAL CDBRESULT Delete(CSIZE);
		VIRTUAL CDBRESULT Truncate();
		

		// [IDbTableDef] IMPLEMENTATION
		
		VIRTUAL CSIZE RowSize() const;

		VIRTUAL DWORD GetAddrOffset() const;
		VIRTUAL PCCHAR GetTableName() const;
		
		VIRTUAL VOID SetAddrOffset(CDWORD);
		VIRTUAL VOID SetTableName(PCCHAR);
				

		// [IStorable] IMPLEMENTATION

		VIRTUAL CSTORAGERESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL CSTORAGERESULT SaveAsString(RCISTORAGE) const;

		VIRTUAL CSTORAGERESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL CSTORAGERESULT LoadFromString(RCISTORAGE);


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

		PIDBTABLEDEF _TableDef;
		DWORD _RowCount = 0;
		

		// [IDbTable] HELPER METHODS

		VIRTUAL CDBRESULT SelectAllRows(PBYTE &, RSIZE);

		VIRTUAL CDBRESULT FindRow(CSIZE, PBYTE, PSIZE = NULL);

		VIRTUAL CDWORD RowsBinarySize() const;
		VIRTUAL CDWORD RowsStringSize() const;

		VIRTUAL CSTORAGERESULT SaveRowAsBinary(RCISTORAGE, CSIZE) const;
		VIRTUAL CSTORAGERESULT SaveRowAsString(RCISTORAGE, CSIZE) const;

		VIRTUAL CSTORAGERESULT LoadRowFromBinary(RCISTORAGE, CSIZE);
		VIRTUAL CSTORAGERESULT LoadFromString(RCISTORAGE, CSIZE);

		VIRTUAL CSIZE RowBinarySize() const;
		VIRTUAL CSIZE RowStringSize() const;

		VIRTUAL PCBYTE RowToBinary(CSIZE) const;
		VIRTUAL PCCHAR RowToString(CSIZE) const;

		VIRTUAL VOID RowFromBinary(PCBYTE, CSIZE);
		VIRTUAL VOID RowFromString(PCCHAR, CSIZE);


		// [IDbTableDef] IHELPER METHODS

		VIRTUAL CBYTE TableNameLength() const;
	};

#pragma endregion
	

#pragma region [TypedDbTable] DEFINITION
	
	template<typename T>
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
		
		TypedDbTable(PCCHAR tableName = NULL, CDWORD addrOffset = 0) 
			: DbTable(ROW_SIZE(), tableName, addrOffset) { }


	public:

		// [DbTable] OVERRIDES

		CSIZE RowSize() const
		{
			return ROW_SIZE();
		}


		// USER METHODS

		CDBRESULT SelectAll(T *& resultSet, RSIZE rowCount)
		{
			return DbResult::SUCCESS;
		}

		CDBRESULT Find(RCSIZE rowIndex, T & result)
		{
			return DbResult::SUCCESS;
		}


	protected:
		
		friend class Database;
	};
	
#pragma endregion
}

#endif
