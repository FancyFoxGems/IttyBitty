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


#pragma region GLOBAL CONSTANT & VARIABLE MEMBER DEFINITIONS

UIOPTIONS MenUIOptions = UiOptions();

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
