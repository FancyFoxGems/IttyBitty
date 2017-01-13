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
using namespace IttyBitty::MUI;


#pragma region [MenUI] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

MenUI::MenUI(CBYTE initMenuCapacity)
	: MenUI(0, NULL, 0, NULL, initMenuCapacity) { }

MenUI::MenUI(CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources,
		CBYTE rendererCount, PPIUIRENDERER renderers, CBYTE initMenuCapacity)
	: Menu(initMenuCapacity), Navigation(UiNavigationController(*this, inputSourceCount, inputSources)),
		Display(UiDisplayController(rendererCount, renderers)) { }


// ACCESSORS/MUTATORS

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
	Navigation.Poll();
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

VOID MenUI::Up(CUIACTIONSTATE state)
{
}

VOID MenUI::Down(CUIACTIONSTATE state)
{
}

VOID MenUI::Left(CUIACTIONSTATE state)
{
}

VOID MenUI::Right(CUIACTIONSTATE state)
{
}

VOID MenUI::Return(CUIACTIONSTATE state)
{
}

VOID MenUI::Select(CUIACTIONSTATE state)
{
}


// [IUiNavigationController] IMPLEMENTATION

CBOOL MenUI::IsShiftOn() const
{
	return Navigation.IsShiftOn();
}

VOID MenUI::ToggleShift()
{
	Navigation.ToggleShift();
}
VOID MenUI::ShiftOn()
{
	Navigation.ShiftOn();
}

VOID MenUI::ShiftOff()
{
	Navigation.ShiftOff();
}

CBOOL MenUI::IsAltOn() const
{
	return Navigation.IsAltOn();
}

VOID MenUI::ToggleAlt()
{
	Navigation.ToggleAlt();
}

VOID MenUI::AltOn()
{
	Navigation.AltOn();
}

VOID MenUI::AltOff()
{
	Navigation.AltOff();
}


// [Print] IMPLEMENTATION

SIZE MenUI::write(BYTE value)
{
	return Display.write(value);
}


// [IUiRenderer] IMPLEMENTATION

CBYTE MenUI::Cols() const
{
	return Display.Cols();
}

CBYTE MenUI::Rows() const
{
	return Display.Rows();
}

CBYTE MenUI::CursorCol() const
{
	return Display.CursorCol();
}

CBYTE MenUI::CursorRow() const
{
	return Display.CursorRow();
}

CBOOL MenUI::IsLineWrapEnabled() const
{
	return Display.IsLineWrapEnabled();
}

VOID MenUI::SetLineWrap(CBOOL wrapLines)
{
	Display.SetLineWrap(wrapLines);
}

VOID MenUI::CursorOn()
{
	Display.CursorOn();
}

VOID MenUI::CursorOff()
{
	Display.CursorOn();
}

VOID MenUI::CursorBlinkOn()
{
	Display.CursorOn();
}

VOID MenUI::CursorBlinkOff()
{
	Display.CursorOn();
}

CBOOL MenUI::Available()
{
	return Display.Available();
}

VOID MenUI::Flush()
{
	Display.Flush();
}

VOID MenUI::Clear()
{
	Display.Clear();
}

VOID MenUI::ClearCol(CBYTE col)
{
	Display.ClearCol(col);
}

VOID MenUI::ClearRow(CBYTE row)
{
	Display.ClearRow(row);
}

VOID MenUI::ScrollLeft()
{
	Display.ScrollLeft();
}

VOID MenUI::ScrollRight()
{
	Display.ScrollRight();
}

VOID MenUI::Home()
{
	Display.Home();
}

VOID MenUI::CursorPrev()
{
	Display.CursorPrev();
}

VOID MenUI::CursorNext()
{
	Display.CursorNext();
}

VOID MenUI::MoveCursor(CBYTE col, CBYTE row)
{
	Display.MoveCursor(col, row);
}

VOID MenUI::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
	Display.LoadCustomChar(charIndex, charData);
}

VOID MenUI::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
	Display.LoadCustomChar_P(charIndex, charDataAddr);
}

CBYTE MenUI::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	return Display.WriteAt(value, col, row);
}

CBYTE MenUI::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	return Display.PrintString(str, col, row);
}

CBYTE MenUI::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return Display.PrintString_P(flashStr, col, row);
}

CBYTE MenUI::PrintStyledLine(PCCHAR str, BYTE row)
{
	return Display.PrintStyledLine(str, row);
}

CBYTE MenUI::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
	return Display.PrintStyledLine_P(flashStr, row);
}


#ifndef NO_ITTYBITTY_EXTENSIONS

VOID MenUI::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
	Display.DrawScrollBar(percentage, options);
}

VOID MenUI::DrawGraph(BYTE startCol, BYTE row,
	BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
	Display.DrawGraph(startCol, row, widthChars, percentage, options);
}

VOID MenUI::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
	Display.DrawSlider(startCol, row, widthChars, percentage, options, redraw);
}

#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
