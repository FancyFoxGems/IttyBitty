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

// ACCESSORS/MUTATORS

VOID UiNavigationController::ToggleShift()
{
}

VOID UiNavigationController::ShiftOn()
{
}

VOID UiNavigationController::ShiftOff()
{
}

VOID UiNavigationController::ToggleAlt()
{
}

VOID UiNavigationController::AltOn()
{
}

VOID UiNavigationController::AltOff()
{
}


// [IUiListener] IMPLEMENTATION

VOID UiNavigationController::Poll()
{
}


// [IUiNavigationListener] IMPLEMENTATION

VOID UiNavigationController::IsShiftOn() const
{
}

VOID UiNavigationController::IsAltOn() const
{
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
