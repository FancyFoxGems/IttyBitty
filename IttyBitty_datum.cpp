/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef EXCLUDE_ITTYBITTY_DATUM


#include "IttyBitty_datum.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

#ifdef ARDUINO
CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;
#endif

CBYTE IttyBitty::DATA_SIZE_MASK = 0xF0;

PBYTE IttyBitty::__datum_buffer = NULL;

#pragma endregion

#endif	// #ifndef EXCLUDE_ITTYBITTY_DATUM
