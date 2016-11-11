/***********************************************************************************************
* [IttyBitty_DB.h]: STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_DB_H
#define _ITTYBITTY_DB_H


#include "IttyBitty_DB_tables.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __database_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	typedef Database DATABASE, * PDATABASE, & RDATABASE, ** PPDATABASE, && RRDATABASE;
	typedef const Database CDATABASE, * PCDATABASE, & RCDATABASE, ** PPCDATABASE;

#pragma endregion


#pragma region [Database] DEFINITION

	CLASS Database final : public IDbTableSet
	{
	public:

		// STATIC FUNCTIONS

		STATIC PDATABASE Load(RCISTORAGE, RDBRESULT);
		STATIC PDATABASE Create(RCISTORAGE, RDBRESULT);
		STATIC CDBRESULT Delete(RCISTORAGE);


		// CONSTRUCTOR

		Database(RCISTORAGE);


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// OPERATORS

		VIRTUAL PCIDBTABLE operator[](CBYTE) const;
		VIRTUAL PIDBTABLE operator[](CBYTE);


		// ACCESSORS

		RCISTORAGE GetStorage() const;


		// MUTATORS

		VOID SetStorage(RCISTORAGE);


		// USER METHODS

		CDBRESULT Create();
		CDBRESULT Delete();

		CDBRESULT Load();
		CDBRESULT Save();


		// [IDbTableSet] IMPLEMENTATION

		VIRTUAL CDWORD Size() const;
		VIRTUAL CWORD Capacity() const;

		VIRTUAL CDBRESULT Grow(RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);
		VIRTUAL CDBRESULT Compress(RCFLOAT = 0.0F);

		VIRTUAL CBYTE TableCount() const;

		VIRTUAL CDBRESULT TruncateAllTables();
		VIRTUAL CDBRESULT DropAllTables();

		VIRTUAL RCIDBTABLE Table(CBYTE = 0) const;
		VIRTUAL RIDBTABLE Table(CBYTE = 0);

		VIRTUAL RCIDBTABLE Table(PCCHAR) const;
		VIRTUAL RIDBTABLE Table(PCCHAR);

		VIRTUAL CDWORD SizeOf(CBYTE) const;
		VIRTUAL CDWORD SizeOf(PCCHAR) const;

		VIRTUAL CDWORD CapacityOf(CBYTE) const;
		VIRTUAL CDWORD CapacityOf(PCCHAR) const;

		VIRTUAL CSIZE RowCountFor(CBYTE) const;
		VIRTUAL CSIZE RowCountFor(PCCHAR) const;

		VIRTUAL CSIZE RowsAvailableFor(CBYTE) const;
		VIRTUAL CSIZE RowsAvailableFor(PCCHAR) const;

		VIRTUAL CDBRESULT CreateTable(CSIZE, PCCHAR = NULL, CBYTE = MAX_T(BYTE));

		template<typename T>
		CDBRESULT CreateTable(PCCHAR = NULL)
		{
			return DbResult::SUCCESS;
		}

		VIRTUAL CDBRESULT GrowTable(CBYTE, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);
		VIRTUAL CDBRESULT GrowTable(PCCHAR, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);

		VIRTUAL CDBRESULT CompressTable(CBYTE, RCFLOAT = 0.0F);
		VIRTUAL CDBRESULT CompressTable(PCCHAR, RCFLOAT = 0.0F);

		VIRTUAL CDBRESULT DropTable(CBYTE);
		VIRTUAL CDBRESULT DropTable(PCCHAR);

		VIRTUAL CDBRESULT SelectAllFrom(CBYTE, PBYTE &, RSIZE);
		VIRTUAL CDBRESULT SelectAllFrom(PCCHAR, PBYTE &, RSIZE);

		template<typename T>
		CDBRESULT SelectAllFrom(CBYTE tableIdx, T *& recordSet, RSIZE recordCount)
		{
			PIDBTABLE table = this->Table(tableIdx);

			return table->SelectAll(reinterpret_cast<PBYTE &>(recordSet), recordCount);
		}

		template<typename T>
		CDBRESULT SelectAllFrom(PCCHAR tableName, T *& recordSet, RSIZE recordCount)
		{
			PIDBTABLE table = this->Table(tableName);

			return table->SelectAll(reinterpret_cast<PBYTE &>(recordSet), recordCount);
		}

		VIRTUAL CDBRESULT FindFrom(CBYTE, CSIZE, PBYTE, PSIZE);
		VIRTUAL CDBRESULT FindFrom(PCCHAR, CSIZE, PBYTE, PSIZE);

		template<typename T>
		CDBRESULT FindFrom(CBYTE tableIdx, CSIZE rowIdx, T * record)
		{
			PIDBTABLE table = this->Table(tableIdx);

			return table->Find(rowIdx, reinterpret_cast<PBYTE>(record));
		}

		template<typename T>
		CDBRESULT FindFrom(PCCHAR tableName, CSIZE rowIdx, T * record)
		{
			PIDBTABLE table = this->Table(tableName);

			return table->Find(rowIdx, reinterpret_cast<PBYTE>(record));
		}

		VIRTUAL CDBRESULT InsertInto(CBYTE, PCBYTE, CSIZE = MAX_T(SIZE));
		VIRTUAL CDBRESULT InsertInto(PCCHAR, PCBYTE, CSIZE = MAX_T(SIZE));

		template<typename T>
		CDBRESULT InsertInto(CBYTE tableIdx, CONST T & rowData, CSIZE insertIdx = MAX_T(SIZE))
		{
			PIDBTABLE table = this->Table(tableIdx);

			return table->Insert(reinterpret_cast<PCBYTE>(rowData), insertIdx);
		}

		template<typename T>
		CDBRESULT InsertInto(PCCHAR tableName, CONST T & rowData, CSIZE insertIdx = MAX_T(SIZE))
		{
			PIDBTABLE table = this->Table(tableName);

			return table->Insert(reinterpret_cast<PCBYTE>(rowData), insertIdx);
		}

		VIRTUAL CDBRESULT UpdateTo(CBYTE, CSIZE, PCBYTE);
		VIRTUAL CDBRESULT UpdateTo(PCCHAR, CSIZE, PCBYTE);

		template<typename T>
		CDBRESULT UpdateTo(CBYTE tableIdx, CSIZE rowIdx, CONST T & rowData)
		{
			PIDBTABLE table = this->Table(tableIdx);

			return table->Update(rowIdx, reinterpret_cast<PCBYTE>(rowData));
		}

		template<typename T>
		CDBRESULT UpdateTo(PCCHAR tableName, CSIZE rowIdx, CONST T & rowData)
		{
			PIDBTABLE table = this->Table(tableName);

			return table->Update(rowIdx, reinterpret_cast<PCBYTE>(rowData));
		}

		VIRTUAL CDBRESULT DeleteFrom(CBYTE, CSIZE);
		VIRTUAL CDBRESULT DeleteFrom(PCCHAR, CSIZE);

		VIRTUAL CDBRESULT TruncateTable(CBYTE);
		VIRTUAL CDBRESULT TruncateTable(PCCHAR);


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

		friend class DbTableDefSet;
		friend class DbTable;
		friend class DbTableDef;


		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		PISTORAGE _Storage = NULL;

		PIDBTABLEDEFSET _DatabaseDef = NULL;
		PPIDBTABLE _Tables = NULL;


		// [IDbTableSet] HELPER METHODS

		VIRTUAL CSTORAGERESULT MoveTables(CSIZE, RCLONG);


		// [IDbTableDefSet] IMPLEMENTATION

		VIRTUAL CBYTE TableDefCount() const;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR);


		// [IDbTableDefSet] HELPER METHODS

		VIRTUAL CSIZE TableDefsByteSize() const;
		VIRTUAL CSIZE TableDefsStringSize() const;
	};

#pragma endregion
}

#endif
