/***********************************************************************************************
* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_REGISTERS_H
#define _ITTYBITTY_REGISTERS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


/* [register] DECLARATION ALIAS */

#define REGISTER volatile register


/* REGISTER-BOUND VARIABLE DECLARATION MACROS */

/*
	!! CONSTRAINT: 2 <= <register_num> <= 7 !!

	The MCU uses r0 and r1 for MUL & MULS 16-bit multiplication instructions;
	General purpose registers r8-15 are utilized by the AVR-C++ compiler;

	SEE: http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_regbind
*/
#define REG_VAR(type, var_name, register_num) REGISTER type var_name asm("r" #register_num)
#define REG_CHAR(var_name, register_num) REG_VAR(CHAR, var_name, register_num)
#define REG_BYTE(var_name, register_num) REG_VAR(BYTE, var_name, register_num)


/* BIT-PACKED SPECIAL-FUNCTION REGISTER DECLARATIONS */

// TODO: ...



#ifndef NO_ITTYBITTY_BYTES

#include "IttyBitty_bytes.h"

namespace IttyBitty
{
	/* BIT-PACKED REGISTER TYPE ALIASES */

	typedef IttyBitty::BYTEFIELD REG8, * PREG8, & RREG8, ** PPREG8, && RRREG8;

#ifndef NO_ITTYBITTY_FULL_BYTES
	typedef WORDFIELD REG16, * PREG16, & RREG16, ** PPREG16, && RRREG16;
	typedef DWORDFIELD REG32, * PREG32, & RREG32, ** PPREG32, && RRREG32;
#endif

	#define NEW_REG8(reg_addr) (new REG8((PVBYTE)reg_addr))
}

#endif	// #ifndef NO_ITTYBITTY_BYTES


#endif
