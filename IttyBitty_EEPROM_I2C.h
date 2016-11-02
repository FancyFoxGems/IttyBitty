/***********************************************************************************************
* [IttyBitty_EEPROM_I2C.h]: EXTERNAL EEPROM CHIP SUPPORT
*	(i.e. Atmel AT24CXXX /  Microchip 24LCXXX Series) 
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef ITTYBITTY_EEPROM_I2C_H
#define ITTYBITTY_EEPROM_I2C_H


#include "IttyBitty_bits.h"

#include "Wire.h"


#pragma region DEFINES

#define SERIAL_EEPROM_DEFAULT_I2C_ADDRESS	0x50

#pragma endregion


namespace IttyBitty
{
#pragma region ENUMS
	
	enum SerialEEPROMChipFamily : CWORD
	{
		UNKNOWN_EEPROM_CHIP	= 0x0100,

		// Atmel 
		AT24C01		= 0x0001,
		AT24C02		= 0x0002,
		AT24C04		= 0x0004,
		AT24C08		= 0x0008,
		AT24C16		= 0x0010,
		AT24C32		= 0x0020,
		AT24C64		= 0x0050,
		AT24C128	= 0x0080,
		AT24C256	= 0x0100,
		AT24C512	= 0x0200,
		AT24C1024	= 0x0400,
		AT24CM01	= 0x0400,
		AT24CM02	= 0x0800,

		// Microchip (Prefixed w/ "mc" since enum val names cannot begin with a number)
		mc24XX01	= 0x0001,
		mc24XX02	= 0x0002,
		mc24XX04	= 0x0004,
		mc24XX08	= 0x0008,
		mc24XX16	= 0x0010,
		mc24XX32	= 0x0020,
		mc24XX64	= 0x0050,
		mc24XX128	= 0x0080,
		mc24XX256	= 0x0100,
		mc24XX512	= 0x0200,
		mc24XX102x	= 0x0400
	};

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	struct EEERef;
	typedef EEERef EEERef, * PEEEREF, & REEEREF, ** PPEEEREF, && RREEEREF;
	typedef const EEERef CEEEREF ,* PCEEEREF, & RCEEEREF, ** PPCEEEREF;

	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	class EEPROM_I2C;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using EEPROMI2C = EEPROM_I2C<ChipType, I2CAddr>;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using PEEPROMI2C = EEPROM_I2C<ChipType, I2CAddr> *;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using REEPROMI2C = EEPROM_I2C<ChipType, I2CAddr> &;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using PPEEPROMI2C = EEPROM_I2C<ChipType, I2CAddr> **;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using RREEPROMI2C = EEPROM_I2C<ChipType, I2CAddr> &&;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using CEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr>;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using PCEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr> *;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using RCEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr> &;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS>
	using PPCEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr> **;

#pragma endregion
	

#pragma region GLOBAL CONSTANTS & VARIABLES	

	EXTERN EEPROMI2C<> ExtEEPROM;

#pragma endregion
	

#pragma region [EEPROM_I2C] DEFINITION

	template<SerialEEPROMChipFamily ChipType, CBYTE I2CAddr>
	class EEPROM_I2C
	{
	public:

		// STATIC CONSTEXPR METHODS
		
		STATIC CONSTEXPR CWORD CapacityKb()
		{
			return (CWORD)ChipType;
		}

		STATIC CONSTEXPR CBYTE CapacityBytes()
		{
			return CapacityKb() * KILO * BITS_PER_BYTE * KILO;
		}
		
		STATIC CONSTEXPR CBYTE PageBytes()
		{
			if (CapacityKb() >= 1024)
				return 256;

			if (CapacityKb() >= 512)
				return 128;

			if (CapacityKb() >= 64)
				return CapacityKb() / 2;

			if (CapacityKb() >= 32)
				return CapacityKb();

			if (CapacityKb() >= 4)
				return 16;

			return 8;
		}


		// CONSTRUCTOR

		EEPROM_I2C(RCWORD = 0)
		{
		}


		// EEPROMClass METHOD HIDES

		VOID Write(RCDWORD addr, RCBYTE data)
		{
		   Wire.beginTransmission((uint8_t)((0x500000 | addr) >> 16));
		   Wire.write((uint8_t)((addr) >> 8));
		   Wire.write((uint8_t)(addr & 0xFF));
		   Wire.write(data);
		   Wire.endTransmission();
		   delay(5);
		}


		CBYTE Read(RCDWORD addr)
		{
		   uint8_t data = 0x00;
		   Wire.beginTransmission((uint8_t)((0x500000 | addr) >> 16));
		   Wire.write((uint8_t)((addr) >> 8));
		   Wire.write((uint8_t)(addr & 0xFF));
		   Wire.endTransmission();
		   Wire.requestFrom((uint8_t)((0x500000 | addr) >> 16),(uint8_t)1);
		   if (Wire.available()) data = Wire.peek();
		   return data;
		}

		//EERef operator[]( const int idx )    { return idx; }
		//uint8_t read( int idx )              { return EERef( idx ); }
		//void write( int idx, uint8_t val )   { (EERef( idx )) = val; }
		//void update( int idx, uint8_t val )  { EERef( idx ).update( val ); }
		//
		////STL and C++11 iteration capability.
		//EEPtr begin()                        { return 0x00; }
		//EEPtr end()                          { return length(); } //Standards requires this to be the item after the last valid entry. The returned pointer is invalid.
		//uint16_t length()                    { return E2END + 1; }

		template<typename T>
		T &get(int idx, T &t)
		{
			//EEPtr e = idx;
			//uint8_t *ptr = (uint8_t*) &t;
			//for( int count = sizeof(T) ; count ; --count, ++e )  *ptr++ = *e;
			return t;
		}
	
		template<typename T>
		const T &put(int idx, const T &t)
		{
			//EEPtr e = idx;
			//const uint8_t *ptr = (const uint8_t*) &t;
			//for( int count = sizeof(T) ; count ; --count, ++e )  (*e).update( *ptr++ );
			return t;
		}


	protected:

	};

#pragma endregion
}

#endif
