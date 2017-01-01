/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_SLIM
	#define ITTYBITTY_BASE
	#define NO_ITTYBITTY_BYTES
#elif defined(ITTYBITTY_BASE)
	#define NO_ITTYBITTY_FULL_BYTES
#endif

#ifndef NO_ITTYBITTY_BYTES


#include "IttyBitty_bytes.h"

using namespace IttyBitty;


/* [_BitProxy/BITREF]: PROXY STRUCT TO ALLOW FOR INDIVIDUAL BIT-ADDRESSED MEMORY WRITES */

#ifndef NO_ITTYBITTY_FULL_BYTES
_BitProxy::_BitProxy(PIBYTEFIELD pParent, SIZE i)
#else
_BitProxy::_BitProxy(PBYTEFIELD pParent, SIZE i)
#endif
	: _Parent(pParent), _BitMask(BIT_MASK(i)) { }

_BitProxy::_BitProxy(RCBITREF other)
	: _Parent(other.Parent()), _BitMask(other.BitMask()) { }

_BitProxy::~_BitProxy() { }

RBITREF _BitProxy::NULL_OBJECT()
{
	STATIC BITREF NULL_BITREF(NULL, 0);
	return NULL_BITREF;
}

_BitProxy::operator BIT() const
{
	return _Parent->Mask(_BitMask) != 0;
}

RBITREF _BitProxy::operator=(RCBITREF crRValue)
{
	*this = (BIT)crRValue;
	return *this;
}

RBITREF _BitProxy::operator=(BIT bit)
{
	_Parent->SetValue(_Parent->Mask(NOT _BitMask) | (bit ? _BitMask : (BYTE)0));
	return *this;
}

BIT _BitProxy::Flip()
{
	return this->operator=(NOT (BIT)this);
}

#ifndef NO_ITTYBITTY_FULL_BYTES
PIBYTEFIELD _BitProxy::Parent() const
#else
PBYTEFIELD _BitProxy::Parent() const
#endif
{
	return _Parent;
}

BYTE _BitProxy::BitMask() const
{
	return _BitMask;
}


/* [BYTEIELD] DEFINITION */

ByteField::ByteField()
{
	this->~ByteField();
	new (this) ByteField((BYTE)0);
}

ByteField::ByteField(RCBYTE byteVal)
	: _pByte(new byte(byteVal)), _DisposeByte(false) { }

ByteField::ByteField(RVBYTE byteRef)
	: _pByte(&byteRef), _DisposeByte(false) { }

ByteField::ByteField(PVBYTE pByte)
	: _pByte(pByte), _DisposeByte(false) { }

ByteField::ByteField(RRBYTEFIELD other)
{
	this->~ByteField();
	new (this) ByteField((RVBYTE)other);

	other._DisposeByte = false;
}

ByteField::ByteField(RCBYTEFIELD other)
{
	this->~ByteField();
	new (this) ByteField((RVBYTE)other);
}

ByteField::~ByteField()
{
	if (_DisposeByte AND _pByte)
	{
		// TODO: Dispose PBYTE
		//delete _pByte;
		_pByte = NULL;
	}
}

RBYTEFIELD ByteField::NULL_OBJECT()
{
	STATIC BYTEFIELD NULL_BYTEFIELD;
	return NULL_BYTEFIELD;
}

RBYTEFIELD ByteField::operator=(RRBYTEFIELD other)
{
	*this = ByteField(other);

	return *this;
}

RBYTEFIELD ByteField::operator=(RCBYTEFIELD other)
{
	*this = ByteField(other);

	return *this;
}

ByteField::operator CBYTE() const
{
	return MAKE_CONST(*_pByte);
}

ByteField::operator CCHAR() const
{
	return (CCHAR)this->operator CBYTE();
}

ByteField::operator PCBYTE() const
{
	return MAKE_CONST(_pByte);
}

ByteField::operator PPVBYTE()
{
	return &_pByte;
}

ByteField::operator PCCHAR() const
{
	return (PCCHAR)this->operator PCBYTE();
}

ByteField::operator PPVCHAR()
{
	return (PPVCHAR)this->operator PPVBYTE();
}

ByteField::operator PBYTEFIELD() const
{
	return NULL;
}

ByteField::operator PPBYTEFIELD()
{
	STATIC PBYTEFIELD sillyPtr[1] = { this };
	return sillyPtr;
}

BIT ByteField::operator[](SIZE i) const
{
	return this->Bit(i);
}

BITREF ByteField::operator[](SIZE i)
{
	return this->Bit(i);
}

CSIZE ByteField::Size() const
{
	return sizeof(ByteField);

}

SIZE ByteField::BitWidth() const
{
	return this->ByteSize() * _BitPack::BitSize();
}

SIZE ByteField::ByteSize() const
{
	return 1;
}

BIT ByteField::Bit(SIZE i) const
{
	return MAKE_CONST(_pBitPack)->Bit(i);
}

BITREF ByteField::Bit(SIZE i)
{
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();

	return BitRef(this, i);
}

BIT ByteField::Flip(SIZE i)
{
	return this->Bit(i).Flip();
}

PPCBYTEFIELD ByteField::Bytes() const
{
	STATIC PCBYTEFIELD thisClone = this;
	return &thisClone;
}

BYTE ByteField::Byte(SIZE i) const
{
	if (i >= this->ByteSize())
		return ByteField::NULL_OBJECT();

	return *_pByte;
}

#ifndef NO_ITTYBITTY_FULL_BYTES
RIBYTEFIELD ByteField::Byte(SIZE i)
#else
RBYTEFIELD ByteField::Byte(SIZE i)
#endif
{
	return *this;
}

BYTE ByteField::Value() const
{
	return *_pByte;
}

VOID ByteField::SetValue(BYTE value)
{
	*_pByte = value;
}

#ifndef NO_ITTYBITTY_FULL_BYTES
VOID ByteField::CopyFrom(RCIBITFIELD<BYTE> other)
#else
VOID ByteField::CopyFrom(RCBYTEFIELD other)
#endif
{
	*_pByte = other.Value();
}

PVBYTE ByteField::Pointer() const
{
	return _pByte;
}

VOID ByteField::PointTo(PVBYTE pByte)
{
	_pByte = pByte;
}

#ifndef NO_ITTYBITTY_FULL_BYTES
VOID ByteField::ReferenceFrom(RCIBITFIELD<BYTE> other)
#else
VOID ByteField::ReferenceFrom(RCBYTEFIELD other)
#endif
{
	_pByte = other.Pointer();
}

BYTE ByteField::Mask(BYTE byteMask) const
{
	return MASK(this->Value(), byteMask);
}

#ifndef NO_ITTYBITTY_FULL_BYTES
BYTE ByteField::Mask(RCIBITFIELD<BYTE> other) const
#else
BYTE ByteField::Mask(RCBYTEFIELD other) const
#endif
{
	return MASK(this->Value(), other.Value());
}

ByteField::operator PVBYTE()
{
	return _pByte;
}

ByteField::operator RVBYTE()
{
	return *_pByte;
}

ByteField::operator PVCHAR()
{
	return (PVCHAR)_pByte;
}

ByteField::operator RVCHAR()
{
	return (RVCHAR)*_pByte;
}

ByteField::operator PCBITPACK() const
{
	return MAKE_CONST(_pBitPack);
}

ByteField::operator PBITPACK()
{
	return _pBitPack;
}

#ifndef NO_ITTYBITTY_FULL_BYTES
PIBYTEFIELD ByteField::CloneByValue() const
#else
PBYTEFIELD ByteField::CloneByValue() const
#endif
{
	return new ByteField(this->Value());
}

#ifndef NO_ITTYBITTY_FULL_BYTES
PIBYTEFIELD ByteField::CloneByReference() const
#else
PBYTEFIELD ByteField::CloneByReference() const
#endif
{
	return new ByteField(_pByte);
}

BYTE ByteField::LowNybble() const
{
	return LOW_NYBBLE(this->Value());
}

#ifndef NO_ITTYBITTY_FULL_BYTES
RIBYTEFIELD ByteField::SetLowNybble(BYTE nybbleVal)
#else
RBYTEFIELD ByteField::SetLowNybble(BYTE nybbleVal)
#endif
{
	*_pByte = (this->HighNybble() << 4) | LOW_NYBBLE(nybbleVal);
	return *this;
}

BYTE ByteField::HighNybble() const
{
	return HIGH_NYBBLE(this->Value());
}

#ifndef NO_ITTYBITTY_FULL_BYTES
RIBYTEFIELD ByteField::SetHighNybble(BYTE nybbleVal)
#else
RBYTEFIELD ByteField::SetHighNybble(BYTE nybbleVal)
#endif
{
	*_pByte = HIGH_NYBBLE(nybbleVal) | this->LowNybble();
	return *this;
}


#endif	// #ifndef NO_ITTYBITTY_BYTES
