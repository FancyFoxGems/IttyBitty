/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) && !defined(EXCLUDE_ITTYBITTY_EEPROM_I2C)
	#define EXCLUDE_ITTYBITTY_EEPROM_I2C
#endif

#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C


#include "IttyBitty_EEPROM_I2C.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLES	

EEPROMI2C<> ExtEEPROM;

#pragma endregion


#pragma region [_EEEPtrBase] DEFINITION

// CONSTRUCTOR
	
_EEEPtrBase::_EEEPtrBase(RCWORD addr) : Address(addr) { }


// OPERATORS
		
_EEEPtrBase::operator CBYTE()
{
	return **this;
}
		
_EEEPtrBase::operator RCWORD() const
{
	return this->Address;
}

CBOOL _EEEPtrBase::operator ==(RCEEEPTRBASE ptr) const
{
	return this->Address == ptr.Address;
}

CBOOL _EEEPtrBase::operator !=(RCEEEPTRBASE ptr) const
{
	return this->Address != ptr.Address;
}

EEEREFBASE _EEEPtrBase::operator *()
{
	return _EEERefBase(this->Address);
}
	
REEEPTRBASE _EEEPtrBase::operator =(RCWORD addr)
{
	this->Address = addr;
	return *this;
}

REEEPTRBASE _EEEPtrBase::operator ++()
{
	++this->Address;
	return *this;
}

REEEPTRBASE _EEEPtrBase::operator --()
{
	--this->Address;
	return *this;
}

EEEPTRBASE _EEEPtrBase::operator ++(INT)
{
	return _EEEPtrBase(this->Address++);
}

EEEPTRBASE _EEEPtrBase::operator --(INT)
{
	return _EEEPtrBase(this->Address--);
}

#pragma endregion


#pragma region [_EEERefBase] DEFINITION

// CONSTRUCTOR

_EEERefBase::_EEERefBase(RCWORD addr)
{
	this->Address = addr;
}


// OPERATORS
	
_EEERefBase::operator CBYTE() const
{
	return **this;
}
	
_EEERefBase::operator RCWORD() const
{
	return this->Address;
}

CBYTE _EEERefBase::operator *() const
{
	return this->Read();
}

CBOOL _EEERefBase::operator ==(RCBYTE value) const
{
	return *this == value;
}

CBOOL _EEERefBase::operator !=(RCBYTE value) const
{
	return *this != value;
}

REEEREFBASE _EEERefBase::operator =(RCBYTE value)
{
	this->Write(value);
	return *this;
}

REEEREFBASE _EEERefBase::operator =(RCEEEREFBASE ref)
{
	return *this = *ref;
}

REEEREFBASE _EEERefBase::operator +=(RCBYTE value)
{
	return *this = **this + value;
}

REEEREFBASE _EEERefBase::operator -=(RCBYTE value)
{
	return *this = **this - value;
}

REEEREFBASE _EEERefBase::operator *=(RCBYTE value)
{
	return *this = **this * value;
}

REEEREFBASE _EEERefBase::operator /=(RCBYTE value)
{
	return *this = **this / value;
}

REEEREFBASE _EEERefBase::operator ^=(RCBYTE value)
{
	return *this = **this ^ value;
}

REEEREFBASE _EEERefBase::operator %=(RCBYTE value)
{
	return *this = **this % value;
}

REEEREFBASE _EEERefBase::operator &=(RCBYTE value)
{
	return *this = **this & value;
}

REEEREFBASE _EEERefBase::operator |=(RCBYTE value)
{
	return *this = **this | value;
}

REEEREFBASE _EEERefBase::operator <<=(RCBYTE value)
{
	return *this = **this << value;
}

REEEREFBASE _EEERefBase::operator >>=(RCBYTE value)
{
	return *this = **this >> value;
}
	
REEEREFBASE _EEERefBase::operator++()
{
	return *this += 1;
}
REEEREFBASE _EEERefBase::operator--()
{
	return *this -= 1;
}
	
CBYTE _EEERefBase::operator ++(INT)
{ 
	BYTE value = **this;
	++(*this);
	return value;
}

CBYTE _EEERefBase::operator --(INT)
{ 
	BYTE value = **this;
	--(*this);
	return value;
}
	

// USER METHODS
	
REEEREFBASE _EEERefBase::Update(RCBYTE value)
{
	if (**this != value)
		*this = value;

	return *this;
}


// HELPER METHODS

CBYTE _EEERefBase::Read() const
{
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

VOID _EEERefBase::Write(RCBYTE value)
{
	Wire.beginTransmission(0x50);

	Wire.write((BYTE)(this->Address >> 8));
	Wire.write((BYTE)this->Address);

	Wire.write(value);

	Wire.endTransmission();
	delay(50);
}

#pragma endregion

#endif //#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C
