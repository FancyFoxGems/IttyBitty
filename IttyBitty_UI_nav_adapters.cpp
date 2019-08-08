/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_MENUI)
	#define NO_ITTYBITTY_UI_NAV_ADAPTERS
#endif

#ifndef NO_ITTYBITTY_UI_NAV_ADAPTERS

#include "IttyBitty_UI_nav_adapters.h"

using namespace IttyBitty;


#pragma region [StreamUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

StreamUiInputSource::StreamUiInputSource(RIUINAVIGATIONCONTROLLER navigation, Stream & stream, CSTREAMUIINPUTOPTIONS options)
	: UiInputSourceBase(navigation),
	_Stream(stream), _Options(options) { }


// [IUiInputSource] IMPLEMENTATION

CBOOL StreamUiInputSource::IsAsynchronous() const
{
	return FALSE;
}

VOID StreamUiInputSource::Poll()
{
	if (!_Stream.available())
		return;

	PCHAR buffer = new char[UI_INPUT_VALUE_BUFFER_SIZE];
	BYTE bufferLength = 0;
	CHAR c = NULL_CHARACTER;

	while (_Stream.available())
	{
		c = _Stream.read();

		switch (c)
		{
		case CR:
			if (CHECK_BITS(_Options, EXCLUDE_CARRIAGE_RETURN))
				continue;
			break;

		case LF:
			if (CHECK_BITS(_Options, EXCLUDE_LINEFEED))
				continue;
			break;

		case SPACE:
			if (CHECK_BITS(_Options, EXCLUDE_SPACE))
				continue;
			break;

		case TAB:
			if (CHECK_BITS(_Options, EXCLUDE_TAB))
				continue;
			break;
		}

		buffer[bufferLength++] = c;
	}

	buffer[bufferLength] = NULL_CHARACTER;

	_Navigation.SendValue(buffer);
}

#pragma endregion


#pragma region [SimpleUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

SimpleUiInputSource::SimpleUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CUIACTION action)
	: UiInputSourceBase(navigation),
	_Action(action) { }


// [IUiInputSource] IMPLEMENTATION

CBOOL SimpleUiInputSource::IsAsynchronous() const
{
	return TRUE;
}

VOID SimpleUiInputSource::Poll() { }


// USER METHODS

VOID SimpleUiInputSource::Fire(CUIACTIONSTATE state)
{
	_Navigation.FireAction(_Action, state);
}

#pragma endregion


#pragma region [StatefulUiInputSourceBase] IMPLEMENTATION

// CONSTRUCTOR

StatefulUiInputSource::StatefulUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CUIACTION action, CUIINPUTSOURCEBEHAVIOR behavior)
	: SimpleUiInputSource(navigation, action),
	_Behavior(behavior) { }


// [IUiInputSource] OVERRIDES

CBOOL StatefulUiInputSource::IsAsynchronous() const
{
	return TRUE;
}


// USER METHODS

VOID StatefulUiInputSource::FireUpAction()
{
	if (CHECK_BITS(_Behavior, ACTION_ON_DOWN_ONLY) && !CHECK_BITS(_Behavior, PRESS_RELEASE))
		return;

	UIACTIONSTATE state = UiInputSourceBehaviorToActionState(_Behavior);

	if (CHECK_BITS(_Behavior, SIMPLE_DOUBLE_CLICK))
		state |= DOUBLE_CLICK;
	else if (CHECK_BITS(_Behavior, PRESS_RELEASE))
		state |= PRESSED;
	else if (CHECK_BITS(_Behavior, INVERSE_PRESS_RELEASE))
		state |= RELEASED;
	else
		state |= CLICK;

	this->Fire(state);
}

VOID StatefulUiInputSource::FireDownAction()
{
	if (CHECK_BITS(_Behavior, ACTION_ON_UP_ONLY) && !CHECK_BITS(_Behavior, PRESS_RELEASE))
		return;

	UIACTIONSTATE state = UiInputSourceBehaviorToActionState(_Behavior);

	if (CHECK_BITS(_Behavior, SIMPLE_DOUBLE_CLICK))
		state |= DOUBLE_CLICK;
	else if (CHECK_BITS(_Behavior, PRESS_RELEASE))
		state |= PRESSED;
	else if (CHECK_BITS(_Behavior, INVERSE_PRESS_RELEASE))
		state |= RELEASED;
	else
		state |= CLICK;

	this->Fire(state);
}

#pragma endregion


#ifdef ARDUINO

#pragma region [DigitalPinUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

DigitalPinUiInputSource::DigitalPinUiInputSource(RIUINAVIGATIONCONTROLLER navigation, 
		CPINNUM pinNum, CUIACTION action, CUIINPUTSOURCEBEHAVIOR behavior)
	: StatefulUiInputSource(navigation, action, behavior),
	_PinNum(pinNum) { }


// [IUiInputSource] OVERRIDES

CBOOL DigitalPinUiInputSource::IsAsynchronous() const
{
	return FALSE;
}

VOID DigitalPinUiInputSource::Poll()
{
	BIT pinState = ReadPin(_PinNum);

	if (pinState != _PrevPinState)
	{
		_PrevPinState = pinState;

		if (pinState)
			this->FireUpAction();
		else
			this->FireDownAction();
	}
}


// USER METHOD

VOID DigitalPinUiInputSource::Initialize()
{
	_PrevPinState = ReadPin(_PinNum);
}

#pragma endregion


#pragma region [ButtonUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

ButtonUiInputSource::ButtonUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CPINNUM pinNum, CUIACTION action, CBOOL actionOnDown)
	: DigitalPinUiInputSource(navigation, pinNum, action, actionOnDown ? CLICK_ON_DOWN : CLICK_ON_UP) { }

#pragma endregion


#pragma region [LatchUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

LatchUiInputSource::LatchUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CPINNUM pinNum, CUIACTION action, CBOOL pressOnDown)
	: DigitalPinUiInputSource(navigation, pinNum, action, pressOnDown ? PRESS_RELEASE : INVERSE_PRESS_RELEASE) { }

#pragma endregion


#pragma region [SwitchUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

SwitchUiInputSource::SwitchUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CPINNUM pinNum, CUIACTION upAction, CUIACTION downAction)
	: DigitalPinUiInputSource(navigation, pinNum, upAction),
	_DownAction(downAction) { }


// [StatefulUiInputSource] OVERRIDES

VOID SwitchUiInputSource::FireUpAction()
{
	this->Fire(RELEASED);
	_Navigation.FireAction(_DownAction, PRESSED);
}

VOID SwitchUiInputSource::FireDownAction()
{
	this->Fire(PRESSED);
	_Navigation.FireAction(_DownAction, RELEASED);
}

#pragma endregion


#pragma region [RotaryUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

RotaryUiInputSource::RotaryUiInputSource(RIUINAVIGATIONCONTROLLER navigation,
		CPINNUM pinNum1, CPINNUM pinNum2, CUIACTION incrementAction, CUIACTION decrementAction)
	: SwitchUiInputSource(navigation, pinNum1, incrementAction, decrementAction),
	_PinNum2(pinNum2) { }


// [IUiInputSource] OVERRIDES

VOID RotaryUiInputSource::Poll()
{
	BIT pin1State = ReadPin(_PinNum);

	if (pin1State != _PrevPinState)
	{
		_PrevPinState = pin1State;

		BIT pin2State = ReadPin(_PinNum2);

		if (pin2State)
			this->FireUpAction();
		else
			this->FireDownAction();
	}
}


// [StatefulUiInputSource] OVERRIDES

VOID RotaryUiInputSource::FireUpAction()
{
	this->Fire(CLICK);
}

VOID RotaryUiInputSource::FireDownAction()
{
	_Navigation.FireAction(_DownAction, CLICK);
}

#pragma endregion


#pragma region [ButtonEncoderUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

ButtonEncoderUiInputSource::ButtonEncoderUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CPINNUM pinNum1, CPINNUM pinNum2, 
		CPINNUM buttonPinNum, CUIACTION incrementAction, CUIACTION decrementAction, CUIACTION buttonAction, CBOOL actionOnDown)
	: RotaryUiInputSource(navigation, pinNum1, pinNum2, incrementAction, decrementAction),
	_ButtonInputSource(navigation, buttonPinNum, buttonAction, actionOnDown) { }


// [IUiInputSource] OVERRIDES

VOID ButtonEncoderUiInputSource::Poll()
{
	RotaryUiInputSource::Poll();

	_ButtonInputSource.Poll();
}


// [DigitalPinUiInputSource] OVERRIDES

VOID ButtonEncoderUiInputSource::Initialize()
{
	RotaryUiInputSource::Initialize();

	_ButtonInputSource.Initialize();
}

#pragma endregion


#pragma region [AnalogPinUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

AnalogPinUiInputSource::AnalogPinUiInputSource(RIUINAVIGATIONCONTROLLER navigation,
		CPINNUM pinNum, CWORD threshold, CUIACTION action, CUIINPUTSOURCEBEHAVIOR behavior)
	: StatefulUiInputSource(navigation, action, behavior),
	_PinNum(pinNum), _PinStateInputSource(navigation, _PinState, threshold, action, behavior) { }


// [IUiInputSource] OVERRIDES

VOID AnalogPinUiInputSource::Poll()
{
	_PinState = analogRead(_PinNum);

	_PinStateInputSource.Poll();
}


// USER METHOD

VOID AnalogPinUiInputSource::Initialize()
{
	_PinState = analogRead(_PinNum);

	_PinStateInputSource.Initialize();
}

#pragma endregion


#pragma region [AnalogValueUiInputSource] IMPLEMENTATION

// CONSTRUCTOR

AnalogValueUiInputSource::AnalogValueUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CPINNUM pinNum, CWORD threshold)
	: UiInputSourceBase(navigation),
	_PinNum(pinNum), _Threshold(threshold) { }


// [IUiInputSource] IMPLEMENTATION

CBOOL AnalogValueUiInputSource::IsAsynchronous() const
{
	return FALSE;
}


VOID AnalogValueUiInputSource::Poll()
{
	WORD pinState = analogRead(_PinNum);

	if (pinState > _PrevPinState + _Threshold OR pinState < _PrevPinState - _Threshold)
	{
		_PrevPinState = pinState;

		PCHAR buffer = new char[UI_INPUT_VALUE_BUFFER_SIZE];

		_Navigation.SendValue(itoa(pinState, buffer, 10));
	}
}


// USER METHOD

VOID AnalogValueUiInputSource::Initialize()
{
	_PrevPinState = analogRead(_PinNum);
}

#pragma endregion

#endif // #ifdef ARDUINO

#endif	// #ifndef NO_ITTYBITTY_UI_NAV_ADAPTERS
