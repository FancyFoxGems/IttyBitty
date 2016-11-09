/***********************************************************************************************
* [IttyBitty_storage.h]: DATA PERSISTENCE TO NON-VOLATILE MEDIA
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_STORAGE_H
#define _ITTYBITTY_STORAGE_H


#include "IttyBitty_datum.h"


//#include "SD.h"


#pragma region DEFINES



#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	union StorageLocation;
	typedef StorageLocation STORAGELOCATION, * PSTORAGELOCATION, & RSTORAGELOCATION, ** PPSTORAGELOCATION, && RRSTORAGELOCATION;
	typedef const StorageLocation CSTORAGELOCATION, * PCSTORAGELOCATION, & RCSTORAGELOCATION, ** PPCSTORAGELOCATION;
	
	class IStorable;
	typedef IStorable ISTORABLE, * PISTORABLE, & RISTORABLE, ** PPISTORABLE, && RRISTORABLE;
	typedef const IStorable CISTORABLE, * PCISTORABLE, & RCISTORABLE, ** PPCISTORABLE;
	
	class IStorage;
	typedef IStorage ISTORAGE, * PISTORAGE, & RISTORAGE, ** PPISTORAGE, && RRISTORAGE;
	typedef const IStorage CISTORAGE, * PCISTORAGE, & RCISTORAGE, ** PPCISTORAGE;

	class StorageBase;
	typedef StorageBase STORAGEBASE, * PSTORAGEBASE, & RSTORAGEBASE, ** PPSTORAGEBASE, && RRSTORAGEBASE;
	typedef const StorageBase CSTORAGEBASE, * PCSTORAGEBASE, & RCSTORAGEBASE, ** PPCSTORAGEBASE;

#pragma endregion

	
#pragma region ENUMS

	ENUM StorageResult : BYTE
	{
		SUCCESS									= 0x00,

		ERROR									= 0x01,
		ERROR_UNKNOWN							= ERROR,

		ERROR_ARGUMENT							= ERROR | 0x20,
		ERROR_ARGUMENT_FILE_NAME_FORMAT			= ERROR_ARGUMENT | 0x10,
		ERROR_ARGUMENT_STORAGE_SPACE_LIMIT		= ERROR_ARGUMENT | 0x08,
		ERROR_ARGUMENT_OUT_OF_RANGE				= ERROR_ARGUMENT | 0x04,
		ERROR_ARGUMENT_NULL_POINTER				= ERROR_ARGUMENT | 0x02,

		ERROR_OPERATION							= ERROR,
		ERROR_OPERATION_UNKOWN					= ERROR_OPERATION,
		ERROR_OPERATION_INTERRUPTED				= ERROR_OPERATION | 0x08,
		
		ERROR_OPERATION_CREATE					= ERROR_OPERATION | 0xF0,
		ERROR_OPERATION_DELETE					= ERROR_OPERATION | 0xE0,
		ERROR_OPERATION_ADD						= ERROR_OPERATION | 0xD0,
		ERROR_OPERATION_BUFFER_FULL				= ERROR_OPERATION_ADD | 0x08,
		ERROR_OPERATION_REMOVE					= ERROR_OPERATION | 0xC0,
		ERROR_OPERATION_READ					= ERROR_OPERATION | 0x90,
		ERROR_OPERATION_WRITE					= ERROR_OPERATION | 0x80,

		ERROR_MEDIA								= ERROR_OPERATION | 0x40,
		ERROR_MEDIA_UNKNOWN_FAILURE				= ERROR_MEDIA,

		ERROR_MEDIA_OPEN						= ERROR_MEDIA,
		ERROR_MEDIA_OPEN_FAILURE				= ERROR_MEDIA_OPEN,
		ERROR_MEDIA_OPEN_FILE_NOT_FOUND			= ERROR_MEDIA | 0x08,
		ERROR_MEDIA_OPEN_FILE_FORMAT			= ERROR_MEDIA | 0x04,
		ERROR_MEDIA_OPEN_FILE_EMPTY				= ERROR_MEDIA | 0x02,

		ERROR_MEDIA_ALLOCATE					= ERROR_MEDIA | ERROR_OPERATION_CREATE,
		ERROR_MEDIA_ALLOCATE_FAILURE			= ERROR_MEDIA_ALLOCATE,
		ERROR_MEDIA_ALLOCATE_INTERRUPTED		= ERROR_MEDIA_ALLOCATE | ERROR_OPERATION_INTERRUPTED,

		ERROR_MEDIA_ERASE						= ERROR_MEDIA | ERROR_OPERATION_DELETE,
		ERROR_MEDIA_ERASE_FAILURE				= ERROR_MEDIA_ERASE,

		ERROR_MEDIA_READ						= ERROR_MEDIA | ERROR_OPERATION_READ,
		ERROR_MEDIA_READ_FAILURE				= ERROR_MEDIA_READ,
		ERROR_MEDIA_READ_BAD_ADDRESS			= ERROR_MEDIA_READ | 0x08,
		ERROR_MEDIA_READ_INTERRUPTED			= ERROR_MEDIA_READ | ERROR_OPERATION_INTERRUPTED,

		ERROR_MEDIA_WRITE						= ERROR_MEDIA | ERROR_OPERATION_WRITE,
		ERROR_MEDIA_WRITE_FAILURE				= ERROR_MEDIA_WRITE,
		ERROR_MEDIA_WRITE_INTERRUPTED			= ERROR_MEDIA_WRITE | ERROR_OPERATION_INTERRUPTED,
	};

	typedef enum StorageResult STORAGERESULT, * PSTORAGERESULT, & RSTORAGERESULT, ** PPSTORAGERESULT;
	typedef const enum StorageResult CSTORAGERESULT, * PCSTORAGERESULT, & RCSTORAGERESULT, ** PPCSTORAGERESULT;

#pragma endregion

	
#pragma region [DbLocation] DEFINITION

	UNION PACKED DbLocation
	{
		BYTE ByteAddress;
		WORD WordAddress;
		DWORD DWordAddress;

		PCCHAR FilePath;
	};

#pragma endregion

	
#pragma region [IStorable] DEFINITION

	CLASS IStorable : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IStorable() { }


		// INTERFACE METHODS

		VIRTUAL CSTORAGERESULT SaveAsBinary(RCISTORAGE) const = 0;
		VIRTUAL CSTORAGERESULT SaveAsString(RCISTORAGE) const = 0;

		VIRTUAL CSTORAGERESULT LoadFromBinary(RCISTORAGE) = 0;
		VIRTUAL CSTORAGERESULT LoadFromString(RCISTORAGE) = 0;


	protected:
		
		IStorable() { }
	};

#pragma endregion

	
#pragma region [IStorage] DEFINITION

	CLASS IStorage
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IStorage() { }


		// INTERFACE METHODS

		VIRTUAL CBOOL Available() = 0;

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE) = 0;

		VIRTUAL CSTORAGERESULT Seek(RCDWORD) = 0;

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE) = 0;
		
		VIRTUAL CSTORAGERESULT Flush() = 0;

		VIRTUAL CSTORAGERESULT Close() = 0;


	protected:
		
		IStorage() { }
	};

#pragma endregion


#pragma region [StorageBase] DEFINITION

	CLASS StorageBase
	{
	public:

		// [IStorage] IMPLEMENTATION

		VIRTUAL CBOOL Available();

		VIRTUAL CSTORAGERESULT Open(RCSTORAGELOCATION, CBOOL = FALSE);

		VIRTUAL CSTORAGERESULT Seek(RCDWORD);

		VIRTUAL CSTORAGERESULT Write(PCBYTE, CSIZE);
		
		VIRTUAL CSTORAGERESULT Flush();

		VIRTUAL CSTORAGERESULT Close();


	protected:

		// INSTANCE VARIABLES
	};

#pragma endregion
}

#endif
