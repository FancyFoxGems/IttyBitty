/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) && !defined(EXCLUDE_ITTYBITTY_EEPROM_I2C)
	#define EXCLUDE_ITTYBITTY_EEPROM_I2C
#endif

#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C


#include "IttyBitty_EEPROM_I2C.h"

using namespace IttyBitty;


EEPROMI2C<> IttyBitty::ExtEEPROM;

#endif //#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C
