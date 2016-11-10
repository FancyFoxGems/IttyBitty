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


#pragma region [EepromStorageAdapter] DEFINITION

	CLASS EepromStorageAdapter
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EepromStorageAdapter();

		~EepromStorageAdapter();


		// [IStorage] IMPLEMENTATION

		VIRTUAL CBOOL Available();

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE);

		VIRTUAL CSTORAGERESULT Seek(RCDWORD);

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE);

		VIRTUAL CSTORAGERESULT Flush();

		VIRTUAL CSTORAGERESULT Close();
	};

#pragma endregion


#pragma region [ExtEepromStorageAdapter] DEFINITION

	CLASS ExtEepromStorageAdapter
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ExtEepromStorageAdapter();

		~ExtEepromStorageAdapter();


		// [IStorage] IMPLEMENTATION

		VIRTUAL CBOOL Available();

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE);

		VIRTUAL CSTORAGERESULT Seek(RCDWORD);

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE);

		VIRTUAL CSTORAGERESULT Flush();

		VIRTUAL CSTORAGERESULT Close();
	};

#pragma endregion


#pragma region [SdStorageAdapter] DEFINITION

	CLASS SdStorageAdapter
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		SdStorageAdapter();

		~SdStorageAdapter();


		// [IStorage] IMPLEMENTATION

		VIRTUAL CBOOL Available();

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE);

		VIRTUAL CSTORAGERESULT Seek(RCDWORD);

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE);

		VIRTUAL CSTORAGERESULT Flush();

		VIRTUAL CSTORAGERESULT Close();
	};

#pragma endregion
};

#endif
