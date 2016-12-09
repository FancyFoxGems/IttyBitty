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

#if defined(ARDUINO) && !defined(NO_ITTYBITTY_EEPROM)

	#include "IttyBitty_info.h"

	#ifndef NO_ITTYBITTY_EEPROM_I2C
		#include "IttyBitty_EEPROM_I2C.h"
	#endif

	#include "EEPROM.h"

#endif


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class MemoryResidentStorageAdapter;
	TYPEDEF_CLASS_ALIASES(MemoryResidentStorageAdapter, MEMORYRESIDENTSTORAGEADAPTER);

	class FlashRomStorageAdapter;
	TYPEDEF_CLASS_ALIASES(FlashRomStorageAdapter, FLASHROMSTORAGEADAPTER);


#if defined(ARDUINO) && !defined(NO_ITTYBITTY_EEPROM)

	class EepromStorageAdapter;
	TYPEDEF_CLASS_ALIASES(EepromStorageAdapter, EEPROMSTORAGEADAPTER);

	#ifndef NO_ITTYBITTY_EEPROM_I2C
		template EEPROMI2C_T_CLAUSE
		class ExtEepromStorageAdapter;
		TEMPLATE_CLASS_USING_ALIASES(CSL(EEPROMI2C_T_CLAUSE), CSL(EEPROMI2C_T_ARGS), ExtEepromStorageAdapter, EXTEEPROMSTORAGEADAPTER);
	#endif

#endif  // #if defined(ARDUINO) && !defined(NO_ITTYBITTY_EEPROM)

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

		CSTORAGERESULT Read(PBYTE, RCDWORD);
		CSTORAGERESULT Write(PCBYTE, RCDWORD);


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

		CSTORAGERESULT Read(PBYTE, RCDWORD);
		CSTORAGERESULT Write(PCBYTE, RCDWORD);

		CSTORAGERESULT Erase(RCDWORD);
	};

#pragma endregion


#if defined(ARDUINO) && !defined(NO_ITTYBITTY_EEPROM)

#pragma region [EepromStorageAdapter] DEFINITION

	CLASS EepromStorageAdapter : public StorageBase
	{
	public:

		// CONSTRUCTORS

		EepromStorageAdapter(CWORD);


		// [IStorage] IMPLEMENTATION

		CDWORD Capacity();

		CSTORAGERESULT Read(PBYTE, RCDWORD);
		CSTORAGERESULT Write(PCBYTE, RCDWORD);

	};

#pragma endregion


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

		CSTORAGERESULT Read(PBYTE buffer, RCDWORD size)
		{
			if (_ExtEEPROM.Read(buffer, size) == size)
				return StorageResult::SUCCESS;

			return StorageResult::ERROR_MEDIA_READ_FAILURE;
		}

		CSTORAGERESULT Write(PCBYTE data, RCDWORD size)
		{
			if (_ExtEEPROM.Write(data, size) == size)
				return StorageResult::SUCCESS;

			return StorageResult::ERROR_MEDIA_READ_FAILURE;
		}

		CSTORAGERESULT Erase(RCDWORD size)
		{
			if (_ExtEEPROM.Erase(size) == size)
				return StorageResult::SUCCESS;

			return StorageBase::Erase(size);
		}

	protected:

		// INSTANCE VARIABLES

		TEEPROMI2C _ExtEEPROM;
	};

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_EEPROM_I2C

#endif  // #if defined(ARDUINO) && !defined(NO_ITTYBITTY_EEPROM)
};

#endif
