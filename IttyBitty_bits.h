/***********************************************************************************************
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_BITS_H
#define _ITTYBITTY_BITS_H


#include "IttyBitty_util.h"


/* BIT OFFSET, L/H NYBBLE, BYTE, & WORD MASK CONSTANT MAPS; NOTE: PRIMARILY FOR REFERENCE PURPOSES */

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


/* REDEFINE [_BV] MACRO FOR CAPABILITY OF ADDRESSING MSB (bit-offset 15)	OF AN <<UNSIGNED>> INT */

#undef _BV
#define _BV(bit_offset)		(1U << (bit_offset))


/* MISCELLANOUS BUILT-IN BIT OPERATION ALIASES */

#define REDUNDANT_LEADING_BITS_16(int_val)				__builtin_clrs(int_val)
#define REDUNDANT_LEADING_BITS_32(long_val)				__builtin_clrsl(long_val)
#define REDUNDANT_LEADING_BITS_64(long_long_val)		__builtin_clrsll(long_long_val)
#define REDUNDANT_LEADING_BITS(val)						REDUNDANT_LEADING_BITS_16(val)

#define LEAST_SIGNIFICANT_ONE_BIT_16(int_val)			__builtin_ffs(int_val)
#define LEAST_SIGNIFICANT_ONE_BIT_32(long_val)			__builtin_ffsl(long_val)
#define LEAST_SIGNIFICANT_ONE_BIT_64(long_long_val)		__builtin_ffsll(long_long_val)
#define LEAST_SIGNIFICANT_ONE_BIT(val)					LEAST_SIGNIFICANT_ONE_BIT_16(val)

#define ONE_BITS_16(int_val)							__builtin_popcount(int_val)
#define ONE_BITS_32(long_val)							__builtin_popcountl(long_val)
#define ONE_BITS_64(long_long_val)						__builtin_popcountll(long_long_val)
#define ONE_BITS(val)									ONE_BITS_16(val)

#define LEADING_ZERO_BITS_16(int_val)					__builtin_clz(int_val)
#define LEADING_ZERO_BITS_32(long_val)					__builtin_clzl(long_val)
#define LEADING_ZERO_BITS_64(long_long_val)				__builtin_clzll(long_long_val)
#define LEADING_ZERO_BITS(val)							LEADING_ZERO_BITS_16(val)

#define TRAILING_ZERO_BITS_16(int_val)					__builtin_ctz(int_val)
#define TRAILING_ZERO_BITS_32(long_val)					__builtin_ctzl(long_val)
#define TRAILING_ZERO_BITS_64(long_long_val)			__builtin_ctzll(long_long_val)
#define TRAILING_ZERO_BITS(val)							TRAILING_ZERO_BITS_16(val)

#define BIT_PARITY_16(int_val)							__builtin_parity(int_val)
#define BIT_PARITY_32(long_val)							__builtin_parityl(long_val)
#define BIT_PARITY_64(long_long_val)					__builtin_parityll(long_long_val)
#define BIT_PARITY(val)									BIT_PARITY_16(val)


/* LOGICAL (BOOLEAN) OPERATOR ALIASES */

#define NOT							!
#define AND							&&
#define OR							||

#define XOR(val1, val2)				(NOT (NOT (val1) ^ NOT (val2)))
#define NAND(val1, val2)			(NOT ((val1) AND (val2)))
#define NOR(val1, val2)				(NOT ((val1) OR (val2)))
#define NXOR(val1, val2)			(NOT (val1) ^ NOT (val2))
#define XNOR(val1, val2)			NXOR(val1, val2)

#define TOGGLE(ref)					((ref) = NOT (ref))


/* BITWISE OPERATOR ALIASES */

#define INVERSE						~
#define INV							INVERSE

#define B(bit_offset)				_BV(bit_offset)
#define NB(bit_offset)				INV B(bit_offset)

#define POWER_OF_TWO(power)			(1 SHL (power))

#define BAND(val1, val2)			((val1) & (val2))
#define BOR(val1, val2)				((val1) | (val2))
#define BXOR(val1, val2)			((val1) ^ (val2))
#define BNAND(val1, val2)			(INV BAND(val1, val2))
#define BNOR(val1, val2)			(INV BOR(val1, val2))
#define BNXOR(val1, val2)			(INV BXOR(val1, val2))
#define BXNOR(val1, val2)			BNXOR(val1, val2)

#define BIT_SHIFT_RIGHT				>>
#define SHIFT_RIGHT					BIT_SHIFT_RIGHT
#define BSHR						BIT_SHIFT_RIGHT
#define SHR							BIT_SHIFT_RIGHT
#define BIT_SHIFT_LEFT				<<
#define SHIFT_LEFT					BIT_SHIFT_LEFT
#define BSHL						BIT_SHIFT_LEFT
#define SHL							BIT_SHIFT_LEFT

#define MASK(ref, mask)				BAND(ref, mask)
#define NOT_MASK(ref, mask)			BAND(~ref, mask)
#define WITH_MASK(ref, mask)		BOR(ref, mask)
#define WITHOUT_MASK(ref, mask)		BAND(ref, ~mask)
#define INVERSE_MASK(ref, mask)		INV MASK(ref, mask)

#ifdef __BUILTIN_AVR_INSERT_BITS
	#define BREV(byte)				__builtin_avr_insert_bits(0x01234567, byte, 0)
#else
	#define BREV(byte)				(BYTE)(((byte * 0x0802LU & 0x22110LU) | (byte * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16)
#endif

#define REVERSE_BYTE(byte)			BREV(byte)


/* MASK GENERATOR MACROS */

#define BITMASK(bit_offset)				B(bit_offset)
#define BITMASK_INVERSE(bit_offset)		NB(bit_offset)
#define NOT_BITMASK(bit_offset)			NB(bit_offset)

#define NYBBLE_MASK(nybble_offset)		(0x0F << ((nybble_offset) * BITS_PER_NYBBLE))
#define NYBBLE_INVERSE(nybble_offset)	INV NYBBLE_MASK(nybble_offset)
#define NOT_NYBBLE(nybble_offset)		NYBBLE_INVERSE(nybble_offset)

#define BYTE_MASK(byte_offset)			(0xFF << ((byte_offset) * BITS_PER_BYTE))
#define BYTE_INVERSE(byte_offset)		INV BYTE_MASK(byte_offset)
#define NOT_BYTE(byte_offset)			BYTE_INVERSE(byte_offset)

#define WORD_MASK(word_offset)			(0xFFFF << ((word_offset) * BIT_SIZE(WORD)))
#define WORD_INVERSE(word_offset)		INV WORD_MASK(word_offset)
#define NOT_WORD(word_offset)			WORD_INVERSE(word_offset)

#define DWORD_MASK(dword_offset)		(0xFFFF << ((dword_offset) * BIT_SIZE(DWORD)))
#define DWORD_INVERSE(dword_offset)		INV DWORD_MASK(dword_offset)
#define NOT_DWORD(dword_offset)			DWORD_INVERSE(dword_offset)


/* BITMASK MACROS (FOR MULTI-BIT MANIPULATION OPERATIONS) */

#define BITSCHK(ref, mask)						MASK(ref, mask)
#define BITS_SET(ref, mask)						BITSCHK(ref, mask)
#define CHECK_BITS(ref, mask)					BITSCHK(ref, mask)
#define CHECK_BITS_SET(ref, mask)				BITSCHK(ref, mask)

#define BITSSNT(ref, mask)						NOT_MASK(ref, mask)
#define BITS_UNSET(ref, mask)					BITSSNT(ref, mask)
#define CHECK_BITS_UNSET(ref, mask)				BITSSNT(ref, mask)

#define BITSWITH(ref, mask)						WITH_MASK(ref, mask)
#define WITH_BITS(ref, mask)					BITSWITH(ref, mask)
#define WITH_BITS_SET(ref, mask)				BITSWITH(ref, mask)

#define BITSWITHOUT(ref, mask)					WITHOUT_MASK(ref, mask)
#define WITHOUT_BITS(ref, mask)					BITSWITHOUT(ref, mask)
#define WITHOUT_BITS_SET(ref, mask)				BITSWITHOUT(ref, mask)

#define BITSNOT(ref, mask)						INVERSE_MASK(ref, mask)
#define NOT_BITS(ref, mask)						BITSNOT(ref, mask)

#define BITSSET(ref, mask)						((ref) |= (mask))
#define SET_BITS(ref, mask)						BITSSET(ref, mask)

#define BITSCHOOSE(ref, mask)					((ref) &= (mask))
#define CHOOSE_BITS(ref, mask)					BITSCHOOSE(ref, mask)
#define MASK_BITS(ref, mask)					BITSCHOOSE(ref, mask)

#define BITSCLEAR(ref)							((ref) &= ~(ref))
#define RESET_ALL_BITS(ref)						BITSCLEAR(ref)
#define UNSET_ALL_BITS(ref)						BITSCLEAR(ref)
#define CLEAR_ALL_BITS(ref)						BITSCLEAR(ref)

#define BITSRST(ref, mask)						((ref) &= ~(mask))
#define RESET_BITS(ref, mask)					BITSRST(ref, mask)
#define UNSET_BITS(ref, mask)					BITSRST(ref, mask)
#define CLEAR_BITS(ref, mask)					BITSRST(ref, mask)

#define BITSSETINV(ref, mask)					((ref) |= ~(mask))
#define SET_INVERSE_BITS(ref, mask)				BITSSETINV(ref, mask)

#define BITSFLP(ref, mask)						((ref) ^= (mask))
#define FLIP_BITS(ref, mask)					BITSFLP(ref, mask)
#define TOGGLE_BITS(ref, mask)					BITSFLP(ref, mask)

#define BITSSETFROM(ref, mask, from_ref)		BITSSET(ref, MASK(from_ref, mask))
#define SET_BITS_FROM(ref, mask, from_ref)		BITSSETFROM(ref, mask, from_ref)

#define BITSCLEARFROM(ref, mask, from_ref)		BITSRST(ref, MASK(from_ref, mask))
#define CLEAR_BITS_FROM(ref, mask, from_ref)	BITSCLEARFROM(ref, mask, from_ref)

#define BITSCOPYFROM(ref, mask, from_ref)		((ref) = BITSWITHOUT(ref, mask) | MASK(from_ref, mask))
#define COPY_BITS_FROM(ref, mask, from_ref)		BITSCOPYFROM(ref, mask, from_ref)
#define COPY_BITS(ref, mask, from_ref)			BITSCOPYFROM(ref, mask, from_ref)


// CORRESPONDING EXPANSION MACROS...

#define BITSCHKP(ref_mask_pair)					BITSCHK(ref_mask_pair)
#define BITS_SET_PAIR(ref_mask_pair)			BITSCHK(ref_mask_pair)
#define CHECK_BITS_PAIR(ref_mask_pair)			BITSCHK(ref_mask_pair)
#define CHECK_BITS_SET_PAIR(ref_mask_pair)		BITSCHK(ref_mask_pair)

#define BITSSNTP(ref_mask_pair)					BITSSNT(ref_mask_pair)
#define BITS_UNSET_PAIR(ref_mask_pair)			BITSSNT(ref_mask_pair)
#define CHECK_BITS_UNSET_PAIR(ref_mask_pair)	BITSSNT(ref_mask_pair)

#define BITSWITHP(ref_mask_pair)				BITSWITH(ref_mask_pair)
#define WITH_BITS_PAIR(ref_mask_pair)			BITSWITH(ref_mask_pair)
#define WITH_BITS_SET_PAIR(ref_mask_pair)		BITSWITH(ref_mask_pair)

#define BITSWITHOUTP(ref_mask_pair)				BITSWITHOUT(ref_mask_pair)
#define WITHOUT_BITS_PAIR(ref_mask_pair)		BITSWITHOUT(ref_mask_pair)
#define WITHOUT_BITS_SET_PAIR(ref_mask_pair)	BITSWITHOUT(ref_mask_pair)

#define BITSNOTP(ref_mask_pair)					BITSNOT(ref_mask_pair)
#define NOT_BITS_PAIR(ref_mask_pair)			BITSNOT(ref_mask_pair)

#define BITSSETP(ref_mask_pair)					BITSSET(ref_mask_pair)
#define SET_BITS_PAIR(ref_mask_pair)			BITSSET(ref_mask_pair)

#define BITSCHOOSEP(ref_mask_pair)				BITSCHOOSE(ref_mask_pair)
#define CHOOSE_BITS_PAIR(ref_mask_pair)			BITSCHOOSE(ref_mask_pair)
#define MASK_BITS_PAIR(ref_mask_pair)			BITSCHOOSE(ref_mask_pair)

#define BITSRSTP(ref_mask_pair)					BITSRST(ref_mask_pair)
#define RESET_BITS_PAIR(ref_mask_pair)			BITSRST(ref_mask_pair)
#define UNSET_BITS_PAIR(ref_mask_pair)			BITSRST(ref_mask_pair)
#define CLEAR_BITS_PAIR(ref_mask_pair)			BITSRST(ref_mask_pair)

#define BITSSETINVP(ref_mask_pair)				BITSSETINV(ref_mask_pair)
#define SET_INVERSE_BITS_PAIR(ref_mask_pair)	BITSSETINV(ref_mask_pair)

#define BITSFLPP(ref_mask_pair)					BITSFLP(ref_mask_pair)
#define FLIP_BITS_PAIR(ref_mask_pair)			BITSFLP(ref_mask_pair)
#define TOGGLE_BITS_PAIR(ref_mask_pair)			BITSFLP(ref_mask_pair)

#define BITSSETFROMP(ref_mask_pair, from_ref)				BITSSETFROM(ref_mask_pair, from_ref)
#define SET_BITS_FROM_PAIR(ref_mask_pair, from_ref)			BITSSETFROM(ref_mask_pair, from_ref)

#define BITSCLEARFROMP(ref_mask_pair, from_ref)				BITSCLEARFROM(ref_mask_pair, from_ref)
#define CLEAR_BITS_FROM_PAIR(ref_mask_pair, from_ref)		BITSCLEARFROM(ref_mask_pair, from_ref)

#define BITSCOPYFROMP(ref_mask_pair, from_ref)				BITSCOPYFROM(ref_mask_pair, from_ref)
#define COPY_BITS__FROMPAIR(ref_mask_pair, from_ref)		BITSCOPYFROM(ref_mask_pair, from_ref)
#define COPY_BITS_PAIR(ref_mask_pair, from_ref)				BITSCOPYFROM(ref_mask_pair, from_ref)

#define BITSSETFROMT(ref_mask_from_ref_tuple)				BITSSETFROM(ref_mask_from_ref_tuple)
#define SET_BITS_FROM_TUPLE(ref_mask_from_ref_tuple)		BITSSETFROM(ref_mask_from_ref_tuple)

#define BITSCLEARFROMT(ref_mask_from_ref_tuple)				BITSCLEARFROM(ref_mask_from_ref_tuple)
#define CLEAR_BITS_FROM_TUPLE(ref_mask_from_ref_tuple)		BITSCLEARFROM(ref_mask_from_ref_tuple)

#define BITSCOPYFROMT(ref_mask_from_ref_tuple)				BITSCOPYFROM(ref_mask_from_ref_tuple)
#define COPY_BITS_FROM_TUPLE(ref_mask_from_ref_tuple)		BITSCOPYFROM(ref_mask_from_ref_tuple)
#define COPY_BITS_TUPLE(ref_mask_from_ref_tuple)			BITSCOPYFROM(ref_mask_from_ref_tuple)


/* (SINGLE) BIT-TWIDDLING MACROS */

#define BMASK(bit_offset)							B(bit_offset)
#define BIT_MASK(bit_offset)						B(bit_offset)

#define BCHK(ref, bit_offset)						BITSCHK(ref, B(bit_offset))
#define BIT_SET(ref, bit_offset)					BCHK(ref, bit_offset)
#define CHECK_BIT(ref, bit_offset)					BCHK(ref, bit_offset)
#define CHECK_SET(ref, bit_offset)					BCHK(ref, bit_offset)

#define BSNT(ref, bit_offset)						BITSSNT(ref, B(bit_offset))
#define BIT_UNSET(ref, bit_offset)					BSNT(ref, bit_offset)
#define CHECK_UNSET(ref, bit_offset)				BSNT(ref, bit_offset)

#define BWITH(ref, bit_offset)						BITSWITH(ref, B(bit_offset))
#define WITH_BIT(ref, bit_offset)					BWITH(ref, bit_offset)
#define WITH_BIT_SET(ref, bit_offset)				BWITH(ref, bit_offset)

#define BWITHOUT(ref, bit_offset)					BITSWITHOUT(ref, B(bit_offset))
#define WITHOUT_BIT(ref, bit_offset)				BWITHOUT(ref, bit_offset)
#define WITHOUT_BIT_SET(ref, bit_offset)			BWITHOUT(ref, bit_offset)

#define BNOT(ref, bit_offset)						BITSNOT(ref, B(bit_offset))
#define NOT_BIT(ref, bit_offset)					BNOT(ref, bit_offset)

#define BSET(ref, bit_offset)						BITSSET(ref, B(bit_offset))
#define SET_BIT(ref, bit_offset)					BSET(ref, bit_offset)

#define BCHOOSE(ref, bit_offset)					BITSCHOOSE(ref, B(bit_offset))
#define CHOOSE_BIT(ref, bit_offset)					BCHOOSE(ref, bit_offset)
#define MASK_BIT(ref, bit_offset)					BCHOOSE(ref, bit_offset)

#define BRST(ref, bit_offset)						BITSRST(ref, B(bit_offset))
#define RESET_BIT(ref, bit_offset)					BRST(ref, bit_offset)
#define UNSET_BIT(ref, bit_offset)					BRST(ref, bit_offset)
#define CLEAR_BIT(ref, bit_offset)					BRST(ref, bit_offset)

#define BSETINV(ref, bit_offset)					BITSSETINV(ref, B(bit_offset))
#define SET_OTHER_BITS(ref, bit_offset)				BSETINV(ref, bit_offset)

#define BFLP(ref, bit_offset)						BITSFLP(ref, B(bit_offset))
#define FLIP_BIT(ref, bit_offset)					BFLP(ref, bit_offset)
#define TOGGLE_BIT(ref, bit_offset)					BFLP(ref, bit_offset)
#define NOW_FLIP_BIT(ref, bit_offset)				BFLP(ref, bit_offset)
#define FLIP_BIT_GOOD(ref, bit_offset)				BFLP(ref, bit_offset)		// [heh...]

#define BSETTO(ref, bit_offset, value)				((ref) = BWITHOUT(ref, bit_offset) | (value) SHL (bit_offset))
#define SET_BIT_TO(ref, bit_offset, value)			BSETTO(ref, bit_offset, value)

#define BSETFROM(ref, bit_offset, from_ref)			BITSSETFROM(ref, B(bit_offset), from_ref)
#define SET_BIT_FROM(ref, bit_offset, from_ref)		BSETFROM(ref, bit_offset, from_ref)

#define BRSTFROM(ref, bit_offset, from_ref)			BITSCLEARFROM(ref, B(bit_offset), from_ref)
#define CLEAR_BIT_FROM(ref, bit_offset, from_ref)	BRSTFROM(ref, bit_offset, from_ref)

#define BCOPYFROM(ref, bit_offset, from_ref)		BITSCOPYFROM(ref, B(bit_offset), from_ref)
#define COPY_BIT_FROM(ref, bit_offset, from_ref)	BCOPYFROM(ref, bit_offset, from_ref)
#define COPY_BIT(ref, bit_offset, from_ref)			BCOPYFROM(ref, bit_offset, from_ref)

// CORRESPONDING EXPANSION MACROS...

#define BCHKP(ref_bit_offset_pair)					BCHK(ref_bit_offset_pair)
#define BIT_SET_PAIR(ref_bit_offset_pair)			BCHK(ref_bit_offset_pair)
#define CHECK_BIT_PAIR(ref_bit_offset_pair)			BCHK(ref_bit_offset_pair)
#define CHECK_SET_PAIR(ref_bit_offset_pair)			BCHK(ref_bit_offset_pair)

#define BSNTP(ref_bit_offset_pair)					BSNT(ref_bit_offset_pair)
#define BIT_UNSET_PAIR(ref_bit_offset_pair)			BSNT(ref_bit_offset_pair)
#define CHECK_UNSET_PAIR(ref_bit_offset_pair)		BSNT(ref_bit_offset_pair)

#define BWITHP(ref_bit_offset_pair)					BWITH(ref_bit_offset_pair)
#define WITH_BIT_PAIR(ref_bit_offset_pair)			BWITH(ref_bit_offset_pair)
#define WITH_BIT_SET_PAIR(ref_bit_offset_pair)		BWITH(ref_bit_offset_pair)

#define BWITHOUTP(ref_bit_offset_pair)				BITSWITHOUT(ref_bit_offset_pair)
#define WITHOUT_BIT_PAIR(ref_bit_offset_pair)		BITSWITHOUT(ref_bit_offset_pair)
#define WITHOUT_BIT_SET_PAIR(ref_bit_offset_pair)	BITSWITHOUT(ref_bit_offset_pair)

#define BNOTP(ref_bit_offset_pair)					BNOT(ref_bit_offset_pair)
#define NOT_BIT_PAIR(ref_bit_offset_pair)			BNOT(ref_bit_offset_pair)

#define BSETP(ref_bit_offset_pair)					BSET(ref_bit_offset_pair)
#define SET_BIT_PAIR(ref_bit_offset_pair)			BSET(ref_bit_offset_pair)

#define BCHOOSEP(ref_bit_offset_pair)				BCHOOSE(ref_bit_offset_pair)
#define CHOOSE_BIT_PAIR(ref_bit_offset_pair)		BCHOOSE(ref_bit_offset_pair)
#define MASK_BIT_PAIR(ref_bit_offset_pair)			BCHOOSE(ref_bit_offset_pair)

#define BRSTP(ref_bit_offset_pair)					BRST(ref_bit_offset_pair)
#define UNSET_BIT_PAIR(ref_bit_offset_pair)			BRST(ref_bit_offset_pair)
#define RESET_BIT_PAIR(ref_bit_offset_pair)			BRST(ref_bit_offset_pair)
#define CLEAR_BIT_PAIR(ref_bit_offset_pair)			BRST(ref_bit_offset_pair)

#define BSETINVP(ref_bit_offset_pair)				BSETINV(ref_bit_offset_pair)
#define SET_OTHER_BITS_PAIR(ref_bit_offset_pair)	BSETINV(ref_bit_offset_pair)

#define BFLPP(ref_bit_offset_pair)					BFLP(ref_bit_offset_pair)
#define FLIP_BIT_PAIR(ref_bit_offset_pair)			BFLP(ref_bit_offset_pair)
#define TOGGLE_BIT_PAIR(ref_bit_offset_pair)		BFLP(ref_bit_offset_pair)

#define BSETTOP(ref_bit_offset_pair, value)						BSETTO(ref_bit_offset_pair, value)
#define SET_BIT_TO_PAIR(ref_bit_offset_pair, value)				BSETTO(ref_bit_offset_pair, value)

#define BSETFROMP(ref_bit_offset_pair, from_ref)				BSETFROM(ref_bit_offset_pair, from_ref)
#define SET_BIT_FROM_PAIR(ref_bit_offset_pair, from_ref)		BSETFROM(ref_bit_offset_pair, from_ref)

#define BCLEARFROMP(ref_bit_offset_pair, from_ref)				BRSTFROM(ref_bit_offset_pair, from_ref)
#define CLEAR_BIT_FROM_PAIR(ref_bit_offset_pair, from_ref)		BRSTFROM(ref_bit_offset_pair, from_ref)

#define BCOPYFROMP(ref_bit_offset_pair, from_ref)				BCOPYFROM(ref_bit_offset_pair, from_ref)
#define COPY_BIT_PAIR(ref_bit_offset_pair, from_ref)			BCOPYFROM(ref_bit_offset_pair, from_ref)

#define BSETTOT(ref_bit_offset_value_tuple)						BSETTO(ref_bit_offset_value_tuple)
#define SET_BIT_TO_TUPLE(ref_bit_offset_value_tuple)			BSETTO(ref_bit_offset_value_tuple)

#define BSETFROMT(ref_bit_offset_from_ref_tuple)				BSETFROM(ref_bit_offset_from_ref_tuple)
#define SET_BIT_FROM_TUPLE(ref_bit_offset_from_ref_tuple)		BSETFROM(ref_bit_offset_from_ref_tuple)

#define BCLEARFROMT(ref_bit_offset_from_ref_tuple)				BRSTFROM(ref_bit_offset_from_ref_tuple)
#define CLEAR_BIT_FROM_TUPLE(ref_bit_offset_from_ref_tuple)		BRSTFROM(ref_bit_offset_from_ref_tuple)

#define BCOPYFROMT(ref_bit_offset_from_ref_tuple)				BCOPYFROM(ref_bit_offset_from_ref_tuple)
#define COPY_BIT_TUPLE(ref_bit_offset_from_ref_tuple)			BCOPYFROM(ref_bit_offset_from_ref_tuple)


/* BIT-SPECIFIC MACRO ALIASES FOR BYTES */

#define BIT0_MASK						BMASK(0)
#define CHECK_BIT0(byte_ref)			CHECK_SET(byte_ref, 0)
#define CHECK_BIT0_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 0)
#define SET_BIT0(byte_ref)				SET_BIT(byte_ref, 0)
#define CLEAR_BIT0(byte_ref)			CLEAR_BIT(byte_ref, 0)
#define TOGGLE_BIT0(byte_ref)			TOGGLE_BIT(byte_ref, 0)

#define BIT1_MASK						BMASK(1)
#define CHECK_BIT1(byte_ref)			CHECK_SET(byte_ref, 1)
#define CHECK_BIT1_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 1)
#define SET_BIT1(byte_ref)				SET_BIT(byte_ref, 1)
#define CLEAR_BIT1(byte_ref)			CLEAR_BIT(byte_ref, 1)
#define TOGGLE_BIT1(byte_ref)			TOGGLE_BIT(byte_ref, 1)

#define BIT2_MASK						BMASK(2)
#define CHECK_BIT2(byte_ref)			CHECK_SET(byte_ref, 2)
#define CHECK_BIT2_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 2)
#define SET_BIT2(byte_ref)				SET_BIT(byte_ref, 2)
#define CLEAR_BIT2(byte_ref)			CLEAR_BIT(byte_ref, 2)
#define TOGGLE_BIT2(byte_ref)			TOGGLE_BIT(byte_ref, 2)

#define BIT3_MASK						BMASK(3)
#define CHECK_BIT3(byte_ref)			CHECK_SET(byte_ref, 3)
#define CHECK_BIT3_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 3)
#define SET_BIT3(byte_ref)				SET_BIT(byte_ref, 3)
#define CLEAR_BIT3(byte_ref)			CLEAR_BIT(byte_ref, 3)
#define TOGGLE_BIT3(byte_ref)			TOGGLE_BIT(byte_ref, 3)

#define BIT4_MASK						BMASK(4)
#define CHECK_BIT4(byte_ref)			CHECK_SET(byte_ref, 4)
#define CHECK_BIT4_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 4)
#define SET_BIT4(byte_ref)				SET_BIT(byte_ref, 4)
#define CLEAR_BIT4(byte_ref)			CLEAR_BIT(byte_ref, 4)
#define TOGGLE_BIT4(byte_ref)			TOGGLE_BIT(byte_ref, 4)

#define BIT5_MASK						BMASK(5)
#define CHECK_BIT5(byte_ref)			CHECK_SET(byte_ref, 5)
#define CHECK_BIT5_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 5)
#define SET_BIT5(byte_ref)				SET_BIT(byte_ref, 5)
#define CLEAR_BIT5(byte_ref)			CLEAR_BIT(byte_ref, 5)
#define TOGGLE_BIT5(byte_ref)			TOGGLE_BIT(byte_ref, 5)

#define BIT6_MASK						BMASK(6)
#define CHECK_BIT6(byte_ref)			CHECK_SET(byte_ref, 6)
#define CHECK_BIT6_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 6)
#define SET_BIT6(byte_ref)				SET_BIT(byte_ref, 6)
#define CLEAR_BIT6(byte_ref)			CLEAR_BIT(byte_ref, 6)
#define TOGGLE_BIT6(byte_ref)			TOGGLE_BIT(byte_ref, 6)

#define BIT7_MASK						BMASK(7)
#define CHECK_BIT7(byte_ref)			CHECK_SET(byte_ref, 7)
#define CHECK_BIT7_UNSET(byte_ref)		CHECK_UNSET(byte_ref, 7)
#define SET_BIT7(byte_ref)				SET_BIT(byte_ref, 7)
#define CLEAR_BIT7(byte_ref)			CLEAR_BIT(byte_ref, 7)
#define TOGGLE_BIT7(byte_ref)			TOGGLE_BIT(byte_ref, 7)


/* NYBBLE MANIPULATION MACROS */

#define NYBBLES_TO_BYTE(nybble1, nybble2)				WITH_MASK(BYTE(nybble1) SHL BITS_PER_NYBBLE, BYTE(nybble2))
#define MAKE_BYTE(nybble1, nybble2)						NYBBLES_TO_BYTE(nybble1, nybble2)

#define LOW_NYBBLE_MASK									NYBBLE_MASK(0)
#define HIGH_NYBBLE_MASK								NYBBLE_MASK(1)

#define LOW_NYBBLE(byte_ref)							MASK(byte_ref, LOW_NYBBLE_MASK)
#define HIGH_NYBBLE(byte_ref)							MASK(byte_ref, HIGH_NYBBLE_MASK)

#define CHECK_NYBBLE_SET(byte_ref, nybble_offset)		MASK(byte_ref, NYBBLE_MASK(nybble_offset))
#define CHECK_NYBBLE(byte_ref, nybble_offset)			CHECK_NYBBLE_SET(byte_ref, nybble_offset)

#define CHECK_NYBBLE_UNSET(byte_ref, nybble_offset)		MASK(byte_ref, NOT_NYBBLE(nybble_offset))

#define SET_LOW_NYBBLE(byte_ref)						SET_BITS_FROM(byte_ref, LOW_NYBBLE_MASK)
#define SET_HIGH_NYBBLE(byte_ref)						SET_BITS_FROM(byte_ref, HIGH_NYBBLE_MASK)

#define CLEAR_LOW_NYBBLE(byte_ref)						CLEAR_BITS_FROM(byte_ref, LOW_NYBBLE_MASK)
#define CLEAR_HIGH_NYBBLE(byte_ref)						CLEAR_BITS_FROM(byte_ref, HIGH_NYBBLE_MASK)

#define TOGGLE_LOW_NYBBLE(byte_ref)						TOGGLE_BITS(byte_ref, LOW_NYBBLE_MASK)
#define TOGGLE_HIGH_NYBBLE(byte_ref)					TOGGLE_BITS(byte_ref, HIGH_NYBBLE_MASK)

#define SET_NYBBLE(ref, nybble_offset)					SET_BITS(ref, NYBBLE_MASK(nybble_offset))

#define CLEAR_NYBBLE(ref, nybble_offset)				CLEAR_BITS(ref, NYBBLE_MASK(nybble_offset))

#define COPY_NYBBLE_FROM(ref, nybble_offset, from_ref)	COPY_BITS_FROM(ref, NYBBLE_MASK(nybble_offset), from_ref)
#define COPY_FROM(ref, nybble_offset, from_ref)			COPY_NYBBLE_FROM(ref, nybble_offset, from_ref)


/* BYTE MANIPULATION MACROS */

#define BYTES_TO_WORD(byte1, byte2)						WITH_MASK(WORD(byte1) SHL BITS_PER_BYTE, WORD(byte2))
#define MAKE_WORD(byte1, byte2)							BYTES_TO_WORD(byte1, byte2)

#define NYBBLES_TO_WORD(nybble1, nybble2, nybble3, nybble4)	\
	MAKE_WORD(MAKE_BYTE(nybble1, nybble2), MAKE_BYTE(nybble3, nybble4))
#define MAKE_WORD_N(nybble1, nybble2, nybble3, nybble4)	NYBBLES_TO_WORD(nybble1, nybble2, nybble3, nybble4)

#define LOW_BYTE_MASK									BYTE_MASK(0)
#define HIGH_BYTE_MASK									BYTE_MASK(1)

#define LOW_BYTE(word_ref)								MASK(word_ref, LOW_BYTE_MASK)
#define HIGH_BYTE(word_ref)								MASK(word_ref, HIGH_BYTE_MASK)

#define CHECK_BYTE_SET(ref, byte_offset)				MASK(ref, BYTE_MASK(byte_offset))
#define CHECK_BYTE(ref, byte_offset)					CHECK_BYTE_SET(ref, byte_offset)

#define CHECK_BYTE_UNSET(ref, byte_offset)				MASK(ref, NOT_BYTE(byte_offset))

#define SET_LOW_BYTE(word_ref)							SET_BITS(word_ref, LOW_BYTE_MASK)
#define SET_HIGH_BYTE(word_ref)							SET_BITS(word_ref, HIGH_BYTE_MASK)

#define CLEAR_LOW_BYTE(word_ref)						CLEAR_BITS(word_ref, LOW_BYTE_MASK)
#define CLEAR_HIGH_BYTE(word_ref)						CLEAR_BITS(word_ref, HIGH_BYTE_MASK)

#define TOGGLE_LOW_BYTE(word_ref)						TOGGLE_BITS(word_ref, LOW_BYTE_MASK)
#define TOGGLE_HIGH_BYTE(word_ref)						TOGGLE_BITS(word_ref, HIGH_BYTE_MASK)

#define SET_BYTE(ref, byte_offset)						SET_BITS(ref, BYTE_MASK(byte_offset))

#define CLEAR_BYTE(ref, byte_offset)					CLEAR_BITS(ref, BYTE_MASK(byte_offset))

#define BYTE_RANGE(ref, bit_offset, bit_size)			ref SHL (BIT_SIZE(BYTE) - bit_size - bit_offset)	SHR bit_offset
#define GET_BITS_FROM_BYTE(ref, bit_offset, bit_size)	BYTE_RANGE(ref, bit_offset, bit_size)

#define COPY_BYTE_FROM(ref, byte_offset, from_ref)		COPY_BITS_FROM(ref, BYTE_MASK(byte_offset), from_ref)
#define COPY_BYTE(ref, byte_offset, from_ref)			COPY_BYTE_FROM(ref, byte_offset, from_ref)


/* WORD MANIPULATION MACROS */

#define WORDS_TO_DWORD(word1, byte2)					WITH_MASK(DWORD(word1) SHL BITS_PER_BYTE, DWORD(word2))
#define MAKE_DWORD(word1, word2)						WORDS_TO_DWORD(word1, word2)

#define BYTES_TO_DWORD(byte1, byte2, byte3, byte4)		MAKE_DWORD(MAKE_WORD(byte1, byte2), MAKE_WORD(byte3, byte4))
#define MAKE_DWORD_B(byte1, byte2, byte3, byte4)		BYTES_TO_DWORD(byte1, byte2, byte3, byte4)

#define NYBBLES_TO_DWORD(nybble1, nybble2, nybble3, nybble4, nybble5, nybble6, nybble7, nybble8)	\
	MAKE_DWORD(MAKE_WORD(nybble1, nybble2, nybble3, nybble4), MAKE_WORD(nybble5, nybble6, nybble7, nybble8))
#define MAKE_DWORD_N(nybble1, nybble2, nybble3, nybble4, nybble5, nybble6, nybble7, nybble8)		\
	NYBBLES_TO_DWORD(nybble1, nybble2, nybble3, nybble4, nybble5, nybble6, nybble7, nybble8)

#define LOW_WORD_MASK									WORD_MASK(0)
#define HIGH_WORD_MASK									WORD_MASK(1)

#define LOW_WORD(dword_ref)								MASK(dword_ref, LOW_WORD_MASK)
#define HIGH_WORD(dword_ref)							MASK(dword_ref, HIGH_WORD_MASK)

#define CHECK_WORD_SET(ref, word_offset)				MASK(ref, WORD_MASK(word_offset))
#define CHECK_WORD(ref, word_offset)					CHECK_WORD_SET(ref, word_offset)

#define CHECK_WORD_UNSET(ref, word_offset)				MASK(ref, NOT_WORD(word_offset))

#define SET_LOW_WORD(dword_ref)							SET_BITS(dword_ref, LOW_WORD_MASK)
#define SET_HIGH_WORD(dword_ref)						SET_BITS(dword_ref, HIGH_WORD_MASK)

#define CLEAR_LOW_WORD(dword_ref)						CLEAR_BITS(dword_ref, LOW_WORD_MASK)
#define CLEAR_HIGH_WORD(dword_ref)						CLEAR_BITS(dword_ref, HIGH_WORD_MASK)

#define TOGGLE_LOW_WORD(dword_ref)						TOGGLE_BITS(dword_ref, LOW_WORD_MASK)
#define TOGGLE_HIGH_WORD(dword_ref)						TOGGLE_BITS(dword_ref, HIGH_WORD_MASK)

#define SET_WORD(ref, word_offset)						SET_BITS(ref, WORD_MASK(word_offset))

#define CLEAR_WORD(ref, word_offset)					CLEAR_BITS(ref, WORD_MASK(word_offset))

#define COPY_WORD_FROM(ref, word_offset, from_ref)		COPY_BITS_FROM(ref, WORD_MASK(word_offset), from_ref)
#define COPY_WORD(ref, word_offset, from_ref)			COPY_WORD_FROM(ref, word_offset, from_ref)


/* SUPRESS COMPILER WARNINGS RELATED TO BITFIELD ALIASING */

IGNORE_WARNING(strict-aliasing)


/* BIT-PACKING / BIT REFERENCE MACROS */

#define PACK_BYTE(byte_addr)		reinterpret_cast<IttyBitty::PBITPACK>(byte_addr)
#define PACK_BYTE_REF(byte_ref)		PACK_BYTE(&(byte_ref))
#define PACK_BYTE_CREF(byte_val)	MAKE_CONST(PACK_BYTE(&(byte_val)))
#define PACK_BYTE_VAL(byte_val)		PACK_BYTE_CREF(byte_val)

#define _B(byte_addr, i)	(PACK_BYTE(byte_addr)->b##i)

#define BIT0(byte_addr)		_B(byte_addr, 0)
#define BIT1(byte_addr)		_B(byte_addr, 1)
#define BIT2(byte_addr)		_B(byte_addr, 2)
#define BIT3(byte_addr)		_B(byte_addr, 3)
#define BIT4(byte_addr)		_B(byte_addr, 4)
#define BIT5(byte_addr)		_B(byte_addr, 5)
#define BIT6(byte_addr)		_B(byte_addr, 6)
#define BIT7(byte_addr)		_B(byte_addr, 7)


namespace IttyBitty
{
	/* [_BitPack]: BITFIELD STRUCT FOR BIT-PACKING / BIT-REFERENCING OF A MEMORY BYTE */

	struct _BitPack;
	TYPEDEF_VOLATILE_STRUCT_ALIASES(BitPack, bitpack, BITPACK);

	BITFIELD_STRUCT _BitPack
	{
	public:

		_BitPack();

		EXPLICIT _BitPack(RCBITPACK);
		EXPLICIT _BitPack(RRBITPACK);

		EXPLICIT _BitPack(RCVBYTE);

		STATIC RCBITPACK NULL_OBJECT();

		STATIC CSIZE BitSize();

		_BitPack & operator =(RCBITPACK);
		_BitPack & operator =(RRBITPACK);

		_BitPack & operator =(RCVBYTE);

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

#endif
