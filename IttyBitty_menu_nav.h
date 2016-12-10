/***********************************************************************************************
* [IttyBitty_menu_nav.h]: NAVIGATION SUB-SYSTEM FOR MENUI COMMAND INPUT INTERFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_NAV_H
#define _ITTYBITTY_MENU_NAV_H


#include "IttyBitty_bits.h"


#pragma region DEFINES

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IUiInputListener;
	TYPEDEF_CLASS_ALIASES(IUiInputListener, IUIINPUTLISTENER);

	class UiInputListenerBase;
	TYPEDEF_CLASS_ALIASES(UiInputListenerBase, UIINPUTLISTENERBASE);


	class UiNavigationController;
	TYPEDEF_CLASS_ALIASES(UiNavigationController, UINAVIGATIONCONTROLLER);

#pragma endregion


#pragma region ENUMS

	ENUM UiAction : BYTE
	{
		UP		= 0x01,
		DOWN	= 0x02,
		LEFT	= 0x04,
		RIGHT	= 0x08,
		ESCAPE	= 0x10,
		SELECT	= 0x20,
		SHIFT	= 0x40,
		ALT		= 0x80
	};

	TYPEDEF_ENUM_ALIASES(UiAction, UIACTION);

#pragma endregion


#pragma region [IUiInputListener] DEFINITION

	INTERFACE IUiInputListener
	{
	public:

		// INTERFACE METHODS

		VIRTUAL CBOOL IsAsynchronous() const = 0;

		VIRTUAL VOID Poll() const = 0;


	protected:

		IUiInputListener() { }
	};

#pragma endregion


#pragma region [UiInputListenerBase] DEFINITION

	CLASS UiInputListenerBase : public IUiInputListener
	{
	public:

		// [IUiListener] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const; // { return TRUE; }

		VIRTUAL VOID Poll() const; // { }


	protected:

		// INSTANCE VARIABLES

		PCUINAVIGATIONCONTROLLER _Navigation = NULL;
	};

#pragma endregion


#pragma region [UiNavigationController] DEFINITION

	class UiNavigationController : public IUiInputListener
	{
	public:

		// USER METHODS

		VOID Up();
		VOID Down();
		VOID Left();
		VOID Right();
		VOID Escape();
		VOID Select();

		VOID ToggleShift();
		VOID ShiftOn();
		VOID ShiftOff();

		VOID ToggleAlt();
		VOID AltOn();
		VOID AltOff();


	protected:

		// INSTANCE VARIABLES

		BOOL _ShiftOn = FALSE;
		BOOL _AltOn = FALSE;
	};

#pragma endregion
};

#endif
