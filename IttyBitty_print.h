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


#include "HardwareSerial.h"

#include "IttyBitty_util.h"


/* SERIAL OPTIONS */

#ifndef SERIAL_PRINT_DELAY_MS
	#define SERIAL_PRINT_DELAY_MS		5
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
	VOID FlushAndDelay(HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintBytes(PCBYTE, CSIZE size, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintBytesAndFlush(PCBYTE, CSIZE size, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintBit(CBIT, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintBitLine(CBIT, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CBOOL, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CBOOL, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CCHAR, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CCHAR, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CBYTE, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CBYTE, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CSHORT, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CSHORT, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CWORD, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CWORD, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CSIZE, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CSIZE, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(CLONG, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CLONG, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCDWORD, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCDWORD, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCFLOAT, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCFLOAT, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintString(PCCHAR, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(PCCHAR = "", HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintString(CONST __FlashStringHelper *, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(CONST __FlashStringHelper *, HardwareSerial & = DEFAULT_SERIAL);
}

#endif
