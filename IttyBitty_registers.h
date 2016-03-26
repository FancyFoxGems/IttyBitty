/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#ifndef _ITTYBITTY_REGISTERS_H
#define _ITTYBITTY_REGISTERS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_util.h"


/* register DECLARATION ALIAS */

#define REG volatile register


/* REGISTER-BOUND VARIABLE DECLARATION MACROS */

/*
	!! CONSTRAINT: 2 <= <register_num> <= 7 !!

	The MCU uses r0 and r1 for MUL & MULS 16-bit multiplication instructions; 
	General purpose registers r8-15 are utilized by the AVR-C++ compiler;
	SEE: http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_regbind
*/
#define REG_VAR(type, var_name, register_num) REG type var_name asm("r" #register_num)
#define REG_CHAR(var_name, register_num) REG_VAR(CHAR, var_name, register_num)
#define REG_BYTE(var_name, register_num) REG_VAR(BYTE, var_name, register_num)


#endif
