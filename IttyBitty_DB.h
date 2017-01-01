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

	TYPEDEF_CLASS_ALIASES(Database, DATABASE);

#pragma endregion


#pragma region [Database] DEFINITION

	CLASS Database : public IDbTableSet
	{
	public:

		// STATIC FUNCTIONS

		STATIC PDATABASE Load(RISTORAGE, RDBRESULT);
		STATIC PDATABASE Create(RISTORAGE, RDBRESULT);
		STATIC CDBRESULT Delete(RISTORAGE);


		// CONSTRUCTORS/DESTRUCTOR

		Database(RISTORAGE = IttyBitty::NULL_STORAGE());

		EXPLICIT Database(PCBYTE, RISTORAGE = IttyBitty::NULL_STORAGE());
		EXPLICIT Database(PCCHAR, RISTORAGE = IttyBitty::NULL_STORAGE());

		VIRTUAL ~Database();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose(CBOOL forceDispose = FALSE);


	public:

		// OPERATORS

		VIRTUAL PCIDBTABLE operator[](CBYTE) const;
		VIRTUAL PIDBTABLE operator[](CBYTE);

		VIRTUAL PCIDBTABLE operator[](PCCHAR) const;
		VIRTUAL PIDBTABLE operator[](PCCHAR);


		// ACCESSORS

		VIRTUAL RISTORAGE GetStorage() const;


		// MUTATORS

		VIRTUAL VOID SetStorage(RISTORAGE);


		// USER METHODS

		CDBRESULT Create();
		CDBRESULT Delete();


		// [IDbTableSet] IMPLEMENTATION

		VIRTUAL CDWORD Size() const;
		VIRTUAL CWORD Capacity() const;

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

		VIRTUAL CDBRESULT CreateTable(CSIZE, PCCHAR = NULL, CSIZE = DB_DEFAULT_INITIAL_ROWS_ALLOCATION, CBYTE = MAX_BYTE);

		VIRTUAL CDBRESULT DropTable(CBYTE);
		VIRTUAL CDBRESULT DropTable(PCCHAR);

		VIRTUAL CDBRESULT GrowTable(CBYTE, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);
		VIRTUAL CDBRESULT GrowTable(PCCHAR, RCFLOAT = DB_DEFAULT_GROWTH_FACTOR);

		VIRTUAL CDBRESULT CompressTable(CBYTE, RCFLOAT = 0.0F);
		VIRTUAL CDBRESULT CompressTable(PCCHAR, RCFLOAT = 0.0F);

		VIRTUAL CDBRESULT SelectAllFrom(CBYTE, PBYTE &, RSIZE, PSIZE);
		VIRTUAL CDBRESULT SelectAllFrom(PCCHAR, PBYTE &, RSIZE, PSIZE);

		VIRTUAL CDBRESULT FindFrom(CBYTE, CSIZE, PBYTE &, PSIZE);
		VIRTUAL CDBRESULT FindFrom(PCCHAR, CSIZE, PBYTE &, PSIZE);

		VIRTUAL CDBRESULT InsertInto(CBYTE, PCBYTE, CSIZE = MAX_VALUE(SIZE));
		VIRTUAL CDBRESULT InsertInto(PCCHAR, PCBYTE, CSIZE = MAX_VALUE(SIZE));

		VIRTUAL CDBRESULT UpdateTo(CBYTE, PCBYTE, CSIZE);
		VIRTUAL CDBRESULT UpdateTo(PCCHAR, PCBYTE, CSIZE);

		VIRTUAL CDBRESULT DeleteFrom(CBYTE, CSIZE);
		VIRTUAL CDBRESULT DeleteFrom(PCCHAR, CSIZE);

		VIRTUAL CDBRESULT TruncateTable(CBYTE);
		VIRTUAL CDBRESULT TruncateTable(PCCHAR);


		// [IStorable] IMPLEMENTATION

		VIRTUAL CSTORAGERESULT Save();
		VIRTUAL CSTORAGERESULT Load();

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

		VIRTUAL VOID FreeBuffer() const;

	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


	protected:


		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		RISTORAGE _Storage = IttyBitty::NULL_STORAGE();

		BYTE _TableCount = 0;
		PPIDBTABLE _Tables = NULL;


		// [IDbTableSet] HELPER METHODS

		VIRTUAL CDBRESULT MoveTableData(RCDWORD, RCLONG, CBOOL = TRUE);
		VIRTUAL CDBRESULT MoveTableDefinition(CWORD, CSHORT, CBOOL = TRUE);

		VIRTUAL CDWORD TablesSize() const;
		VIRTUAL CDWORD TablesCapacity() const;

		VIRTUAL CSIZE TablesBinarySize() const;
		VIRTUAL CSIZE TablesStringSize() const;


		// [IDbTableDefSet] IMPLEMENTATION

		VIRTUAL CBYTE TableDefCount() const;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR);


		// [IDbTableDefSet] HELPER METHODS

		VIRTUAL CSIZE TableDefsBinarySize() const;
		VIRTUAL CSIZE TableDefsStringSize() const;
	};

#pragma endregion
}

#endif
