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

	struct _EEEPtrBase;
	typedef struct _EEEPtrBase EEEPtrBase, _eeeptr_base_t, EEEPTRBASE, * PEEEPTRBASE, & REEEPTRBASE, ** PPEEEPTRBASE, && RREEEPTRBASE;
	typedef const struct _EEEPtrBase CEEEPTRBASE ,* PCEEEPTRBASE, & RCEEEPTRBASE, ** PPCEEEPTRBASE;

	struct _EEERefBase;
	typedef struct _EEERefBase EEERefBase, _eeeref_base_t, EEEREFBASE, * PEEEREFBASE, & REEEREFBASE, ** PPEEEREFBASE, && RREEEREFBASE;
	typedef const struct _EEERefBase CEEEREFBASE ,* PCEEEREFBASE, & RCEEEREFBASE, ** PPCEEEREFBASE;

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	struct _EEEPtr;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using EEEPtr = _EEEPtr<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using EEEPtr = EEEPtr<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PEEEPtr = EEEPtr<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using REEEPtr = EEEPtr<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPEEEPtr = EEEPtr<DeviceAddr, UseWordAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RREEEPtr = EEEPtr<DeviceAddr, UseWordAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using CEEEPtr = const EEEPtr<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PCEEEPtr = const EEEPtr<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RCEEEPtr = const EEEPtr<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPCEEEPtr = const EEEPtr<DeviceAddr, UseWordAddr> **;

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	struct _EEERef;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using EEERef = _EEERef<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using EEEREF = EEERef<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PEEEREF = EEERef<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using REEEREF = EEERef<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPEEEREF = EEERef<DeviceAddr, UseWordAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RREEEREF = EEERef<DeviceAddr, UseWordAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using CEEEREF = const EEERef<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PCEEEREF = const EEERef<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RCEEEREF = const EEERef<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPCEEEREF = const EEERef<DeviceAddr, UseWordAddr> **;

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


#pragma region [_EEEPtrBase] DECLARATION

struct _EEEPtrBase //: public EEPtr
{
public:

	// CONSTRUCTOR
	
	_EEEPtrBase(RCWORD);


	// OPERATORS
		
	operator RCWORD() const;

	BOOL operator !=(RCEEEPTRBASE) const;

	VIRTUAL EEEREFBASE operator *() const;
	
	REEEPTRBASE operator =(RCWORD);

	REEEPTRBASE operator ++();
	REEEPTRBASE operator --();

	VIRTUAL EEEPTRBASE operator ++(INT);
	VIRTUAL EEEPTRBASE operator --(INT);


	// INSTANCE VARIABLES

	WORD Address = 0;
};

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

	
	// USER METHODS
	
	REEEREFBASE Update(RCBYTE);
	
	
	// INSTANCE VARIABLES

	WORD Address = 0;


protected:
	
	// HELPER METHODS

	VIRTUAL CBYTE Read(RCWORD) const;
	VIRTUAL VOID Write(RCDWORD, RCBYTE);
};

#pragma endregion


#pragma region [_EEEPtr] DEFINITION

template<CBYTE DeviceAddr, CBOOL UseWordAddr>
struct _EEEPtr : public _EEEPtrBase
{
public:

	// _EEEPtrBase OPERATOR OVERRIDES
		
	operator RCWORD() const;

	BOOL operator !=(RCEEEPTRBASE) const;

	VIRTUAL EEEREFBASE operator *() const
	{
		return _EEERef<DeviceAddr, UseWordAddr>(this->Address);
	}

	VIRTUAL EEEPTRBASE operator ++(INT)
	{
		return _EEEPtr<DeviceAddr, UseWordAddr>(this->Address++);
	}

	VIRTUAL EEEPTRBASE operator --(INT)
	{
		return _EEEPtr<DeviceAddr, UseWordAddr>(this->Address--);
	}
};

#pragma endregion


#pragma region [_EEERef] DEFINITION

template<CBYTE DeviceAddr, CBOOL UseWordAddr>
struct _EEERef : public _EEERefBase
{
public:

	// CONSTRUCTOR

	_EEERef(RCWORD addr, RCBIT setPageBit = FALSE) : _EEERefBase(addr), _SetPageBit(setPageBit) { }

	
protected:

	// INSTANCE VARIABLES

	CBIT _SetPageBit = FALSE;

	
	// HELPER METHOD OVERRIDES

	VIRTUAL CBYTE Read(RCWORD addr) const
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

	VIRTUAL VOID Write(RCDWORD addr, RCBYTE value)
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
		
		STATIC CONSTEXPR CWORD (*CapacityBytes)() = &Length;
		
		STATIC CONSTEXPR CBYTE BytesPerPage()
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

		EEEREFBASE operator[](RCWORD addr)
		{
			return EEERefBase(addr);
		}		


		// ITERATOR METHODS

		EEEPTRBASE begin()
		{
			return EEEPtrBase(0);
		} 

		EEEPTRBASE end() const
		{
			return EEEPtrBase(Length());
		} 


		// USER METHODS
		
		BYTE Read(RCWORD addr) const
		{
			return *EEERefBase(addr);
		}
	
		VOID Write(RCWORD addr, RCBYTE value)
		{
			EEEREFBASE ref(addr);
			ref = value;
		}

		VOID Update(RCWORD addr, RCBYTE value)
		{
			EEERefBase(addr).Update(value);
		}
		
		template<typename T>
		CSIZE Load(RCWORD addr, T & datum) const
		{
			EEEPTRBASE ptr(addr);
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < SIZEOF(T))
				data[i++] = *ptr++;

			return i;
		}
	
		template<typename T>
		CSIZE Save(RCWORD addr, CONST T & datum)
		{
			EEEPTRBASE ptr(addr);
			PCBYTE data = reinterpret_cast<PCBYTE>(&datum);

			SIZE i = 0;

			while (i < SIZEOF(T))
				(*ptr++).Update(data[i++]);

			return i;
		}


	protected:

		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBIT GetPageBitFromAddress(RCDWORD address)
		{
			return address > (CDWORD)0xFFFF;
		}

		STATIC CONSTEXPR CBYTE BuildDeviceAddressByte()
		{
			return SERIAL_EEPROM_DEFAULT_I2C_ADDRESS;
		}
	};

#pragma endregion
}
	

#pragma region GLOBAL VARIABLES	

EXTERN IttyBitty::EEPROMI2C<> ExtEEPROM;

#pragma endregion

#endif
