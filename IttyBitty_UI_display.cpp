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


#pragma region [UiRendererBase] IMPLEMENTATION

// CONSTRUCTORS

UiRendererBase::UiRendererBase() : UiRendererBase(MUI::DefaultRendererOptions()) { }

UiRendererBase::UiRendererBase(RCUIRENDEREROPTIONS options) : Options(options)
{
	if (Options.WrapLines)
		this->SetLineWrapEnabled();
}


// [IUiRenderer] (NON-)IMPLEMENTATION

CBYTE UiRendererBase::Cols() const { return MAX_BYTE; }

CBYTE UiRendererBase::Rows() const { return MAX_BYTE; }

CBYTE UiRendererBase::CursorCol() const { return MAX_BYTE; }

CBYTE UiRendererBase::CursorRow() const { return MAX_BYTE; }

CBOOL UiRendererBase::IsLineWrapEnabled() const { return FALSE; }

VOID UiRendererBase::SetLineWrapEnabled(CBOOL) { }

VOID UiRendererBase::CursorOff() { }

VOID UiRendererBase::CursorBlinkOn() { }

VOID UiRendererBase::CursorBlinkOff() { }

CBOOL UiRendererBase::Available() { return TRUE; }

VOID UiRendererBase::Flush() { }

VOID UiRendererBase::Clear() { }

VOID UiRendererBase::ClearCol(BYTE) { }

VOID UiRendererBase::ClearRow(BYTE) { }

VOID UiRendererBase::ClearArea(BYTE, BYTE, BYTE, BYTE) { }

VOID UiRendererBase::ScrollLeft() { }

VOID UiRendererBase::ScrollRight() { }

VOID UiRendererBase::Home() { }

VOID UiRendererBase::CursorPrev() { }

VOID UiRendererBase::CursorNext() { }

VOID UiRendererBase::MoveCursor(BYTE, BYTE) { }

VOID UiRendererBase::LoadCustomChar(BYTE charIndex, PCBYTE charData) { }

VOID UiRendererBase::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr) { }

CBYTE UiRendererBase::WriteAt(BYTE value, BYTE col, BYTE row)
{
	return (BYTE)this->write(value);
}

CBYTE UiRendererBase::UpdateAt(BYTE value, BYTE col, BYTE row)
{
	return 0;
}

CBYTE UiRendererBase::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	return this->print(str);
}

CBYTE UiRendererBase::UpdateString(PCCHAR str, BYTE col, BYTE row)
{
	return 0;
}

CBYTE UiRendererBase::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return this->print(flashStr);
}

CBYTE UiRendererBase::UpdateString_P(FLASH_STRING str, BYTE col, BYTE row)
{
	return 0;
}

CBYTE UiRendererBase::PrintStyledLine(PCCHAR str, BYTE col, BYTE row, BYTE cols)
{
	this->ClearRow(row);
	this->MoveCursor(col, row);
	
	if (cols == 0)
		cols = this->Cols();

	BYTE strLen = strlen(str);
	if (cols - strLen - 2 * Options.StyledLineMargins < 2)
		return this->print(str);

	BYTE glyphNum = (cols - strLen) / 2 - Options.StyledLineMargins;
	CHAR glyphs[glyphNum + 1];

	memset(glyphs, Options.StyledLineLeftGlyph, glyphNum);
	glyphs[glyphNum] = NULL_CHARACTER;

	BYTE charsWritten = this->print(glyphs);

	for (BYTE i = 0; i < Options.StyledLineMargins; i++)
		charsWritten += this->print(' ');

	charsWritten += this->print(str);

	for (BYTE i = 0; i < Options.StyledLineMargins; i++)
		charsWritten += this->print(' ');

	memset(glyphs, Options.StyledLineRightGlyph, glyphNum);
	glyphs[glyphNum] = NULL_CHARACTER;

	charsWritten += this->print(glyphs);

	return charsWritten;
}

CBYTE UiRendererBase::PrintStyledLine_P(FLASH_STRING flashStr, BYTE col, BYTE row, BYTE cols)
{
	BYTE strLen = 0;

	PCCHAR strAddr = reinterpret_cast<PCCHAR>(flashStr);
	BYTE c = pgm_read_byte_near(strAddr++);

	while (c != NULL_CHARACTER)
	{
		++strLen;

		c = pgm_read_byte_near(strAddr++);
	}

	CHAR str[strLen + 1];
	strAddr = reinterpret_cast<PCCHAR>(flashStr);

	for (BYTE i = 0; i < strLen; i++)
		str[i] = (CHAR)pgm_read_byte_near(strAddr++);

	str[strLen] = NULL_CHARACTER;

	return this->PrintStyledLine(str, row, cols);
}

CBYTE UiRendererBase::PrintGlyph(BYTE glyph, BYTE col, BYTE row) { return 0; }

VOID UiRendererBase::BeginListItem(BYTE itemNumber) { }

VOID UiRendererBase::EndListItem(CCHAR inputTag) { }


#ifndef NO_ITTYBITTY_LCD_EXTENSIONS

VOID UiRendererBase::DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS) { }

VOID UiRendererBase::DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS) { }

VOID UiRendererBase::DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL) { }

#endif	// #ifndef NO_ITTYBITTY_LCD_EXTENSIONS

#pragma endregion


#pragma region [UiDisplayController] IMPLEMENTATION

// CONSTRUCTOR/DESTRUCTOR

UiDisplayController::UiDisplayController(CBYTE rendererCount, PPIUIRENDERER renderers)
	: _RendererCount(rendererCount), _Renderers(renderers)
{
	if (_Renderers)
		_DisposeRenderers = TRUE;
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

	if (_DisposeRenderers)
	{
		for (BYTE i = 0; i < _RendererCount; i++)
		{
			if (_Renderers[i])
			{
				delete _Renderers[i];
				_Renderers[i] = NULL;
			}
		}

		_DisposeRenderers = FALSE;
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
	if (_DisposeRenderers)
		return FALSE;

	PPIUIRENDERER newRenderers = new PIUIRENDERER[++_RendererCount];

	for (BYTE i = 0; i < _RendererCount - 1; i++)
		newRenderers[i] = _Renderers[i];

	newRenderers[_RendererCount - 1] = &renderer;

	this->Dispose();

	_Renderers = newRenderers;

	return TRUE;
}

VOID UiDisplayController::ClearRenderers()
{
	this->Dispose();

	_RendererCount = 0;
}

VOID UiDisplayController::RemoveRenderer(CBYTE rendererIdx)
{
	if (rendererIdx >= _RendererCount)
		return;

	PPIUIRENDERER newRenderers = new PIUIRENDERER[--_RendererCount];
	BYTE currIdx = 0;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (currIdx != rendererIdx)
			newRenderers[currIdx++] = _Renderers[i];
	}

	if (_DisposeRenderers)
	{
		delete _Renderers[rendererIdx];
		_Renderers[rendererIdx] = NULL;
	}

	delete[] _Renderers;

	_Renderers = newRenderers;
}

VOID UiDisplayController::RemoveRenderer(RIUIRENDERER renderer)
{
	if (!_Renderers)
		return;

	for (BYTE i = 0; i < _RendererCount; i++)
	{
		if (_Renderers[i] == &renderer)
		{
			this->RemoveRenderer(i);
			break;
		}
	}
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

VOID UiDisplayController::SetLineWrapEnabled(CBOOL lineWrapEnabled)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::SetLineWrapEnabled, lineWrapEnabled);
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

VOID UiDisplayController::ClearCol(BYTE col)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearCol, col);
}

VOID UiDisplayController::ClearRow(BYTE row)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearRow, row);
}

VOID UiDisplayController::ClearArea(BYTE col, BYTE row, BYTE cols, BYTE rows)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::ClearArea, col, row, cols, rows);
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

VOID UiDisplayController::MoveCursor(BYTE col, BYTE row)
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

CBYTE UiDisplayController::WriteAt(BYTE value, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::WriteAt, value, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::UpdateAt(BYTE value, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::UpdateAt, value, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString, str, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::UpdateString(PCCHAR str, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::UpdateString, str, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintString_P, flashStr, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::UpdateString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::UpdateString_P, flashStr, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintStyledLine(PCCHAR str, BYTE col, BYTE row, BYTE cols)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintStyledLine, str, col, row, cols);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintStyledLine_P(FLASH_STRING flashStr, BYTE col, BYTE row, BYTE cols)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintStyledLine_P, flashStr, col, row, cols);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

CBYTE UiDisplayController::PrintGlyph(BYTE glyph, BYTE col, BYTE row)
{
	BYTE results[_RendererCount];

	PtrCallAll(_RendererCount, _Renderers, results, &IUiRenderer::PrintGlyph, glyph, col, row);

	return __ResultFromCallResults(results, _RendererCount, MAX_BYTE);
}

VOID UiDisplayController::BeginListItem(BYTE itemNumber)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::BeginListItem, itemNumber);
}

VOID UiDisplayController::EndListItem(CCHAR inputTag)
{
	PtrApplyAll(_RendererCount, _Renderers, &IUiRenderer::EndListItem, inputTag);
}


#ifndef NO_ITTYBITTY_LCD_EXTENSIONS

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

#endif	// #ifndef NO_ITTYBITTY_LCD_EXTENSIONS


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
