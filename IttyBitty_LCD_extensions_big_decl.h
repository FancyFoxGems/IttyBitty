/***********************************************************************************************
* [IttyBitty_LCD_extensions_big_decl.h]: METHOD DECLARATIONS FOR ADDED SUPPORT FOR LARGE
*	(TWO-ROW, MULTI-COLUMN) CHARACTER PRINTING ON I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_EXTENSIONS_BIG_DECL_H
#define _ITTYBITTY_LCD_EXTENSIONS_BIG_DECL_H


private:


	STATIC CONSTEXPR CCHAR ToUpperCase(CCHAR c)
	{
		return  (c >= 'a' && c <= 'z') ? c & 0x5f : c;
	}

	STATIC CONSTEXPR CBOOL BigFontHasChar(CCHAR c)
	{
		return (c >= ' ' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}


	VOID LoadBigFontTableData(CCHAR c, RBYTE tableCode, RBYTE index)
	{
		CBYTE tableAndIndex = pgm_read_byte_near(LCD_BIG_FONT_CHARACTERS + c - ' ');
		// Top 3 bits are the table, bottom 5 are index into table
		tableCode = (CBYTE)((tableAndIndex & 0xE0) >> 5);
		index = (CBYTE)(tableAndIndex & 0x1F);
	}

	PCBYTE BigFontTable(CBYTE tableCode)
	{
		switch (tableCode)
		{
		case BF_WIDTH1_TABLE:
			return LCD_BIG_FONT_WIDTH1;
		case BF_WIDTH2_TABLE:
			return LCD_BIG_FONT_WIDTH2;
		case BF_WIDTH3_TABLE:
			return LCD_BIG_FONT_WIDTH3;
		case BF_WIDTH4_TABLE:
			return LCD_BIG_FONT_WIDTH4;
		case BF_WIDTH5_TABLE:
			return LCD_BIG_FONT_WIDTH5;
		case BF_WIDTH3_SYMBOLS_TABLE:
			return LCD_BIG_FONT_WIDTH3_SYMBOLS;
		default:
			return NULL;
		}
	}

	CBYTE WidthFromTableCode(CBYTE tableCode)
	{
		if (tableCode == BF_WIDTH3_SYMBOLS_TABLE)
			return 3;

		return tableCode;
	}

	CBYTE FindBigCharWidth(CCHAR c)
	{
		if (!this->BigFontHasChar(c))
			return 0;

		CCHAR ch = toUpperCase(c);

		CBYTE tableCode;
		CBYTE index;
		this->LoadBigFontTableData(ch, tableCode, index);

		CBYTE width = this->FindBigCharWidth(tableCode);
		if (width == 0)
			return 0;

		return width + 1; // add one for space after character
	}

	VOID ClearColumn(CBYTE col, CBYTE row)
	{
		this->MoveCursor(col, row);
		this->write(0x20);
		this->MoveCursor(col, row + 1);
		this->write(0x20);
	}


public:


	VOID LoadBigFont()
	{
		BYTE customChar[CHAR_HEIGHT()];

		for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
		{
			for (BYTE j = 0; j < CHAR_HEIGHT(); j++)
				customChar[j] = pgm_read_byte_near(LCD_BIG_FONT_SHAPES + (i * CHAR_HEIGHT()) + j);

			this->LoadCustomChar(i, customChar);
		}
	}

	CBYTE WriteBig(CCHAR c, CBYTE col, CBYTE row)
	{
		if (!this->BigFontHasChar(c))
			return 0;

		CCHAR ch = ToUpperCase(c);

		CBYTE tableCode;
		CBYTE index;
		this->LoadBigFontTableData(ch, tableCode, index);

		const CBYTE* table = this->BigFontTable(tableCode);
		if (table == NULL)
		{
			return 0;
		}
		CBYTE width = this->FindBigCharWidth(tableCode);

		int tableOffset = (width * 2) * index;

		// Write first row
		this->MoveCursor(col, row);
		for (BYTE i = 0; i < width; i++)
			this->write(pgm_read_byte_near(table + tableOffset + i));

		// Write second row
		this->MoveCursor(col, row + 1);
		for (BYTE i = 0; i < width; i++)
			this->write(pgm_read_byte_near(table + tableOffset + width + i));

		// Clear last column
		this->ClearColumn(col + width, row);

		return width + 1; // add one for the cleared column
	}

	CBYTE PrintBig(PCCHAR str, CBYTE col, CBYTE row)
	{
		BYTE width = 0;
		CCHAR *c = str;

		while (*c != '\0')
		{
			width += this->WriteBig(*c, col + width, row);
			*c++;
		}

		return width;
	}

	CBYTE PrintBig(FLASH_STRING flashStr, CBYTE col, CBYTE row)
	{
		BYTE width = 0;
		PCCHAR strAddr = reinterpret_cast<PCCHAR>(flashStr);
		CCHAR c = pgm_read_byte_near(strAddr++);

		while (c != '\0')
		{
			this->WriteBig(c, col + width++, row);
			c = pgm_read_byte_near(strAddr++);
		}

		return width;
	}

#endif
