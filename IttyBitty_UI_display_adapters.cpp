/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_MENUI)
	#define NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
#endif

#ifndef NO_ITTYBITTY_UI_DISPLAY_ADAPTERS

#include "IttyBitty_UI_display_adapters.h"

using namespace IttyBitty;


#pragma region [StreamUiRenderer] IMPLEMENTATION

// CONSTRUCTORS

StreamUiRenderer::StreamUiRenderer(Stream & serial) : UiRenderer(), _Serial(serial) { }

StreamUiRenderer::StreamUiRenderer(RUIRENDEREROPTIONS options,
	Stream & serial) : UiRenderer(options), _Serial(serial) { }


// [Print] IMPLEMENTATION

SIZE StreamUiRenderer::write(BYTE value)
{
	return _Serial.write(value);
}


// [IUiRenderer] OVERRIDES

CBOOL StreamUiRenderer::Available()
{
	// TODO: Works without HardwareSerial reference?
	return TRUE;	/// return _Serial.availableForWrite();
}

VOID StreamUiRenderer::Flush()
{
	return _Serial.flush();
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
