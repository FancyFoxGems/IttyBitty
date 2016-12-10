/***********************************************************************************************
* [IttyBitty_menui.h]: MENU-BASED UI SYSTEM W/ INPUT FIELDS AND EXTENSIBLE NAVIGATION/DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENUI_H
#define _ITTYBITTY_MENUI_H


#include "IttyBitty_menu_items.h"
#include "IttyBitty_menu_field_decorators.h"


#pragma region MenUI OPTIONS/CONSTANTS

// MenUI DEFAULT OPTIONS

// Behavior/interaction default options

#define MENUI_DEFAULT_SCROLL_WRAP				TRUE
#define MENUI_DEFAULT_SCROLL_HOLD_ROW			MAX_BYTE

#define MENUI_DEFAULT_IDLE_TIMEOUT_TICKS		50


// Navigation/input default options

#define MENUI_DEFAULT_NAV_HOLD_THRESHOLD_MS		800
#define MENUI_DEFAULT_NAV_HOLD_REPEAT_MS		50

#define MENUI_DEFAULT_SELECT_ON_RETURN			FALSE
#define MENUI_DEFAULT_HOLD_SELECT_TO_SELECT		TRUE
#define MENUI_DEFAULT_HOLD_SELECT_TO_RETURN		TRUE


// Rendering/display default options

#define MENUI_DEFAULT_SHOW_CURSOR				TRUE
#define MENUI_DEFAULT_BLINK_CURSOR				TRUE
#define MENUI_DEFAULT_WRAP_LABELS				FALSE

#define MENUI_DEFAULT_MENU_LAYOUT				UiLayout::VERTICAL_1_COL
#define MENUI_DEFAULT_LIST_LAYOUT				UiLayout::HORIZONTAL_AUTO

#define MENUI_DEFAULT_MENU_STATUS_INDICATOR		UiStatusIndicatorFlags::UI_STATUS_SCROLLBAR
#define MENUI_DEFAULT_LIST_STATUS_INDICATOR		UiStatusIndicatorFlags::UI_STATUS_SCROLLBAR

#define MENUI_DEFAULT_ITEM_MARGIN				0
#define MENUI_DEFAULT_LIST_SPACING				1
#define MENUI_DEFAULT_SELECTION_GLYPH_OFFSET	0

#define MENUI_DEFAULT_MENU_ITEM_GLYPH			LCD_SYMBOL_BULLET
#define MENUI_DEFAULT_LIST_CHOICE_GLYPH			LCD_SYMBOL_BULLET
#define MENUI_DEFAULT_CURR_ITEM_GLYPH			LCD_SYMBOL_FORWARD
#define MENUI_DEFAULT_SELECTION_GLYPH			LCD_SYMBOL_FORWARD
#define MENUI_DEFAULT_MULTI_SELECTION_GLYPH		LCD_SYMBOL_FORWARD

#define MENUI_DEFAULT_HIGHLIGHT_SELECTIONS		FALSE



// MenUI CONSTANTS

#define MENUI_DEFAULT_MENU_CAPACITY				5


// GENERAL CONSTANTS

#define MENUI_IDLE_TICK_MS						100

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	struct _UiOptions;
	TYPEDEF_STRUCT_ALIASES(UiOptions, uioptions, UIOPTIONS);

	class MenUI;
	TYPEDEF_CLASS_ALIASES(MenUI, MENUI);

#pragma endregion


#pragma region [UiOptions] DEFINITION

	STRUCT _UiOptions final
	{
	public:

		// PUBLIC INSTANCE VARIABLES

		// Behavior/interaction options

		BOOL ScrollWrap				= MENUI_DEFAULT_SCROLL_WRAP;
		BYTE ScrollHoldRow			= MENUI_DEFAULT_SCROLL_HOLD_ROW;

		WORD IdleTimeoutTicks		= MENUI_DEFAULT_IDLE_TIMEOUT_TICKS;


		// Navigation/input options

		BOOL NavHoldThresholdMS		= MENUI_DEFAULT_NAV_HOLD_THRESHOLD_MS;
		BOOL NavHoldRepeatMS		= MENUI_DEFAULT_NAV_HOLD_REPEAT_MS;

		BOOL SelectOnReturn			= MENUI_DEFAULT_SELECT_ON_RETURN;
		BOOL HoldSelectToSelect		= MENUI_DEFAULT_HOLD_SELECT_TO_SELECT;
		BOOL HoldSelectToReturn		= MENUI_DEFAULT_HOLD_SELECT_TO_RETURN;


		// Display/rendering options

		BOOL ShowCursor				= MENUI_DEFAULT_SHOW_CURSOR;
		BOOL BlinkCursor			= MENUI_DEFAULT_BLINK_CURSOR;
		BOOL WrapLabels				= MENUI_DEFAULT_WRAP_LABELS;

		UILAYOUT MenuLayout			= MENUI_DEFAULT_MENU_LAYOUT;
		UILAYOUT ListLayout			= MENUI_DEFAULT_LIST_LAYOUT;

		BOOL MenuStatusIndicator	= MENUI_DEFAULT_MENU_STATUS_INDICATOR;
		BOOL ListStatusIndicator	= MENUI_DEFAULT_LIST_STATUS_INDICATOR;

		BYTE ItemMargin				= MENUI_DEFAULT_ITEM_MARGIN;
		BYTE ListSpacing			= MENUI_DEFAULT_LIST_SPACING;
		BYTE SelectionGlyphOffset	= MENUI_DEFAULT_SELECTION_GLYPH_OFFSET;

		CHAR MenuItemGlyph			= MENUI_DEFAULT_MENU_ITEM_GLYPH;
		CHAR ListChoiceGlyph		= MENUI_DEFAULT_LIST_CHOICE_GLYPH;
		CHAR CurrItemGlyph			= MENUI_DEFAULT_CURR_ITEM_GLYPH;
		CHAR SelectionGlyph			= MENUI_DEFAULT_SELECTION_GLYPH;
		CHAR MultiSelectionGlyph	= MENUI_DEFAULT_MULTI_SELECTION_GLYPH;

		BOOL HighlightSelections UNUSED	= MENUI_DEFAULT_HIGHLIGHT_SELECTIONS;
	};

#pragma endregion


#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

	EXTERN UIOPTIONS MenUIOptions;

#pragma endregion


#pragma region [MenUI] DEFINITION

	typedef VOID CustomUiCallback(RMENUI, PTR, CPTR),
		CUSTOMUICALLBACK(RMENUI, PTR, CPTR), (*PCUSTOMUICALLBACK)(RMENUI, PTR, CPTR);

	CLASS MenUI : public Menu
	{
	public:

		// PUBLIC [UiOptions] MEMBER

		RUIOPTIONS Options = IttyBitty::MenUIOptions;


		// CONSTRUCTORS/DESTRUCTOR

		MenUI(CBYTE cols, CBYTE rows, PPCIMENUITEM menuHierarchy, CBOOL useGlobalOptions = TRUE);
		MenUI(CBYTE cols, CBYTE rows,
			CBYTE initMenuCapacity = MENUI_DEFAULT_MENU_CAPACITY, CBOOL useGlobalOptions = TRUE);


		template<typename T>
		CONST T Prompt(RCIUIFIELD field)
		{
			return T(0);
		}



	protected:

		// INSTANCE VARIABLES

	};

#pragma endregion
};

#endif
