/***********************************************************************************************
* [IttyBitty_menu_display.h]: RENDERING SUB-SYSTEM FOR MENUI DISPLAY INTEFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_DISPLAY_H
#define _ITTYBITTY_MENU_DISPLAY_H


#ifndef NO_ITTYBITTY_EXTENSIONS
	#include "IttyBitty_LCD_I2C.h"
#else
	#include "IttyBitty_bits.h"
#endif

#include "Print.h"


#pragma region DEFINES

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IUiRenderer;
	TYPEDEF_CLASS_ALIASES(IUiRenderer, IUIRENDERER);

	class UiRendererBase;
	TYPEDEF_CLASS_ALIASES(UiRendererBase, UIRENDERERBASE);


	class UiDisplayController;
	TYPEDEF_CLASS_ALIASES(UiDisplayController, UIDISPLAYCONTROLLER);

#pragma endregion


#pragma region [IUiRenderer] DEFINITION

	INTERFACE IUiRenderer : public Print
	{
	public:

		// ACCESSORS & MUTATORS

		VIRTUAL CBOOL IsLineWrapEnabled() = 0;
		VIRTUAL VOID SetLineWrap(CBOOL wrapLines = TRUE) = 0;

		VIRTUAL CBYTE CursorCol() = 0;
		VIRTUAL CBYTE CursorRow() = 0;

		VIRTUAL VOID CursorOn() = 0;
		VIRTUAL VOID CursorOff() = 0;

		VIRTUAL VOID CursorBlinkOn() = 0;
		VIRTUAL VOID CursorBlinkOff() = 0;

		// INTERFACE METHODS

		VIRTUAL CBOOL Available() = 0;

		VIRTUAL VOID Clear() = 0;
		VIRTUAL VOID ClearCol(CBYTE = MAX_BYTE) = 0;
		VIRTUAL VOID ClearRow(CBYTE = MAX_BYTE) = 0;

		VIRTUAL VOID ScrollLeft() = 0;
		VIRTUAL VOID ScrollRight() = 0;

		VIRTUAL VOID Home() = 0;
		VIRTUAL VOID CursorPrev() = 0;
		VIRTUAL VOID CursorNext() = 0;
		VIRTUAL VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE) = 0;

		VIRTUAL VOID LoadCustomChar(BYTE charIndex, PCBYTE charData) = 0;
		VIRTUAL VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr) = 0;

		VIRTUAL CBYTE WriteAt(CBYTE value, CBYTE col, CBYTE row) = 0;

		VIRTUAL CBYTE PrintString(PCCHAR str, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE) = 0;
		VIRTUAL CBYTE PrintString_P(FLASH_STRING flashStr, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE) = 0;

		VIRTUAL CBYTE PrintStyledLine(PCCHAR str, BYTE row = MAX_BYTE) = 0;
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING flashStr, BYTE row = MAX_BYTE) = 0;

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options) = 0;
		VIRTUAL VOID DrawGraph(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options) = 0;
		VIRTUAL VOID DrawSlider(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage,
			CLCDSLIDEROPTIONS options, BOOL redraw = FALSE) = 0;
	#endif

	protected:

		IUiRenderer() { }
	};

#pragma endregion


#pragma region [UiRendererBase] DEFINITION

	CLASS UiRendererBase : public IUiRenderer
	{
	public:

		// [IUiRenderer] IMPLEMENTATION

		VIRTUAL CBOOL IsLineWrapEnabled(); // { return FALSE; };
		VIRTUAL VOID SetLineWrap(CBOOL wrapLines = TRUE); // { };

		VIRTUAL CBYTE CursorCol(); // { return MAX_BYTE; };
		VIRTUAL CBYTE CursorRow(); // { return MAX_BYTE; };

		VIRTUAL VOID CursorOn(); // { }
		VIRTUAL VOID CursorOff(); // { }

		VIRTUAL VOID CursorBlinkOn(); // { }
		VIRTUAL VOID CursorBlinkOff(); // { }

		VIRTUAL CBOOL Available(); // { return TRUE; }

		VIRTUAL VOID Clear(); // { }
		VIRTUAL VOID ClearCol(); // { }
		VIRTUAL VOID ClearRow(); // { }

		VIRTUAL VOID ScrollLeft(); // { }
		VIRTUAL VOID ScrollRight(); // { }

		VIRTUAL VOID Home(); // { }
		VIRTUAL VOID CursorPrev(); // { }
		VIRTUAL VOID CursorNext(); // { }
		VIRTUAL VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE); // { }

		VIRTUAL VOID LoadCustomChar(BYTE charIndex, PCBYTE charData); // { }
		VIRTUAL VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr); // { }

		VIRTUAL CBYTE WriteAt(CBYTE value, CBYTE col, CBYTE row); // { }

		VIRTUAL CBYTE PrintString(PCCHAR str, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE); // { }
		VIRTUAL CBYTE PrintString_P(FLASH_STRING flashStr, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE); // { }

		VIRTUAL CBYTE PrintStyledLine(PCCHAR str, BYTE row = MAX_BYTE); // { }
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING flashStr, BYTE row = MAX_BYTE); // { }

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options); // { }
		VIRTUAL VOID DrawGraph(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options); // { }
		VIRTUAL VOID DrawSlider(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage,
			CLCDSLIDEROPTIONS options, BOOL redraw = FALSE); // { }
	#endif
	};

#pragma endregion


#pragma region [UiDisplayController] DEFINITION

	CLASS UiDisplayController : public IUiRenderer
	{
	public:

		// [IUiRenderer] IMPLEMENTATION

		VIRTUAL CBOOL IsLineWrapEnabled(); // { return FALSE; };
		VIRTUAL VOID SetLineWrap(CBOOL wrapLines = TRUE); // { };

		VIRTUAL CBYTE CursorCol(); // { return MAX_BYTE; };
		VIRTUAL CBYTE CursorRow(); // { return MAX_BYTE; };

		VIRTUAL CBOOL Available(); // { return TRUE; }

		VIRTUAL VOID Clear(); // { }
		VIRTUAL VOID ClearCol(); // { }
		VIRTUAL VOID ClearRow(); // { }

		VIRTUAL VOID ScrollLeft(); // { }
		VIRTUAL VOID ScrollRight(); // { }

		VIRTUAL VOID Home(); // { }
		VIRTUAL VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE); // { }

		VIRTUAL VOID LoadCustomChar(BYTE charIndex, PCBYTE charData); // { }
		VIRTUAL VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr); // { }

		VIRTUAL CBYTE WriteAt(CBYTE value, CBYTE col, CBYTE row); // { }

		VIRTUAL CBYTE PrintString(PCCHAR str, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE); // { }
		VIRTUAL CBYTE PrintString_P(FLASH_STRING flashStr, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE); // { }

		VIRTUAL CBYTE PrintStyledLine(PCCHAR str, BYTE row = MAX_BYTE); // { }
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING flashStr, BYTE row = MAX_BYTE); // { }

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE percentage, CLCDSCROLLBAROPTIONS options); // { }
		VIRTUAL VOID DrawGraph(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage, CLCDGRAPHOPTIONS options); // { }
		VIRTUAL VOID DrawSlider(BYTE startCol, BYTE row, BYTE widthChars, BYTE percentage,
			CLCDSLIDEROPTIONS options, BOOL redraw = FALSE); // { }
	#endif


	protected:

		// INSTANCE VARIABLES


		BYTE _Cols = 0;
		BYTE _Rows = 0;
	};

#pragma endregion
};

#endif
