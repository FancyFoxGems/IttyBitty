/***********************************************************************************************
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_PRINT_H
#define _ITTYBITTY_PRINT_H


#include "IttyBitty_bits.h"

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

#define ONE_STRING					F("1")
#define ZERO_STRING					F("0")

#ifndef HIGH_STRING
	#define HIGH_STRING				ONE_STRING
#endif

#ifndef LOW_STRING
	#define LOW_STRING				ZERO_STRING
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


	INLINE CSIZE PrintBool(CBOOL data, FLASH_STRING trueString, FLASH_STRING falseString, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data ? trueString : falseString);
	}

	INLINE CSIZE PrintBool(CBOOL data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintBool(data, DEFAULT_TRUE_STRING, DEFAULT_FALSE_STRING, printer);
	}

	INLINE CSIZE PrintBit(CBIT data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintBool(data, HIGH_STRING, LOW_STRING, printer);
	}

	INLINE CSIZE PrintValue(CCHAR data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS(data) / 2;
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(static_cast<CSHORT>(data), base);

		return result;
	}

	INLINE CSIZE PrintValue(CBYTE data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS(data) / 2;
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(data, base);

		return result;
	}

	INLINE CSIZE PrintValue(CSHORT data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS(data);
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(data, base);

		return result;
	}

	INLINE CSIZE PrintValue(CWORD data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS(data);
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(data, base);

		return result;
	}

	INLINE CSIZE PrintValue(CLONG data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS_32(MAKE_UNSIGNED(data));
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(data, base);

		return result;
	}

	INLINE CSIZE PrintValue(RCDWORD data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS_32(data);
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(data, base);

		return result;
	}

	INLINE CSIZE PrintValue(CUINT data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;

		if (base != DEC)
		{
			INT leadingZeroes = LEADING_ZERO_BITS_UINT(data);
			if (base == HEX)
				leadingZeroes /= BITS_PER_NYBBLE;
			else if (base != BIN)
				leadingZeroes = leadingZeroes / 3 + HAS_REMAINDER(leadingZeroes, 3);

			if (data == 0) --leadingZeroes;

			for (SIZE i = 0; i < leadingZeroes; i++)
				result += printer.print(ZERO_STRING);
		}

		result += printer.print(data, base);

		return result;
	}

	INLINE CSIZE PrintValue(CINT data, CINT base = DEC, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintValue(static_cast<UINT>(data), base, printer);
	}

	INLINE CSIZE PrintValue(RCFLOAT data, CINT digits = 2, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data, 2);
	}

	template<typename T>
	INLINE CSIZE PrintBinary(T data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
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

	INLINE CSIZE PrintString(FLASH_STRING data, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return printer.print(data);
	}

	template<typename T>
	INLINE CSIZE PrintValues(CONST T * values, CSIZE size, CINT base = DEC, PCCHAR separator = " ", HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = 0;
		for (SIZE i = 0; i < size; i++)
		{
			if (i > 0)
				result += PrintString(separator, printer);
			result += PrintValue(values[i], base, printer);
		}

		return result;
	}
	

	INLINE CSIZE _PrintLine(CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = printer.println();
		if (flushAndDelay)
			FlushAndDelay(printer);

		return result;
	}

	INLINE CSIZE PrintLine(CBOOL data, FLASH_STRING trueString, FLASH_STRING falseString, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintBool(data, trueString, falseString, printer);
		result += _PrintLine(flushAndDelay, printer);

		return result;
	}

	INLINE CSIZE PrintBoolLine(CBOOL data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, DEFAULT_TRUE_STRING, DEFAULT_FALSE_STRING, flushAndDelay, printer);
	}

	INLINE CSIZE PrintBitLine(CBIT data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, HIGH_STRING, LOW_STRING, flushAndDelay, printer);
	}

	template<typename T>
	INLINE CSIZE PrintLine(T data, CINT base = DEC, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintValue(data, base);
		result += _PrintLine(flushAndDelay, printer);

		return result;
	}

	template<typename T>
	INLINE CSIZE PrintBinaryLine(T data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, BIN, flushAndDelay, printer);
	}

	template<typename T>
	INLINE CSIZE PrintOctalLine(T data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, OCT, flushAndDelay, printer);
	}

	template<typename T>
	INLINE CSIZE PrintHexLine(T data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(data, HEX, flushAndDelay, printer);
	}

	INLINE CSIZE PrintCharLine(CCHAR data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintChar(data);
		result += _PrintLine(flushAndDelay, printer);

		return result;
	}

	INLINE CSIZE PrintLine(PCCHAR data = "", CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintString(data, printer);
		result += _PrintLine(flushAndDelay, printer);

		return result;
	}

	INLINE CSIZE PrintLine(FLASH_STRING data, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintString(data, printer);
		result += _PrintLine(flushAndDelay, printer);

		return result;
	}

	template<typename T>
	INLINE CSIZE PrintLine(CONST T * values, CSIZE size, CINT base = DEC, PCCHAR separator = " ", CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		SIZE result = PrintValues(values, size, base, separator, printer);
		result += _PrintLine(flushAndDelay, printer);

		return result;
	}

	template<typename T>
	INLINE CSIZE PrintLines(CONST T * values, CSIZE size, CINT base = DEC, CBOOL flushAndDelay = TRUE, HardwareSerial & printer = SERIAL_PRINT_DEFAULT_PORT)
	{
		return PrintLine(values, size, base, "\n", flushAndDelay, printer);
	}

#pragma endregion
}

#endif
