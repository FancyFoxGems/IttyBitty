/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/


#include "IttyBitty_values.h"

using namespace IttyBitty;


#pragma region Value DEFINITION

// CONSTRUCTORS

Value::Value() : Bytes(0) { }

//Value::Value(CBYTE byteSize)
//{
//	this->Bytes = new byte[byteSize];
//}

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

RVALUE Value::operator =(RCCHAR rValue)
{
	*this->CharPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCBYTE rValue)
{
	*this->BytePtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCBOOL rValue)
{
	*this->BoolPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCSHORT rValue)
{
	*this->ShortPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCWORD rValue)
{
	*this->WordPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCLONG rValue)
{
	*this->LongPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCDWORD rValue)
{
	*this->DWordPtr = rValue;
	return *this;
}

RVALUE Value::operator =(RCFLOAT rValue)
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


#pragma region Datum DEFINITION

// CONSTRUCTORS

Datum::Datum() : Bytes(0) { }

//Datum::Datum(CBYTE byteSize)
//{
//	this->Bytes = new byte[byteSize];
//}

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

RDATUM Datum::operator =(RCCHAR rValue)
{
	*this->CharPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCBYTE rValue)
{
	*this->BytePtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCBOOL rValue)
{
	*this->BoolPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCSHORT rValue)
{
	*this->ShortPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCWORD rValue)
{
	*this->WordPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCLONG rValue)
{
	*this->LongPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCDWORD rValue)
{
	*this->DWordPtr = rValue;
	return *this;
}

RDATUM Datum::operator =(RCFLOAT rValue)
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
