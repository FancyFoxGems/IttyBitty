/************************************************************************************************
* Name:		Itty Bitty (Arduino Library)
* Created:	3/20/2016
* Author:	Tom Biuso <tjbtech@yahoo.com>
*
* This file is the root, primary source code file for the Itty Bitty Arduino Library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
*
* Itty Bitty is free software: you can redistribute it and/or modify it under the terms of the
* GNU General Public License as published by the Free Software Foundation, either version 3 of
* the License, or (at your option) any later version.
*
* Itty Bitty is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* See the included GNU General Public License text for more details.
************************************************************************************************/

#ifndef _ITTYBITTY_
#define _ITTYBITTY_ "FTW"

#ifdef __AVR__	// NOTE: AVR architecture compatibility only!


/* NOTE: DEFINE [ITTYBITTY_BASE] TO INCLUDE ONLY THE BARE MINIMUM, SUCH AS BIT-TWIDDLING MACROS */

/**********************************************************************************
* [IttyBitty_slim.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*	LIBRARY - SLIM BUNDLE: BASIC UTILITY HELPERS & BIT MANIPULATION MACROS ONLY
*	NOTE: ^-- Uses hardly ANY program space or memory!
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
* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE
*
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* [IttyBitty_registers.h]: REGISTER VARIABLE TYPE & SFR MACROS
*	NOTE: ^-- In Slim bundle, no structure-based abstractions
*
* [IttyBitty_gpio.h]: MACROS FOR PIN ACCESS & MANIPULATION
*	NOTE: ^-- In Slim bundle, excludes structures for port/pin access
*
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#if defined(ITTYBITTY_SLIM) && !defined(ITTYBITTY_BASE)
	#define ITTYBITTY_BASE
#endif

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_BYTES)
	#define EXCLUDE_ITTYBITTY_BYTES
#endif


/* NOTE: DEFINE [ITTYBITTY_BASE] TO EXCLUDE (MORE RESOURCE-DEMANDING) FULL-FEATURED FUNCTIONALITY */

/**********************************************************************************
* [IttyBitty_base.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*	LIBRARY - BASE BUNDLE: FULL LIBRARY FUNCTIONALITY MINUS HEAVY DATA STRUCTURES
*	NOTE: ^-- Requires approximately 5 KB of program space and 500 B memory
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
* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE
*
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES (ONLY)
*	NOTE: ^-- Base bundle excludes data structures for larger blocks
*
* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY
*
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* [IttyBitty_values.h]: UNIVERSAL TYPE (TAGGED) UNIONS
*
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
*
* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC
*
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifdef ITTYBITTY_BASE
	#undef EXCLUDE_ITTYBITTY_INTERRUPTS
#endif


//#include "IttyBitty_aliases.h"		// Included by [IttyBitty_type_traits.h]
//#include "IttyBitty_type_traits.h"	// Included by [IttyBitty_util.h]
//#include "IttyBitty_util.h"			// Included by [IttyBitty_bits.h]


/* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE */

#ifndef EXCLUDE_ITTYBITTY_INFO
	#include "IttyBitty_info.h"
#endif


/* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES, WORDS, DWORDS, ... */

#ifndef EXCLUDE_ITTYBITTY_BYTES
	#include "IttyBitty_bytes.h"
#else
	#include "IttyBitty_bits.h"			// Included by [IttyBitty_bytes.h] otherwise
#endif


/* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY */

#ifndef EXCLUDE_ITTYBITTY_REGISTERS
	#include "IttyBitty_registers.h"
#elif !defined(EXCLUDE_ITTYBITTY_INTERRUPTS)
	#define EXCLUDE_ITTYBITTY_INTERRUPTS
#endif


/* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS */

#ifndef EXCLUDE_ITTYBITTY_GPIO
	#include "IttyBitty_gpio.h"
#elif !defined(EXCLUDE_ITTYBITTY_LED)
	#define EXCLUDE_ITTYBITTY_LED
#endif


/* [IttyBitty_interrupts.h]:  */

#ifndef EXCLUDE_ITTYBITTY_INTERRUPTS
	#include "IttyBitty_interrupts.h"
#elif !defined(EXCLUDE_ITTYBITTY_LED)
	#define EXCLUDE_ITTYBITTY_LED
#endif


/* [IttyBitty_led.h]: DATA TYPE FOR DEAD-EASY ON-BOARD & EXTERNAL LED BLINKING */

#ifndef EXCLUDE_ITTYBITTY_LED
	#include "IttyBitty_led.h"
#endif


/* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS */

#ifndef EXCLUDE_ITTYBITTY_PRINT
	#include "IttyBitty_print.h"
#endif


/* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC */

#ifndef EXCLUDE_ITTYBITTY_MESSAGES
	#include "IttyBitty_messages.h"
#elif !defined(EXCLUDE_ITTYBITTY_FIELDS)
	#define EXCLUDE_ITTYBITTY_FIELDS
#endif


#endif	// __AVR__

#endif
