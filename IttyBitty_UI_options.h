/***********************************************************************************************
* [IttyBitty_menui.h]: MENU-BASED UI SYSTEM W/ INPUT FIELDS AND EXTENSIBLE NAVIGATION/DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_OPTIONS_H
#define _ITTYBITTY_UI_OPTIONS_H


#include "IttyBitty_bits.h"
#include "IttyBitty_LCD_chars.h"
// !TODO: line wrap callback

#pragma region MenUI OPTIONS/CONSTANTS

// [UiOptions] DEFAULT OPTIONS

// Layout & general presentation/interaction default options

#define MENUI_DEFAULT_MENU_LAYOUT					UiLayout::TOP_TO_BOTTOM_JUSTIFIED_AUTO
#define MENUI_DEFAULT_LIST_LAYOUT					UiLayout::LEFT_TO_RIGHT_JUSTIFIED_AUTO

#define MENUI_DEFAULT_MENU_STATUS					UiStatusFlags::UI_STATUS_SCROLLBAR
#define MENUI_DEFAULT_LIST_STATUS					UiStatusFlags::UI_STATUS_SCROLLBAR

#define MENUI_DEFAULT_IDLE_TIMEOUT_TICKS			50


// Scrolling default options

#define MENUI_DEFAULT_SCROLL_BEHAVIOR				UiScrollBehavior::NORMAL
#define MENUI_DEFAULT_SCROLL_WRAP					TRUE

#define MENUI_DEFAULT_SCROLL_AUTO_DELAY_MS			2000
#define MENUI_DEFAULT_SCROLL_HORIZONTAL_MS			500
#define MENUI_DEFAULT_SCROLL_VERTICAL_MS			500


// Input default options

#define MENUI_DEFAULT_DBL_CLICK_THRESHOLD_MS		2000
#define MENUI_DEFAULT_HOLD_THRESHOLD_MS				800
#define MENUI_DEFAULT_HOLD_REPEAT_MS				500


// Navigation default options

#define MENUI_DEFAULT_SET_ON_RETURN					FALSE
#define MENUI_DEFAULT_DBL_CLICK_SELECT_TO_SET		TRUE
#define MENUI_DEFAULT_HOLD_SELECT_TO_SET			TRUE
#define MENUI_DEFAULT_DBL_CLICK_SELECT_TO_ESCAPE	TRUE
#define MENUI_DEFAULT_HOLD_SELECT_TO_ESCAPE			TRUE
#define MENUI_DEFAULT_DBL_CLICK_RETURN_TO_HOME		TRUE
#define MENUI_DEFAULT_HOLD_RETURN_TO_HOME			TRUE


// Display default options

#define MENUI_DEFAULT_SHOW_CURSOR_ON_ENTRY			TRUE
#define MENUI_DEFAULT_BLINK_CURSOR_ON_ENTRY			TRUE

#define MENUI_DEFAULT_LAYOUT_COL_SPACING			1
#define MENUI_DEFAULT_LIST_ITEM_MARGIN				0
#define MENUI_DEFAULT_SELECTION_GLYPH_OFFSET		0

#define MENUI_DEFAULT_HIGHLIGHT_SELECTIONS			FALSE



// [UiRendererOptions] DEFAULT OPTIONS/CONSTANTS

// General renderer-specific default options

#define MENUI_DEFAULT_WRAP_LINES					FALSE
#define MENUI_DEFAULT_STYLED_LINE_MARGINS			1


// Glyph default options for non-LCD-based renderers

#define MENUI_DEFAULT_STYLED_LINE_LEFT_GLYPH		'['
#define MENUI_DEFAULT_STYLED_LINE_RIGHT_GLYPH		']'

#define MENUI_DEFAULT_MENU_ITEM_GLYPH				'-'
#define MENUI_DEFAULT_LIST_CHOICE_GLYPH				'*'
#define MENUI_DEFAULT_CURR_ITEM_GLYPH				'>'
#define MENUI_DEFAULT_SELECTION_GLYPH				'X'
#define MENUI_DEFAULT_MULTI_SELECTION_GLYPH			'+'
#define MENUI_DEFAULT_VALUE_SEPARATOR_GLYPH			':'


// Glyph default options for LCD -based renderers

#define MENUI_DEFAULT_LCD_STYLED_LINE_LEFT_GLYPH	LCD_SYMBOL_BACKWARD
#define MENUI_DEFAULT_LCD_STYLED_LINE_RIGHT_GLYPH	LCD_SYMBOL_FORWARD

#define MENUI_DEFAULT_LCD_MENU_ITEM_GLYPH			LCD_SYMBOL_BULLET
#define MENUI_DEFAULT_LCD_LIST_CHOICE_GLYPH			LCD_SYMBOL_BULLET
#define MENUI_DEFAULT_LCD_CURR_ITEM_GLYPH			LCD_SYMBOL_ARROW_RIGHT
#define MENUI_DEFAULT_LCD_SELECTION_GLYPH			LCD_SYMBOL_TRIANGLE_UP
#define MENUI_DEFAULT_LCD_MULTI_SELECTION_GLYPH		LCD_SYMBOL_MULTIPLICATION
#define MENUI_DEFAULT_LCD_VALUE_SEPARATOR_GLYPH		MENUI_DEFAULT_VALUE_SEPARATOR_GLYPH



// MenUI PARAMETER DEFAULT VALUES

// Text display default values

#define MENUI_DEFAULT_TEXT_TIMEOUT_MS				0
#define MENUI_DEFAULT_TEXT_ALLOW_ESCAPE				TRUE
#define MENUI_DEFAULT_TEXT_ANY_ACTION_RETURNS		TRUE


// Menu/List default values

#define MENUI_DEFAULT_MENU_CAPACITY					5
#define MENUI_DEFAULT_LIST_CAPACITY					5


// Dialog/field default values

#define MENUI_DEFAULT_NUMERIC_FIELD_STEP			1
#define MENUI_DEFAULT_NUMERIC_FIELD_STEP_LARGE		10



// MISCELLANEOUS MenUI CONSTANTS

#define MENUI_IDLE_TICK_MS							100

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	struct _UiOptions;
	TYPEDEF_STRUCT_ALIASES(UiOptions, uioptions, UIOPTIONS);

	struct _UiRendererOptions;
	TYPEDEF_STRUCT_ALIASES(UiRendererOptions, uirendereroptions, UIRENDEREROPTIONS);

#pragma endregion


#pragma region ENUMS

	ENUM UiOrientation : BYTE
	{
		VERTICAL	= 0x00,
		HORIZONTAL	= 0x01
	};

	DECLARE_ENUM_AS_FLAGS(UiOrientation, UIORIENTATION);


	ENUM UiDirection : BYTE
	{
		FORWARD		= 0x00,
		BACKWARD	= 0x02
	};

	DECLARE_ENUM_AS_FLAGS(UiDirection, UIDIRECTION);


	ENUM UiLayoutMode : BYTE
	{
		TOP_TO_BOTTOM	= VERTICAL | FORWARD,
		BOTTOM_TO_TOP	= VERTICAL | BACKWARD,
		LEFT_TO_RIGHT	= HORIZONTAL | FORWARD,
		RIGHT_TO_LEFT	= HORIZONTAL | BACKWARD
	};

	TYPEDEF_ENUM_ALIASES(UiLayoutMode, UILAYOUTMODE);

	#define UI_LAYOUT_MODE_ORIENTATIONL_OFFSET	0x0
	#define UI_LAYOUT_MODE_DIRECTION_OFFSET		0x1

	INLINE CBOOL UiLayoutModeIsHorizontal(CUIORIENTATION orientation)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)orientation, UI_LAYOUT_MODE_ORIENTATIONL_OFFSET));
	}

	INLINE CBOOL UiLayoutModeIsBackward(CUIORIENTATION orientation)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)orientation, UI_LAYOUT_MODE_DIRECTION_OFFSET));
	}
	

	ENUM UiAlignment : BYTE
	{
		EDGE_ALIGNED	= 0x00,
		JUSTIFIED		= 0x04,
		CENTERED		= 0x08
	};

	DECLARE_ENUM_AS_FLAGS(UiAlignment, UIALIGNMENT);


	ENUM UiLayoutCols : BYTE
	{
		COLS_AUTO		= 0x00,
		COLS_1			= 0x10,
		COLS_2			= 0x20,
		COLS_3			= 0x30,
		COLS_4			= 0x40,
		COLS_5			= 0x50,
		COLS_6			= 0x60,
		COLS_7			= 0x70,
		COLS_8			= 0x80
	};

	TYPEDEF_ENUM_ALIASES(UiLayoutCols, UILAYOUTCOLS);


	ENUM_CLASS UiLayout : BYTE
	{
		EDGE_ALIGNED					= TOP_TO_BOTTOM | EDGE_ALIGNED | COLS_1,
		JUSTIFIED_1_COL					= TOP_TO_BOTTOM | JUSTIFIED | COLS_1,
		CENTERED_1_COL					= TOP_TO_BOTTOM | CENTERED | COLS_1,

		TOP_TO_BOTTOM_JUSTIFIED_AUTO	= TOP_TO_BOTTOM | JUSTIFIED | COLS_AUTO,
		TOP_TO_BOTTOM_JUSTIFIED_2_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_2,
		TOP_TO_BOTTOM_JUSTIFIED_3_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_3,
		TOP_TO_BOTTOM_JUSTIFIED_4_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_4,
		TOP_TO_BOTTOM_JUSTIFIED_5_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_5,
		TOP_TO_BOTTOM_JUSTIFIED_6_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_6,
		TOP_TO_BOTTOM_JUSTIFIED_7_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_7,
		TOP_TO_BOTTOM_JUSTIFIED_8_COL	= TOP_TO_BOTTOM | JUSTIFIED | COLS_8,

		TOP_TO_BOTTOM_CENTERED_AUTO		= TOP_TO_BOTTOM | CENTERED | COLS_AUTO,
		TOP_TO_BOTTOM_CENTERED_2_COL	= TOP_TO_BOTTOM | CENTERED | COLS_2,
		TOP_TO_BOTTOM_CENTERED_3_COL	= TOP_TO_BOTTOM | CENTERED | COLS_3,
		TOP_TO_BOTTOM_CENTERED_4_COL	= TOP_TO_BOTTOM | CENTERED | COLS_4,
		TOP_TO_BOTTOM_CENTERED_5_COL	= TOP_TO_BOTTOM | CENTERED | COLS_5,
		TOP_TO_BOTTOM_CENTERED_6_COL	= TOP_TO_BOTTOM | CENTERED | COLS_6,
		TOP_TO_BOTTOM_CENTERED_7_COL	= TOP_TO_BOTTOM | CENTERED | COLS_7,
		TOP_TO_BOTTOM_CENTERED_8_COL	= TOP_TO_BOTTOM | CENTERED | COLS_8,

		LEFT_TO_RIGHT_JUSTIFIED_AUTO	= LEFT_TO_RIGHT | JUSTIFIED | COLS_AUTO,
		LEFT_TO_RIGHT_JUSTIFIED_2_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_2,
		LEFT_TO_RIGHT_JUSTIFIED_3_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_3,
		LEFT_TO_RIGHT_JUSTIFIED_4_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_4,
		LEFT_TO_RIGHT_JUSTIFIED_5_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_5,
		LEFT_TO_RIGHT_JUSTIFIED_6_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_6,
		LEFT_TO_RIGHT_JUSTIFIED_7_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_7,
		LEFT_TO_RIGHT_JUSTIFIED_8_COL	= LEFT_TO_RIGHT | JUSTIFIED | COLS_8,

		LEFT_TO_RIGHT_CENTERED_AUTO		= LEFT_TO_RIGHT | CENTERED | COLS_AUTO,
		LEFT_TO_RIGHT_CENTERED_2_COL	= LEFT_TO_RIGHT | CENTERED | COLS_2,
		LEFT_TO_RIGHT_CENTERED_3_COL	= LEFT_TO_RIGHT | CENTERED | COLS_3,
		LEFT_TO_RIGHT_CENTERED_4_COL	= LEFT_TO_RIGHT | CENTERED | COLS_4,
		LEFT_TO_RIGHT_CENTERED_5_COL	= LEFT_TO_RIGHT | CENTERED | COLS_5,
		LEFT_TO_RIGHT_CENTERED_6_COL	= LEFT_TO_RIGHT | CENTERED | COLS_6,
		LEFT_TO_RIGHT_CENTERED_7_COL	= LEFT_TO_RIGHT | CENTERED | COLS_7,
		LEFT_TO_RIGHT_CENTERED_8_COL	= LEFT_TO_RIGHT | CENTERED | COLS_8,
		
		BOTTOM_TO_TOP_EDGE_ALIGNED		= BOTTOM_TO_TOP | EDGE_ALIGNED | COLS_1,
		BOTTOM_TO_TOP_JUSTIFIED_1_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_1,
		BOTTOM_TO_TOP_CENTERED_1_COL	= BOTTOM_TO_TOP | CENTERED | COLS_1,

		BOTTOM_TO_TOP_JUSTIFIED_AUTO	= BOTTOM_TO_TOP | JUSTIFIED | COLS_AUTO,
		BOTTOM_TO_TOP_JUSTIFIED_2_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_2,
		BOTTOM_TO_TOP_JUSTIFIED_3_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_3,
		BOTTOM_TO_TOP_JUSTIFIED_4_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_4,
		BOTTOM_TO_TOP_JUSTIFIED_5_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_5,
		BOTTOM_TO_TOP_JUSTIFIED_6_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_6,
		BOTTOM_TO_TOP_JUSTIFIED_7_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_7,
		BOTTOM_TO_TOP_JUSTIFIED_8_COL	= BOTTOM_TO_TOP | JUSTIFIED | COLS_8,

		BOTTOM_TO_TOP_CENTERED_AUTO		= BOTTOM_TO_TOP | CENTERED | COLS_AUTO,
		BOTTOM_TO_TOP_CENTERED_2_COL	= BOTTOM_TO_TOP | CENTERED | COLS_2,
		BOTTOM_TO_TOP_CENTERED_3_COL	= BOTTOM_TO_TOP | CENTERED | COLS_3,
		BOTTOM_TO_TOP_CENTERED_4_COL	= BOTTOM_TO_TOP | CENTERED | COLS_4,
		BOTTOM_TO_TOP_CENTERED_5_COL	= BOTTOM_TO_TOP | CENTERED | COLS_5,
		BOTTOM_TO_TOP_CENTERED_6_COL	= BOTTOM_TO_TOP | CENTERED | COLS_6,
		BOTTOM_TO_TOP_CENTERED_7_COL	= BOTTOM_TO_TOP | CENTERED | COLS_7,
		BOTTOM_TO_TOP_CENTERED_8_COL	= BOTTOM_TO_TOP | CENTERED | COLS_8,

		RIGHT_TO_LEFT_JUSTIFIED_AUTO	= RIGHT_TO_LEFT | JUSTIFIED | COLS_AUTO,
		RIGHT_TO_LEFT_JUSTIFIED_2_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_2,
		RIGHT_TO_LEFT_JUSTIFIED_3_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_3,
		RIGHT_TO_LEFT_JUSTIFIED_4_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_4,
		RIGHT_TO_LEFT_JUSTIFIED_5_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_5,
		RIGHT_TO_LEFT_JUSTIFIED_6_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_6,
		RIGHT_TO_LEFT_JUSTIFIED_7_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_7,
		RIGHT_TO_LEFT_JUSTIFIED_8_COL	= RIGHT_TO_LEFT | JUSTIFIED | COLS_8,

		RIGHT_TO_LEFT_CENTERED_AUTO		= RIGHT_TO_LEFT | CENTERED | COLS_AUTO,
		RIGHT_TO_LEFT_CENTERED_2_COL	= RIGHT_TO_LEFT | CENTERED | COLS_2,
		RIGHT_TO_LEFT_CENTERED_3_COL	= RIGHT_TO_LEFT | CENTERED | COLS_3,
		RIGHT_TO_LEFT_CENTERED_4_COL	= RIGHT_TO_LEFT | CENTERED | COLS_4,
		RIGHT_TO_LEFT_CENTERED_5_COL	= RIGHT_TO_LEFT | CENTERED | COLS_5,
		RIGHT_TO_LEFT_CENTERED_6_COL	= RIGHT_TO_LEFT | CENTERED | COLS_6,
		RIGHT_TO_LEFT_CENTERED_7_COL	= RIGHT_TO_LEFT | CENTERED | COLS_7,
		RIGHT_TO_LEFT_CENTERED_8_COL	= RIGHT_TO_LEFT | CENTERED | COLS_8
	};

	TYPEDEF_ENUM_ALIASES(UiLayout, UILAYOUT);
	
	#define UI_LAYOUT_MODE_OFFSET			0x0
	#define UI_LAYOUT_MODE_BIT_SIZE			2
	#define UI_LAYOUT_ORIENTATION_OFFSET	UI_LAYOUT_MODE_OFFSET
	#define UI_LAYOUT_DIRECTION_OFFSET		0x1
	#define UI_LAYOUT_ALIGNMENT_OFFSET		0x2
	#define UI_LAYOUT_ALIGNMENT_BIT_SIZE	2

	INLINE CUILAYOUTMODE UiLayoutToLayoutMode(CUILAYOUT layout)
	{
		return static_cast<CUILAYOUTMODE>(BYTE_RANGE((CBYTE)layout, UI_LAYOUT_MODE_OFFSET, UI_LAYOUT_MODE_BIT_SIZE));
	}

	INLINE CBOOL UiLayoutIsHorizontal(CUILAYOUT layout)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)layout, UI_LAYOUT_ORIENTATION_OFFSET));
	}

	INLINE CBOOL UiLayoutIsBackward(CUILAYOUT layout)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)layout, UI_LAYOUT_DIRECTION_OFFSET));
	}

	INLINE CUIALIGNMENT UiLayoutToAlignment(CUILAYOUT layout)
	{
		return static_cast<CUIALIGNMENT>(BYTE_RANGE((CBYTE)layout, UI_LAYOUT_ALIGNMENT_OFFSET, UI_LAYOUT_ALIGNMENT_BIT_SIZE));
	}

	INLINE CBYTE UiLayoutToNumCols(CUILAYOUT layout)
	{
		return HIGH_NYBBLE((CBYTE)layout);
	}


	ENUM UiStatusFlags : BYTE
	{
		UI_STATUS_NONE				= 0x0,
		UI_STATUS_SCROLLBAR			= 0x1,
		UI_STATUS_ITEM_INDEX		= 0x2,
		UI_STATUS_PAGE_INDEX		= 0x4,
		UI_STATUS_SHOW_TOTAL		= 0x8
	};

	DECLARE_ENUM_AS_FLAGS(UiStatusFlags, UISTATUSFLAGS);


	ENUM_CLASS UiScrollBehavior : BYTE
	{
		NORMAL			= 0x0,
		PAGED			= 0x1,
		STICKY_TOP		= 0x2,
		STICKY_MIDDLE	= 0x4,
		STICKY_BOTTOM	= 0x8
	};

	TYPEDEF_ENUM_ALIASES(UiScrollBehavior, UISCROLLBEHAVIOR);

#pragma endregion


#pragma region [_UiOptions] DEFINITION

	STRUCT _UiOptions final
	{
		// PUBLIC INSTANCE VARIABLES

		// Layout & general presentation/interaction options

		UILAYOUT MenuLayout						= MENUI_DEFAULT_MENU_LAYOUT;
		UILAYOUT ListLayout						= MENUI_DEFAULT_LIST_LAYOUT;

		UISTATUSFLAGS MenuStatus				= MENUI_DEFAULT_MENU_STATUS;
		UISTATUSFLAGS ListStatus				= MENUI_DEFAULT_LIST_STATUS;

		WORD IdleTimeoutTicks					= MENUI_DEFAULT_IDLE_TIMEOUT_TICKS;


		// Scrolling options

		STRUCT
		{
			UISCROLLBEHAVIOR Behavior			= MENUI_DEFAULT_SCROLL_BEHAVIOR;
			BOOL Wrap							= MENUI_DEFAULT_SCROLL_WRAP;
			WORD AutoDelayMS					= MENUI_DEFAULT_SCROLL_AUTO_DELAY_MS;
			WORD HorizontalMS					= MENUI_DEFAULT_SCROLL_HORIZONTAL_MS;
			WORD VerticalMS						= MENUI_DEFAULT_SCROLL_VERTICAL_MS;
		}
		Scrolling;


		// Input options


		STRUCT _UiInputOptions
		{
			WORD DblClickThresholdMS			= MENUI_DEFAULT_DBL_CLICK_THRESHOLD_MS;
			WORD HoldThresholdMS				= MENUI_DEFAULT_HOLD_THRESHOLD_MS;
			WORD HoldRepeatMS					= MENUI_DEFAULT_HOLD_REPEAT_MS;
			
			DWORD ValueEntryExpirationMs		= 0;
			BOOL RemoveValueEntriesUponReading	= TRUE;
		}
		Input;


		// Navigation options

		STRUCT
		{
			BOOL SetOnReturn					= MENUI_DEFAULT_SET_ON_RETURN;
			BOOL DblClickSelectToSet			= MENUI_DEFAULT_DBL_CLICK_SELECT_TO_SET;
			BOOL HoldSelectToSet				= MENUI_DEFAULT_HOLD_SELECT_TO_SET;
			BOOL DblClickSelectToEscape			= MENUI_DEFAULT_DBL_CLICK_SELECT_TO_ESCAPE;
			BOOL HoldSelectToEscape				= MENUI_DEFAULT_HOLD_SELECT_TO_ESCAPE;
			BOOL DblClickReturnToEscape			= MENUI_DEFAULT_DBL_CLICK_RETURN_TO_HOME;
			BOOL HoldReturnToHome				= MENUI_DEFAULT_HOLD_RETURN_TO_HOME;
		}
		Navigation;


		// Display options

		STRUCT
		{
			BOOL ShowCursorOnEntry				= MENUI_DEFAULT_SHOW_CURSOR_ON_ENTRY;
			BOOL BlinkCursorOnEntry				= MENUI_DEFAULT_BLINK_CURSOR_ON_ENTRY;

			BYTE LayoutColSpacing				= MENUI_DEFAULT_LAYOUT_COL_SPACING;
			BYTE ListItemMargin					= MENUI_DEFAULT_LIST_ITEM_MARGIN;
			BYTE SelectionGlyphOffset			= MENUI_DEFAULT_SELECTION_GLYPH_OFFSET;

			BOOL HighlightSelections UNUSED		= MENUI_DEFAULT_HIGHLIGHT_SELECTIONS;
		}
		Display;
	};

#pragma endregion



#pragma region [_UiRendererOptions] DEFINITION

	STRUCT _UiRendererOptions final
	{
	public:

		// PUBLIC INSTANCE VARIABLES

		// General renderer-specific options

		BOOL WrapLines				= MENUI_DEFAULT_WRAP_LINES;
		BYTE StyledLineMargins		= MENUI_DEFAULT_STYLED_LINE_MARGINS;


		// Glyph options

		CHAR StyledLineLeftGlyph	= MENUI_DEFAULT_STYLED_LINE_LEFT_GLYPH;
		CHAR StyledLineRightGlyph	= MENUI_DEFAULT_STYLED_LINE_RIGHT_GLYPH;

		CHAR MenuItemGlyph			= MENUI_DEFAULT_MENU_ITEM_GLYPH;
		CHAR ListChoiceGlyph		= MENUI_DEFAULT_LIST_CHOICE_GLYPH;
		CHAR CurrItemGlyph			= MENUI_DEFAULT_CURR_ITEM_GLYPH;
		CHAR SelectionGlyph			= MENUI_DEFAULT_SELECTION_GLYPH;
		CHAR MultiSelectionGlyph	= MENUI_DEFAULT_MULTI_SELECTION_GLYPH;
		CHAR ValueSeparatorGlyph	= MENUI_DEFAULT_VALUE_SEPARATOR_GLYPH;
	};

#pragma endregion


#pragma region GLOBAL VARIABLE & FUNCTION DECLARATIONS

	namespace MUI
	{
		EXTERN UIOPTIONS Options;

		EXTERN RCUIRENDEREROPTIONS DefaultRendererOptions();
		EXTERN RCUIRENDEREROPTIONS DefaultLcdRendererOptions();
	}

#pragma endregion
};

#endif
