/***********************************************************************************************
* [IttyBitty_storage_adapters.h]: LONG-TERM DATA STORAGE IMPLEMENTATIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_STORAGE_ADAPTERS_H
#define _ITTYBITTY_STORAGE_ADAPTERS_H


#include "IttyBitty_storage.h"
#include "IttyBitty_EEPROM_I2C.h"


//#include "SD.h"


#pragma region DEFINES



#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class EepromStorageAdapter;
	typedef EepromStorageAdapter EEPROMSTORAGEADAPTER, * PEEPROMSTORAGEADAPTER,
		& REEPROMSTORAGEADAPTER, ** PPEEPROMSTORAGEADAPTER, && RREEPROMSTORAGEADAPTER;
	typedef const EepromStorageAdapter CEEPROMSTORAGEADAPTER, * PCEEPROMSTORAGEADAPTER,
		& RCEEPROMSTORAGEADAPTER, ** PPCEEPROMSTORAGEADAPTER;

	class ExtEepromStorageAdapter;
	typedef ExtEepromStorageAdapter EXTEEPROMSTORAGEADAPTER, * PEXTEEPROMSTORAGEADAPTER,
		& REXTEEPROMSTORAGEADAPTER, ** PPEXTEEPROMSTORAGEADAPTER, && RREXTEEPROMSTORAGEADAPTER;
	typedef const ExtEepromStorageAdapter CEXTEEPROMSTORAGEADAPTER, * PCEXTEEPROMSTORAGEADAPTER,
		& RCEXTEEPROMSTORAGEADAPTER, ** PPCEXTEEPROMSTORAGEADAPTER;

	class SdStorageAdapter;
	typedef SdStorageAdapter SDSTORAGEADAPTER, * PSDSTORAGEADAPTER,
		& RSDSTORAGEADAPTER, ** PPSDSTORAGEADAPTER, && RRSDSTORAGEADAPTER;
	typedef const SdStorageAdapter CSDSTORAGEADAPTER, * PCSDSTORAGEADAPTER,
		& RCSDSTORAGEADAPTER, ** PPCSDSTORAGEADAPTER;

#pragma endregion
}

#endif
