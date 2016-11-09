/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (!defined(ARDUINO) || defined(ITTYBITTY_BASE)) && !defined(EXCLUDE_ITTYBITTY_EEPROM_I2C)
	#define EXCLUDE_ITTYBITTY_EEPROM_I2C
#endif

#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C


#include "IttyBitty_EEPROM_I2C.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANT & VARIABLE DEFINITIONS

CWORD IttyBitty::SERIAL_EEPROM_TIMEOUT_MS		= 500;
CBYTE IttyBitty::SERIAL_EEPROM_WAIT_DELAY_MS	= 1;
	
CBYTE IttyBitty::SERIAL_EEPROM_ERASE_VALUE		= 0xFF;


EEPROMI2C<> ExtEEPROM;

#pragma endregion


#endif //#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C
