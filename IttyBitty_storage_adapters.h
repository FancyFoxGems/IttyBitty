/***********************************************************************************************
* [IttyBitty_storage_adapters.h]: LONG-TERM DATA STORAGE IMPLEMENTATIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_STORAGE_ADAPTERS_H
#define ITTYBITTY_STORAGE_ADAPTERS_H


#include "IttyBitty_storage.h"
#include "IttyBitty_EEPROM_I2C.h"


//#include "SD.h"


#pragma region DEFINES



#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class StorageAdapter;
	typedef StorageAdapter STORAGEADAPTER, * PSTORAGEADAPTER, & RSTORAGEADAPTER, ** PPSTORAGEADAPTER, && RRSTORAGEADAPTER;
	typedef const StorageAdapter CSTORAGEADAPTER, * PCSTORAGEADAPTER, & RCSTORAGEADAPTER, ** PPCSTORAGEADAPTER;

#pragma endregion


#pragma region [StorageBase] DEFINITION


#pragma endregion
}

#endif
