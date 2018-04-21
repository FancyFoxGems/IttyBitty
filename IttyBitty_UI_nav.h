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


	class UiInputSource;
	TYPEDEF_CLASS_ALIASES(UiInputSource, UIINPUTSOURCE);

	interface IUiNavigationListener;
	TYPEDEF_CLASS_ALIASES(IUiNavigationListener, IUINAVIGATIONLISTENER);

	class UiNavigationController;
	TYPEDEF_CLASS_ALIASES(UiNavigationController, UINAVIGATIONCONTROLLER);

#pragma endregion


#pragma region [IUiInputSource] DEFINITION

	INTERFACE IUiInputSource
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiInputSource() { }


		// ACCESSORS

		VIRTUAL CBOOL IsAsynchronous() const = 0;


		// INTERFACE METHODS

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

		VIRTUAL VOID Up(CUIACTIONSTATE = CLICK) = 0;
		VIRTUAL VOID Down(CUIACTIONSTATE = CLICK) = 0;
		VIRTUAL VOID Left(CUIACTIONSTATE = CLICK) = 0;
		VIRTUAL VOID Right(CUIACTIONSTATE = CLICK) = 0;
		VIRTUAL VOID Return(CUIACTIONSTATE = CLICK) = 0;
		VIRTUAL VOID Select(CUIACTIONSTATE = CLICK) = 0;


	protected:

		IUiNavigationListener() { }
	};

#pragma endregion


#pragma region [IUiNavigationController] DEFINITION

	INTERFACE IUiNavigationController
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiNavigationController() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE InputSourceCount() const = 0;

		VIRTUAL RCIUIINPUTSOURCE InputSource(CBYTE = 0) const = 0;
		VIRTUAL RIUIINPUTSOURCE InputSource(CBYTE = 0) = 0;

		VIRTUAL CBOOL AddInputSource(RIUIINPUTSOURCE) = 0;

		VIRTUAL VOID RemoveInputSource(CBYTE) = 0;
		VIRTUAL VOID RemoveInputSource(RIUIINPUTSOURCE) = 0;


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL IsShiftOn() const = 0;
		VIRTUAL VOID ToggleShift() = 0;
		VIRTUAL VOID ShiftOn() = 0;
		VIRTUAL VOID ShiftOff() = 0;

		VIRTUAL CBOOL IsAltOn() const = 0;
		VIRTUAL VOID ToggleAlt() = 0;
		VIRTUAL VOID AltOn() = 0;
		VIRTUAL VOID AltOff() = 0;

		VIRTUAL VOID FireAction(CUIACTION, CUIACTIONSTATE = CLICK) = 0;


	protected:

		// PROTECTED INTERFACE METHOD

		CUIACTIONSTATE UpdateState(CUIACTIONTYPE, CUIACTIONSTATE);


		IUiNavigationController() { }
	};

#pragma endregion


#pragma region [UiInputSource] DEFINITION

	CLASS UiInputSource : public IUiInputSource
	{
	public:

		// CONSTRUCTOR

		UiInputSource(RIUINAVIGATIONCONTROLLER);


		// [IUiListener] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// INSTANCE VARIABLES

		RIUINAVIGATIONCONTROLLER const _Navigation;
	};

#pragma endregion


#pragma region [UiNavigationController] DEFINITION

	class UiNavigationController : public IUiNavigationController, public IUiNavigationListener, public IUiInputSource
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


		// [IUiNavigationController] IMPLEMENTATION

		VIRTUAL CBYTE InputSourceCount() const;

		VIRTUAL RCIUIINPUTSOURCE InputSource(CBYTE = 0) const;
		VIRTUAL RIUIINPUTSOURCE InputSource(CBYTE = 0);

		VIRTUAL CBOOL AddInputSource(RIUIINPUTSOURCE);

		VIRTUAL VOID RemoveInputSource(CBYTE);
		VIRTUAL VOID RemoveInputSource(RIUIINPUTSOURCE);

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();

		VIRTUAL VOID FireAction(CUIACTION, CUIACTIONSTATE = CLICK);


		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL VOID Up(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = CLICK);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// [__StateEntry] DEFINITION

		STRUCT __StateEntry
		{
			UIACTIONSTATE State = INACTION;
			LONG Timestamp = 0;
		};

		typedef struct __StateEntry STATEENTRY, & RSTATEENTRY;


		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		RIUINAVIGATIONLISTENER const _NavListener;

		PPIUIINPUTSOURCE _InputSources = NULL;
		BYTE _InputSourceCount = 0;

		BOOL _ShiftOn = FALSE;
		BOOL _AltOn = FALSE;

		STATEENTRY _PrevStates[MENUI_NUM_STATEFUL_ACTIONS];


		// PROTECTED INTERFACE METHOD

		CUIACTIONSTATE UpdateState(CUIACTIONTYPE, CUIACTIONSTATE);


		// PROTECTED HELPER MEMBER FUNCTION DECLARATIONS

		CUIACTIONSTATE ApplyShiftAltFlags(CUIACTIONSTATE);
	};

#pragma endregion
};

#endif
