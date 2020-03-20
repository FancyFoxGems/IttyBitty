/***********************************************************************************************
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_PRINT_H
#define _ITTYBITTY_PRINT_H


#include "IttyBitty_util.h"

#include "HardwareSerial.h"


#pragma region DEFINES

// NOTE: To use a value other than  its default here, #define the constant before including IttyBitty.

// SERIAL OPTIONS

#ifndef SERIAL_PRINT_DELAY_MS
	#define SERIAL_PRINT_DELAY_MS		5
#endif

#ifndef SERIAL_PRINT_DEFAULT_PORT
	#define SERIAL_PRINT_DEFAULT_PORT	SERIAL_PORT_MONITOR
#endif


// PRINTED VALUE LITERALS

#ifndef ON_STRING
	#define ON_STRING					"1"
#endif

#ifndef OFF_STRING
	#define OFF_STRING					"0"
#endif

#ifndef TRUE_STRING
	#define TRUE_STRING					"TRUE"
#endif

#ifndef FALSE_STRING
	#define FALSE_STRING				"FALSE"
#endif

#pragma endregion


namespace IttyBitty
{
#pragma region SERIAL PRINT GLOBAL FUNCTION DEFINITIONS

	INLINE VOID FlushAndDelay(HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		printer.flush();
		delay(SERIAL_PRINT_DELAY_MS);
	}

	INLINE CSIZE PrintBytes(PCBYTE buffer, CSIZE size, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;
		for (SIZE i = 0; i < size; i++)
			result += printer.write(buffer[i]);

		return result;
	}

	INLINE CSIZE PrintBytesAndFlush(PCBYTE buffer, CSIZE size, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintBytes(buffer, size);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintBit(CBIT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data ? ON_STRING : OFF_STRING);
	}

	INLINE CSIZE PrintBitLine(CBIT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data ? ON_STRING : OFF_STRING);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CBOOL data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data ? TRUE_STRING : FALSE_STRING);
	}

	INLINE CSIZE PrintLine(CBOOL data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data ? TRUE_STRING : FALSE_STRING);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CCHAR data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CCHAR data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CBYTE data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CBYTE data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CSHORT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CSHORT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CWORD data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CWORD data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CLONG data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CLONG data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(RCDWORD data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(RCDWORD data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CSIZE data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CSIZE data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CINT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(CINT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(RCFLOAT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(RCFLOAT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintString(PCCHAR data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(PCCHAR data = "", HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintString(FLASH_STRING data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(FLASH_STRING data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println(data);
		FlushAndDelay();

		return result;
	}

#pragma endregion
}

#endif
