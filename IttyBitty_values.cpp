/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(EXCLUDE_ITTY_BITTY_FIELDS) && !defined(EXCLUDE_ITTYBITTY_VALUES)
	#define EXCLUDE_ITTYBITTY_VALUES
#endif

#ifndef EXCLUDE_ITTYBITTY_VALUES


#include "IttyBitty_values.h"

using namespace IttyBitty;


#pragma region [Value] IMPLEMENTATION

// CONSTRUCTORS

Value::Value() : Bytes(0) { }

Value::Value(RCVALUE other)
{
	this->Bytes = other.Bytes;
}

Value::Value(RRVALUE other)
{	
	new (this) Value(other.Bytes);
}

Value::Value(PCBYTE value) : Bytes(value) { }

Value::Value(PCCHAR value) : String(value) { }

Value::Value(PCBITPACK value) : BitFields(value) { }

Value::Value(RCCHAR value) : Char(value) { }

Value::Value(RCBYTE value) : Byte(value) { }

Value::Value(RCBOOL value) : Bool(value) { }

Value::Value(RCSHORT value) : Short(value) { }

Value::Value(RCWORD value) : Word(value) { }

Value::Value(RCLONG value) : Long(value) { }
		
Value::Value(RCDWORD value) : DWord(value) { }

Value::Value(RCFLOAT value) : Float(value) { }


// OPERATORS

RVALUE Value::operator =(RCVALUE rValue)
{
	*this = Value(rValue);
	return *this;
}

RVALUE Value::operator =(RRVALUE rValue)
{
	*this = Value(rValue);
	return *this;
}

RVALUE Value::operator =(PCBYTE rValue)
{
	this->Bytes = rValue;
	return *this;
}

RVALUE Value::operator =(PCCHAR rValue)
{
	this->String = rValue;
	return *this;
}

RVALUE Value::operator =(PCBITPACK rValue)
{
	this->BitFields = rValue;
	return *this;
}

RVALUE Value::operator =(RCCHAR rValue)
{
	this->Char = rValue;
	return *this;
}

RVALUE Value::operator =(RCBYTE rValue)
{
	this->Byte = rValue;
	return *this;
}

RVALUE Value::operator =(RCBOOL rValue)
{
	this->Bool = rValue;
	return *this;
}

RVALUE Value::operator =(RCSHORT rValue)
{
	this->Short = rValue;
	return *this;
}

RVALUE Value::operator =(RCWORD rValue)
{
	this->Word = rValue;
	return *this;
}

RVALUE Value::operator =(RCLONG rValue)
{
	this->Long = rValue;
	return *this;
}

RVALUE Value::operator =(RCDWORD rValue)
{
	this->DWord = rValue;
	return *this;
}

RVALUE Value::operator =(RCFLOAT rValue)
{
	this->Float = rValue;
	return *this;
}

Value::operator PCBYTE() const
{
	return this->Bytes;
}

Value::operator PCCHAR() const
{
	return this->String;
}

Value::operator PCBITPACK() const
{
	return this->BitFields;
}

Value::operator RCCHAR() const
{
	return this->Char;
}

Value::operator RCBYTE() const
{
	return this->Byte;
}

Value::operator RCBOOL() const
{
	return this->Bool;
}

Value::operator RCSHORT() const
{
	return this->Short;
}

Value::operator RCWORD() const
{
	return this->Word;
}

Value::operator RCLONG() const
{
	return this->Long;
}

Value::operator RCDWORD() const
{
	return this->DWord;
}

Value::operator RCFLOAT() const
{
	return this->Float;
}


// USER METHODS

VOID Value::FreePtr()
{
	if (this->Bytes)
		delete this->Bytes;
}

VOID Value::FreeData()
{
	if (this->Bytes)
		delete[] this->Bytes;
}

#pragma endregion


#pragma region [Datum] IMPLEMENTATION

// CONSTRUCTORS

Datum::Datum() : Bytes(0) { }

Datum::Datum(RCDATUM other)
{
	this->Bytes = other.Bytes;
}

Datum::Datum(RRDATUM other)
{	
	new (this) Datum(other.Bytes);
}

Datum::Datum(PBYTE value) : Bytes(value) { }

Datum::Datum(PCHAR value) : String(value) { }

Datum::Datum(PBITPACK value) : BitFields(value) { }

Datum::Datum(RCHAR value) : CharPtr(&value) { }

Datum::Datum(RBYTE value) : BytePtr(&value) { }

Datum::Datum(RBOOL value) : BoolPtr(&value) { }

Datum::Datum(RSHORT value) : ShortPtr(&value) { }

Datum::Datum(RWORD value) : WordPtr(&value) { }

Datum::Datum(RLONG value) : LongPtr(&value) { }
		
Datum::Datum(RDWORD value) : DWordPtr(&value) { }

Datum::Datum(RFLOAT value) : FloatPtr(&value) { }


// OPERATORS

RDATUM Datum::operator =(RCDATUM rValue)
{
	*this = Datum(rValue);
	return *this;
}

RDATUM Datum::operator =(RRDATUM rValue)
{
	*this = Datum(rValue);
	return *this;
}

RDATUM Datum::operator =(PBYTE rValue)
{
	this->Bytes = rValue;
	return *this;
}

RDATUM Datum::operator =(PCHAR rValue)
{
	this->String = rValue;
	return *this;
}

RDATUM Datum::operator =(PBITPACK rValue)
{
	this->BitFields = rValue;
	return *this;
}

RDATUM Datum::operator =(RCHAR rValue)
{
	*this->CharPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RBYTE rValue)
{
	*this->BytePtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RBOOL rValue)
{
	*this->BoolPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RSHORT rValue)
{
	*this->ShortPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RWORD rValue)
{
	*this->WordPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RLONG rValue)
{
	*this->LongPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RDWORD rValue)
{
	*this->DWordPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RFLOAT rValue)
{
	*this->FloatPtr = rValue;
	return *this;
}


Datum::operator PCBYTE() const
{
	return MAKE_CONST(this->Bytes);
}

Datum::operator PBYTE()
{
	return this->Bytes;
}

Datum::operator PCCHAR() const
{
	return MAKE_CONST(this->String);
}

Datum::operator PCHAR()
{
	return this->String;
}

Datum::operator PCBITPACK() const
{
	return MAKE_CONST(this->BitFields);
}

Datum::operator PBITPACK()
{
	return this->BitFields;
}

Datum::operator RCCHAR() const
{
	return MAKE_CONST(*this->CharPtr);
}

Datum::operator RCHAR()
{
	return *this->CharPtr;
}

Datum::operator RCBYTE() const
{
	return MAKE_CONST(*this->BytePtr);
}

Datum::operator RBYTE()
{
	return *this->BytePtr;	
}

Datum::operator RCBOOL() const
{
	return MAKE_CONST(*this->BoolPtr);
}

Datum::operator RBOOL()
{
	return *this->BoolPtr;
}

Datum::operator RCSHORT() const
{
	return MAKE_CONST(*this->ShortPtr);
}

Datum::operator RSHORT()
{
	return *this->ShortPtr;
}

Datum::operator RCWORD() const
{
	return MAKE_CONST(*this->WordPtr);
}

Datum::operator RWORD()
{
	return *this->WordPtr;
}

Datum::operator RCLONG() const
{
	return MAKE_CONST(*this->LongPtr);
}

Datum::operator RLONG()
{
	return *this->LongPtr;
}

Datum::operator RCDWORD() const
{
	return MAKE_CONST(*this->DWordPtr);
}

Datum::operator RDWORD()
{
	return *this->DWordPtr;
}

Datum::operator RCFLOAT() const
{
	return MAKE_CONST(*this->FloatPtr);
}

Datum::operator RFLOAT()
{
	return *this->FloatPtr;
}


// USER METHODS

VOID Datum::FreePtr()
{
	if (this->Bytes)
		delete this->Bytes;
}

VOID Datum::FreeData()
{
	if (this->Bytes)
		delete[] this->Bytes;
}

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_VALUES
