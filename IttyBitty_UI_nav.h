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
// !TODO: set position

// SUPRESS COMPILER WARNINGS RELATED TO PARAM REORDERING
IGNORE_WARNING(reorder)


#pragma region DEFINES

#define UI_INPUT_VALUE_BUFFER_SIZE		256

#pragma endregion


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


#pragma region ENUMS

	#define MENUI_NUM_STATEFUL_ACTIONS		0x6

	ENUM UiActionType : BYTE
	{
		ACTION_UP		= 0x0,
		ACTION_DOWN		= 0x1,
		ACTION_LEFT		= 0x2,
		ACTION_RIGHT	= 0x3,
		ACTION_RETURN	= 0x4,
		ACTION_SELECT	= 0x5,
		ACTION_SHIFT	= 0x6,
		ACTION_ALT		= 0x7
	};

	DECLARE_ENUM_AS_FLAGS(UiActionType, UIACTIONTYPE);

	ENUM UiActionBehavior : BYTE
	{
		ACTION_LATCH		= 0x00,
		ACTION_STATEFUL		= 0x10
	};

	DECLARE_ENUM_AS_FLAGS(UiActionBehavior, UIACTIONBEHAVIOR);

	ENUM_CLASS UiAction : BYTE
	{
		UP		= ACTION_UP | ACTION_STATEFUL,
		DOWN	= ACTION_DOWN | ACTION_STATEFUL,
		LEFT	= ACTION_LEFT | ACTION_STATEFUL,
		RIGHT	= ACTION_RIGHT | ACTION_STATEFUL,
		RETURN	= ACTION_RETURN | ACTION_STATEFUL,
		SELECT	= ACTION_SELECT | ACTION_STATEFUL,
		SHIFT	= ACTION_SHIFT | ACTION_LATCH,
		ALT		= ACTION_ALT | ACTION_LATCH
	};

	TYPEDEF_ENUM_ALIASES(UiAction, UIACTION);

	INLINE CBOOL UiActionIsStateful(CUIACTION action)
	{
		return static_cast<CBOOL>(HIGH_NYBBLE((CBYTE)action));
	}

	INLINE CUIACTIONTYPE UiActionToActionType(CUIACTION action)
	{
		return static_cast<CUIACTIONTYPE>(LOW_NYBBLE((CBYTE)action));
	}


	ENUM UiActionState : BYTE
	{
		INACTION		= 0x00,
		PRESSED			= 0x01,
		RELEASED		= 0x02,
		CLICK			= 0x04 | RELEASED,
		DOUBLE_CLICK	= 0x08 | CLICK,
		HELD			= 0x10 | PRESSED,
		SHIFT_ON		= 0x20,
		ALT_ON			= 0x40,

		SHIFT_CLICK			= CLICK | SHIFT_ON,
		ALT_CLICK			= CLICK | ALT_ON,
		SHIFT_ALT_CLICK		= CLICK | SHIFT_ON | ALT_ON,
		SHIFT_DOUBLE		= DOUBLE_CLICK | SHIFT_ON,
		ALT_DOUBLE			= DOUBLE_CLICK | ALT_ON,
		SHIFT_ALT_DOUBLE	= DOUBLE_CLICK | SHIFT_ON | ALT_ON,
		SHIFT_HELD			= HELD | SHIFT_ON,
		ALT_HELD			= HELD | ALT_ON,
		SHIFT_ALT_HELD		= HELD | SHIFT_ON | ALT_ON
	};

	DECLARE_ENUM_AS_FLAGS(UiActionState, UIACTIONSTATE);

	INLINE CBOOL UiActionStateIsPressed(CUIACTIONSTATE state)
	{
		return UiActionStateHas(state, PRESSED);
	}

	INLINE CBOOL UiActionStateIsShiftOn(CUIACTIONSTATE state)
	{
		return UiActionStateHas(state, SHIFT_ON);
	}

	INLINE CBOOL UiActionStateIsAltOn(CUIACTIONSTATE state)
	{
		return UiActionStateHas(state, ALT_ON);
	}

	INLINE CBOOL UiActionStateIsShiftAltOn(CUIACTIONSTATE state)
	{
		return UiActionStateHas(state, static_cast<CUIACTIONSTATE>(BOR(SHIFT_ON, ALT_ON)));
	}


	ENUM UiBoolValueFlags : BYTE
	{
		BOOL_VALUE_NONEMPTY	= 0x1,
		BOOL_VALUE_0_1		= 0x2,
		BOOL_VALUE_T_F		= 0x4,
		BOOL_VALUE_Y_N		= 0x8
	};

	DECLARE_ENUM_AS_FLAGS(UiBoolValueFlags, UIBOOLVALUEFLAGS);

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

		VIRTUAL VOID Value(CBYTE) = 0;


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

		VIRTUAL CBYTE ValueEntryCount() const = 0;

		VIRTUAL VOID RemoveValueEntry(CBYTE) = 0;
		VIRTUAL VOID ClearValueEntriesOlderThan(CDWORD) = 0;
		VIRTUAL VOID ClearValueEntries() = 0;

		VIRTUAL CBOOL IsShiftOn() const = 0;
		VIRTUAL VOID ToggleShift() = 0;
		VIRTUAL VOID ShiftOn() = 0;
		VIRTUAL VOID ShiftOff() = 0;

		VIRTUAL CBOOL IsAltOn() const = 0;
		VIRTUAL VOID ToggleAlt() = 0;
		VIRTUAL VOID AltOn() = 0;
		VIRTUAL VOID AltOff() = 0;


		// INTERFACE METHODS

		VIRTUAL VOID FireAction(CUIACTION, CUIACTIONSTATE = CLICK) = 0;
		VIRTUAL VOID SendValue(PCCHAR) = 0;

		// TODO: Separate below methods into separate interface?
		// TODO: Type erasure to templated?
		VIRTUAL CBOOL ReadValueAsBool(CBYTE, CUIBOOLVALUEFLAGS = BOOL_VALUE_T_F) = 0;
		VIRTUAL CBYTE ReadValueAsByte(CBYTE) = 0;
		VIRTUAL CCHAR ReadValueAsChar(CBYTE) = 0;
		VIRTUAL CWCHAR ReadValueAsWChar(CBYTE) = 0;
		VIRTUAL CWORD ReadValueAsWord(CBYTE) = 0;
		VIRTUAL CSHORT ReadValueAsShort(CBYTE) = 0;
		VIRTUAL CDWORD ReadValueAsDWord(CBYTE) = 0;
		VIRTUAL CLONG ReadValueAsLong(CBYTE) = 0;
		VIRTUAL PCBYTE ReadValueAsBinary(CBYTE) = 0;
		VIRTUAL PCCHAR ReadValueAsString(CBYTE) = 0;


	protected:

		// PROTECTED INTERFACE METHODS

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

		UiNavigationController(RIUINAVIGATIONLISTENER, DWORD = 0, CBYTE = 0, PPIUIINPUTSOURCE = NULL);

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

		VIRTUAL CBYTE ValueEntryCount() const;

		VIRTUAL VOID RemoveValueEntry(CBYTE);
		VIRTUAL VOID ClearValueEntriesOlderThan(CDWORD);
		VIRTUAL VOID ClearValueEntries();

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();

		VIRTUAL VOID FireAction(CUIACTION, CUIACTIONSTATE = CLICK);
		VIRTUAL VOID SendValue(PCCHAR);

		VIRTUAL CBOOL ReadValueAsBool(CBYTE, CUIBOOLVALUEFLAGS = BOOL_VALUE_T_F);
		VIRTUAL CBYTE ReadValueAsByte(CBYTE);
		VIRTUAL CCHAR ReadValueAsChar(CBYTE);
		VIRTUAL CWCHAR ReadValueAsWChar(CBYTE);
		VIRTUAL CWORD ReadValueAsWord(CBYTE);
		VIRTUAL CSHORT ReadValueAsShort(CBYTE);
		VIRTUAL CDWORD ReadValueAsDWord(CBYTE);
		VIRTUAL CLONG ReadValueAsLong(CBYTE);
		VIRTUAL PCBYTE ReadValueAsBinary(CBYTE);
		VIRTUAL PCCHAR ReadValueAsString(CBYTE);


		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL VOID Up(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = CLICK);

		VIRTUAL VOID Value(CBYTE);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


	protected:

		// [__TimestampedEntry] DEFINITION

		STRUCT __TimestampedEntry
		{
			DWORD Timestamp = 0;
		};
		

		// [__ValueEntry] DEFINITION : public __TimestampedEntry

		STRUCT __ValueEntry : public __TimestampedEntry
		{
			BYTE Token = 0;
			PCCHAR Buffer = NULL;
		};

		typedef struct __ValueEntry VALUEENTRY, * PVALUEENTRY, ** PPVALUEENTRY;


		// [__StateEntry] DEFINITION

		STRUCT __StateEntry : public __TimestampedEntry
		{
			UIACTIONSTATE State = INACTION;
		};

		typedef struct __StateEntry STATEENTRY, & RSTATEENTRY;


		// INSTANCE VARIABLES

		BOOL _DisposeInputSources = FALSE;

		RIUINAVIGATIONLISTENER const _NavListener;

		DWORD _ValueEntryExpirationMs = 0;

		PPIUIINPUTSOURCE _InputSources = NULL;
		BYTE _InputSourceCount = 0;

		PPVALUEENTRY _ValueEntries = NULL;
		BYTE _ValueEntryCount = 0;
		BYTE _NextValueEntryToken = 0;

		BOOL _ShiftOn = FALSE;
		BOOL _AltOn = FALSE;

		STATEENTRY _PrevStates[MENUI_NUM_STATEFUL_ACTIONS];


		// PROTECTED INTERFACE METHOD

		CUIACTIONSTATE UpdateState(CUIACTIONTYPE, CUIACTIONSTATE);


		// PROTECTED HELPER MEMBER FUNCTION DECLARATIONS

		CBYTE FindValueEntry(CBYTE, PPVALUEENTRY);
		VOID DeleteValueEntry(CBYTE);
		VOID CompressValueEntries();

		CUIACTIONSTATE ApplyShiftAltFlags(CUIACTIONSTATE);
	};

#pragma endregion
};

#endif
