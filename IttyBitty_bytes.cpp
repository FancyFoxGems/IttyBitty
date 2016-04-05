/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#include "IttyBitty_bytes.h"

using namespace IttyBitty;


/* [BITPROXY/BITREF]: PROXY CLASS TO ALLOW FOR INDIVIDUAL BIT-ADDRESSED MEMORY WRITES */

_BitProxy::_BitProxy(PIBYTEFIELD pParent, SIZE i) : _Parent(pParent), _BitMask(BIT_MASK(i)) { }

_BitProxy::_BitProxy(RCBITREF other) : _Parent(other.Parent()), _BitMask(other.BitMask()) { }

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

PIBYTEFIELD _BitProxy::Parent() const
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

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField((BYTE)0);
	new (this) ByteField((BYTE)0);
}

ByteField::ByteField(RCBYTE byteVal) : _pByte(new BYTE(byteVal)), _DisposeByte(true) { }

ByteField::ByteField(RBYTE byteRef) : _pByte(&byteRef), _DisposeByte(false) { }

ByteField::ByteField(PBYTE pByte) : _pByte(pByte), _DisposeByte(false) { }

ByteField::ByteField(RCBYTEFIELD other)
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField(other.ByteRef());
	new (this) ByteField((RBYTE)other);
}
	
ByteField::~ByteField()
{
	if (_DisposeByte)
		delete _pByte;
}

RBYTEFIELD ByteField::NULL_OBJECT()
{
	STATIC BYTEFIELD NULL_BYTEFIELD((BYTE)0);
	return NULL_BYTEFIELD;
}

CSIZE ByteField::Size() const
{
	return sizeof(ByteField);

}

SIZE ByteField::BitWidth() const
{
	return this->ByteSize() * BitPack::BitSize();
}

SIZE ByteField::ByteSize() const
{
	return 1;
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

ByteField::operator PPBYTE()
{
	return &_pByte;
}

ByteField::operator PCCHAR() const
{
	return (PCCHAR)this->operator PCBYTE();
}

ByteField::operator PPCHAR()
{
	return (PPCHAR)this->operator PPBYTE();
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

RIBYTEFIELD ByteField::Byte(SIZE i)
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

VOID ByteField::CopyFrom(RCIBITFIELD<BYTE> other)
{
	*_pByte = other.Value();
}

PBYTE ByteField::Pointer() const
{
	return _pByte;
}

VOID ByteField::PointTo(PBYTE pByte)
{
	_pByte = pByte;
}

VOID ByteField::ReferenceFrom(RCIBITFIELD<BYTE> other)
{
	_pByte = other.Pointer();
}

BYTE ByteField::Mask(BYTE byteMask) const
{
	return MASK(this->Value(), byteMask);
}

BYTE ByteField::Mask(RCIBITFIELD<BYTE> other) const
{
	return MASK(this->Value(), other.Value());
}

ByteField::operator PBYTE()
{
	return _pByte;
}

ByteField::operator RBYTE()
{
	return *_pByte;
}

ByteField::operator PCHAR()
{
	return (PCHAR)_pByte;
}

ByteField::operator RCHAR()
{
	return (RCHAR)*_pByte;
}

ByteField::operator PCBITPACK() const
{
	return MAKE_CONST(_pBitPack);
}

ByteField::operator PBITPACK()
{
	return _pBitPack;
}

PIBYTEFIELD ByteField::CloneByValue() const
{
	return new ByteField(this->Value());
}

PIBYTEFIELD ByteField::CloneByReference() const
{
	return new ByteField(_pByte);
}

BYTE ByteField::LowNybble() const
{
	return LOW_NYBBLE(this->Value());
}

RIBYTEFIELD ByteField::SetLowNybble(BYTE nybbleVal)
{
	*_pByte = (this->HighNybble() << 4) | LOW_NYBBLE(nybbleVal);
	return *this;
}

BYTE ByteField::HighNybble() const
{
	return HIGH_NYBBLE(this->Value());
}

RIBYTEFIELD ByteField::SetHighNybble(BYTE nybbleVal)
{
	*_pByte = HIGH_NYBBLE(nybbleVal) | this->LowNybble();
	return *this;
}
