/************************************************************************************************
* [IttyBitty_slim.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*	LIBRARY - SLIM BUNDLE: BASIC UTILITY, BIT MANIPULATION, & PIN MACROS/FUNCTIONS ONLY
*		Memory Usage:	< 2.75 KB Program Memory (Flash ROM) / < 400 B SRAM
*	NOTE: Uses very little program space or volatile memory! --^
*
* INCLUDES:
*
* [IttyBitty_aliases.h]: TYPEDEFS FOR WIN32 API-STYLE TYPE REFERENCES
*
* [IttyBitty_type_traits.h]: METAFUNCTIONS FOR TEMPLATED TYPING GOODNESS
*	NOTE: ^-- As found in a subset of type support implemented in the Boost.MPL
*		as well as various versions of C++ Standard Library [VERSION(C++) >= 11]
*
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
*
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* [IttyBitty_registers.h]: REGISTER VARIABLE TYPE & SFR MACROS
*	NOTE: ^-- In Slim bundle, no structure-based abstractions
*
* [IttyBitty_GPIO.h]: MACROS & FUNCTIONS FOR PIN ACCESS & MANIPULATION
*	NOTE: ^-- In Slim bundle, excludes structures for port/pin access
*
*
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
************************************************************************************************/

#ifndef ITTYBITTY_SLIM
	#define ITTYBITTY_SLIM
#endif

#ifndef NO_ITTYBITTY_INFO
	#define NO_ITTYBITTY_INFO
#endif

#ifndef NO_ITTYBITTY_BYTES
	#define NO_ITTYBITTY_BYTES
#endif

#ifndef NO_ITTYBITTY_INTERRUPTS
	#define NO_ITTYBITTY_INTERRUPTS
#endif

#ifndef NO_ITTYBITTY_TIMERS
	#define NO_ITTYBITTY_TIMERS
#endif

#ifndef NO_ITTYBITTY_LED
	#define NO_ITTYBITTY_LED
#endif

#ifndef NO_ITTYBITTY_PRINT
	#define NO_ITTYBITTY_PRINT
#endif

#ifndef NO_ITTYBITTY_MESSAGES
	#define NO_ITTYBITTY_MESSAGES
#endif

#include "IttyBitty_base.h"
