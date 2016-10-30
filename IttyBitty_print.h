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

#define ON_STRING						"1"
#define OFF_STRING						"0"

#define TRUE_STRING						"TRUE"
#define FALSE_STRING					"FALSE"


namespace IttyBitty
{
	VOID FlushAndDelay(Stream & = DEFAULT_SERIAL);

	VOID PrintBytes(PCBYTE, CSIZE size, Stream & = DEFAULT_SERIAL);
	VOID PrintBytesAndFlush(PCBYTE, CSIZE size, Stream & = DEFAULT_SERIAL);

	VOID PrintBit(RCBIT, Stream & = DEFAULT_SERIAL);
	VOID PrintBitLine(RCBIT, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCBOOL, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCBOOL, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCCHAR, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCCHAR, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCBYTE, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCBYTE, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCSHORT, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCSHORT, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCWORD, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCWORD, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCSIZE, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCSIZE, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCLONG, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCLONG, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCDWORD, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCDWORD, Stream & = DEFAULT_SERIAL);

	VOID PrintVal(RCFLOAT, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(RCFLOAT, Stream & = DEFAULT_SERIAL);

	VOID PrintString(PCCHAR, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(PCCHAR = "", Stream & = DEFAULT_SERIAL);

	VOID PrintString(CONST __FlashStringHelper *, Stream & = DEFAULT_SERIAL);
	VOID PrintLine(CONST __FlashStringHelper *, Stream & = DEFAULT_SERIAL);
}

#endif
