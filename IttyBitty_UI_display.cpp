/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_UI_display.h"

using namespace IttyBitty;


#pragma region [UiRendererBase] IMPLEMENTATION

// [IUiRenderer] IMPLEMENTATION

CBYTE UiRendererBase::Cols() const { return MAX_BYTE; }

CBYTE UiRendererBase::Rows() const { return MAX_BYTE; }

CBOOL UiRendererBase::IsLineWrapEnabled() const { return FALSE; }

VOID UiRendererBase::SetLineWrap(CBOOL) { }

VOID UiRendererBase::CursorOff() { }

VOID UiRendererBase::CursorBlinkOn() { }

VOID UiRendererBase::CursorBlinkOff() { }

CBOOL UiRendererBase::Available() { return TRUE; }

VOID UiRendererBase::Flush() { }

VOID UiRendererBase::Clear() { }

VOID UiRendererBase::ClearCol(CBYTE) { }

VOID UiRendererBase::ClearRow(CBYTE) { }

VOID UiRendererBase::ScrollLeft() { }

VOID UiRendererBase::ScrollRight() { }

VOID UiRendererBase::Home() { }

VOID UiRendererBase::CursorPrev() { }

VOID UiRendererBase::CursorNext() { }

VOID UiRendererBase::MoveCursor(CBYTE, CBYTE) { }

VOID UiRendererBase::LoadCustomChar(BYTE charIndex, PCBYTE charData) { }

VOID UiRendererBase::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr) { }

CBYTE UiRendererBase::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	this->write(value);

	return 1;
}

#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiRendererBase::DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS) { }

VOID UiRendererBase::DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS) { }

VOID UiRendererBase::DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL) { }

#endif

#pragma endregion


#pragma region [UiDisplayController] IMPLEMENTATION

UiDisplayController::UiDisplayController(CBYTE rendererCount, PPIUIRENDERER renderers)
	: _RendererCount(rendererCount), _Renderers(renderers) { }

UiDisplayController::UiDisplayController(RIUIRENDERER renderer) : _RendererCount(1)
{
	_Renderers = new PIUIRENDERER[1];
	_Renderers[0] = &renderer;
}

UiDisplayController::~UiDisplayController()
{
	if (_Renderers)
	{
		for (BYTE i = 0; i < _RendererCount; i++)
		{
			if (_Renderers[i])
			{
				delete _Renderers[i];
				_Renderers[i] = NULL;
			}
		}

		delete _Renderers;
		_Renderers = NULL;

		_RendererCount = 0;
	}
}


// OPERATORS

PCIUIRENDERER UiDisplayController::operator[](CBYTE i) const
{
	if (!_Renderers)
		return NULL;

	return _Renderers[i];
}

PIUIRENDERER UiDisplayController::operator[](CBYTE i)
{
	if (!_Renderers)
		return NULL;

	return _Renderers[i];
}


// ACCESSORS

CBYTE UiDisplayController::RendererCount() const
{
	return _RendererCount;
}

RCIUIRENDERER UiDisplayController::Renderer(CBYTE i) const
{
	return *this->operator[](i);
}

RIUIRENDERER UiDisplayController::Renderer(CBYTE i)
{
	return *this->operator[](i);
}


// [IUiRenderer] IMPLEMENTATION

CBYTE UiDisplayController::Cols() const
{
	BYTE cols = MAX_BYTE;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		cols = _Renderers[i]->Cols();
		if (cols < MAX_BYTE)
			return cols;
	}

	return cols;
}

CBYTE UiDisplayController::Rows() const
{
	BYTE rows = MAX_BYTE;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		rows = _Renderers[i]->Rows();
		if (rows < MAX_BYTE)
			return rows;
	}

	return rows;
}

CBOOL UiDisplayController::IsLineWrapEnabled() const
{
	return PtrAny<BYTE, IUIRENDERER>(_RendererCount, _Renderers, &IUiRenderer::IsLineWrapEnabled);
}

VOID UiDisplayController::SetLineWrap(CBOOL wrapLines)
{
	//PtrApplyAll<BYTE, IUIRENDERER, CBOOL>(_RendererCount, _Renderers, &IUiRenderer::SetLineWrap, wrapLines);
}

VOID UiDisplayController::CursorOff()
{
	PtrApplyAll<BYTE, IUIRENDERER>(_RendererCount, _Renderers, &IUiRenderer::CursorOff);
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

VOID UiDisplayController::ClearCol(CBYTE col)
{
}

VOID UiDisplayController::ClearRow(CBYTE row)
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

VOID UiDisplayController::MoveCursor(CBYTE col, CBYTE row)
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
