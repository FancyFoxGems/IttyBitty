/***********************************************************************************************
* [IttyBitty_LCD_extensions_decl.h]: METHOD DECLARATIONS FOR EXTENDED FUNCTIONALITY FOR
*	I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS, SUCH AS CHARACTER MANIPULATION,
*	SCROLL BARS, GRAPHS, AND SLIDERS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_EXTENSIONS_DECL_H
#define _ITTYBITTY_EXTENSIONS_DECL_H


#pragma region LCD EXTENSION HELPER FUNCTIONS

protected:

	PBYTE CreateScrollBarChar(BYTE cellPercentage, CLCDSCROLLBARINDICATOR indicator)
	{
		PBYTE scrollBarChar = new byte[CHAR_HEIGHT()];

		BYTE scrollerRow = cellPercentage == 100 ?
			LCD_CELL_LAST_PIXEL_ROW : cellPercentage * CHAR_HEIGHT() / 100;

		for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
		{
			if (pixY == scrollerRow)
				scrollBarChar[pixY] = LCD_SCROLLER_PIXEL_ROW;
			else
				scrollBarChar[pixY] = 0;
		}

		return scrollBarChar;
	}

	PBYTE CreateSpaceChar(CLCDSPACETYLE spaceStyle)
	{
		PBYTE spaceChar = new byte[CHAR_HEIGHT()];

		switch (spaceStyle)
		{
		case LcdSpaceStyle::DASH_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				if (pixY == LCD_CELL_MIDDLE_PIXEL_ROW)
					spaceChar[pixY] = LCD_CELL_LINE_PIXEL_ROW;
				else
					spaceChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
			}

			break;


		case LcdSpaceStyle::PLUS_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				switch (pixY)
				{
				case 3:
				case 5:

					spaceChar[pixY] = LCD_CELL_CENTER_PIXEL_ROW;
					break;


				case 4:

					spaceChar[pixY] = LCD_CELL_SMALL_DASH_PIXEL_ROW;
					break;


				default:

					spaceChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
				}
			}

			break;


		case LcdSpaceStyle::SQUARE_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				switch (pixY)
				{
				case 2:
				case CHAR_HEIGHT() - 2:

					spaceChar[pixY] = LCD_CELL_LINE_PIXEL_ROW;
					break;


				case 3:
				case 4:
				case 5:

					spaceChar[pixY] = LCD_CELL_FIRST_LAST_PIXEL_ROW;
					break;


				default:

					spaceChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
				}
			}


		case LcdSpaceStyle::DIAMOND_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				spaceChar[pixY] = pgm_read_byte_near(LCD_CHAR_SHAPE_DIAMOND + pixY);

			break;


		case LcdSpaceStyle::CIRCLE_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				spaceChar[pixY] = pgm_read_byte_near(LCD_CHAR_SHAPE_CIRCLE + pixY);

			break;


		case LcdSpaceStyle::LINES_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				switch (pixY)
				{
				case 0:
				case CHAR_HEIGHT() - 1:

					spaceChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
					break;


				default:

					spaceChar[pixY] = LCD_CELL_DOTS_PIXEL_ROW;
				}
			}

			break;


		case LcdSpaceStyle::DOTS_SPACE:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				if (pixY == LCD_CELL_MIDDLE_PIXEL_ROW)
					spaceChar[pixY] = LCD_CELL_DOTS_PIXEL_ROW;
				else
					spaceChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
			}

			break;


		default:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				spaceChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;

			break;
		}

		return spaceChar;
	}

	PBYTE CreateGraphFullCellChar(CLCDGRAPHCELL cellStyle, PBYTE spaceChar)
	{
		PBYTE fullCellChar = new byte[CHAR_HEIGHT()];

		switch (cellStyle)
		{
		case LcdGraphCell::BLOCK_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = LCD_CELL_LINE_PIXEL_ROW;

			break;


		case LcdGraphCell::LINE_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = spaceChar[pixY];

			fullCellChar[LCD_CELL_MIDDLE_PIXEL_ROW - 1] |= LCD_CELL_LINE_PIXEL_ROW;
			fullCellChar[LCD_CELL_MIDDLE_PIXEL_ROW] |= LCD_CELL_LINE_PIXEL_ROW;

			break;


		case LcdGraphCell::PLUS_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = spaceChar[pixY];

			fullCellChar[3] |= LCD_CELL_CENTER_PIXEL_ROW;
			fullCellChar[4] |= LCD_CELL_SMALL_DASH_PIXEL_ROW;
			fullCellChar[5] |= LCD_CELL_CENTER_PIXEL_ROW;

			break;


		case LcdGraphCell::SQUARE_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				fullCellChar[pixY] = spaceChar[pixY];

				if (pixY >= 3 AND pixY <=5)
					fullCellChar[pixY] |= LCD_CELL_SMALL_DASH_PIXEL_ROW;
			}

			break;


		case LcdGraphCell::DISC_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = spaceChar[pixY];

			for (BYTE pixY = 2; pixY < CHAR_HEIGHT() - 1; pixY++)
				fullCellChar[pixY] |= pgm_read_byte_near(LCD_CHAR_SHAPE_ROUND + pixY);

			break;


		case LcdGraphCell::DIAMOND_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = spaceChar[pixY];

			for (BYTE pixY = 2; pixY < CHAR_HEIGHT() - 1; pixY++)
				fullCellChar[pixY] |= pgm_read_byte_near(LCD_CHAR_SHAPE_DIAMOND + pixY);

			fullCellChar[3] |= LCD_CELL_DOTS_SPARSE_PIXEL_ROW;
			fullCellChar[5] |= LCD_CELL_DOTS_SPARSE_PIXEL_ROW;

			break;


		case LcdGraphCell::STRIPES_CELL:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = LCD_CELL_DOTS_PIXEL_ROW;

			break;


		default:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				fullCellChar[pixY] = LCD_CELL_LINE_PIXEL_ROW;
		}


		return fullCellChar;
	}

	PBYTE CreateGraphPartialCellChar(BYTE cellPercentage, PBYTE fullCellChar, PBYTE spaceChar)
	{
		PBYTE partialCellChar = new byte[CHAR_HEIGHT()];

		for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
		{
			partialCellChar[pixY] = spaceChar[pixY] | MASK(fullCellChar[pixY],
				LCD_CELL_LINE_PIXEL_ROW - (B((100 - cellPercentage) * CHAR_WIDTH() / 100) - 1));
		}

		return partialCellChar;
	}

	PBYTE CreateGraphSemiFillCellChar(BYTE cellPercentage, PBYTE fullCellChar)
	{
		PBYTE semiCellChar = new byte[CHAR_HEIGHT()];

		for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
		{
			if (cellPercentage <= 33)
				semiCellChar[pixY] = MASK(fullCellChar[pixY], LCD_CELL_SEMI_MASKS[0][pixY % 3]);
			else if (cellPercentage <= 66)
				semiCellChar[pixY] = MASK(fullCellChar[pixY], LCD_CELL_SEMI_MASKS[1][pixY % 2]);
			else
				semiCellChar[pixY] = MASK(fullCellChar[pixY], LCD_CELL_SEMI_MASKS[2][pixY % 3]);
		}

		return semiCellChar;
	}

	PBYTE CreateSliderMarker(CLCDSLIDERMARKER markerStyle)
	{
		PBYTE markerChar = new byte[CHAR_HEIGHT()];

		switch (markerStyle)
		{
		case LcdSliderMarker::CARET_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				switch (pixY)
				{
				case 1:

					markerChar[pixY] = LCD_CELL_CENTER_PIXEL_ROW;
					break;


				case 2:

					markerChar[pixY] = LCD_CELL_DOTS_SPARSE_PIXEL_ROW;
					break;


				default:

					markerChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
				}
			}

			break;


		case LcdSliderMarker::LINE_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				markerChar[pixY] = LCD_CELL_CENTER_PIXEL_ROW;

			break;


		case LcdSliderMarker::PLUS_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				switch (pixY)
				{
				case 3:
				case 5:

					markerChar[pixY] = LCD_CELL_CENTER_PIXEL_ROW;
					break;


				case 4:

					markerChar[pixY] = LCD_CELL_SMALL_DASH_PIXEL_ROW;
					break;


				default:

					markerChar[pixY] = LCD_CELL_BLANK_PIXEL_ROW;
				}
			}

			break;


		case LcdSliderMarker::SQUARE_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				switch (pixY)
				{
				case 3:
				case 4:
				case 5:

					markerChar[pixY] = LCD_CELL_SMALL_DASH_PIXEL_ROW;
					break;


				default:

					markerChar[pixY] = 0;
				}
			}

			break;


		case LcdSliderMarker::DIAMOND_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				markerChar[pixY] = pgm_read_byte_near(LCD_CHAR_SHAPE_ROUND + pixY);

			break;


		case LcdSliderMarker::DISC_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				markerChar[pixY] = pgm_read_byte_near(LCD_CHAR_SHAPE_ROUND + pixY);

			break;


		case LcdSliderMarker::TRIANGLE_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				markerChar[pixY] = pgm_read_byte_near(LCD_CHAR_SHAPE_TRIANGLE + pixY);

			break;


		case LcdSliderMarker::STRIPES_MARKER:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				markerChar[pixY] = LCD_CELL_DOTS_SPARSE_PIXEL_ROW;

			break;


		default:

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				markerChar[pixY] = LCD_CELL_LINE_PIXEL_ROW;
		}

		return markerChar;
	}

#pragma endregion


#pragma region LCD EXTENSIONS FUNCTION DEFINITIONS

public:

	PBYTE CreateInvertedChar(PBYTE lcdChar)
	{
		PBYTE newLcdChar = new byte[CHAR_HEIGHT()];

		for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			newLcdChar[pixY] = LCD_CELL_LINE_PIXEL_ROW - lcdChar[pixY];

		return newLcdChar;
	}

	PBYTE CreateInvertedChar_P(PCCHAR lcdChar)
	{
		PCHAR lcdCharData = new char[CHAR_HEIGHT()];

		for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
			lcdCharData[i] = pgm_read_byte_near(lcdChar++);

		return this->CreateInvertedChar((PBYTE)lcdCharData);
	}

	VOID LoadInvertedChar(BYTE customCharIdx, PBYTE lcdChar)
	{
		PBYTE invertedLcdChar = this->CreateInvertedChar(lcdChar);

		this->LoadCustomChar(customCharIdx, invertedLcdChar);

		delete invertedLcdChar;
	}

	VOID LoadInvertedChar_P(BYTE customCharIdx, PCCHAR lcdChar)
	{
		PBYTE invertedLcdChar = this->CreateInvertedChar_P(lcdChar);

		this->LoadCustomChar(customCharIdx, invertedLcdChar);

		delete invertedLcdChar;
	}

	VOID DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
	{
		BYTE col = LcdScrollBarOptionsToLcdScrollBarPosition(options)
			== LcdScrollBarPosition::LEFT_POSITION ? 0 : Cols - 1;
		BYTE currRow = percentage == 100 ? Rows - 1 : percentage * Rows / 100;

		PBYTE scrollBarChar = this->CreateScrollBarChar(percentage == 100 ? 100 :
				((10 * percentage) % (1000 / Rows)) * Rows / 10,
			LcdScrollBarOptionsToLcdScrollBarIndicator(options));
		this->LoadCustomChar(0x7, scrollBarChar);

		delete scrollBarChar;

		for (BYTE row = 0; row < Rows; row++)
		{
			this->MoveCursor(col, row);

			if (row == currRow)
				this->write(0x7);
			else
				this->write(LCD_SYMBOL_BLANK);
		}
	}

	VOID DrawGraph(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
	{
		CLCDGRAPHCELL cellStyle = LcdGraphOptionsToLcdGraphCell(options);
		CLCDSPACETYLE spaceStyle = LcdGraphOptionsToLcdSpaceStyle(options);

		PBYTE spaceChar = this->CreateSpaceChar(spaceStyle);
		this->LoadCustomChar(0x7, spaceChar);

		PBYTE fullCellChar = this->CreateGraphFullCellChar(cellStyle, spaceChar);
		this->LoadCustomChar(0x6, fullCellChar);

		if (((10 * percentage) % (1000 / widthChars)) / 10 > 0)
		{
			PBYTE partialCellChar = NULL;

			if (LcdGraphOptionsToLcdGraphPartialStyle(options) == LcdGraphPartialStyle::SEMI_FILL_PARTIAL)
			{
				partialCellChar = this->CreateGraphSemiFillCellChar(
					((10 * percentage) % (1000 / widthChars)) * widthChars / 10, fullCellChar);
			}
			else
			{
				partialCellChar = this->CreateGraphPartialCellChar(
					((10 * percentage) % (1000 / widthChars)) * widthChars / 10, fullCellChar, spaceChar);
			}

			this->LoadCustomChar(0x5, partialCellChar);

			delete partialCellChar;
		}

		delete spaceChar;
		delete fullCellChar;

		BYTE cellPercentage = 0;

		for (BYTE col = 0; col < widthChars; col++)
		{
			this->MoveCursor(col + startCol, row);

			if (10 * percentage <= col * 1000 / widthChars)
				this->write(0x7);
			else if (10 * percentage >= (col + 1) * 1000 / widthChars)
				this->write(0x6);
			else
				this->write(0x5);
		}
	}

	VOID DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
		BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw = FALSE)
	{
		CLCDSLIDERMARKER markerStyle = LcdSliderOptionsToLcdSliderMarker(options);
		CLCDSPACETYLE spaceStyle = LcdSliderOptionsToLcdSpaceStyle(options);

		if ((CBYTE)LcdSliderOptionsToLcdSliderEnds(options))
		{
			this->LoadCustomChar_P(0x4, LCD_CHAR_SLIDER_END_LEFT);

			this->MoveCursor(startCol, row);
			this->write(0x4);

			this->LoadCustomChar_P(0x3, LCD_CHAR_SLIDER_END_RIGHT);

			this->MoveCursor(startCol + widthChars - 1, row);
			this->write(0x3);

			++startCol;
			widthChars -= 2;
		}

		PBYTE spaceChar = this->CreateSpaceChar(spaceStyle);
		this->LoadCustomChar(0x7, spaceChar);

		PBYTE markerChar = this->CreateSliderMarker(markerStyle);

		PBYTE partialMarkerChar = NULL;
		CHAR cellOffset = MAX_CHAR;
		BYTE sliderCharIdx = 0x7;

	#ifdef DEBUG_ITTYBITTY_LCD
		this->MoveCursor(0, 0);
		this->print(percentage);
		this->write('%');
	#endif

		for (BYTE col = 0; col < widthChars; col++)
		{
			if (cellOffset < 0
				OR col > 0 AND 10 * percentage <= (col - 1) * 1000 / widthChars
				OR (percentage < 100 OR col < widthChars - 1)
					AND 10 * percentage >= (col + 1) * 1000 / widthChars)
			{
			#ifdef DEBUG_ITTYBITTY_LCD
				this->MoveCursor(col + startCol, 1);
				this->write(' ');
			#endif

				this->MoveCursor(col + startCol, row);
				this->write(0x7);

				if (col == widthChars - 1)
					this->write(0x7);

				cellOffset = MAX_CHAR;

				continue;
			}

			if(cellOffset == MAX_CHAR)
			{
				if (percentage == 100)
				{
					cellOffset = 2;
				}
				else if ((10 * percentage) % (1000 / widthChars) / 10 == 0)
				{

					cellOffset = -2;
				}
				else
				{
					cellOffset = ((CHAR)(((10 * percentage) % (1000 / widthChars)) *
						widthChars / 10) - 50) * (CHAR)CHAR_WIDTH() / 100;
				}
			}
			else if (cellOffset > 0)
			{
				cellOffset = -1 * ((CHAR)CHAR_WIDTH() - cellOffset);
			}
			else
			{
			#ifdef DEBUG_ITTYBITTY_LCD
				this->MoveCursor(col + startCol, 1);
				this->write(' ');
			#endif

				this->MoveCursor(col + startCol, row);
				this->write(0x7);

				continue;
			}

		#ifdef DEBUG_ITTYBITTY_LCD
			if (cellOffset >= 0)
			{
				this->MoveCursor(col + startCol, 1);
				this->write((CHAR)(cellOffset + 48));
			}
			else if (cellOffset == -4)
			{
				this->MoveCursor(col + startCol, 1);
				this->write(0x5C);
			}
			else if (cellOffset == -3)
			{
				this->MoveCursor(col + startCol, 1);
				this->print("|");
			}
			else if (cellOffset == -2)
			{
				this->MoveCursor(col + startCol, 1);
				this->print("/");
			}
			else if (cellOffset == -1)
			{
				this->MoveCursor(col + startCol, 1);
				this->print("-");
			}
			else
			{
				this->MoveCursor(col + startCol, 1);
				this->write((CHAR)(cellOffset + 48));
			}
		#endif

			--sliderCharIdx;

			if (!cellOffset)
			{
				for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
					markerChar[pixY] |= spaceChar[pixY];

				this->LoadCustomChar(sliderCharIdx, markerChar);

				this->MoveCursor(col + startCol, row);
				this->write(sliderCharIdx);

				continue;
			}

			partialMarkerChar = new byte[CHAR_HEIGHT()];

			if (cellOffset < 0)
			{
				for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
				{
					partialMarkerChar[pixY] = MASK(markerChar[pixY] SHL
						(255 - (CBYTE)cellOffset + 1), LCD_CELL_LINE_PIXEL_ROW);
				}
			}
			else
			{
				for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
					partialMarkerChar[pixY] = markerChar[pixY] SHR cellOffset;
			}

		#ifdef DEBUG_ITTYBITTY_LCD
			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				this->MoveCursor(pixY * 2 + 2, 2);
				this->print("  ");
				this->MoveCursor(pixY * 2 + 2, 2);
				this->print(partialMarkerChar[pixY]);
			}
		#endif

			for (BYTE pixY = 0; pixY < CHAR_HEIGHT(); pixY++)
			{
				partialMarkerChar[pixY] |= spaceChar[pixY];

			#ifdef DEBUG_ITTYBITTY_LCD
				this->MoveCursor(pixY * 2 + 2, 3);
				this->print("  ");
				this->MoveCursor(pixY * 2 + 2, 3);
				this->print(partialMarkerChar[pixY]);
			#endif
			}

			if (partialMarkerChar[0] == LCD_CELL_BLANK_PIXEL_ROW)
			{
				this->MoveCursor(col + startCol, row);
				this->write(0x7);
			}
			else
			{
				this->LoadCustomChar(sliderCharIdx, partialMarkerChar);

				this->MoveCursor(col + startCol, row);
				this->write(sliderCharIdx);

				this->MoveCursor(col + startCol + 1, row);
			}

			delete partialMarkerChar;
		}

		delete spaceChar;
		delete markerChar;
	}

#pragma endregion

#endif
