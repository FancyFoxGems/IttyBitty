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
using namespace IttyBitty::MUI;


#pragma region [UiInputSourceBase] IMPLEMENTATION

// CONSTRUCTOR

UiInputSourceBase::UiInputSourceBase(RIUINAVIGATIONCONTROLLER navigation) : _Navigation(navigation) { }


// [IUiListener] (NON-)IMPLEMENTATION

CBOOL UiInputSourceBase::IsAsynchronous() const { return TRUE; }

VOID UiInputSourceBase::Poll() { }

#pragma endregion


#pragma region [UiNavigationController] IMPLEMENTATION

// CONSTRUCTOR/DESTRUCTOR

UiNavigationController::UiNavigationController(RIUINAVIGATIONLISTENER navListener,
		CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources)
	: _NavListener(navListener), _InputSourceCount(inputSourceCount), _InputSources(inputSources)
{
	if (!_InputSources)
		_Dispose = TRUE;
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


// [IUiNavigationController] IMPLEMENTATION

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

CBOOL UiNavigationController::AddInputSource(RIUIINPUTSOURCE inputSource)
{
	if (!_Dispose)
		return FALSE;

	PPIUIINPUTSOURCE newInputSources = new PIUIINPUTSOURCE[++_InputSourceCount];

	for (BYTE i = 0; i < _InputSourceCount - 1; i++)
		newInputSources[i] = _InputSources[i];

	newInputSources[_InputSourceCount - 1] = &inputSource;

	if (_InputSources)
		delete[] _InputSources;

	_InputSources = newInputSources;

	return TRUE;
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


// [IUiNavigationListener] IMPLEMENTATION

CBOOL UiNavigationController::IsShiftOn() const
{
	return _ShiftOn;
}

CBOOL UiNavigationController::IsAltOn() const
{
	return _AltOn;
}

VOID UiNavigationController::Up(CUIACTIONSTATE state)
{
	UIACTIONSTATE resultState = this->UpdateState(ACTION_UP, state);

	if (resultState != INACTION)
		_NavListener.Up(this->ApplyShiftAltFlags(resultState));
}
VOID UiNavigationController::Down(CUIACTIONSTATE state)
{
	UIACTIONSTATE resultState = this->UpdateState(ACTION_DOWN, state);

	if (resultState != INACTION)
		_NavListener.Down(this->ApplyShiftAltFlags(resultState));
}

VOID UiNavigationController::Left(CUIACTIONSTATE state)
{
	UIACTIONSTATE resultState = this->UpdateState(ACTION_LEFT, state);

	if (resultState != INACTION)
		_NavListener.Left(this->ApplyShiftAltFlags(resultState));
}

VOID UiNavigationController::Right(CUIACTIONSTATE state)
{
	UIACTIONSTATE resultState = this->UpdateState(ACTION_RIGHT, state);

	if (resultState != INACTION)
		_NavListener.Right(this->ApplyShiftAltFlags(resultState));
}

VOID UiNavigationController::Return(CUIACTIONSTATE state)
{
	UIACTIONSTATE resultState = this->UpdateState(ACTION_RETURN, state);

	if (resultState != INACTION)
		_NavListener.Return(this->ApplyShiftAltFlags(resultState));
}

VOID UiNavigationController::Select(CUIACTIONSTATE state)
{
	UIACTIONSTATE resultState = this->UpdateState(ACTION_SELECT, state);

	if (resultState != INACTION)
		_NavListener.Select(this->ApplyShiftAltFlags(resultState));
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

	UIACTIONSTATE resultState = INACTION;

	for (BYTE actionType = 0; actionType < MENUI_NUM_STATEFUL_ACTIONS; actionType++)
	{
		resultState = this->UpdateState(static_cast<CUIACTIONTYPE>(actionType), INACTION);

		if (resultState != INACTION)
		{
			switch (actionType)
			{
			case ACTION_UP:
				this->Up(this->ApplyShiftAltFlags(resultState));
				break;

			case ACTION_DOWN:
				this->Down(this->ApplyShiftAltFlags(resultState));
				break;

			case ACTION_LEFT:
				this->Left(this->ApplyShiftAltFlags(resultState));
				break;

			case ACTION_RIGHT:
				this->Right(this->ApplyShiftAltFlags(resultState));
				break;

			case ACTION_SELECT:
				this->Select(this->ApplyShiftAltFlags(resultState));
				break;

			case ACTION_RETURN:
				this->Return(this->ApplyShiftAltFlags(resultState));
				break;
			}
		}
	}
}


// PROTECTED MEMBER FUNCTION DEFINITIONS

CUIACTIONSTATE UiNavigationController::UpdateState(CUIACTIONTYPE actionType, CUIACTIONSTATE newState)
{
	RSTATEENTRY entry = _PrevStates[actionType];
	LONG now = millis();

	if (newState != INACTION)
	{
		for (BYTE i = 0; i < MENUI_NUM_STATEFUL_ACTIONS; i++)
		{
			if (i == actionType)
				continue;

			if (_PrevStates[i].State == HELD)
				_PrevStates[i].Timestamp = now;
			else if (_PrevStates[i].State != PRESSED)
				_PrevStates[i].State = INACTION;
		}
	}

	switch (newState)
	{
	case INACTION:

		if (entry.State == PRESSED && entry.Timestamp - now >= Options.Input.HoldThresholdMS)
		{
			entry.State = HELD;
			entry.Timestamp = now;

			return HELD;
		}

		if (entry.State == HELD && entry.Timestamp - now >= Options.Input.HoldRepeatMS)
		{
			entry.Timestamp = now;

			return CLICK;
		}

		return INACTION;


	case PRESSED:

		if (entry.State == PRESSED && entry.Timestamp - now >= Options.Input.HoldThresholdMS)
		{
			entry.State = HELD;
			entry.Timestamp = now;

			return HELD;
		}

		if (entry.State == CLICK || entry.State == DOUBLE_CLICK)
			return PRESSED;

		if (entry.State == HELD)
			return HELD;

		entry.State = PRESSED;
		entry.Timestamp = now;

		return entry.State;


	case RELEASED:

		if (entry.State == PRESSED)
		{
			entry.State = CLICK;
			entry.Timestamp = now;

			return CLICK;
		}

		if ((entry.State == CLICK || entry.State == DOUBLE_CLICK)
			&& now - entry.Timestamp <= Options.Input.DblClickThresholdMS)
		{
			entry.State = CLICK;
			entry.Timestamp = now;

			return DOUBLE_CLICK;
		}

		entry.State = INACTION;

		return RELEASED;


	case CLICK:

		if ((entry.State == RELEASED || entry.State == CLICK || entry.State == DOUBLE_CLICK)
			&& now - entry.Timestamp <= Options.Input.DblClickThresholdMS)
		{
			entry.State = CLICK;
			entry.Timestamp = now;

			return DOUBLE_CLICK;
		}

		if (entry.State != PRESSED)
			entry.Timestamp = now;

		entry.State = CLICK;

		return CLICK;


	case DOUBLE_CLICK:

		entry.State = CLICK;
		entry.Timestamp = now;

		return DOUBLE_CLICK;


	case HELD:

		if (entry.State != HELD)
		{
			entry.State = HELD;
			entry.Timestamp = now;
		}

		return HELD;


	default:

		return newState;
	}

	return newState;
}

CUIACTIONSTATE UiNavigationController::ApplyShiftAltFlags(CUIACTIONSTATE state)
{
	return static_cast<CUIACTIONSTATE>(WITH_BITS(state, (_ShiftOn ? SHIFT_ON : 0x0) OR (_AltOn ? ALT_ON : 0x0)));
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
