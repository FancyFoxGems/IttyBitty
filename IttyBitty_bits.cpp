#include "IttyBitty_bits.h"


STRUCT _bitfield::_bitproxy
{
public:

	_bitproxy(PBITFIELD pParent, SIZE i) : _Parent(pParent), _BitMask(BITMASK[i]) { }
				
	_bitproxy& operator=(const RBITPROXY crRValue)
	{
		_Parent->SetValue(crRValue);
		return *this;
	}
				
	_bitproxy& operator=(BIT bit)
	{
		_Parent->SetValue(_Parent->Mask(~_BitMask) | (bit ? _BitMask : (BYTE)0));
		return *this;
	}

	operator bool()
	{
		return (_Parent->Value() & _BitMask) != 0;
	}

private:

	VOLATILE PBITFIELD _Parent;
	BYTE _BitMask;
};


_bitfield::_bitfield(BYTE byteVal) : _rByte(byteVal)
{
	*Byte = byteVal;
	_pByte = &byteVal;
	_rByte = byteVal;
}
	
_bitfield::_bitfield(RBYTE byteRef) : _rByte(byteRef)
{
	*Byte = byteRef;
	*_pByte = byteRef;
}
	
_bitfield::_bitfield(PBYTE pByte) : _rByte(*pByte)
{
	*Byte = *pByte;
	_pByte = pByte;
}

CONST SIZE _bitfield::Size() const
{
	return sizeof(BitPack);
}

BIT _bitfield::operator[](SIZE i)
{
	if (i >= Size())
		return 0;
	return BITPROXY(this, i);
}

BYTE _bitfield::Value() const
{
	return *_pByte;
}

VOID _bitfield::SetValue(BYTE byteVal)
{
	*_pByte = byteVal;
}

BYTE _bitfield::Mask(BYTE bitMask) const
{
	return this->Value() & bitMask;
}

BIT _bitfield::Bit(SIZE i)
{
	if (i >= Size())
		return 0;

	switch (i)
	{
	case 0:
		return B(Byte, 0);
	case 1:
		return B(Byte, 1);
	case 2:
		return B(Byte, 2);
	case 3:
		return B(Byte, 3);
	case 4:
		return B(Byte, 4);
	case 5:
		return B(Byte, 5);
	case 6:
		return B(Byte, 6);
	case 7:
		return B(Byte, 7);
	}

	return B(Byte, 0);
}