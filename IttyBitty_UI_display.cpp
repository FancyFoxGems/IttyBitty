/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_expressions.h"
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

UiRendererBase::UiRendererBase() : Options(MUI::GetDefaultRendererOptions()) { }

UiRendererBase::UiRendererBase(RUIRENDEREROPTIONS options) : Options(options) { }


// [IUiRenderer] (NON-)IMPLEMENTATION

CBYTE UiRendererBase::Cols() const { return MAX_BYTE; }

CBYTE UiRendererBase::Rows() const { return MAX_BYTE; }

CBYTE UiRendererBase::CursorCol() const { return MAX_BYTE; }

CBYTE UiRendererBase::CursorRow() const { return MAX_BYTE; }

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
	return (BYTE)this->write(value);
}

CBYTE UiRendererBase::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	return this->print(str);
}

CBYTE UiRendererBase::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return this->print(flashStr);
}

CBYTE UiRendererBase::PrintStyledLine(PCCHAR str, BYTE row)
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

CBYTE UiRendererBase::PrintStyledLine_P(FLASH_STRING flashStr, BYTE row)
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

VOID UiRendererBase::DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS) { }

VOID UiRendererBase::DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS) { }

VOID UiRendererBase::DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL) { }

#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS

#pragma endregion


#pragma region [UiDisplayController] IMPLEMENTATION

UiDisplayController::UiDisplayController(CBYTE rendererCount, PPIUIRENDERER renderers)
	: _Dispose(FALSE), _RendererCount(rendererCount), _Renderers(renderers) { }

UiDisplayController::UiDisplayController(RIUIRENDERER renderer) : _Dispose(TRUE), _RendererCount(1)
{
	_Renderers = new PIUIRENDERER[1];
	_Renderers[0] = &renderer;
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


// ACCESSORS/MUTATORS

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

RIUIRENDERER UiDisplayController::AddRenderer(RIUIRENDERER renderer)
{
	PPIUIRENDERER newRenderers = new PIUIRENDERER[++_RendererCount];

	for (BYTE i = 0; i < _RendererCount - 1; i++)
		newRenderers[i] = _Renderers[i];

	newRenderers[_RendererCount - 1] = &renderer;

	this->Dispose();

	_Renderers = newRenderers;

	return renderer;
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


// [Print] IMPLEMENTATION

SIZE UiDisplayController::write(BYTE value)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, BYTE>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::write, value);

	return __ResultFromCallResults(results, _RendererCount);
}


// [Print] OVERRIDES
/*
SIZE UiDisplayController::write(PCBYTE buffer, SIZE size)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, PCBYTE, SIZE>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::write, buffer, size);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::write(PCCHAR str)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, PCBYTE, SIZE>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::write, str);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::write(PCCHAR buffer, SIZE size)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, PCBYTE, SIZE>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::write, buffer, size);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(FLASH_STRING flashStr)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, FLASH_STRING>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, flashStr);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(CONST String & str)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, CONST String &>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, str);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(PCCHAR str)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, PCCHAR>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, str);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(CHAR value)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, CHAR>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(BYTE value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, BYTE, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(INT value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, INT, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(UINT value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, UINT, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(LONG value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, LONG, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(DWORD value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, DWORD, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(DOUBLE value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, DOUBLE, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::print(CONST Printable & printable)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, CONST Printable &>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::print, printable);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(FLASH_STRING flashStr)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, FLASH_STRING>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, flashStr);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(CONST String & str)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, CONST String &>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, str);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(PCCHAR str)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, PCCHAR>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, str);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(CHAR value)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, CHAR>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(BYTE value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, BYTE, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(INT value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, INT, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(UINT value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, UINT, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(LONG value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, LONG, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(DWORD value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, DWORD, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(DOUBLE value, INT base)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, DOUBLE, INT>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, value, base);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println(CONST Printable & printable)
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE, CONST Printable &>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println, printable);

	return __ResultFromCallResults(results, _RendererCount);
}

SIZE UiDisplayController::println()
{
	SIZE results[_RendererCount];

	PtrCallAll<BYTE, Print, SIZE>(_RendererCount,
		(Print **)_Renderers, results, &IUiRenderer::println);

	return __ResultFromCallResults(results, _RendererCount);
}

INT UiDisplayController::printf(PCCHAR format, ...)
{
	INT results[_RendererCount];

	va_list args;
	va_start(args, 0);
	va_end(args);

	for (BYTE i = 0; i < _RendererCount; i++)
		results[i] = _Renderers[i]->printf(format, args);

	return __ResultFromCallResults(results, _RendererCount);
}

INT UiDisplayController::printf(FLASH_STRING format, ...)
{
	INT results[_RendererCount];

	va_list args;
	va_start(args, 0);
	va_end(args);

	for (BYTE i = 0; i < _RendererCount; i++)
		results[i] = _Renderers[i]->printf(format, args);

	return __ResultFromCallResults(results, _RendererCount);
}
*/


// [IUiRenderer] OVERRIDES

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

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
