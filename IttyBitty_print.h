/***********************************************************************************************
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
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

#ifndef DEFAULT_TRUE_STRING
	#define DEFAULT_TRUE_STRING		F("TRUE")
#endif

#ifndef DEFAULT_FALSE_STRING
	#define DEFAULT_FALSE_STRING	F("FALSE")
#endif

#ifndef HIGH_STRING
	#define HIGH_STRING				F("1")
#endif

#ifndef LOW_STRING
	#define LOW_STRING				F("0")
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
		result += printer.println();
		FlushAndDelay();

		return result;
	}

	INLINE CSIZE PrintValue(CBOOL data, FLASH_STRING trueString, FLASH_STRING falseString, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data ? trueString : falseString);
	}

	INLINE CSIZE PrintLine(CBOOL data, FLASH_STRING trueString, FLASH_STRING falseString, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintValue(data, trueString, falseString, printer);
		result += printer.println();
		FlushAndDelay(printer);

		return result;
	}

	INLINE CSIZE PrintValue(CBOOL data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintValue(data, DEFAULT_TRUE_STRING, DEFAULT_FALSE_STRING, printer);
	}

	INLINE CSIZE PrintLine(CBOOL data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, DEFAULT_TRUE_STRING, DEFAULT_FALSE_STRING, printer);
	}

	INLINE CSIZE PrintBit(CBIT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintValue(data, HIGH_STRING, LOW_STRING, printer);
	}

	INLINE CSIZE PrintBitLine(CBIT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, HIGH_STRING, LOW_STRING, printer);
	}

	INLINE CSIZE PrintValue(CBYTE data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(CSHORT data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(CWORD data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(CLONG data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(RCDWORD data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(CSIZE data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(CINT data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, base);
	}

	INLINE CSIZE PrintValue(RCFLOAT data, CINT digits = 2, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, 2);
	}

	template<typename T>
	INLINE CSIZE PrintLine(T data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintValue(data, base);
		result += printer.println();
		FlushAndDelay(printer);

		return result;
	}

	template<typename T>
	INLINE CSIZE PrintBits(T data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintValue(data, BIN, printer);
	}

	template<typename T>
	INLINE CSIZE PrintOctal(T data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintValue(data, OCT, printer);
	}

	template<typename T>
	INLINE CSIZE PrintHex(T data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintValue(data, HEX, printer);
	}

	INLINE CSIZE PrintChar(CCHAR data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintString(PCCHAR data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(PCCHAR data = "", HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintString(data, printer);
		result += printer.println();
		FlushAndDelay(printer);

		return result;
	}

	INLINE CSIZE PrintString(FLASH_STRING data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	INLINE CSIZE PrintLine(FLASH_STRING data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintString(data, printer);
		result += printer.println();
		FlushAndDelay(printer);

		return result;
	}

#pragma endregion
}

#endif
