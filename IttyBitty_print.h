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

	VOID PrintBit(RCBIT, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintBitLine(RCBIT, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCBOOL, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCBOOL, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCCHAR, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCCHAR, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCBYTE, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCBYTE, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCSHORT, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCSHORT, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCWORD, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCWORD, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCSIZE, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCSIZE, HardwareSerial & = DEFAULT_SERIAL);

	VOID PrintVal(RCLONG, HardwareSerial & = DEFAULT_SERIAL);
	VOID PrintLine(RCLONG, HardwareSerial & = DEFAULT_SERIAL);

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
