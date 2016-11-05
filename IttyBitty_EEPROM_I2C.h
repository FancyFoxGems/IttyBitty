/***********************************************************************************************
* [IttyBitty_EEPROM_I2C.h]: EXTERNAL EEPROM CHIP SUPPORT
*	(i.e. Atmel AT24CXXX /  Microchip 24LCXXX Series) 
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#if !defined(ARDUINO) && !defined(ITTYBITTY_EEPROM_I2C_H)
	#define ITTYBITTY_EEPROM_I2C_H
#endif

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

#define SERIAL_EEPROM_ERASE_VALUE			0xFF

#pragma endregion


#pragma region MACROS/ALIASES

#ifdef ARDUINO_SAM_DUE
	#define Wire		Wire1
#endif

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
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	struct _EEEPtr;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using EEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using EEEPTR = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PEEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using REEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PPEEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using RREEEPtr = _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using CEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using RCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PPCEEEPtr = const _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;

	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	struct _EEERef;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using EEERef = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using EEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PEEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using REEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PPEEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> **;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using RREEEREF = _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &&;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using CEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using PCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> *;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	using RCEEEREF = const _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> &;
	template<CBYTE DeviceAddr = SERIAL_EEPROM_DEFAULT_I2C_ADDRESS, 
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
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
		
		typedef TAddr & RTADDR;
		typedef const TAddr & RCTADDR;

		typedef _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEEPtr, TEEEPTR, & RTEEEPTR;
		typedef const TEEEPtr CTEEEPTR, & RCTEEEPTR;

		typedef _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEERef, TEEEREF;


	public:

		// CONSTRUCTORS
	
		_EEEPtr(RCTADDR addr) : Address(addr) { }


		// OPERATORS
		
		operator CBYTE() const
		{
			return (CBYTE)**this;
		}
		
		operator RCTADDR() const
		{
			return this->Address;
		}

		TEEEREF operator *()
		{
			return TEEERef(this->Address);
		}

		CBOOL operator ==(RCTEEEPTR ptr) const
		{
			return this->Address == ptr.Address;
		}

		CBOOL operator !=(RCTEEEPTR ptr) const
		{
			return this->Address != ptr.Address;
		}
	
		RTEEEPTR operator =(RCTADDR addr)
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

		STATIC CONSTEXPR CSIZE PageSize()
		{
			return UseWordDataAddress() ? 2 ^ BIT_SIZE(BYTE) : 2 ^ BIT_SIZE(WORD);
		}


		// META-TYPEDEF ALIAS

		typedef const TAddr & RCTADDR;

		typedef _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEERef, TEEEREF, & RTEEEREF;
		typedef const TEEERef CTEEEREF, & RCTEEEREF;


	public:

		// CONSTRUCTORS
	
		_EEERef(RCTADDR addr) : Address(addr) { }


		// OPERATORS
	
		operator CBYTE() const
		{
			return **this;
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

		CBYTE GetDataAddressMSB() const
		{
			return (CBYTE)(UseWordDataAddress() ? this->Address SHR 2 * BITS_PER_BYTE : this->Address SHR BITS_PER_BYTE);
		}

		CBYTE GetPageBitsFromAddress() const
		{
			return GetDataAddressMSB() SHL 0b1;
		}

		CBYTE BuildDeviceAddressWord(RCBOOL setReadFlag = FALSE) const
		{
			return DeviceAddr OR GetPageBitsFromAddress() OR ((CBYTE)setReadFlag);
		}

		CBYTE WaitForReady() const
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

		CBYTE SendDeviceAddressWord(RCBOOL waitForReady = TRUE) const
		{
			if (waitForReady)
			{
				BYTE errCode = this->WaitForReady();
				if (errCode)
					return errCode;
			}

			Wire.beginTransmission(BuildDeviceAddressWord());

			return 0;
		}

		CBYTE SendAddressWords(RCBOOL waitForReady = TRUE) const
		{			
			BYTE errCode = this->SendDeviceAddressWord(waitForReady);
			if (errCode)
				return errCode;

			if (UseWordDataAddress())
				WIRE_WRITE((BYTE)(this->Address SHR BITS_PER_BYTE));
			WIRE_WRITE((BYTE)this->Address);
		}


	public:
			
		// USER METHODS

		CBYTE Read() const
		{			
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;

			errCode = Wire.endTransmission();
			if (errCode)
				return errCode;
			
			Wire.requestFrom((BYTE)BuildDeviceAddressWord(), (BYTE)1);

			return (BYTE)WIRE_READ(); 
		}
		
		CSIZE Read(PBYTE data, CSIZE size)
		{
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;

			errCode = Wire.endTransmission();
			if (errCode)
				return errCode;

			Wire.requestFrom((INT)BuildDeviceAddressWord(), (INT)size, FALSE);

			SIZE bytesRead = 0;

			while (bytesRead < size)
			{
				data[bytesRead++] = (BYTE)WIRE_READ();
				
				++this->Address;

				if (this->Address % PageSize() == 0 && bytesRead < size)
				{
					if (Wire.endTransmission() || this->SendAddressWords())
						return bytesRead;

					Wire.requestFrom((INT)BuildDeviceAddressWord(), (INT)(size - bytesRead), FALSE);
				}
			}

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
			SIZE bytesWritten = 0;

			while (bytesWritten < size)
			{
				if (bytesWritten % PageWriteBytes == 0 || this->Address % PageSize() == 0)
				{
					if (bytesWritten > 0 && Wire.endTransmission())
						return bytesWritten;

					if (this->SendAddressWords(bytesWritten == 0))
						return bytesWritten;
				}

				WIRE_WRITE(data[bytesWritten++]);

				++this->Address;
			}
			
			Wire.endTransmission();

			return bytesWritten;
		}
	
		CBYTE Update(RCBYTE value)
		{
			if (**this != value)
				*this = value;

			return *this;
		}
		
		CSIZE Update(PCBYTE data, CSIZE size)
		{						
			SIZE bytesWritten = 0;

			while (bytesWritten < size)
			{
				this->Update(data[bytesWritten++]);

				++this->Address;
			}

			return bytesWritten;
		}
	
		CBYTE Erase(CSIZE size)
		{
			PBYTE nullBuffer = new BYTE[size];
			memset(nullBuffer, SERIAL_EEPROM_ERASE_VALUE, size);

			CBYTE bytesErased = this->Write(nullBuffer, size);

			delete[] nullBuffer;

			return bytesErased;
		}
	};

#pragma endregion


#pragma region [EEPROM_I2C] DEFINITION

	template<SerialEEPROMChipFamily ChipType, CBYTE DeviceNum>
	class EEPROM_I2C
	{
	public:
		
		// STATIC CONSTEXPR METHODS
		
		STATIC CONSTEXPR CSIZE CapacityKb()
		{
			return (CSIZE)ChipType;
		}
		

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

		typedef TYPE_IF((CapacityKb() >= 0x0400), DWORD, TYPE_IF((CapacityKb() >= 0x0004), WORD, BYTE)) TAddr, & RTADDR;
		typedef const TAddr CTADDR, & RCTADDR;
		
		typedef _EEEPtr<GetDeviceAddress(), PageAddressBits(), BytesPerPageWrite(), TAddr> TEEEPtr, TEEEPTR, & RTEEEPTR;
		typedef const TEEEPtr & RCTEEEPTR;

		typedef _EEERef<GetDeviceAddress(), PageAddressBits(), BytesPerPageWrite(), TAddr> TEEERef, TEEEREF;
		typedef const TEEERef CTEEEREF;


	public:		
		
		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CTADDR Size()
		{
			return CapacityKb() * KILObit / BITS_PER_BYTE;
		}
		
		STATIC CONSTEXPR CTADDR (*CapacityBytes)() = &Size;

		
		// STATIC CONSTEXPR FUNCTION ALIASES

		STATIC CONSTEXPR CSIZE (*PageSize)() = &TEEERef::PageSize();


		// INSTANCE VARIABLES

		TEEEPTR _Iterator;


		// CONSTRUCTOR

		EEPROM_I2C(RCBOOL use400KHz = FALSE, RCTADDR startAddr = (CTADDR)0) : _Iterator(TEEEPtr(startAddr))
		{
			Wire.begin();

			if (use400KHz)
				TWBR = (CBYTE)((F_CPU / 400 * kilo) - 16) / 2;
		}


		// OPERATORS

		operator RCTEEEPTR() const
		{
			return _Iterator;
		}

		operator RTEEEPTR()
		{
			return _Iterator;
		}

		TEEEREF operator *()
		{
			return TEEERef(this->Address);
		}

		CTEEEREF operator[](RCTADDR addr) const
		{
			return TEEERef(addr);
		}

		TEEEREF operator[](RCTADDR addr)
		{
			return TEEERef(addr);
		}


		// ITERATOR METHODS

		CTADDR length() const
		{
			return EEPROM_I2C::Size();
		}

		TEEEPTR begin()
		{
			_Iterator = TEEEPtr(0);
			return _Iterator;
		}

		TEEEPTR curr()
		{
			return _Iterator;
		}

		TEEEPTR next()
		{
			return _Iterator++;
		}

		TEEEPTR end() const
		{
			return TEEEPtr(Size());
		}

		TEEEPTR seek(RCTADDR addr)
		{
			(RTADDR)_Iterator = addr;
			return _Iterator;
		}


		// USER METHODS
		
		CBYTE Read() const
		{
			return (*_Iterator).Read();
		}
		
		CBYTE Read(RCTADDR addr) const
		{
			this->seek(addr);
			return this->Read();
		}
		
		CSIZE Read(PBYTE buffer, CSIZE size) const
		{
			return (*_Iterator).Read(buffer, size);
		}
		
		CSIZE Read(PBYTE buffer, CSIZE size, RCTADDR addr) const
		{
			this->seek(addr);
			return this->Read(buffer, size);
		}
	
		CBYTE Write(RCBYTE value)
		{
			return (*_Iterator).Write(value);
		}
	
		CBYTE Write(RCBYTE value, RCTADDR addr)
		{
			this->seek(addr);
			return this->Write(value);
		}
	
		CSIZE Write(PCBYTE data, CSIZE size)
		{
			return (*_Iterator).Write(data, size);
		}
	
		CSIZE Write(PCBYTE data, CSIZE size, RCTADDR addr)
		{
			this->seek(addr);
			return this->Write(data, size);
		}
	
		CSIZE Write(PCCHAR data)
		{
			return (*_Iterator).Write(reinterpret_cast<PCBYTE>(data), strlen(data));
		}
	
		CSIZE Write(PCCHAR data, RCTADDR addr)
		{
			this->seek(addr);
			return this->Write(data, data);
		}

		CBYTE Update(RCBYTE value)
		{
			return (*_Iterator).Update(value);
		}

		CBYTE Update(RCBYTE value, RCTADDR addr)
		{
			this->seek(addr);
			return this->Update(value);
		}
	
		CSIZE Update(PCBYTE data, CSIZE size)
		{
			return (*_Iterator).Update(data, size);
		}
	
		CSIZE Update(PCBYTE data, CSIZE size, RCTADDR addr)
		{
			this->seek(addr);
			return this->Update(data, size);
		}
	
		CSIZE Update(PCCHAR data)
		{
			return (*_Iterator).Update(reinterpret_cast<PCBYTE>(data), strlen(data));
		}
	
		CSIZE Update(PCCHAR data, RCTADDR addr)
		{
			this->seek(addr);
			return this->Update(data, data);
		}

		CBYTE Erase(CSIZE size)
		{
			return (*_Iterator).Clear(size);
		}

		CBYTE Erase(CSIZE size, RCTADDR addr)
		{
			this->seek(addr);
			return this->Clear(size);
		}

		template<typename T>
		CSIZE Load(T & datum) const
		{
			PCBYTE data = reinterpret_cast<PBYTE>(&datum);

			SIZE i = 0;
			
			while (i < T_SIZE)
				data[i++] = *_Iterator++;

			return i;
		}

		template<typename T>
		CSIZE Load(RCTADDR addr, T & datum) const
		{
			this->seek(addr);
			return this->Load(datum);
		}
	
		template<typename T>
		CSIZE Save(CONST T & datum)
		{
			PCBYTE data = reinterpret_cast<PCBYTE>(&datum);

			SIZE i = 0;

			while (i < T_SIZE)
				(*_Iterator++).Update(data[i++]);

			return i;
		}
	
		template<typename T>
		CSIZE Save(RCTADDR addr, CONST T & datum)
		{
			this->seek(addr);
			return this->Save(datum);
		}
	};

#pragma endregion
}


#pragma region GLOBAL VARIABLES	

EXTERN IttyBitty::EEPROMI2C<> ExtEEPROM;

#pragma endregion

#endif
