/***********************************************************************************************
* [IttyBitty_DB.h]: STRUCTURED DATA STORAGE SUPPORT
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_DB_H
#define ITTYBITTY_DB_H


#include "IttyBitty_bits.h"


#pragma region DEFINES


#define DB_FLAG B11011011

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	typedef byte* DB_Rec;

	class Database;
	typedef Database DATABASE;

#pragma endregion

	
#pragma region ENUMS

	ENUM DatabaseCommandResult : BYTE
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

#pragma endregion

	
#pragma region [DBHeader] DEFINITION

	struct DB_Header
	{
		byte flag;
		unsigned long n_recs;
		unsigned int rec_size;
		unsigned long table_size;
	};

#pragma endregion


#pragma region [Database] DEFINITION

	#define DB_REC (byte*)(void*)&

	class Database
	{
	public:

		typedef void DB_Write_Handler(unsigned long, const uint8_t);
		typedef uint8_t DB_Read_Handler(unsigned long);
		
		
		// CONSTRUCTOR

		Database(DB_Write_Handler *, DB_Read_Handler *);


		// USER METHODS

		unsigned long limit();
		unsigned long count();

		DatabaseCommandResult create(unsigned long, unsigned long, unsigned int);
		DatabaseCommandResult open(unsigned long);
		void clear();

		DatabaseCommandResult readRec(unsigned long, DB_Rec);
		DatabaseCommandResult deleteRec(unsigned long);
		DatabaseCommandResult insertRec(unsigned long, const DB_Rec);
		DatabaseCommandResult updateRec(unsigned long, const DB_Rec);
		DatabaseCommandResult appendRec(DB_Rec rec);


	private:
		
		// INSTANCE VARIABLES

		unsigned long DB_head_ptr;
		unsigned long DB_table_ptr;

		DB_Write_Handler *_write_byte;
		DB_Read_Handler *_read_byte;
		DB_Header DB_head;


		// HELPER METHODS

		void Write(unsigned long ee, const byte* p, unsigned int);
		void Read(unsigned long ee, byte* p, unsigned int);

		void writeHead();
		void readHead();

		DatabaseCommandResult writeRec(unsigned long, const DB_Rec);
	};
}


#pragma region GLOBAL CONSTANTS & VARIABLES

EXTERN IttyBitty::DATABASE DB;

#pragma endregion

#endif
