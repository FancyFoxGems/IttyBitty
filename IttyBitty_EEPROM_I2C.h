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

	struct _EEERefBase;
	typedef struct _EEERefBase EEERef, EEEREF, * PEEEREF, & REEEREF, ** PPEEEREF, && RREEEREF; // TODO
	typedef struct _EEERefBase EEERefBase, _eeeref_base_t, EEEREFBASE, * PEEEREFBASE, & REEEREFBASE, ** PPEEEREFBASE, && RREEEREFBASE;
	typedef const struct _EEERefBase CEEEREFBASE ,* PCEEEREFBASE, & RCEEEREFBASE, ** PPCEEEREFBASE;

	struct _EEEPtr;
	typedef struct _EEEPtr EEEPtr, _eeeptr_t, EEEPTR, * PEEEPTR, & REEEPTR, ** PPEEEPTR, && RREEEPTR;
	typedef const struct _EEEPtr CEEEPTR ,* PCEEEPTR, & RCEEEPTR, ** PPCEEEPTR;

	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	class EEPROM_I2C;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using EEPROMI2C = EEPROM_I2C<ChipType, I2CAddr, DeviceNum>;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using PEEPROMI2C = EEPROM_I2C<ChipType, I2CAddr, DeviceNum> *;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using REEPROMI2C = EEPROM_I2C<ChipType, I2CAddr, DeviceNum> &;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using PPEEPROMI2C = EEPROM_I2C<ChipType, I2CAddr, DeviceNum> **;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using RREEPROMI2C = EEPROM_I2C<ChipType, I2CAddr, DeviceNum> &&;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using CEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr, DeviceNum>;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using PCEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr, DeviceNum> *;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using RCEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr, DeviceNum> &;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, 
		CBYTE I2CAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBYTE DeviceNum = 0x0>
	using PPCEEPROMI2C = const EEPROM_I2C<ChipType, I2CAddr, DeviceNum> **;

#pragma endregion


#pragma region [_EEERefBase] DEFINITION

struct _EEERefBase //: public EERef
{
public:

	// CONSTRUCTOR

	_EEERefBase(RCWORD);


	// OPERATORS
	
	operator CBYTE() const;

	BYTE operator *() const;

	REEEREFBASE operator =(RCBYTE);
	REEEREFBASE operator =(RCEEEREFBASE);

	REEEREFBASE operator +=(RCBYTE);
	REEEREFBASE operator -=(RCBYTE);
	REEEREFBASE operator *=(RCBYTE);
	REEEREFBASE operator /=(RCBYTE);
	REEEREFBASE operator ^=(RCBYTE);
	REEEREFBASE operator %=(RCBYTE);
	REEEREFBASE operator &=(RCBYTE);
	REEEREFBASE operator |=(RCBYTE);
	REEEREFBASE operator <<=(RCBYTE);
	REEEREFBASE operator >>=(RCBYTE);
	
	REEEREFBASE operator++();
	REEEREFBASE operator--();
	
	BYTE operator ++(INT);
	BYTE operator --(INT);

	
	// USERMETHODS
	
	REEEREFBASE Update(RCBYTE);
	
	
	// INSTANCE VARIABLES

	WORD Address = 0;


protected:
	
	// HELPER METHODS

	CBYTE Read(RCWORD) const;
	VOID Write(RCDWORD, RCBYTE);
};

#pragma endregion


#pragma region [_EEEPtr] DECLARATION

struct _EEEPtr //: public EEPtr
{
public:

	// CONSTRUCTOR
	
	_EEEPtr(RCWORD);


	// OPERATORS
		
	operator RCWORD() const;

	BOOL operator !=(RCEEEPTR);

	EEEREF operator *();
	
	REEEPTR operator =(RCWORD);

	REEEPTR operator ++();
	REEEPTR operator --();

	EEEPTR operator ++(INT);
	EEEPTR operator --(INT);


	// INSTANCE VARIABLES

	WORD Address = 0;
};

#pragma endregion


#pragma region [EEPROM_I2C] DEFINITION

	template<SerialEEPROMChipFamily ChipType, CBYTE I2CAddr, CBYTE DeviceNum>
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
			EEERef(addr).Update(value);
		}
		
		template<typename T>
		CSIZE Load(RCWORD addr, T & datum) const
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
				(*ptr++).Update(data[i++]);

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
