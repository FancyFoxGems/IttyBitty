/**********************************************************************************
* [IttyBitty_base.h]: A STRIPPED-DOWN BUNDLING OF ITTYBITTY'S FUNCTIONALITY
*
*
*		LIBRARY - BASE ONLY: BASIC UTILITY HELPERS & BIT MANIPULATION MACROS 
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
*	NOTE: ^-- In Base Only bundle, includes port/pin-referencing macros
*
* [IttyBitty_registers.h]: REGISTER VARIABLE TYPE & SFR MACROS
*	NOTE: ^-- In Base Only bundle, no structure-based abstractions
*
*
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#define ITTYBITTY_BASE_ONLY

#include "IttyBitty.h"
