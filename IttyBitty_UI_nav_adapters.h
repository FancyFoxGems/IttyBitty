/***********************************************************************************************
* [IttyBitty_UI_nav_adapters.h]: NAVIGATION ADAPTERS FOR INPUT OF MENUI COMMANDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
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

	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF	<typename TVar>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE		<typename TVar>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_ARGS			<TVar>

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE
	class DataBoundUiInputSource;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE), \
		CSL(DATA_BOUND_UI_INPUT_LISTENER_T_ARGS), DataBoundUiInputSource, DATABOUNDUIINPUTSOURCE);

	class SerialUiInputSource;
	TYPEDEF_CLASS_ALIASES(SerialUiInputSource, SERIALUIINPUTSOURCE);

	class DigitalPinUiInputSource;
	TYPEDEF_CLASS_ALIASES(DigitalPinUiInputSource, DIGITALPINUIINPUTSOURCE);

	class AnalogPinUiInputSource;
	TYPEDEF_CLASS_ALIASES(AnalogPinUiInputSource, ANALOGPINUIINPUTSOURCE);

	class SwitchUiInputSource;
	TYPEDEF_CLASS_ALIASES(SwitchUiInputSource, SWITCHUIINPUTSOURCE);

	class ButtonUiInputSource;
	TYPEDEF_CLASS_ALIASES(ButtonUiInputSource, BUTTONUIINPUTSOURCE);

	class RotaryUiInputSource;
	TYPEDEF_CLASS_ALIASES(RotaryUiInputSource, ROTARYUIINPUTSOURCE);

	class ClickEncoderUiInputSource;
	TYPEDEF_CLASS_ALIASES(ClickEncoderUiInputSource, CLICKENCODERUIINPUTSOURCE);

	class PotentiometerUiInputSource;
	TYPEDEF_CLASS_ALIASES(PotentiometerUiInputSource, POTENTIOMETERUIINPUTSOURCE);

#pragma endregion


#pragma region [DataBoundUiInputSource] DEFINITION

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF
	CLASS DataBoundUiInputSource : public UiInputSource
	{
	public:

		// CONSTRUCTOR

		DataBoundUiInputSource(RIUINAVIGATIONCONTROLLER navigation, CUIACTION action, CONST TVar & variable, CONST TVar tolerance = TVar(1))
			: UiInputSource(navigation), _Action(action), _Variable(variable), _Tolerance(tolerance) { }


		// [IUiListener] OVERRIDES

		CBOOL IsAsynchronous() const { return FALSE; }

		VOID Poll()
		{
			if (_Variable > _PrevValue + _Tolerance || _Variable < _PrevValue - _Tolerance)
			{
				_PrevValue = _Variable;

				this.DoAction();
			}
		}


	protected:

		// INSTANCE VARIABLES

		CUIACTION _Action = UiAction::SELECT;

		CONST TVar & _Variable;
		CONST TVar _Tolerance = TVar(0);

		TVar _PrevValue = 0;


		// HELPER METHODS

		VIRTUAL VOID DoAction()
		{
			switch (_Action)
			{
			case UiAction::SHIFT:
				_Navigation.ToggleShift();
				break;

			case UiAction::ALT:
				_Navigation.ToggleAlt();
				break;

			default:
				_Navigation.FireAction(_Action);
				break;
			}
		}
	};

#pragma endregion


#pragma region [StreamUiInputSource] DEFINITION

	CLASS StreamUiInputSource : public UiInputSource
	{
	public:

		// CONSTRUCTOR

		StreamUiInputSource();
		StreamUiInputSource(Stream &);


		// [IUiListener] OVERRIDES

		CBOOL IsAsynchronous() const;

		VOID Poll();


	protected:

		// INSTANCE VARIABLES

		Stream & _Stream = SERIAL_PORT_MONITOR;
	};

#pragma endregion


#pragma region [DigitalPinUiInputSource] DEFINITION

	CLASS DigitalPinUiInputSource : public UiInputSource
	{
	public:

		// CONSTRUCTOR

		DigitalPinUiInputSource(CBYTE, CUIACTION);


		// [IUiListener] OVERRIDES

		CBOOL IsAsynchronous() const;

		VOID Poll();


	protected:

		// INSTANCE VARIABLES

		BOOL _IsAsynchronous = FALSE;
		BYTE _PinNum = 0;
	};

#pragma endregion


#pragma region [AnalogPinUiInputSource] DEFINITION

	CLASS AnalogPinUiInputSource : public DigitalPinUiInputSource
	{
	public:

		// [IUiListener] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES
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

		// [IUiListener] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [ClickEncoderUiInputSource] DEFINITION

	CLASS ClickEncoderUiInputSource : public RotaryUiInputSource
	{
	public:

		// [IUiListener] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [PotentiometerUiInputSource] DEFINITION

	CLASS PotentiometerUiInputSource : public AnalogPinUiInputSource
	{
	public:

		// [IUiListener] OVERRIDES

		VOID Poll();


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion

#pragma endregion
};

#endif
