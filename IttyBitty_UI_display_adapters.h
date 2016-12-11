/***********************************************************************************************
* [IttyBitty_UI_display_adapters.h]: RENDERING ADAPTERS FOR DISPLAY OF MENUI ELEMENTS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_DISPLAY_ADAPTERS_H
#define _ITTYBITTY_UI_DISPLAY_ADAPTERS_H


#include "IttyBitty_UI_display.h"

#ifndef NO_ITTYBITTY_LCD
	#include "IttyBitty_LCD_I2C.h"
#endif

#include "HardwareSerial.h"


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


#pragma region [SerialUiRenderer] DEFINITION

	CLASS SerialUiRenderer : public UiRendererBase
	{
	public:

		// [Print] OVERRIDES

		SIZE write(BYTE);


		// [IUiRenderer] IMPLEMENTATION

		CBYTE Cols() const;
		CBYTE Rows() const;

		CBOOL IsLineWrapEnabled();
		VOID SetLineWrap(CBOOL = TRUE);

		CBYTE CursorCol();
		CBYTE CursorRow();

		CBOOL Available();
		VOID Flush();

		CBYTE PrintString(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE);
		CBYTE PrintString_P(FLASH_STRING, BYTE col = MAX_BYTE, BYTE = MAX_BYTE);

		CBYTE PrintStyledLine(PCCHAR, BYTE = MAX_BYTE);
		CBYTE PrintStyledLine_P(FLASH_STRING, BYTE = MAX_BYTE);

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VOID DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS);
		VOID DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS);
		VOID DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL = FALSE);
	#endif


	protected:

		// INSTANCE VARIABLES

		HardwareSerial & _Serial = SERIAL_PORT_MONITOR;
	};

#pragma endregion


#ifndef NO_ITTYBITTY_LCD

#pragma region [LcdI2CUiRenderer] DEFINITION

	template LCDI2C_UI_RENDERER_T_CLAUSE_DEF
	CLASS LcdI2CUiRenderer : public UiRendererBase
	{
	public:

		// [Print] OVERRIDES

		SIZE write(BYTE);

		// [IUiRenderer] IMPLEMENTATION


	protected:

		// INSTANCE VARIABLES

		PLCDI2C LCDI2C_UI_RENDERER_T_ARGS _LCD = NULL;
	};

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_LCD
};

#endif
