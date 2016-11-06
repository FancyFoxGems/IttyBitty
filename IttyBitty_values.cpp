/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(EXCLUDE_ITTY_BITTY_FIELDS) && !defined(EXCLUDE_ITTYBITTY_CONSTVALUES)
	#define EXCLUDE_ITTYBITTY_CONSTVALUES
#endif

#ifndef EXCLUDE_ITTYBITTY_CONSTVALUES


#include "IttyBitty_values.h"

using namespace IttyBitty;


#pragma region [ConstValue] IMPLEMENTATION

// CONSTRUCTORS

ConstValue::ConstValue() : Bytes(0) { }

ConstValue::ConstValue(RCCONSTVALUE other)
{
	this->Bytes = other.Bytes;
}

ConstValue::ConstValue(RRCONSTVALUE other)
{	
	new (this) ConstValue(other.Bytes);
}

ConstValue::ConstValue(PCBYTE value) : Bytes(value) { }

ConstValue::ConstValue(PCCHAR value) : String(value) { }

ConstValue::ConstValue(PCBITPACK value) : BitFields(value) { }

ConstValue::ConstValue(RCCHAR value) : Char(value) { }

ConstValue::ConstValue(RCBYTE value) : Byte(value) { }

ConstValue::ConstValue(RCBOOL value) : Bool(value) { }

ConstValue::ConstValue(RCSHORT value) : Short(value) { }

ConstValue::ConstValue(RCWORD value) : Word(value) { }

ConstValue::ConstValue(RCLONG value) : Long(value) { }
		
ConstValue::ConstValue(RCDWORD value) : DWord(value) { }

ConstValue::ConstValue(RCFLOAT value) : Float(value) { }


// OPERATORS

RCONSTVALUE ConstValue::operator =(RCCONSTVALUE rValue)
{
	*this = ConstValue(rValue);
	return *this;
}

RCONSTVALUE ConstValue::operator =(RRCONSTVALUE rValue)
{
	*this = ConstValue(rValue);
	return *this;
}

RCONSTVALUE ConstValue::operator =(PCBYTE rValue)
{
	this->Bytes = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(PCCHAR rValue)
{
	this->String = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(PCBITPACK rValue)
{
	this->BitFields = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCCHAR rValue)
{
	this->Char = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCBYTE rValue)
{
	this->Byte = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCBOOL rValue)
{
	this->Bool = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCSHORT rValue)
{
	this->Short = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCWORD rValue)
{
	this->Word = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCLONG rValue)
{
	this->Long = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCDWORD rValue)
{
	this->DWord = rValue;
	return *this;
}

RCONSTVALUE ConstValue::operator =(RCFLOAT rValue)
{
	this->Float = rValue;
	return *this;
}

ConstValue::operator PCBYTE() const
{
	return this->Bytes;
}

ConstValue::operator PCCHAR() const
{
	return this->String;
}

ConstValue::operator PCBITPACK() const
{
	return this->BitFields;
}

ConstValue::operator RCCHAR() const
{
	return this->Char;
}

ConstValue::operator RCBYTE() const
{
	return this->Byte;
}

ConstValue::operator RCBOOL() const
{
	return this->Bool;
}

ConstValue::operator RCSHORT() const
{
	return this->Short;
}

ConstValue::operator RCWORD() const
{
	return this->Word;
}

ConstValue::operator RCLONG() const
{
	return this->Long;
}

ConstValue::operator RCDWORD() const
{
	return this->DWord;
}

ConstValue::operator RCFLOAT() const
{
	return this->Float;
}


// USER METHODS

VOID ConstValue::FreePtr()
{
	if (this->Bytes)
		delete this->Bytes;
}

VOID ConstValue::FreeData()
{
	if (this->Bytes)
		delete[] this->Bytes;
}

#pragma endregion


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

Value::Value(PBYTE value) : Bytes(value) { }

Value::Value(PCHAR value) : String(value) { }

Value::Value(PBITPACK value) : BitFields(value) { }

Value::Value(RCHAR value) : CharPtr(&value) { }

Value::Value(RBYTE value) : BytePtr(&value) { }

Value::Value(RBOOL value) : BoolPtr(&value) { }

Value::Value(RSHORT value) : ShortPtr(&value) { }

Value::Value(RWORD value) : WordPtr(&value) { }

Value::Value(RLONG value) : LongPtr(&value) { }
		
Value::Value(RDWORD value) : DWordPtr(&value) { }

Value::Value(RFLOAT value) : FloatPtr(&value) { }


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

RVALUE Value::operator =(PBYTE rValue)
{
	this->Bytes = rValue;
	return *this;
}

RVALUE Value::operator =(PCHAR rValue)
{
	this->String = rValue;
	return *this;
}

RVALUE Value::operator =(PBITPACK rValue)
{
	this->BitFields = rValue;
	return *this;
}

RVALUE Value::operator =(RCHAR rValue)
{
	*this->CharPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RBYTE rValue)
{
	*this->BytePtr = rValue;
	return *this;
}

RVALUE Value::operator =(RBOOL rValue)
{
	*this->BoolPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RSHORT rValue)
{
	*this->ShortPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RWORD rValue)
{
	*this->WordPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RLONG rValue)
{
	*this->LongPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RDWORD rValue)
{
	*this->DWordPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RFLOAT rValue)
{
	*this->FloatPtr = rValue;
	return *this;
}


Value::operator PCBYTE() const
{
	return MAKE_CONST(this->Bytes);
}

Value::operator PBYTE()
{
	return this->Bytes;
}

Value::operator PCCHAR() const
{
	return MAKE_CONST(this->String);
}

Value::operator PCHAR()
{
	return this->String;
}

Value::operator PCBITPACK() const
{
	return MAKE_CONST(this->BitFields);
}

Value::operator PBITPACK()
{
	return this->BitFields;
}

Value::operator RCCHAR() const
{
	return MAKE_CONST(*this->CharPtr);
}

Value::operator RCHAR()
{
	return *this->CharPtr;
}

Value::operator RCBYTE() const
{
	return MAKE_CONST(*this->BytePtr);
}

Value::operator RBYTE()
{
	return *this->BytePtr;	
}

Value::operator RCBOOL() const
{
	return MAKE_CONST(*this->BoolPtr);
}

Value::operator RBOOL()
{
	return *this->BoolPtr;
}

Value::operator RCSHORT() const
{
	return MAKE_CONST(*this->ShortPtr);
}

Value::operator RSHORT()
{
	return *this->ShortPtr;
}

Value::operator RCWORD() const
{
	return MAKE_CONST(*this->WordPtr);
}

Value::operator RWORD()
{
	return *this->WordPtr;
}

Value::operator RCLONG() const
{
	return MAKE_CONST(*this->LongPtr);
}

Value::operator RLONG()
{
	return *this->LongPtr;
}

Value::operator RCDWORD() const
{
	return MAKE_CONST(*this->DWordPtr);
}

Value::operator RDWORD()
{
	return *this->DWordPtr;
}

Value::operator RCFLOAT() const
{
	return MAKE_CONST(*this->FloatPtr);
}

Value::operator RFLOAT()
{
	return *this->FloatPtr;
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

#endif	// #ifndef EXCLUDE_ITTYBITTY_CONSTVALUES
