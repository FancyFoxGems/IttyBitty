/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.     		*
* Credit for this font, however, goes to the BigCrystal Arduino library					   *
*	...which has been released to the Public Domain     		   *
*	SEE https://github.com/gregington/BigCrystal     			  *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.			*
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if !defined(ARDUINO) || defined(ITTYBITTY_BASE) || defined(NO_ITTYBITTY_LCD) || defined(NO_ITTYBITTY_LCD_I2C)
	#define NO_ITTYBITTY_BIG
#endif

#ifndef NO_ITTYBITTY_BIG


#include "IttyBitty_LCD_I2C.h"


namespace IttyBitty
{
#pragma region LCD BIG FONT FLASH DATA TABLES

	PROGMEM BYTE_P LCD_BIG_FONT_SHAPES[64] =
	{
		// BFLT[8]
		0b00000111, 0b00001111, 0b00011111, 0b00011111,
		0b00011111, 0b00011111, 0b00011111, 0b00011111,
		// BFUB[8]
		0b00011111, 0b00011111, 0b00011111, 0b00000000,
		0b00000000, 0b00000000, 0b00000000, 0b00000000,
		// BFRT[8]
		0b00011100, 0b00011110, 0b00011111, 0b00011111,
		0b00011111, 0b00011111, 0b00011111, 0b00011111,
		// BFLL[8]
		0b00011111, 0b00011111, 0b00011111, 0b00011111,
		0b00011111, 0b00011111, 0b00001111, 0b00000111,
		// BFLB[8]
		0b00000000, 0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00011111, 0b00011111, 0b00011111,
		// BFLR[8]
		0b00011111, 0b00011111, 0b00011111, 0b00011111,
		0b00011111, 0b00011111, 0b00011110, 0b00011100,
		// BFUM[8]
		0b00011111, 0b00011111, 0b00011111, 0b00000000,
		0b00000000, 0b00000000, 0b00011111, 0b00011111,
		// BFFF[8]
		0b00011111, 0b00011111, 0b00011111, 0b00011111,
		0b00011111, 0b00011111, 0b00011111, 0b00011111
	};

	PROGMEM BYTE_P LCD_BIG_FONT_CHAR_MAP[] =
	{
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			0),		// 0x20 (space)
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			1),		// 0x21 !
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3_SYMBOLS,	0),		// 0x22 "
		LCD_BIG_NO_FONT,										// 0x23 #
		LCD_BIG_NO_FONT,										// 0x24 $
		LCD_BIG_NO_FONT,										// 0x25 %
		LCD_BIG_NO_FONT,										// 0x26 &
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			2),		// 0x27 '
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			3),		// 0x28 (
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			4),		// 0x29 )
		LCD_BIG_NO_FONT,										// 0x2A *
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3_SYMBOLS,	1),		// 0x2B +
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			5),		// 0x2C ,
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_2,			0),		// 0x2D -
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			6),		// 0x2E .
		LCD_BIG_NO_FONT,										//
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			0),		// 0x30 0
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			1),		// 0x31 1
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			2),		// 0x32 2
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			3),		// 0x33 3
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			4),		// 0x34 4
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			5),		// 0x35 5
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			6),		// 0x36 6
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			7),		// 0x37 7
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			8),		// 0x38 8
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			9),		// 0x39 9
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			7),		// 0x3A :
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_1,			8),		// 0x3B ;
		LCD_BIG_NO_FONT,										// 0x3C <
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_2,			1),		// 0x3D =
		LCD_BIG_NO_FONT,										// 0x3E <
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3_SYMBOLS,	2),		// 0x3F ?
		LCD_BIG_NO_FONT,										// 0x40 @
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			10),	// 0x41 A
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			11),	// 0x42 B
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			12),	// 0x43 C
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			13),	// 0x44 D
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			14),	// 0x45 E
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			15),	// 0x46 F
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			16),	// 0x47 G
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			17),	// 0x48 H
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			18),	// 0x49 I
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			19),	// 0x4A J
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			20),	// 0x4B K
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			21),	// 0x4C L
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_5,			0),		// 0x4D M
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_4,			0),		// 0x4E N
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			0),		// 0x4F O (re-use of font for number 0)
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			22),	// 0x50 P
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_4,			1),		// 0x51 Q
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			23),	// 0x52 R
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			24),	// 0x53 S
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			25),	// 0x54 T
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			26),	// 0x55 U
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_4,			2),		// 0x56 V
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_5,			1),		// 0x57 W
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			27),	// 0x58 X
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			28),	// 0x59 Y
		LCD_BIG_CHAR_MAP_ENTRY(LCD_BIG_FONT_3,			29)		// 0x5A Z
	};

	PPROGMEM BYTE_P LCD_BIG_FONT_DATA_TABLES[6] =
	{
		LCD_BIG_FONT_DATA_1, LCD_BIG_FONT_DATA_2, LCD_BIG_FONT_DATA_3,
		LCD_BIG_FONT_DATA_4, LCD_BIG_FONT_DATA_5, LCD_BIG_FONT_DATA_3_SYMBOLS
	};

	PROGMEM BYTE_P LCD_BIG_FONT_DATA_1[] =
	{
		BFBL, BFBL,		     					// BFBL space
		BFLT, BFLB,	     						// 0x21 !
		BFLR, BFBL,	     						// 0x27 '
		BFLT, BFLL,	     						// 0x28 (
		BFRT, BFLR,		     					// 0x29 )
		BFBL, BFLR,		     					// 0x2C ,
		BFBL, BFLB,	     						// 0x2E .
		BFUN, BFUN,		     					// 0x3A :
		BFUB, BFLR 		     					// 0x3B ;
	};

	PROGMEM BYTE_P LCD_BIG_FONT_DATA_2[] =
	{
		BFLB, BFLB, BFBL, BFBL,     			// 0x2D -
		BFLB, BFLB, BFLB, BFLB      			// 0x3D =
	};

	PROGMEM BYTE_P LCD_BIG_FONT_DATA_3[] =
	{
		BFLT, BFUB, BFRT, BFLL, BFLB, BFLR,     // 0x30 0, 0x4F O
		BFUB, BFRT, BFBL, BFLB, BFFF, BFLB,     // 0x31 1
		BFUM, BFUM, BFRT, BFLL, BFLB, BFLB,     // 0x32 2
		BFUM, BFUM, BFRT, BFLB, BFLB, BFLR,     // 0x33 3
		BFLL, BFLB, BFRT, BFBL, BFBL, BFLR,     // 0x34 4
		BFFF, BFUM, BFUM, BFLB, BFLB, BFLR,     // 0x35 5
		BFLT, BFUM, BFUM, BFLL, BFLB, BFLR,     // 0x36 6
		BFUB, BFUB, BFRT, BFBL, BFLT, BFBL,     // 0x37 7
		BFLT, BFUM, BFRT, BFLL, BFLB, BFLR,     // 0x38 8
		BFLT, BFUM, BFRT, BFBL, BFBL, BFLR,     // 0x39 9
		BFLT, BFUM, BFRT, BFFF, BFBL, BFFF,     // 0x41 A
		BFFF, BFUM, BFLR, BFFF, BFLB, BFRT,     // 0x42 B
		BFLT, BFUB, BFUB, BFLL, BFLB, BFLB,     // 0x43 C
		BFFF, BFUB, BFRT, BFFF, BFLB, BFLR,     // 0x44 D
		BFFF, BFUM, BFUM, BFFF, BFLB, BFLB,     // 0x45 E
		BFFF, BFUM, BFUM, BFFF, BFBL, BFBL,     // 0x46 F
		BFLT, BFUB, BFUB, BFLL, BFLB, BFRT,     // 0x47 G
		BFFF, BFLB, BFFF, BFFF, BFBL, BFFF,     // 0x48 H
		BFUB, BFFF, BFUB, BFLB, BFFF, BFLB,     // 0x49 I
		BFBL, BFBL, BFFF, BFLB, BFLB, BFLR,     // 0x4A J
		BFFF, BFLB, BFLR, BFFF, BFBL, BFRT,     // 0x4B K
		BFFF, BFBL, BFBL, BFFF, BFLB, BFLB,     // 0x4C L
		BFLT, BFUM, BFRT, BFLL, BFBL, BFBL,     // 0x50 P
		BFLT, BFUM, BFLR, BFLL, BFBL, BFRT,     // 0x52 R
		BFLT, BFUM, BFUM, BFLB, BFLB, BFLR,     // 0x53 S
		BFUB, BFRT, BFUB, BFBL, BFLR, BFBL,     // 0x54 T
		BFRT, BFBL, BFRT, BFLL, BFLB, BFLR,     // 0x55 U
		BFLL, BFLB, BFLR, BFLT, BFBL, BFRT,     // 0x58 X
		BFLL, BFLB, BFLR, BFBL, BFLR, BFBL,     // 0x59 Y
		BFUB, BFUM, BFLR, BFLT, BFLB, BFLB		// 0x5A Z
	};

	PROGMEM BYTE_P LCD_BIG_FONT_DATA_3_SYMBOLS[] =
	{
		BFLR, BFBL, BFLR, BFBL, BFBL, BFBL,		// 0x22 "
		BFLB, BFFF, BFLB, BFUB, BFFF, BFUB,     // 0x2B +
		BFUB, BFUM, BFRT, BFBL, BFLB, BFBL		// 0x3F ?
	};

	PROGMEM BYTE_P LCD_BIG_FONT_DATA_4[] =
	{
		BFLT, BFLL, BFBL, BFRT,					// 0x4E N
		BFLL, BFBL, BFRT, BFLR,
		BFLT, BFUB, BFRT, BFBL,					// 0x51 Q
		BFLL, BFLB, BFLL, BFLB,
		BFLL, BFBL, BFBL, BFLR,					// 0x56 V
		BFBL, BFLL, BFLR, BFBL
	};

	PROGMEM BYTE_P LCD_BIG_FONT_DATA_5[] =
	{
		BFLT, BFUB, BFLL, BFUB, BFRT, 			// 0x4D M
		BFLL, BFBL, BFBL, BFBL, BFLR,
		BFLT, BFBL, BFBL, BFBL, BFRT, 			// 0x57 W
		BFLL, BFLB, BFLT, BFLB, BFLR
	};

#pragma endregion
};

#endif	// #ifndef NO_ITTYBITTY_BIG
