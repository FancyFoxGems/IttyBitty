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

#include "IttyBitty_print.h"
using namespace IttyBitty;

#include "Wire.h"
#include "EEPROM.h"


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

	struct _EEEPtr;
	typedef struct _EEEPtr EEEPtr, _eeeptr_t, EEEPTR, * PEEEPTR, & REEEPTR, ** PPEEEPTR, && RREEEPTR;
	typedef const struct _EEEPtr CEEEPTR ,* PCEEEPTR, & RCEEEPTR, ** PPCEEEPTR;

	struct _EEERef;
	typedef struct _EEERef EEERef, _eeeref_t, EEEREF, * PEEEREF, & REEEREF, ** PPEEEREF, && RREEEREF;
	typedef const struct _EEERef CEEEREF ,* PCEEEREF, & RCEEEREF, ** PPCEEEREF;

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


#pragma region [_EEERef] DEFINITION

struct _EEERef : public EERef
{
public:

	// CONSTRUCTOR

	_EEERef(RCWORD addr) : EERef(0)
	{
		this->index = addr;
	}


	// EERef METHOD HIDES

	BYTE operator *() const
	{
		PrintLine("*");
		return this->Read((CWORD)this->index);
	}

	REEEREF operator =(RCBYTE value)
	{
		PrintLine("=");
		this->Write((DWORD)this->index, value);
		return *this;
	}


protected:

	BYTE Read(RCWORD addr) const
	{
		PrintLine("EEEREAD");
		Wire.beginTransmission(0x50);

		Wire.write((BYTE)(addr >> 8));
		Wire.write((BYTE)addr);

		Wire.endTransmission();
		delay(5);
		
		BYTE value = 0;

		Wire.requestFrom(0x50, 1);
		if (!Wire.available()) delay(50);

		return Wire.read(); 
	}

	VOID Write(RCDWORD addr, RCBYTE value)
	{
		PrintLine("EEEWRITE");
		Wire.beginTransmission(0x50);

		Wire.write((BYTE)(addr >> 8));
		Wire.write((BYTE)addr);

		Wire.write(value);

		Wire.endTransmission();
		delay(50);
	}
};

#pragma endregion


#pragma region [_EEEPtr] DEFINITION

struct _EEEPtr //: public EEPtr
{
	// CONSTRUCTOR
	
	_EEEPtr(RCWORD addr) : Address(addr) { }


	// OPERATORS
		
	operator RCWORD() const
	{
		return this->Address;
	}

	BOOL operator !=(RCEEEPTR ptr)
	{
		return this->Address != ptr.Address;
	}

	EEEREF operator *()
	{
		return EEERef(this->Address);
	}
	
	REEEPTR operator =(RCWORD addr)
	{
		this->Address = addr;
		return *this;
	}

	REEEPTR operator ++()
	{
		++this->Address;
		return *this;
	}

	REEEPTR operator --()
	{
		--this->Address;
		return *this;
	}

	EEEPTR operator ++(INT)
	{
		return _EEEPtr(this->Address++);
	}

	EEEPTR operator --(INT)
	{
		return _EEEPtr(this->Address--);
	}

	// INSTANCE VARIABLES

	WORD Address = 0;
};

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

		STATIC CONSTEXPR CBYTE Length()
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

		EEPROM_I2C()
		{
			Wire.begin();
		}


		// OPERATORS

		EEEREF operator[](RCWORD addr)
		{
			return EEERef(addr);
		}		


		// ITERATOR METHODS

		EEEPTR begin()
		{
			return EEEPtr(0);
		} 

		EEEPTR end() const
		{
			return EEEPtr(Length());
		} 


		// USER METHODS
		
		BYTE Read(RCWORD addr) const
		{
			return *EEERef(addr);
		}
	
		VOID Write(RCWORD addr, RCBYTE value)
		{
			EEERef ref(addr);
			ref = value;
		}

		VOID Update(RCWORD addr, RCBYTE value)
		{
			EEERef(addr).update(value);
		}
		
		template<typename T>
		CSIZE Load(RCWORD addr, T& datum) const
		{
			EEEPTR ptr(addr);
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < SIZEOF(T))
				data[i++] = *ptr++;

			return i;
		}
	
		template<typename T>
		CSIZE Save(RCWORD addr, CONST T & datum)
		{
			EEEPTR ptr(addr);
			PCBYTE data = reinterpret_cast<PCBYTE>(&datum);

			SIZE i = 0;

			while (i < SIZEOF(T))
				(*ptr++).update(data[i++]);

			return i;
		}


	protected:

	};

#pragma endregion
}
	

#pragma region GLOBAL VARIABLES	

EXTERN IttyBitty::EEPROMI2C<> ExtEEPROM;

#pragma endregion

#endif
