/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (!defined(ARDUINO) || defined(ITTYBITTY_BASE)) && !defined(NO_ITTYBITTY_STORAGE_ADAPTERS)
	#define NO_ITTYBITTY_STORAGE_ADAPTERS
#endif

#ifndef NO_ITTYBITTY_STORAGE_ADAPTERS


#include "IttyBitty_storage_adapters.h"

using namespace IttyBitty;

#include <avr/pgmspace.h>

#ifdef ARDUINO
	#include "EEPROM.h"
	#include "SD.h"
#endif


#pragma region [MemoryResidentStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

MemoryResidentStorageAdapter::MemoryResidentStorageAdapter(CDWORD addr) : StorageBase(addr) { }


// [IStorage] IMPLEMENTATION

CBOOL MemoryResidentStorageAdapter::Available()
{
	return TRUE;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Open(CBOOL)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Close()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Seek(RCDWORD)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Read(PBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Write(PCBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Flush()
{
	return StorageResult::SUCCESS;
}

#pragma endregion


#pragma region [FlashRomStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

FlashRomStorageAdapter::FlashRomStorageAdapter(CDWORD addr) : StorageBase(addr) { }


// [IStorage] IMPLEMENTATION

CBOOL FlashRomStorageAdapter::Available()
{
	return TRUE;
}

CSTORAGERESULT FlashRomStorageAdapter::Open(CBOOL)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT FlashRomStorageAdapter::Close()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT FlashRomStorageAdapter::Seek(RCDWORD)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT FlashRomStorageAdapter::Read(PBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT FlashRomStorageAdapter::Write(PCBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT FlashRomStorageAdapter::Flush()
{
	return StorageResult::SUCCESS;
}

#pragma endregion


#ifdef ARDUINO

#pragma region [EepromStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

EepromStorageAdapter::EepromStorageAdapter(CWORD addr) : StorageBase(addr) { }


// [IStorage] IMPLEMENTATION

CBOOL EepromStorageAdapter::Available()
{
	return TRUE;
}

CSTORAGERESULT EepromStorageAdapter::Open(CBOOL)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT EepromStorageAdapter::Close()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT EepromStorageAdapter::Seek(RCDWORD)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT EepromStorageAdapter::Read(PBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT EepromStorageAdapter::Write(PCBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT EepromStorageAdapter::Flush()
{
	return StorageResult::SUCCESS;
}

#pragma endregion


#pragma region [SdStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

SdStorageAdapter::SdStorageAdapter(PCCHAR filePath) : StorageBase(filePath) { }


// [IStorage] IMPLEMENTATION

CBOOL SdStorageAdapter::Available()
{
	return TRUE;
}

CSTORAGERESULT SdStorageAdapter::Open(CBOOL)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Close()
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Seek(RCDWORD)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Read(PBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Write(PCBYTE, CSIZE)
{
	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Flush()
{
	return StorageResult::SUCCESS;
}

#pragma endregion

#endif  // #ifdef ARDUINO

#endif	// #ifndef NO_ITTYBITTY_STORAGE
