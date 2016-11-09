/***********************************************************************************************
* [IttyBitty_DB_tables.h]: TABLE DATA STRUCTURES FOR STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_DB_TABLES_H
#define ITTYBITTY_DB_TABLES_H


#include "IttyBitty_DB_defs.h"


#pragma region DEFINES

#define ITTYBITTY_DB_DEFAULT_GROWTH_FACTOR		2U

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

	class DbTable;
	typedef DbTable DBTABLE, * PDBTABLE, & RDBTABLE, ** PPDBTABLE, && RRDBTABLE;
	typedef const DbTable CDBTABLE, * PCDBTABLE, & RCDBTABLE, ** PPCDBTABLE;

	template<typename T>
	class TypedDbTable;
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

		VIRTUAL CDBRESULT Grow(CDWORD, CBOOL = FALSE) = 0;
		VIRTUAL CDBRESULT Shrink(CDWORD, CBOOL = FALSE);

		VIRTUAL CDBRESULT SelectAll(PBYTE &, RSIZE);
		VIRTUAL CDBRESULT Find(CSIZE, PBYTE, PSIZE = NULL) = 0;

		VIRTUAL CDBRESULT Insert(PCBYTE, CSIZE = MAX_T(SIZE)) = 0;
		VIRTUAL CDBRESULT Update(PCBYTE, CSIZE, PSIZE = NULL) = 0;
		VIRTUAL CDBRESULT Delete(CSIZE) = 0;
		VIRTUAL CDBRESULT Truncate() = 0;
		

	protected:

		IDbTable() { }
	};

#pragma endregion

	
#pragma region [DbTable] DEFINITION

	CLASS DbTable : public IDbTable
	{
	protected:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTable(CSIZE, PCCHAR = NULL, CDWORD = 0);

		EXPLICIT DbTable(PCBYTE);
		EXPLICIT DbTable(PCCHAR);

				
	public:

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

		VIRTUAL CDBRESULT Grow(CDWORD, CBOOL = FALSE);
		VIRTUAL CDBRESULT Shrink(CDWORD, CBOOL = FALSE);

		VIRTUAL CDBRESULT SelectAll(PBYTE &, RSIZE);

		template<typename T>
		CDBRESULT SelectAll(T *& resultSet, RSIZE rowCount)
		{
			return DbResult::SUCCESS;
		}

		VIRTUAL CDBRESULT Find(CSIZE, PBYTE, PSIZE = NULL);

		template<typename T>
		CDBRESULT Find(CSIZE rowIndex, T & result)
		{
			return DbResult::SUCCESS;
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

		VIRTUAL MEDIARESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL MEDIARESULT SaveAstring(RCISTORAGE) const;

		VIRTUAL MEDIARESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL MEDIARESULT LoadFromString(RCISTORAGE);


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

		// INSTANCE VARIABLES

		PIDBTABLEDEF _TableDef;
		DWORD _RowCount = 0;
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
	};
	
#pragma endregion
}

#endif
