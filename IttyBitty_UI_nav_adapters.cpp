/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_MENUI)
	#define NO_ITTYBITTY_UI_NAV_ADAPTERS
#endif

#ifndef NO_ITTYBITTY_UI_NAV_ADAPTERS

#include "IttyBitty_UI_nav_adapters.h"

using namespace IttyBitty;


#pragma region [SimpleUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

SimpleUiInputSource::SimpleUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CUIACTION action)
	: UiInputSource(navigation),
	_Action(action) { }


// [IUiInputSource] OVERRIDES

CBOOL SimpleUiInputSource::IsAsynchronous() const
{
	return TRUE;
}

VOID SimpleUiInputSource::Poll() { }


// USER METHODS

VOID SimpleUiInputSource::Fire(CUIACTIONSTATE state)
{
	_Navigation.FireAction(_Action, state);
}

#pragma endregion


#pragma region [StreamUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

StreamUiInputSource::StreamUiInputSource(RIUINAVIGATIONCONTROLLER navigation, Stream & stream, CSTREAMUIINPUTOPTIONS options)
	: UiInputSource(navigation), 
		_Stream(stream), _Options(options) { }


// [IUiInputSource] OVERRIDES

CBOOL StreamUiInputSource::IsAsynchronous() const
{
	return FALSE;
}

VOID StreamUiInputSource::Poll()
{
	if (!_Stream.available())
		return;

	PCHAR buffer = new char[UI_INPUT_VALUE_BUFFER_SIZE];
	BYTE bufferLength = 0;
	CHAR c = NULL_CHARACTER;

	while (_Stream.available())
	{
		c = _Stream.read();

		switch (c)
		{
		case CR:
			if (WITH_BITS(_Options, EXCLUDE_CARRIAGE_RETURN))
				continue;
			break;

		case LF:
			if (WITH_BITS(_Options, EXCLUDE_LINEFEED))
				continue;
			break;

		case SPACE:
			if (WITH_BITS(_Options, EXCLUDE_SPACE))
				continue;
			break;

		case TAB:
			if (WITH_BITS(_Options, EXCLUDE_TAB))
				continue;
			break;
		}

		buffer[bufferLength++] = c;
	}

	buffer[bufferLength] = NULL_CHARACTER;

	_Navigation.SendValue(buffer);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_UI_NAV_ADAPTERS
