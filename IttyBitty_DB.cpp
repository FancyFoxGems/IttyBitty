/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_DB)
	#define EXCLUDE_ITTYBITTY_DB
#endif

#ifndef EXCLUDE_ITTYBITTY_DB


#include "IttyBitty_DB.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

//DATABASE DB;

#pragma endregion


#pragma region DB IMPLEMENTATION

// CONSTRUCTOR

Database::Database(DB_Write_Handler *w, DB_Read_Handler *r)
{
	_write_byte = w;
	_read_byte = r;
}


// USER METHODS

unsigned long Database::count()
{
	return DB_head.n_recs;
}

unsigned long Database::limit()
{
	// Thanks to oleh.sok...@gmail.com for the next line
	return (DB_head.table_size - sizeof(DB_Header)) / DB_head.rec_size;
}

DatabaseCommandResult Database::create(unsigned long head_ptr, unsigned long tablesize, unsigned int recsize)
{
	DB_head_ptr = head_ptr;
	DB_table_ptr = sizeof(DB_Header) + DB_head_ptr;
	DB_head.flag = DB_FLAG;
	DB_head.n_recs = 0;
	DB_head.rec_size = recsize;
	DB_head.table_size = tablesize;
	writeHead();
	if (DB_head.flag == DB_FLAG)
	{
		return DatabaseCommandResult::SUCCESS;
	}
	else
	{
		return DatabaseCommandResult::SUCCESS;
	}
}

DatabaseCommandResult Database::open(unsigned long head_ptr)
{
	DB_head_ptr = head_ptr;
	// Thanks to Steve Kelly for the next line...
	DB_table_ptr = sizeof(DB_Header) + DB_head_ptr; // this line was originally missing in the downloaded library
	readHead();
	return DatabaseCommandResult::SUCCESS;
}

void Database::clear()
{
	readHead();
	create(DB_head_ptr, DB_head.table_size, DB_head.rec_size);
}

DatabaseCommandResult Database::writeRec(unsigned long recno, const DB_Rec rec)
{
	Write(DB_table_ptr + ((recno - 1) * DB_head.rec_size), rec, DB_head.rec_size);
	return DatabaseCommandResult::SUCCESS;
}

DatabaseCommandResult Database::readRec(unsigned long recno, DB_Rec rec)
{
	if (recno < 1 || recno > DB_head.n_recs) return DatabaseCommandResult::SUCCESS;
	Read(DB_table_ptr + ((recno - 1) * DB_head.rec_size), rec, DB_head.rec_size);
	return DatabaseCommandResult::SUCCESS;
}

DatabaseCommandResult Database::deleteRec(unsigned long recno)
{
	if (recno < 0 || recno > DB_head.n_recs) return  DatabaseCommandResult::SUCCESS;
	DB_Rec rec = (byte*)malloc(DB_head.rec_size);
	for (unsigned long i = recno + 1; i <= DB_head.n_recs; i++)
	{
		readRec(i, rec);
		writeRec(i - 1, rec);
	}
	free(rec);
	DB_head.n_recs--;
	writeHead();
	return DatabaseCommandResult::SUCCESS;
}

DatabaseCommandResult Database::insertRec(unsigned long recno, DB_Rec rec)
{
	if (count() == limit()) return DatabaseCommandResult::SUCCESS;
	if (count() > 0 && (recno < 0 || recno > DB_head.n_recs)) return DatabaseCommandResult::SUCCESS;
	if (count() == 0 && recno == 1) return appendRec(rec);

	DB_Rec buf = (byte*)malloc(DB_head.rec_size);
	for (unsigned long i = DB_head.n_recs; i >= recno; i--)
	{
		readRec(i, buf);
		writeRec(i + 1, buf);
	}
	free(buf);
	writeRec(recno, rec);
	DB_head.n_recs++;
	writeHead();
	return DatabaseCommandResult::SUCCESS;
}

DatabaseCommandResult Database::updateRec(unsigned long recno, DB_Rec rec)
{
	if (recno < 0 || recno > DB_head.n_recs) return DatabaseCommandResult::SUCCESS;
	writeRec(recno, rec);
	return DatabaseCommandResult::SUCCESS;
}

DatabaseCommandResult Database::appendRec(DB_Rec rec)
{
	if (DB_head.n_recs + 1 > limit()) return DatabaseCommandResult::SUCCESS;
	DB_head.n_recs++;
	writeRec(DB_head.n_recs, rec);
	writeHead();
	return DatabaseCommandResult::SUCCESS;
}


// HELPER METHODS

void Database::Write(unsigned long ee, const byte* p, unsigned int recsize)
{
	for (unsigned int i = 0; i < recsize; i++)
		_write_byte(ee++, *p++);
}

void Database::Read(unsigned long ee, byte* p, unsigned int recsize)
{
	for (unsigned i = 0; i < recsize; i++)
		*p++ = _read_byte(ee++);
}

void Database::writeHead()
{
	Write(DB_head_ptr, DB_REC DB_head, (unsigned long)sizeof(DB_Header));
}

void Database::readHead()
{
	Read(DB_head_ptr, DB_REC DB_head, (unsigned long)sizeof(DB_Header));
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DB
