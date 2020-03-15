/***********************************************************************************************
* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_REGISTERS_H
#define _ITTYBITTY_REGISTERS_H


#include "IttyBitty_bits.h"

using namespace IttyBitty;


/* BIT OPERATION MACROS */

#ifndef sbi
	#define sbi(sfr, bit)				SET_BIT(_SFR_BYTE(sfr), bit)
#endif

#define SBI(sfr, bit)					sbi(sfr, bit)
#define SET_SFR_BIT(sfr, bit)			SBI(sfr, bit)
#define SET_IO_REG_BIT(io_reg, bit)		SBI(io_reg, bit)

#define SBIS(sfr, mask)					SET_BITS(_SFR_BYTE(sfr), mask)
#define SET_SFR_BITS(sfr, mask)			SBIS(sfr, mask)
#define SET_IO_REG_BITS(io_reg, mask)	SBIS(io_reg, mask)

#ifndef cbi
	#define cbi(sfr, bit)				CLEAR_BIT(_SFR_BYTE(sfr), bit)
#endif

#define CBI(sfr, bit)					cbi(sfr, bit)
#define CLEAR_SFR_BIT(sfr, bit)			CBI(sfr, bit)
#define CLEAR_IO_REG_BIT(io_reg, bit)	CBI(io_reg, bit)

#define CBIS(sfr, mask)					CLEAR_BITS(_SFR_BYTE(sfr), mask)
#define CLEAR_SFR_BITS(sfr, mask)		CBIS(sfr, mask)
#define CLEAR_IO_REG_BITS(io_reg, mask)	CBIS(io_reg, mask)

#define RBIS(sfr)						CLEAR_ALL_BITS(_SFR_BYTE(sfr))
#define CLEAR_ALL_SFR_BITS(sfr)			RBIS(sfr)
#define CLEAR_ALL_IO_REG_BITS(io_reg)	RBIS(io_reg)
#define RESET_SFR(sfr)					RBIS(sfr)
#define RESET_IO_REG(io_reg)			RBIS(io_reg)


/* [register] DECLARATION ALIAS */

#define REGISTER volatile register


/* REGISTER-BOUND VARIABLE DECLARATION MACROS */

/*
	!! CONSTRAINT: 2 <= <register_num> <= 7 (up to 15 typically safe but not guaranteed) !!

	The MCU uses r0 and r1 for MUL & MULS 16-bit multiplication instructions;
	General purpose registers r8-15 may be utilized by the AVR-GCC compiler in certain scenarios;

	SEE: http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_regbind
*/
#define REG_VAR(type, var_name, register_num)	REGISTER type var_name asm("r" #register_num)
#define REG_BOOL(var_name, register_num)		REG_VAR(BOOL, var_name, register_num)
#define REG_CHAR(var_name, register_num)		REG_VAR(CHAR, var_name, register_num)
#define REG_BYTE(var_name, register_num)		REG_VAR(BYTE, var_name, register_num)


/* BIT-PACKED REGISTER TYPES */

#ifndef NO_ITTYBITTY_BYTES

#include "IttyBitty_bytes.h"

namespace IttyBitty
{

	TYPEDEF_CLASS_ALIASES(ByteField, REG8);

#ifndef NO_ITTYBITTY_FULL_BYTES
	TYPEDEF_CLASS_ALIASES(WordField, REG16);
	TYPEDEF_CLASS_ALIASES(DWordField, REG32);
#endif
}

#else	// #ifndef NO_ITTYBITTY_BYTES

namespace IttyBitty
{
	TYPEDEF_CLASS_ALIASES(_BitPack, REG8);
}

#endif	// #ifndef NO_ITTYBITTY_BYTES

#define REG_FIELD(mem_addr)				(*(reinterpret_cast<PVREG8>(mem_addr))
#define SFR_FIELD(sfr)					REG_FIELD(_SFR_MEM_ADDR(sfr))
#define IO_REG_FIELD(io_reg)			SFR_FIELD(io_reg))
#define EXT_IO_REG_FIELD(ext_io_reg)	SFR_FIELD(ext_io_reg)

#define NEW_REG8(mem_addr)				(new REG8(reinterpret_cast<PVBYTE>(mem_addr)))
#define NEW_SFR_REG8(sfr)				NEW_REG8(_SFR_MEM_ADDR(sfr))
#define NEW_IO_REG8(io_reg)				NEW_SFR_REG8(io_reg)
#define NEW_EXT_IO_REG8(ext_io_reg)		NEW_SFR_REG8(ext_io_reg)

#ifndef NO_ITTYBITTY_BYTES

#define REG_BIT(mem_addr, bit)			REG_FIELD(mem_addr)[bit]
#define SFR_BIT(sfr, bit)				SFR_FIELD(sfr)[bit]
#define IO_REG_BIT(io_reg, bit)			SFR_BIT(sfr, bit)
#define EXT_IO_REG_BIT(ext_io_reg, bit)	SFR_BIT(sfr, bit)

#else	// #ifndef NO_ITTYBITTY_BYTES

#define REG_BIT(mem_addr, bit)			REG_FIELD(mem_addr).b ## bit
#define SFR_BIT(sfr, bit)				SFR_FIELD(sfr).b ## bit
#define IO_REG_BIT(io_reg, bit)			SFR_BIT(io_reg, bit)
#define EXT_IO_REG_BIT(ext_io_reg, bit)	SFR_BIT(ext_io_reg, bit)

#endif	// #ifndef NO_ITTYBITTY_BYTES


/* BIT-PACKED IO/SPECIAL-FUNCTION REGISTER DECLARATIONS */

// TODO: Not yet implemented.


#endif
