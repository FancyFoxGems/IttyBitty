/**********************************************************************************
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_BITS_H
#define _ITTYBITTY_BITS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
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


/* REDEFINE [_BV] MACRO FOR CAPABILITY OF ADDRESSING MSB (bit-offset 15) OF AN <<UNSIGNED>> INT */

#undef _BV
#define _BV(bit_offset) (1U << (bit_offset))


/* BIT-WISE OPERATOR ALIASES */

#define NOT ~
#define AND &
#define OR |
#define XOR ^
#define SHR >>
#define SHIFT_RIGHT SHR
#define SHL <<
#define SHIFT_LEFT SHL

#define MASK(ref, mask) ((ref) & (mask))
#define INVERSE_MASK(ref, mask) ((ref) & ~(mask))


/* MASK GENERATOR MACROS */

#define BIT_MASK(bit_offset) _BV(bit_offset)
#define BMASK(bit_offset) BIT_MASK(bit_offset)
#define NOT_BIT(bit_offset) NOT BIT_MASK(bit_offset)

#define NYBBLE_MASK(nybble_offset) (0x0F << (nybble_offset) * 4)
#define NOT_NYBBLE(nybble_offset) NOT NYBBLE_MASK(nybble_offset)

#define BYTE_MASK(byte_offset) (0xFF << (byte_offset) * 8)
#define NOT_BYTE(byte_offset) NOT BYTE_MASK(byte_offset)

#define WORD_MASK(word_offset) (0xFFFF << (word_offset) * 16)
#define NOT_WORD(word_offset) NOT WORD_MASK(word_offset)

#define DWORD_MASK(dword_offset) (0xFFFF << (dword_offset) * 32)
#define NOT_DWORD(dword_offset) NOT DWORD_MASK(dword_offset)


/* BITMASK MACROS (FOR MULTI-BIT MANIPULATION OPERATIONS) */

#define BMASKNOT(ref, mask) INVERSE_MASK(ref, mask)
#define NOT_BITS(ref, mask) BMASKNOT(ref, mask)

#define BITS(ref, mask) BMASK(ref, mask)
#define CHECK_BITS(ref, mask) BMASK(ref, mask)
#define CHECK_BITS_SET(ref, mask) BMASK(ref, mask)

#define BMASKSNT(ref, mask) ~MASK(ref, mask)
#define CHECK_BITS_SNT(ref, mask) BMASKSNT(ref, mask)
#define CHECK_BITS_UNSET(ref, mask) BMASKSNT(ref, mask)

#define BMASKSET(ref, mask) ((ref) |= (mask))
#define SET_BITS(ref, mask) BMASKSET(ref, mask)

#define BMASKRST(ref, mask) ((ref) &= ~(mask))
#define RESET_BITS(ref, mask) BMASKRST(ref, mask)
#define UNSET_BITS(ref, mask) BMASKRST(ref, mask)
#define CLEAR_BITS(ref, mask) BMASKRST(ref, mask)

#define BMASKFLP(ref, mask) ((ref) ^= (mask))
#define FLIP_BITS(ref, mask) BMASKFLP(ref, mask)
#define TOGGLE_BITS(ref, mask) BMASKFLP(ref, mask)

#define SET_BITS_FROM(ref, mask, from_ref) BMASKSET(ref, MASK(from_ref, mask))

#define CLEAR_BITS_FROM(ref, mask, from_ref) BMASKRST(ref, MASK(from_ref, mask))

#define COPY_BITS(ref, mask, from_ref) ((ref) = NOT_BITS(ref, mask) | MASK(ref, from_ref))

// CORRESPONDING EXPANSION MACROS...

#define BMASKNOTP(ref_mask_pair) BMASKNOT(ref_mask_pair)
#define NOT_BITS_PAIR(ref_mask_pair) BMASKNOT(ref_mask_pair)

#define BMASKP(ref_mask_pair) BMASK(ref_mask_pair)
#define BITS_PAIR(ref_mask_pair) BMASK(ref_mask_pair)
#define MASK_PAIR(ref_mask_pair) BMASK(ref_mask_pair)
#define CHECK_BITS_PAIR(ref_mask_pair) BMASK(ref_mask_pair)
#define CHECK_BITS_SET_PAIR(ref_mask_pair) BMASK(ref_mask_pair)

#define BMASKSNTP(ref_mask_pair) BMASKSNT(ref_mask_pair)
#define CHECK_BITS_SNT_PAIR(ref_mask_pair) BMASKSNT(ref_mask_pair)
#define CHECK_BITS_UNSET_PAIR(ref_mask_pair) BMASKSNT(ref_mask_pair)

#define BMASKSETP(ref_mask_pair) BMASKSET(ref_mask_pair)
#define SET_BITS_PAIR(ref_mask_pair) BMASKSET(ref_mask_pair)

#define BMASKRSTP(ref_mask_pair) BMASKRST(ref_mask_pair)
#define RESET_BITS_PAIR(ref_mask_pair) BMASKRST(ref_mask_pair)
#define UNSET_BITS_PAIR(ref_mask_pair) BMASKRST(ref_mask_pair)
#define CLEAR_BITS_PAIR(ref_mask_pair) BMASKRST(ref_mask_pair)

#define BMASKFLPP(ref_mask_pair) BMASKFL(ref_mask_pair)
#define FLIP_BITS_PAIR(ref_mask_pair) BMASKFLP(ref_mask_pair)
#define TOGGLE_BITS_PAIR(ref_mask_pair) BMASKFLP(ref_mask_pair)

#define SET_BITS_FROM_PAIR(ref_mask_pair, from_ref) SET_BITS_FROM(ref_mask_pair, from_ref)

#define CLEAR_BITS_FROM_PAIR(ref_mask_pair, from_ref) CLEAR_BITS_FROM(ref_mask_pair, from_ref)

#define COPY_BITS_PAIR(ref_mask_pair, from_ref) COPY_BITS(ref_mask_pair, from_ref)

#define SET_BITS_FROM_TUPLE(ref_mask_from_ref_tuple) SET_BITS_FROM(ref_mask_from_ref_tuple

#define CLEAR_BITS_FROM_TUPLE(ref_mask_from_ref_tuple) CLEAR_BITS_FROM(ref_mask_from_ref_tuple

#define COPY_BITS_TUPLE(ref_mask_from_ref_tuple) COPY_BITS(ref_mask_from_ref_tuple


/* (SINGLE) BIT-TWIDDLING MACROS */

#define BNOT(ref, bit_offset) NOT_BIT(ref, bit_offset)

#define BCHK(ref, bit_offset) CHECK_BITS((ref) & BMASK(bit_offset))
#define CHECK_BIT(ref, bit_offset) BCHK(ref, bit_offset)
#define CHECK_SET(ref, bit_offset) BCHK(ref, bit_offset)

#define BSNT(ref, bit_offset) ~BCHK(ref, bit_offset)
#define CHECK_BIT_NOT(ref, bit_offset) BSNT(ref, bit_offset)
#define CHECK_UNSET(ref, bit_offset) BSNT(ref, bit_offset)

#define BSET(ref, bit_offset) ((ref) |= BMASK(bit_offset))
#define SET_BIT(ref, bit_offset) BSET(ref, bit_offset)

#define BRST(ref, bit_offset) ((ref) &= ~BMASK(bit_offset))
#define RESET_BIT(ref, bit_offset) BRST(ref, bit_offset)
#define UNSET_BIT(ref, bit_offset) BRST(ref, bit_offset)
#define CLEAR_BIT(ref, bit_offset) BRST(ref, bit_offset)

#define BFLP(ref, bit_offset) ((ref) ^= BMASK(bit_offset))
#define FLIP_BIT(ref, bit_offset) BFLP(ref, bit_offset)
#define TOGGLE_BIT(ref, bit_offset) BFLP(ref, bit_offset)
#define NOW_FLIP_BIT(ref, bit_offset) BFLP(ref, bit_offset)
#define FLIP_BIT_GOOD(ref, bit_offset) BFLP(ref, bit_offset) // [heh...]

#define SET_BIT_TO(ref, bit_offset, value) ((ref) = BNOT(bit_offset) | (value) << bit_offset)

#define SET_BIT_FROM(ref, bit_offset, from_ref) SET_BIT_TO(ref, bit_offset, BCHK(from_ref, bit_offset))

#define CLEAR_BIT_FROM(ref, bit_offset, from_ref) SET_BIT_TO(ref, bit_offset, BSNT(from_ref, bit_offset))

#define COPY_BIT(ref, bit_offset, from_ref) ((ref) = NOT_BIT(ref, bit_offset) | BCHK(ref, bit_offset))

// CORRESPONDING EXPANSION MACROS...

#define BNOTP(ref_bit_offset_pair) BNOT(ref_bit_offset_pair)
#define NOT_BIT_PAIR(ref_bit_offset_pair) BNOT(ref_bit_offset_pair)

#define BCHKP(ref_bit_offset_pair) BCHK(ref_bit_offset_pair)
#define CHECK_BIT_PAIR(ref_bit_offset_pair) BCHK(ref_bit_offset_pair)
#define CHECK_SET_PAIR(ref_bit_offset_pair) BCHK(ref_bit_offset_pair)

#define BSNTP(ref_bit_offset_pair) BSNT(ref_bit_offset_pair)
#define CHECK_BIT_NOT_PAIR(ref_bit_offset_pair) BSNT(ref_bit_offset_pair)
#define CHECK_UNSET_PAIR(ref_bit_offset_pair) BSNT(ref_bit_offset_pair)

#define BSETP(ref_bit_offset_pair) BSET(ref_bit_offset_pair)
#define SET_BIT_PAIR(ref_bit_offset_pair) BSET(ref_bit_offset_pair)

#define BRSTP(ref_bit_offset_pair) BRST(ref_bit_offset_pair)
#define UNSET_BIT_PAIR(ref_bit_offset_pair) BRST(ref_bit_offset_pair)
#define RESET_BIT_PAIR(ref_bit_offset_pair) BRST(ref_bit_offset_pair)
#define CLEAR_BIT_PAIR(ref_bit_offset_pair) BRST(ref_bit_offset_pair)

#define BFLPP(ref_bit_offset_pair) BFLP(ref_bit_offset_pair)
#define FLIP_BIT_PAIR(ref_bit_offset_pair) BFLP(ref_bit_offset_pair)
#define TOGGLE_BIT_PAIR(ref_bit_offset_pair) BFLP(ref_bit_offset_pair)

#define SET_BIT_TO_PAIR(ref_mask_pair, value) SET_BIT_TO(ref_mask_pair, value)

#define SET_BIT_FROM_PAIR(ref_bit_offset_pair, from_ref) SET_BIT_FROM(ref_bit_offset_pair, from_ref)

#define CLEAR_BIT_FROM_PAIR(ref_bit_offset_pair, from_ref) CLEAR_BIT_FROM(ref_bit_offset_pair, from_ref)

#define COPY_BIT_PAIR(ref_bit_offset_pair, from_ref) COPY_BIT(ref_bit_offset_pair, from_ref)

#define SET_BIT_TO_TUPLE(ref_mask_value_tuple) SET_BIT_TO(ref_mask_value_tuple)

#define SET_BIT_FROM_TUPLE(ref_bit_offset_from_ref_tuple) SET_BIT_FROM(ref_bit_offset_from_ref_tuple)

#define CLEAR_BIT_FROM_TUPLE(ref_bit_offset_from_ref_tuple) CLEAR_BIT_FROM(ref_bit_offset_from_ref_tuple)

#define COPY_BIT_TUPLE(ref_bit_offset_from_ref_tuple) COPY_BIT(ref_bit_offset_from_ref_tuple)


/* BIT-SPECIFIC MACRO ALIASES FOR BYTES */

#define BIT0_MASK BMASK(0)
#define CHECK_BIT0(byte_ref) CHECK_BIT(byte_ref, 0)
#define CHECK_UNSET_BIT0(byte_ref) CHECK_UNSET(byte_ref, 0)
#define SET_BIT0(byte_ref) SET_BIT(byte_ref, 0)
#define CLEAR_BIT0(byte_ref) CLEAR_BIT(byte_ref, 0)
#define TOGGLE_BIT0(byte_ref) TOGGLE_BIT(byte_ref, 0)

#define BIT1_MASK BMASK(1)
#define CHECK_BIT1(byte_ref) CHECK_BIT(byte_ref, 1)
#define CHECK_UNSET_BIT1(byte_ref) CHECK_UNSET(byte_ref, 1)
#define SET_BIT1(byte_ref) SET_BIT(byte_ref, 1)
#define CLEAR_BIT1(byte_ref) CLEAR_BIT(byte_ref, 1)
#define TOGGLE_BIT1(byte_ref) TOGGLE_BIT(byte_ref, 1)

#define BIT2_MASK BMASK(2)
#define CHECK_BIT2(byte_ref) CHECK_BIT(byte_ref, 2)
#define CHECK_UNSET_BIT2(byte_ref) CHECK_UNSET_BIT(byte_ref, 2)
#define SET_BIT2(byte_ref) SET_BIT(byte_ref, 2)
#define CLEAR_BIT2(byte_ref) CLEAR_BIT(byte_ref, 2)
#define TOGGLE_BIT2(byte_ref) TOGGLE_BIT(byte_ref, 2)

#define BIT3_MASK BMASK(3)
#define CHECK_BIT3(byte_ref) CHECK_BIT(byte_ref, 3)
#define CHECK_UNSET_BIT3(byte_ref) CHECK_UNSET_BIT(byte_ref, 3)
#define SET_BIT3(byte_ref) SET_BIT(byte_ref, 3)
#define CLEAR_BIT3(byte_ref) CLEAR_BIT(byte_ref, 3)
#define TOGGLE_BIT3(byte_ref) TOGGLE_BIT(byte_ref, 3)

#define BIT4_MASK BMASK(4)
#define CHECK_BIT4(byte_ref) CHECK_BIT(byte_ref, 4)
#define CHECK_UNSET_BIT4(byte_ref) CHECK_UNSET_BIT(byte_ref, 4)
#define SET_BIT4(byte_ref) SET_BIT(byte_ref, 4)
#define CLEAR_BIT4(byte_ref) CLEAR_BIT(byte_ref, 4)
#define TOGGLE_BIT4(byte_ref) TOGGLE_BIT(byte_ref, 4)

#define BIT5_MASK BMASK(5)
#define CHECK_BIT5(byte_ref) CHECK_BIT(byte_ref, 5)
#define CHECK_UNSET_BIT5(byte_ref) CHECK_UNSET_BIT(byte_ref, 5)
#define SET_BIT5(byte_ref) SET_BIT(byte_ref, 5)
#define CLEAR_BIT5(byte_ref) CLEAR_BIT(byte_ref, 5)
#define TOGGLE_BIT5(byte_ref) TOGGLE_BIT(byte_ref, 5)

#define BIT6_MASK BMASK(6)
#define CHECK_BIT6(byte_ref) CHECK_BIT(byte_ref, 6)
#define CHECK_UNSET_BIT6(byte_ref) CHECK_UNSET_BIT(byte_ref, 6)
#define SET_BIT6(byte_ref) SET_BIT(byte_ref, 6)
#define CLEAR_BIT6(byte_ref) CLEAR_BIT(byte_ref, 6)
#define TOGGLE_BIT6(byte_ref) TOGGLE_BIT(byte_ref, 6)

#define BIT7_MASK BMASK(7)
#define CHECK_BIT7(byte_ref) CHECK_BIT(byte_ref, 7)
#define CHECK_UNSET_BIT7(byte_ref) CHECK_UNSET_BIT(byte_ref, 7)
#define SET_BIT7(byte_ref) SET_BIT(byte_ref, 7)
#define CLEAR_BIT7(byte_ref) CLEAR_BIT(byte_ref, 7)
#define TOGGLE_BIT7(byte_ref) TOGGLE_BIT(byte_ref, 7)


/* BYTE MANIPULATION MACROS */

#define LOW_NYBBLE_MASK NYBBLE_MASK(0)
#define HIGH_NYBBLE_MASK NYBBLE_MASK(1)

#define LOW_NYBBLE(byte_ref) MASK(byte_ref, LOW_NYBBLE_MASK)
#define HIGH_NYBBLE(byte_ref) MASK(byte_ref, HIGH_NYBBLE_MASK)

#define CHECK_NYBBLE(byte_ref, nybble_offset) MASK(byte_ref, NYBBLE_MASK(nybble_offset))

#define CHECK_UNSET_NYBBLE(byte_ref, nybble_offset) MASK(byte_ref, NOT_NYBBLE(nybble_offset))

#define SET_LOW_NYBBLE(byte_ref, from_ref) SET_BITS(byte_ref, LOW_NYBBLE_MASK, from_ref)
#define SET_HIGH_NYBBLE(byte_ref, from_ref) SET_BITS(byte_ref, HIGH_NYBBLE_MASK, from_ref)

#define CLEAR_LOW_NYBBLE(byte_ref, from_ref) CLEAR_BITS(byte_ref, LOW_NYBBLE_MASK, from_ref)
#define CLEAR_HIGH_NYBBLE(byte_ref, from_ref) CLEAR_BITS(byte_ref, HIGH_NYBBLE_MASK, from_ref)

#define TOGGLE_LOW_NYBBLE(byte_ref, from_ref) TOGGLE_BITS(byte_ref, LOW_NYBBLE_MASK, from_ref)
#define TOGGLE_HIGH_NYBBLE(byte_ref, from_ref) TOGGLE_BITS(byte_ref, HIGH_NYBBLE_MASK, from_ref)

#define SET_NYBBLE(ref, nybble_offset, from_ref) SET_BITS(ref, NYBBLE_MASK(nybble_offset), from_ref)

#define CLEAR_NYBBLE(ref, nybble_offset, from_ref) CLEAR_BITS(ref, NYBBLE_MASK(nybble_offset), from_ref)

#define COPY_NYBBLE(ref, nybble_offset, from_ref) COPY_BITS(ref, NYBBLE_MASK(nybble_offset), from_ref)


/* BYTE MANIPULATION MACROS */

#define LOW_BYTE_MASK BYTE_MASK(0)
#define HIGH_BYTE_MASK BYTE_MASK(1)

#define LOW_BYTE(word_ref) MASK(word_ref, LOW_BYTE_MASK)
#define HIGH_BYTE(word_ref) MASK(word_ref, HIGH_BYTE_MASK)

#define CHECK_BYTE(ref, byte_offset) MASK(ref, BYTE_MASK(byte_offset))

#define CHECK_UNSET_BYTE(ref, byte_offset) MASK(ref, NOT_BYTE(byte_offset))

#define SET_LOW_BYTE(word_ref, from_ref) SET_BITS(word_ref, LOW_BYTE_MASK, from_ref)
#define SET_HIGH_BYTE(word_ref, from_ref) SET_BITS(word_ref, HIGH_BYTE_MASK, from_ref)

#define CLEAR_LOW_BYTE(word_ref, from_ref) CLEAR_BITS(word_ref, LOW_BYTE_MASK, from_ref)
#define CLEAR_HIGH_BYTE(word_ref, from_ref) CLEAR_BITS(word_ref, HIGH_BYTE_MASK, from_ref)

#define TOGGLE_LOW_BYTE(word_ref, from_ref) TOGGLE_BITS(word_ref, LOW_BYTE_MASK, from_ref)
#define TOGGLE_HIGH_BYTE(word_ref, from_ref) TOGGLE_BITS(word_ref, HIGH_BYTE_MASK, from_ref)

#define SET_BYTE(ref, byte_offset, from_ref) SET_BITS(ref, BYTE_MASK(byte_offset), from_ref)

#define CLEAR_BYTE(ref, byte_offset, from_ref) CLEAR_BITS(ref, BYTE_MASK(byte_offset), from_ref)

#define COPY_BYTE(ref, byte_offset, from_ref) COPY_BITS(ref, BYTE_MASK(byte_offset), from_ref)


/* WORD MANIPULATION MACROS */

#define LOW_WORD_MASK WORD_MASK(0)
#define HIGH_WORD_MASK WORD_MASK(1)

#define LOW_WORD(dword_ref) MASK(dword_ref, LOW_WORD_MASK)
#define HIGH_WORD(dword_ref) MASK(dword_ref, HIGH_WORD_MASK)

#define CHECK_WORD(ref, word_offset) MASK(ref, WORD_MASK(word_offset))

#define CHECK_UNSET_WORD(ref, word_offset) MASK(ref, NOT_WORD(word_offset))

#define SET_LOW_WORD(dword_ref, from_ref) SET_BITS(dword_ref, LOW_WORD_MASK, from_ref)
#define SET_HIGH_WORD(dword_ref, from_ref) SET_BITS(dword_ref, HIGH_WORD_MASK, from_ref)

#define CLEAR_LOW_WORD(dword_ref, from_ref) CLEAR_BITS(dword_ref, LOW_WORD_MASK, from_ref)
#define CLEAR_HIGH_WORD(dword_ref, from_ref) CLEAR_BITS(dword_ref, HIGH_WORD_MASK, from_ref)

#define TOGGLE_LOW_WORD(dword_ref, from_ref) TOGGLE_BITS(dword_ref, LOW_WORD_MASK, from_ref)
#define TOGGLE_HIGH_WORD(dword_ref, from_ref) TOGGLE_BITS(dword_ref, HIGH_WORD_MASK, from_ref)

#define SET_WORD(ref, word_offset, from_ref) SET_BITS(ref, WORD_MASK(word_offset), from_ref)

#define CLEAR_WORD(ref, word_offset, from_ref) CLEAR_BITS(ref, WORD_MASK(word_offset), from_ref)

#define COPY_WORD(ref, word_offset, from_ref) COPY_BITS(ref, WORD_MASK(word_offset), from_ref)


/* SUPRESS COMPILER WARNINGS RELATED TO BITFIELD ALIASING */

IGNORE_WARNING(-Wstrict-aliasing)


/* BIT-PACKING / BIT REFERENCE MACROS */

#define PACK_BYTE(byte_addr) reinterpret_cast<IttyBitty::PBITPACK>(byte_addr)
#define PACK_BYTE_REF(byte_ref) PACK_BYTE(&(byte_ref))
#define PACK_BYTE_CREF(byte_val) MAKE_CONST(PACK_BYTE(&(byte_val)))
#define PACK_BYTE_VAL(byte_val) PACK_BYTE_CREF(byte_val)

#define _B(byte_addr, i) (PACK_BYTE(byte_addr)->b##i)

#define BIT0(byte_addr) _B(byte_addr, 0)
#define BIT1(byte_addr) _B(byte_addr, 1)
#define BIT2(byte_addr) _B(byte_addr, 2)
#define BIT3(byte_addr) _B(byte_addr, 3)
#define BIT4(byte_addr) _B(byte_addr, 4)
#define BIT5(byte_addr) _B(byte_addr, 5)
#define BIT6(byte_addr) _B(byte_addr, 6)
#define BIT7(byte_addr) _B(byte_addr, 7)


namespace IttyBitty
{
	/* [BITPACK]: BITFIELD STRUCT FOR BIT-PACKING / BIT-REFERENCING OF A MEMORY BYTE */

	struct _BitPack;
	typedef volatile struct _BitPack BitPack, BITPACK, * PBITPACK, & RBITPACK, ** PPBITPACK, && RRBITPACK;
	typedef const struct _BitPack CBITPACK, * PCBITPACK, & RCBITPACK, ** PPCBITPACK;

	BITFIELD_STRUCT _BitPack
	{
	public:

		_BitPack(RCBITPACK other);

		STATIC RCBITPACK NULL_OBJECT();

		STATIC CSIZE BitSize();

		BIT operator[](SIZE i) const;

		BIT Bit(SIZE i) const;

		
		BIT b0 : 1;
		BIT b1 : 1;
		BIT b2 : 1;
		BIT b3 : 1;
		BIT b4 : 1;
		BIT b5 : 1;
		BIT b6 : 1;
		BIT b7 : 1;
	};
}


#ifdef EXCLUDE_ITTYBITTY_BYTES


#endif	// #ifdef EXCLUDE_ITTYBITTY_BYTES


#endif
