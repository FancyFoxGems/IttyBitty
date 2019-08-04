/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_MENUI)
	#define NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
#endif

#ifndef NO_ITTYBITTY_UI_DISPLAY_ADAPTERS

#include "IttyBitty_UI_display_adapters.h"

using namespace IttyBitty;


#pragma region [SerialUiRenderer] IMPLEMENTATION

// CONSTRUCTORS

SerialUiRenderer::SerialUiRenderer(Stream & serial) : UiRenderer(), _Serial(serial) { }

SerialUiRenderer::SerialUiRenderer(RUIRENDEREROPTIONS options,
	Stream & serial) : UiRenderer(options), _Serial(serial) { }


// [Print] IMPLEMENTATION

SIZE SerialUiRenderer::write(BYTE value)
{
	return _Serial.write(value);
}


// [IUiRenderer] OVERRIDES

CBOOL SerialUiRenderer::Available()
{
	// TODO: Works without HardwareSerial reference?
	return TRUE;	/// return _Serial.availableForWrite();
}

VOID SerialUiRenderer::Flush()
{
	return _Serial.flush();
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
