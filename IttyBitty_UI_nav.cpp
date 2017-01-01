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
#include "IttyBitty_UI_nav.h"

using namespace IttyBitty;


#pragma region [UiInputSourceBase] IMPLEMENTATION

// CONSTRUCTOR

UiInputSourceBase::UiInputSourceBase(PIUINAVIGATIONLISTENER navListener) : _NavListener(navListener) { }


// [IUiListener] (NON-)IMPLEMENTATION

CBOOL UiInputSourceBase::IsAsynchronous() const { return TRUE; }

VOID UiInputSourceBase::Poll() { }

#pragma endregion


#pragma region [UiNavigationController] IMPLEMENTATION

UiNavigationController::UiNavigationController(RIUINAVIGATIONLISTENER navListener,
	CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources)
	 : _Dispose(FALSE), _NavListener(navListener), _InputSourceCount(inputSourceCount), _InputSources(inputSources) { }

UiNavigationController::UiNavigationController(RIUINAVIGATIONLISTENER navListener, RIUIINPUTSOURCE inputSource)
	: _Dispose(TRUE), _NavListener(navListener), _InputSourceCount(1)
{
	_InputSources = new PIUIINPUTSOURCE[1];
	_InputSources[0] = &inputSource;
}

UiNavigationController::~UiNavigationController()
{
	this->Dispose();
}


// PROTECTED DISPOSAL METHOD

VOID UiNavigationController::Dispose()
{
	if (!_InputSources)
		return;

	if (_Dispose)
	{
		for (BYTE i = 0; i < _InputSourceCount; i++)
		{
			if (_InputSources[i])
			{
				delete _InputSources[i];
				_InputSources[i] = NULL;
			}
		}
	}

	delete _InputSources;
	_InputSources = NULL;
}


// OPERATORS

PCIUIINPUTSOURCE UiNavigationController::operator[](CBYTE i) const
{
	if (!_InputSources)
		return NULL;

	return _InputSources[i];
}

PIUIINPUTSOURCE UiNavigationController::operator[](CBYTE i)
{
	if (!_InputSources)
		return NULL;

	return _InputSources[i];
}


// ACCESSORS/MUTATORS

CBYTE UiNavigationController::InputSourceCount() const
{
	return _InputSourceCount;
}

RCIUIINPUTSOURCE UiNavigationController::InputSource(CBYTE i) const
{
	return *this->operator[](i);
}

RIUIINPUTSOURCE UiNavigationController::InputSource(CBYTE i)
{
	return *this->operator[](i);
}

RIUIINPUTSOURCE UiNavigationController::AddInputSource(RIUIINPUTSOURCE inputSource)
{
	PPIUIINPUTSOURCE newInputSources = new PIUIINPUTSOURCE[++_InputSourceCount];

	for (BYTE i = 0; i < _InputSourceCount - 1; i++)
		newInputSources[i] = _InputSources[i];

	newInputSources[_InputSourceCount - 1] = &inputSource;

	if (_InputSources)
		delete[] _InputSources;

	_InputSources = newInputSources;

	return inputSource;
}

VOID UiNavigationController::RemoveInputSource(CBYTE inputSourceIdx)
{
	PPIUIINPUTSOURCE newInputSources = new PIUIINPUTSOURCE[--_InputSourceCount];
	BYTE currIdx = 0;

	for (BYTE i = 0; i < _InputSourceCount; i++)
	{
		if (currIdx != inputSourceIdx)
			newInputSources[currIdx++] = _InputSources[i];
	}

	if (_InputSources)
		delete[] _InputSources;

	_InputSources = newInputSources;
}

VOID UiNavigationController::RemoveInputSource(RIUIINPUTSOURCE inputSource)
{
	PPIUIINPUTSOURCE newInputSources = new PIUIINPUTSOURCE[--_InputSourceCount];
	BYTE currIdx = 0;

	for (BYTE i = 0; i < _InputSourceCount; i++)
	{
		if (_InputSources[i] != &inputSource)
			newInputSources[currIdx++] = _InputSources[i];
	}

	if (_InputSources)
		delete[] _InputSources;

	_InputSources = newInputSources;
}


// [IUiInputSource] IMPLEMENTATION

CBOOL UiNavigationController::IsAsynchronous() const
{
	return PtrAll(_InputSourceCount, _InputSources, &IUiInputSource::IsAsynchronous);
}

VOID UiNavigationController::Poll()
{
	for (BYTE i = 0; i < _InputSourceCount; i++)
	{
		if (!_InputSources[i]->IsAsynchronous())
			_InputSources[i]->Poll();
	}
}


// [IUiNavigationListener] IMPLEMENTATION

CBOOL UiNavigationController::IsShiftOn() const
{
	return _ShiftOn;
}

VOID UiNavigationController::ToggleShift()
{
	_ShiftOn = NOT _ShiftOn;
}

VOID UiNavigationController::ShiftOn()
{
	_ShiftOn = TRUE;
}

VOID UiNavigationController::ShiftOff()
{
	_ShiftOn = FALSE;
}

CBOOL UiNavigationController::IsAltOn() const
{
	return _AltOn;
}

VOID UiNavigationController::ToggleAlt()
{
	_AltOn = NOT _AltOn;
}

VOID UiNavigationController::AltOn()
{
	_AltOn = TRUE;
}

VOID UiNavigationController::AltOff()
{
	_AltOn = FALSE;
}

VOID UiNavigationController::Up(CUIACTIONSTATE state)
{
	_NavListener.Up(state);
}
VOID UiNavigationController::Down(CUIACTIONSTATE state)
{
	_NavListener.Down(state);
}

VOID UiNavigationController::Left(CUIACTIONSTATE state)
{
	_NavListener.Left(state);
}

VOID UiNavigationController::Right(CUIACTIONSTATE state)
{
	_NavListener.Up(state);
}

VOID UiNavigationController::Return(CUIACTIONSTATE state)
{
	_NavListener.Return(state);
}

VOID UiNavigationController::Select(CUIACTIONSTATE state)
{
	_NavListener.Select(state);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
