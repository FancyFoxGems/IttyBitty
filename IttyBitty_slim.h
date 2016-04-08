/**********************************************************************************
* [IttyBitty_slim.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*	LIBRARY - SLIM BUNDLE: FULL LIBRARY FUNCTIONALITY MINUS HEAVY DATA STRUCTURES
*
* INCLUDES:
*
* [IttyBitty_aliases.h]: TYPEDEFS FOR WIN32 API-STYLE TYPE REFERENCES

* [IttyBitty_type_traits.h]: METAFUNCTIONS FOR TEMPLATED TYPING GOODNESS
*	NOTE: ^-- As found in a subset of type support implemented in the Boost.MPL 
*		as well as various versions of C++ Standard Library [VERSION(C++) >= 11]

* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.

* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES (ONLY)
*	NOTE: ^-- Slim bundle excludes data structures for larger blocks
*
* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY
*
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#define ITTYBITTY_SLIM

#include "IttyBitty.h"
