/***********************************************************************************************
* [IttyBitty_LCD_big.h]: ADDED SUPPORT FOR LARGE (TWO-ROW, MULTI-COLUMN)
*	CHARACTER PRINTING ON I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_BIG_H
#define _ITTYBITTY_LCD_BIG_H


#include "IttyBitty_aliases.h"


#pragma region DEFINES

// UPPER CASE MASK CONSTANT

#define CHAR_UPPER_CASE_MASK	0x5F

// BIG FONT SHAPE CHARACTER INDEXES

#define BFLT	0x00
#define BFUB	0x01
#define BFRT	0x02
#define BFLL	0x03
#define BFLB	0x04
#define BFLR	0x05
#define BFUM	0x06
#define BFFF	0x07

#define BFBL	0x20
#define BFUN	0x6F


// BIG FONT TABLE CODES

#define LCD_BIG_FONT_WIDTH_MASK		0x7

#define LCD_BIG_NO_FONT				0x0
#define LCD_BIG_FONT_1				0x1
#define LCD_BIG_FONT_2				0x2
#define LCD_BIG_FONT_3				0x3
#define LCD_BIG_FONT_3_SYMBOLS		0x6
#define LCD_BIG_FONT_4				0x4
#define LCD_BIG_FONT_5				0x5


// BIG FONT CHARACTER MAP CONSTANTS, MASKS, AND MACROS

#define LCD_BIG_CHAR_MAP_CHAR_INDEX_OFFSET	0x20	// Space character: ' '

#define LCD_BIG_CHAR_MAP_TABLE_CODE_OFFSET	0x5		// To upper three bits: BITS_PER_BYTE - 3 (bit-size of table code)

#define LCD_BIG_CHAR_MAP_TABLE_CODE_MASK	0xE0	// Upper three bits: B(5) | ... | (B7)
#define LCD_BIG_CHAR_MAP_FONT_INDEX_MASK	0x1F	// Lower five bits: B(0) | ... | B(4)

#define LCD_BIG_CHAR_MAP_TABLE_CODE(table_code)			(table_code) SHL LCD_BIG_CHAR_MAP_TABLE_CODE_OFFSET
#define LCD_BIG_CHAR_MAP_FONT_INDEX(font_index)			MASK(font_index, LCD_BIG_CHAR_MAP_FONT_INDEX_MASK)
#define LCD_BIG_CHAR_MAP_ENTRY(table_code, font_index)	\
	WITH_BITS(LCD_BIG_CHAR_MAP_TABLE_CODE(table_code), LCD_BIG_CHAR_MAP_FONT_INDEX(font_index))


#define LCD_BIG_TABLE_CODE_FROM_CHAR_MAP_ENTRY(char_map_entry)			(char_map_entry) SHR LCD_BIG_CHAR_MAP_TABLE_CODE_OFFSET
#define LCD_BIG_FONT_INDEX_FROM_CHAR_MAP_ENTRY(char_map_entry)			MASK(char_map_entry, LCD_BIG_CHAR_MAP_FONT_INDEX_MASK)

#pragma endregion


namespace IttyBitty
{
#pragma region LCD BIG FONT FLASH DATA TABLE DECLARATIONS

	EXTERN PROGMEM CBYTE LCD_BIG_FONT_SHAPES[64];

	EXTERN PROGMEM CBYTE LCD_BIG_FONT_CHAR_MAP[59];

	EXTERN PROGMEM PCBYTE const LCD_BIG_FONT_DATA_TABLES[6];

	EXTERN PROGMEM CBYTE LCD_BIG_FONT_DATA_1[18];			//	1 cols/char * 2 rows/char * 18 chars
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_DATA_2[8];			//	2 cols/char * 2 rows/char * 2 chars
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_DATA_3[180];			//	3 cols/char * 2 rows/char * 30 chars
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_DATA_3_SYMBOLS[18];	//	3 cols/char * 2 rows/char * 3 chars
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_DATA_4[24];			//	4 cols/char * 2 rows/char * 3 chars
	EXTERN PROGMEM CBYTE LCD_BIG_FONT_DATA_5[20];			//	5 cols/char * 2 rows/char * 2 chars

#pragma endregion
};

#endif
