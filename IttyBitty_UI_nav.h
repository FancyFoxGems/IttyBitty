/***********************************************************************************************
* [IttyBitty_UI_nav.h]: NAVIGATION SUB-SYSTEM FOR MENUI COMMAND INPUT INTERFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_NAV_H
#define _ITTYBITTY_UI_NAV_H


#include "IttyBitty_bits.h"


// SUPRESS COMPILER WARNINGS RELATED TO PARAM REORDERING
IGNORE_WARNING(reorder)


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IUiNavigationListener;
	TYPEDEF_CLASS_ALIASES(IUiNavigationListener, IUINAVIGATIONLISTENER);

	interface IUiInputListener;
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
		RETURN	= 0x10,
		SELECT	= 0x20,
		SHIFT	= 0x40,
		ALT		= 0x80
	};

	TYPEDEF_ENUM_ALIASES(UiAction, UIACTION);

#pragma endregion


#pragma region [IUiNavigationListener] DEFINITION

	INTERFACE IUiNavigationListener
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiNavigationListener() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL IsShiftOn() const = 0;
		VIRTUAL VOID ToggleShift() = 0;
		VIRTUAL VOID ShiftOn() = 0;
		VIRTUAL VOID ShiftOff() = 0;

		VIRTUAL CBOOL IsAltOn() const = 0;
		VIRTUAL VOID ToggleAlt() = 0;
		VIRTUAL VOID AltOn() = 0;
		VIRTUAL VOID AltOff() = 0;


		// INTERFACE METHODS

		VIRTUAL VOID Up() = 0;
		VIRTUAL VOID Down() = 0;
		VIRTUAL VOID Left() = 0;
		VIRTUAL VOID Right() = 0;
		VIRTUAL VOID Return() = 0;
		VIRTUAL VOID Select() = 0;


	protected:

		IUiNavigationListener() { }
	};

#pragma endregion


#pragma region [IUiInputListener] DEFINITION

	INTERFACE IUiInputListener
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiInputListener() { }


		// INTERFACE METHODS

		VIRTUAL CBOOL IsAsynchronous() const = 0;

		VIRTUAL VOID Poll() = 0;


	protected:

		IUiInputListener() { }
	};

#pragma endregion


#pragma region [UiInputListenerBase] DEFINITION

	CLASS UiInputListenerBase : public IUiInputListener
	{
	public:

		// CONSTRUCTOR

		UiInputListenerBase(PIUINAVIGATIONLISTENER);


		// [IUiListener] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// INSTANCE VARIABLES

		PIUINAVIGATIONLISTENER _Navigation = NULL;
	};

#pragma endregion


#pragma region [UiNavigationController] DEFINITION

	class UiNavigationController : public IUiInputListener, public IUiNavigationListener
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		UiNavigationController(CBYTE = 0, PPIUIINPUTLISTENER = NULL);
		UiNavigationController(RIUIINPUTLISTENER);

		VIRTUAL ~UiNavigationController();


		// OPERATORS

		PCIUIINPUTLISTENER operator[](CBYTE) const;
		PIUIINPUTLISTENER operator[](CBYTE);


		// ACCESSORS

		CBYTE ListenerCount() const;

		RCIUIINPUTLISTENER Listener(CBYTE) const;
		RIUIINPUTLISTENER Listener(CBYTE);


		// [IUiListener] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();

		VIRTUAL VOID Up();
		VIRTUAL VOID Down();
		VIRTUAL VOID Left();
		VIRTUAL VOID Right();
		VIRTUAL VOID Return();
		VIRTUAL VOID Select();


	protected:

		// INSTANCE VARIABLES

		PPIUIINPUTLISTENER _Listeners = NULL;
		BYTE _ListenerCount = 0;

		BOOL _ShiftOn = FALSE;
		BOOL _AltOn = FALSE;
	};

#pragma endregion
};

#endif
