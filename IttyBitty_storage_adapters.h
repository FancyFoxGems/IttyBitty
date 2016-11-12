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

	class MemoryResidentStorageAdapter;
	TYPEDEF_CLASS_ALIASES(MemoryResidentStorageAdapter, MEMORYRESIDENTSTORAGEADAPTER);

	class FlashRomStorageAdapter;
	TYPEDEF_CLASS_ALIASES(FlashRomStorageAdapter, FLASHROMSTORAGEADAPTER);

	class EepromStorageAdapter;
	TYPEDEF_CLASS_ALIASES(EepromStorageAdapter, EEPROMSTORAGEADAPTER);

	class ExtEepromStorageAdapter;
	TYPEDEF_CLASS_ALIASES(ExtEepromStorageAdapter, EXTEEPROMSTORAGEADAPTER);

	class SdStorageAdapter;
	TYPEDEF_CLASS_ALIASES(SdStorageAdapter, SDSTORAGEADAPTER);

#pragma endregion


#pragma region [MemoryResidentStorageAdapter] DEFINITION

	CLASS MemoryResidentStorageAdapter
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MemoryResidentStorageAdapter();

		~MemoryResidentStorageAdapter();


		// [IStorage] IMPLEMENTATION

		VIRTUAL CBOOL Available();

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE);

		VIRTUAL CSTORAGERESULT Seek(RCDWORD);

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE);

		VIRTUAL CSTORAGERESULT Flush();

		VIRTUAL CSTORAGERESULT Close();
	};

#pragma endregion


#pragma region [FlashRomStorageAdapter] DEFINITION

	CLASS FlashRomStorageAdapter
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		FlashRomStorageAdapter();

		~FlashRomStorageAdapter();


		// [IStorage] IMPLEMENTATION

		VIRTUAL CBOOL Available();

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE);

		VIRTUAL CSTORAGERESULT Seek(RCDWORD);

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE);

		VIRTUAL CSTORAGERESULT Flush();

		VIRTUAL CSTORAGERESULT Close();
	};

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
