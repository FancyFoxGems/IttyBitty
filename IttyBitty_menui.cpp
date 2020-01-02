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

MenUI::MenUI(FLASH_STRING mainTitle, CBYTE initMenuCapacity)
	: MenUI(0, NULL, 0, NULL, mainTitle, initMenuCapacity) { }

MenUI::MenUI(CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources, CBYTE rendererCount, PPIUIRENDERER renderers, FLASH_STRING mainTitle, CBYTE initMenuCapacity)
	: Menu(mainTitle, this, initMenuCapacity),
		_DisposeNavigationPtr(TRUE),
		_NavigationPtr(new UiNavigationController(*this, inputSourceCount, inputSources)),
		_DisplayPtr(new UiDisplayController(rendererCount, renderers)) { }

MenUI::~MenUI()
{
	this->DisposeNavigationPtr();
	this->DisposeDisplayPtr();
}


// PROTECTED DISPOSAL METHODS

VOID MenUI::DisposeNavigationPtr()
{
	if (_NavigationPtr && _DisposeNavigationPtr)
	{
		delete _NavigationPtr;
		_NavigationPtr = NULL;

		_DisposeNavigationPtr = FALSE;
	}
}

VOID MenUI::DisposeDisplayPtr()
{
	if (_DisplayPtr && _DisposeDisplayPtr)
	{
		delete _DisplayPtr;
		_DisplayPtr = NULL;

		_DisposeDisplayPtr = FALSE;
	}
}


// ACCESSORS/MUTATORS

PUICALLBACK MenUI::GetIdleHandler() const
{
	return _OnIdleHandler;
}

VOID MenUI::SetIdleHandler(PUICALLBACK onIdleHandler)
{
	_OnIdleHandler = onIdleHandler;
}

RUINAVIGATIONCONTROLLER MenUI::GetNavigationController() const
{
	return *_NavigationPtr;
}

VOID MenUI::SetNavigationController(RUINAVIGATIONCONTROLLER navigation)
{
	this->DisposeNavigationPtr();

	_NavigationPtr = &navigation;
}

RUIDISPLAYCONTROLLER MenUI::GetDisplayController() const
{
	return *_DisplayPtr;
}

VOID MenUI::SetDisplayController(RUIDISPLAYCONTROLLER display)
{
	this->DisposeDisplayPtr();

	_DisplayPtr = &display;
}



// USER METHODS

VOID MenUI::Initialize()
{
}

VOID MenUI::Update()
{
	_NavigationPtr->Poll();
}

VOID MenUI::ShowMessage(PCCHAR str, CWORD timeoutMS, CBOOL allowEscape, CBOOL anyActionReturns)
{
}

VOID MenUI::ShowMessage_P(FLASH_STRING flashStr, CWORD timeoutMS, CBOOL allowEscape, CBOOL anyActionReturns)
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

VOID MenUI::Value(RIUIINPUTVALUERESOLVER inputValueController, CBYTE token)
{
}


// [IUiNavigationController] IMPLEMENTATION

CBYTE MenUI::InputSourceCount() const
{
	return _NavigationPtr->InputSourceCount();
}

RCIUIINPUTSOURCE MenUI::InputSource(CBYTE i) const
{
	return _NavigationPtr->InputSource(i);
}

RIUIINPUTSOURCE MenUI::InputSource(CBYTE i)
{
	return _NavigationPtr->InputSource(i);
}

CBOOL MenUI::AddInputSource(RIUIINPUTSOURCE inputSource)
{
	return _NavigationPtr->AddInputSource(inputSource);
}

VOID MenUI::ClearInputSources()
{
	_NavigationPtr->ClearInputSources();
}

VOID MenUI::RemoveInputSource(CBYTE inputSourceIdx)
{
	_NavigationPtr->RemoveInputSource(inputSourceIdx);
}

VOID MenUI::RemoveInputSource(RIUIINPUTSOURCE inputSource)
{
	_NavigationPtr->RemoveInputSource(inputSource);
}

CBOOL MenUI::IsShiftOn() const
{
	return _NavigationPtr->IsShiftOn();
}

VOID MenUI::ToggleShift()
{
	_NavigationPtr->ToggleShift();
}
VOID MenUI::ShiftOn()
{
	_NavigationPtr->ShiftOn();
}

VOID MenUI::ShiftOff()
{
	_NavigationPtr->ShiftOff();
}

CBOOL MenUI::IsAltOn() const
{
	return _NavigationPtr->IsAltOn();
}

VOID MenUI::ToggleAlt()
{
	_NavigationPtr->ToggleAlt();
}

VOID MenUI::AltOn()
{
	_NavigationPtr->AltOn();
}

VOID MenUI::AltOff()
{
	_NavigationPtr->AltOff();
}

VOID MenUI::FireAction(CUIACTION action, CUIACTIONSTATE state)
{
	return _NavigationPtr->FireAction(action, state);
}

VOID MenUI::SendValue(PCCHAR buffer)
{
	_NavigationPtr->SendValue(buffer);
}


// [IUiInputValueResolver] IMPLEMENTATION

CBYTE MenUI::ValueEntryCount() const
{
	return _NavigationPtr->ValueEntryCount();
}

VOID MenUI::RemoveValueEntry(CBYTE token)
{
	_NavigationPtr->RemoveValueEntry(token);
}

VOID MenUI::ClearValueEntriesOlderThan(CDWORD expirationMS)
{
	_NavigationPtr->ClearValueEntriesOlderThan(expirationMS);
}

VOID MenUI::ClearValueEntries()
{
	_NavigationPtr->ClearValueEntries();
}

CBOOL MenUI::ReadValueAsBool(CBYTE token, CUIBOOLVALUEFLAGS flags)
{
	return _NavigationPtr->ReadValueAsBool(token, flags);
}

CBYTE MenUI::ReadValueAsByte(CBYTE token)
{
	return _NavigationPtr->ReadValueAsByte(token);
}

CCHAR MenUI::ReadValueAsChar(CBYTE token)
{
	return _NavigationPtr->ReadValueAsChar(token);
}

CWCHAR MenUI::ReadValueAsWChar(CBYTE token)
{
	return _NavigationPtr->ReadValueAsWChar(token);
}

CWORD MenUI::ReadValueAsWord(CBYTE token)
{
	return _NavigationPtr->ReadValueAsWord(token);
}

CSHORT MenUI::ReadValueAsShort(CBYTE token)
{
	return _NavigationPtr->ReadValueAsShort(token);
}

CDWORD MenUI::ReadValueAsDWord(CBYTE token)
{
	return _NavigationPtr->ReadValueAsDWord(token);
}

CLONG MenUI::ReadValueAsLong(CBYTE token)
{
	return _NavigationPtr->ReadValueAsLong(token);
}

PCBYTE MenUI::ReadValueAsBinary(CBYTE token)
{
	return _NavigationPtr->ReadValueAsBinary(token);
}

PCCHAR MenUI::ReadValueAsString(CBYTE token)
{
	return _NavigationPtr->ReadValueAsString(token);
}


// [IUiInputSource] IMPLEMENTATION

CBOOL MenUI::IsAsynchronous() const
{
	return _NavigationPtr->IsAsynchronous();
}

VOID MenUI::Poll()
{
	_NavigationPtr->Poll();
}


// [IUiDisplayController] IMPLEMENTATION

CBYTE MenUI::RendererCount() const
{
	return _DisplayPtr->RendererCount();
}

RCIUIRENDERER MenUI::Renderer(CBYTE i) const
{
	return _DisplayPtr->Renderer(i);
}

RIUIRENDERER MenUI::Renderer(CBYTE i)
{
	return _DisplayPtr->Renderer(i);
}

CBOOL MenUI::AddRenderer(RIUIRENDERER renderer)
{
	return _DisplayPtr->AddRenderer(renderer);
}

VOID MenUI::ClearRenderers()
{
	_DisplayPtr->ClearRenderers();
}

VOID MenUI::RemoveRenderer(CBYTE rendererIdx)
{
	_DisplayPtr->RemoveRenderer(rendererIdx);
}

VOID MenUI::RemoveRenderer(RIUIRENDERER renderer)
{
	_DisplayPtr->RemoveRenderer(renderer);
}


// [IUiRenderer] IMPLEMENTATION

CBYTE MenUI::Cols() const
{
	return _DisplayPtr->Cols();
}

CBYTE MenUI::Rows() const
{
	return _DisplayPtr->Rows();
}

CBYTE MenUI::CursorCol() const
{
	return _DisplayPtr->CursorCol();
}

CBYTE MenUI::CursorRow() const
{
	return _DisplayPtr->CursorRow();
}

CBOOL MenUI::IsLineWrapEnabled() const
{
	return _DisplayPtr->IsLineWrapEnabled();
}

VOID MenUI::SetLineWrapEnabled(CBOOL lineWrapEnabled)
{
	_DisplayPtr->SetLineWrapEnabled(lineWrapEnabled);
}

VOID MenUI::CursorOn()
{
	_DisplayPtr->CursorOn();
}

VOID MenUI::CursorOff()
{
	_DisplayPtr->CursorOn();
}

VOID MenUI::CursorBlinkOn()
{
	_DisplayPtr->CursorOn();
}

VOID MenUI::CursorBlinkOff()
{
	_DisplayPtr->CursorOn();
}

CBOOL MenUI::Available()
{
	return _DisplayPtr->Available();
}

VOID MenUI::Flush()
{
	_DisplayPtr->Flush();
}

VOID MenUI::Clear()
{
	_DisplayPtr->Clear();
}

VOID MenUI::ClearCol(BYTE col)
{
	_DisplayPtr->ClearCol(col);
}

VOID MenUI::ClearRow(BYTE row)
{
	_DisplayPtr->ClearRow(row);
}

VOID MenUI::ClearArea(BYTE col, BYTE row, BYTE cols, BYTE rows)
{
	_DisplayPtr->ClearArea(col, row, cols, rows);
}

VOID MenUI::ScrollLeft()
{
	_DisplayPtr->ScrollLeft();
}

VOID MenUI::ScrollRight()
{
	_DisplayPtr->ScrollRight();
}

VOID MenUI::Home()
{
	_DisplayPtr->Home();
}

VOID MenUI::CursorPrev()
{
	_DisplayPtr->CursorPrev();
}

VOID MenUI::CursorNext()
{
	_DisplayPtr->CursorNext();
}

VOID MenUI::MoveCursor(BYTE col, BYTE row)
{
	_DisplayPtr->MoveCursor(col, row);
}

VOID MenUI::LoadCustomChar(BYTE charIndex, PCBYTE charData)
{
	_DisplayPtr->LoadCustomChar(charIndex, charData);
}

VOID MenUI::LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
{
	_DisplayPtr->LoadCustomChar_P(charIndex, charDataAddr);
}

CBYTE MenUI::WriteAt(BYTE value, BYTE col, BYTE row)
{
	return _DisplayPtr->WriteAt(value, col, row);
}

CBYTE MenUI::UpdateAt(BYTE value, BYTE col, BYTE row)
{
	return _DisplayPtr->UpdateAt(value, col, row);
}

CBYTE MenUI::PrintString(PCCHAR str, BYTE col, BYTE row)
{
	return _DisplayPtr->PrintString(str, col, row);
}

CBYTE MenUI::UpdateString(PCCHAR str, BYTE col, BYTE row)
{
	return _DisplayPtr->UpdateString(str, col, row);
}

CBYTE MenUI::PrintString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return _DisplayPtr->PrintString_P(flashStr, col, row);
}

CBYTE MenUI::UpdateString_P(FLASH_STRING flashStr, BYTE col, BYTE row)
{
	return _DisplayPtr->UpdateString_P(flashStr, col, row);
}

CBYTE MenUI::PrintStyledLine(PCCHAR str, BYTE col, BYTE row, BYTE cols)
{
	return _DisplayPtr->PrintStyledLine(str, col, row, cols);
}

CBYTE MenUI::PrintStyledLine_P(FLASH_STRING flashStr, BYTE col, BYTE row, BYTE cols)
{
	return _DisplayPtr->PrintStyledLine_P(flashStr, col, row, cols);
}

CBYTE MenUI::PrintGlyph(BYTE glyph, BYTE col, BYTE row)
{
	return _DisplayPtr->PrintGlyph(glyph, col, row);
}

VOID MenUI::BeginListItem(BYTE itemNumber)
{
	return _DisplayPtr->BeginListItem(itemNumber);
}

VOID MenUI::EndListItem(CCHAR inputTag)
{
	return _DisplayPtr->EndListItem(inputTag);
}


#ifndef NO_ITTYBITTY_LCD_EXTENSIONS

VOID MenUI::DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
{
	_DisplayPtr->DrawScrollBar(percentage, options);
}

VOID MenUI::DrawGraph(BYTE startCol, BYTE row,
	BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
{
	_DisplayPtr->DrawGraph(startCol, row, widthChars, percentage, options);
}

VOID MenUI::DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
	BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw)
{
	_DisplayPtr->DrawSlider(startCol, row, widthChars, percentage, options, redraw);
}

#endif	// #ifndef NO_ITTYBITTY_LCD_EXTENSIONS


// [Print] IMPLEMENTATION

SIZE MenUI::write(BYTE value)
{
	return _DisplayPtr->write(value);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
