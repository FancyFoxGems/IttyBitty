/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_STORAGE) || \
		defined(NO_ITTYBITTY_STORAGE_ADAPTERS) || defined(NO_ITTYBITTY_SD)
	#define NO_ITTYBITTY_STORAGE_ADAPTER_SD
#endif

#ifndef NO_ITTYBITTY_STORAGE_ADAPTER_SD


#include "IttyBitty_storage_adapter_sd.h"

using namespace IttyBitty;


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

#endif	// #ifndef NO_ITTYBITTY_STORAGE_ADAPTER_SD
