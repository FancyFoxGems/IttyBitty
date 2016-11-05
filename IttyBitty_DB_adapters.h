/***********************************************************************************************
* [IttyBitty_DB_storage.h]: STRUCTURED DATA STORAGE ADAPTERS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_DB_STORAGE_H
#define ITTYBITTY_DB_STORAGE_H


#include "IttyBitty_DB.h"
#include "IttyBitty_EEPROM_I2C.h"


//#include "SD.h"


#pragma region DEFINES



#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class DbStorageBase;
	typedef DbStorageBase DBSTORAGEBASE, * PDBSTORAGEBASE, & RDBSTORAGEBASE, ** PPDBSTORAGEBASE, && RRDBSTORAGEBASE;
	typedef const DbStorageBase CDBSTORAGEBASE, * PCDBSTORAGEBASE, & RCDBSTORAGEBASE, ** PPCDBSTORAGEBASE;

	class DbStorageAdapter;
	typedef DbStorageAdapter DBSTORAGEADAPTER, * PDBSTORAGEADAPTER, & RDBSTORAGEADAPTER, ** PPDBSTORAGEADAPTER, && RRDBSTORAGEADAPTER;
	typedef const DbStorageAdapter CDBSTORAGEADAPTER, * PCDBSTORAGEADAPTER, & RCDBSTORAGEADAPTER, ** PPCDBSTORAGEADAPTER;

#pragma endregion


#pragma region [DbStorageBase] DEFINITION


#pragma endregion
}

#endif
