/***********************************************************************************************
* [IttyBitty_EEPROM_I2C.h]: EXTERNAL EEPROM CHIP SUPPORT (i.e. Atmel AT24CXXX /  Microchip 24LCXXX Series) 
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#if (!defined(ARDUINO) || defined(ITTYBITTY_NO_TWI)) && !defined(ITTYBITTY_EEPROM_I2C_H)
	#define ITTYBITTY_EEPROM_I2C_H
#endif

#ifndef ITTYBITTY_EEPROM_I2C_H
#define ITTYBITTY_EEPROM_I2C_H


#include "IttyBitty_bits.h"

#include "Wire.h"


namespace IttyBitty
{

#define FULL_MASK 0x7FFFF
#define DEVICE_MASK 0x7F0000
#define WORD_MASK 0xFFFF

class EEPROM_I2C
{
  public:

	EEPROM_I2C();

	static void write(unsigned long, uint8_t);
	static uint8_t read(unsigned long);
};

extern EEPROM_I2C ExtEEPROM;
}

#endif
