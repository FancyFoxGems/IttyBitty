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
		CBYTE tableAndIndex = pgm_read_byte_near(&LCD_BIG_FONT_CHAR_MAP[c - LCD_BIG_CHAR_MAP_CHAR_INDEX_OFFSET]);
		// Top 3 bits are the table, bottom 5 are index into table
		tableCode = (CBYTE)((tableAndIndex & 0xE0) >> 5);
		index = (CBYTE)(tableAndIndex & 0x1F);
	}

	PCBYTE BigFontTable(CBYTE tableCode)
	{
		switch (tableCode)
		{
		case LCD_BIG_FONT_1:
			return LCD_BIG_FONT_DATA_1;
		case LCD_BIG_FONT_2:
			return LCD_BIG_FONT_DATA_2;
		case LCD_BIG_FONT_3:
			return LCD_BIG_FONT_DATA_3;
		case LCD_BIG_FONT_4:
			return LCD_BIG_FONT_DATA_4;
		case LCD_BIG_FONT_5:
			return LCD_BIG_FONT_DATA_5;
		case LCD_BIG_FONT_3_SYMBOLS:
			return LCD_BIG_FONT_DATA_3_SYMBOLS;
		default:
			return NULL;
		}
	}

	CBYTE WidthFromTableCode(CBYTE tableCode)
	{
		if (tableCode == LCD_BIG_FONT_3_SYMBOLS)
			return 3;

		return tableCode;
	}

	CBYTE FindBigCharWidth(CCHAR c)
	{
		if (!this->BigFontHasChar(c))
			return 0;

		CCHAR ch = toUpperCase(c);

		BYTE tableCode;
		BYTE index;
		this->LoadBigFontTableData(ch, tableCode, index);

		CBYTE width = this->FindBigCharWidth(tableCode);
		if (width == 0)
			return 0;

		return width + 1; // add one for space after character
	}

	VOID ClearColumn(CBYTE col, CBYTE row)
	{
		this->MoveCursor(col, row);
		this->write(LCD_CELL_BLANK_PIXEL_ROW);
		this->MoveCursor(col, row + 1);
		this->write(LCD_CELL_BLANK_PIXEL_ROW);
	}


public:


	VOID LoadBigFont()
	{
		for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
			this->LoadCustomChar_P(i, &LCD_BIG_FONT_SHAPES[i * CHAR_HEIGHT()]);
	}

	CBYTE WriteBig(CCHAR c, CBYTE col, CBYTE row)
	{
		if (!this->BigFontHasChar(c))
			return 0;

		CCHAR ch = ToUpperCase(c);

		BYTE tableCode;
		BYTE index;
		this->LoadBigFontTableData(ch, tableCode, index);

		CBYTE* table = this->BigFontTable(tableCode);
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

	CBYTE PrintStringBig(PCCHAR str, CBYTE col, CBYTE row)
	{
		BYTE width = 0;
		CHAR *c = str;

		while (*c != '\0')
		{
			width += this->WriteBig(*c, col + width, row);
			*c++;
		}

		return width;
	}

	CBYTE PrintStringBig_P(FLASH_STRING flashStr, CBYTE col, CBYTE row)
	{
		BYTE width = 0;
		PCCHAR strAddr = reinterpret_cast<PCCHAR>(flashStr);
		CHAR c = pgm_read_byte_near(strAddr++);

		while (c != '\0')
		{
			this->WriteBig(c, col + width++, row);
			c = pgm_read_byte_near(strAddr++);
		}

		return width;
	}

	//CBYTE WriteBig(CBYTE c, CBYTE col, CBYTE row)
	//{
	//	if (!this->BigFontHasChar(c))
	//		return 0;

	//	CCHAR ch = ToUpperCase((CBYTE)c);

	//	BYTE tableCode;
	//	BYTE index;
	//	this->LoadBigFontTableData(ch, tableCode, index);

	//	CBYTE* table = this->BigFontTable(tableCode);
	//	if (table == NULL)
	//	{
	//		return 0;
	//	}
	//	CBYTE width = this->FindBigCharWidth(tableCode);

	//	int tableOffset = (width * 2) * index;

	//	// Write first row
	//	this->MoveCursor(col, row);
	//	for (BYTE i = 0; i < width; i++)
	//		this->write(pgm_read_byte_near(table + tableOffset + i));

	//	// Write second row
	//	this->MoveCursor(col, row + 1);
	//	for (BYTE i = 0; i < width; i++)
	//		this->write(pgm_read_byte_near(table + tableOffset + width + i));

	//	// Clear last column
	//	this->ClearColumn(col + width, row);

	//	return width + 1; // add one for the cleared column
	//}

	//CBYTE PrintStringBig(PCCHAR str, CBYTE col, CBYTE row)
	//{
	//	return this->PrintString_P(str, col, row, &LCD_I2C::WriteBig);
	//}

	//CBYTE PrintStringBig_P(FLASH_STRING flashStr, CBYTE col, CBYTE row)
	//{
	//	return this->PrintString_P(flashStr, col, row, &LCD_I2C::WriteBig);
	//}

#endif
