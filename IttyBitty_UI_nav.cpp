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

UiNavigationController::UiNavigationController(PIUINAVIGATIONLISTENER navListener,
	CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources)
	 : _NavListener(navListener), _InputSourceCount(inputSourceCount), _InputSources(inputSources) { }

UiNavigationController::UiNavigationController(PIUINAVIGATIONLISTENER navListener,
	RIUIINPUTSOURCE inputSource)  : _NavListener(navListener), _InputSourceCount(1)
{
	_InputSources = new PIUIINPUTSOURCE[1];
	_InputSources[0] = &inputSource;
}

UiNavigationController::~UiNavigationController()
{
	if (_NavListener)
	{
		delete _NavListener;
		_NavListener = NULL;
	}

	if (_InputSources)
	{
		for (BYTE i = 0; i < _InputSourceCount; i++)
		{
			if (_InputSources[i])
			{
				delete _InputSources[i];
				_InputSources[i] = NULL;
			}
		}

		delete _InputSources;
		_InputSources = NULL;

		_InputSourceCount = 0;
	}
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


// ACCESSORS

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


// [IUiInputSource] IMPLEMENTATION

VOID UiNavigationController::Poll()
{
	PtrApplyAll(_InputSourceCount, _InputSources, &IUiInputSource::Poll);
}


// [IUiNavigationInputSource] IMPLEMENTATION

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
	_NavListener->Up(state);
}
VOID UiNavigationController::Down(CUIACTIONSTATE state)
{
	_NavListener->Down(state);
}

VOID UiNavigationController::Left(CUIACTIONSTATE state)
{
	_NavListener->Left(state);
}

VOID UiNavigationController::Right(CUIACTIONSTATE state)
{
	_NavListener->Up(state);
}

VOID UiNavigationController::Return(CUIACTIONSTATE state)
{
	_NavListener->Return(state);
}

VOID UiNavigationController::Select(CUIACTIONSTATE state)
{
	_NavListener->Select(state);
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
