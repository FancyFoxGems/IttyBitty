/***********************************************************************************************
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_PRINT_H
#define _ITTYBITTY_PRINT_H


#include <Stream.h>

#include "IttyBitty_util.h"


#define STREAM_PRINT_DELAY_MS		100


namespace IttyBitty
{
	VOID FlushAndDelay(Stream & = Serial);

	VOID PrintBytes(PCBYTE, CSIZE size, Stream & = Serial);
	VOID PrintBytesAndFlush(PCBYTE, CSIZE size, Stream & = Serial);

	VOID PrintAndFlush(PCCHAR, Stream & = Serial);
	VOID PrintLineAndFlush(PCCHAR, Stream & = Serial);

	VOID PrintAndFlush(CFLOAT, Stream & = Serial);
	VOID PrintLineAndFlush(CFLOAT, Stream & = Serial);

	VOID PrintAndFlush(CLONG, Stream & = Serial);
	VOID PrintLineAndFlush(CLONG, Stream & = Serial);
	VOID PrintAndFlush(CWORD, Stream & = Serial);
	VOID PrintLineAndFlush(CWORD, Stream & = Serial);

	VOID PrintAndFlush(CBYTE, Stream & = Serial);
	VOID PrintLineAndFlush(CBYTE, Stream & = Serial);

	VOID PrintAndFlush(const __FlashStringHelper *, Stream & = Serial);
	VOID PrintLineAndFlush(const __FlashStringHelper *, Stream & = Serial);
}

#endif
