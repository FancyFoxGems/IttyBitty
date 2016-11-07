/************************************************************************************************
* [IttyBitty_base.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*	LIBRARY - BASE BUNDLE: FULL LIBRARY FUNCTIONALITY MINUS HEAVY DATA STRUCTURES
*	Memory Usage: < 6.85 KB Program Memory (Flash ROM) / < 660 B SRAM
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
* [IttyBitty_GPIO.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
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
************************************************************************************************/

#ifndef ITTYBITTY_BASE
	#define ITTYBITTY_BASE
#endif

#ifndef EXCLUDE_ITTYBITTY_FULL_BYTES
	#define EXCLUDE_ITTYBITTY_FULL_BYTES
#endif

#ifndef EXCLUDE_ITTYBITTY_INTERRUPTS
	#define EXCLUDE_ITTYBITTY_INTERRUPTS
#endif

#ifndef EXCLUDE_ITTYBITTY_STORAGE
	#define EXCLUDE_ITTYBITTY_STORAGE
#endif

#ifndef EXCLUDE_ITTYBITTY_EEPROM_I2C
	#define EXCLUDE_ITTYBITTY_EEPROM_I2C
#endif

#ifndef EXCLUDE_ITTYBITTY_DB
	#define EXCLUDE_ITTYBITTY_DB
#endif

#include "IttyBitty.h"
