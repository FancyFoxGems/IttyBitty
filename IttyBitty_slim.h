/************************************************************************************************
* [IttyBitty_slim.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*	LIBRARY - SLIM BUNDLE: BASIC UTILITY, BIT MANIPULATION, & PIN MACROS/FUNCTIONS ONLY
*
*		Memory Usage:	~1.93 KB Program Memory (Flash ROM) / 225 B SRAM
*		NOTE: Uses very little program space or system memory! --^
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
* [IttyBitty_interrupts.h]:
*	NOTE: ^-- In Slim bundle, excludes structures for interrupt management
*
* [IttyBitty_timers.h]:
*	NOTE: ^-- In Slim bundle, excludes structures for timer management
*
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
************************************************************************************************/

#define ITTYBITTY_SLIM

#define NO_ITTYBITTY_BYTES
#define NO_ITTYBITTY_PRINT
#define NO_ITTYBITTY_INFO
#define NO_ITTYBITTY_LED
#define NO_ITTYBITTY_VALUES

#include "IttyBitty_base.h"
