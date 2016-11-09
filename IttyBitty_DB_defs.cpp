/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (defined(ITTYBITTY_SLIM) || defined(EXCLUDE_ITTYBITTY_DB)) && !defined(EXCLUDE_ITTYBITTY_DB_DEFS)
	#define EXCLUDE_ITTYBITTY_DB_DEFS
#endif

#ifndef EXCLUDE_ITTYBITTY_DB_DEFS


#include "IttyBitty_DB_defs.h"

using namespace IttyBitty;


#pragma region [DbTableSet] IMPLEMENTATION
/*
DbTableSet::DbTableSet(CBYTE = 0)
{
}

DbTableSet::DbTableSet(PCBYTE)
{
}

DbTableSet::DbTableSet(PCCHAR)
{
}

DbTableSet::DbTableSet(RCIDBTABLEDEF)
{
}

DbTableSet::DbTableSet(CBYTE, PPIDBTABLEDEF)
{
}

DbTableSet::~DbTableSet()
{
}

		
// PROTECTED DISPOSAL METHOD

VOID DbTableSet::Dispose()
{
}

PCIDBTABLEDEF operator[]DbTableSet::(CBYTE) const
{
}

PIDBTABLEDEF operator[]DbTableSet::(CBYTE)
{
}
				

// [IDbTableSet] IMPLEMENTATION
		
CBYTE DbTableSet::GetTableDefCount() const
{
}
		
RCIDBTABLEDEF DbTableSet::TableDef(CBYTE = 0) const
{
}

RIDBTABLEDEF DbTableSet::TableDef(CBYTE = 0)
{
}

RCIDBTABLEDEF DbTableSet::TableDef(PCCHAR) const
{
}

RIDBTABLEDEF DbTableSet::TableDef(PCCHAR)
{
}
				

// [IStorable] IMPLEMENTATION

MEDIARESULT DbTableSet::SaveAsBinary(RCISTORAGE) const
{
}

MEDIARESULT DbTableSet::SaveAstring(RCISTORAGE) const
{
}

MEDIARESULT DbTableSet::LoadFromBinary(RCISTORAGE)
{
}

MEDIARESULT DbTableSet::LoadFromString(RCISTORAGE)
{
}
		

// [ISerializable] IMPLEMENTATION

CSIZE DbTableSet::BinarySize() const
{
}

CSIZE DbTableSet::StringSize() const
{
}

CSIZE DbTableSet::ByteWidth() const
{
}

CSIZE DbTableSet::StringLength() const
{
}

PCBYTE DbTableSet::ToBinary() const
{
}

PCCHAR DbTableSet::ToString() const
{
}

VOID DbTableSet::FromBinary(PCBYTE)
{
}

VOID DbTableSet::FromString(PCCHAR)
{
}
		
#ifdef ARDUINO		

SIZE DbTableSet::printTo(Print &) const
{
}

#endif

		
// [IDbTableSet] HELPER METHODS

CSIZE DbTableSet::GetTableDefsByteSize() const
{
}

CSIZE DbTableSet::GetTableDefsStringSize() const
{
}
*/
#pragma endregion


#pragma region [DbTableDef] IMPLEMENTATION
/*
// CONSTRUCTORS/DESTRUCTOR

DbTableDef::DbTableDef(CSIZE, PCCHAR = NULL, CDWORD = 0)
{
}

DbTableDef::DbTableDef(PCBYTE)
{
}
DbTableDef::DbTableDef(PCCHAR)
{
}

DbTableDef::~DbTableDef()
{
}
		
// PROTECTED DISPOSAL METHOD

VOID DbTableDef::Dispose()
{
}
		

// [IDbTableDef] IMPLEMENTATION
		
CSIZE DbTableDef::GetRowSize() const
{
}

DWORD DbTableDef::GetAddrOffset() const
{
}

PCCHAR DbTableDef::GetTableName() const
{
}
		
VOID DbTableDef::SetAddrOffset(CDWORD)
{
}

VOID DbTableDef::SetTableName(PCCHAR)
{
}
				

// [IStorable] IMPLEMENTATION

MEDIARESULT DbTableDef::SaveAsBinary(RCISTORAGE) const
{
}

MEDIARESULT DbTableDef::SaveAstring(RCISTORAGE) const
{
}

MEDIARESULT DbTableDef::LoadFromBinary(RCISTORAGE)
{
}

MEDIARESULT DbTableDef::LoadFromString(RCISTORAGE)
{
}


// [ISerializable] IMPLEMENTATION

CSIZE DbTableDef::BinarySize() const
{
}

CSIZE DbTableDef::StringSize() const
{
}

CSIZE DbTableDef::ByteWidth() const
{
}

CSIZE DbTableDef::StringLength() const
{
}

PCBYTE DbTableDef::ToBinary() const
{
}

PCCHAR DbTableDef::ToString() const
{
}

VOID DbTableDef::FromBinary(PCBYTE)
{
}

VOID DbTableDef::FromString(PCCHAR)
{
}
		
#ifdef ARDUINO		

SIZE DbTableDef::printTo(Print &) const
{
}

#endif
*/
#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB_DEFS
