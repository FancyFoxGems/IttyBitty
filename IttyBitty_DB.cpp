/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_DB)
	#define EXCLUDE_ITTYBITTY_DB
#endif

#ifndef EXCLUDE_ITTYBITTY_DB


#include "IttyBitty_DB.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE DEFINITION

PBYTE IttyBitty::__database_buffer = NULL;

#pragma endregion


#pragma region [DataBase] IMPLEMENTATION
/*		
// STATIC FUNCTIONS
		
STATIC PDATABASE Database::Open(RCISTORAGE, RCSTORAGELOCATION)
{
	PDATABASE database = NULL;

	return database;
}

STATIC PDATABASE Database::Create(RCISTORAGE, RCSTORAGELOCATION)
{
	PDATABASE database = NULL;

	return database;
}

STATIC CDBRESULT Database::Delete(RCISTORAGE, RCSTORAGELOCATION)
{
	return DbResult::SUCCESS;
}

		
// CONSTRUCTOR
		
Database::Database(RCSTORAGELOCATION)
{
}

		
// PROTECTED DISPOSAL METHOD

VOID Database::Dispose()
{
}

		
// OPERATORS

PCIDBTABLE operator[]Database::(CBYTE) const
{
}

PIDBTABLE operator[]Database::(CBYTE)
{
}


// USER METHODS
		
CDWORD Database::Size() const
{
}

CWORD Database::Capacity() const
{
}
		
CBYTE Database::TableCount() const
{
}
		
RCIDBTABLE Database::Table(CBYTE) const
{
}

RIDBTABLE Database::Table(CBYTE)
{
}

RCIDBTABLE Database::Table(PCCHAR) const
{
}

RIDBTABLE Database::Table(PCCHAR)
{
}
		
CDWORD Database::SizeOf(CBYTE) const
{
}

CDWORD Database::SizeOf(PCCHAR) const
{
}

CDWORD Database::CapacityOf(CBYTE) const
{
}

CDWORD Database::CapacityOf(PCCHAR) const
{
}

CSIZE Database::RowCountFor(CBYTE) const
{
}

CSIZE Database::RowCountFor(PCCHAR) const
{
}

CSIZE Database::RowsAvailableFor(CBYTE) const
{
}

CSIZE Database::RowsAvailableFor(RCISTORAGE) const
{
}

CDBRESULT Database::CreateDatabase(RCISTORAGE)
{
}

CDBRESULT Database::DeleteDatabase(RCISTORAGE)
{
}
		
CDBRESULT Database::LoadDatabase(RCISTORAGE)
{
}

CDBRESULT Database::SaveDatabase(RCISTORAGE)
{
}

CDBRESULT Database::GrowDatabase(CDWORD, CBOOL)
{
}

CDBRESULT Database::ShrinkDatabase(CDWORD, CBOOL)
{
}

CDBRESULT Database::TruncateDatabase()
{
}

CDBRESULT Database::WipeDatabase()
{
}

CDBRESULT Database::CreateTable(CSIZE, PCCHAR)
{
}

CDBRESULT Database::GrowTable(CBYTE, CDWORD, CBOOL)
{
}

CDBRESULT Database::GrowTable(PCCHAR, CDWORD, CBOOL)
{
}

CDBRESULT Database::ShrinkTable(CBYTE, CDWORD, CBOOL)
{
}

CDBRESULT Database::ShrinkTable(PCCHAR, CDWORD, CBOOL)
{
}

CDBRESULT Database::DropTable(CBYTE)
{
}

CDBRESULT Database::DropTable(PCCHAR)
{
}

CDBRESULT Database::SelectAllFrom(CBYTE, PBYTE &, RSIZE)
{
}

CDBRESULT Database::SelectAllFrom(PCCHAR, PBYTE &, RSIZE)
{
}

CDBRESULT Database::FindFrom(CBYTE, CSIZE, PBYTE, PSIZE)
{
}

CDBRESULT Database::FindFrom(PCCHAR, CSIZE, PBYTE, PSIZE)
{
}

CDBRESULT Database::InsertInto(CBYTE, PCBYTE, CSIZE)
{
}

CDBRESULT Database::InsertInto(PCCHAR, PCBYTE, CSIZE)
{
}


CDBRESULT Database::UpdateTo(CBYTE, PCBYTE, CSIZE, PSIZE)
{
}

CDBRESULT Database::UpdateTo(PCCHAR, PCBYTE, CSIZE, PSIZE)
{
}

CDBRESULT Database::DeleteFrom(CBYTE, CSIZE)
{
}

CDBRESULT Database::DeleteFrom(PCCHAR, CSIZE)
{
}

CDBRESULT Database::TruncateFrom(CBYTE)
{
}

CDBRESULT Database::TruncateFrom(PCCHAR)
{
}
				

// [IStorable] IMPLEMENTATION

STORAGERESULT Database::SaveAsBinary(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT Database::SaveAsString(RCISTORAGE storage) const
{
	return StorageResult::SUCCESS;
}

STORAGERESULT Database::LoadFromBinary(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}

STORAGERESULT Database::LoadFromString(RCISTORAGE storage)
{
	return StorageResult::SUCCESS;
}


// [ISerializable] IMPLEMENTATION

CSIZE Database::BinarySize() const
{
}

CSIZE Database::StringSize() const
{
}

PCBYTE Database::ToBinary() const
{
}

PCCHAR Database::ToString() const
{
}

VOID Database::FromBinary(PCBYTE data)
{
}

VOID Database::FromString(PCCHAR data)
{
}
		
#ifdef ARDUINO

SIZE Database::printTo(Print & printer) const
{
}

#endif
				

// [IDbTableSet] IMPLEMENTATION
		
CBYTE Database::TableDefCount() const
{
}
		
RCIDBTABLEDEF Database::TableDef(CBYTE) const
{
}

RIDBTABLEDEF Database::TableDef(CBYTE)
{
}

RCIDBTABLEDEF Database::TableDef(PCCHAR) const
{
}

RIDBTABLEDEF Database::TableDef(PCCHAR)
{
}

		
// [IDbTableSet] HELPER METHODS

CSIZE Database::TableDefsByteSize() const
{
}

CSIZE Database::TableDefsStringSize() const
{
}
*/
#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB
