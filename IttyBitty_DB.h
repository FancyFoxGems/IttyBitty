/***********************************************************************************************
* [IttyBitty_DB.h]: STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_DB_H
#define ITTYBITTY_DB_H


#include "IttyBitty_DB_tables.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS
		
	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __database_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class Database;
	typedef Database DATABASE, * PDATABASE, & RDATABASE, ** PPDATABASE, && RRDATABASE;
	typedef const Database CDATABASE, * PCDATABASE, & RCDATABASE, ** PPCDATABASE;

#pragma endregion


#pragma region [Database] DEFINITION

	CLASS Database final : protected IDbTableSet
	{
	public:
		
		// STATIC FUNCTIONS
		
		STATIC PDATABASE Open(RCISTORAGE, RCSTORAGELOCATION);
		STATIC PDATABASE Create(RCISTORAGE, RCSTORAGELOCATION);
		STATIC CDBRESULT Delete(RCISTORAGE, RCSTORAGELOCATION);

		
		// CONSTRUCTOR
		
		Database(RCSTORAGELOCATION);


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		
		// OPERATORS

		PCIDBTABLE operator[](CBYTE) const;
		PIDBTABLE operator[](CBYTE);


		// USER METHODS
		
		CDWORD Size() const;
		CWORD Capacity() const;
		
		CBYTE TableCount() const;
		
		RCIDBTABLE Table(CBYTE = 0) const;
		RIDBTABLE Table(CBYTE = 0);

		RCIDBTABLE Table(PCCHAR) const;
		RIDBTABLE Table(PCCHAR);
		
		CDWORD SizeOf(CBYTE) const;
		CDWORD SizeOf(PCCHAR) const;

		CDWORD CapacityOf(CBYTE) const;
		CDWORD CapacityOf(PCCHAR) const;

		CSIZE RowCountFor(CBYTE) const;
		CSIZE RowCountFor(PCCHAR) const;

		CSIZE RowsAvailableFor(CBYTE) const;
		CSIZE RowsAvailableFor(RCISTORAGE) const;

		CDBRESULT CreateDatabase(RCISTORAGE);
		CDBRESULT DeleteDatabase(RCISTORAGE);
		
		CDBRESULT LoadDatabase(RCISTORAGE);
		CDBRESULT SaveDatabase(RCISTORAGE);

		CDBRESULT GrowDatabase(CDWORD, CBOOL = FALSE);
		CDBRESULT ShrinkDatabase(CDWORD, CBOOL = FALSE);
		CDBRESULT TruncateDatabase();
		CDBRESULT WipeDatabase();

		CDBRESULT CreateTable(CSIZE, PCCHAR = NULL);

		template<typename T>
		CDBRESULT CreateTable(PCCHAR = NULL)
		{
			return DbResult::SUCCESS;
		}

		CDBRESULT GrowTable(CBYTE, CDWORD, CBOOL = FALSE);
		CDBRESULT GrowTable(PCCHAR, CDWORD, CBOOL = FALSE);

		CDBRESULT ShrinkTable(CBYTE, CDWORD, CBOOL = FALSE);
		CDBRESULT ShrinkTable(PCCHAR, CDWORD, CBOOL = FALSE);

		CDBRESULT DropTable(CBYTE);
		CDBRESULT DropTable(PCCHAR);

		CDBRESULT SelectAllFrom(CBYTE, PBYTE &, RSIZE);
		CDBRESULT SelectAllFrom(PCCHAR, PBYTE &, RSIZE);

		template<typename T>
		CDBRESULT SelectAllFrom(CBYTE tableIndex, T *& resultSet, RSIZE rowCount)
		{
			return DbResult::SUCCESS;
		}
		
		template<typename T>
		CDBRESULT SelectAllFrom(PCCHAR tableName, T *& resultSet, RSIZE rowCount)
		{
			return DbResult::SUCCESS;
		}

		CDBRESULT FindFrom(CBYTE, CSIZE, PBYTE, PSIZE = NULL);
		CDBRESULT FindFrom(PCCHAR, CSIZE, PBYTE, PSIZE = NULL);

		template<typename T>
		CDBRESULT FindFrom(CBYTE tableIndex, CSIZE rowIndex, T & result)
		{
			return DbResult::SUCCESS;
		}
		
		template<typename T>
		CDBRESULT FindFrom(PCCHAR tableName, CSIZE rowIndex, T & result)
		{
			return DbResult::SUCCESS;
		}

		CDBRESULT InsertInto(CBYTE, PCBYTE, CSIZE = MAX_T(SIZE));
		CDBRESULT InsertInto(PCCHAR, PCBYTE, CSIZE = MAX_T(SIZE));

		CDBRESULT UpdateTo(CBYTE, PCBYTE, CSIZE, PSIZE = NULL);
		CDBRESULT UpdateTo(PCCHAR, PCBYTE, CSIZE, PSIZE = NULL);

		CDBRESULT DeleteFrom(CBYTE, CSIZE);
		CDBRESULT DeleteFrom(PCCHAR, CSIZE);

		CDBRESULT TruncateFrom(CBYTE);
		CDBRESULT TruncateFrom(PCCHAR);
				

		// [IStorable] IMPLEMENTATION

		VIRTUAL STORAGERESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL STORAGERESULT SaveAsString(RCISTORAGE) const;

		VIRTUAL STORAGERESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL STORAGERESULT LoadFromString(RCISTORAGE);


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

		friend class DbTableSet;
		friend class DbTableDef;

		
		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		PCSTORAGELOCATION _StorageLocation = NULL;
		PIDBTABLESET _DatabaseDef = NULL;
		PPIDBTABLE _Tables = NULL;
				

		// [IDbTableSet] IMPLEMENTATION
		
		VIRTUAL CBYTE TableDefCount() const;
		
		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR);

		
		// [IDbTableSet] HELPER METHODS

		VIRTUAL CSIZE TableDefsByteSize() const;
		VIRTUAL CSIZE TableDefsStringSize() const;
	};

#pragma endregion
}

#endif
