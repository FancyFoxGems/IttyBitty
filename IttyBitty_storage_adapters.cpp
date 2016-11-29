/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_STORAGE)
	#define NO_ITTYBITTY_STORAGE_ADAPTERS
#endif

#ifndef NO_ITTYBITTY_STORAGE_ADAPTERS


#include "IttyBitty_storage_adapters.h"

using namespace IttyBitty;


#pragma region [MemoryResidentStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

MemoryResidentStorageAdapter::MemoryResidentStorageAdapter(CDWORD bufferSize)
	: StorageBase((WORD)new byte[bufferSize]), _BufferSize(bufferSize) { }


// [IStorage] IMPLEMENTATION

CDWORD MemoryResidentStorageAdapter::Capacity()
{
	return _BufferSize;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Close()
{
	delete[] (PBYTE)_Location.WordAddress;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Read(PBYTE buffer, RCDWORD size)
{
	memcpy(buffer, (PCBYTE)_Location.WordAddress, size);

	return StorageResult::SUCCESS;
}

CSTORAGERESULT MemoryResidentStorageAdapter::Write(PCBYTE data, RCDWORD size)
{
	memcpy((PBYTE)_Location.WordAddress, data, size);

	return StorageResult::SUCCESS;
}

#pragma endregion


#pragma region [FlashRomStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

FlashRomStorageAdapter::FlashRomStorageAdapter(CDWORD addr) : StorageBase(addr) { }


// [IStorage] IMPLEMENTATION

CSTORAGERESULT FlashRomStorageAdapter::Open(CBOOL rwFlag)
{
	if (rwFlag)
		return StorageResult::ERROR_MEDIA_WRITE_NOT_ALLOWED;

	return StorageResult::SUCCESS;
}

CDWORD FlashRomStorageAdapter::Capacity()
{
	return FlashRomTotalSize();
}

CSTORAGERESULT FlashRomStorageAdapter::Read(PBYTE buffer, RCDWORD size)
{
	SIZE bytesRead = 0;

	while (bytesRead < size)
	{
	#ifdef pgm_read_byte_far
		if (_Location.DWordAddress <= MAX_OF(WORD))
			buffer[bytesRead++] = pgm_read_byte_near(_Location.WordAddress++);
		else
			buffer[bytesRead++] = pgm_read_byte_far(_Location.DWordAddress++);
	#else
		buffer[bytesRead++] = pgm_read_byte_near(_Location.WordAddress++);
	#endif
	}

	return StorageResult::SUCCESS;
}

CSTORAGERESULT FlashRomStorageAdapter::Write(PCBYTE data, RCDWORD size)
{
	return StorageResult::ERROR_MEDIA_WRITE_NOT_ALLOWED;
}

CSTORAGERESULT FlashRomStorageAdapter::Erase(RCDWORD size)
{
	return StorageResult::ERROR_MEDIA_ERASE_NOT_ALLOWED;
}

#pragma endregion


#ifdef ARDUINO

#pragma region [EepromStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

EepromStorageAdapter::EepromStorageAdapter(CWORD addr) : StorageBase((WORD)addr) { }


// [IStorage] IMPLEMENTATION

CDWORD EepromStorageAdapter::Capacity()
{
	return EepromTotalSize();
}

CSTORAGERESULT EepromStorageAdapter::Read(PBYTE buffer, RCDWORD size)
{
	SIZE bytesRead = 0;

	while (bytesRead < size)
		buffer[bytesRead++] = EEPROM.read((INT)_Location.WordAddress++);

	return StorageResult::SUCCESS;
}

CSTORAGERESULT EepromStorageAdapter::Write(PCBYTE data, RCDWORD size)
{
	SIZE bytesWritten = 0;

	while (bytesWritten < size)
		EEPROM.write((INT)_Location.WordAddress++, data[bytesWritten++]);

	return StorageResult::SUCCESS;
}

#pragma endregion


#ifndef NO_ITTYBITTY_SD

#pragma region [SdStorageAdapter] IMPLEMENTATION

// CONSTRUCTOR

SdStorageAdapter::SdStorageAdapter(PCCHAR filePath, CBYTE csPin) : StorageBase(filePath)
{
	SD.begin(csPin);
}


// [IStorage] IMPLEMENTATION

CDWORD SdStorageAdapter::Capacity()
{
	return _File.size();
}

CBOOL SdStorageAdapter::Available()
{
	return _File.available();
}

CSTORAGERESULT SdStorageAdapter::Open(CBOOL rwFlag)
{
	_File = SD.open(_Location.FilePath, rwFlag);

	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Close()
{
	_File.close();

	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Flush()
{
	_File.flush();

	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Seek(RCDWORD address)
{
	if (!_File.seek(address))
		return StorageResult::ERROR_MEDIA_UNKNOWN_FAILURE;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Read(PBYTE buffer, RCDWORD size)
{
	if (_File.readBytes(buffer, size) == size)
		return StorageResult::ERROR_MEDIA_READ_FAILURE;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Write(PCBYTE data, RCDWORD size)
{
	if (_File.write(data, size) == size)
		return StorageResult::ERROR_MEDIA_WRITE_FAILURE;

	return StorageResult::SUCCESS;
}

CSTORAGERESULT SdStorageAdapter::Erase(RCDWORD size)
{
	if (size == 0)
	{
		if (!SD.remove(_Location.FilePath))
			return StorageResult::ERROR_MEDIA_ERASE_FAILURE;
	}

	return StorageBase::Erase(size);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_SD

#endif  // #ifdef ARDUINO

#endif	// #ifndef NO_ITTYBITTY_STORAGE
