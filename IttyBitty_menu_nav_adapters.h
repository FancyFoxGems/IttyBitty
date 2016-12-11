/***********************************************************************************************
* [IttyBitty_menu_nav_adapters.h]: NAVIGATION ADAPTERS FOR INPUT OF MENUI COMMANDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_NAV_ADAPTERS_H
#define _ITTYBITTY_MENU_NAV_ADAPTERS_H


#include "IttyBitty_menu_nav.h"


#pragma region DEFINES

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
	class DataBoundUiInputListener;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE), \
		CSL(DATA_BOUND_UI_INPUT_LISTENER_T_ARGS), DataBoundUiInputListener, DATABOUNDUIINPUTLISTENER);


	class SerialUiInputListener;
	TYPEDEF_CLASS_ALIASES(SerialUiInputListener, SERIALUIINPUTLISTENER);

	class SwitchUiInputListener;
	TYPEDEF_CLASS_ALIASES(SwitchUiInputListener, SWITCHUIINPUTLISTENER);

	class ButtonUiInputListener;
	TYPEDEF_CLASS_ALIASES(ButtonUiInputListener, BUTTONUIINPUTLISTENER);

	class RotaryUiInputListener;
	TYPEDEF_CLASS_ALIASES(RotaryUiInputListener, ROTARYUIINPUTLISTENER);

	class PotentiometerUiInputListener;
	TYPEDEF_CLASS_ALIASES(PotentiometerUiInputListener, POTENTIOMETERUIINPUTLISTENER);

#pragma endregion


#pragma region [SerialUiInputListener] DEFINITION

	template DATA_BOUND_UI_INPUT_LISTENER_T_CLAUSE_DEF
	CLASS DataBoundUiInputListener : public UiInputListenerBase
	{
	public:

		// [IUiListener] IMPLEMENTATION

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
				_Navigation->Up();
				break;

			case UiAction::DOWN:
				_Navigation->Down();
				break;

			case UiAction::LEFT:
				_Navigation->Left();
				break;

			case UiAction::RIGHT:
				_Navigation->Right();
				break;

			case UiAction::RETURN:
				_Navigation->Return();
				break;

			case UiAction::SELECT:
				_Navigation->Select();
				break;

			case UiAction::SHIFT:
				_Navigation->ToggleShift();
				break;

			case UiAction::ALT:
				_Navigation->ToggleAlt();
				break;

			default:
				break;
			}
		}
	};

#pragma endregion


#pragma region [SerialUiInputListener] DEFINITION

	CLASS SerialUiInputListener : public UiInputListenerBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [SwitchUiInputListener] DEFINITION

	CLASS SwitchUiInputListener : public UiInputListenerBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [ButtonUiInputListener] DEFINITION

	CLASS ButtonUiInputListener : public SwitchUiInputListener
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [RotaryUiInputListener] DEFINITION

	CLASS RotaryUiInputListener : public UiInputListenerBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [PotentiometerUiInputListener] DEFINITION

	CLASS PotentiometerUiInputListener : public UiInputListenerBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion

#pragma endregion
};

#endif
