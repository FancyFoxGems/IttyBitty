/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_UI_options.h"

using namespace IttyBitty;


#pragma region GLOBAL VARIABLE & FUNCTION DEFINITIONS

UIOPTIONS MUI::Options = UiOptions();


RCUIRENDEREROPTIONS MUI::DefaultRendererOptions()
{
	STATIC UIRENDEREROPTIONS rendererOptions;

	return rendererOptions;
}

RCUIRENDEREROPTIONS MUI::DefaultLcdRendererOptions()
{
	STATIC UIRENDEREROPTIONS rendererOptions;

	rendererOptions.StyledLineLeftGlyph		= MENUI_DEFAULT_LCD_STYLED_LINE_LEFT_GLYPH;
	rendererOptions.StyledLineRightGlyph	= MENUI_DEFAULT_LCD_STYLED_LINE_RIGHT_GLYPH;

	return rendererOptions;
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
