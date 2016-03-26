/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#include "IttyBitty_bytes.h"

using namespace IttyBitty;


#define __BIT(i) (this->b##i)

CONST SIZE _BitPack::Size() const
{
	return BIT_SIZE(_BitPack);
}

BIT _BitPack::operator[](SIZE i) const
{
	return this->Bit(i);
}

BIT _BitPack::Bit(SIZE i) const
{
	if (i >= Size())
		return NULL;
	
	switch (i)
	{
	case 0:
		return __BIT(0);
	case 1:
		return __BIT(1);
	case 2:
		return __BIT(2);
	case 3:
		return __BIT(3);
	case 4:
		return __BIT(4);
	case 5:
		return __BIT(5);
	case 6:
		return __BIT(6);
	case 7:
		return __BIT(7);
	default:
		return NULL;
	}
}


STRUCT ByteField::__BitProxy
{
public:

	__BitProxy(PBYTEFIELD pParent, SIZE i) : _Parent(pParent), _BitMask(BITMASK(i)) { }

	operator BIT() const
	{
		return MASK(_Parent->ByteValue(), _BitMask) != 0;
	}
				
	__BitProxy& operator=(CONST RBITPROXY crRValue)
	{
		*this = (BIT)crRValue;
		return *this;
	}
				
	__BitProxy& operator=(BIT bit)
	{
		_Parent->SetByteValue(_Parent->Mask(~_BitMask) | (bit ? _BitMask : (BYTE)0));
		return *this;
	}

private:

	VOLATILE PBYTEFIELD _Parent;
	BYTE _BitMask;
};


ByteField::CBITREF ByteField::NULL_BITREF(nullptr, 0);

ByteField::ByteField(BYTE byteVal)
{
	_Byte = new BYTE(byteVal);
	_DestroyPtr = true;
}
	
ByteField::ByteField(RBYTE byteRef)
{
	_Byte = &byteRef;
}
	
ByteField::ByteField(PBYTE pByte) : _Byte(pByte) { }
	
ByteField::~ByteField()
{
	if (_DestroyPtr)
		delete _Byte;
}

CONST SIZE ByteField::Size() const
{
	return _Bits->Size();
}

ByteField::operator BYTE() const
{
	return this->ByteValue();
}

ByteField::operator BYTE()
{
	return *_Byte;
}

ByteField::operator CHAR() const
{
	return (CHAR)this->ByteValue();
}

ByteField::operator CHAR()
{
	return (CHAR)*_Byte;
}

ByteField::operator BitPack()
{
	return *_Bits;
}

BIT ByteField::operator[](SIZE i) const
{
	return this->Bit(i);
}

ByteField::BITREF ByteField::operator[](SIZE i)
{
	return this->Bit(i);
}

BIT ByteField::Bit(SIZE i) const
{
	return MAKE_CONST(_Bits)->Bit(i);
}

ByteField::BITREF ByteField::Bit(SIZE i)
{
	if (i >= _Bits->Size())
		return NULL_BITREF;

	return BITREF(this, i);
}

BYTE ByteField::ByteValue() const
{
	return *MAKE_CONST(_Byte);
}

PBYTEFIELD ByteField::SetByteValue(BYTE byteVal)
{
	*_Byte = byteVal;
	return this;
}

PBYTEFIELD ByteField::CopyByte(PBYTE pByte)
{
	return this->SetByteValue(*pByte);
}

PBYTEFIELD ByteField::PointTo(PBYTE pByte)
{
	_Byte = pByte;
	return this;
}

BYTE ByteField::Mask(BYTE bitMask) const
{
	return MASK(this->ByteValue(), bitMask);
}
