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

#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
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

		// PUBLIC [UiOptions] MEMBER

		RUIOPTIONS const Options = MUI::Options;


		// CONSTRUCTORS/DESTRUCTOR

		MenUI(FLASH_STRING = NULL, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);
		MenUI(CBYTE, PPIUIINPUTSOURCE, CBYTE, PPIUIRENDERER, FLASH_STRING = NULL, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~MenUI();


	protected:

		// PROTECTED DISPOSAL METHODS

		VOID DisposeNavigationPtr();
		VOID DisposeDisplayPtr();


	public:

		// ACCESSORS/MUTATORS

		PUICALLBACK GetIdleHandler() const;
		VOID SetIdleHandler(PUICALLBACK);

		RUINAVIGATIONCONTROLLER GetNavigationController() const;
		VOID SetNavigationController(RUINAVIGATIONCONTROLLER);

		RUIDISPLAYCONTROLLER GetDisplayController() const;
		VOID SetDisplayController(RUIDISPLAYCONTROLLER);


		// USER METHODS

		VOID Initialize();

		VOID Update();

		VOID ShowMessage(PCCHAR, CWORD = MENUI_DEFAULT_MESSAGE_TIMEOUT_MS,
			CBOOL = MENUI_DEFAULT_MESSAGE_ALLOW_ESCAPE,
			CBOOL = MENUI_DEFAULT_MESSAGE_ANY_ACTION_RETURNS);
		VOID ShowMessage_P(FLASH_STRING, CWORD = MENUI_DEFAULT_MESSAGE_TIMEOUT_MS,
			CBOOL = MENUI_DEFAULT_MESSAGE_ALLOW_ESCAPE,
			CBOOL = MENUI_DEFAULT_MESSAGE_ANY_ACTION_RETURNS);

		VOID Prompt(RUIDIALOG dialog);

		template<typename T>
		CONST T Prompt(RIUIFIELD<T> field)
		{
			if (field.Prompt(*_DisplayPtr))
				return field.Value();

			return T(T_MAX);
		}


		// [IUiNavigationListener] OVERRIDES

		VIRTUAL VOID Up(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = CLICK);

		VIRTUAL VOID Value(RIUIINPUTVALUERESOLVER, CBYTE);


		// [IUiNavigationController] IMPLEMENTATION

		VIRTUAL CBYTE InputSourceCount() const;

		VIRTUAL RCIUIINPUTSOURCE InputSource(CBYTE = 0) const;
		VIRTUAL RIUIINPUTSOURCE InputSource(CBYTE = 0);

		VIRTUAL CBOOL AddInputSource(RIUIINPUTSOURCE);

		VIRTUAL VOID ClearInputSources();

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

		VIRTUAL VOID FireAction(CUIACTION, CUIACTIONSTATE = CLICK);
		VIRTUAL VOID SendValue(PCCHAR);


		// [IUiInputValueResolver] IMPLEMENTATION

		VIRTUAL CBYTE ValueEntryCount() const;

		VIRTUAL VOID RemoveValueEntry(CBYTE);
		VIRTUAL VOID ClearValueEntriesOlderThan(CDWORD);
		VIRTUAL VOID ClearValueEntries();

		VIRTUAL CBOOL ReadValueAsBool(CBYTE, CUIBOOLVALUEFLAGS = BOOL_VALUE_T_F);
		VIRTUAL CBYTE ReadValueAsByte(CBYTE);
		VIRTUAL CCHAR ReadValueAsChar(CBYTE);
		VIRTUAL CWCHAR ReadValueAsWChar(CBYTE);
		VIRTUAL CWORD ReadValueAsWord(CBYTE);
		VIRTUAL CSHORT ReadValueAsShort(CBYTE);
		VIRTUAL CDWORD ReadValueAsDWord(CBYTE);
		VIRTUAL CLONG ReadValueAsLong(CBYTE);
		VIRTUAL PCBYTE ReadValueAsBinary(CBYTE);
		VIRTUAL PCCHAR ReadValueAsString(CBYTE);


		// [IUiInputSource] IMPLEMENTATION

		VIRTUAL CBOOL IsAsynchronous() const;

		VIRTUAL VOID Poll();


		// [IUiDisplayController] IMPLEMENTATION

		VIRTUAL CBYTE RendererCount() const;

		VIRTUAL RCIUIRENDERER Renderer(CBYTE = 0) const;
		VIRTUAL RIUIRENDERER Renderer(CBYTE = 0);

		VIRTUAL CBOOL AddRenderer(RIUIRENDERER);

		VIRTUAL VOID ClearRenderers();

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
		VIRTUAL VOID ClearCol(BYTE = MAX_BYTE);
		VIRTUAL VOID ClearRow(BYTE = MAX_BYTE);
		VIRTUAL VOID ClearArea(BYTE, BYTE, BYTE, BYTE);

		VIRTUAL VOID ScrollLeft();
		VIRTUAL VOID ScrollRight();

		VIRTUAL VOID Home();
		VIRTUAL VOID CursorPrev();
		VIRTUAL VOID CursorNext();
		VIRTUAL VOID MoveCursor(BYTE = MAX_BYTE, BYTE = MAX_BYTE);

		VIRTUAL VOID LoadCustomChar(BYTE, PCBYTE);
		VIRTUAL VOID LoadCustomChar_P(BYTE, PCBYTE);

		VIRTUAL CBYTE WriteAt(BYTE, BYTE, BYTE);
		VIRTUAL CBYTE UpdateAt(BYTE, BYTE, BYTE);

		VIRTUAL CBYTE PrintString(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE);
		VIRTUAL CBYTE UpdateString(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE);
		VIRTUAL CBYTE PrintString_P(FLASH_STRING, BYTE = MAX_BYTE, BYTE = MAX_BYTE);
		VIRTUAL CBYTE UpdateString_P(FLASH_STRING, BYTE = MAX_BYTE, BYTE = MAX_BYTE);

		VIRTUAL CBYTE PrintStyledLine(PCCHAR, BYTE = MAX_BYTE, BYTE = MAX_BYTE, BYTE = 0);
		VIRTUAL CBYTE PrintStyledLine_P(FLASH_STRING, BYTE = MAX_BYTE, BYTE = MAX_BYTE, BYTE = 0);

		VIRTUAL CBYTE PrintGlyph(BYTE, BYTE = MAX_BYTE, BYTE = MAX_BYTE);

		VIRTUAL VOID BeginListItem(BYTE);
		VIRTUAL VOID EndListItem(CCHAR = NULL_CHARACTER);

	#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
		VIRTUAL VOID DrawScrollBar(BYTE, CLCDSCROLLBAROPTIONS);
		VIRTUAL VOID DrawGraph(BYTE, BYTE, BYTE, BYTE, CLCDGRAPHOPTIONS);
		VIRTUAL VOID DrawSlider(BYTE, BYTE, BYTE, BYTE, CLCDSLIDEROPTIONS, BOOL = FALSE);
	#endif


		// [Print] IMPLEMENTATION

		VIRTUAL SIZE write(BYTE);


	protected:

		// INSTANCE VARIABLES

		BOOL _DisposeNavigationPtr = FALSE;
		BOOL _DisposeDisplayPtr = FALSE;

		PUINAVIGATIONCONTROLLER _NavigationPtr;
		PUIDISPLAYCONTROLLER _DisplayPtr;

		WORD _TextShownMS = 0;


		// EVENT CALLBACKS

		PUICALLBACK _OnIdleHandler = NULL;
	};

#pragma endregion
};

#endif
