/***********************************************************************************************
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#if !defined(ARDUINO) && !defined(EXCLUDE_ITTYBITTY_PRINT)
	#define EXCLUDE_ITTYBITTY_PRINT
	#define _ITTYBITTY_PRINT_H
#endif


#ifndef _ITTYBITTY_PRINT_H
#define _ITTYBITTY_PRINT_H


#include <Stream.h>

#include "IttyBitty_util.h"


/* SERIAL OPTIONS */

#ifndef STREAM_PRINT_DELAY_MS
	#define STREAM_PRINT_DELAY_MS		100
#endif

#ifndef DEFAULT_SERIAL
	#define DEFAULT_SERIAL				SERIAL_PORT_MONITOR
#endif

#define TRUE_STRING						"TRUE"
#define FALSE_STRING					"FALSE"


namespace IttyBitty
{
	VOID FlushAndDelay(Stream & = DEFAULT_SERIAL);

	VOID PrintBytes(PCBYTE, CSIZE size, Stream & = DEFAULT_SERIAL);
	VOID PrintBytesAndFlush(PCBYTE, CSIZE size, Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(CBOOL, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(CBOOL, Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(CBYTE, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(CBYTE, Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(CWORD, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(CWORD, Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(CLONG, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(CLONG, Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(CFLOAT, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(CFLOAT, Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(PCCHAR, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(PCCHAR = "", Stream & = DEFAULT_SERIAL);

	VOID PrintAndFlush(const __FlashStringHelper *, Stream & = DEFAULT_SERIAL);
	VOID PrintLineAndFlush(const __FlashStringHelper *, Stream & = DEFAULT_SERIAL);
}

#endif
