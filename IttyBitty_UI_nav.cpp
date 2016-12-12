/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_UI_nav.h"

using namespace IttyBitty;


#pragma region [UiInputListenerBase] IMPLEMENTATION

// CONSTRUCTOR

UiInputListenerBase::UiInputListenerBase(PIUINAVIGATIONLISTENER navigation) : _Navigation(navigation) { }


// [IUiListener] IMPLEMENTATION

CBOOL UiInputListenerBase::IsAsynchronous() const { return TRUE; }

VOID UiInputListenerBase::Poll() { }

#pragma endregion


#pragma region [UiNavigationController] IMPLEMENTATION

UiNavigationController::UiNavigationController(CBYTE listenerCount, PPIUIINPUTLISTENER listeners)
	: _ListenerCount(listenerCount), _Listeners(listeners) { }

UiNavigationController::UiNavigationController(RIUIINPUTLISTENER listener) : _ListenerCount(1)
{
	_Listeners = new PIUIINPUTLISTENER[1];
	_Listeners[0] = &listener;
}

UiNavigationController::~UiNavigationController()
{
	if (!_Listeners)
		return;

	for (BYTE i = 0; i < _ListenerCount; i++)
	{
		if (_Listeners[i])
		{
			delete _Listeners[i];
			_Listeners[i] = NULL;
		}
	}

	delete _Listeners;
	_Listeners = NULL;

	_ListenerCount = 0;
}


// OPERATORS

PCIUIINPUTLISTENER UiNavigationController::operator[](CBYTE i) const
{
	if (!_Listeners)
		return NULL;

	return _Listeners[i];
}

PIUIINPUTLISTENER UiNavigationController::operator[](CBYTE i)
{
	if (!_Listeners)
		return NULL;

	return _Listeners[i];
}


// ACCESSORS

CBYTE UiNavigationController::ListenerCount() const
{
	return _ListenerCount;
}

RCIUIINPUTLISTENER UiNavigationController::Listener(CBYTE i) const
{
	return *this->operator[](i);
}

RIUIINPUTLISTENER UiNavigationController::Listener(CBYTE i)
{
	return *this->operator[](i);
}


// [IUiListener] IMPLEMENTATION

VOID UiNavigationController::Poll()
{
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

VOID UiNavigationController::Up()
{
}
VOID UiNavigationController::Down()
{
}

VOID UiNavigationController::Left()
{
}

VOID UiNavigationController::Right()
{
}

VOID UiNavigationController::Return()
{
}

VOID UiNavigationController::Select()
{
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
