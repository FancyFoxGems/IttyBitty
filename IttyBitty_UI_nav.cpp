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


#pragma region [UiInputSource] IMPLEMENTATION

// CONSTRUCTOR

UiInputSource::UiInputSource(RIUINAVIGATIONCONTROLLER navigation) : _Navigation(navigation) { }


// [IUiInputSource] (NON-)IMPLEMENTATION

CBOOL UiInputSource::IsAsynchronous() const { return TRUE; }

VOID UiInputSource::Poll() { }

#pragma endregion


#pragma region [UiNavigationController] IMPLEMENTATION

// CONSTRUCTOR/DESTRUCTOR

UiNavigationController::UiNavigationController(RIUINAVIGATIONLISTENER navListener, CDWORD valueEntryExpirationMs, 
		CBOOL removeValueEntriesUponReading, CBYTE inputSourceCount, PPIUIINPUTSOURCE inputSources)
	: _NavListener(navListener), _ValueEntryExpirationMs(valueEntryExpirationMs), 
		_RemoveValueEntriesUponReading(removeValueEntriesUponReading), _InputSourceCount(inputSourceCount), _InputSources(inputSources)
{
	if (!_InputSources)
		_DisposeInputSources = TRUE;
}

UiNavigationController::~UiNavigationController()
{
	this->Dispose();
}


// PROTECTED DISPOSAL METHOD

VOID UiNavigationController::Dispose()
{
	this->ClearValueEntries();

	if (!_InputSources)
		return;

	if (_DisposeInputSources)
	{
		for (BYTE i = 0; i < _InputSourceCount; i++)
		{
			if (!_InputSources[i])
				continue;

			delete _InputSources[i];
			_InputSources[i] = NULL;
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
	if (!_DisposeInputSources)
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

VOID UiNavigationController::FireAction(CUIACTION action, CUIACTIONSTATE state)
{
	CUIACTIONTYPE actionType = UiActionToActionType(action);

	switch (actionType)
	{
	case ACTION_UP:
		this->Up(state);
		break;

	case ACTION_DOWN:
		this->Down(state);
		break;

	case ACTION_LEFT:
		this->Left(state);
		break;

	case ACTION_RIGHT:
		this->Right(state);
		break;

	case ACTION_SELECT:
		this->Select(state);
		break;

	case ACTION_RETURN:
		this->Return(state);
		break;

	case ACTION_SHIFT:
		this->ToggleShift();
		break;

	case ACTION_ALT:
		this->ToggleAlt();
		break;
	}
}

VOID UiNavigationController::SendValue(PCCHAR buffer)
{
	PVALUEENTRY newValueEntry = new __ValueEntry;
	newValueEntry->Timestamp = millis();
	newValueEntry->Buffer = buffer;

	PVALUEENTRY findEntry = NULL;
	do
	{
		this->FindValueEntry(_NextValueEntryToken++, &findEntry);
	}
	while (findEntry != NULL);

	newValueEntry->Token = _NextValueEntryToken - 1;
	
	PPVALUEENTRY newValueEntries = new PVALUEENTRY[_ValueEntryCount + 1];
	newValueEntries[_ValueEntryCount] = newValueEntry;

	for (BYTE i = 0; i < _ValueEntryCount; i++)
	{
		newValueEntries[i] = _ValueEntries[i];
	}
	
	delete[] _ValueEntries;
	_ValueEntries = newValueEntries;

	++_ValueEntryCount;

	this->Value(newValueEntry->Token, *this);
}


// [IUiNavigationListener] IMPLEMENTATION

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

VOID UiNavigationController::Value(CBYTE token, RIUIINPUTVALUECONTROLLER inputValueController)
{
	_NavListener.Value(token, inputValueController);
}


// [IUiInputValueController] IMPLEMENTATION

CBYTE UiNavigationController::ValueEntryCount() const
{
	return _ValueEntryCount;
}

VOID UiNavigationController::RemoveValueEntry(CBYTE token)
{
	PVALUEENTRY valueEntry = NULL;
	BYTE index = this->FindValueEntry(token, &valueEntry);

	if (!valueEntry)
		return;

	this->DeleteValueEntry(index);
	this->CompressValueEntries();
}

VOID UiNavigationController::ClearValueEntriesOlderThan(CDWORD expirationMs)
{
	DWORD now = millis();
	BOOL anyDeleted = FALSE;

	for (BYTE i = 0; i < _ValueEntryCount; i++)
	{
		if (now - _ValueEntries[i]->Timestamp >= expirationMs)
		{
			this->DeleteValueEntry(i);
			anyDeleted = TRUE;
		}
	}

	if (anyDeleted)
		this->CompressValueEntries();
}

VOID UiNavigationController::ClearValueEntries()
{
	if (!_ValueEntries)
		return;

	for (BYTE i = 0; i < _ValueEntryCount; i++)
	{
		if (!_ValueEntries[i])
			continue;

		this->DeleteValueEntry(i);
	}

	delete[] _ValueEntries;
	_ValueEntries = NULL;

	_ValueEntryCount = 0;
	_NextValueEntryToken = 0;
}

CBOOL UiNavigationController::ReadValueAsBool(CBYTE token, CUIBOOLVALUEFLAGS flags)
{
	CCHAR charValue = this->ReadValueAsChar(token);

	if (!charValue)
		return FALSE;

	if (WITH_BITS(flags, BOOL_VALUE_NONEMPTY))
		return TRUE;

	if (WITH_BITS(flags, BOOL_VALUE_0_1))
	{
		if (charValue == '0')
			return FALSE;
		if (charValue == '1')
			return TRUE;
	}

	if (WITH_BITS(flags, BOOL_VALUE_T_F))
	{
		if (charValue == 'f' || charValue == 'F')
			return FALSE;
		if (charValue == 't' || charValue == 'T')
			return TRUE;
	}

	if (WITH_BITS(flags, BOOL_VALUE_Y_N))
	{
		if (charValue == 'n' || charValue == 'N')
			return FALSE;
		if (charValue == 'y' || charValue == 'Y')
			return TRUE;
	}

	return FALSE;
}

CBYTE UiNavigationController::ReadValueAsByte(CBYTE token)
{
	return static_cast<CBYTE>(this->ReadValueAsShort(token));
}

CCHAR UiNavigationController::ReadValueAsChar(CBYTE token)
{
	PCCHAR buffer = this->ReadValueAsString(token);

	if (!buffer)
		return 0;

	CHAR value = buffer[0];

	if (_RemoveValueEntriesUponReading)
		delete buffer;

	return value;
}

CWCHAR UiNavigationController::ReadValueAsWChar(CBYTE token)
{
	PCCHAR buffer = this->ReadValueAsString(token);

	if (!buffer)
		return 0;

	WCHAR value = static_cast<CWCHAR>(*buffer);

	if (_RemoveValueEntriesUponReading)
		delete buffer;

	return value;
}

CWORD UiNavigationController::ReadValueAsWord(CBYTE token)
{
	return static_cast<CWORD>(this->ReadValueAsShort(token));
}

CSHORT UiNavigationController::ReadValueAsShort(CBYTE token)
{
	PCCHAR buffer = this->ReadValueAsString(token);

	if (!buffer)
		return 0;

	SHORT value = atoi(buffer);

	if (_RemoveValueEntriesUponReading)
		delete buffer;

	return value;
}

CDWORD UiNavigationController::ReadValueAsDWord(CBYTE token)
{
	return static_cast<CDWORD>(this->ReadValueAsLong(token));
}

CLONG UiNavigationController::ReadValueAsLong(CBYTE token)
{
	PCCHAR buffer = this->ReadValueAsString(token);

	if (!buffer)
		return 0;

	LONG value = atol(buffer);

	if (_RemoveValueEntriesUponReading)
		delete buffer;

	return value;
}

PCBYTE UiNavigationController::ReadValueAsBinary(CBYTE token)
{
	return (PCBYTE)this->ReadValueAsString(token);
}

PCCHAR UiNavigationController::ReadValueAsString(CBYTE token)
{
	return this->GetValueBuffer(token);
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

	if (_ValueEntryExpirationMs)
		this->ClearValueEntriesOlderThan(_ValueEntryExpirationMs);
}


// PROTECTED INTERFACE METHOD

CUIACTIONSTATE UiNavigationController::UpdateState(CUIACTIONTYPE actionType, CUIACTIONSTATE newState)
{
	RSTATEENTRY entry = _PrevStates[actionType];
	DWORD now = millis();

	if (newState != INACTION)
	{
		for (BYTE i = 0; i < MENUI_NUM_STATEFUL_ACTIONS; i++)
		{
			if (i == actionType)
				continue;

			if (_PrevStates[i].State != HELD && _PrevStates[i].State != PRESSED)
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


// PROTECTED HELPER MEMBER FUNCTIONS

CUIACTIONSTATE UiNavigationController::ApplyShiftAltFlags(CUIACTIONSTATE state)
{
	return static_cast<CUIACTIONSTATE>(WITH_BITS(state, (_ShiftOn ? SHIFT_ON : 0x0) OR(_AltOn ? ALT_ON : 0x0)));
}

CBYTE UiNavigationController::FindValueEntry(CBYTE token, PPVALUEENTRY resultPtr)
{
	if (!_ValueEntries)
	{
		*resultPtr = NULL;
		return 0;
	}

	for (BYTE i = 0; i < _ValueEntryCount; i++)
	{
		if (!_ValueEntries[i])
			continue;

		if (_ValueEntries[i]->Token == token)
		{
			*resultPtr = _ValueEntries[i];
			return i;
		}
	}

	*resultPtr = NULL;
	return 0;
}

VOID UiNavigationController::DeleteValueEntry(CBYTE index, CBOOL destroyBuffer)
{
	PVALUEENTRY valueEntry = _ValueEntries[index];
	
	if (destroyBuffer && valueEntry->Buffer)
	{
		delete valueEntry->Buffer;
		valueEntry->Buffer = NULL;
	}

	delete valueEntry;
	_ValueEntries[index] = NULL;
}

VOID UiNavigationController::CompressValueEntries()
{
	if (!_ValueEntries)
		return;

	BYTE removedValueEntries = 0;
	BYTE maxToken = 0;

	for (BYTE i = 0; i < _ValueEntryCount; i++)
	{
		if (!_ValueEntries[i])
			++removedValueEntries;
		else if (_ValueEntries[i]->Token > maxToken)
			maxToken = _ValueEntries[i]->Token;
	}

	BYTE newValueEntryCount = _ValueEntryCount - removedValueEntries;
	PPVALUEENTRY newValueEntries = new PVALUEENTRY[newValueEntryCount];
	BYTE j = 0;

	for (BYTE i = 0; i < _ValueEntryCount; i++)
	{
		if (_ValueEntries[i])
			newValueEntries[j++] = _ValueEntries[i];
	}

	delete[] _ValueEntries;
	_ValueEntries = newValueEntries;

	_ValueEntryCount = newValueEntryCount;
	_NextValueEntryToken = maxToken + 1;
}

PCCHAR UiNavigationController::GetValueBuffer(CBYTE token)
{
	PVALUEENTRY valueEntry = NULL;
	BYTE index = this->FindValueEntry(token, &valueEntry);

	if (!valueEntry)
		return NULL;

	PCCHAR buffer = valueEntry->Buffer;

	if (_RemoveValueEntriesUponReading)
	{
		this->DeleteValueEntry(index, FALSE);
		this->CompressValueEntries();
	}

	return buffer;
}

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
