/***********************************************************************************************
* [IttyBitty_LCD_big_decl.h]: METHOD DECLARATIONS FOR ADDED SUPPORT FOR LARGE
*	(TWO-ROW, MULTI-COLUMN) CHARACTER PRINTING ON I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_BIG_DECL_H
#define _ITTYBITTY_LCD_BIG_DECL_H


#pragma region LCD LARGE PRINT HELPER FUNCTIONS

private:

	STATIC CONSTEXPR CCHAR ToUpperCase(CCHAR c)
	{
		return  (c >= 'a' && c <= 'z') ? MASK(c, CHAR_UPPER_CASE_MASK) : c;
	}

	VOID FindBigFontCharEntry(CCHAR c, RBYTE tableCode, RBYTE fontIndex)
	{
		CBYTE charMapEntry = pgm_read_byte_near(&LCD_BIG_FONT_CHAR_MAP[c - LCD_BIG_CHAR_MAP_CHAR_INDEX_OFFSET]);

		tableCode = LCD_BIG_TABLE_CODE_FROM_CHAR_MAP_ENTRY(charMapEntry);
		fontIndex = LCD_BIG_FONT_INDEX_FROM_CHAR_MAP_ENTRY(charMapEntry);
	}

	CBYTE BigCharWidthFromTableCode(CBYTE tableCode)
	{
		if (tableCode == LCD_BIG_FONT_3_SYMBOLS)
			return 3;

		return MASK(tableCode, LCD_BIG_FONT_WIDTH_MASK);
	}

	CBYTE BigCharWidthOf(CCHAR c)
	{
		CCHAR upper = toUpperCase(c);

		BYTE tableCode;
		BYTE fontIndex;
		this->FindBigFontCharEntry(upper, tableCode, fontIndex);

		CBYTE bigCharWidth = this->BigCharWidthOf(tableCode);
		if (bigCharWidth == 0)
			return 0;

		return bigCharWidth + 1;
	}

	PCBYTE BigFontTable(CBYTE tableCode)
	{
		return reinterpret_cast<PCBYTE>(pgm_read_word_near(&LCD_BIG_FONT_DATA_TABLES[tableCode - 1]));
	}

	VOID WriteSpaceBig(CBYTE col, CBYTE row)
	{
		this->MoveCursor(col, row);
		this->write(BFBL);
		this->MoveCursor(col, row + 1);
		this->write(BFBL);
	}

#pragma endregion


#pragma region LCD BIG EXTENSIONS FUNCTION DEFINITIONS

public:

	VOID LoadBigFont()
	{
		for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
			this->LoadCustomChar_P(i, &LCD_BIG_FONT_SHAPES[i * CHAR_HEIGHT()]);

		_BigFontLoaded = TRUE;
	}

	CBYTE WriteBig(CBYTE c, CBYTE col, CBYTE row)
	{
		CCHAR upper = ToUpperCase((CHAR)c);

		BYTE tableCode;
		BYTE fontIndex;
		this->FindBigFontCharEntry(upper, tableCode, fontIndex);

		PCBYTE table = this->BigFontTable(tableCode);
		if (!table)
			return 0;

		if (!_BigFontLoaded)
			this->LoadBigFont();

		CBYTE bigCharWidth = this->BigCharWidthFromTableCode(tableCode);
		int tableOffset = bigCharWidth * 2 * fontIndex;

		this->MoveCursor(col, row);
		for (BYTE i = 0; i < bigCharWidth; i++)
			this->write(pgm_read_byte_near(&table[tableOffset + i]));

		this->MoveCursor(col, row + 1);
		for (BYTE i = 0; i < bigCharWidth; i++)
			this->write(pgm_read_byte_near(&table[tableOffset + i + bigCharWidth]));

		this->WriteSpaceBig(col + bigCharWidth, row);

		return bigCharWidth + 1;
	}

	CBYTE PrintStringBig(PCCHAR str, CBYTE col, CBYTE row)
	{
		return this->PrintString(str, col, row, &LCD_I2C::WriteBig);
	}

	CBYTE PrintStringBig_P(FLASH_STRING flashStr, CBYTE col, CBYTE row)
	{
		return this->PrintString_P(flashStr, col, row, &LCD_I2C::WriteBig);
	}

#pragma endregion

#endif
