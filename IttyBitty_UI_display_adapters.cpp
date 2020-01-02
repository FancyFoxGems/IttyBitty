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


#pragma region [SerialUiRenderer] IMPLEMENTATION

// CONSTRUCTORS

SerialUiRenderer::SerialUiRenderer(HardwareSerial & serial, CUILISTITEMNUMBERINGFORMAT numberingFormat)
	: UiRendererBase(), _Serial(serial), _NumberingFormat(numberingFormat) { }

SerialUiRenderer::SerialUiRenderer(RUIRENDEREROPTIONS options, HardwareSerial & serial, CUILISTITEMNUMBERINGFORMAT numberingFormat)
	: UiRendererBase(options), _Serial(serial), _NumberingFormat(numberingFormat) { }


// [Print] OVERRIDE

SIZE SerialUiRenderer::write(BYTE value)
{
	return _Serial.write(value);
}


// [IUiRenderer] OVERRIDES

CBOOL SerialUiRenderer::Available()
{
	return _Serial.availableForWrite();
}

VOID SerialUiRenderer::Flush()
{
	return _Serial.flush();
}

VOID SerialUiRenderer::Clear()
{
	for (BYTE i = 0; i < MENUI_SERIAL_CLEAR_LINES; i++)
		_Serial.println();
}

CBYTE SerialUiRenderer::PrintStyledLine(PCCHAR str, BYTE col, BYTE row, BYTE cols)
{
	return UiRendererBase::PrintStyledLine(str, col, row, cols > 0 ? cols : MENUI_SERIAL_STYLED_LINE_COLS);
}

CBYTE SerialUiRenderer::PrintStyledLine_P(FLASH_STRING flashStr, BYTE col, BYTE row, BYTE cols)
{
	return UiRendererBase::PrintStyledLine_P(flashStr, col, row, cols > 0 ? cols : MENUI_SERIAL_STYLED_LINE_COLS);
}

VOID SerialUiRenderer::BeginListItem(BYTE itemNumber)
{
	char afterChar = NULL_CHARACTER;

	switch (_NumberingFormat)
	{
	case UiListItemNumberingFormat::NONE:
		break;

	case UiListItemNumberingFormat::NUMBER_DASH:
		afterChar = '-';
		break;

	case UiListItemNumberingFormat::NUMBER_DOT:
		afterChar = '.';
		break;

	case UiListItemNumberingFormat::PAREN_NUMBER_PAREN:
		_Serial.print('(');
	case UiListItemNumberingFormat::NUMBER_PAREN:
		afterChar = ')';
		break;

	case UiListItemNumberingFormat::BRACKETED_NUMBER:
		_Serial.print('[');
		afterChar = ']';
		break;
	}

	_Serial.print(itemNumber);

	if (afterChar)
		_Serial.print(afterChar);

	_Serial.print(' ');
}

VOID SerialUiRenderer::EndListItem(CCHAR inputTag)
{
	if (inputTag)
	{
		_Serial.print(" [");
		_Serial.print(inputTag);
		_Serial.print(']');
	}

	_Serial.println();
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
