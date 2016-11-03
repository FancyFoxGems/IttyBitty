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

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	struct _EEEPtr;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using EEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using EEEPTR = _EEEPtr<DeviceAddr, PageAddrBits, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PEEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using REEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PPEEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, TAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using RREEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, TAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using CEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using RCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PPCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, TAddr> **;

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	struct _EEERef;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using EEERef = _EEERef<DeviceAddr, PageAddrBits, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using EEEREF = _EEERef<DeviceAddr, PageAddrBits, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PEEEREF = _EEERef<DeviceAddr, PageAddrBits, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using REEEREF = _EEERef<DeviceAddr, PageAddrBits, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PPEEEREF = _EEERef<DeviceAddr, PageAddrBits, TAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using RREEEREF = _EEERef<DeviceAddr, PageAddrBits, TAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using CEEEREF = const _EEERef<DeviceAddr, PageAddrBits, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using RCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, typename TAddr = RCBYTE>
	using PPCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, TAddr> **;

	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	class EEPROM_I2C;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using EEPROMI2C = EEPROM_I2C<ChipType, DeviceNum>;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using PEEPROMI2C = EEPROM_I2C<ChipType, DeviceNum> *;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using REEPROMI2C = EEPROM_I2C<ChipType, DeviceNum> &;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using PPEEPROMI2C = EEPROM_I2C<ChipType, DeviceNum> **;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using RREEPROMI2C = EEPROM_I2C<ChipType, DeviceNum> &&;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using CEEPROMI2C = const EEPROM_I2C<ChipType, DeviceNum>;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using PCEEPROMI2C = const EEPROM_I2C<ChipType, DeviceNum> *;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using RCEEPROMI2C = const EEPROM_I2C<ChipType, DeviceNum> &;
	template<SerialEEPROMChipFamily ChipType = SerialEEPROMChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	using PPCEEPROMI2C = const EEPROM_I2C<ChipType, DeviceNum> **;

#pragma endregion


#pragma region [_EEEPtrBase] DECLARATION

	struct _EEEPtrBase //: public EEPtr
	{
	public:

		// CONSTRUCTORS
	
		EXPLICIT _EEEPtrBase(RCBYTE);
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

		// CONSTRUCTORS
	
		EXPLICIT _EEERefBase(RCBYTE);
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

	template<CBYTE DeviceAddr, CBYTE PageAddrBits, typename TAddr>
	struct _EEEPtr : public _EEEPtrBase
	{
	protected:

		// META-TYPEDEF ALIAS

		typedef _EEERef<DeviceAddr, PageAddrBits, TAddr> TEEERef;


	public:

		// OPERATORS
		
		//operator CWORD() const;


		// _EEEPtrBase OPERATOR OVERRIDES

		VIRTUAL EEEREFBASE operator *()
		{
			return TEEERef(this->Address);
		}

		VIRTUAL EEEPTRBASE operator ++(INT)
		{
			return TEEERef(this->Address++);
		}

		VIRTUAL EEEPTRBASE operator --(INT)
		{
			return TEEERef(this->Address--);
		}
	};

#pragma endregion


#pragma region [_EEERef] DEFINITION

	template<CBYTE DeviceAddr, CBYTE PageAddrBits, typename TAddr>
	struct _EEERef : public _EEERefBase
	{
	protected:
		
		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE GetPageBitsFromAddress(TAddr address)
		{
			return HIGH_BYTE(address) SHL 0b1 OR (0b1 SHL (PageAddrBits + 0b1) - 1);
			return NAND((TAddr(0) - 0b1), HIGH_BYTE(address) SHL 0b1);
		}

		STATIC CONSTEXPR CBYTE BuildDeviceAddressByte(TAddr address)
		{
			return DeviceAddr OR GetPageBitsFromAddress();
		}


		// META-TYPEDEF ALIAS

		typedef _EEEPtr<DeviceAddr, PageAddrBits, TAddr> TEEEPtr;


	public:

		// CONSTRUCTORS
	
		_EEERef(RCBYTE addr) : _EEERefBase(addr) { }

		_EEERef(RCWORD addr) : _EEERefBase(addr) { }

	
		// HELPER METHOD OVERRIDES

		VIRTUAL CBYTE Read() const
		{
			//return _EEERefBase::Read();
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
			//return _EEERefBase::Write(value);
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

	template<SerialEEPROMChipFamily ChipType, CBYTE DeviceNum>
	class EEPROM_I2C
	{
	protected:
		
		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE PageAddressBits()
		{
			return ((CBYTE)ChipType == 0x0010) ? 3 :
				((CBYTE)ChipType == 0x0008 || (CBYTE)ChipType == 0x0800) ? 2 :
					((CBYTE)ChipType == 0x0004 || (CBYTE)ChipType == 0x0400) ? 1 : 0;
		}

		STATIC CONSTEXPR CBYTE DeviceNumberBits()
		{
			return 3 - PageAddressBits();
		}

		STATIC CONSTEXPR CBYTE BuildDeviceNumberBits()
		{
			return DeviceNum SHL (PageAddressBits() + 0b1);
		}

		STATIC CONSTEXPR CBYTE GetDeviceAddress()
		{
			return SERIAL_EEPROM_DEFAULT_I2C_ADDRESS OR BuildDeviceNumberBits();
		}


		// META-TYPEDEF ALIASES

		typedef TYPE_IF(((CBYTE)ChipType >= 0x0400), RCDWORD, TYPE_IF(((CBYTE)ChipType >= 0x0004), RCWORD, RCBYTE)) TAddr;
		
		typedef _EEEPtr<GetDeviceAddress(), PageAddressBits(), TAddr> TEEEPtr;
		typedef _EEERef<GetDeviceAddress(), PageAddressBits(), TAddr> TEEERef;


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

		TEEERef operator[](TAddr addr)
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
		
		BYTE Read(TAddr addr) const
		{
			return *TEEERef(addr);
		}
	
		VOID Write(TAddr addr, RCBYTE value)
		{
			TEEERef(addr).Write(value);
		}

		VOID Update(TAddr addr, RCBYTE value)
		{
			TEEERef(addr).Update(value);
		}
		
		template<typename T>
		CSIZE Load(TAddr addr, T & datum) const
		{
			TEEEPtr ptr(addr);
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < SIZEOF(T))
				data[i++] = *ptr++;

			return i;
		}
	
		template<typename T>
		CSIZE Save(TAddr addr, CONST T & datum)
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
