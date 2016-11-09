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


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IDbTableSet;
	typedef IDbTableSet IDBTABLESET, * PIDBTABLESET, & RIDBTABLESET, ** PPIDBTABLESET, && RRIDBTABLESET;
	typedef const IDbTableSet CIDBTABLESET, * PCIDBTABLESET, & RCIDBTABLESET, ** PPCIDBTABLESET;

	class DbTableSet;
	typedef DbTableSet DBTABLESET, * PDBTABLESET, & RDBTABLESET, ** PPDBTABLESET, && RRDBTABLESET;
	typedef const DbTableSet CDBTABLESET, * PCDBTABLESET, & RCDBTABLESET, ** PPCDBTABLESET;

	class IDbTableDef;
	typedef IDbTableDef IDBTABLEDEF, * PIDBTABLEDEF, & RIDBTABLEDEF, ** PPIDBTABLEDEF, && RRIDBTABLEDEF;
	typedef const IDbTableDef CIDBTABLEDEF, * PCIDBTABLEDEF, & RCIDBTABLEDEF, ** PPCIDBTABLEDEF;

	template<CBYTE TableDefCount = 0>
	class GenericDbTableSet;
	template<CBYTE TableDefCount = 0>
	using GENERICDBTABLESET = GenericDbTableSet<TableDefCount>;
	template<CBYTE TableDefCount = 0>
	using PGENERICDBTABLESET = GenericDbTableSet<TableDefCount> *;
	template<CBYTE TableDefCount = 0>
	using RGENERICDBTABLESET = GenericDbTableSet<TableDefCount> &;
	template<CBYTE TableDefCount = 0>
	using PPGENERICDBTABLESET = GenericDbTableSet<TableDefCount> **;
	template<CBYTE TableDefCount = 0>
	using RRGENERICDBTABLESET = GenericDbTableSet<TableDefCount> &&;
	template<CBYTE TableDefCount = 0>
	using CGENERICDBTABLESET = const GenericDbTableSet<TableDefCount>;
	template<CBYTE TableDefCount = 0>
	using PCGENERICDBTABLESET = const GenericDbTableSet<TableDefCount> *;
	template<CBYTE TableDefCount = 0>
	using RCGENERICDBTABLESET = const GenericDbTableSet<TableDefCount> &;
	template<CBYTE TableDefCount = 0>
	using PPCGENERICDBTABLESET = const GenericDbTableSet<TableDefCount> **;

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

	// TODO: Not yet implemented.
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
	

#pragma region DbTableSet/DbTableDef PARSING GLOBAL FUNCTION DECLARATIONS

	PDBTABLESET DbTableSetFromBytes(Stream & stream);
	PDBTABLESET DbTableSetFromString(Stream & stream);

	PIDBTABLEDEF DbTableDefFromBytes(Stream & stream);
	PIDBTABLEDEF DbTableDefFromString(Stream & stream);

#pragma endregion

	
#pragma region [IDbTableSet] DEFINITION

	CLASS IDbTableSet : public IStorable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableSet() { }


		// ACCESSORS

		VIRTUAL CBYTE GetTableDefCount() const = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0) = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR) = 0;


	protected:
		
		// HELPER METHODS

		VIRTUAL CSIZE GetTableDefsByteSize() const = 0;
		VIRTUAL CSIZE GetTableDefsStringSize() const = 0;


		IDbTableSet() { }
	};

#pragma endregion

	
#pragma region [DbTableSet] DEFINITION

	CLASS DbTableSet : public DatumBase<ConstValue>, public IDbTableSet
	{
	protected:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTableSet(CBYTE = 0);

		EXPLICIT DbTableSet(PCBYTE);
		EXPLICIT DbTableSet(PCCHAR);

		DbTableSet(RCIDBTABLEDEF);
		DbTableSet(CBYTE, PPIDBTABLEDEF);


	public:

		VIRTUAL ~DbTableSet();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		
		// OPERATORS

		VIRTUAL PCIDBTABLEDEF operator[](CBYTE) const;
		VIRTUAL PIDBTABLEDEF operator[](CBYTE);
				

		// [IDbTableSet] IMPLEMENTATION
		
		VIRTUAL CBYTE GetTableDefCount() const;
		
		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0);

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR);
				

		// [IStorable] IMPLEMENTATION

		VIRTUAL MEDIARESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL MEDIARESULT SaveAstring(RCISTORAGE) const;

		VIRTUAL MEDIARESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL MEDIARESULT LoadFromString(RCISTORAGE);
		

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

		
		// [IDbTableSet] HELPER METHODS

		VIRTUAL CSIZE GetTableDefsByteSize() const;
		VIRTUAL CSIZE GetTableDefsStringSize() const;
	};

#pragma endregion
	

#pragma region [GenericDbTableSet] DEFINITION

	template<CBYTE TableDefCount>
	CLASS GenericDbTableSet : public DbTableSet
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE TABLE_DEF_COUNT()
		{
			return TableDefCount;
		}


		// CONSTRUCTORS

		GenericDbTableSet() : DbTableSet(TableDefCount) { }
		
		GenericDbTableSet(PPIDBTABLEDEF tableDefs) : DbTableSet(TableDefCount, tableDefs) { }


		// [DbTableSet] OVERRIDES

		CBYTE GetTableDefCount() const
		{
			return TABLE_DEF_COUNT();
		}


	protected:

		using DbTableSet::_Dispose;
		using DbTableSet::_TableDefs;
	};
	
#pragma endregion

	
#pragma region [IDbTableDef] DEFINITION

	class IDbTableDef : public IStorable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableDef() { }
		

		// ACCESSORS
		
		VIRTUAL CSIZE GetRowSize() const = 0;
		VIRTUAL DWORD GetAddrOffset() const = 0;
		VIRTUAL PCCHAR GetTableName() const = 0;
		

		// MUTATORS
		
		VIRTUAL VOID SetAddrOffset(CDWORD) = 0;
		VIRTUAL VOID SetTableName(PCCHAR) = 0;


		// INTERFACE METHODS


	protected:

		IDbTableDef() { }
	};

#pragma endregion

	
#pragma region [DbTableDef] DEFINITION

	class DbTableDef : public IDbTableDef
	{
	protected:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTableDef(CSIZE, PCCHAR = NULL, CDWORD = 0);

		EXPLICIT DbTableDef(PCBYTE);
		EXPLICIT DbTableDef(PCCHAR);

		
	public:

		VIRTUAL ~DbTableDef();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		

		// [IDbTableDef] IMPLEMENTATION
		
		VIRTUAL CSIZE GetRowSize() const;
		VIRTUAL DWORD GetAddrOffset() const;
		VIRTUAL PCCHAR GetTableName() const;
		
		VIRTUAL VOID SetAddrOffset(CDWORD) = 0;
		VIRTUAL VOID SetTableName(PCCHAR) = 0;
				

		// [IStorable] IMPLEMENTATION

		VIRTUAL MEDIARESULT SaveAsBinary(RCISTORAGE) const;
		VIRTUAL MEDIARESULT SaveAstring(RCISTORAGE) const;

		VIRTUAL MEDIARESULT LoadFromBinary(RCISTORAGE);
		VIRTUAL MEDIARESULT LoadFromString(RCISTORAGE);


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
		PCCHAR _TableName = 0;
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


	protected:

		// CONSTRUCTORS

		TypedDbTableDef(PCCHAR tableName = NULL, CDWORD addrOffset = 0) 
			: DbTableDef(ROW_SIZE(), tableName, addrOffset) { }

		
	public:

		// [DbTableDef] OVERRIDES

		CSIZE GetRowSize() const
		{
			return ROW_SIZE();
		}
	};
	
#pragma endregion
}

#endif
