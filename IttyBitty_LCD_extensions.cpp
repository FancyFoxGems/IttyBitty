/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_LCD) || defined(NO_ITTYBITTY_LCD_I2C)
	#define NO_ITTYBITTY_EXTENSIONS
#endif

#ifndef NO_ITTYBITTY_EXTENSIONS


#include "IttyBitty_LCD_I2C.h"


namespace IttyBitty
{
#pragma region LCD EXTENSIONS CONSTANT DEFINITIONS

	CBYTE LCD_CELL_SEMI_MASKS[3][3]	= { { 0x9, 0x12, 0x4 }, { 0x15, 0xA, 0xFF }, { 0x16, 0xD, 0x1B } };

#pragma endregion


#pragma region CUSTOM CHARACTER FLASH DATA DECLARATIONS

	// Scrollbar icons
	PROGMEM CBYTE LCD_CHAR_SCROLLBAR_TOP[8]			= { 0x1F, 0x1F, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	PROGMEM CBYTE LCD_CHAR_SCROLLBAR_BOTTOM[8]		= { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1F, 0x1F };

	// Slider icons
	PROGMEM CBYTE LCD_CHAR_SLIDER_END_LEFT[8]		= { 0x1F, 0x13, 0x15, 0x19, 0x19, 0x15, 0x13, 0x1F };
	PROGMEM CBYTE LCD_CHAR_SLIDER_END_RIGHT[8]		= { 0x1F, 0x19, 0x15, 0x13, 0x13, 0x15, 0x19, 0x1F };

#pragma endregion
};

#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS
