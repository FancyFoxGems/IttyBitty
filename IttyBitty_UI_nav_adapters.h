/***********************************************************************************************
* [IttyBitty_UI_nav_adapters.h]: NAVIGATION ADAPTERS FOR INPUT OF MENUI COMMANDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_NAV_ADAPTERS_H
#define _ITTYBITTY_UI_NAV_ADAPTERS_H


#ifdef ARDUINO
#include "IttyBitty_GPIO.h"
#endif // #ifdef ARDUINO

#include "IttyBitty_UI_nav.h"

#include "Stream.h"


#pragma region NAVIGATION ADAPTER OPTIONS/CONSTANTS

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class StreamUiInputSource;
	TYPEDEF_CLASS_ALIASES(StreamUiInputSource, STREAMUIINPUTSOURCE);

	class SimpleUiInputSource;
	TYPEDEF_CLASS_ALIASES(SimpleUiInputSource, SIMPLEUIINPUTSOURCE);

	class StatefulUiInputSource;
	TYPEDEF_CLASS_ALIASES(StatefulUiInputSource, STATEFULUIINPUTSOURCE);

	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF	<typename TVar>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE		<typename TVar>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_ARGS			<TVar>

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE
	class DataBoundUiInputSource;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE), \
		CSL(DATA_BOUND_UI_INPUT_LISTENER_T_ARGS), DataBoundUiInputSource, DATABOUNDUIINPUTSOURCE);


#ifdef ARDUINO

	class DigitalPinUiInputSource;
	TYPEDEF_CLASS_ALIASES(DigitalPinUiInputSource, DIGITALPINUIINPUTSOURCE);

	class ButtonUiInputSource;
	TYPEDEF_CLASS_ALIASES(ButtonUiInputSource, BUTTONUIINPUTSOURCE);

	class LatchUiInputSource;
	TYPEDEF_CLASS_ALIASES(LatchUiInputSource, LATCHUIINPUTSOURCE);

	class SwitchUiInputSource;
	TYPEDEF_CLASS_ALIASES(SwitchUiInputSource, SWITCHUIINPUTSOURCE);

	class RotaryUiInputSource;
	TYPEDEF_CLASS_ALIASES(RotaryUiInputSource, ROTARYUIINPUTSOURCE);

	class ButtonEncoderUiInputSource;
	TYPEDEF_CLASS_ALIASES(ButtonEncoderUiInputSource, BUTTONENCODERUIINPUTSOURCE);

	class AnalogPinUiInputSource;
	TYPEDEF_CLASS_ALIASES(AnalogPinUiInputSource, ANALOGPINUIINPUTSOURCE);

	class PotentiometerUiInputSource;
	TYPEDEF_CLASS_ALIASES(PotentiometerUiInputSource, POTENTIOMETERUIINPUTSOURCE);

#endif // #ifdef ARDUINO

#pragma endregion


#pragma region ENUMS

	ENUM StreamUiInputOptions : BYTE
	{
		EXCLUDE_CARRIAGE_RETURN	= 0x1,
		EXCLUDE_LINEFEED		= 0x2,
		EXCLUDE_CR_AND_LF		= EXCLUDE_CARRIAGE_RETURN | EXCLUDE_LINEFEED,

		EXCLUDE_SPACE			= 0x4,
		EXCLUDE_TAB				= 0x8,
		EXCLUDE_WHITESPACE		= EXCLUDE_SPACE | EXCLUDE_TAB | EXCLUDE_CR_AND_LF
	};

	DECLARE_ENUM_AS_FLAGS(StreamUiInputOptions, STREAMUIINPUTOPTIONS);


	ENUM UiInputSourceBehavior : BYTE
	{
		SIMPLE_CLICK				= 0x00,
		SIMPLE_DOUBLE_CLICK			= 0x01,
		PRESS_RELEASE				= 0x02,

		ACTION_ON_ANY_CHANGE		= 0x00,
		ACTION_ON_UP_ONLY			= 0x04,
		ACTION_ON_DOWN_ONLY			= 0x08,
		INVERSE_ACTION				= ACTION_ON_DOWN_ONLY,

		CLICK_ON_ANY_CHANGE			= SIMPLE_CLICK | ACTION_ON_ANY_CHANGE,
		CLICK_ON_UP					= SIMPLE_CLICK | ACTION_ON_UP_ONLY,
		CLICK_ON_DOWN				= SIMPLE_CLICK | ACTION_ON_DOWN_ONLY,
		DOUBLE_CLICK_ON_ANY_CHANGE	= SIMPLE_DOUBLE_CLICK | ACTION_ON_ANY_CHANGE,
		DOUBLE_CLICK_ON_UP			= SIMPLE_DOUBLE_CLICK | ACTION_ON_UP_ONLY,
		DOUBLE_CLICK_ON_DOWN		= SIMPLE_DOUBLE_CLICK | ACTION_ON_DOWN_ONLY,
		INVERSE_PRESS_RELEASE		= INVERSE_ACTION | PRESS_RELEASE,

		RELATIVE_CHANGE				= 0x00,
		ABSOLUTE_COMPARE			= 0x10,

		WITH_SHIFT					= SHIFT_ON,
		WITH_ALT					= ALT_ON,
		WITH_SHIFT_ALT				= WITH_SHIFT | WITH_ALT,
	};

	DECLARE_ENUM_AS_FLAGS(UiInputSourceBehavior, UIINPUTSOURCEBEHAVIOR);

	INLINE CUIACTIONSTATE UiInputSourceBehaviorToActionState(CUIINPUTSOURCEBEHAVIOR behavior)
	{
		return static_cast<CUIACTIONSTATE>(MASK((CBYTE)behavior, SHIFT_ON | ALT_ON));
	}

#pragma endregion


#pragma region [StreamUiInputSource] DEFINITION

	CLASS StreamUiInputSource : public BaseUiInputSource
	{
	public:

		// CONSTRUCTOR

		StreamUiInputSource(RIUINAVIGATIONCONTROLLER, Stream & = SERIAL_PORT_MONITOR, CSTREAMUIINPUTOPTIONS = EXCLUDE_CR_AND_LF);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		typedef Stream & RSTREAM;


		// INSTANCE VARIABLES

		RSTREAM const _Stream;

		STREAMUIINPUTOPTIONS _Options;
	};

#pragma endregion


#pragma region [SimpleUiInputSource] DEFINITION

	CLASS SimpleUiInputSource : public BaseUiInputSource
	{
	public:

		// CONSTRUCTOR

		SimpleUiInputSource(RIUINAVIGATIONCONTROLLER, CUIACTION);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


		// USER METHODS

		VOID Fire(CUIACTIONSTATE = CLICK);


	protected:

		// INSTANCE VARIABLES

		UIACTION _Action = UiAction::SELECT;
	};

#pragma endregion


#pragma region [StatefulUiInputSource] DEFINITION

	CLASS StatefulUiInputSource : public SimpleUiInputSource
	{
	public:

		// CONSTRUCTOR

		StatefulUiInputSource(RIUINAVIGATIONCONTROLLER, CUIACTION = UiAction::SHIFT, CUIINPUTSOURCEBEHAVIOR = PRESS_RELEASE);


		// [IUiInputSource] OVERRIDES

		VIRTUAL CBOOL IsAsynchronous() const;


		// USER METHODS

		VIRTUAL VOID FireUpAction();
		VIRTUAL VOID FireDownAction();


	protected:


		// INSTANCE VARIABLES

		UIINPUTSOURCEBEHAVIOR _Behavior = SIMPLE_CLICK;
	};

#pragma endregion


#pragma region [DataBoundUiInputSource] DEFINITION

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF
	CLASS DataBoundUiInputSource : public StatefulUiInputSource
	{
	public:

		// CONSTRUCTORS

		DataBoundUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CONST TVar & variable, CONST TVar threshold = TVar(1), 
				CUIACTION action = UiAction::SHIFT, CUIINPUTSOURCEBEHAVIOR behavior = PRESS_RELEASE | RELATIVE_CHANGE)
			: StatefulUiInputSource(navigation, action, behavior),
				_Variable(variable), _Threshold(threshold) { }


		// [IUiInputSource] OVERRIDES

		VIRTUAL CBOOL IsAsynchronous() const
		{
			return FALSE;
		}

		VIRTUAL VOID Poll()
		{
			if (WITH_BITS(_Behavior, ABSOLUTE_COMPARE))
			{
				if (_Variable > _Threshold)
					this->FireUpAction();
				else if (_Variable < _Threshold)
					this->FireDownAction();
			}
			else
			{
				if (_Variable > _PrevValue + _Threshold)
				{
					_PrevValue = _Variable;

					this->FireUpAction();
				}
				else if (_Variable < _PrevValue - _Threshold)
				{
					_PrevValue = _Variable;

					this->FireDownAction();
				}
			}
		}


		// USER METHOD

		VIRTUAL VOID Initialize()
		{
			_PrevValue = _Variable;
}


	protected:

		// INSTANCE VARIABLES

		CONST TVar & _Variable;
		TVar _Threshold = TVar(0);

		TVar _PrevValue = 0;
	};

#pragma endregion


#ifdef ARDUINO

#pragma region [DigitalPinUiInputSource] DEFINITION

	CLASS DigitalPinUiInputSource : public StatefulUiInputSource
	{
	public:

		// CONSTRUCTOR

		DigitalPinUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, CUIACTION = UiAction::SELECT, CUIINPUTSOURCEBEHAVIOR = CLICK_ON_UP);


		// [IUiInputSource] OVERRIDES

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


		// USER METHOD

		VIRTUAL VOID Initialize();

	protected:

		// INSTANCE VARIABLES

		SIZE _PinNum = 0;

		BIT _PrevPinState = LOW;
	};

#pragma endregion


#pragma region [ButtonUiInputSource] DEFINITION

	CLASS ButtonUiInputSource : public DigitalPinUiInputSource
	{
	public:

		// CONSTRUCTOR

		ButtonUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, CUIACTION = UiAction::SELECT, CBOOL = TRUE);
	};

#pragma endregion


#pragma region [LatchUiInputSource] DEFINITION

	CLASS LatchUiInputSource : public DigitalPinUiInputSource
	{
	public:

		// CONSTRUCTOR

		LatchUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, CUIACTION = UiAction::SHIFT, CBOOL = TRUE);
	};

#pragma endregion


#pragma region [SwitchUiInputSource] DEFINITION

	CLASS SwitchUiInputSource : public DigitalPinUiInputSource
	{
	public:

		// CONSTRUCTOR

		SwitchUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, CUIACTION = UiAction::SHIFT, CUIACTION = UiAction::ALT);


		// [StatefulUiInputSource] OVERRIDES

		VIRTUAL VOID FireUpAction();
		VIRTUAL VOID FireDownAction();


	protected:

		// INSTANCE VARIABLES

		UIACTION _DownAction = UiAction::ALT;
	};

#pragma endregion


#pragma region [RotaryUiInputSource] DEFINITION

	CLASS RotaryUiInputSource : public SwitchUiInputSource
	{
	public:

		// CONSTRUCTOR

		RotaryUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, PIN_NUMBER, CUIACTION = UiAction::UP, CUIACTION = UiAction::DOWN);


		// [IUiInputSource] OVERRIDES

		VIRTUAL VOID Poll();


		// [StatefulUiInputSource] OVERRIDES

		VIRTUAL VOID FireUpAction();
		VIRTUAL VOID FireDownAction();


	protected:

		// INSTANCE VARIABLES

		SIZE _PinNum2 = 0;
	};

#pragma endregion


#pragma region [ButtonEncoderUiInputSource] DEFINITION

	CLASS ButtonEncoderUiInputSource : public RotaryUiInputSource
	{
	public:

		// CONSTRUCTOR

		ButtonEncoderUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, PIN_NUMBER, PIN_NUMBER,
			CUIACTION = UiAction::UP, CUIACTION = UiAction::DOWN, CUIACTION = UiAction::SELECT, CBOOL = TRUE);


		// [IUiInputSource] OVERRIDES

		VIRTUAL VOID Poll();


		// [DigitalPinUiInputSource] OVERRIDE

		VIRTUAL VOID Initialize();


	protected:

		// INSTANCE VARIABLES

		BUTTONUIINPUTSOURCE _ButtonInputSource;
	};

#pragma endregion


#pragma region [AnalogPinUiInputSource] DEFINITION

	CLASS AnalogPinUiInputSource : public StatefulUiInputSource
	{
	public:

		// CONSTRUCTOR

		AnalogPinUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, CWORD = 1,
			CUIACTION = UiAction::SHIFT, CUIINPUTSOURCEBEHAVIOR = PRESS_RELEASE | RELATIVE_CHANGE);


		// [IUiInputSource] OVERRIDES

		VIRTUAL VOID Poll();


		// USER METHOD

		VIRTUAL VOID Initialize();


	protected:

		// INSTANCE VARIABLES

		SIZE _PinNum = 0;
		WORD _PinState = 0;
		DataBoundUiInputSource<WORD> _PinStateInputSource;
	};

#pragma endregion


#pragma region [PotentiometerUiInputSource] DEFINITION

	CLASS PotentiometerUiInputSource : public AnalogPinUiInputSource
	{
	public:

		// CONSTRUCTOR

		PotentiometerUiInputSource(RIUINAVIGATIONCONTROLLER, PIN_NUMBER, CWORD = 1, CUIACTION = UiAction::UP, CUIACTION = UiAction::DOWN);


		// [IUiInputSource] OVERRIDES

		VIRTUAL VOID Poll();


		// [StatefulUiInputSource] OVERRIDES

		VIRTUAL VOID FireUpAction();
		VIRTUAL VOID FireDownAction();


		//  [AnalogPinUiInputSource] OVERRIDE

		VIRTUAL VOID Initialize();


	protected:

		// INSTANCE VARIABLES

		DataBoundUiInputSource<WORD> _DownPinStateInputSource;
	};

#pragma endregion

#endif // #ifdef ARDUINO

#pragma endregion
};

#endif
