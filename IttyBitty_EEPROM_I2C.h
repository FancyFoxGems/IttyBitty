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


#pragma region [_EEEPtr] DEFINITION

	template<CBYTE DeviceAddr, CBYTE PageAddrBits, typename TAddr>
	struct _EEEPtr //: public EEPtr
	{
	protected:

		// META-TYPEDEF ALIAS
		// META-TYPEDEF ALIAS

		typedef _EEEPtr<DeviceAddr, PageAddrBits, TAddr> TEEEPtr, TEEEPTR, & RTEEEPTR;
		typedef const _EEEPtr<DeviceAddr, PageAddrBits, TAddr> CTEEEPTR, & RCTEEEPTR;

		typedef _EEERef<DeviceAddr, PageAddrBits, TAddr> TEEERef, TEEEREF;


	public:

		// CONSTRUCTORS
	
		_EEEPtr(TAddr addr) : Address(addr) { }


		// OPERATORS
		
		operator CBYTE()
		{
			return **this;
		}
		
		operator RCWORD() const
		{
			return this->Address;
		}

		CBOOL operator ==(RCTEEEPTR ptr) const
		{
			return this->Address == ptr.Address;
		}

		CBOOL operator !=(RCTEEEPTR ptr) const
		{
			return this->Address != ptr.Address;
		}

		TEEEREF operator *()
		{
			return TEEERef(this->Address);
		}
	
		RTEEEPTR operator =(RCWORD addr)
		{
			this->Address = addr;
			return *this;
		}

		RTEEEPTR operator ++()
		{
			++this->Address;
			return *this;
		}

		RTEEEPTR operator --()
		{
			--this->Address;
			return *this;
		}

		TEEEPTR operator ++(INT)
		{
			return TEEEPtr(this->Address++);
		}

		TEEEPTR operator --(INT)
		{
			return TEEEPtr(this->Address--);
		}
	
	
		// INSTANCE VARIABLES

		TAddr Address = 0;
	};

#pragma endregion


#pragma region [_EEERef] DEFINITION

	template<CBYTE DeviceAddr, CBYTE PageAddrBits, typename TAddr>
	struct _EEERef //: public EERef
	{
	protected:
		
		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE GetPageBitsFromAddress(TAddr address)
		{
			return HIGH_BYTE(address) SHL 0b1 OR (0b1 SHL (PageAddrBits + 0b1) - 1);
			return NAND(MAX_T(TAddr), HIGH_BYTE(address) SHL 0b1);
		}

		STATIC CONSTEXPR CBYTE BuildDeviceAddressByte(TAddr address)
		{
			return DeviceAddr OR GetPageBitsFromAddress();
		}

		STATIC CONSTEXPR CBOOL UseWordDataAddress()
		{
			return (SIZEOF(TAddr) - (PageAddrBits > 0 ? 1 : 0)) > 1 ? TRUE : FALSE;
		}


		// META-TYPEDEF ALIAS

		typedef _EEERef<DeviceAddr, PageAddrBits, TAddr> TEEERef, TEEEREF, & RTEEEREF;
		typedef const _EEERef<DeviceAddr, PageAddrBits, TAddr> CTEEEREF, & RCTEEEREF;


	public:

		// CONSTRUCTORS
	
		_EEERef(TAddr addr) : Address(addr) { }


		// OPERATORS
	
		operator CBYTE() const
		{
			return **this;
		}
	
		operator RCWORD() const
		{
			return this->Address;
		}

		CBYTE operator *() const
		{
			return this->Read();
		}

		CBOOL operator ==(RCBYTE value) const
		{
			return *this == value;
		}

		CBOOL operator !=(RCBYTE value) const
		{
			return *this != value;
		}

		RTEEEREF operator =(RCBYTE value)
		{
			this->Write(value);
			return *this;
		}

		RTEEEREF operator =(RCTEEEREF ref)
		{
			return *this = *ref;
		}

		RTEEEREF operator +=(RCBYTE value)
		{
			return *this = **this + value;
		}

		RTEEEREF operator -=(RCBYTE value)
		{
			return *this = **this - value;
		}

		RTEEEREF operator *=(RCBYTE value)
		{
			return *this = **this * value;
		}

		RTEEEREF operator /=(RCBYTE value)
		{
			return *this = **this / value;
		}

		RTEEEREF operator ^=(RCBYTE value)
		{
			return *this = **this ^ value;
		}

		RTEEEREF operator %=(RCBYTE value)
		{
			return *this = **this % value;
		}

		RTEEEREF operator &=(RCBYTE value)
		{
			return *this = **this & value;
		}

		RTEEEREF operator |=(RCBYTE value)
		{
			return *this = **this | value;
		}

		RTEEEREF operator <<=(RCBYTE value)
		{
			return *this = **this << value;
		}

		RTEEEREF operator >>=(RCBYTE value)
		{
			return *this = **this >> value;
		}
	
		RTEEEREF operator++()
		{
			return *this += 1;
		}
		RTEEEREF operator--()
		{
			return *this -= 1;
		}
	
		CBYTE operator ++(INT)
		{ 
			BYTE value = **this;
			++(*this);
			return value;
		}

		CBYTE operator --(INT)
		{ 
			BYTE value = **this;
			--(*this);
			return value;
		}
	

		// USER METHODS
	
		RTEEEREF Update(RCBYTE value)
		{
			if (**this != value)
				*this = value;

			return *this;
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
	
	
		// INSTANCE VARIABLES

		TAddr Address = 0;
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
		
		typedef _EEEPtr<GetDeviceAddress(), PageAddressBits(), TAddr> TEEEPtr, TEEEPTR;
		typedef _EEERef<GetDeviceAddress(), PageAddressBits(), TAddr> TEEERef, TEEEREF;


	public:

		// STATIC CONSTEXPR METHODS
		
		STATIC CONSTEXPR CWORD CapacityKb()
		{
			return (CWORD)ChipType;
		}

		STATIC CONSTEXPR CBYTE Size()
		{
			return CapacityKb() * KILO * BITS_PER_BYTE * KILO;
		}
		
		STATIC CONSTEXPR CWORD (*CapacityBytes)() = &Size;
		
		STATIC CONSTEXPR CBYTE BytesPerPageWrite()
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

		TEEEREF operator[](TAddr addr)
		{
			return TEEERef(addr);
		}		


		// ITERATOR METHODS

		TEEEPTR begin()
		{
			return TEEEPtr(0);
		} 

		TEEEPTR end() const
		{
			return TEEEPtr(Size());
		} 


		// USER METHODS

		VOID Update(TAddr addr, RCBYTE value)
		{
			TEEERef(addr).Update(value);
		}
	
		VOID Write(TAddr addr, RCBYTE value)
		{
			TEEERef(addr).Write(value);
		}
		
		BYTE Read(TAddr addr) const
		{
			return *TEEERef(addr);
		}
		
		template<typename T>
		CSIZE Load(TAddr addr, T & datum) const
		{
			TEEEPTR ptr(addr);
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < SIZEOF(T))
				data[i++] = *ptr++;

			return i;
		}
	
		template<typename T>
		CSIZE Save(TAddr addr, CONST T & datum)
		{
			TEEEPTR ptr(addr);
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
