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

#include "IttyBitty_info.h"

#ifdef ARDUINO
	#include "IttyBitty_EEPROM_I2C.h"
#endif

#ifdef ARDUINO

	#include "EEPROM.h"

	#ifndef NO_ITTYBITTY_SD
		#include "SD.h"
	#endif

#endif

#include <avr/pgmspace.h>


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

	#ifndef NO_ITTYBITTY_SD
		class SdStorageAdapter;
		TYPEDEF_CLASS_ALIASES(SdStorageAdapter, SDSTORAGEADAPTER);
	#endif

	#ifndef NO_ITTYBITTY_EEPROM_I2C
		template EEPROMI2C_T_CLAUSE
		class ExtEepromStorageAdapter;
		TEMPLATE_CLASS_USING_ALIASES(CSL(EEPROMI2C_T_CLAUSE), CSL(EEPROMI2C_T_ARGS), ExtEepromStorageAdapter, EXTEEPROMSTORAGEADAPTER);
	#endif

#endif  // #ifdef ARDUINO

#pragma endregion


#pragma region [MemoryResidentStorageAdapter] DEFINITION

	CLASS MemoryResidentStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		MemoryResidentStorageAdapter(CDWORD);


		// [IStorage] IMPLEMENTATION

		CDWORD Capacity();

		CSTORAGERESULT Close();

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);


	protected:

		// INSTANCE VARIABLES

		CDWORD _BufferSize = 0;
	};

#pragma endregion


#pragma region [FlashRomStorageAdapter] DEFINITION

	CLASS FlashRomStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		FlashRomStorageAdapter(CDWORD);


		// [IStorage] IMPLEMENTATION

		CDWORD Capacity();

		CSTORAGERESULT Open(CBOOL = FALSE);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);
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

		CDWORD Capacity();

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

	};

#pragma endregion


#ifndef NO_ITTYBITTY_SD

#pragma region [SdStorageAdapter] DEFINITION

	CLASS SdStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		SdStorageAdapter(PCCHAR, CBYTE = 10);


		// [IStorage] IMPLEMENTATION

		CDWORD Capacity();

		CBOOL Available();

		CSTORAGERESULT Open(CBOOL = FALSE);
		CSTORAGERESULT Close();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, CSIZE);
		CSTORAGERESULT Write(PCBYTE, CSIZE);

		CSTORAGERESULT Flush();


	protected:

		// INSTANCE VARIABLES

		File _File;
	};

#pragma endregion

#endif	//#ifndef NO_ITTYBITTY_SD


#ifndef NO_ITTYBITTY_EEPROM_I2C

#pragma region [ExtEepromStorageAdapter] DEFINITION

	template EEPROMI2C_T_CLAUSE_DEF
	CLASS ExtEepromStorageAdapter : public StorageBase
	{
	protected:

		// META-TYPEDEF ALIASES

		typedef EEPROMI2C<ChipType, DeviceNum> TEEPROMI2C;
		typedef typename TEEPROMI2C::TADDR TADDR;
		typedef typename TEEPROMI2C::CTADDR CTADDR;


	public:

		// CONSTRUCTORS

		ExtEepromStorageAdapter(CBOOL use400KHz = FALSE, RCDWORD startAddress = (CDWORD)0) : StorageBase(startAddress)
		{
			_ExtEEPROM = TEEPROMI2C(use400KHz, (CTADDR)startAddress);
		}


		// [IStorage] IMPLEMENTATION

		CDWORD Capacity()
		{
			return (CDWORD)_ExtEEPROM.Capacity();
		}

		CSTORAGERESULT Seek(RCDWORD address)
		{
			_ExtEEPROM.Seek((CTADDR)address);

			return StorageResult::SUCCESS;
		}

		CSTORAGERESULT Read(PBYTE buffer, CSIZE size)
		{
			if (_ExtEEPROM.Read(buffer, size) == size)
				return StorageResult::SUCCESS;

			return StorageResult::ERROR_MEDIA_READ_FAILURE;
		}

		CSTORAGERESULT Write(PCBYTE data, CSIZE size)
		{
			if (_ExtEEPROM.Write(data, size) == size)
				return StorageResult::SUCCESS;

			return StorageResult::ERROR_MEDIA_READ_FAILURE;
		}

	protected:

		// INSTANCE VARIABLES

		TEEPROMI2C _ExtEEPROM;
	};

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_EEPROM_I2C

#endif  // #ifdef ARDUINO
};

#endif
