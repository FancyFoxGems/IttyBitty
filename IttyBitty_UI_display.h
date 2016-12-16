/***********************************************************************************************
* [IttyBitty_UI_display.h]: RENDERING SUB-SYSTEM FOR MENUI DISPLAY INTEFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_DISPLAY_H
#define _ITTYBITTY_UI_DISPLAY_H


#include "IttyBitty_UI_options.h"

#ifndef NO_ITTYBITTY_EXTENSIONS
	#include "IttyBitty_LCD_I2C.h"
#endif

#include "Print.h"


// SUPRESS COMPILER WARNINGS RELATED TO PARAM REORDERING
IGNORE_WARNING(reorder)


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


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE Cols() const = 0;
		VIRTUAL CBYTE Rows() const = 0;

		VIRTUAL CBOOL IsLineWrapEnabled() const = 0;
		VIRTUAL VOID SetLineWrap(CBOOL = TRUE) = 0;

		VIRTUAL VOID CursorOn() = 0;
		VIRTUAL VOID CursorOff() = 0;

		VIRTUAL VOID CursorBlinkOn() = 0;
		VIRTUAL VOID CursorBlinkOff() = 0;

		VIRTUAL CBYTE CursorCol() = 0;
		VIRTUAL CBYTE CursorRow() = 0;

		VIRTUAL CCHAR StyledLineLeftGlyph() const = 0;
		VIRTUAL CCHAR StyledLineRightGlyph() const = 0;
		VIRTUAL CCHAR MenuItemGlyph() const = 0;
		VIRTUAL CCHAR ListChoiceGlyph() const = 0;
		VIRTUAL CCHAR CurrItemGlyph() const = 0;
		VIRTUAL CCHAR SelectionGlyph() const = 0;
		VIRTUAL CCHAR MultiSelectionGlyph() const = 0;
		VIRTUAL CCHAR ValueSeparatorGlyph() const = 0;


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

		// PUBLIC [UiOptions] MEMBER

		RUIRENDEREROPTIONS Options = MUI::DefaultUiRendererOptions;


		// CONSTRUCTORS

		UiRendererBase(CBOOL = FALSE);
		UiRendererBase(RUIRENDEREROPTIONS);


		// [IUiRenderer] IMPLEMENTATION

		VIRTUAL CBYTE Cols() const;
		VIRTUAL CBYTE Rows() const;

		VIRTUAL CBOOL IsLineWrapEnabled() const;
		VIRTUAL VOID SetLineWrap(CBOOL = TRUE);

		VIRTUAL VOID CursorOn();
		VIRTUAL VOID CursorOff();

		VIRTUAL VOID CursorBlinkOn();
		VIRTUAL VOID CursorBlinkOff();

		VIRTUAL CBYTE CursorCol();
		VIRTUAL CBYTE CursorRow();

		VIRTUAL CCHAR StyledLineLeftGlyph() const;
		VIRTUAL CCHAR StyledLineRightGlyph() const;
		VIRTUAL CCHAR MenuItemGlyph() const;
		VIRTUAL CCHAR ListChoiceGlyph() const;
		VIRTUAL CCHAR CurrItemGlyph() const;
		VIRTUAL CCHAR SelectionGlyph() const;
		VIRTUAL CCHAR MultiSelectionGlyph() const;
		VIRTUAL CCHAR ValueSeparatorGlyph() const;

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

	CLASS UiDisplayController : public UiRendererBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		UiDisplayController(CBYTE = 0, PPIUIRENDERER = NULL);
		UiDisplayController(RIUIRENDERER);

		VIRTUAL ~UiDisplayController();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// OPERATORS

		VIRTUAL PCIUIRENDERER operator[](CBYTE) const;
		VIRTUAL PIUIRENDERER operator[](CBYTE);


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE RendererCount() const;

		VIRTUAL RCIUIRENDERER Renderer(CBYTE = 0) const;
		VIRTUAL RIUIRENDERER Renderer(CBYTE = 0);

		VIRTUAL RIUIRENDERER AddRenderer(RIUIRENDERER);

		VIRTUAL VOID RemoveRenderer(CBYTE);
		VIRTUAL VOID RemoveRenderer(RIUIRENDERER);


		// [Print] IMPLEMENTATION

		SIZE write(BYTE);

		// [Print] OVERRIDES

		SIZE write(PCBYTE buffer, SIZE size);

		SIZE print(FLASH_STRING);
		SIZE print(CONST String &);
		SIZE print(PCCHAR);
		SIZE print(CHAR);
		SIZE print(BYTE, INT = DEC);
		SIZE print(INT, INT = DEC);
		SIZE print(UINT, INT = DEC);
		SIZE print(LONG, INT = DEC);
		SIZE print(DWORD, INT = DEC);
		SIZE print(DOUBLE, INT = 2);
		SIZE print(CONST Printable &);

		SIZE println(FLASH_STRING);
		SIZE println(CONST String &);
		SIZE println(PCCHAR);
		SIZE println(CHAR);
		SIZE println(BYTE, INT = DEC);
		SIZE println(INT, INT = DEC);
		SIZE println(UINT, INT = DEC);
		SIZE println(LONG, INT = DEC);
		SIZE println(DWORD, INT = DEC);
		SIZE println(DOUBLE, INT = 2);
		SIZE println(CONST Printable &);
		SIZE println();

		INT printf(PCCHAR format, ...) PRINTF_FORMAT(2, 3) ;
		INT printf(FLASH_STRING format, ...);


		// [IUiRenderer] OVERRIDES

		CBOOL IsLcdBased() const;

		CBYTE Cols() const;
		CBYTE Rows() const;

		CBOOL IsLineWrapEnabled() const;
		VOID SetLineWrap(CBOOL = TRUE);

		VOID CursorOn();
		VOID CursorOff();

		VOID CursorBlinkOn();
		VOID CursorBlinkOff();

		CBYTE CursorCol();
		CBYTE CursorRow();

		CBOOL Available();
		VOID Flush();

		VOID Clear();
		VOID ClearCol(CBYTE = MAX_BYTE);
		VOID ClearRow(CBYTE = MAX_BYTE);

		VOID ScrollLeft();
		VOID ScrollRight();

		VOID Home();
		VOID CursorPrev();
		VOID CursorNext();
		VOID MoveCursor(CBYTE = MAX_BYTE, CBYTE = MAX_BYTE);

		VOID LoadCustomChar(BYTE, PCBYTE);
		VOID LoadCustomChar_P(BYTE, PCBYTE);

		CBYTE WriteAt(CBYTE, CBYTE, CBYTE);

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

		BOOL _Dispose = FALSE;

		PPIUIRENDERER _Renderers = NULL;
		BYTE _RendererCount = 0;
	};

#pragma endregion
};

#endif