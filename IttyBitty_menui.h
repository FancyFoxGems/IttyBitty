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

#pragma endregion


#pragma region [MenUI] DEFINITION

	typedef VOID UiCallback(RMENUI, PTR, CPTR), UICALLBACK(RMENUI, PTR, CPTR),
		(*PUICALLBACK)(RMENUI, PTR, CPTR), (**PPUICALLBACK)(RMENUI, PTR, CPTR);

	CLASS MenUI : public Menu, public IUiRenderer
	{
	public:

		// PUBLIC [UiOptions] MEMBER

		RUIOPTIONS Options = MUI::Options;


		// CONSTRUCTORS/DESTRUCTOR

		MenUI(CBYTE, PPIMENUITEM, CBOOL = TRUE);
		MenUI(CBYTE initMenuCapacity = MENUI_DEFAULT_MENU_CAPACITY, CBOOL useGlobalOptions = TRUE);


		// ACCESSORS/MUTATORS

		PUINAVIGATIONCONTROLLER Navigation();
		PUIDISPLAYCONTROLLER Display();

		VOID SetIdleCallback(PUICALLBACK onIdleCallback);


		// USER METHODS

		VOID Update();

		VOID ShowText(PCCHAR str, CWORD timeoutMS = MENUI_DEFAULT_TEXT_TIMEOUT_MS,
			CBOOL allowEscape = MENUI_DEFAULT_TEXT_ALLOW_ESCAPE,
			CBOOL anyActionReturns = MENUI_DEFAULT_TEXT_ANY_ACTION_RETURNS);
		VOID ShowText_P(FLASH_STRING flashStr, CWORD timeoutMS = MENUI_DEFAULT_TEXT_TIMEOUT_MS,
			CBOOL allowEscape = MENUI_DEFAULT_TEXT_ALLOW_ESCAPE,
			CBOOL anyActionReturns = MENUI_DEFAULT_TEXT_ANY_ACTION_RETURNS);

		VOID Prompt(RUIDIALOG dialog);

		template<typename T>
		CONST T Prompt(RIUIFIELD field)
		{
			if (field.Prompt(_Display))
				return (T)field.Value();

			return T(T_MAX);
		}


		// [IUiNavigationListener] OVERRIDES

		CBOOL IsShiftOn() const;
		VOID ToggleShift();
		VOID ShiftOn();
		VOID ShiftOff();

		CBOOL IsAltOn() const;
		VOID ToggleAlt();
		VOID AltOn();
		VOID AltOff();

		VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


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

		PUIDISPLAYCONTROLLER _Display = NULL;
		PUINAVIGATIONCONTROLLER _Navigation = NULL;


		// EVENT CALLBACKS

		PUICALLBACK _OnIdleCallback = NULL;
	};

#pragma endregion
};

#endif
