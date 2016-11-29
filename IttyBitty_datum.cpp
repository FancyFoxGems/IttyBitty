/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_VALUES)
	#define NO_ITTYBITTY_DATUM
#endif

#ifndef NO_ITTYBITTY_DATUM


#include "IttyBitty_datum.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANT & VARIABLE DEFINITIONS

#ifdef ARDUINO
CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;
#endif

PBYTE IttyBitty::__datum_buffer = NULL;

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_DATUM
