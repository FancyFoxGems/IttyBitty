/***********************************************************************************************
* [IttyBitty_menui.h]: MENU-BASED UI SYSTEM W/ INPUT FIELDS AND EXTENSIBLE NAVIGATION/DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENUI_H
#define _ITTYBITTY_MENUI_H


#include "IttyBitty_UI_menus.h"
#include "IttyBitty_UI_field_decorators.h"

#ifndef NO_ITTYBITTY_EXTENSIONS
	#include "IttyBitty_LCD_I2C.h"
#endif


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class MenUI;
	TYPEDEF_CLASS_ALIASES(MenUI, MENUI);


	typedef VOID UiCallback(RMENUI, PTR, CPTR), UICALLBACK(RMENUI, PTR, CPTR),
		(*PUICALLBACK)(RMENUI, PTR, CPTR), (**PPUICALLBACK)(RMENUI, PTR, CPTR);

#pragma endregion


#pragma region [MenUI] DEFINITION

	CLASS MenUI : public Menu, public IUiNavigationController, public IUiDisplayController
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MenUI(FLASH_STRING = NULL, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);
		MenUI(CBYTE, PPIUIINPUTSOURCE, CBYTE, PPIUIRENDERER, FLASH_STRING = NULL, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~MenUI() { }


		// ACCESSORS/MUTATORS

		PUICALLBACK GetIdleHandler() const;
		VOID SetIdleHandler(PUICALLBACK);


		// USER METHODS

		VOID Update();

		VOID ShowText(PCCHAR, CWORD = MENUI_DEFAULT_TEXT_TIMEOUT_MS,
			CBOOL = MENUI_DEFAULT_TEXT_ALLOW_ESCAPE,
			CBOOL = MENUI_DEFAULT_TEXT_ANY_ACTION_RETURNS);
		VOID ShowText_P(FLASH_STRING, CWORD = MENUI_DEFAULT_TEXT_TIMEOUT_MS,
			CBOOL = MENUI_DEFAULT_TEXT_ALLOW_ESCAPE,
			CBOOL = MENUI_DEFAULT_TEXT_ANY_ACTION_RETURNS);

		VOID Prompt(RUIDIALOG dialog);

		template<typename T>
		CONST T Prompt(RIUIFIELD<T> field)
		{
			if (field.Prompt(_Display))
				return field.Value();

			return T(T_MAX);
		}


		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE = CLICK);
		VOID Down(CUIACTIONSTATE = CLICK);
		VOID Left(CUIACTIONSTATE = CLICK);
		VOID Right(CUIACTIONSTATE = CLICK);
		VOID Return(CUIACTIONSTATE = CLICK);
		VOID Select(CUIACTIONSTATE = CLICK);


		// [IUiNavigationController] IMPLEMENTATION

		VIRTUAL CBYTE InputSourceCount() const;

		VIRTUAL RCIUIINPUTSOURCE InputSource(CBYTE = 0) const;
		VIRTUAL RIUIINPUTSOURCE InputSource(CBYTE = 0);

		VIRTUAL CBOOL AddInputSource(RIUIINPUTSOURCE);

		VIRTUAL VOID RemoveInputSource(CBYTE);
		VIRTUAL VOID RemoveInputSource(RIUIINPUTSOURCE);

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();


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
		VIRTUAL VOID SetLineWrap(CBOOL = TRUE);

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


	protected:

		// INSTANCE VARIABLES

		UINAVIGATIONCONTROLLER _Navigation;
		UIDISPLAYCONTROLLER _Display;

		WORD _TextShownMS = 0;


		// EVENT CALLBACKS

		PUICALLBACK _OnIdleHandler = NULL;
	};

#pragma endregion
};

#endif
