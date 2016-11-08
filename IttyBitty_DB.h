/***********************************************************************************************
* [IttyBitty_DB.h]: STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_DB_H
#define ITTYBITTY_DB_H


#include "IttyBitty_DB_defs.h"


#pragma region DEFINES

#define ITTYBITTY_DB_DEFAULT_GROWTH_FACTOR		2U

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IDbTable;
	typedef IDbTable IDBTABLE, * PIDBTABLE, & RIDBTABLE, ** PPIDBTABLE, && RRIDBTABLE;
	typedef const IDbTable CIDBTABLE, * PCIDBTABLE, & RCIDBTABLE, ** PPCIDBTABLE;

	class DbTable;
	typedef DbTable DBTABLE, * PDBTABLE, & RDBTABLE, ** PPDBTABLE, && RRDBTABLE;
	typedef const DbTable CDBTABLE, * PCDBTABLE, & RCDBTABLE, ** PPCDBTABLE;

	template<typename T>
	class TypedDbTable;
	template<typename T>
	using TYPEDDBTABLE = TypedDbTable<T>;
	template<typename T>
	using PTYPEDDBTABLE = TypedDbTable<T> *;
	template<typename T>
	using RTYPEDDBTABLE = TypedDbTable<T> &;
	template<typename T>
	using PPTYPEDDBTABLE = TypedDbTable<T> **;
	template<typename T>
	using RRTYPEDDBTABLE = TypedDbTable<T> &&;
	template<typename T>
	using CTYPEDDBTABLE = const TypedDbTable<T>;
	template<typename T>
	using PCTYPEDDBTABLE = const TypedDbTable<T> *;
	template<typename T>
	using RCTYPEDDBTABLE = const TypedDbTable<T> &;
	template<typename T>
	using PPCTYPEDDBTABLE = const TypedDbTable<T> **;

	class FieldedDbTable;
	typedef FieldedDbTable FIELDEDDBTABLE, * PFIELDEDDBTABLE, & RFIELDEDDBTABLE, ** PPFIELDEDDBTABLE, && RRFIELDEDDBTABLE;
	typedef const FieldedDbTable CFIELDEDDBTABLE, * PCFIELDEDDBTABLE, & RCFIELDEDDBTABLE, ** PPCFIELDEDDBTABLE;

	class Database;
	typedef Database DATABASE, * PDATABASE, & RDATABASE, ** PPDATABASE, && RRDATABASE;
	typedef const Database CDATABASE, * PCDATABASE, & RCDATABASE, ** PPCDATABASE;

#pragma endregion

	
/*#pragma region ENUMS

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

#pragma endregion*/

	
#pragma region [IDbTable] DEFINITION

	class IDbTable : public ISerializable, public IStorable
	{
	public:
		
		// DESTRUCTOR

		VIRTUAL ~IDbTable() { }

		
		// INTERFACE METHODS
		
		VIRTUAL CDWORD Size() const = 0;
		VIRTUAL CDWORD Capacity() const = 0;
		VIRTUAL CSIZE RowCount() const = 0;
		VIRTUAL CSIZE RowsAvailable() const = 0;

		VIRTUAL CDBRESULT Grow(CDWORD) = 0;
		

	protected:

		IDbTable() { }
	};

#pragma endregion

	
#pragma region [DbTable] DEFINITION

	class DbTable : public IDbTable
	{
	public:
		
		// CONSTRUCTORS/DESTRUCTOR

		DbTable();

		EXPLICIT DbTable(PCBYTE);
		EXPLICIT DbTable(PCCHAR);

		VIRTUAL ~DbTable();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IDbTable] IMPLEMENTATION
		
		VIRTUAL CDWORD Size() const;
		VIRTUAL CDWORD Capacity() const;
		VIRTUAL CSIZE RowCount() const;
		VIRTUAL CSIZE RowsAvailable() const;

		VIRTUAL CDBRESULT Grow(CDWORD);
				

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

		PIDBTABLEDEF _TableDef;
		DWORD _RowCount = 0;
	};

#pragma endregion
	

#pragma region [TypedDbTable] DEFINITION
	
	template<typename T>
	CLASS TypedDbTable : public DbTable
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

		TypedDbTable() : DbTable(ROW_SIZE()) { }


		// [DbTable] OVERRIDES

		CSIZE GetRowSize() const
		{
			return ROW_SIZE();
		}
	};
	
#pragma endregion


#pragma region [Database] DEFINITION

	class Database final : public ISerializable, public IStorable
	{
	public:		
		
		// CONSTRUCTOR

		Database(RCISTORAGE);


		// USER METHODS
		
		CDWORD Size() const;
		CBYTE Capacity() const;

		CDBRESULT Create();
		CDBRESULT Grow(CDWORD);

		CDBRESULT Open(RCSTORAGELOCATION);
		CDBRESULT WipeAllData();

		CDBRESULT readRec(unsigned long, PBYTE);
		CDBRESULT deleteRec(unsigned long);
		CDBRESULT insertRec(unsigned long, const PBYTE);
		CDBRESULT updateRec(unsigned long, const PBYTE);
		CDBRESULT appendRec(PBYTE rec);
				

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

		PIDBHEADER _Header;
		PPIDBTABLE _Tables = NULL;


		// HELPER METHODS

		void Write(unsigned long ee, const byte* p, unsigned int);
		void Read(unsigned long ee, byte* p, unsigned int);

		void writeHead();
		void readHead();

		CDBRESULT writeRec(unsigned long, const PBYTE);
	};

#pragma endregion
}

#endif
