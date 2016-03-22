#ifndef _ITTYBITTY_BITS_H
#define _ITTYBITTY_BITS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IttyBitty_util.h"


#define BSET(byte_addr, bit_offset) (byte_addr |= (1 << bit_offset))
#define SETBIT(byte_addr, bit_offset) BSET(byte_addr, bit_offset)

#define BRST(byte_addr, bit_offset) (byte_addr &= ~(1 << bit_offset))
#define CLEARBIT(byte_addr, bit_offset) BRST(byte_addr, bit_offset)

#define BCHK(byte_addr, bit_offset) (byte_addr & (1 << bit_offset))
#define CHECKBIT(byte_addr, bit_offset) BCHK(byte_addr, bit_offset)

#define BFLP(byte_addr, bit_offset) (byte_addr ^= (1 << bit_offset))
#define TOGGLEBIT(byte_addr, bit_offset) BFLP(byte_addr, bit_offset)
#define NOWFLIPIT(byte_addr, bit_offset) BFLP(byte_addr, bit_offset)
#define FLIPITGOOD(byte_addr, bit_offset) BFLP(byte_addr, bit_offset)

#define BSETP(byte_addr_bit_offset_pair) SETBIT(COMBA(byte_addr_bit_offset_pair), COMBB(byte_addr_bit_offset_pair))
#define SETBIT_PAIR(byte_addr_bit_offset_pair) BSETP(byte_addr_bit_offset_pair)

#define BRSTP(byte_addr_bit_offset_pair) CLEARBIT(COMBA(byte_addr_bit_offset_pair), COMBB(byte_addr_bit_offset_pair))
#define CLEARBIT_PAIR(byte_addr_bit_offset_pair) BRSTP(byte_addr_bit_offset_pair)

#define BCHKP(byte_addr_bit_offset_pair) CHECKBIT(COMBA(byte_addr_bit_offset_pair), COMBB(byte_addr_bit_offset_pair))
#define CHECKBIT_PAIR(byte_addr_bit_offset_pair) BCHKP(byte_addr_bit_offset_pair)

#define BFLPP(byte_addr_bit_offset_pair) FLIPBIT(COMBA(byte_addr_bit_offset_pair), COMBB(byte_addr_bit_offset_pair))
#define TOGGLEBIT_PAIR(byte_addr_bit_offset_pair) BFLPP(byte_addr_bit_offset_pair)

#define BMASKSET(byte, mask) (byte |= (mask))
#define SETBITMASK(byte, mask) BMASKSET(byte, mask)
#define SETBITS(byte, mask) BMASKSET(byte, mask)

#define BMASKRST(byte, mask) (byte &= (~mask))
#define CLEARBITMASK(byte, mask) BMASKRST(byte, mask)
#define CLEARBITS(byte, mask) BMASKRST(byte, mask)

#define BMASKCHK(byte, mask) (byte & (mask))
#define CHECKBITMASK(byte, mask) BMASKCHK(byte, mask)
#define CHECKBITS(byte, mask) BMASKCHK(byte, mask)

#define BMASKFLP(byte, mask) (byte ^= (mask))
#define TOGGLEBITMASK(byte, mask) BMASKFLP(byte, mask)
#define TOGGLEBITS(byte, mask) BMASKFLP(byte, mask)


CBYTE BITMASK[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

#define B0(byte) CHECKBITS(byte, BITMASK[0])


STRUCT PACKED _bitpack
{
	BYTE b0 : 1;
	BYTE b1 : 1;
	BYTE b2 : 1;
	BYTE b3 : 1;
	BYTE b4 : 1;
	BYTE b5 : 1;
	BYTE b6 : 1;
	BYTE b7 : 1;
};

typedef volatile struct _bitpack _bitpack_t, bitpack, BitPack, BITPACK, * PBITPACK, & RBITPACK;
typedef const _bitpack_t CBITPACK, * PCBITPACK, & RCBITPACK;

IGNORE_WARNING(-Wstrict-aliasing)
#define B(value, i) (((PBITPACK)&value)->b##i)


STRUCT _bitfield
{
public:

	_bitfield(BYTE);
	_bitfield(RBYTE);
	_bitfield(PBYTE);

	VOLATILE UNION
	{
		PBYTE Byte;
		PBITPACK Bits;
	} PACKED;

	CONST SIZE Size() const;

	BOOL operator[](SIZE index);

private:

	VOLATILE PBYTE _pByte;
	VOLATILE RBYTE _rByte;

	BYTE Value() const;
	VOID SetValue(BYTE);
	BYTE Mask(BYTE) const;
	BIT Bit(SIZE);

	struct _bitproxy;
	typedef struct _bitproxy _bitproxy_t, bitproxy, BitProxy, BITPROXY, * PBITPROXY, & RBITPROXY;
	typedef const _bitproxy_t CBITPROXY, * PCBITPROXY, & RCBITPROXY;
};

typedef struct _bitfield _bitfield_t, bitfield, BitField, BITFIELD, * PBITFIELD, & RBITFIELD;
typedef const _bitfield_t CBITFIELD, * PCBITFIELD, & RCBITFIELD;

#endif
