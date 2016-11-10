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

		PCIDBTABLE operator[](CBYTE) const;
		PIDBTABLE operator[](CBYTE);


		// ACCESSORS

		RCISTORAGE GetStorage() const;


		// MUTATORS

		VOID SetStorage(RCISTORAGE);


		// USER METHODS

		CDBRESULT CreateDatabase();
		CDBRESULT DeleteDatabase();

		CDBRESULT GrowDatabase(RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);
		CDBRESULT CompressDatabase(RCFLOAT = 0.0F);
		CDBRESULT TruncateAllTables();
		CDBRESULT WipeDatabase();

		CDBRESULT Load();
		CDBRESULT Save();


		// [IDbTableSet] IMPLEMENTATION

		VIRTUAL CDWORD Size() const;
		VIRTUAL CWORD Capacity() const;

		VIRTUAL CBYTE TableCount() const;

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
		VIRTUAL CSIZE RowsAvailableFor() const;

		VIRTUAL CDBRESULT CreateTable(CSIZE, PCCHAR = NULL);

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
		CDBRESULT SelectAllFrom(CBYTE tableIndex, T *& resultSet, RSIZE resultCount)
		{
			PIDBTABLE table = this->Table(tableIndex);

			return table->SelectAllRows(reinterpret_cast<PBYTE &>(resultSet), resultCount);
		}

		template<typename T>
		CDBRESULT SelectAllFrom(PCCHAR tableName, T *& resultSet, RSIZE resultCount)
		{
			PIDBTABLE table = this->Table(tableName);

			return table->SelectAllRows(reinterpret_cast<PBYTE &>(resultSet), resultCount);
		}

		VIRTUAL CDBRESULT FindFrom(CBYTE, CSIZE, PBYTE, PSIZE = NULL);
		VIRTUAL CDBRESULT FindFrom(PCCHAR, CSIZE, PBYTE, PSIZE = NULL);

		template<typename T>
		CDBRESULT FindFrom(CBYTE tableIndex, CSIZE rowIndex, T * result)
		{
			PIDBTABLE table = this->Table(tableIndex);

			return table->FindRow(rowIndex, reinterpret_cast<PBYTE>(result));
		}

		template<typename T>
		CDBRESULT FindFrom(PCCHAR tableName, CSIZE rowIndex, T * result)
		{
			PIDBTABLE table = this->Table(tableName);

			return table->FindRow(rowIndex, reinterpret_cast<PBYTE>(result));
		}

		VIRTUAL CDBRESULT InsertInto(CBYTE, PCBYTE, CSIZE = MAX_T(SIZE));
		VIRTUAL CDBRESULT InsertInto(PCCHAR, PCBYTE, CSIZE = MAX_T(SIZE));

		VIRTUAL CDBRESULT UpdateTo(CBYTE, PCBYTE, CSIZE, PSIZE = NULL);
		VIRTUAL CDBRESULT UpdateTo(PCCHAR, PCBYTE, CSIZE, PSIZE = NULL);

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

		VIRTUAL CSTORAGERESULT MoveTables(CBYTE, RCLONG);


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
