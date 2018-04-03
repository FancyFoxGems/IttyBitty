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


#pragma region RESULTS HELPER FUNCTION

template<typename TResult, typename TResultCount>
STATIC TResult __ResultFromCallResults(TResult * results,
	TResultCount resultCount, TResult defaultResult = 0)
{
	for (UNCONST_TYPE(TResultCount) i = 0; i < resultCount; i++)
	{
		if (results[i] < MAX_BYTE)
			return results[i];
	}

	return defaultResult;
}

#pragma endregion


#pragma region [UiRenderer] IMPLEMENTATION

// CONSTRUCTORS

UiRenderer::UiRenderer() : UiRenderer(MUI::DefaultRendererOptions()) { }

UiRenderer::UiRenderer(RUIRENDEREROPTIONS options) : Options(options)
{
	if (Options.WrapText)
		this->SetLineWrap();
}


// [IUiRenderer] (NON-)IMPLEMENTATION

CBYTE UiRenderer::Cols() const { return MAX_BYTE; }

CBYTE UiRenderer::Rows() const { return MAX_BYTE; }

CBYTE UiRenderer::CursorCol() const { return MAX_BYTE; }

CBYTE UiRenderer::CursorRow() const { return MAX_BYTE; }

CBOOL UiRenderer::IsLineWrapEnabled() const { return FALSE; }

VOID UiRenderer::SetLineWrap(CBOOL) { }

VOID UiRenderer::CursorOff() { }

VOID UiRenderer::CursorBlinkOn() { }

VOID UiRenderer::CursorBlinkOff() { }

CBOOL UiRenderer::Available() { return TRUE; }

VOID UiRenderer::Flush() { }

VOID UiRenderer::Clear() { }

VOID UiRenderer::ClearCol(CBYTE) { }

VOID UiRenderer::ClearRow(CBYTE) { }

VOID UiRenderer::ScrollLeft() { }

VOID UiRenderer::ScrollRight() { }

VOID UiRenderer::Home() { }

VOID UiRenderer::CursorPrev() { }

VOID UiRenderer::CursorNext() { }

VOID UiRenderer::MoveCursor(CBYTE, CBYTE) { }

VOID UiRenderer::LoadCustomChar(BYTE charIndex, PCBYTE charData) { }

VOID UiRenderer::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr) { }

CBYTE UiRenderer::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	return (BYTE)this->write(value);
}

CBYTE UiRenderer::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	return this->print(str);
}

CBYTE UiRenderer::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return this->print(flashStr);
}

CBYTE UiRenderer::PrintStyledLine(PCCHAR str, BYTE row)
{
	this->ClearRow(row);
	this->MoveCursor(0, row);

	BYTE strLen = strlen(str);
	BYTE leftGlyphNum = (this->Cols() - strLen) / 2 - Options.StyledLineMargins;
	BYTE rightGlyphNum = this->Cols() - leftGlyphNum - strLen - Options.StyledLineMargins;

	CHAR glyphs[rightGlyphNum + 1];
	memset(glyphs, Options.StyledLineLeftGlyph, leftGlyphNum);
	glyphs[leftGlyphNum] = '\0';

	BYTE charsWritten = this->print(glyphs);

	for (BYTE i = 0; i < Options.StyledLineMargins; i++)
		charsWritten += this->print(' ');

	charsWritten += this->print(str);

	for (BYTE i = 0; i < Options.StyledLineMargins; i++)
		charsWritten += this->print(' ');

	memset(glyphs, Options.StyledLineRightGlyph, rightGlyphNum);
	glyphs[rightGlyphNum] = '\0';

	charsWritten += this->print(glyphs);

	return charsWritten;
}

CBYTE UiRenderer::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
	BYTE strLen = 0;

	PCCHAR strAddr = reinterpret_cast<PCCHAR>(flashStr);
	BYTE c = pgm_read_byte_near(strAddr++);

	while (c != '\0')
	{
		++strLen;

		c = pgm_read_byte_near(strAddr++);
	}

	CHAR str[strLen + 1];
	strAddr = reinterpret_cast<PCCHAR>(flashStr);

	for (BYTE i = 0; i < strLen; i++)
		str[i] = (CHAR)pgm_read_byte_near(strAddr++);

	str[strLen] = '\0';

	return this->PrintStyledLine(str, row);
}


#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiRenderer::DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS) { }

VOID UiRenderer::DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS) { }

VOID UiRenderer::DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL) { }

#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS

#pragma endregion


#pragma region [UiDisplayController] IMPLEMENTATION

// CONSTRUCTOR/DESTRUCTOR

UiDisplayController::UiDisplayController(CBYTE rendererCount, PPIUIRENDERER renderers)
	: _RendererCount(rendererCount), _Renderers(renderers)
{
	if (!_Renderers)
		_Dispose = TRUE;
}

UiDisplayController::~UiDisplayController()
{
	this->Dispose();
}


// PROTECTED DISPOSAL METHOD

VOID UiDisplayController::Dispose()
{
	if (!_Renderers)
		return;

	if (_Dispose)
	{
		for (BYTE i = 0; i < _RendererCount; i++)
		{
			if (_Renderers[i])
			{
				delete _Renderers[i];
				_Renderers[i] = NULL;
			}
		}
	}

	delete _Renderers;
	_Renderers = NULL;
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


// [IUiDisplayController] IMPLEMENTATION

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

CBOOL UiDisplayController::AddRenderer(RIUIRENDERER renderer)
{
	if (!_Dispose)
		return FALSE;

	PPIUIRENDERER newRenderers = new PIUIRENDERER[++_RendererCount];

	for (BYTE i = 0; i < _RendererCount - 1; i++)
		newRenderers[i] = _Renderers[i];

	newRenderers[_RendererCount - 1] = &renderer;

	this->Dispose();

	_Renderers = newRenderers;

	return TRUE;
}

VOID UiDisplayController::RemoveRenderer(CBYTE rendererIdx)
{
	PPIUIRENDERER newRenderers = new PIUIRENDERER[--_RendererCount];
	BYTE currIdx = 0;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (currIdx != rendererIdx)
			newRenderers[currIdx++] = _Renderers[i];
	}

	this->Dispose();

	_Renderers = newRenderers;
}

VOID UiDisplayController::RemoveRenderer(RIUIRENDERER renderer)
{
	PPIUIRENDERER newRenderers = new PIUIRENDERER[--_RendererCount];
	BYTE currIdx = 0;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (_Renderers[i] != &renderer)
			newRenderers[currIdx++] = _Renderers[i];
	}

	this->Dispose();

	_Renderers = newRenderers;
}


// [IUiRenderer] IMPLEMENTATION

CBYTE UiDisplayController::Cols() const
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::Cols);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::Rows() const
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::Rows);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::CursorCol() const
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::CursorCol);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::CursorRow() const
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::CursorRow);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBOOL UiDisplayController::IsLineWrapEnabled() const
{
	return PtrAny(_RendererCount, _Renderers, &IUiRenderer::IsLineWrapEnabled);
}

VOID UiDisplayController::SetLineWrap(CBOOL wrapLines)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::SetLineWrap, wrapLines);
}

VOID UiDisplayController::CursorOn()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorOn);
}

VOID UiDisplayController::CursorOff()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorOff);
}

VOID UiDisplayController::CursorBlinkOn()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorBlinkOn);
}

VOID UiDisplayController::CursorBlinkOff()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorBlinkOff);
}

CBOOL UiDisplayController::Available()
{
	return PtrAll(_RendererCount, _Renderers, &IUiRenderer::Available);
}

VOID UiDisplayController::Flush()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::Flush);
}

VOID UiDisplayController::Clear()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::Clear);
}

VOID UiDisplayController::ClearCol(CBYTE col)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearCol, col);
}

VOID UiDisplayController::ClearRow(CBYTE row)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearRow, row);
}

VOID UiDisplayController::ScrollLeft()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ScrollLeft);
}

VOID UiDisplayController::ScrollRight()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ScrollRight);
}

VOID UiDisplayController::Home()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::Home);
}

VOID UiDisplayController::CursorPrev()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorPrev);
}

VOID UiDisplayController::CursorNext()
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::CursorNext);
}

VOID UiDisplayController::MoveCursor(CBYTE col, CBYTE row)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::MoveCursor, col, row);
}

VOID UiDisplayController::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::LoadCustomChar, charIndex, charData);
}

VOID UiDisplayController::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::LoadCustomChar_P, charIndex, charDataAddr);
}

CBYTE UiDisplayController::WriteAt(CBYTE value, CBYTE col, CBYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::WriteAt, value, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString, str, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString_P, flashStr, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintStyledLine(PCCHAR str, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintStyledLine, str, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintStyledLine_P, flashStr, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}


#ifndef NO_ITTYBITTY_EXTENSIONS

VOID UiDisplayController::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::DrawScrollBar, percentage, options);
}

VOID UiDisplayController::DrawGraph(BYTE startCol, BYTE row,
	BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::DrawGraph,
		startCol, row, widthChars, percentage, options);
}

VOID UiDisplayController::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::DrawSlider,
		startCol, row, widthChars, percentage, options, redraw);
}

#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS


// [Print] IMPLEMENTATION

SIZE UiDisplayController::write(BYTE value)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, BYTE>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::write, value);

	return __ResultFromCallResults(results, _RendererCount);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
