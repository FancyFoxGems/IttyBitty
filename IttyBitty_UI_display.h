/***********************************************************************************************
* [IttyBitty_UI_display.h]: RENDERING SUB-SYSTEM FOR MENUI DISPLAY INTEFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_DISPLAY_H
#define _ITTYBITTY_UI_DISPLAY_H


#ifndef NO_ITTYBITTY_EXTENSIONS
	#include "IttyBitty_LCD_I2C.h"
#else
	#include "IttyBitty_bits.h"
#endif

#include "Print.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IUiRenderer;
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

		// DESTRUCTOR

		VIRTUAL ~IUiRenderer() { }


		// ACCESSORS & MUTATORS

		VIRTUAL CBYTE Cols() const = 0;
		VIRTUAL CBYTE Rows() const = 0;

		VIRTUAL CBOOL IsLineWrapEnabled() = 0;
		VIRTUAL VOID SetLineWrap(CBOOL = TRUE) = 0;

		VIRTUAL VOID CursorOn() = 0;
		VIRTUAL VOID CursorOff() = 0;

		VIRTUAL VOID CursorBlinkOn() = 0;
		VIRTUAL VOID CursorBlinkOff() = 0;

		VIRTUAL CBYTE CursorCol() = 0;
		VIRTUAL CBYTE CursorRow() = 0;


		// INTERFACE METHODS

		VIRTUAL CBOOL Available() = 0;
		VIRTUAL VOID Flush() = 0;

		VIRTUAL VOID Clear() = 0;
		VIRTUAL VOID ClearCol(CBYTE = MAX_BYTE) = 0;
		VIRTUAL VOID ClearRow(CBYTE = MAX_BYTE) = 0;

		VIRTUAL VOID ScrollLeft() = 0;
		VIRTUAL VOID ScrollRight() = 0;

		VIRTUAL VOID Home() = 0;
		VIRTUAL VOID CursorPrev() = 0;
		VIRTUAL VOID CursorNext() = 0;
		VIRTUAL VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE) = 0;

		VIRTUAL VOID LoadCustomChar(BYTE, PCBYTE) = 0;
		VIRTUAL VOID LoadCustomChar_P(BYTE, PCBYTE) = 0;

		VIRTUAL CBYTE WriteAt(CBYTE, CBYTE, CBYTE) = 0;

		VIRTUAL CBYTE PrintString(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE) = 0;
		VIRTUAL CBYTE PrintString_P(FLASH_STRING, BYTE col = MAX_BYTE, BYTE = MAX_BYTE) = 0;

		VIRTUAL CBYTE PrintStyledLine(PCCHAR, BYTE = MAX_BYTE) = 0;
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING, BYTE = MAX_BYTE) = 0;

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS) = 0;
		VIRTUAL VOID DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS) = 0;
		VIRTUAL VOID DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL = FALSE);
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

		VIRTUAL CBYTE Cols() const;
		VIRTUAL CBYTE Rows() const;

		VIRTUAL CBOOL IsLineWrapEnabled();
		VIRTUAL VOID SetLineWrap(CBOOL = TRUE);

		VIRTUAL VOID CursorOn();
		VIRTUAL VOID CursorOff();

		VIRTUAL VOID CursorBlinkOn();
		VIRTUAL VOID CursorBlinkOff();

		VIRTUAL CBYTE CursorCol();
		VIRTUAL CBYTE CursorRow();

		VIRTUAL CBOOL Available();
		VIRTUAL VOID Flush();

		VIRTUAL VOID Clear();
		VIRTUAL VOID ClearCol(CBYTE = MAX_BYTE);
		VIRTUAL VOID ClearRow(CBYTE = MAX_BYTE);

		VIRTUAL VOID ScrollLeft();
		VIRTUAL VOID ScrollRight();

		VIRTUAL VOID Home();
		VIRTUAL VOID CursorPrev();
		VIRTUAL VOID CursorNext();
		VIRTUAL VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE);

		VIRTUAL VOID LoadCustomChar(BYTE, PCBYTE);
		VIRTUAL VOID LoadCustomChar_P(BYTE, PCBYTE);

		VIRTUAL CBYTE WriteAt(CBYTE, CBYTE, CBYTE);

		VIRTUAL CBYTE PrintString(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE);
		VIRTUAL CBYTE PrintString_P(FLASH_STRING, BYTE col = MAX_BYTE, BYTE = MAX_BYTE);

		VIRTUAL CBYTE PrintStyledLine(PCCHAR, BYTE = MAX_BYTE);
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING, BYTE = MAX_BYTE);

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS);
		VIRTUAL VOID DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS);
		VIRTUAL VOID DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL = FALSE);
	#endif
	};

#pragma endregion


#pragma region [UiDisplayController] DEFINITION

	CLASS UiDisplayController : public IUiRenderer
	{
	public:

		// [IUiRenderer] IMPLEMENTATION

		VIRTUAL CBYTE Cols() const;
		VIRTUAL CBYTE Rows() const;

		VIRTUAL CBOOL IsLineWrapEnabled();
		VIRTUAL VOID SetLineWrap(CBOOL = TRUE);

		VIRTUAL VOID CursorOn();
		VIRTUAL VOID CursorOff();

		VIRTUAL VOID CursorBlinkOn();
		VIRTUAL VOID CursorBlinkOff();

		VIRTUAL CBYTE CursorCol();
		VIRTUAL CBYTE CursorRow();

		VIRTUAL CBOOL Available();

		VIRTUAL VOID Clear();
		VIRTUAL VOID ClearCol(CBYTE = MAX_BYTE);
		VIRTUAL VOID ClearRow(CBYTE = MAX_BYTE);

		VIRTUAL VOID ScrollLeft();
		VIRTUAL VOID ScrollRight();

		VIRTUAL VOID Home();
		VIRTUAL VOID CursorPrev();
		VIRTUAL VOID CursorNext();
		VIRTUAL VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE);

		VIRTUAL VOID LoadCustomChar(BYTE, PCBYTE);
		VIRTUAL VOID LoadCustomChar_P(BYTE, PCBYTE);

		VIRTUAL CBYTE WriteAt(CBYTE, CBYTE, CBYTE);

		VIRTUAL CBYTE PrintString(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE);
		VIRTUAL CBYTE PrintString_P(FLASH_STRING, BYTE col = MAX_BYTE, BYTE = MAX_BYTE);

		VIRTUAL CBYTE PrintStyledLine(PCCHAR, BYTE = MAX_BYTE);
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING, BYTE = MAX_BYTE);

	#ifndef NO_ITTYBITTY_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS);
		VIRTUAL VOID DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS);
		VIRTUAL VOID DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL = FALSE);
	#endif


	protected:

		// INSTANCE VARIABLES


		BYTE _Cols = 0;
		BYTE _Rows = 0;
	};

#pragma endregion
};

#endif
