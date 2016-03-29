/*******************************************************************************
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register management for ATmegas
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


/* BIT-WISE OPERATOR ALIASES */

#define NOT ~
#define AND &
#define OR |
#define XOR ^
#define SHR >>
#define SHIFT_RIGHT SHR
#define SHL <<
#define SHIFT_LEFT SHL


/* SINGLE-BIT-TWIDDLING MACROS */

#define BMASK(bit_offset) (1 << (bit_offset))
#define BITMASK(bit_offset) BMASK(bit_offset)

#define BNOT(bit_offset) NOT BMASK(bit_offset)
#define NOT_BIT(bit_offset) BNOT(bit_offset)

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

// CORRESPONDING EXPANSION MACROS...

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


/* BITMASK MACROS (FOR MULTI-BIT MANIPULATION OPERATIONS) */

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


#endif
