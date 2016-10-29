/**********************************************************************************************
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) && !defined(EXCLUDE_ITTYBITTY_PRINT)
	#define EXCLUDE_ITTYBITTY_PRINT
#endif

#ifndef EXCLUDE_ITTYBITTY_PRINT

#include "IttyBitty_print.h"

using namespace IttyBitty;


namespace IttyBitty
{
	VOID PrintBytes(PCBYTE buffer, CSIZE size, Stream & printer)
	{
		for (SIZE i = 0; i < size; i++)
			printer.write(buffer[i]);
	}

	VOID PrintBytesAndFlush(PCBYTE buffer, CSIZE size, Stream & printer)
	{
		PrintBytes(buffer, size);
		FlushAndDelay();
	}

	VOID PrintAndFlush(CBOOL data, Stream & printer)
	{
		printer.print(data ? TRUE_STRING : FALSE_STRING);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(CBOOL data, Stream & printer)
	{
		printer.println(data ? TRUE_STRING : FALSE_STRING);
		FlushAndDelay();
	}

	VOID PrintAndFlush(CBYTE data, Stream & printer)
	{
		printer.print(data);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(CBYTE data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintAndFlush(CWORD data, Stream & printer)
	{
		printer.print(data);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(CWORD data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintAndFlush(CLONG data, Stream & printer)
	{
		printer.print(data);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(CLONG data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintAndFlush(CFLOAT data, Stream & printer)
	{
		printer.print(data);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(CFLOAT data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintAndFlush(PCCHAR buffer, Stream & printer)
	{
		printer.print(buffer);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(PCCHAR buffer, Stream & printer)
	{
		printer.println(buffer);
		FlushAndDelay();
	}

	VOID PrintAndFlush(const __FlashStringHelper * flashBuffer, Stream & printer)
	{
		printer.print(flashBuffer);
		FlushAndDelay();
	}

	VOID PrintLineAndFlush(const __FlashStringHelper * flashBuffer, Stream & printer)
	{
		printer.println(flashBuffer);
		FlushAndDelay();
	}

	VOID FlushAndDelay(Stream & printer)
	{
		printer.flush();
		delay(STREAM_PRINT_DELAY_MS);
	}
}

#endif // #ifndef EXCLUDE_ITTYBITTY_PRINT
