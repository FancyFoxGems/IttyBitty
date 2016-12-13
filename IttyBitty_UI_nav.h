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


#pragma region DISPLAY ADAPTER OPTIONS/CONSTANTS

// [SerialUiRenderer] default options

#define MENUI_NAV_SERIAL_MENU_ITEM_GLYPH			'-'
#define MENUI_NAV_SERIAL_LIST_CHOICE_GLYPH			'*'
#define MENUI_NAV_SERIAL_CURR_ITEM_GLYPH			'>'
#define MENUI_NAV_SERIAL_SELECTION_GLYPH			'X'
#define MENUI_NAV_SERIAL_MULTI_SELECTION_GLYPH		'+'

#define MENUI_NAV_SERIAL_STYLED_LINE_LEFT_GLYPH		'<'
#define MENUI_NAV_SERIAL_STYLED_LINE_RIGHT_GLYPH	'>'

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IUiNavigationListener;
	TYPEDEF_CLASS_ALIASES(IUiNavigationListener, IUINAVIGATIONLISTENER);

	interface IUiInputSource;
	TYPEDEF_CLASS_ALIASES(IUiInputSource, IUIINPUTSOURCE);

	class UiInputSourceBase;
	TYPEDEF_CLASS_ALIASES(UiInputSourceBase, UIINPUTSOURCEBASE);

	class UiNavigationController;
	TYPEDEF_CLASS_ALIASES(UiNavigationController, UINAVIGATIONCONTROLLER);

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


#pragma region [UiInputSourceBase] DEFINITION

	CLASS UiInputSourceBase : public IUiInputSource
	{
	public:

		// CONSTRUCTOR

		UiInputSourceBase(PIUINAVIGATIONLISTENER);


		// [IUiListener] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// INSTANCE VARIABLES

		PIUINAVIGATIONLISTENER _NavListener = NULL;
	};

#pragma endregion


#pragma region [UiNavigationController] DEFINITION

	class UiNavigationController : public IUiInputSource, public IUiNavigationListener
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		UiNavigationController(PIUINAVIGATIONLISTENER, CBYTE = 0, PPIUIINPUTSOURCE = NULL);
		UiNavigationController(PIUINAVIGATIONLISTENER, RIUIINPUTSOURCE);

		VIRTUAL ~UiNavigationController();


		// OPERATORS

		PCIUIINPUTSOURCE operator[](CBYTE) const;
		PIUIINPUTSOURCE operator[](CBYTE);


		// ACCESSORS

		CBYTE InputSourceCount() const;

		RCIUIINPUTSOURCE InputSource(CBYTE = 0) const;
		RIUIINPUTSOURCE InputSource(CBYTE = 0);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


		// [IUiNavigationInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();

		VIRTUAL VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


	protected:

		// INSTANCE VARIABLES

		PIUINAVIGATIONLISTENER _NavListener = NULL;

		PPIUIINPUTSOURCE _InputSources = NULL;
		BYTE _InputSourceCount = 0;

		BOOL _ShiftOn = FALSE;
		BOOL _AltOn = FALSE;
	};

#pragma endregion
};

#endif
