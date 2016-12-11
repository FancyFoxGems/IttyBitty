/***********************************************************************************************
* [IttyBitty_DB_table_defs.h]: HEADERS/TABLE DEFINITIONS FOR STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_DB_DEFS_H
#define _ITTYBITTY_DB_DEFS_H


#include "IttyBitty_fields.h"
#include "IttyBitty_storage.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

	// ToBinary() / ToString() BUFFER POINTERS
	EXTERN PBYTE __db_table_def_set_buffer;
	EXTERN PBYTE __db_table_def_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IDbTableDef;
	TYPEDEF_CLASS_ALIASES(IDbTableDef, IDBTABLEDEF);

	class DbTableDef;
	TYPEDEF_CLASS_ALIASES(DbTableDef, DBTABLEDEF);


	template DEFAULT_T_CLAUSE
	class TypedDbTableDef;
	TEMPLATE_CLASS_USING_ALIASES(DEFAULT_T_CLAUSE, DEFAULT_T_ARGS, TypedDbTableDef, TYPEDDBTABLEDEF);


	// TODO: Not yet implemented.
	class FieldedDbTableDef;
	TYPEDEF_CLASS_ALIASES(FieldedDbTableDef, FIELDEDDBTABLEDEF);


	interface IDbTableDefSet;
	TYPEDEF_CLASS_ALIASES(IDbTableDefSet, IDBTABLEDEFSET);


	class DbTable;

	template DEFAULT_T_CLAUSE
	class TypedDbTable;

#pragma endregion


#pragma region ENUMS

	ENUM DbResult : BYTE
	{
		SUCCESS									= 0x00,

		ERROR									= 0x01,
		ERROR_UNKNOWN							= ERROR,

		ERROR_ARGUMENT							= ERROR | 0x20,
		ERROR_ARGUMENT_DATABASE_TOO_LARGE		= ERROR_ARGUMENT,
		ERROR_ARGUMENT_FILE_NAME_FORMAT			= ERROR_ARGUMENT | 0x10,
		ERROR_ARGUMENT_STORAGE_SPACE_LIMIT		= ERROR_ARGUMENT | 0x08,
		ERROR_ARGUMENT_OUT_OF_RANGE				= ERROR_ARGUMENT | 0x04,
		ERROR_ARGUMENT_NULL_POINTER				= ERROR_ARGUMENT | 0x02,

		ERROR_OPERATION							= ERROR,
		ERROR_OPERATION_ALREADY_CREATED			= ERROR_OPERATION,
		ERROR_OPERATION_UNKNOWN					= ERROR_OPERATION,
		ERROR_OPERATION_INTERRUPTED				= ERROR_OPERATION | 0x08,

		ERROR_OPERATION_CREATE					= ERROR_OPERATION | 0xF0,
		ERROR_OPERATION_DELETE					= ERROR_OPERATION | 0xE0,
		ERROR_OPERATION_ADD						= ERROR_OPERATION | 0xD0,
		ERROR_OPERATION_TABLE_FULL				= ERROR_OPERATION_ADD | 0x08,
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
		ERROR_MEDIA_ERASE_NOT_ALLOWED			= ERROR_MEDIA_ERASE,

		ERROR_MEDIA_READ						= ERROR_MEDIA | ERROR_OPERATION_READ,
		ERROR_MEDIA_READ_FAILURE				= ERROR_MEDIA_READ,
		ERROR_MEDIA_READ_BAD_ADDRESS			= ERROR_MEDIA_READ | 0x08,
		ERROR_MEDIA_READ_INTERRUPTED			= ERROR_MEDIA_READ | ERROR_OPERATION_INTERRUPTED,

		ERROR_MEDIA_WRITE						= ERROR_MEDIA | ERROR_OPERATION_WRITE,
		ERROR_MEDIA_WRITE_FAILURE				= ERROR_MEDIA_WRITE,
		ERROR_MEDIA_WRITE_NOT_ALLOWED			= ERROR_MEDIA_WRITE,
		ERROR_MEDIA_WRITE_INTERRUPTED			= ERROR_MEDIA_WRITE | ERROR_OPERATION_INTERRUPTED,
	};

	TYPEDEF_ENUM_ALIASES(DbResult, DBRESULT);

#pragma endregion


#pragma region [IDbTableDef] DEFINITION

	INTERFACE IDbTableDef : public IStorable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableDef() { }


		// ACCESSORS

		VIRTUAL RISTORAGE GetStorage() const = 0;

		VIRTUAL CSIZE RowSize() const = 0;

		VIRTUAL CWORD GetAddrOffset() const = 0;
		VIRTUAL PCCHAR GetTableName() const = 0;


		// MUTATORS

		VIRTUAL VOID SetStorage(RISTORAGE) = 0;


		// MUTATORS

		VIRTUAL VOID SetAddrOffset(CWORD) = 0;
		VIRTUAL VOID SetTableName(PCCHAR) = 0;


	protected:

		friend class DbTable;


		// [IDbTableDef] IHELPER METHODS

		VIRTUAL CBYTE TableNameLength() const = 0;


		IDbTableDef() { }
	};

#pragma endregion


#pragma region [DbTableDef] DEFINITION

	CLASS DbTableDef : public IDbTableDef
	{
	protected:

		// CONSTRUCTORS

		DbTableDef(RISTORAGE = IttyBitty::NULL_STORAGE(), CSIZE = 0, PCCHAR = NULL, CWORD = 0);

		EXPLICIT DbTableDef(PCBYTE, RISTORAGE = IttyBitty::NULL_STORAGE());
		EXPLICIT DbTableDef(PCCHAR, RISTORAGE = IttyBitty::NULL_STORAGE());


		// STATIC FUNCTIONS

		STATIC RDBTABLEDEF NULL_OBJECT();


	public:

		// DESTRUCTOR

		VIRTUAL ~DbTableDef();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// ACCESSORS

		VIRTUAL RISTORAGE GetStorage() const;


		// MUTATORS

		VIRTUAL VOID SetStorage(RISTORAGE);


		// [IDbTableDef] IMPLEMENTATION

		VIRTUAL CSIZE RowSize() const;

		VIRTUAL CWORD GetAddrOffset() const;
		VIRTUAL PCCHAR GetTableName() const;

		VIRTUAL VOID SetAddrOffset(CWORD);
		VIRTUAL VOID SetTableName(PCCHAR);


		// [IStorable] IMPLEMENTATION

		VIRTUAL CSTORAGERESULT Save();
		VIRTUAL CSTORAGERESULT Load();

		VIRTUAL CSTORAGERESULT SaveAsBinary() const;
		VIRTUAL CSTORAGERESULT SaveAsString() const;

		VIRTUAL CSTORAGERESULT LoadFromBinary();
		VIRTUAL CSTORAGERESULT LoadFromString();


		// [ISerializable] IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

		VIRTUAL VOID FreeBuffer() const;

	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


	protected:

		friend class DbTable;


		// INSTANCE VARIABLES

		RISTORAGE _Storage = IttyBitty::NULL_STORAGE();

		SIZE _RowSize = 0;
		PCCHAR _TableName = NULL;

		WORD _AddrOffset = 0;


		// [IDbTableDef] IHELPER METHODS

		VIRTUAL CBYTE TableNameLength() const;
	};

#pragma endregion


#pragma region [TypedDbTableDef] DEFINITION

	template DEFAULT_T_CLAUSE
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

		TypedDbTableDef(RISTORAGE storage = IttyBitty::NULL_STORAGE(), PCCHAR tableName = NULL, RCDWORD addrOffset = 0)
			: DbTableDef(storage, ROW_SIZE(), tableName, addrOffset) { }


	public:

		friend class TypedDbTable<T>;


		// [DbTableDef] OVERRIDES

		CSIZE RowSize() const
		{
			return ROW_SIZE();
		}
	};

#pragma endregion


#pragma region [IDbTableDefSet] DEFINITION

	INTERFACE IDbTableDefSet : public IStorable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDbTableDefSet() { }


		// ACCESSORS

		VIRTUAL CBYTE TableDefCount() const = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(CBYTE = 0) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(CBYTE = 0) = 0;

		VIRTUAL RCIDBTABLEDEF TableDef(PCCHAR) const = 0;
		VIRTUAL RIDBTABLEDEF TableDef(PCCHAR) = 0;


	protected:

		friend interface IDbTableSet;


		// HELPER METHODS

		VIRTUAL CSIZE TableDefsBinarySize() const = 0;
		VIRTUAL CSIZE TableDefsStringSize() const = 0;


		IDbTableDefSet() { }
	};

#pragma endregion
}

#endif
