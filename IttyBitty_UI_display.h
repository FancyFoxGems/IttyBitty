/***********************************************************************************************
* [IttyBitty_UI_display.h]: RENDERING SUB-SYSTEM FOR MENUI DISPLAY INTEFACE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_DISPLAY_H
#define _ITTYBITTY_UI_DISPLAY_H


#include "IttyBitty_expressions.h"
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

	interface IUiDisplayController;
	TYPEDEF_CLASS_ALIASES(IUiDisplayController, IUIDISPLAYCONTROLLER);


	class UiRenderer;
	TYPEDEF_CLASS_ALIASES(UiRenderer, UIRENDERER);

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

		VIRTUAL CBYTE CursorCol() const = 0;
		VIRTUAL CBYTE CursorRow() const = 0;

		VIRTUAL CBOOL IsLineWrapEnabled() const = 0;
		VIRTUAL VOID SetLineWrapEnabled(CBOOL = TRUE) = 0;

		VIRTUAL VOID CursorOn() = 0;
		VIRTUAL VOID CursorOff() = 0;

		VIRTUAL VOID CursorBlinkOn() = 0;
		VIRTUAL VOID CursorBlinkOff() = 0;


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
		VIRTUAL VOID DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL = FALSE) = 0;
	#endif


	protected:

		IUiRenderer() { }
	};

#pragma endregion


#pragma region [IUiDisplayController] DEFINITION

	INTERFACE IUiDisplayController : public IUiRenderer
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiDisplayController() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE RendererCount() const = 0;

		VIRTUAL RCIUIRENDERER Renderer(CBYTE = 0) const = 0;
		VIRTUAL RIUIRENDERER Renderer(CBYTE = 0) = 0;

		VIRTUAL CBOOL AddRenderer(RIUIRENDERER) = 0;

		VIRTUAL VOID RemoveRenderer(CBYTE) = 0;
		VIRTUAL VOID RemoveRenderer(RIUIRENDERER) = 0;


	protected:

		IUiDisplayController() { }
	};

#pragma endregion


#pragma region [UiRenderer] DEFINITION

	CLASS UiRenderer : public IUiRenderer
	{
	public:

		// PUBLIC [UiOptions] MEMBER

		RCUIRENDEREROPTIONS const Options;


		// CONSTRUCTORS

		UiRenderer();
		UiRenderer(RCUIRENDEREROPTIONS);


		// [IUiRenderer] IMPLEMENTATION

		VIRTUAL CBYTE Cols() const;
		VIRTUAL CBYTE Rows() const;

		VIRTUAL CBYTE CursorCol() const;
		VIRTUAL CBYTE CursorRow() const;

		VIRTUAL CBOOL IsLineWrapEnabled() const;
		VIRTUAL VOID SetLineWrapEnabled(CBOOL = TRUE);

		VIRTUAL VOID CursorOn();
		VIRTUAL VOID CursorOff();

		VIRTUAL VOID CursorBlinkOn();
		VIRTUAL VOID CursorBlinkOff();

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

	CLASS UiDisplayController : public IUiDisplayController
	{
	public:

		// CONSTRUCTOR/DESTRUCTOR

		UiDisplayController(CBYTE = 0, PPIUIRENDERER = NULL);

		VIRTUAL ~UiDisplayController();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// OPERATORS

		VIRTUAL PCIUIRENDERER operator[](CBYTE) const;
		VIRTUAL PIUIRENDERER operator[](CBYTE);


		// [IUiDisplayController] IMPLEMENTATION

		VIRTUAL CBYTE RendererCount() const;

		VIRTUAL RCIUIRENDERER Renderer(CBYTE = 0) const;
		VIRTUAL RIUIRENDERER Renderer(CBYTE = 0);

		VIRTUAL CBOOL AddRenderer(RIUIRENDERER);

		VIRTUAL VOID RemoveRenderer(CBYTE);
		VIRTUAL VOID RemoveRenderer(RIUIRENDERER);


		// [IUiRenderer] IMPLEMENTATION

		VIRTUAL CBYTE Cols() const;
		VIRTUAL CBYTE Rows() const;

		VIRTUAL CBYTE CursorCol() const;
		VIRTUAL CBYTE CursorRow() const;

		VIRTUAL CBOOL IsLineWrapEnabled() const;
		VIRTUAL VOID SetLineWrapEnabled(CBOOL = TRUE);

		VIRTUAL VOID CursorOn();
		VIRTUAL VOID CursorOff();

		VIRTUAL VOID CursorBlinkOn();
		VIRTUAL VOID CursorBlinkOff();

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


		// [Print] IMPLEMENTATION

		VIRTUAL SIZE write(BYTE);

		using Print::write;


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		PPIUIRENDERER _Renderers = NULL;
		BYTE _RendererCount = 0;
	};

#pragma endregion
};

#endif
