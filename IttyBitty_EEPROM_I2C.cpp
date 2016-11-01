/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if (!defined(ARDUINO) || defined(ITTYBITTY_NO_TWI)) && !defined(EXCLUDE_ITTYBITTY_EEPROM_I2C)
	#define EXCLUDE_ITTYBITTY_EEPROM_I2C
#endif

#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C


#include "IttyBitty_EEPROM_I2C.h"

using namespace IttyBitty;


IttyBitty::EEPROM_I2C ExtEEPROM;


EEPROM_I2C::EEPROM_I2C(void)
{
   Wire.begin();
}

void EEPROM_I2C::write(unsigned long dataAddress, uint8_t data)
{
   Wire.beginTransmission((uint8_t)((0x500000 | dataAddress) >> 16)); // B1010xxx
   Wire.write((uint8_t)((dataAddress & WORD_MASK) >> 8)); // MSB
   Wire.write((uint8_t)(dataAddress & 0xFF)); // LSB
   Wire.write(data);
   Wire.endTransmission();
   delay(5);
}

uint8_t EEPROM_I2C::read(unsigned long dataAddress)
{
   uint8_t data = 0x00;
   Wire.beginTransmission((uint8_t)((0x500000 | dataAddress) >> 16)); // B1010xxx
   Wire.write((uint8_t)((dataAddress & WORD_MASK) >> 8)); // MSB
   Wire.write((uint8_t)(dataAddress & 0xFF)); // LSB
   Wire.endTransmission();
   Wire.requestFrom((uint8_t)((0x500000 | dataAddress) >> 16),(uint8_t)1);
   if (Wire.available()) data = Wire.peek();
   return data;
}

#endif //#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C
