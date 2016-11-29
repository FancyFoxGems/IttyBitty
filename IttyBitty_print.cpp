/**********************************************************************************************
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_SLIM)
	#define NO_ITTYBITTY_PRINT
#endif

#ifndef NO_ITTYBITTY_PRINT


#include "IttyBitty_print.h"

using namespace IttyBitty;


namespace IttyBitty
{
#pragma region SERIAL PRINT GLOBAL FUNCTION DEFINITIONS

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


	VOID PrintBit(CBIT data, HardwareSerial & printer)
	{
		printer.print(data ? ON_STRING : OFF_STRING);
	}

	VOID PrintBitLine(CBIT data, HardwareSerial & printer)
	{
		printer.println(data ? ON_STRING : OFF_STRING);
		FlushAndDelay();
	}

	VOID PrintVal(CBOOL data, HardwareSerial & printer)
	{
		printer.print(data ? TRUE_STRING : FALSE_STRING);
	}

	VOID PrintLine(CBOOL data, HardwareSerial & printer)
	{
		printer.println(data ? TRUE_STRING : FALSE_STRING);
		FlushAndDelay();
	}

	VOID PrintVal(CCHAR data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(CCHAR data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(CBYTE data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(CBYTE data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(CSHORT data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(CSHORT data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(CWORD data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(CWORD data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(CSIZE data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(CSIZE data, HardwareSerial & printer)
	{
		printer.println(data);
		FlushAndDelay();
	}

	VOID PrintVal(CLONG data, HardwareSerial & printer)
	{
		printer.print(data);
	}

	VOID PrintLine(CLONG data, HardwareSerial & printer)
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

#pragma endregion
}

#endif // #ifndef NO_ITTYBITTY_PRINT
