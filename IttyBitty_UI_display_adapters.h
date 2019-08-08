/***********************************************************************************************
* [IttyBitty_UI_display_adapters.h]: RENDERING ADAPTERS FOR DISPLAY OF MENUI ELEMENTS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_DISPLAY_ADAPTERS_H
#define _ITTYBITTY_UI_DISPLAY_ADAPTERS_H


#include "IttyBitty_UI_display.h"

#ifndef NO_ITTYBITTY_LCD
	#include "IttyBitty_LCD_I2C.h"
#endif

#include "Stream.h"


// SUPRESS COMPILER WARNINGS RELATED TO NON-VIRTUAL DESTRUCTORS
IGNORE_WARNING(delete-non-virtual-dtor);


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class SerialUiRenderer;
	TYPEDEF_CLASS_ALIASES(SerialUiRenderer, SERIALUIRENDERER);


#ifndef NO_ITTYBITTY_LCD

	#define LCDI2C_UI_RENDERER_T_CLAUSE_DEF	<CBYTE LineChars, CBYTE Lines, CBYTE I2CAddr, BOOL Use5x10Chars>
	#define LCDI2C_UI_RENDERER_T_CLAUSE		<CBYTE LineChars = LCD_DEFAULT_COLS, CBYTE Lines = LCD_DEFAULT_ROWS, \
		CBYTE I2CAddr = LCD_DEFAULT_I2C_ADDRESS, BOOL Use5x10Chars = FALSE>
	#define LCDI2C_UI_RENDERER_T_ARGS		<LineChars, Lines, I2CAddr, Use5x10Chars>

	template LCDI2C_UI_RENDERER_T_CLAUSE
	class LcdI2CUiRenderer;
	TEMPLATE_CLASS_USING_ALIASES(CSL(LCDI2C_UI_RENDERER_T_CLAUSE),
		CSL(LCDI2C_UI_RENDERER_T_ARGS), LcdI2CUiRenderer, LCDI2CUIRENDERER);

#endif	// #ifndef NO_ITTYBITTY_LCD

#pragma endregion


#pragma region ENUMS

	ENUM_CLASS UiListItemNumberingFormat : BYTE
	{
		NONE				= 0x0,
		NUMBER_DASH			= 0x1,
		NUMBER_DOT			= 0x2,
		NUMBER_PAREN		= 0x3,
		PAREN_NUMBER_PAREN	= 0x4,
		BRACKETED_NUMBER	= 0x5
	};

	TYPEDEF_ENUM_ALIASES(UiListItemNumberingFormat, UILISTITEMNUMBERINGFORMAT);

#pragma endregion


#pragma region [SerialUiRenderer] DEFINITION

	CLASS SerialUiRenderer : public UiRendererBase
	{
	public:

		// CONSTRUCTORS

		SerialUiRenderer(HardwareSerial & = SERIAL_PORT_MONITOR, CUILISTITEMNUMBERINGFORMAT = UiListItemNumberingFormat::NUMBER_DASH);
		SerialUiRenderer(RUIRENDEREROPTIONS, HardwareSerial & = SERIAL_PORT_MONITOR, CUILISTITEMNUMBERINGFORMAT = UiListItemNumberingFormat::NUMBER_DASH);


		// [Print] OVERRIDE

		VIRTUAL SIZE write(BYTE);


		// [IUiRenderer] OVERRIDES

		VIRTUAL CBOOL Available();
		VIRTUAL VOID Flush();

		VIRTUAL VOID BeginListItem(BYTE);
		VIRTUAL VOID EndListItem(CHAR = NULL_CHARACTER);


	protected:

		// INSTANCE VARIABLES

		HardwareSerial & _Serial = SERIAL_PORT_MONITOR;
		UILISTITEMNUMBERINGFORMAT _NumberingFormat = UiListItemNumberingFormat::NUMBER_DASH;
	};

#pragma endregion


#ifndef NO_ITTYBITTY_LCD

#pragma region [LcdI2CUiRenderer] DEFINITION

	template LCDI2C_UI_RENDERER_T_CLAUSE_DEF
	CLASS LcdI2CUiRenderer : public UiRendererBase
	{
	public:

		// CONSTRUCTOR/DESTRUCTOR

		LcdI2CUiRenderer(PLCDI2C LCDI2C_UI_RENDERER_T_ARGS lcd)
			: UiRendererBase(MUI::DefaultLcdRendererOptions()),
			_LCD(lcd) { }

		LcdI2CUiRenderer(PLCDI2C LCDI2C_UI_RENDERER_T_ARGS lcd, RUIRENDEREROPTIONS options)
			: UiRendererBase(options),
			_LCD(lcd) { }

		VIRTUAL ~LcdI2CUiRenderer()
		{
			if (_LCD)
			{
				delete _LCD;
				_LCD = NULL;
			}
		}


		// [Print] OVERRIDE

		VIRTUAL SIZE write(BYTE value)
		{
			return _LCD->write(value);
		}


		// [IUiRenderer] OVERRIDES

		VIRTUAL CBYTE Cols() const
		{
			return LineChars;
		}

		VIRTUAL CBYTE Rows() const
		{
			return Lines;
		}

		VIRTUAL CBYTE CursorCol()
		{
			return _LCD->CursorCol();
		}

		VIRTUAL CBYTE CursorRow()
		{
			return _LCD->CursorRow();
		}

		VIRTUAL CBOOL IsLineWrapEnabled() const
		{
			return _LCD->IsLineWrapEnabled();
		}

		VIRTUAL VOID SetLineWrapEnabled(CBOOL lineWrapEnabled = TRUE)
		{
			_LCD->SetLineWrapEnabled(lineWrapEnabled);
		}

		VIRTUAL VOID CursorOn()
		{
			_LCD->CursorOn();
		}

		VIRTUAL VOID CursorOff()
		{
			_LCD->CursorOff();
		}

		VIRTUAL VOID CursorBlinkOn()
		{
			_LCD->CursorBlinkOn();
		}

		VIRTUAL VOID CursorBlinkOff()
		{
			_LCD->CursorBlinkOff();
		}

		VIRTUAL VOID Clear()
		{
			_LCD->Clear();
		}

		VIRTUAL VOID ClearCol(CBYTE col = MAX_BYTE)
		{
			_LCD->ClearRow(col);
		}

		VIRTUAL VOID ClearRow(CBYTE row = MAX_BYTE)
		{
			_LCD->ClearRow(row);
		}

		VIRTUAL VOID ScrollLeft()
		{
			_LCD->ScrollLeft();
		}

		VIRTUAL VOID ScrollRight()
		{
			_LCD->ScrollRight();
		}

		VIRTUAL VOID Home()
		{
			_LCD->Home();
		}

		VIRTUAL VOID CursorPrev()
		{
			_LCD->CursorPrev();
		}

		VIRTUAL VOID CursorNext()
		{
			_LCD->CursorNext();
		}

		VIRTUAL VOID MoveCursor(CBYTE col = MAX_BYTE, CBYTE row = MAX_BYTE)
		{
			_LCD->MoveCursor(col, row);
		}

		VIRTUAL VOID LoadCustomChar(BYTE charIndex, PCBYTE charData)
		{
			_LCD->LoadCustomChar(charIndex, charData);
		}

		VIRTUAL VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
		{
			_LCD->LoadCustomChar_P(charIndex, charDataAddr);
		}

		VIRTUAL CBYTE WriteAt(CBYTE value, CBYTE col = MAX_BYTE, CBYTE row = MAX_BYTE)
		{
			return _LCD->WriteAt(value, col, row);
		}

		VIRTUAL CBYTE PrintString(PCCHAR str, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE)
		{
			return _LCD->PrintString(str, col, row);
		}

		VIRTUAL CBYTE PrintString_P(FLASH_STRING flashStr, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE)
		{
			return _LCD->PrintString_P(flashStr, col, row);
		}


	#ifndef NO_ITTYBITTY_EXTENSIONS

		VIRTUAL VOID DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options)
		{
			_LCD->DrawScrollBar(percentage, options);
		}

		VIRTUAL VOID DrawGraph(BYTE startCol, BYTE row,
			BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options)
		{
			_LCD->DrawGraph(startCol, row, widthChars, percentage, options);
		}

		VIRTUAL VOID DrawSlider(BYTE startCol, BYTE row, BYTE widthChars,
			BYTE percentage, CLCDSLIDEROPTIONS options, BOOL redraw = FALSE)
		{
			_LCD->DrawSlider(startCol, row, widthChars, percentage, options, redraw);
		}

	#endif	// #ifndef NO_ITTYBITTY_EXTENSIONS


	protected:

		// INSTANCE VARIABLES

		PLCDI2C LCDI2C_UI_RENDERER_T_ARGS _LCD = NULL;
	};

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_LCD
};

#endif
