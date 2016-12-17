/***********************************************************************************************
* [IttyBitty_UI_nav_adapters.h]: NAVIGATION ADAPTERS FOR INPUT OF MENUI COMMANDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_NAV_ADAPTERS_H
#define _ITTYBITTY_UI_NAV_ADAPTERS_H


#include "IttyBitty_UI_nav.h"

#include "HardwareSerial.h"


#pragma region NAVIGATION ADAPTER OPTIONS/CONSTANTS

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF	\
		<CUIACTION Action, typename TVar, CONST TVar & Var, CONST TVar Tolerance>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE		\
		<CUIACTION Action, typename TVar, CONST TVar & Var, CONST TVar Tolerance = TVar(1)>
	#define DATA_BOUND_UI_INPUT_LISTENER_T_ARGS			<Action, TVar, Var, Tolerance>

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


#pragma region [SerialUiInputSource] DEFINITION

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF
	CLASS DataBoundUiInputSource : public UiInputSourceBase
	{
	public:

		// [IUiListener] OVERRIDES

		CBOOL IsAsynchronous() const { return FALSE; }

		VOID Poll()
		{
			if (_PrevValue + Tolerance <= Var)
			{
				_PrevValue = Var;
				this->DoAction();
			}
		}


	protected:

		// INSTANCE VARIABLES

		TVar _PrevValue = 0;


		// HELPER METHODS

		VOID DoAction()
		{
			switch (Action)
			{
			case UiAction::UP:
				_NavListener->Up();
				break;

			case UiAction::DOWN:
				_NavListener->Down();
				break;

			case UiAction::LEFT:
				_NavListener->Left();
				break;

			case UiAction::RIGHT:
				_NavListener->Right();
				break;

			case UiAction::RETURN:
				_NavListener->Return();
				break;

			case UiAction::SELECT:
				_NavListener->Select();
				break;

			case UiAction::SHIFT:
				_NavListener->ToggleShift();
				break;

			case UiAction::ALT:
				_NavListener->ToggleAlt();
				break;

			default:
				break;
			}
		}
	};

#pragma endregion


#pragma region [SerialUiInputSource] DEFINITION

	CLASS SerialUiInputSource : public UiInputSourceBase
	{
	public:

		// [IUiListener] OVERRIDES

		CBOOL IsAsynchronous() const;

		VOID Poll();


	protected:

		// INSTANCE VARIABLES

		HardwareSerial & _Serial = SERIAL_PORT_MONITOR;
	};

#pragma endregion


#pragma region [DigitalPinUiInputSource] DEFINITION

	CLASS DigitalPinUiInputSource : public UiInputSourceBase
	{
	public:

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
