/***********************************************************************************************
* [IttyBitty_UI_elements.h]: SPECIALIZED MENU ITEM TYPES TO ALLOW FOR DATA ENTRY AND DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_ELEMENTS_H
#define _ITTYBITTY_UI_ELEMENTS_H


#include "IttyBitty_UI_nav.h"
#include "IttyBitty_UI_display.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IUiElement;
	TYPEDEF_CLASS_ALIASES(UiElement, UIELEMENT);

	class UiElementBase;
	TYPEDEF_CLASS_ALIASES(UiElement, UIELEMENT);


	#define UI_LIST_ELEMENT_T_CLAUSE_DEF	<class TElement>
	#define UI_LIST_ELEMENT_T_CLAUSE		<class TElement>
	#define UI_LIST_ELEMENT_T_ARGS			<TElement>

	template UI_LIST_ELEMENT_T_CLAUSE
	interface IUiContainerElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_LIST_ELEMENT_T_CLAUSE), \
		CSL(UI_LIST_ELEMENT_T_ARGS), IUiContainerElement, IUICONTAINERELEMENT);

	interface IUiChoice;
	TYPEDEF_CLASS_ALIASES(IUiChoice, IUICHOICE);

	template UI_LIST_ELEMENT_T_CLAUSE
	interface IUiListElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_LIST_ELEMENT_T_CLAUSE), \
		CSL(UI_LIST_ELEMENT_T_ARGS), IUiListElement, IUILISTELEMENT);


	interface IUiDialog;
	TYPEDEF_CLASS_ALIASES(IUiDialog, IUIDIALOG);

	class UiDialog;
	TYPEDEF_CLASS_ALIASES(UiDialog, UIDIALOG);

#pragma endregion


#pragma region [IUiElement] DEFINITION

	INTERFACE IUiElement : public IUiNavigationListener
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE Height() const = 0;
		VIRTUAL CBYTE Width() const = 0;
		VIRTUAL CBYTE TopOffset() const = 0;
		VIRTUAL CBYTE LeftOffset() const = 0;


		// INTERFACE METHODS

		VIRTUAL VOID Render(PIUIRENDERER) = 0;


	protected:

		IUiElement() { }
	};

#pragma endregion


#pragma region [IUiContainerElement] DEFINITION

	template UI_LIST_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiContainerElement : public IUiElement
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiContainerElement() { }


		// OPERATORS

		VIRTUAL CONST TElement * operator[](CBYTE) const = 0;
		VIRTUAL TElement * operator[](CBYTE) = 0;


		// ACCESSORS

		VIRTUAL CBYTE ChildCount() const = 0;

		VIRTUAL CONST TElement & Child(CBYTE) const = 0;
		VIRTUAL TElement & Child(CBYTE) = 0;


		// INTERFACE METHODS


	protected:

		IUiContainerElement() { }
	};

#pragma endregion


#pragma region [IUiChoice] DEFINITION

	INTERFACE IUiChoice : public IUiElement
	{
	public:


		// ACCESSORS/MUTATORS


		// INTERFACE METHODS


	protected:

		IUiChoice() { }
	};

#pragma endregion


#pragma region [IUiListElement] DEFINITION

	template UI_LIST_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiListElement : public IUiContainerElement<TElement>
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiListElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL MultipleSelectionsAllowed() const = 0;
		VIRTUAL VOID SetAllowMultipleSelections(CBOOL) = 0;


	protected:

		IUiListElement() { }
	};

#pragma endregion


#pragma region [IUiDialog] DEFINITION

	INTERFACE IUiDialog : public IUiElement
	{
	public:


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL ShowMessage() const = 0;


		// INTERFACE METHODS

		VIRTUAL VOID Prompt(PIUIRENDERER) = 0;


	protected:

		IUiDialog() { }
	};

#pragma endregion


#pragma region [UiElementBase] DEFINITION

	CLASS UiElementBase : public IUiElement
	{
	public:

		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL VOID IsShiftOn();
		VIRTUAL VOID IsAltOn();
		VIRTUAL VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


		// [IUiElement] IMPLEMENTATION

		VIRTUAL CBYTE Height() const;
		VIRTUAL CBYTE Width() const;
		VIRTUAL CBYTE TopOffset() const;
		VIRTUAL CBYTE LeftOffset() const;

		VIRTUAL VOID Render(PIUIRENDERER);


	protected:

		// INSTANCE VARIABLES
	};

#pragma endregion


#pragma region [UiDialog] DEFINITION

	CLASS UiDialog : public UiElementBase, public IUiDialog
	{
	public:

		// [IUiDialog] IMPLEMENTATION

		VIRTUAL CBOOL ShowMessage() const;


		// INTERFACE METHODS

		VIRTUAL VOID Prompt(PIUIRENDERER);


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion
};

#endif
