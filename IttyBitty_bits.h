/*******************************************************************************
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*******************************************************************************/

#ifndef _ITTYBITTY_BITS_H
#define _ITTYBITTY_BITS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_util.h"


/* BIT OFFSET, L/H NYBBLE, BYTE, & WORD MASK CONSTANT MAPS; NOTE: PRIMARY FOR REFERENCE PURPOSES */

//CBYTE BYTE_BIT_MASKS[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
//CBYTE BYTE_NYBBLE_MASKS[] = { 0x0F, 0xF0 };

//CWORD WORD_BIT_MASKS[] = { 
//	0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,		// LOW BYTE
//	0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };	// HIGH BYTE
//CWORD WORD_BYTE_MASKS[] = { 0x00FF, 0xFF00 };
	
//CWORD DWORD_BIT_MASKS[] = { 
//	0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00800000,		// LSB; LOW WORD
//	0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,		// BYTE 1
//	0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,		// BYTE 2; HIGH WORD
//	0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000	};	// MSB
//CDWORD DWORD_BYTE_MASKS[] = { 0x000000FF, 0x00FF0000, 0x0000FF00, 0xFF000000 };
//CDWORD DWORD_WORD_MASKS[] = { 0x0000FFFF, 0xFFFF0000 };


/* BIT-WISE OPERATOR ALIASES */

#define NOT ~
#define AND &
#define OR |
#define XOR ^
#define SHR >>
#define SHIFT_RIGHT SHR
#define SHL <<
#define SHIFT_LEFT SHL


/* MASK GENERATOR MACROS */

#define BIT_MASK(bit_offset) (1 << (bit_offset))
#define NOT_BIT_MASK(bit_offset) NOT BIT_MASK(bit_offset)

#define NYBBLE_MASK(nybble_offset) (0x0F << (nybble_offset) * 4)
#define NOT_NYBBLE(nybble_offset) NOT NYBBLE_MASK(nybble_offset)

#define BYTE_MASK(byte_offset) (0xFF << (byte_offset) * 8)
#define NOT_BYTE(byte_offset) NOT BYTE_MASK(byte_offset)

#define WORD_MASK(word_offset) (0xFFFF << (word_offset) * 16)
#define NOT_WORD(word_offset) NOT WORD_MASK(word_offset)

#define DWORD_MASK(dword_offset) (0xFFFF << (dword_offset) * 32)
#define NOT_DWORD(dword_offset) NOT DWORD_MASK(dword_offset)


/* BITMASK MACROS (FOR MULTI-BIT MANIPULATION OPERATIONS) */

#define BMASKNOT(addr, mask) MASK(addr, NOT (mask))
#define NOT_BITS(addr, mask) BMASKNOT(addr, mask)

#define BMASKSET(addr, mask) ((addr) |= (mask))
#define SET_BITS(addr, mask) BMASKSET(addr, mask)

#define BMASKRST(addr, mask) ((addr) &= ~(mask))
#define RESET_BITS(addr, mask) BMASKRST(addr, mask)
#define UNSET_BITS(addr, mask) BMASKRST(addr, mask)
#define CLEAR_BITS(addr, mask) BMASKRST(addr, mask)

#define BMASKCHK(addr, mask) ((addr) & (mask))
#define MASK(addr, mask) BMASKCHK(addr, mask)
#define CHECK_BITS(addr, mask) BMASKCHK(addr, mask)
#define CHECK_BITS_SET(addr, mask) BMASKCHK(addr, mask)

#define BMASKSNT(addr, mask) ((addr) & ~(mask))
#define CHECK_BITS_NOT(addr, mask) BMASKSNT(addr, mask)
#define CHECK_BITS_UNSET(addr, mask) BMASKSNT(addr, mask)

#define BMASKFLP(addr, mask) ((addr) ^= (mask))
#define FLIP_BITS(addr, mask) BMASKFLP(addr, mask)
#define TOGGLE_BITS(addr, mask) BMASKFLP(addr, mask)

#define SET_BITS_FROM(addr, mask, from_addr) BMASKSET(addr, MASK(from_addr, mask))

#define CLEAR_BITS_FROM(addr, mask, from_addr) BMASKRST(addr, MASK(from_addr, mask))

#define COPY_BITS(addr, mask, from_addr) ((addr) = NOT_BITS(addr, mask) | MASK(addr, from_addr))

// CORRESPONDING EXPANSION MACROS...

#define BMASKNOTP(addr_mask_pair) BMASKNOT(COMBA(addr_mask_pair), COMBB(addr_mask_pair))
#define NOT_BITS_PAIR(addr_mask_pair) BMASKNOTP(addr_mask_pair)

#define BMASKSETP(addr_mask_pair) BMASKSET(COMBA(addr_mask_pair), COMBB(addr_mask_pair))
#define SET_BITS_PAIR(addr_mask_pair) BMASKSETP(addr_mask_pair)

#define BMASKRSTP(addr_mask_pair) BMASKRST(COMBA(addr_mask_pair), COMBB(addr_mask_pair))
#define RESET_BITS_PAIR(addr_mask_pair) BMASKRSTP(addr_mask_pair)
#define UNSET_BITS_PAIR(addr_mask_pair) BMASKRSTP(addr_mask_pair)
#define CLEAR_BITS_PAIR(addr_mask_pair) BMASKRSTP(addr_mask_pair)

#define BMASKCHKP(addr_mask_pair) BMASKCHK(COMBA(addr_mask_pair), COMBB(addr_mask_pair))
#define MASK_PAIR(addr_mask_pair) BMASKCHKP(addr_mask_pair)
#define CHECK_BITS_PAIR(addr_mask_pair) BMASKCHKP(addr_mask_pair)
#define CHECK_BITS_SET_PAIR(addr_mask_pair) BMASKCHKP(addr_mask_pair)

#define BMASKSNTP(addr_mask_pair) BMASKSNT(COMBA(addr_mask_pair), COMBB(addr_mask_pair))
#define CHECK_BITS_NOT_PAIR(addr_mask_pair) BMASKSNTP(addr_mask_pair)
#define CHECK_BITS_UNSET_PAIR(addr_mask_pair) BMASKSNTP(addr_mask_pair)

#define BMASKFLPP(addr_mask_pair) BMASKFLP(COMBA(addr_mask_pair), COMBB(addr_mask_pair))
#define FLIP_BITS_PAIR(addr_mask_pair) BMASKFLPP(addr_mask_pair)
#define TOGGLE_BITS_PAIR(addr_mask_pair) BMASKFLPP(addr_mask_pair)

#define SET_BITS_FROM_TUPLE(addr_mask_from_addr_tuple) \
	SET_BITS_FROM(COMBA(addr_mask_from_addr_tuple), COMBB(addr_mask_from_addr_tuple), COMBC(addr_mask_from_addr_tuple))

#define CLEAR_BITS_FROM_TUPLE(addr_mask_from_addr_tuple) \
	CLEAR_BITS_FROM(COMBA(addr_mask_from_addr_tuple), COMBB(addr_mask_from_addr_tuple), COMBC(addr_mask_from_addr_tuple))

#define COPY_BITS_TUPLE(addr_mask_from_addr_tuple) \
	COPY_BITS(COMBA(addr_mask_from_addr_tuple), COMBB(addr_mask_from_addr_tuple), COMBC(addr_mask_from_addr_tuple))


/* (SINGLE) BIT-TWIDDLING MACROS */

#define BNOT(addr, bit_offset) MASK(addr, NOT_BIT_MASK(bit_offset))
#define NOT_BIT(addr, bit_offset) BNOT(addr, bit_offset)

#define BSET(addr, bit_offset) ((addr) |= BMASK(bit_offset))
#define SET_BIT(addr, bit_offset) BSET(addr, bit_offset)

#define BRST(addr, bit_offset) ((addr) &= ~BMASK(bit_offset))
#define RESET_BIT(addr, bit_offset) BRST(addr, bit_offset)
#define UNSET_BIT(addr, bit_offset) BRST(addr, bit_offset)
#define CLEAR_BIT(addr, bit_offset) BRST(addr, bit_offset)

#define BCHK(addr, bit_offset) CHECK_BITS((addr) & BMASK(bit_offset))
#define CHECK_BIT(addr, bit_offset) BCHK(addr, bit_offset)
#define CHECK_SET(addr, bit_offset) BCHK(addr, bit_offset)

#define BSNT(addr, bit_offset) ~BCHK(addr, bit_offset)
#define CHECK_BIT_NOT(addr, bit_offset) BSNT(addr, bit_offset)
#define CHECK_UNSET(addr, bit_offset) BSNT(addr, bit_offset)

#define BFLP(addr, bit_offset) ((addr) ^= BMASK(bit_offset))
#define FLIP_BIT(addr, bit_offset) BFLP(addr, bit_offset)
#define TOGGLE_BIT(addr, bit_offset) BFLP(addr, bit_offset)
#define NOW_FLIP_BIT(addr, bit_offset) BFLP(addr, bit_offset)
#define FLIP_BIT_GOOD(addr, bit_offset) BFLP(addr, bit_offset) // [heh...]

#define SET_BIT_TO(addr, bit_offset, value) ((addr) = BNOT(bit_offset) | (value) << bit_offset)

#define SET_BIT_FROM(addr, bit_offset, from_addr) SET_BIT_TO(addr, bit_offset, BCHK(from_addr, bit_offset))

#define CLEAR_BIT_FROM(addr, bit_offset, from_addr) SET_BIT_TO(addr, bit_offset, BSNT(from_addr, bit_offset))

#define COPY_BIT(addr, bit_offset, from_addr) ((addr) = NOT_BIT(addr, bit_offset) | BCHK(addr, bit_offset))

// CORRESPONDING EXPANSION MACROS...

#define BNOTP(addr_bit_offset_pair) BNOT(COMBA(addr_bit_offset_pair), COMBB(addr_bit_offset_pair))
#define NOT_BIT_PAIR(addr_bit_offset_pair) BNOTP(addr_bit_offset_pair)

#define BSETP(addr_bit_offset_pair) BSET(COMBA(addr_bit_offset_pair), COMBB(addr_bit_offset_pair))
#define SET_BIT_PAIR(addr_bit_offset_pair) BSETP(addr_bit_offset_pair)

#define BRSTP(addr_bit_offset_pair) BRST(COMBA(addr_bit_offset_pair), COMBB(addr_bit_offset_pair))
#define UNSET_BIT_PAIR(addr_bit_offset_pair) BRSTP(addr_bit_offset_pair)
#define RESET_BIT_PAIR(addr_bit_offset_pair) BRSTP(addr_bit_offset_pair)
#define CLEAR_BIT_PAIR(addr_bit_offset_pair) BRSTP(addr_bit_offset_pair)

#define BCHKP(addr_bit_offset_pair) BCHK(COMBA(addr_bit_offset_pair), COMBB(addr_bit_offset_pair))
#define CHECK_BIT_PAIR(addr_bit_offset_pair) BCHKP(addr_bit_offset_pair)
#define CHECK_SET_PAIR(addr_bit_offset_pair) BCHKP(addr_bit_offset_pair)

#define BSNTP(addr_bit_offset_pair) BSNT(COMBA(addr_bit_offset_pair), COMBB(addr_bit_offset_pair))
#define CHECK_BIT_NOT_PAIR(addr_bit_offset_pair) BSNTP(addr_bit_offset_pair)
#define CHECK_UNSET_PAIR(addr_bit_offset_pair) BSNTP(addr_bit_offset_pair)

#define BFLPP(addr_bit_offset_pair) BFLP(COMBA(addr_bit_offset_pair), COMBB(addr_bit_offset_pair))
#define FLIP_BIT_PAIR(addr_bit_offset_pair) BFLPP(addr_bit_offset_pair)
#define TOGGLE_BIT_PAIR(addr_bit_offset_pair) BFLPP(addr_bit_offset_pair)

#define SET_BIT_TO_TUPLE(addr_mask_value_tuple) SET_BIT_TO(COMBA(addr_mask_value_tuple), \
	COMBB(addr_mask_value_tuple), COMBC(addr_mask_value_tuple))

#define SET_BIT_FROM_TUPLE(addr_bit_offset_from_addr_tuple) SET_BIT_FROM(COMBA(addr_bit_offset_from_addr_tuple), \
	COMBB(addr_bit_offset_from_addr_tuple), COMBC(addr_bit_offset_from_addr_tuple))

#define CLEAR_BIT_FROM_TUPLE(addr_bit_offset_from_addr_tuple) CLEAR_BIT_FROM(COMBA(addr_bit_offset_from_addr_tuple), \
	COMBB(addr_bit_offset_from_addr_tuple), COMBC(addr_bit_offset_from_addr_tuple))

#define COPY_BIT_TUPLE(addr_bit_offset_from_addr_tuple) COPY_BIT(COMBA(addr_bit_offset_from_addr_tuple), \
	COMBB(addr_bit_offset_from_addr_tuple), COMBC(addr_bit_offset_from_addr_tuple))


/* BIT-SPECIFIC MACRO ALIASES FOR BYTES */

#define BIT0_MASK BMASK(0)
#define SET_BIT0(byte) SET_BIT(byte, 0)
#define CLEAR_BIT0(byte) CLEAR_BIT(byte, 0)
#define CHECK_BIT0(byte) CHECK_BIT(byte, 0)
#define CHECK_UNSET_BIT0(byte) CHECK_UNSET(byte, 0)
#define TOGGLE_BIT0(byte) TOGGLEBIT(byte, 0)

#define BIT1_MASK BMASK(1)
#define SET_BIT1(byte) SET_BIT(byte, 1)
#define CLEAR_BIT1(byte) CLEAR_BIT(byte, 1)
#define CHECK_BIT1(byte) CHECK_BIT(byte, 1)
#define CHECK_UNSET_BIT1(byte) CHECK_UNSET(byte, 1)
#define TOGGLEBIT1(byte) TOGGLEBIT(byte, 1)

#define BIT2_MASK BMASK(2)
#define SET_BIT2(byte) SET_BIT(byte, 2)
#define CLEAR_BIT2(byte) CLEAR_BIT(byte, 2)
#define CHECK_BIT2(byte) CHECK_BIT(byte, 2)
#define CHECK_UNSET_BIT2(byte) CHECK_UNSET_BIT(byte, 2)
#define TOGGLE_BIT2(byte) TOGGLEBIT(byte, 2)

#define BIT3_MASK BMASK(3)
#define SET_BIT3(byte) SET_BIT(byte, 3)
#define CLEAR_BIT3(byte) CLEAR_BIT(byte, 3)
#define CHECK_BIT3(byte) CHECK_BIT(byte, 3)
#define CHECK_UNSET_BIT3(byte) CHECK_UNSET_BIT(byte, 3)
#define TOGGLE_BIT3(byte) TOGGLEBIT(byte, 3)

#define BIT4_MASK BMASK(4)
#define SET_BIT4(byte) SET_BIT(byte, 4)
#define CLEAR_BIT4(byte) CLEAR_BIT(byte, 4)
#define CHECK_BIT4(byte) CHECK_BIT(byte, 4)
#define CHECK_UNSET_BIT4(byte) CHECK_UNSET_BIT(byte, 4)
#define TOGGLE_BIT4(byte) TOGGLEBIT(byte, 4)

#define BIT5_MASK BMASK(5)
#define SET_BIT5(byte) SET_BIT(byte, 5)
#define CLEAR_BIT5(byte) CLEAR_BIT(byte, 5)
#define CHECK_BIT5(byte) CHECK_BIT(byte, 5)
#define CHECK_UNSET_BIT5(byte) CHECK_UNSET_BIT(byte, 5)
#define TOGGLE_BIT5(byte) TOGGLEBIT(byte, 5)

#define BIT6_MASK BMASK(6)
#define SET_BIT6(byte) SET_BIT(byte, 6)
#define CLEAR_BIT6(byte) CLEAR_BIT(byte, 6)
#define CHECK_BIT6(byte) CHECK_BIT(byte, 6)
#define CHECK_UNSET_BIT6(byte) CHECK_UNSET_BIT(byte, 6)
#define TOGGLE_BIT6(byte) TOGGLEBIT(byte, 6)

#define BIT7_MASK BMASK(7)
#define SET_BIT7(byte) SET_BIT(byte, 7)
#define CLEAR_BIT7(byte) CLEAR_BIT(byte, 7)
#define CHECK_BIT7(byte) CHECK_BIT(byte, 7)
#define CHECK_UNSET_BIT7(byte) CHECK_UNSET_BIT(byte, 7)
#define TOGGLE_BIT7(byte) TOGGLEBIT(byte, 7)


/* BYTE MANIPULATION MACROS */

#define LOW_NYBBLE_MASK NYBBLE_MASK(0)
#define HIGH_NYBBLE_MASK NYBBLE_MASK(1)

#define LOW_NYBBLE(byte_addr) MASK(byte_addr, LOW_NYBBLE_MASK)
#define HIGH_NYBBLE(byte_addr) MASK(byte_addr, HIGH_NYBBLE_MASK)

#define SET_LOW_NYBBLE(byte_addr, from_addr) SET_BITS(byte_addr, LOW_NYBBLE_MASK, from_addr)
#define SET_HIGH_NYBBLE(byte_addr, from_addr) SET_BITS(byte_addr, HIGH_NYBBLE_MASK, from_addr)


/* BYTE MANIPULATION MACROS */

#define LOW_BYTE_MASK BYTE_MASK(0)
#define HIGH_BYTE_MASK BYTE_MASK(1)

#define LOW_BYTE(word_addr) MASK(word_addr, LOW_BYTE_MASK)
#define HIGH_BYTE(word_addr) MASK(word_addr, HIGH_BYTE_MASK)

#define SET_LOW_BYTE(word_addr, from_addr) SET_BITS(word_addr, LOW_BYTE_MASK, from_addr)
#define SET_HIGH_BYTE(word_addr, from_addr) SET_BITS(word_addr, HIGH_BYTE_MASK, from_addr)

#define CHECK_BYTE(addr, byte_offset) MASK(addr, BYTE_MASK(byte_offset))

#define SET_BYTE(addr, byte_offset, from_addr) SET_BITS(addr, BYTE_MASK(byte_offset), from_addr)

#define CLEAR_BYTE(addr, byte_offset, from_addr) CLEAR_BITS(addr, BYTE_MASK(byte_offset), from_addr)

#define COPY_BYTE(addr, byte_offset, from_addr) COPY_BITS(addr, BYTE_MASK(byte_offset), from_addr)


/* WORD MANIPULATION MACROS */

#define LOW_WORD_MASK WORD_MASK(0)
#define HIGH_WORD_MASK WORD_MASK(1)

#define LOW_WORD(dword_addr) MASK(dword_addr, LOW_WORD_MASK)
#define HIGH_WORD(dword_addr) MASK(dword_addr, HIGH_WORD_MASK)

#define SET_LOW_WORD(dword_addr, from_addr) SET_BITS(dword_addr, LOW_WORD_MASK, from_addr)
#define SET_HIGH_WORD(dword_addr, from_addr) SET_BITS(dword_addr, HIGH_WORD_MASK, from_addr)

#define CHECK_WORD(addr, word_offset) MASK(addr, WORD_MASK(word_offset))

#define SET_WORD(addr, word_offset, from_addr) SET_BITS(addr, WORD_MASK(word_offset), from_addr)

#define CLEAR_WORD(addr, word_offset, from_addr) CLEAR_BITS(addr, WORD_MASK(word_offset), from_addr)

#define COPY_WORD(addr, word_offset, from_addr) COPY_BITS(addr, WORD_MASK(word_offset), from_addr)


/* SUPRESS COMPILER WARNINGS RELATED TO BITFIELD ALIASING */

IGNORE_WARNING(-Wstrict-aliasing)


/* BIT-PACKING / BIT REFERENCE MACROS */

#define PACK_BYTE(byte_addr) (*reinterpret_cast<IttyBitty::PBITPACK>(byte_addr))
#define PACK_BYTE_VAL(byte_val) PACK_BYTE(&byte_val)

#define _B(byte_addr, i) (BIT)(PACK_BYTE(byte_addr).b##i)

#define BIT0(byte) _B(byte, 0)
#define BIT1(byte) _B(byte, 1)
#define BIT2(byte) _B(byte, 2)
#define BIT3(byte) _B(byte, 3)
#define BIT4(byte) _B(byte, 4)
#define BIT5(byte) _B(byte, 5)
#define BIT6(byte) _B(byte, 6)
#define BIT7(byte) _B(byte, 7)


namespace IttyBitty
{
	/* [BITPACK]: BITFIELD STRUCT FOR BIT-PACKING / BIT-REFERENCING OF A MEMORY BYTE */

	struct _BitPack;
	typedef volatile struct _BitPack BitPack, BITPACK, * PBITPACK, & RBITPACK, ** PPBITPACK;
	typedef const struct _BitPack CBITPACK, * PCBITPACK, & RCBITPACK, ** PPCBITPACK;

	BITFIELD_STRUCT _BitPack
	{
	public:

		BIT b0 : 1;
		BIT b1 : 1;
		BIT b2 : 1;
		BIT b3 : 1;
		BIT b4 : 1;
		BIT b5 : 1;
		BIT b6 : 1;
		BIT b7 : 1;

		_BitPack(RCBITPACK other);

		STATIC RCBITPACK NULL_OBJECT();

		STATIC CSIZE BitSize();

		BIT operator[](SIZE i) const;

		BIT Bit(SIZE i) const;
	};
}


#endif
