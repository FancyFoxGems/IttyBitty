/***********************************************************************************************
* [IttyBitty_EEPROM_I2C.h]: EXTERNAL EEPROM CHIP SUPPORT
*	(i.e. Atmel AT24CXXX /  Microchip 24LCXXX Series)
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_EEPROM_I2C_H
#define _ITTYBITTY_EEPROM_I2C_H


#include "IttyBitty_bits.h"

using namespace IttyBitty;

#include "Wire.h"
#include "EEPROM.h"


#pragma region DEFINES

#define SERIAL_EEPROM_I2C_ADDRESS		0x50

#define SERIAL_EEPROM_ERASE_VALUE		0xFF

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
#pragma region GLOBAL CONSTANT DECLARATIONS

	EXTERN CWORD SERIAL_EEPROM_TIMEOUT_MS;
	EXTERN CBYTE SERIAL_EEPROM_WAIT_DELAY_MS;

#pragma endregion


#pragma region ENUMS

	ENUM SerialEepromChipFamily : WORD
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

	TYPEDEF_ENUM_ALIASES(SerialEepromChipFamily, SERIALEEPROMCHIPFAMILY);

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	#define _EEEPTR_T_CLAUSE_DEF	<CBYTE DeviceAddr, CBYTE PageAddrBits, CSIZE PageWriteBytes, typename TAddr>
	#define _EEEPTR_T_CLAUSE		<CBYTE DeviceAddr = SERIAL_EEPROM_I2C_ADDRESS,	\
		CBYTE PageAddrBits = 0, CSIZE PageWriteBytes = 8, typename TAddr = BYTE>
	#define _EEEPTR_T_ARGS			<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr>

	template _EEEPTR_T_CLAUSE
	struct _EEEPtr;
	TEMPLATE_STRUCT_USING_ALIASES(CSL(_EEEPTR_T_CLAUSE), CSL(_EEEPTR_T_ARGS), EEEPtr, eeeptr, EEEPTR);


	#define _EEEREF_T_CLAUSE_DEF	_EEEPTR_T_CLAUSE_DEF
	#define _EEEREF_T_CLAUSE		_EEEPTR_T_CLAUSE
	#define _EEEREF_T_ARGS			_EEEPTR_T_ARGS

	template _EEEREF_T_CLAUSE
	struct _EEERef;
	TEMPLATE_STRUCT_USING_ALIASES(CSL(_EEEREF_T_CLAUSE), CSL(_EEEREF_T_ARGS), EEERef, eeeref, EEEREF);


	#define EEPROMI2C_T_CLAUSE_DEF	<CSERIALEEPROMCHIPFAMILY ChipType, CBYTE DeviceNum>
	#define EEPROMI2C_T_CLAUSE		<CSERIALEEPROMCHIPFAMILY ChipType = SerialEepromChipFamily::UNKNOWN_EEPROM_CHIP, CBYTE DeviceNum = 0x0>
	#define EEPROMI2C_T_ARGS		<ChipType, DeviceNum>

	template EEPROMI2C_T_CLAUSE
	class EEPROM_I2C;
	TEMPLATE_CLASS_USING_ALIASES(CSL(EEPROMI2C_T_CLAUSE), CSL(EEPROMI2C_T_ARGS), EEPROM_I2C, EEPROMI2C);

#pragma endregion


#pragma region [_EEEPtr] DEFINITION

	template _EEEPTR_T_CLAUSE_DEF
	struct _EEEPtr //: public EEPtr
	{
	protected:

		// META-TYPEDEF ALIAS

		typedef _EEEPtr<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEEPtr, TEEEPTR, & RTEEEPTR;
		typedef const TEEEPtr CTEEEPTR, & RCTEEEPTR;

		typedef _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEERef, TEEEREF;

		typedef TAddr TADDR;
		typedef const TAddr & RCTADDR;


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

		TADDR Address = 0;
	};

#pragma endregion


#pragma region [_EEERef] DEFINITION

	template _EEEREF_T_CLAUSE_DEF
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

		typedef _EEERef<DeviceAddr, PageAddrBits, PageWriteBytes, TAddr> TEEERef, TEEEREF, & RTEEEREF;
		typedef const TEEERef CTEEEREF, & RCTEEEREF;

		typedef TAddr TADDR;
		typedef const TAddr CTADDR, & RCTADDR;


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

		CBOOL operator ==(CBYTE value) const
		{
			return *this == value;
		}

		CBOOL operator !=(CBYTE value) const
		{
			return *this != value;
		}

		RTEEEREF operator =(CBYTE value)
		{
			this->Write(value);
			return *this;
		}

		RTEEEREF operator =(RCTEEEREF ref)
		{
			return *this = *ref;
		}

		RTEEEREF operator +=(CBYTE value)
		{
			return *this = **this + value;
		}

		RTEEEREF operator -=(CBYTE value)
		{
			return *this = **this - value;
		}

		RTEEEREF operator *=(CBYTE value)
		{
			return *this = **this * value;
		}

		RTEEEREF operator /=(CBYTE value)
		{
			return *this = **this / value;
		}

		RTEEEREF operator ^=(CBYTE value)
		{
			return *this = **this ^ value;
		}

		RTEEEREF operator %=(CBYTE value)
		{
			return *this = **this % value;
		}

		RTEEEREF operator &=(CBYTE value)
		{
			return *this = **this & value;
		}

		RTEEEREF operator |=(CBYTE value)
		{
			return *this = **this | value;
		}

		RTEEEREF operator <<=(CBYTE value)
		{
			return *this = **this << value;
		}

		RTEEEREF operator >>=(CBYTE value)
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

		TADDR Address = 0;


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

		CBYTE BuildDeviceAddressWord(CBOOL setReadFlag = FALSE) const
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

			return MAX_BYTE;
		}

		CBYTE SendDeviceAddressWord(CBOOL waitForReady = TRUE) const
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

		CBYTE SendAddressWords(CBOOL waitForReady = TRUE) const
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

		CTADDR Read(PBYTE data, RCTADDR size)
		{
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;

			errCode = Wire.endTransmission();
			if (errCode)
				return errCode;

			Wire.requestFrom((INT)BuildDeviceAddressWord(), (INT)size, FALSE);

			TADDR bytesRead = 0;

			while (bytesRead < size)
			{
				data[bytesRead++] = (BYTE)WIRE_READ();

				++this->Address;

				if (this->Address % PageSize() == 0 AND bytesRead < size)
				{
					if (Wire.endTransmission() OR this->SendAddressWords())
						return bytesRead;

					Wire.requestFrom((INT)BuildDeviceAddressWord(), (INT)(size - bytesRead), FALSE);
				}
			}

			return bytesRead;
		}

		CBYTE Write(CBYTE value)
		{
			BYTE errCode = this->SendAddressWords();
			if (errCode)
				return errCode;

			WIRE_WRITE(value);

			return Wire.endTransmission();
		}

		CTADDR Write(PCBYTE data, RCTADDR size)
		{
			TADDR bytesWritten = 0;

			while (bytesWritten < size)
			{
				if (bytesWritten % PageWriteBytes == 0 OR this->Address % PageSize() == 0)
				{
					if (bytesWritten > 0 AND Wire.endTransmission())
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

		CBYTE Update(CBYTE value)
		{
			if (**this != value)
				*this = value;

			return *this;
		}

		CTADDR Update(PCBYTE data, RCTADDR size)
		{
			TADDR bytesWritten = 0;

			while (bytesWritten < size)
			{
				this->Update(data[bytesWritten++]);

				++this->Address;
			}

			return bytesWritten;
		}

		CTADDR Erase(RCTADDR size)
		{
			PBYTE nullBuffer = new byte[size];
			memset(nullBuffer, SERIAL_EEPROM_ERASE_VALUE, size);

			TADDR bytesErased = this->Write(MAKE_CONST(nullBuffer), size);

			delete[] nullBuffer;

			return bytesErased;
		}
	};

#pragma endregion


#pragma region [EEPROM_I2C] DEFINITION

	template EEPROMI2C_T_CLAUSE_DEF
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
				(CapacityKb() == 0x0008 OR CapacityKb() == 0x0800) ? 2 :
					(CapacityKb() == 0x0004 OR CapacityKb() == 0x0400) ? 1 : 0;
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
			return SERIAL_EEPROM_I2C_ADDRESS OR BuildDeviceNumberBits();
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

		typedef TYPE_IF((CapacityKb() >= 0x0400), DWORD, TYPE_IF((CapacityKb() >= 0x0004), WORD, BYTE)) TAddr, TADDR, & RTADDR;

	public:

		typedef const TAddr CTADDR, & RCTADDR;

	protected:

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

		STATIC CTADDR Capacity() ALIAS(Size);


		// STATIC CONSTEXPR FUNCTION ALIASES

		STATIC CONSTEXPR CSIZE (&PageSize)() = TEEERef::PageSize;


		// INSTANCE VARIABLES

		TEEEPTR _Iterator;


		// CONSTRUCTOR

		EEPROM_I2C(CBOOL use400KHz = FALSE, RCTADDR startAddr = (CTADDR)0) : _Iterator(TEEEPtr(startAddr))
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

		TEEEPTR Seek(RCTADDR addr)
		{
			(RTADDR)_Iterator = addr;
			return _Iterator;
		}

		CBYTE Read() const
		{
			return (*_Iterator).Read();
		}

		CBYTE Read(RCTADDR addr) const
		{
			this->Seek(addr);
			return this->Read();
		}

		CTADDR Read(PBYTE buffer, RCTADDR size) const
		{
			return (*_Iterator).Read(buffer, size);
		}

		CTADDR Read(PBYTE buffer, RCTADDR size, RCTADDR addr) const
		{
			this->Seek(addr);
			return this->Read(buffer, size);
		}

		template DEFAULT_T_CLAUSE
		CTADDR Read(T & datum) const
		{
			return this->Read(reinterpret_cast<PBYTE>(&datum), T_SIZE);
		}

		template DEFAULT_T_CLAUSE
		CTADDR Read(T & datum, RCTADDR addr) const
		{
			this->Seek(addr);
			return this->Read(datum);
		}

		CBYTE Write(CBYTE value)
		{
			return (*_Iterator).Write(value);
		}

		CBYTE Write(CBYTE value, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Write(value);
		}

		CTADDR Write(PCBYTE data, RCTADDR size)
		{
			return (*_Iterator).Write(data, size);
		}

		CTADDR Write(PCBYTE data, RCTADDR size, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Write(data, size);
		}

		CSIZE Write(PCCHAR data)
		{
			return (CSIZE)(*_Iterator).Write(reinterpret_cast<PCBYTE>(data), (CTADDR)strlen(data));
		}

		CSIZE Write(PCCHAR data, RCTADDR addr)
		{
			this->Seek(addr);
			return (CSIZE)this->Write(data, (CTADDR)strlen(data));
		}

		template DEFAULT_T_CLAUSE
		CTADDR Write(CONST T & datum)
		{
			return this->Write(reinterpret_cast<PCBYTE>(&datum), T_SIZE);
		}

		template DEFAULT_T_CLAUSE
		CTADDR Write(CONST T & datum, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Write(datum);
		}

		CBYTE Update(CBYTE value)
		{
			return (*_Iterator).Update(value);
		}

		CBYTE Update(CBYTE value, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Update(value);
		}

		CTADDR Update(PCBYTE data, RCTADDR size)
		{
			return (*_Iterator).Update(data, size);
		}

		CTADDR Update(PCBYTE data, RCTADDR size, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Update(data, size);
		}

		CSIZE Update(PCCHAR data)
		{
			return (CSIZE)(*_Iterator).Update(reinterpret_cast<PCBYTE>(data), (CTADDR)strlen(data));
		}

		CSIZE Update(PCCHAR data, RCTADDR addr)
		{
			this->Seek(addr);
			return (CSIZE)this->Update(data, (CTADDR)strlen(data));
		}

		template DEFAULT_T_CLAUSE
		CTADDR Update(CONST T & datum)
		{
			return this->Update(reinterpret_cast<PCBYTE>(&datum), T_SIZE);
		}

		template DEFAULT_T_CLAUSE
		CTADDR Update(CONST T & datum, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Save(datum);
		}

		CTADDR Erase(RCTADDR size)
		{
			return (*_Iterator).Erase(size);
		}

		CTADDR Erase(CSIZE size, RCTADDR addr)
		{
			this->Seek(addr);
			return this->Erase(size);
		}

		template DEFAULT_T_CLAUSE
		CTADDR Erase()
		{
			return this->Erase(T_SIZE);
		}

		template DEFAULT_T_CLAUSE
		CTADDR Erase(RCTADDR addr)
		{
			this->Seek(addr);
			return this->Erase(T_SIZE);
		}
	};

#pragma endregion
}

#endif
