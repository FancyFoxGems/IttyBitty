/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_SLIM
	#define NO_ITTYBITTY_VALUES
#endif

#ifndef NO_ITTYBITTY_VALUES


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

VOID ConstValue::FreeData()
{
	if (this->Bytes)
	{
		delete[] this->Bytes;
		this->Bytes = NULL;
	}
}

VOID ConstValue::FreeReference()
{
	this->Bytes = NULL;
}

#pragma endregion


#pragma region [Value] IMPLEMENTATION

// CONSTRUCTORS

Value::Value() : BytesRef(0) { }

Value::Value(RCVALUE other)
{
	this->BytesRef = other.BytesRef;
}

Value::Value(RRVALUE other)
{
	new (this) Value(*other.BytesRef);
}

Value::Value(PBYTE value) : BytesRef(&value) { }

Value::Value(PCHAR value) : StringRef(&value) { }

Value::Value(PBITPACK value) : BitFieldsRef(&value) { }

Value::Value(RCHAR value) : CharRef(&value) { }

Value::Value(RBYTE value) : ByteRef(&value) { }

Value::Value(RBOOL value) : BoolRef(&value) { }

Value::Value(RSHORT value) : ShortRef(&value) { }

Value::Value(RWORD value) : WordRef(&value) { }

Value::Value(RLONG value) : LongRef(&value) { }

Value::Value(RDWORD value) : DWordRef(&value) { }

Value::Value(RFLOAT value) : FloatRef(&value) { }


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
	*this->BytesRef = rValue;
	return *this;
}

RVALUE Value::operator =(PCHAR rValue)
{
	*this->StringRef = rValue;
	return *this;
}

RVALUE Value::operator =(PBITPACK rValue)
{
	*this->BitFieldsRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCCHAR rValue)
{
	*this->CharRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCBYTE rValue)
{
	*this->ByteRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCBOOL rValue)
{
	*this->BoolRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCSHORT rValue)
{
	*this->ShortRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCWORD rValue)
{
	*this->WordRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCLONG rValue)
{
	*this->LongRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCDWORD rValue)
{
	*this->DWordRef = rValue;
	return *this;
}

RVALUE Value::operator =(RCFLOAT rValue)
{
	*this->FloatRef = rValue;
	return *this;
}


Value::operator PCBYTE() const
{
	return MAKE_CONST(*this->BytesRef);
}

Value::operator PBYTE()
{
	return *this->BytesRef;
}

Value::operator PCCHAR() const
{
	return MAKE_CONST(*this->StringRef);
}

Value::operator PCHAR()
{
	return *this->StringRef;
}

Value::operator PCBITPACK() const
{
	return MAKE_CONST(*this->BitFieldsRef);
}

Value::operator PBITPACK()
{
	return *this->BitFieldsRef;
}

Value::operator RCCHAR() const
{
	return MAKE_CONST(*this->CharRef);
}

Value::operator RCHAR()
{
	return *this->CharRef;
}

Value::operator RCBYTE() const
{
	return MAKE_CONST(*this->ByteRef);
}

Value::operator RBYTE()
{
	return *this->ByteRef;
}

Value::operator RCBOOL() const
{
	return MAKE_CONST(*this->BoolRef);
}

Value::operator RBOOL()
{
	return *this->BoolRef;
}

Value::operator RCSHORT() const
{
	return MAKE_CONST(*this->ShortRef);
}

Value::operator RSHORT()
{
	return *this->ShortRef;
}

Value::operator RCWORD() const
{
	return MAKE_CONST(*this->WordRef);
}

Value::operator RWORD()
{
	return *this->WordRef;
}

Value::operator RCLONG() const
{
	return MAKE_CONST(*this->LongRef);
}

Value::operator RLONG()
{
	return *this->LongRef;
}

Value::operator RCDWORD() const
{
	return MAKE_CONST(*this->DWordRef);
}

Value::operator RDWORD()
{
	return *this->DWordRef;
}

Value::operator RCFLOAT() const
{
	return MAKE_CONST(*this->FloatRef);
}

Value::operator RFLOAT()
{
	return *this->FloatRef;
}


// USER METHODS

VOID Value::FreeData()
{
	if (this->BytesRef)
	{
		if (*this->BytesRef)
		{
			delete[] *this->BytesRef;
			*this->BytesRef = NULL;
		}

		delete this->BytesRef;
		this->BytesRef = NULL;
	}
}

VOID Value::FreeReference()
{
	if (this->BytesRef)
	{
		delete this->BytesRef;
		this->BytesRef = NULL;
	}
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_CONSTVALUES
