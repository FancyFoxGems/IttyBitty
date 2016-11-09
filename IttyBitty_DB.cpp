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


#pragma region [DataBase] IMPLEMENTATION
/*		
// STATIC FUNCTIONS
		
STATIC PDATABASE Database::Open(RCISTORAGE, RCSTORAGELOCATION)
{
}

STATIC PDATABASE Database::Create(RCISTORAGE, RCSTORAGELOCATION)
{
}

STATIC CDBRESULT Database::Delete(RCISTORAGE, RCSTORAGELOCATION)
{
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
		
CBYTE Database::GetTableCount() const
{
}
		
RCIDBTABLE Database::Table(CBYTE = 0) const
{
}

RIDBTABLE Database::Table(CBYTE = 0)
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

CDBRESULT Database::GrowDatabase(CDWORD, CBOOL = FALSE)
{
}

CDBRESULT Database::ShrinkDatabase(CDWORD, CBOOL = FALSE)
{
}

CDBRESULT Database::TruncateDatabase()
{
}

CDBRESULT Database::WipeDatabase()
{
}

CDBRESULT Database::CreateTable(CSIZE, PCCHAR = NULL)
{
}

CDBRESULT Database::GrowTable(CBYTE, CDWORD, CBOOL = FALSE)
{
}

CDBRESULT Database::GrowTable(PCCHAR, CDWORD, CBOOL = FALSE)
{
}

CDBRESULT Database::ShrinkTable(CBYTE, CDWORD, CBOOL = FALSE)
{
}

CDBRESULT Database::ShrinkTable(PCCHAR, CDWORD, CBOOL = FALSE)
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

CDBRESULT Database::FindFrom(CBYTE, CSIZE, PBYTE, PSIZE = NULL)
{
}

CDBRESULT Database::FindFrom(PCCHAR, CSIZE, PBYTE, PSIZE = NULL)
{
}

CDBRESULT Database::InsertInto(CBYTE, PCBYTE, CSIZE = MAX_Database::T(SIZE))
{
}

CDBRESULT Database::InsertInto(PCCHAR, PCBYTE, CSIZE = MAX_Database::T(SIZE))
{
}


CDBRESULT Database::UpdateTo(CBYTE, PCBYTE, CSIZE, PSIZE = NULL)
{
}

CDBRESULT Database::UpdateTo(PCCHAR, PCBYTE, CSIZE, PSIZE = NULL)
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

MEDIARESULT Database::SaveAsBinary(RCISTORAGE) const
{
}

MEDIARESULT Database::SaveAstring(RCISTORAGE) const
{
}

MEDIARESULT Database::LoadFromBinary(RCISTORAGE)
{
}

MEDIARESULT Database::LoadFromString(RCISTORAGE)
{
}


// [ISerializable] IMPLEMENTATION

CSIZE Database::BinarySize() const
{
}

CSIZE Database::StringSize() const
{
}

CSIZE Database::ByteWidth() const
{
}

CSIZE Database::StringLength() const
{
}

PCBYTE Database::ToBinary() const
{
}

PCCHAR Database::ToString() const
{
}

VOID Database::FromBinary(PCBYTE)
{
}

VOID Database::FromString(PCCHAR)
{
}
		
#ifdef ARDUINO

SIZE Database::printTo(Print &) const
{
}

#endif
				

// [IDbTableSet] IMPLEMENTATION
		
CBYTE Database::GetTableDefCount() const
{
}
		
RCIDBTABLEDEF Database::TableDef(CBYTE = 0) const
{
}

RIDBTABLEDEF Database::TableDef(CBYTE = 0)
{
}

RCIDBTABLEDEF Database::TableDef(PCCHAR) const
{
}

RIDBTABLEDEF Database::TableDef(PCCHAR)
{
}

		
// [IDbTableSet] HELPER METHODS

CSIZE Database::GetTableDefsByteSize() const
{
}

CSIZE Database::GetTableDefsStringSize() const
{
}
*/
#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB
