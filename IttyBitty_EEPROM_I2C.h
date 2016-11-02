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
	using EEEPTR = _EEEPtr<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PEEEPtr = _EEEPtr<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using REEEPtr = _EEEPtr<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPEEEPtr = _EEEPtr<DeviceAddr, UseWordAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RREEEPtr = _EEEPtr<DeviceAddr, UseWordAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using CEEEPtr = const _EEEPtr<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PCEEEPtr = const _EEEPtr<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RCEEEPtr = const _EEEPtr<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPCEEEPtr = const _EEEPtr<DeviceAddr, UseWordAddr> **;

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	struct _EEERef;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using EEERef = _EEERef<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using EEEREF = _EEERef<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PEEEREF = _EEERef<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using REEEREF = _EEERef<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPEEEREF = _EEERef<DeviceAddr, UseWordAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RREEEREF = _EEERef<DeviceAddr, UseWordAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using CEEEREF = const _EEERef<DeviceAddr, UseWordAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PCEEEREF = const _EEERef<DeviceAddr, UseWordAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using RCEEEREF = const _EEERef<DeviceAddr, UseWordAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, CBOOL UseWordAddr = FALSE>
	using PPCEEEREF = const _EEERef<DeviceAddr, UseWordAddr> **;

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
	
	EXPLICIT _EEEPtrBase(RCWORD);


	// OPERATORS
		
	operator CBYTE();
	operator RCWORD() const;

	VIRTUAL EEEREFBASE operator *();
	
	CBOOL operator ==(RCEEEPTRBASE) const;
	CBOOL operator !=(RCEEEPTRBASE) const;
	
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

	EXPLICIT _EEERefBase(RCWORD);


	// OPERATORS
	
	operator CBYTE() const;
	operator RCWORD() const;

	CBYTE operator *() const;

	CBOOL operator ==(RCBYTE) const;
	CBOOL operator !=(RCBYTE) const;

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
	
	CBYTE operator ++(INT);
	CBYTE operator --(INT);

	
	// USER METHODS
	
	REEEREFBASE Update(RCBYTE);

	
	// HELPER METHODS

	VIRTUAL CBYTE Read() const;
	VIRTUAL VOID Write(RCBYTE);
	
	
	// INSTANCE VARIABLES

	WORD Address = 0;
};

#pragma endregion


#pragma region [_EEEPtr] DEFINITION

template<CBYTE DeviceAddr, CBOOL UseWordAddr>
struct _EEEPtr : public _EEEPtrBase
{
public:

	// OPERATORS
		
	//operator CWORD() const;


	// _EEEPtrBase OPERATOR OVERRIDES

	VIRTUAL EEEREFBASE operator *()
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
	
	_EEERef(RCWORD addr) : _EEERefBase(addr) { }

	
	// HELPER METHOD OVERRIDES

	VIRTUAL CBYTE Read() const
	{
		PrintLine("EEEREAD");
		Wire.beginTransmission(0x50);

		Wire.write((BYTE)(this->Address >> 8));
		Wire.write((BYTE)this->Address);

		Wire.endTransmission();
		delay(5);
		
		BYTE value = 0;

		Wire.requestFrom(0x50, 1);
		if (!Wire.available()) delay(50);

		return Wire.read(); 
	}

	VIRTUAL VOID Write(RCBYTE value)
	{
		PrintLine("EEEWRITE");
		Wire.beginTransmission(0x50);

		Wire.write((BYTE)(this->Address >> 8));
		Wire.write((BYTE)this->Address);
		delay(5);
		
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
	protected:

		// PROTECTED CLASS VARIABLES

		STATIC BYTE _PageBits;

		
		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE GetPageBitsFromAddress(RCDWORD address)
		{
			return address > (CDWORD)0xFFFF;
		}

		STATIC CONSTEXPR CBYTE BuildDeviceAddressByte()
		{
			return SERIAL_EEPROM_DEFAULT_I2C_ADDRESS;
		}


		// META-TYPEDEF ALIASES

		typedef TYPE_IF(((CBYTE)ChipType >= 1024), RCDWORD, TYPE_IF(((CBYTE)ChipType >= 32), RCWORD, RCBYTE)) TAddr;
		
		typedef _EEEPtr<BuildDeviceAddressByte(), TRUE> teeeptr_yes_t;
		typedef _EEEPtr<BuildDeviceAddressByte(), FALSE> teeeptr_no_t;
		typedef TYPE_IF((CBYTE)ChipType >= 32, teeeptr_yes_t, teeeptr_no_t) TEEEPtr;
				
		typedef _EEERef<BuildDeviceAddressByte(), TRUE> teeeref_yes_t;
		typedef _EEERef<BuildDeviceAddressByte(), FALSE> teeeref_no_t;
		typedef TYPE_IF((CBYTE)ChipType >= 32, teeeref_yes_t, teeeref_no_t) TEEERef;


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

		TEEERef operator[](RCWORD addr)
		{
			return TEEERef(addr);
		}		


		// ITERATOR METHODS

		TEEEPtr begin()
		{
			return TEEEPtr(0);
		} 

		TEEEPtr end() const
		{
			return TEEEPtr(Length());
		} 


		// USER METHODS
		
		BYTE Read(RCWORD addr) const
		{
			return *TEEERef(addr);
		}
	
		VOID Write(RCWORD addr, RCBYTE value)
		{
			TEEERef(addr).Write(value);
		}

		VOID Update(RCWORD addr, RCBYTE value)
		{
			TEEERef(addr).Update(value);
		}
		
		template<typename T>
		CSIZE Load(RCWORD addr, T & datum) const
		{
			TEEEPtr ptr(addr);
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < SIZEOF(T))
				data[i++] = *ptr++;

			return i;
		}
	
		template<typename T>
		CSIZE Save(RCWORD addr, CONST T & datum)
		{
			TEEEPtr ptr(addr);
			PCBYTE data = reinterpret_cast<PCBYTE>(&datum);

			SIZE i = 0;

			while (i < SIZEOF(T))
				(*ptr++).Update(data[i++]);

			return i;
		}
	};

#pragma endregion
}
	

#pragma region GLOBAL VARIABLES	

EXTERN IttyBitty::EEPROMI2C<> ExtEEPROM;

#pragma endregion

#endif
