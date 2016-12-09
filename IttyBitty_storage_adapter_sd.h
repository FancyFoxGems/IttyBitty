/***********************************************************************************************
* [IttyBitty_storage_adapter_sd.h]: SD STORAGE ADAPTER IMPLEMENTATION
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_STORAGE_ADAPTER_SD_H
#define _ITTYBITTY_STORAGE_ADAPTER_SD_H


#include "IttyBitty_storage_adapters.h"

#include "SD.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class SdStorageAdapter;
	TYPEDEF_CLASS_ALIASES(SdStorageAdapter, SDSTORAGEADAPTER);

#pragma endregion

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

		CSTORAGERESULT Flush();

		CSTORAGERESULT Seek(RCDWORD);

		CSTORAGERESULT Read(PBYTE, RCDWORD);
		CSTORAGERESULT Write(PCBYTE, RCDWORD);

		CSTORAGERESULT Erase(RCDWORD);


	protected:

		// INSTANCE VARIABLES

		File _File;
	};

#pragma endregion
};

#endif
