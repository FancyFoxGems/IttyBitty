/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_STORAGE
#endif

#ifndef NO_ITTYBITTY_STORAGE

#include "IttyBitty_storage.h"


#pragma region GLOBAL CONSTANT DEFINITIONS

CBYTE IttyBitty::STORAGE_ERASE_VALUE			= 0xFF;

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_STORAGE
