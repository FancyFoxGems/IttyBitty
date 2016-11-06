/**********************************************************************************************
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_PRINT)
	#define EXCLUDE_ITTYBITTY_PRINT
#endif

#ifndef EXCLUDE_ITTYBITTY_PRINT


#include "IttyBitty_print.h"

using namespace IttyBitty;


namespace IttyBitty
{
	VOID PrintBytes(PCBYTE buffer, CSIZE size, HardwareSerial & printer)
	{
		for (SIZE i = 0; i < size; i++)
			printer.write(buffer[i]);
	}

	VOID PrintBytesAndFlush(PCBYTE buffer, CSIZE size, HardwareSerial & printer)
	{
		PrintBytes(buffer, size);
		FlushAndDelay();
	}


	VOID PrintBit(RCBIT data, HardwareSerial & printer)
	{
		printer.print(data ? ON_STRING : OFF_STRING);
	}

	VOID PrintBitLine(RCBIT data, HardwareSerial & printer)
	{
		printer.println(data ? ON_STRING : OFF_STRING);
		FlushAndDelay();
	}

	VOID PrintVal(RCBOOL data, HardwareSerial & printer)
	{
		printer.print(data ? TRUE_STRING : FALSE_STRING);
	}

	VOID PrintLine(RCBOOL data, HardwareSerial & printer)
	{
		printer.println(data ? TRUE_STRING : FALSE_STRING);
		FlushAndDelay();
	}

	VOID PrintVal(RCCHAR data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCCHAR data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCBYTE data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCBYTE data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCSHORT data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCSHORT data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCWORD data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCWORD data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCSIZE data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCSIZE data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCLONG data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCLONG data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCDWORD data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCDWORD data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(RCFLOAT data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(RCFLOAT data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintString(PCCHAR buffer, HardwareSerial & printer)
	{
		printer.print(buffer);
	}

	VOID PrintLine(PCCHAR buffer, HardwareSerial & printer)
	{
		printer.println(buffer);
		FlushAndDelay();
	}

	VOID PrintString(CONST __FlashStringHelper * flashBuffer, HardwareSerial & printer)
	{
		printer.print(flashBuffer);
	}

	VOID PrintLine(CONST __FlashStringHelper * flashBuffer, HardwareSerial & printer)
	{
		printer.println(flashBuffer);
		FlushAndDelay();
	}

	VOID FlushAndDelay(HardwareSerial & printer)
	{
		printer.flush();
		delay(SERIAL_PRINT_DELAY_MS);
	}
}

#endif // #ifndef EXCLUDE_ITTYBITTY_PRINT
