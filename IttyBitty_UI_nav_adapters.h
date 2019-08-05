/***********************************************************************************************
* [IttyBitty_UI_nav_adapters.h]: NAVIGATION ADAPTERS FOR INPUT OF MENUI COMMANDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_NAV_ADAPTERS_H
#define _ITTYBITTY_UI_NAV_ADAPTERS_H


#include "IttyBitty_GPIO.h"
#include "IttyBitty_UI_nav.h"

#include "Stream.h"


#pragma region NAVIGATION ADAPTER OPTIONS/CONSTANTS

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class SimpleUiInputSource;
	TYPEDEF_CLASS_ALIASES(SimpleUiInputSource, SIMPLEUIINPUTSOURCE);

	class SerialUiInputSource;
	TYPEDEF_CLASS_ALIASES(SerialUiInputSource, SERIALUIINPUTSOURCE);

	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF	<typename TVar>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE		<typename TVar>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_ARGS			<TVar>

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE
	class DataBoundUiInputSource;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE), \
		CSL(DATA_BOUND_UI_INPUT_LISTENER_T_ARGS), DataBoundUiInputSource, DATABOUNDUIINPUTSOURCE);

	class DigitalPinUiInputSource;
	TYPEDEF_CLASS_ALIASES(DigitalPinUiInputSource, DIGITALPINUIINPUTSOURCE);

	class SwitchUiInputSource;
	TYPEDEF_CLASS_ALIASES(SwitchUiInputSource, SWITCHUIINPUTSOURCE);

	class ButtonUiInputSource;
	TYPEDEF_CLASS_ALIASES(ButtonUiInputSource, BUTTONUIINPUTSOURCE);

	class RotaryUiInputSource;
	TYPEDEF_CLASS_ALIASES(RotaryUiInputSource, ROTARYUIINPUTSOURCE);

	class ClickEncoderUiInputSource;
	TYPEDEF_CLASS_ALIASES(ClickEncoderUiInputSource, CLICKENCODERUIINPUTSOURCE);

	class AnalogPinUiInputSource;
	TYPEDEF_CLASS_ALIASES(AnalogPinUiInputSource, ANALOGPINUIINPUTSOURCE);

	class PotentiometerUiInputSource;
	TYPEDEF_CLASS_ALIASES(PotentiometerUiInputSource, POTENTIOMETERUIINPUTSOURCE);

#pragma endregion


#pragma region ENUMS

	ENUM UiInputSourceBehavior : BYTE
	{
		CLICK_ONLY				= 0x0,
		PRESS_RELEASE			= 0x1,
		INVERSE_PRESS_RELEASE	= 0x2,

		RELATIVE_CHANGE			= 0x0,
		ABSOLUTE_COMPARE		= 0x4,

		WITH_SHIFT				= SHIFT_ON,
		WITH_ALT				= ALT_ON,
		WITH_SHIFT_ALT			= WITH_SHIFT | WITH_ALT
	};

	DECLARE_ENUM_AS_FLAGS(UiInputSourceBehavior, UIINPUTSOURCEBEHAVIOR);

	INLINE CUIACTIONSTATE UiInputSourceBehaviorToActionState(CUIINPUTSOURCEBEHAVIOR behavior)
	{
		return static_cast<CUIACTIONSTATE>(HIGH_NYBBLE((CBYTE)behavior));
	}


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

#pragma endregion


#pragma region [SimpleUiInputSource] DEFINITION

	CLASS SimpleUiInputSource : public UiInputSource
	{
	public:

		// CONSTRUCTOR

		SimpleUiInputSource(RIUINAVIGATIONCONTROLLER, CUIACTION);


		// [IUiInputSource] OVERRIDES

		CBOOL IsAsynchronous() const;

		VOID Poll();


		// USER METHODS

		VOID Fire(CUIACTIONSTATE = CLICK);


	protected:

		// INSTANCE VARIABLES

		UIACTION _Action = UiAction::SELECT;
	};

#pragma endregion


#pragma region [StreamUiInputSource] DEFINITION

	CLASS StreamUiInputSource : public UiInputSource
	{
	public:

		// CONSTRUCTOR

		StreamUiInputSource(RIUINAVIGATIONCONTROLLER navigation, Stream & = SERIAL_PORT_MONITOR, CSTREAMUIINPUTOPTIONS = EXCLUDE_CR_AND_LF);


		// [IUiInputSource] OVERRIDES

		CBOOL IsAsynchronous() const;

		VOID Poll();


	protected:

		typedef Stream & RSTREAM;


		// INSTANCE VARIABLES

		RSTREAM const _Stream;

		STREAMUIINPUTOPTIONS _Options;
	};

#pragma endregion


#pragma region [DataBoundUiInputSource] DEFINITION

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF
	CLASS DataBoundUiInputSource : public SimpleUiInputSource
	{
	public:

		// CONSTRUCTOR

		DataBoundUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CUIACTION action, CONST TVar & variable, 
				CONST TVar tolerance = TVar(1), CUIINPUTSOURCEBEHAVIOR behavior = CLICK_ONLY)
			: SimpleUiInputSource(navigation, action), 
				_Variable(variable), _Tolerance(tolerance), _Behavior(behavior) { }


		// [IUiInputSource] OVERRIDES

		CBOOL IsAsynchronous() const { return FALSE; }

		VOID Poll()
		{
			BOOL fireGreaterThanAction = FALSE;
			BOOL fireLessThanAction = FALSE;

			if (WITH_BITS(_Behavior, ABSOLUTE_COMPARE))
			{
				if (_Variable > _Tolerance)
					fireGreaterThanAction = TRUE;
				else if (_Variable < _Tolerance)
					fireLessThanAction = TRUE;
			}
			else
			{
				if (_Variable > _PrevValue + _Tolerance)
				{
					fireGreaterThanAction = TRUE;

					_PrevValue = _Variable;
				}
				else if (_Variable < _PrevValue - _Tolerance)
				{
					fireLessThanAction = TRUE;

					_PrevValue = _Variable;
				}
			}

			if (fireGreaterThanAction OR fireLessThanAction)
			{
				UIACTIONSTATE state = UiInputSourceBehaviorToActionState(_Behavior);

				if (fireGreaterThanAction)
				{
					if (WITH_BITS(_Behavior, PRESS_RELEASE))
						state |= PRESSED;
					else if (WITH_BITS(_Behavior, INVERSE_PRESS_RELEASE))
						state |= RELEASED;
					else
						state |= CLICK;
				}
				else if (fireLessThanAction)
				{
					if (WITH_BITS(_Behavior, PRESS_RELEASE))
						state |= PRESSED;
					else if (WITH_BITS(_Behavior, INVERSE_PRESS_RELEASE))
						state |= RELEASED;
					else
						state |= CLICK;
				}

				this.Fire(state);
			}
		}


	protected:

		// INSTANCE VARIABLES

		UIINPUTSOURCEBEHAVIOR _Behavior = CLICK_ONLY;

		CONST TVar & _Variable;
		TVar _Tolerance = TVar(0);

		TVar _PrevValue = 0;
	};

#pragma endregion


#pragma region [DigitalPinUiInputSource] DEFINITION

	CLASS DigitalPinUiInputSource : public SimpleUiInputSource
	{
	public:

		// CONSTRUCTOR

		DigitalPinUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CBYTE, CUIACTION);


		// [IUiInputSource] OVERRIDES

		CBOOL IsAsynchronous() const;

		VOID Poll();


	protected:

		// INSTANCE VARIABLES

		BYTE _PinNum = 0;
		BOOL _IsAsynchronous = FALSE;
	};

#pragma endregion


#pragma region [SwitchUiInputSource] DEFINITION

	CLASS SwitchUiInputSource : public DigitalPinUiInputSource
	{
	public:


	protected:

		// INSTANCE VARIABLES
	};

#pragma endregion


#pragma region [ButtonUiInputSource] DEFINITION

	CLASS ButtonUiInputSource : public SwitchUiInputSource
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [RotaryUiInputSource] DEFINITION

	CLASS RotaryUiInputSource : public DigitalPinUiInputSource
	{
	public:

		// [IUiInputSource] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [ClickEncoderUiInputSource] DEFINITION

	CLASS ClickEncoderUiInputSource : public RotaryUiInputSource
	{
	public:

		// [IUiInputSource] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [AnalogPinUiInputSource] DEFINITION

	CLASS AnalogPinUiInputSource : public DigitalPinUiInputSource
	{
	public:

		// [IUiInputSource] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES
	};

#pragma endregion


#pragma region [PotentiometerUiInputSource] DEFINITION

	CLASS PotentiometerUiInputSource : public AnalogPinUiInputSource
	{
	public:

		// [IUiInputSource] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion

#pragma endregion
};

#endif
