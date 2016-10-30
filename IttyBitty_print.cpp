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


	VOID PrintBit(RCBIT data, Stream & printer)
	{
		printer.print(data ? ON_STRING : OFF_STRING);
	}

	VOID PrintBitLine(RCBIT data, Stream & printer)
	{
		printer.println(data ? ON_STRING : OFF_STRING);
		FlushAndDelay();
	}

	VOID PrintVal(RCBOOL data, Stream & printer)
	{
		printer.print(data ? TRUE_STRING : FALSE_STRING);
	}

	VOID PrintLine(RCBOOL data, Stream & printer)
	{
		printer.println(data ? TRUE_STRING : FALSE_STRING);
		FlushAndDelay();
	}

	VOID PrintVal(RCCHAR data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCCHAR data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCBYTE data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCBYTE data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCSHORT data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCSHORT data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCWORD data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCWORD data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCSIZE data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCSIZE data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCLONG data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCLONG data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCDWORD data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCDWORD data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCFLOAT data, Stream & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCFLOAT data, Stream & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintString(PCCHAR buffer, Stream & printer)
	{
		printer.print(buffer);
	}

	VOID PrintLine(PCCHAR buffer, Stream & printer)
	{
		printer.println(buffer);
		FlushAndDelay();
	}

	VOID PrintString(CONST __FlashStringHelper * flashBuffer, Stream & printer)
	{
		printer.print(flashBuffer);
	}

	VOID PrintLine(CONST __FlashStringHelper * flashBuffer, Stream & printer)
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
