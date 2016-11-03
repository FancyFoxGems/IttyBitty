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

using namespace IttyBitty;

#include "Wire.h"
#include "EEPROM.h"


#pragma region DEFINES

#define SERIAL_EEPROM_DEFAULT_I2C_ADDRESS	0x50

#define SERIAL_EEPROM_TIMEOUT_MS			500
#define SERIAL_EEPROM_WAIT_DELAY_MS			1

#pragma endregion


#pragma region MACROS

#if ARDUINO >= 100
	#define WIRE_WRITE	Wire.write
	#define WIRE_READ	Wire.read
#else
	#define WIRE_WRITE	Wire.send
	#define WIRE_READ	Wire.receive
#endif

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
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	struct _EEEPtr;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using EEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using EEEPTR = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PEEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using REEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PPEEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using RREEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using CEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using RCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PPCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	struct _EEERef;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using EEERef = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using EEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PEEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using REEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PPEEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using RREEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using CEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using RCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = RCBYTE>
	using PPCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;

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

	template<CBYTE DeviceAddr, CBYTE PageAddrBits, CSIZE PageWriteBytes, typename TAddr>
	struct _EEEPtr //: public EEPtr
	{
	protected:

		// META-TYPEDEF ALIAS
		// META-TYPEDEF ALIAS

		typedef _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEEPtr, TEEEPTR, & RTEEEPTR;
		typedef const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> CTEEEPTR, & RCTEEEPTR;

		typedef _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEERef, TEEEREF;


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

	template<CBYTE DeviceAddr, CBYTE PageAddrBits, CSIZE PageWriteBytes, typename TAddr>
	struct _EEERef //: public EERef
	{
	protected:
		
		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBOOL UseWordDataAddress()
		{
			return (SIZEOF(TAddr) - (PageAddrBits > 0 ? 1 : 0)) > 1 ? TRUE : FALSE;
		}


		// META-TYPEDEF ALIAS

		typedef _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEERef, TEEEREF, & RTEEEREF;
		typedef const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> CTEEEREF, & RCTEEEREF;


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
	
	
		// INSTANCE VARIABLES

		TAddr Address = 0;


	protected:

		// HELPER METHODS

		CBYTE GetPageBitsFromAddress()
		{
			return HIGH_BYTE(this->Address) SHL 0b1 OR (0b1 SHL (PageAddrBits + 0b1) - 1);
			return NAND(MAX_T(TAddr), HIGH_BYTE(this->Address) SHL 0b1);
		}

		BYTE BuildDeviceAddressWord(RCBOOL setReadFlag = FALSE)
		{
			return DeviceAddr OR GetPageBitsFromAddress() OR ((CBYTE)setReadFlag);
		}

		CBYTE WaitForReady()
		{
			BYTE errCode = 0;
			WORD currMS = millis();

			while (millis() - currMS <= SERIAL_EEPROM_TIMEOUT_MS)
			{
				Wire.beginTransmission(BuildDeviceAddressWord());

				errCode = Wire.endTransmission();
				if (!errCode)
					return 0;

				delay(SERIAL_EEPROM_WAIT_DELAY_MS);
			}

			return MAX_T(BYTE);
		}

		CBYTE SendDeviceAddressWord()
		{
			BYTE errCode = this->WaitForReady();
			if (errCode)
				return errCode;

			Wire.beginTransmission(BuildDeviceAddressWord());

			return 0;
		}

		CBYTE SendAddressWords()
		{			
			BYTE errCode = this->SendDeviceAddressWord();
			if (errCode)
				return errCode;

			if (UseWordDataAddress())
				WIRE_WRITE((BYTE)(this->Address SHR 8));
			WIRE_WRITE((BYTE)this->Address);
			
			return Wire.endTransmission();
		}


	public:
			
		// USER METHODS

		CBYTE Read()
		{			
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;

			Wire.beginTransmission(BuildDeviceAddressWord(TRUE));
			errCode = Wire.endTransmission();
			if (errCode)
				return errCode;
			
			Wire.requestFrom((BYTE)BuildDeviceAddressWord(TRUE), (BYTE)1);

			return (BYTE)WIRE_READ(); 
		}
		
		CSIZE Read(PBYTE data, CSIZE size)
		{
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;

			Wire.requestFrom((INT)BuildDeviceAddressWord(), (INT)size, FALSE);

			SIZE bytesRead = 0;

			while (bytesRead < size)
				data[bytesRead++] = (BYTE)WIRE_READ();

			return bytesRead;
		}

		CBYTE Write(RCBYTE value)
		{
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;
		
			WIRE_WRITE(value);

			return Wire.endTransmission();
		}
		
		CSIZE Write(PCBYTE data, CSIZE size)
		{
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;
						
			SIZE bytesWritten = 0;

			while (bytesWritten < size)
			{
				if (bytesWritten > 0 && bytesWritten % PageWriteBytes == 0)
				{
					if (Wire.endTransmission())
						return errCode;

					if (this->SendAddressWords())
						return bytesWritten;
				}

				WIRE_WRITE(data[bytesWritten++]);

				++this->Address;
			}

			return 0;
		}
	
		CBYTE Update(RCBYTE value)
		{
			if (**this != value)
				*this = value;

			return *this;
		}
	};

#pragma endregion


#pragma region [EEPROM_I2C] DEFINITION

	template<SerialEEPROMChipFamily ChipType, CBYTE DeviceNum>
	class EEPROM_I2C
	{
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
		

	protected:
		
		// PROTECTED STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE PageAddressBits()
		{
			return (CapacityKb() == 0x0010) ? 3 :
				(CapacityKb() == 0x0008 || CapacityKb() == 0x0800) ? 2 :
					(CapacityKb() == 0x0004 || CapacityKb() == 0x0400) ? 1 : 0;
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
		
		STATIC CONSTEXPR CBYTE BytesPerPageWrite()
		{
			return (CapacityKb() >= 0x0400) ? 256 :
				(CapacityKb() >= 0x0200) ? 128 :
					(CapacityKb() >= 0x0040) ? 64 :
						(CapacityKb() >= 0x0020) ? 32 :
							(CapacityKb() >= 0x0004) ? 16 : 8;
		}


		// META-TYPEDEF ALIASES

		typedef TYPE_IF((CapacityKb() >= 0x0400), DWORD, TYPE_IF((CapacityKb() >= 0x0004), WORD, BYTE)) TAddr;
		typedef const TAddr CTAddr;
		
		typedef _EEEPtr<GetDeviceAddress(), PageAddressBits(), BytesPerPageWrite(), TAddr> TEEEPtr, TEEEPTR;
		typedef _EEERef<GetDeviceAddress(), PageAddressBits(), BytesPerPageWrite(), TAddr> TEEERef, TEEEREF;
		typedef const _EEERef<GetDeviceAddress(), PageAddressBits(), BytesPerPageWrite(), TAddr> CTEEEREF;


	public:

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
		
		CBYTE Read(CTAddr addr)
		{
			return TEEERef(addr).Read();
		}
		
		CSIZE Read(CTAddr startAddr, PBYTE buffer, CSIZE size)
		{
			return TEEERef(startAddr).Read(buffer, size);
		}
	
		CBYTE Write(CTAddr addr, RCBYTE value)
		{
			return TEEERef(addr).Write(value);
		}
	
		CSIZE Write(CTAddr startAddr, PCBYTE data, CSIZE size)
		{
			return TEEERef(startAddr).Write(data, size);
		}

		CBYTE Update(CTAddr addr, RCBYTE value)
		{
			return TEEERef(addr).Update(value);
		}
		
		template<typename T>
		CSIZE Load(CTAddr addr, T & datum) const
		{
			TEEEPTR ptr(addr);
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < SIZEOF(T))
				data[i++] = *ptr++;

			return i;
		}
	
		template<typename T>
		CSIZE Save(CTAddr addr, CONST T & datum)
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
