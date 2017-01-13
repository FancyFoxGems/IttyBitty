/***********************************************************************************************
* [IttyBitty_UI_nav.h]: NAVIGATION SUB-SYSTEM FOR MENUI COMMAND INPUT INTERFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_NAV_H
#define _ITTYBITTY_UI_NAV_H


#include "IttyBitty_UI_options.h"


// SUPRESS COMPILER WARNINGS RELATED TO PARAM REORDERING
IGNORE_WARNING(reorder)


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IUiInputSource;
	TYPEDEF_CLASS_ALIASES(IUiInputSource, IUIINPUTSOURCE);

	interface IUiNavigationListener;
	TYPEDEF_CLASS_ALIASES(IUiNavigationListener, IUINAVIGATIONLISTENER);

	interface IUiNavigationController;
	TYPEDEF_CLASS_ALIASES(IUiNavigationController, IUINAVIGATIONCONTROLLER);

	class UiInputSourceBase;
	TYPEDEF_CLASS_ALIASES(UiInputSourceBase, UIINPUTSOURCEBASE);

	class UiNavigationController;
	TYPEDEF_CLASS_ALIASES(UiNavigationController, UINAVIGATIONCONTROLLER);

#pragma endregion


#pragma region [IUiInputSource] DEFINITION

	INTERFACE IUiInputSource
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiInputSource() { }


		// INTERFACE METHODS

		VIRTUAL CBOOL IsAsynchronous() const = 0;

		VIRTUAL VOID Poll() = 0;


	protected:

		IUiInputSource() { }
	};

#pragma endregion


#pragma region [IUiNavigationListener] DEFINITION

	INTERFACE IUiNavigationListener
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiNavigationListener() { }


		// INTERFACE METHODS

		VIRTUAL VOID Up(CUIACTIONSTATE = UiActionState::CLICK) = 0;
		VIRTUAL VOID Down(CUIACTIONSTATE = UiActionState::CLICK) = 0;
		VIRTUAL VOID Left(CUIACTIONSTATE = UiActionState::CLICK) = 0;
		VIRTUAL VOID Right(CUIACTIONSTATE = UiActionState::CLICK) = 0;
		VIRTUAL VOID Return(CUIACTIONSTATE = UiActionState::CLICK) = 0;
		VIRTUAL VOID Select(CUIACTIONSTATE = UiActionState::CLICK) = 0;


	protected:

		IUiNavigationListener() { }
	};

#pragma endregion


#pragma region [IUiNavigationController] DEFINITION

	INTERFACE IUiNavigationController : public IUiNavigationListener, public IUiInputSource
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiNavigationController() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL IsShiftOn() const = 0;
		VIRTUAL VOID ToggleShift() = 0;
		VIRTUAL VOID ShiftOn() = 0;
		VIRTUAL VOID ShiftOff() = 0;

		VIRTUAL CBOOL IsAltOn() const = 0;
		VIRTUAL VOID ToggleAlt() = 0;
		VIRTUAL VOID AltOn() = 0;
		VIRTUAL VOID AltOff() = 0;


	protected:

		IUiNavigationController() { }
	};

#pragma endregion


#pragma region [UiInputSourceBase] DEFINITION

	CLASS UiInputSourceBase : public IUiInputSource
	{
	public:

		// CONSTRUCTOR

		UiInputSourceBase(RIUINAVIGATIONCONTROLLER);


		// [IUiListener] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// INSTANCE VARIABLES

		RIUINAVIGATIONCONTROLLER _Navigation;
	};

#pragma endregion


#pragma region [UiNavigationController] DEFINITION

	class UiNavigationController : public IUiNavigationController
	{
	public:

		// CONSTRUCTOR/DESTRUCTOR

		UiNavigationController(RIUINAVIGATIONLISTENER, CBYTE = 0, PPIUIINPUTSOURCE = NULL);

		VIRTUAL ~UiNavigationController();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// OPERATORS

		VIRTUAL PCIUIINPUTSOURCE operator[](CBYTE) const;
		VIRTUAL PIUIINPUTSOURCE operator[](CBYTE);


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE InputSourceCount() const;

		VIRTUAL RCIUIINPUTSOURCE InputSource(CBYTE = 0) const;
		VIRTUAL RIUIINPUTSOURCE InputSource(CBYTE = 0);

		VIRTUAL CBOOL AddInputSource(RIUIINPUTSOURCE);

		VIRTUAL VOID RemoveInputSource(CBYTE);
		VIRTUAL VOID RemoveInputSource(RIUIINPUTSOURCE);


		// [IUiNavigationController] IMPLEMENTATION

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();


		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// [__StateEntry] DEFINITION

		STRUCT __StateEntry
		{
			UIACTIONSTATE State = UiActionState::INACTION;
			LONG Timestamp = 0;
		};

		typedef struct __StateEntry STATEENTRY, & RSTATEENTRY;


		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		RIUINAVIGATIONLISTENER _NavListener;

		PPIUIINPUTSOURCE _InputSources = NULL;
		BYTE _InputSourceCount = 0;

		BOOL _ShiftOn = FALSE;
		BOOL _AltOn = FALSE;

		STATEENTRY _PrevStates[MENUI_NUM_STATEFUL_ACTIONS];


		// PROTECTED MEMBER FUNCTION DECLARATIONS

		CUIACTIONSTATE UpdateState(CUIACTIONTYPE, CUIACTIONSTATE);
		CUIACTIONSTATE ApplyShiftAltFlags(CUIACTIONSTATE);
	};

#pragma endregion
};

#endif
