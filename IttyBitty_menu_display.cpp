/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_menu_display.h"

using namespace IttyBitty;


#pragma region [UiRendererBase] IMPLEMENTATION

// [IUiRenderer] IMPLEMENTATION

CBYTE UiRendererBase::Cols() const
{
}

CBYTE UiRendererBase::Rows() const
{
}

CBOOL UiRendererBase::IsLineWrapEnabled() { return FALSE; }

VOID UiRendererBase::SetLineWrap(CBOOL wrapLines)
{
}

VOID UiRendererBase::CursorOff()
{
}

VOID UiRendererBase::CursorBlinkOn()
{
}

VOID UiRendererBase::CursorBlinkOff()
{
}

CBYTE UiRendererBase::CursorCol() { return MAX_BYTE; }

CBYTE UiRendererBase::CursorRow() { return MAX_BYTE; }

VOID UiRendererBase::CursorOn()
{
}

CBOOL UiRendererBase::Available() { return TRUE; }

VOID UiRendererBase::Clear()
{
}

VOID UiRendererBase::ClearCol(CBYTE)
{
}

VOID UiRendererBase::ClearRow(CBYTE)
{
}

VOID UiRendererBase::ScrollLeft()
{
}

VOID UiRendererBase::ScrollRight()
{
}

VOID UiRendererBase::Home()
{
}

VOID UiRendererBase::CursorPrev()
{
}

VOID UiRendererBase::CursorNext()
{
}

VOID UiRendererBase::MoveCursor(CBYTE, CBYTE)
{
}

VOID UiRendererBase::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
}

VOID UiRendererBase::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
}

CBYTE UiRendererBase::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
}

CBYTE UiRendererBase::PrintString(PCCHAR str, BYTE col, BYTE row)
{
}

CBYTE UiRendererBase::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
}

CBYTE UiRendererBase::PrintStyledLine(PCCHAR str, BYTE row)
{
}

CBYTE UiRendererBase::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
}

#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiRendererBase::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
}

VOID UiRendererBase::DrawGraph(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
}

VOID UiRendererBase::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
}

#endif

#pragma endregion


#pragma region [UiDisplayController] IMPLEMENTATION

// [IUiRenderer] IMPLEMENTATION

CBYTE UiDisplayController::Cols() const
{
}

CBYTE UiDisplayController::Rows() const
{
}

CBOOL UiDisplayController::IsLineWrapEnabled() { return FALSE; }

VOID UiDisplayController::SetLineWrap(CBOOL wrapLines)
{
}

VOID UiDisplayController::CursorOff()
{
}

VOID UiDisplayController::CursorBlinkOn()
{
}

VOID UiDisplayController::CursorBlinkOff()
{
}

CBOOL UiDisplayController::Available() { return TRUE; }

VOID UiDisplayController::Clear()
{
}

VOID UiDisplayController::ClearCol(CBYTE)
{
}

VOID UiDisplayController::ClearRow(CBYTE)
{
}

VOID UiDisplayController::ScrollLeft()
{
}

VOID UiDisplayController::ScrollRight()
{
}

VOID UiDisplayController::Home()
{
}

VOID UiDisplayController::CursorPrev()
{
}

VOID UiDisplayController::CursorNext()
{
}

VOID UiDisplayController::MoveCursor(CBYTE, CBYTE)
{
}

VOID UiDisplayController::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
}

VOID UiDisplayController::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
}

CBYTE UiDisplayController::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
}

CBYTE UiDisplayController::PrintString(PCCHAR str, BYTE col, BYTE row)
{
}

CBYTE UiDisplayController::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
}

CBYTE UiDisplayController::PrintStyledLine(PCCHAR str, BYTE row)
{
}

CBYTE UiDisplayController::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
}

#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiDisplayController::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
}

VOID UiDisplayController::DrawGraph(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
}

VOID UiDisplayController::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
}

#endif

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
