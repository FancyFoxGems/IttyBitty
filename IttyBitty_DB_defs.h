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

	class IDbHeader;
	typedef IDbHeader IDBHEADER, * PIDBHEADER, & RIDBHEADER, ** PPIDBHEADER, && RRIDBHEADER;
	typedef const IDbHeader CIDBHEADER, * PCIDBHEADER, & RCIDBHEADER, ** PPCIDBHEADER;

	class DbHeader;
	typedef DbHeader DBHEADER, * PDBHEADER, & RDBHEADER, ** PPDBHEADER, && RRDBHEADER;
	typedef const DbHeader CDBHEADER, * PCDBHEADER, & RCDBHEADER, ** PPCDBHEADER;

	class IDbTableDef;
	typedef IDbTableDef IDBTABLEDEF, * PIDBTABLEDEF, & RIDBTABLEDEF, ** PPIDBTABLEDEF, && RRIDBTABLEDEF;
	typedef const IDbTableDef CIDBTABLEDEF, * PCIDBTABLEDEF, & RCIDBTABLEDEF, ** PPCIDBTABLEDEF;

	template<CBYTE TableDefCount = 0>
	class GenericDbHeader;
	template<CBYTE TableDefCount = 0>
	using GENERICDBHEADER = GenericDbHeader<TableDefCount>;
	template<CBYTE TableDefCount = 0>
	using PGENERICDBHEADER = GenericDbHeader<TableDefCount> *;
	template<CBYTE TableDefCount = 0>
	using RGENERICDBHEADER = GenericDbHeader<TableDefCount> &;
	template<CBYTE TableDefCount = 0>
	using PPGENERICDBHEADER = GenericDbHeader<TableDefCount> **;
	template<CBYTE TableDefCount = 0>
	using RRGENERICDBHEADER = GenericDbHeader<TableDefCount> &&;
	template<CBYTE TableDefCount = 0>
	using CGENERICDBHEADER = const GenericDbHeader<TableDefCount>;
	template<CBYTE TableDefCount = 0>
	using PCGENERICDBHEADER = const GenericDbHeader<TableDefCount> *;
	template<CBYTE TableDefCount = 0>
	using RCGENERICDBHEADER = const GenericDbHeader<TableDefCount> &;
	template<CBYTE TableDefCount = 0>
	using PPCGENERICDBHEADER = const GenericDbHeader<TableDefCount> **;

	class DbTableDef;
	typedef DbTableDef DBTABLEDEF, * PDBTABLEDEF, & RDBTABLEDEF, ** PPDBTABLEDEF, && RRDBTABLEDEF;
	typedef const DbTableDef CDBTABLEDEF, * PCDBTABLEDEF, & RCDBTABLEDEF, ** PPCDBTABLEDEF;

	template<typename T>
	class TypedDbTableDef;
	template<typename T>
	using TYPEDDBTABLEDEF = TypedDbTableDef<T>;
	template<typename T>
	using PTYPEDDBTABLEDEF = TypedDbTableDef<T> *;
	template<typename T>
	using RTYPEDDBTABLEDEF = TypedDbTableDef<T> &;
	template<typename T>
	using PPTYPEDDBTABLEDEF = TypedDbTableDef<T> **;
	template<typename T>
	using RRTYPEDDBTABLEDEF = TypedDbTableDef<T> &&;
	template<typename T>
	using CTYPEDDBTABLEDEF = const TypedDbTableDef<T>;
	template<typename T>
	using PCTYPEDDBTABLEDEF = const TypedDbTableDef<T> *;
	template<typename T>
	using RCTYPEDDBTABLEDEF = const TypedDbTableDef<T> &;
	template<typename T>
	using PPCTYPEDDBTABLEDEF = const TypedDbTableDef<T> **;

	class FieldedDbTableDef;
	typedef FieldedDbTableDef FIELDEDDBTABLEDEF, * PFIELDEDDBTABLEDEF, & RFIELDEDDBTABLEDEF, ** PPFIELDEDDBTABLEDEF, && RRFIELDEDDBTABLEDEF;
	typedef const FieldedDbTableDef CFIELDEDDBTABLEDEF, * PCFIELDEDDBTABLEDEF, & RCFIELDEDDBTABLEDEF, ** PPCFIELDEDDBTABLEDEF;

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
	

#pragma region DbHeader/DbTableDef PARSING GLOBAL FUNCTION DECLARATIONS

	PDBHEADER DbHeaderFromBytes(Stream & stream);
	PDBHEADER DbHeaderFromString(Stream & stream);

	PIDBTABLEDEF DbTableDefFromBytes(Stream & stream);
	PIDBTABLEDEF DbTableDefFromString(Stream & stream);

#pragma endregion

	
#pragma region [IDbHeader] DEFINITION

	class IDbHeader : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbHeader() { }


		// OPERATORS

		//VIRTUAL RDBHEADER operator=(RCDBHEADER) = 0;
		//VIRTUAL RDBHEADER operator=(RRDBHEADER) = 0;

		VIRTUAL PCIDBTABLEDEF operator[](CBYTE) const = 0;
		VIRTUAL PIDBTABLEDEF operator[](CBYTE) = 0;


		// ACCESSORS

		VIRTUAL CBYTE GetTableDefCount() const = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0) = 0;


	protected:
		
		// HELPER METHODS

		VIRTUAL CSIZE GetTableDefsByteSize() const = 0;
		VIRTUAL CSIZE GetTableDefsStringSize() const = 0;


		IDbHeader() { }
	};

#pragma endregion

	
#pragma region [DbHeader] DEFINITION

	class DbHeader : public DatumBase<ConstValue>, public IDbHeader
	{
	public:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbHeader(CBYTE = 0);

		//DbHeader(RCDBHEADER);
		//DbHeader(RRDBHEADER);

		EXPLICIT DbHeader(PCBYTE);
		EXPLICIT DbHeader(PCCHAR);

		DbHeader(RCIDBTABLEDEF);
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
				

		// [IDbHeader] IMPLEMENTATION
		
		VIRTUAL CBYTE GetTableDefCount() const;
		
		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);
		

		// [ISerializable] IMPLEMENTATION

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

		BOOL _Dispose = FALSE;

		BYTE _TableCount = 0;
		PPIDBTABLEDEF _TableDefs = NULL;

		
		// [IDbHeader] HELPER METHODS

		VIRTUAL CSIZE GetTableDefsByteSize() const;
		VIRTUAL CSIZE GetTableDefsStringSize() const;
	};

#pragma endregion
	

#pragma region [GenericDbHeader] DEFINITION

	template<CBYTE TableDefCount>
	CLASS GenericDbHeader : public DbHeader
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE TABLE_DEF_COUNT()
		{
			return TableDefCount;
		}


		// CONSTRUCTORS

		GenericDbHeader() : DbHeader(TableDefCount) { }
		
		GenericDbHeader(PPIDBTABLEDEF tableDefs) : DbHeader(TableDefCount, tableDefs) { }


		// [DbHeader] OVERRIDES

		CBYTE GetTableDefCount() const
		{
			return TABLE_DEF_COUNT();
		}


	protected:

		using DbHeader::_Dispose;
		using DbHeader::_TableDefs;
	};
	
#pragma endregion

	
#pragma region [IDbTableDef] DEFINITION

	class IDbTableDef : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableDef() { }
		

		// ACCESSORS
		
		VIRTUAL CSIZE GetRowSize() const = 0;

		VIRTUAL DWORD GetAddrOffset() const = 0;


		// INTERFACE METHODS


	protected:

		IDbTableDef() { }
	};

#pragma endregion

	
#pragma region [DbTableDef] DEFINITION

	class DbTableDef : public IDbTableDef
	{
	public:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTableDef(CSIZE = 0);

		EXPLICIT DbTableDef(DWORD);

		EXPLICIT DbTableDef(PCBYTE);
		EXPLICIT DbTableDef(PCCHAR);

		VIRTUAL ~DbTableDef();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		

		// [IDbTableDef] IMPLEMENTATION
		
		VIRTUAL CSIZE GetRowSize() const;

		VIRTUAL DWORD GetAddrOffset() const;


		// [ISerializable] IMPLEMENTATION

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

		BOOL _Dispose = FALSE;

		SIZE _RowSize = 0;
		DWORD _AddrOffset = 0;
	};

#pragma endregion
	

#pragma region [TypedDbTableDef] DEFINITION
	
	template<typename T>
	CLASS TypedDbTableDef : public DbTableDef
	{
	public:

		// TYPEDEF ALIASES

		typedef T ROW_TYPE;


		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CSIZE ROW_SIZE()
		{
			return T_SIZE;
		}


		// CONSTRUCTORS

		TypedDbTableDef() : DbTableDef(ROW_SIZE()) { }


		// [DbTableDef] OVERRIDES

		CSIZE GetRowSize() const
		{
			return ROW_SIZE();
		}
	};
	
#pragma endregion
}

#endif
