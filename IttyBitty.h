/************************************************************
* Name:		IttyBitty Library
* Created:	3/20/2016
* Author:	Tom Biuso <tjbtech@yahoo.com>
*
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*************************************************************/

#ifndef _ITTYBITTY_
#define _ITTYBITTY_ "FTW"


#include "IttyBitty_aliases.h"
#include "IttyBitty_util.h"
#include "IttyBitty_bits.h"


#ifdef ITTY_BITTY_BASE_ONLY
	#define EXCLUDE_ITTYBITTY_REGISTERS
	#define EXCLUDE_ITTYBITTY_BYTES
#endif

#ifndef EXCLUDE_ITTYBITTY_REGISTERS
	#include "IttyBitty_registers.h"
#else
	#define EXCLUDE_ITTYBITTY_GPIO
	#define EXCLUDE_ITTYBITTY_INTERRUPTS
#endif

#ifndef EXCLUDE_ITTYBITTY_BYTES
	#include "IttyBitty_bytes.h"
#else
	#define EXCLUDE_ITTYBITTY_GPIO
	#define EXCLUDE_ITTYBITTY_INTERRUPTS
#endif

#ifndef EXCLUDE_ITTYBITTY_GPIO
	#include "IttyBitty_gpio.h"
#else
	#define EXCLUDE_ITTYBITTY_LED
#endif

#ifndef EXCLUDE_ITTYBITTY_INTERRUPTS
	#include "IttyBitty_interrupts.h"
#else
	#define EXCLUDE_ITTYBITTY_LED
#endif

#ifndef EXCLUDE_ITTYBITTY_LED
	#include "IttyBitty_led.h"
#endif


#endif
