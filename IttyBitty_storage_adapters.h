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

#ifdef ARDUINO
	#include "IttyBitty_EEPROM_I2C.h"
#endif


#pragma region DEFINES



#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class MemoryResidentStorageAdapter;
	TYPEDEF_CLASS_ALIASES(MemoryResidentStorageAdapter, MEMORYRESIDENTSTORAGEADAPTER);

	class FlashRomStorageAdapter;
	TYPEDEF_CLASS_ALIASES(FlashRomStorageAdapter, FLASHROMSTORAGEADAPTER);

#ifdef ARDUINO

	class EepromStorageAdapter;
	TYPEDEF_CLASS_ALIASES(EepromStorageAdapter, EEPROMSTORAGEADAPTER);

	class SdStorageAdapter;
	TYPEDEF_CLASS_ALIASES(SdStorageAdapter, SDSTORAGEADAPTER);

	class ExtEepromStorageAdapter;
	TYPEDEF_CLASS_ALIASES(ExtEepromStorageAdapter, EXTEEPROMSTORAGEADAPTER);

#endif  // #ifdef ARDUINO

#pragma endregion


#pragma region [MemoryResidentStorageAdapter] DEFINITION

	CLASS MemoryResidentStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		MemoryResidentStorageAdapter(CDWORD);


		// [IStorage] IMPLEMENTATION

		CBOOL Available();

		CSTORAGERESULT Open(CBOOL = FALSE);
		CSTORAGERESULT Close();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

		CSTORAGERESULT Flush();
	};

#pragma endregion


#pragma region [FlashRomStorageAdapter] DEFINITION

	CLASS FlashRomStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		FlashRomStorageAdapter(CDWORD);


		// [IStorage] IMPLEMENTATION

		CBOOL Available();

		CSTORAGERESULT Open(CBOOL = FALSE);
		CSTORAGERESULT Close();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

		CSTORAGERESULT Flush();
	};

#pragma endregion


#ifdef ARDUINO

#pragma region [EepromStorageAdapter] DEFINITION

	CLASS EepromStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		EepromStorageAdapter(CWORD);


		// [IStorage] IMPLEMENTATION

		CBOOL Available();

		CSTORAGERESULT Open(CBOOL = FALSE);
		CSTORAGERESULT Close();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

		CSTORAGERESULT Flush();

	};

#pragma endregion


#pragma region [SdStorageAdapter] DEFINITION

	CLASS SdStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		SdStorageAdapter(PCCHAR);


		// [IStorage] IMPLEMENTATION

		CBOOL Available();

		CSTORAGERESULT Open(CBOOL = FALSE);
		CSTORAGERESULT Close();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

		CSTORAGERESULT Flush();
	};

#pragma endregion


#pragma region [ExtEepromStorageAdapter] DEFINITION

	CLASS ExtEepromStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		ExtEepromStorageAdapter();


		// [IStorage] IMPLEMENTATION

		CBOOL Available();

		CSTORAGERESULT Open(CBOOL = FALSE);
		CSTORAGERESULT Close();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

		CSTORAGERESULT Flush();
	};

#pragma endregion

#endif  // #ifdef ARDUINO
};

#endif
