/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#include "IttyBitty_bytes.h"

using namespace IttyBitty;


/* [BITPACK] DEFINITION */

#define __BIT(i) (this->b##i)

_BitPack::_BitPack(RCBITPACK other)
{
	*this = other;
}

CSIZE _BitPack::BitSize()
{
	return BIT_SIZE(_BitPack);
}

BIT _BitPack::operator[](SIZE i) const
{
	return this->Bit(i);
}

BIT _BitPack::Bit(SIZE i) const
{
	if (i >= this->BitSize())
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
