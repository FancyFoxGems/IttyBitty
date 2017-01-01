/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_menui.h"

using namespace IttyBitty;


#pragma region [MenUI] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

MenUI::MenUI(CBYTE initMenuCapacity, CBOOL useGlobalOptions) : Menu(initMenuCapacity),
	_Navigation(UiNavigationController(*this)), _Display(UiDisplayController())
{
}

MenUI::MenUI(CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources,
		CBYTE rendererCount, PPIUIRENDERER renderers, CBYTE initMenuCapacity, CBOOL useGlobalOptions)
	: Menu(initMenuCapacity), _Navigation(UiNavigationController(*this,	inputSourceCount, inputSources)),
		_Display(UiDisplayController(rendererCount, renderers))
{
}

MenUI::~MenUI()
{
	//~Menu();
}


// ACCESSORS/MUTATORS

RUINAVIGATIONCONTROLLER MenUI::Navigation()
{
	return _Navigation;
}

RUIDISPLAYCONTROLLER MenUI::Display()
{
	return _Display;
}

PUICALLBACK MenUI::GetIdleHandler() const
{
	return _OnIdleHandler;
}

VOID MenUI::SetIdleHandler(PUICALLBACK onIdleHandler)
{
	_OnIdleHandler = onIdleHandler;
}



// USER METHODS

VOID MenUI::Update()
{
	_Navigation.Poll();
}

VOID MenUI::ShowText(PCCHAR str, CWORD timeoutMS, CBOOL allowEscape, CBOOL anyActionReturns)
{
}

VOID MenUI::ShowText_P(FLASH_STRING flashStr, CWORD timeoutMS, CBOOL allowEscape, CBOOL anyActionReturns)
{
}

VOID MenUI::Prompt(RUIDIALOG dialog)
{
}


// [IUiNavigationListener] OVERRIDES

CBOOL MenUI::IsShiftOn() const
{
	return _Navigation.IsShiftOn();
}

VOID MenUI::ToggleShift()
{
	_Navigation.ToggleShift();
}

VOID MenUI::ShiftOn()
{
	_Navigation.ShiftOn();
}

VOID MenUI::ShiftOff()
{
	_Navigation.ShiftOff();
}

CBOOL MenUI::IsAltOn() const
{
	return _Navigation.IsAltOn();
}

VOID MenUI::ToggleAlt()
{
	_Navigation.ToggleAlt();
}

VOID MenUI::AltOn()
{
	_Navigation.AltOn();
}

VOID MenUI::AltOff()
{
	_Navigation.AltOff();
}


// [Print] IMPLEMENTATION

SIZE MenUI::write(BYTE value)
{
	return _Display.write(value);
}


// [IUiRenderer] IMPLEMENTATION

CBYTE MenUI::Cols() const
{
	return _Display.Cols();
}

CBYTE MenUI::Rows() const
{
	return _Display.Rows();
}

CBYTE MenUI::CursorCol() const
{
	return _Display.CursorCol();
}

CBYTE MenUI::CursorRow() const
{
	return _Display.CursorRow();
}

CBOOL MenUI::IsLineWrapEnabled() const
{
	return _Display.IsLineWrapEnabled();
}

VOID MenUI::SetLineWrap(CBOOL wrapLines)
{
	_Display.SetLineWrap(wrapLines);
}

VOID MenUI::CursorOn()
{
	_Display.CursorOn();
}

VOID MenUI::CursorOff()
{
	_Display.CursorOn();
}

VOID MenUI::CursorBlinkOn()
{
	_Display.CursorOn();
}

VOID MenUI::CursorBlinkOff()
{
	_Display.CursorOn();
}

CBOOL MenUI::Available()
{
	return _Display.Available();
}

VOID MenUI::Flush()
{
	_Display.Flush();
}

VOID MenUI::Clear()
{
	_Display.Clear();
}

VOID MenUI::ClearCol(CBYTE col)
{
	_Display.ClearCol(col);
}

VOID MenUI::ClearRow(CBYTE row)
{
	_Display.ClearRow(row);
}

VOID MenUI::ScrollLeft()
{
	_Display.ScrollLeft();
}

VOID MenUI::ScrollRight()
{
	_Display.ScrollRight();
}

VOID MenUI::Home()
{
	_Display.Home();
}

VOID MenUI::CursorPrev()
{
	_Display.CursorPrev();
}

VOID MenUI::CursorNext()
{
	_Display.CursorNext();
}

VOID MenUI::MoveCursor(CBYTE col, CBYTE row)
{
	_Display.MoveCursor(col, row);
}

VOID MenUI::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
	_Display.LoadCustomChar(charIndex, charData);
}

VOID MenUI::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
	_Display.LoadCustomChar_P(charIndex, charDataAddr);
}

CBYTE MenUI::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	return _Display.WriteAt(value, col, row);
}

CBYTE MenUI::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	return _Display.PrintString(str, col, row);
}

CBYTE MenUI::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return _Display.PrintString_P(flashStr, col, row);
}

CBYTE MenUI::PrintStyledLine(PCCHAR str, BYTE row)
{
	return _Display.PrintStyledLine(str, row);
}

CBYTE MenUI::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
	return _Display.PrintStyledLine_P(flashStr, row);
}


#ifndef NO_ITTYBITTY_EXTENSIONS

VOID MenUI::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
	_Display.DrawScrollBar(percentage, options);
}

VOID MenUI::DrawGraph(BYTE startCol, BYTE row,
	BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
	_Display.DrawGraph(startCol, row, widthChars, percentage, options);
}

VOID MenUI::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
	_Display.DrawSlider(startCol, row, widthChars, percentage, options, redraw);
}

#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
