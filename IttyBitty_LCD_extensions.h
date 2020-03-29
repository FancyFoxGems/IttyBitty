/***********************************************************************************************
* [IttyBitty_LCD_extensions.h]: EXTENDED FUNCTIONALITY FOR I2C-DRIVEN HD44780-COMPATIBLE
* 	LCD DISPLAYS, SUCH AS CHARACTER MANIPULATION, SCROLL BARS, GRAPHS, AND SLIDERS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_EXTENSIONS_H
#define _ITTYBITTY_LCD_EXTENSIONS_H


#include "IttyBitty_LCD_I2C.h"


#pragma region DEFINES

// LCD SCROLL BAR CHARACTER OPTIONS/CONSTANTS

#define LCD_SCROLLER_WIDTH_PIXELS		3
#define LCD_SCROLLER_PIXEL_ROW			B(LCD_SCROLLER_WIDTH_PIXELS + 1) - 1


// LCD GRAPH & SLIDER CELL PIXEL DATA

#define LCD_CELL_MIDDLE_PIXEL_ROW		(CHAR_HEIGHT() / 2 + 1)
#define LCD_CELL_LAST_PIXEL_ROW			(CHAR_HEIGHT() - 1)

#define LCD_CELL_BLANK_PIXEL_ROW		0x0
#define LCD_CELL_LINE_PIXEL_ROW			0x1F
#define LCD_CELL_DOTS_PIXEL_ROW			0x15
#define LCD_CELL_DOTS_SPARSE_PIXEL_ROW	0xA
#define LCD_CELL_SMALL_DASH_PIXEL_ROW	0xE
#define LCD_CELL_CENTER_PIXEL_ROW		0x4
#define LCD_CELL_FIRST_LAST_PIXEL_ROW	0x11

#pragma endregion


namespace IttyBitty
{
#pragma region LCD EXTENSIONS CONSTANT DECLARATIONS

	EXTERN CBYTE LCD_CELL_SEMI_MASKS[3][3];

#pragma endregion


#pragma region CUSTOM CHARACTER FLASH DATA DECLARATIONS

	// Scrollbar icons
	EXTERN PROGMEM BYTE_P LCD_CHAR_SCROLLBAR_TOP[8];
	EXTERN PROGMEM BYTE_P LCD_CHAR_SCROLLBAR_BOTTOM[8];

	// Slider icons
	EXTERN PROGMEM BYTE_P LCD_CHAR_SLIDER_END_LEFT[8];
	EXTERN PROGMEM BYTE_P LCD_CHAR_SLIDER_END_RIGHT[8];

#pragma endregion


#pragma region LCD SCROLLBAR ENUMS

	ENUM LcdScrollBarIndicator : BYTE
	{
		LINE_INDICATOR = 0x00,
		BLOCK_INDICATOR = 0x10
	};

	DECLARE_ENUM_AS_FLAGS(LcdScrollBarIndicator, LCDSCROLLBARINDICATOR);


	ENUM LcdScrollBarPosition : BYTE
	{
		RIGHT_POSITION = 0x0,
		LEFT_POSITION = 0x1
	};

	DECLARE_ENUM_AS_FLAGS(LcdScrollBarPosition, LCDSCROLLBARPOSITION);


	ENUM_CLASS LcdScrollBarOptions : BYTE
	{
		LINE = LINE_INDICATOR | RIGHT_POSITION,
		LINE_LEFT = LINE_INDICATOR | LEFT_POSITION,

		BLOCK = BLOCK_INDICATOR | RIGHT_POSITION,
		BLOCK_LEFT = BLOCK_INDICATOR | LEFT_POSITION
	};

	TYPEDEF_ENUM_ALIASES(LcdScrollBarOptions, LCDSCROLLBAROPTIONS);



	INLINE CLCDSCROLLBARINDICATOR LcdScrollBarOptionsToLcdScrollBarIndicator(CLCDSCROLLBAROPTIONS lcdScrollBarOptions)
	{
		return static_cast<CLCDSCROLLBARINDICATOR>(HIGH_NYBBLE((CBYTE)lcdScrollBarOptions));
	}

	INLINE CLCDSCROLLBARPOSITION LcdScrollBarOptionsToLcdScrollBarPosition(CLCDSCROLLBAROPTIONS lcdScrollBarOptions)
	{
		return static_cast<CLCDSCROLLBARPOSITION>(LOW_NYBBLE((CBYTE)lcdScrollBarOptions));
	}

#pragma endregion


#pragma region LCD GRAPH ENUMS

	// Also used for LCD Slider...
	ENUM LcdSpaceStyle : BYTE
	{
		EMPTY_SPACE		= 0x0,
		DASH_SPACE		= 0x1,
		PLUS_SPACE		= 0x2,
		SQUARE_SPACE	= 0x3,
		DIAMOND_SPACE	= 0x4,
		CIRCLE_SPACE	= 0x5,
		LINES_SPACE		= 0x6,
		DOTS_SPACE		= 0x7
	};

	DECLARE_ENUM_AS_FLAGS(LcdSpaceStyle, LCDSPACETYLE);


	ENUM LcdGraphCell : BYTE
	{
		BLOCK_CELL		= 0x00,
		LINE_CELL		= 0x10,
		PLUS_CELL		= 0x20,
		SQUARE_CELL		= 0x30,
		DIAMOND_CELL	= 0x40,
		DISC_CELL		= 0x50,
		STRIPES_CELL	= 0x60
	};

	DECLARE_ENUM_AS_FLAGS(LcdGraphCell, LCDGRAPHCELL);


	ENUM LcdGraphPartialStyle : BYTE
	{
		NORMAL_PARTIAL		= 0x00,
		SEMI_FILL_PARTIAL	= 0x80
	};

	DECLARE_ENUM_AS_FLAGS(LcdGraphPartialStyle, LCDGRAPHPARTIALSTYLE);


	ENUM_CLASS LcdGraphOptions : BYTE
	{
		BAR						= BLOCK_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		BAR_DASH				= BLOCK_CELL | NORMAL_PARTIAL | DASH_SPACE,
		BAR_PLUS				= BLOCK_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		BAR_SQUARE				= BLOCK_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		BAR_DIAMOND				= BLOCK_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		BAR_CIRCLE				= BLOCK_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		BAR_LINES				= BLOCK_CELL | NORMAL_PARTIAL | LINES_SPACE,
		BAR_DOTS				= BLOCK_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		BAR_SEMI				= BLOCK_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		BAR_DASH_SEMI			= BLOCK_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		BAR_PLUS_SEMI			= BLOCK_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		BAR_SQUARE_SEMI			= BLOCK_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		BAR_DIAMOND_SEMI		= BLOCK_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		BAR_CIRCLE_SEMI			= BLOCK_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		BAR_LINES_SEMI			= BLOCK_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		BAR_DOTS_SEMI			= BLOCK_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE,

		LINE					= LINE_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		LINE_DASH				= LINE_CELL | NORMAL_PARTIAL | DASH_SPACE,
		LINE_PLUS				= LINE_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		LINE_SQUARE				= LINE_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		LINE_DIAMOND			= LINE_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		LINE_CIRCLE				= LINE_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		LINE_LINES				= LINE_CELL | NORMAL_PARTIAL | LINES_SPACE,
		LINES					= LINE_LINES,
		LINE_DOTS				= LINE_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		LINE_SEMI				= LINE_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		LINE_DASH_SEMI			= LINE_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		LINE_PLUS_SEMI			= LINE_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		LINE_SQUARE_SEMI		= LINE_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		LINE_DIAMOND_SEMI		= LINE_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		LINE_CIRCLE_SEMI		= LINE_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		LINE_LINES_SEMI			= LINE_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		LINES_SEMI				= LINE_LINES_SEMI,
		LINE_DOTS_SEMI			= LINE_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE,

		PLUS					= PLUS_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		PLUS_DASH				= PLUS_CELL | NORMAL_PARTIAL | DASH_SPACE,
		//PLUS_PLUS				= PLUS_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		PLUS_SQUARE				= PLUS_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		PLUS_DIAMOND			= PLUS_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		FILLED_DIAMOND			= PLUS_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		PLUS_CIRCLE				= PLUS_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		PLUS_LINES				= PLUS_CELL | NORMAL_PARTIAL | LINES_SPACE,
		PLUS_DOTS				= PLUS_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		PLUS_SEMI				= PLUS_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		PLUS_DASH_SEMI			= PLUS_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		//PLUS_PLUS_SEMI			= PLUS_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		PLUS_SQUARE_SEMI		= PLUS_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		PLUS_DIAMOND_SEMI		= PLUS_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		FILLED_DIAMOND_SEMI		= PLUS_DIAMOND_SEMI,
		PLUS_CIRCLE_SEMI		= PLUS_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		PLUS_LINES_SEMI			= PLUS_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		PLUS_DOTS_SEMI			= PLUS_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE,

		SQUARE					= SQUARE_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		SQUARE_DASH				= SQUARE_CELL | NORMAL_PARTIAL | DASH_SPACE,
		SQUARE_PLUS				= SQUARE_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		SQUARE_SQUARE			= SQUARE_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		SQUARES					= SQUARE_SQUARE,
		SQUARE_DIAMOND			= SQUARE_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		SQUARE_CIRCLE			= SQUARE_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		FILLED_CIRCLE			= SQUARE_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		SQUARE_LINES			= SQUARE_CELL | NORMAL_PARTIAL | LINES_SPACE,
		SQUARE_DOTS				= SQUARE_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		SQUARE_SEMI				= SQUARE_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		SQUARE_DASH_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		SQUARE_PLUS_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		SQUARE_SQUARE_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		SQUARES_SEMI			= SQUARE_SQUARE_SEMI,
		SQUARE_DIAMOND_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		SQUARE_CIRCLE_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		FILLED_CIRCLE_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		SQUARE_LINES_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		SQUARE_DOTS_SEMI		= SQUARE_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE,

		DIAMOND					= DIAMOND_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		DIAMOND_DASH			= DIAMOND_CELL | NORMAL_PARTIAL | DASH_SPACE,
		DIAMOND_PLUS			= DIAMOND_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		DIAMOND_SQUARE			= DIAMOND_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		DIAMOND_DIAMOND			= DIAMOND_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		DIAMONDS				= DIAMOND_DIAMOND,
		DIAMOND_CIRCLE			= DIAMOND_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		DIAMOND_LINES			= DIAMOND_CELL | NORMAL_PARTIAL | LINES_SPACE,
		DIAMOND_DOTS			= DIAMOND_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		DIAMOND_SEMI			= DIAMOND_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		DIAMOND_DASH_SEMI		= DIAMOND_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		DIAMOND_PLUS_SEMI		= DIAMOND_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		DIAMOND_SQUARE_SEMI		= DIAMOND_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		DIAMOND_DIAMOND_SEMI	= DIAMOND_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		DIAMONDS_SEMI			= DIAMOND_DIAMOND_SEMI,
		DIAMOND_CIRCLE_SEMI		= DIAMOND_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		DIAMOND_LINES_SEMI		= DIAMOND_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		DIAMOND_DOTS_SEMI		= DIAMOND_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE,

		DISC					= DISC_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		DISC_DASH				= DISC_CELL | NORMAL_PARTIAL | DASH_SPACE,
		DISC_PLUS				= DISC_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		DISC_SQUARE				= DISC_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		DISC_DIAMOND			= DISC_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		DISC_CIRCLE				= DISC_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		CIRCLES					= DISC_CIRCLE,
		DISC_LINES				= DISC_CELL | NORMAL_PARTIAL | LINES_SPACE,
		DISC_DOTS				= DISC_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		DISC_SEMI				= DISC_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		DISC_DASH_SEMI			= DISC_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		DISC_PLUS_SEMI			= DISC_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		DISC_SQUARE_SEMI		= DISC_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		DISC_DIAMOND_SEMI		= DISC_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		DISC_CIRCLE_SEMI		= DISC_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		CIRCLES_SEMI			= DISC_CIRCLE_SEMI,
		DISC_LINES_SEMI			= DISC_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		DISC_DOTS_SEMI			= DISC_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE,

		STRIPES					= STRIPES_CELL | NORMAL_PARTIAL | EMPTY_SPACE,
		STRIPES_DASH			= STRIPES_CELL | NORMAL_PARTIAL | DASH_SPACE,
		STRIPES_PLUS			= STRIPES_CELL | NORMAL_PARTIAL | PLUS_SPACE,
		STRIPES_SQUARE			= STRIPES_CELL | NORMAL_PARTIAL | SQUARE_SPACE,
		STRIPES_DIAMOND			= STRIPES_CELL | NORMAL_PARTIAL | DIAMOND_SPACE,
		STRIPES_CIRCLE			= STRIPES_CELL | NORMAL_PARTIAL | CIRCLE_SPACE,
		STRIPES_LINES			= STRIPES_CELL | NORMAL_PARTIAL | LINES_SPACE,
		STRIPES_DOTS			= STRIPES_CELL | NORMAL_PARTIAL | DOTS_SPACE,

		STRIPES_SEMI			= STRIPES_CELL | SEMI_FILL_PARTIAL | EMPTY_SPACE,
		STRIPES_DASH_SEMI		= STRIPES_CELL | SEMI_FILL_PARTIAL | DASH_SPACE,
		STRIPES_PLUS_SEMI		= STRIPES_CELL | SEMI_FILL_PARTIAL | PLUS_SPACE,
		STRIPES_SQUARE_SEMI		= STRIPES_CELL | SEMI_FILL_PARTIAL | SQUARE_SPACE,
		STRIPES_DIAMOND_SEMI	= STRIPES_CELL | SEMI_FILL_PARTIAL | DIAMOND_SPACE,
		STRIPES_CIRCLE_SEMI		= STRIPES_CELL | SEMI_FILL_PARTIAL | CIRCLE_SPACE,
		STRIPES_LINES_SEMI		= STRIPES_CELL | SEMI_FILL_PARTIAL | LINES_SPACE,
		STRIPES_DOTS_SEMI		= STRIPES_CELL | SEMI_FILL_PARTIAL | DOTS_SPACE
	};

	TYPEDEF_ENUM_ALIASES(LcdGraphOptions, LCDGRAPHOPTIONS);


	#define LCD_GRAPH_PARTIAL_CELL_STYLE_MASK	0x80

	INLINE CLCDGRAPHCELL LcdGraphOptionsToLcdGraphCell(CLCDGRAPHOPTIONS lcdGraphOptions)
	{
		return static_cast<CLCDGRAPHCELL>(HIGH_NYBBLE(
			WITHOUT_BITS((CBYTE)lcdGraphOptions, (CBYTE)LCD_GRAPH_PARTIAL_CELL_STYLE_MASK)));
	}

	INLINE CLCDGRAPHPARTIALSTYLE LcdGraphOptionsToLcdGraphPartialStyle(CLCDGRAPHOPTIONS lcdGraphOptions)
	{
		return static_cast<CLCDGRAPHPARTIALSTYLE>(HIGH_NYBBLE(
			MASK((CBYTE)lcdGraphOptions, LCD_GRAPH_PARTIAL_CELL_STYLE_MASK)));
	}

	INLINE CLCDSPACETYLE LcdGraphOptionsToLcdSpaceStyle(CLCDGRAPHOPTIONS lcdGraphOptions)
	{
		return static_cast<CLCDSPACETYLE>(LOW_NYBBLE((CBYTE)lcdGraphOptions));
	}

#pragma endregion


#pragma region LCD SLIDER ENUMS

	ENUM LcdSliderMarker : BYTE
	{
		CARET_MARKER	= 0x00,
		LINE_MARKER		= 0x10,
		PLUS_MARKER		= 0x20,
		SQUARE_MARKER	= 0x30,
		DIAMOND_MARKER	= 0x40,
		DISC_MARKER		= 0x50,
		TRIANGLE_MARKER	= 0x60,
		STRIPES_MARKER	= 0x70
	};

	DECLARE_ENUM_AS_FLAGS(LcdSliderMarker, LCDSLIDERMARKER);


	ENUM LcdSliderEnds : BYTE
	{
		NO_ENDS			= 0x00,
		NORMAL_ENDS		= 0x80
	};

	DECLARE_ENUM_AS_FLAGS(LcdSliderEnds, LCDSLIDERENDS);


	ENUM_CLASS LcdSliderOptions : BYTE
	{
		CARET					= CARET_MARKER | EMPTY_SPACE,
		CARET_DASH				= CARET_MARKER | DASH_SPACE,
		CARET_PLUS				= CARET_MARKER | PLUS_SPACE,
		CARET_SQUARE			= CARET_MARKER | SQUARE_SPACE,
		CARET_DIAMOND			= CARET_MARKER | DIAMOND_SPACE,
		CARET_CIRCLE			= CARET_MARKER | CIRCLE_SPACE,
		CARET_LINES				= CARET_MARKER | LINES_SPACE,
		CARET_DOTS				= CARET_MARKER | DOTS_SPACE,

		CARET_ENDS				= CARET_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		CARET_DASH_ENDS			= CARET_MARKER | DASH_SPACE | NORMAL_ENDS,
		CARET_PLUS_ENDS			= CARET_MARKER | PLUS_SPACE | NORMAL_ENDS,
		CARET_SQUARE_ENDS		= CARET_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		CARET_DIAMOND_ENDS		= CARET_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		CARET_CIRCLE_ENDS		= CARET_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		CARET_LINES_ENDS		= CARET_MARKER | LINES_SPACE | NORMAL_ENDS,
		CARET_DOTS_ENDS			= CARET_MARKER | DOTS_SPACE | NORMAL_ENDS,

		LINE					= LINE_MARKER | EMPTY_SPACE,
		LINE_DASH				= LINE_MARKER | DASH_SPACE,
		LINE_PLUS				= LINE_MARKER | PLUS_SPACE,
		LINE_SQUARE				= LINE_MARKER | SQUARE_SPACE,
		LINE_DIAMOND			= LINE_MARKER | DIAMOND_SPACE,
		LINE_CIRCLE				= LINE_MARKER | CIRCLE_SPACE,
		LINE_LINES				= LINE_MARKER | LINES_SPACE,
		LINES					= LINE_LINES,
		LINE_DOTS				= LINE_MARKER | DOTS_SPACE,

		LINE_ENDS				= LINE_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		LINE_DASH_ENDS			= LINE_MARKER | DASH_SPACE | NORMAL_ENDS,
		LINE_PLUS_ENDS			= LINE_MARKER | PLUS_SPACE | NORMAL_ENDS,
		LINE_SQUARE_ENDS		= LINE_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		LINE_DIAMOND_ENDS		= LINE_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		LINE_CIRCLE_ENDS		= LINE_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		LINE_LINES_ENDS			= LINE_MARKER | LINES_SPACE | NORMAL_ENDS,
		LINES_ENDS				= LINE_LINES_ENDS,
		LINE_DOTS_ENDS			= LINE_MARKER | DOTS_SPACE | NORMAL_ENDS,

		PLUS					= PLUS_MARKER | EMPTY_SPACE,
		PLUS_DASH				= PLUS_MARKER | DASH_SPACE,
		//PLUS_PLUS				= PLUS_MARKER | PLUS_SPACE,
		PLUS_SQUARE				= PLUS_MARKER | SQUARE_SPACE,
		PLUS_DIAMOND			= PLUS_MARKER | DIAMOND_SPACE,
		PLUS_CIRCLE				= PLUS_MARKER | CIRCLE_SPACE,
		PLUS_LINES				= PLUS_MARKER | LINES_SPACE,
		PLUS_DOTS				= PLUS_MARKER | DOTS_SPACE,

		PLUS_ENDS				= PLUS_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		PLUS_DASH_ENDS			= PLUS_MARKER | DASH_SPACE | NORMAL_ENDS,
		//PLUS_PLUS_ENDS			= PLUS_MARKER | PLUS_SPACE | NORMAL_ENDS,
		PLUS_SQUARE_ENDS		= PLUS_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		PLUS_DIAMOND_ENDS		= PLUS_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		PLUS_CIRCLE_ENDS		= PLUS_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		PLUS_LINES_ENDS			= PLUS_MARKER | LINES_SPACE | NORMAL_ENDS,
		PLUS_DOTS_ENDS			= PLUS_MARKER | DOTS_SPACE | NORMAL_ENDS,

		SQUARE					= SQUARE_MARKER | EMPTY_SPACE,
		SQUARE_DASH				= SQUARE_MARKER | DASH_SPACE,
		SQUARE_PLUS				= SQUARE_MARKER | PLUS_SPACE,
		SQUARE_SQUARE			= SQUARE_MARKER | SQUARE_SPACE,
		SQUARES					= SQUARE_SQUARE,
		SQUARE_DIAMOND			= SQUARE_MARKER | DIAMOND_SPACE,
		SQUARE_CIRCLE			= SQUARE_MARKER | CIRCLE_SPACE,
		SQUARE_LINES			= SQUARE_MARKER | LINES_SPACE,
		SQUARE_DOTS				= SQUARE_MARKER | DOTS_SPACE,

		SQUARE_ENDS				= SQUARE_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		SQUARE_DASH_ENDS		= SQUARE_MARKER | DASH_SPACE | NORMAL_ENDS,
		SQUARE_PLUS_ENDS		= SQUARE_MARKER | PLUS_SPACE | NORMAL_ENDS,
		SQUARE_SQUARE_ENDS		= SQUARE_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		SQUARES_ENDS			= SQUARE_SQUARE_ENDS,
		SQUARE_DIAMOND_ENDS		= SQUARE_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		SQUARE_CIRCLE_ENDS		= SQUARE_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		SQUARE_LINES_ENDS		= SQUARE_MARKER | LINES_SPACE | NORMAL_ENDS,
		SQUARE_DOTS_ENDS		= SQUARE_MARKER | DOTS_SPACE | NORMAL_ENDS,

		DIAMOND					= DIAMOND_MARKER | EMPTY_SPACE,
		DIAMOND_DASH			= DIAMOND_MARKER | DASH_SPACE,
		DIAMOND_PLUS			= DIAMOND_MARKER | PLUS_SPACE,
		DIAMOND_SQUARE			= DIAMOND_MARKER | SQUARE_SPACE,
		DIAMOND_DIAMOND			= DIAMOND_MARKER | DIAMOND_SPACE,
		DIAMONDS				= DIAMOND_DIAMOND,
		DIAMOND_CIRCLE			= DIAMOND_MARKER | CIRCLE_SPACE,
		DIAMOND_LINES			= DIAMOND_MARKER | LINES_SPACE,
		DIAMOND_DOTS			= DIAMOND_MARKER | DOTS_SPACE,

		DIAMOND_ENDS			= DIAMOND_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		DIAMOND_DASH_ENDS		= DIAMOND_MARKER | DASH_SPACE | NORMAL_ENDS,
		DIAMOND_PLUS_ENDS		= DIAMOND_MARKER | PLUS_SPACE | NORMAL_ENDS,
		DIAMOND_SQUARE_ENDS		= DIAMOND_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		DIAMOND_DIAMOND_ENDS	= DIAMOND_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		DIAMONDS_ENDS			= DIAMOND_DIAMOND_ENDS,
		DIAMOND_CIRCLE_ENDS		= DIAMOND_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		DIAMOND_LINES_ENDS		= DIAMOND_MARKER | LINES_SPACE | NORMAL_ENDS,
		DIAMOND_DOTS_ENDS		= DIAMOND_MARKER | DOTS_SPACE | NORMAL_ENDS,

		DISC					= DISC_MARKER | EMPTY_SPACE,
		DISC_DASH				= DISC_MARKER | DASH_SPACE,
		DISC_PLUS				= DISC_MARKER | PLUS_SPACE,
		DISC_SQUARE				= DISC_MARKER | SQUARE_SPACE,
		DISC_DIAMOND			= DISC_MARKER | DIAMOND_SPACE,
		DISC_CIRCLE				= DISC_MARKER | CIRCLE_SPACE,
		CIRCLES					= DISC_CIRCLE,
		DISC_LINES				= DISC_MARKER | LINES_SPACE,
		DISC_DOTS				= DISC_MARKER | DOTS_SPACE,

		DISC_ENDS				= DISC_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		DISC_DASH_ENDS			= DISC_MARKER | DASH_SPACE | NORMAL_ENDS,
		DISC_PLUS_ENDS			= DISC_MARKER | PLUS_SPACE | NORMAL_ENDS,
		DISC_SQUARE_ENDS		= DISC_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		DISC_DIAMOND_ENDS		= DISC_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		DISC_CIRCLE_ENDS		= DISC_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		CIRCLES_ENDS			= DISC_CIRCLE_ENDS,
		DISC_LINES_ENDS			= DISC_MARKER | LINES_SPACE | NORMAL_ENDS,
		DISC_DOTS_ENDS			= DISC_MARKER | DOTS_SPACE | NORMAL_ENDS,

		TRIANGLE				= TRIANGLE_MARKER | EMPTY_SPACE,
		TRIANGLE_DASH			= TRIANGLE_MARKER | DASH_SPACE,
		TRIANGLE_PLUS			= TRIANGLE_MARKER | PLUS_SPACE,
		TRIANGLE_SQUARE			= TRIANGLE_MARKER | SQUARE_SPACE,
		TRIANGLE_DIAMOND		= TRIANGLE_MARKER | DIAMOND_SPACE,
		TRIANGLE_CIRCLE			= TRIANGLE_MARKER | CIRCLE_SPACE,
		TRIANGLE_LINES			= TRIANGLE_MARKER | LINES_SPACE,
		TRIANGLE_DOTS			= TRIANGLE_MARKER | DOTS_SPACE,

		TRIANGLE_ENDS			= TRIANGLE_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		TRIANGLE_DASH_ENDS		= TRIANGLE_MARKER | DASH_SPACE | NORMAL_ENDS,
		TRIANGLE_PLUS_ENDS		= TRIANGLE_MARKER | PLUS_SPACE | NORMAL_ENDS,
		TRIANGLE_SQUARE_ENDS	= TRIANGLE_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		TRIANGLE_DIAMOND_ENDS	= TRIANGLE_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		TRIANGLE_CIRCLE_ENDS	= TRIANGLE_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		TRIANGLE_LINES_ENDS		= TRIANGLE_MARKER | LINES_SPACE | NORMAL_ENDS,
		TRIANGLE_DOTS_ENDS		= TRIANGLE_MARKER | DOTS_SPACE | NORMAL_ENDS,

		STRIPES					= STRIPES_MARKER | EMPTY_SPACE,
		STRIPES_DASH			= STRIPES_MARKER | DASH_SPACE,
		STRIPES_PLUS			= STRIPES_MARKER | PLUS_SPACE,
		STRIPES_SQUARE			= STRIPES_MARKER | SQUARE_SPACE,
		STRIPES_DIAMOND			= STRIPES_MARKER | DIAMOND_SPACE,
		STRIPES_CIRCLE			= STRIPES_MARKER | CIRCLE_SPACE,
		STRIPES_LINES			= STRIPES_MARKER | LINES_SPACE,
		STRIPES_DOTS			= STRIPES_MARKER | DOTS_SPACE,

		STRIPES_ENDS			= STRIPES_MARKER | EMPTY_SPACE | NORMAL_ENDS,
		STRIPES_DASH_ENDS		= STRIPES_MARKER | DASH_SPACE | NORMAL_ENDS,
		STRIPES_PLUS_ENDS		= STRIPES_MARKER | PLUS_SPACE | NORMAL_ENDS,
		STRIPES_SQUARE_ENDS		= STRIPES_MARKER | SQUARE_SPACE | NORMAL_ENDS,
		STRIPES_DIAMOND_ENDS	= STRIPES_MARKER | DIAMOND_SPACE | NORMAL_ENDS,
		STRIPES_CIRCLE_ENDS		= STRIPES_MARKER | CIRCLE_SPACE | NORMAL_ENDS,
		STRIPES_LINES_ENDS		= STRIPES_MARKER | LINES_SPACE | NORMAL_ENDS,
		STRIPES_DOTS_ENDS		= STRIPES_MARKER | DOTS_SPACE | NORMAL_ENDS
	};

	TYPEDEF_ENUM_ALIASES(LcdSliderOptions, LCDSLIDEROPTIONS);


	#define LCD_SLIDER_ENDS_MASK	0x80

	INLINE CLCDSLIDERMARKER LcdSliderOptionsToLcdSliderMarker(CLCDSLIDEROPTIONS lcdSliderOptions)
	{
		return static_cast<CLCDSLIDERMARKER>(HIGH_NYBBLE(
			WITHOUT_BITS((CBYTE)lcdSliderOptions, (CBYTE)LCD_SLIDER_ENDS_MASK)));
	}

	INLINE CLCDSLIDERENDS LcdSliderOptionsToLcdSliderEnds(CLCDSLIDEROPTIONS lcdSliderOptions)
	{
		return static_cast<CLCDSLIDERENDS>(HIGH_NYBBLE(
			MASK((CBYTE)lcdSliderOptions, LCD_SLIDER_ENDS_MASK)));
	}

	INLINE CLCDSPACETYLE LcdSliderOptionsToLcdSpaceStyle(CLCDSLIDEROPTIONS lcdSliderOptions)
	{
		return static_cast<CLCDSPACETYLE>(LOW_NYBBLE((CBYTE)lcdSliderOptions));
	}

#pragma endregion
};

#endif
