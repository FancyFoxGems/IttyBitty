/***********************************************************************************************
* [IttyBitty_DB_defs.h]: HEADERS/TABLE DEFINITIONS FOR STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_DB_DEFS_H
#define ITTYBITTY_DB_DEFS_H


#include "IttyBitty_fields.h"
#include "IttyBitty_storage.h"


#pragma region DEFINES

#define ITTYBITTY_DB_DEFAULT_GROWTH_FACTOR		2U

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class DbHeader;
	typedef DbHeader DBHEADER, * PDBHEADER, & RDBHEADER, ** PPDBHEADER, && RRDBHEADER;
	typedef const DbHeader CDBHEADER, * PCDBHEADER, & RCDBHEADER, ** PPCDBHEADER;

	class IDbTableDef;
	typedef IDbTableDef IDBTABLEDEF, * PIDBTABLEDEF, & RIDBTABLEDEF, ** PPIDBTABLEDEF, && RRIDBTABLEDEF;
	typedef const IDbTableDef CIDBTABLEDEF, * PCIDBTABLEDEF, & RCIDBTABLEDEF, ** PPCIDBTABLEDEF;

	class DbTableDef;
	typedef DbTableDef DBTABLEDEF, * PDBTABLEDEF, & RDBTABLEDEF, ** PPDBTABLEDEF, && RRDBTABLEDEF;
	typedef const DbTableDef CDBTABLEDEF, * PCDBTABLEDEF, & RCDBTABLEDEF, ** PPCDBTABLEDEF;

	template<typename T = BYTE>
	class TypedDbTableDef;
	template<typename T = BYTE>
	using TYPEDDBTABLEDEF = TypedDbTableDef<T>;
	template<typename T = BYTE>
	using PTYPEDDBTABLEDEF = TypedDbTableDef<T> *;
	template<typename T = BYTE>
	using RTYPEDDBTABLEDEF = TypedDbTableDef<T> &;
	template<typename T = BYTE>
	using PPTYPEDDBTABLEDEF = TypedDbTableDef<T> **;
	template<typename T = BYTE>
	using RRTYPEDDBTABLEDEF = TypedDbTableDef<T> &&;
	template<typename T = BYTE>
	using CTYPEDDBTABLEDEF = const TypedDbTableDef<T>;
	template<typename T = BYTE>
	using PCTYPEDDBTABLEDEF = const TypedDbTableDef<T> *;
	template<typename T = BYTE>
	using RCTYPEDDBTABLEDEF = const TypedDbTableDef<T> &;
	template<typename T = BYTE>
	using PPCTYPEDDBTABLEDEF = const TypedDbTableDef<T> **;

#pragma endregion

	
#pragma region ENUMS

	ENUM DbResult : BYTE
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

	typedef enum DbResult DBRESULT, * PDBRESULT, & RDBRESULT, ** PPDBRESULT;
	typedef const enum DbResult CDBRESULT, * PCDBRESULT, & RCDBRESULT, ** PPCDBRESULT;

#pragma endregion

	
#pragma region [DbHeader] DEFINITION

	class DbHeader : public ISerializable
	{
	public:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbHeader(CBYTE = 0);

		//DbHeader(RCDBHEADER);
		//DbHeader(RRDBHEADER);

		EXPLICIT DbHeader(PCBYTE);
		EXPLICIT DbHeader(PCCHAR);

		DbHeader(RCDBTABLEDEF);
		DbHeader(CBYTE, PPIDBTABLEDEF);

		VIRTUAL ~DbHeader();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		
		// OPERATORS

		//VIRTUAL RDBHEADER operator=(RCDBHEADER);
		//VIRTUAL RDBHEADER operator=(RRDBHEADER);

		VIRTUAL PCIDBTABLEDEF operator[](CBYTE) const;
		VIRTUAL PIDBTABLEDEF operator[](CBYTE);
		

		// ACCESSORS
		
		VIRTUAL CBYTE GetTableDefCount() const;
		
		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);
		

		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;
		VIRTUAL CSIZE ByteWidth() const;
		VIRTUAL CSIZE StringLength() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		
	#ifdef ARDUINO
		
		VIRTUAL SIZE printTo(Print &) const;

	#endif


	protected:

		// INSTANCE VARIABLES

		PPIDBTABLEDEF _TableDefs = NULL;
	};

#pragma endregion

	
#pragma region [DbTableDef] DEFINITION

	class DbTableDef : public ISerializable
	{
	public:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTableDef();

		EXPLICIT DbTableDef(PCBYTE);
		EXPLICIT DbTableDef(PCCHAR);

		VIRTUAL ~DbTableDef();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:		

		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;
		VIRTUAL CSIZE ByteWidth() const;
		VIRTUAL CSIZE StringLength() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		
	#ifdef ARDUINO
		
		VIRTUAL SIZE printTo(Print &) const;

	#endif


	protected:

		// INSTANCE VARIABLES

		DWORD _AddrOffset = 0;
		DWORD _RowSize = 0;
	};

#pragma endregion
}

#endif
