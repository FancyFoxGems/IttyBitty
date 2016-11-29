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
#pragma region SERIAL PRINT GLOBAL FUNCTION DECLARATIONS

	VOID FlushAndDelay(HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintBytes(PCBYTE, CSIZE size, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintBytesAndFlush(PCBYTE, CSIZE size, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintBit(CBIT, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintBitLine(CBIT, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CBOOL, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CBOOL, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CCHAR, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CCHAR, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CBYTE, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CBYTE, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CSHORT, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CSHORT, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CWORD, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CWORD, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CSIZE, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CSIZE, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(CLONG, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CLONG, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(RCDWORD, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(RCDWORD, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintVal(RCFLOAT, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(RCFLOAT, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintString(PCCHAR, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(PCCHAR = "", HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

	VOID PrintString(CONST __FlashStringHelper *, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);
	VOID PrintLine(CONST __FlashStringHelper *, HardwareSerial & = SERIAL_PRINT_DEFAULT_PORT);

#pragma endregion
}

#endif
