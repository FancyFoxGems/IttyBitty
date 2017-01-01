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
	TYPEDEF_CLASS_ALIASES(IUiElement, IUIELEMENT);

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

#pragma endregion


#pragma region [IUiElement] DEFINITION

	INTERFACE IUiElement : public virtual IUiNavigationListener
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL PIUIELEMENT Parent() const = 0;

		VIRTUAL CBYTE Width() const = 0;
		VIRTUAL CBYTE Height() const = 0;

		VIRTUAL CBYTE GetLeft() const = 0;
		VIRTUAL VOID SetLeft(CBYTE) = 0;

		VIRTUAL CBYTE GetTop() const = 0;
		VIRTUAL VOID SetTop(CBYTE) = 0;

		VIRTUAL PCCHAR GetLabel() const = 0;
		VIRTUAL VOID SetLabel(PCCHAR) = 0;

		VIRTUAL PPCCHAR Lines() const = 0;


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

		VIRTUAL CONST TElement & Child(CBYTE = 0) const = 0;
		VIRTUAL TElement & Child(CBYTE = 0) = 0;

		VIRTUAL TElement & AddChild(TElement &);

		VIRTUAL VOID RemoveChild(CBYTE);
		VIRTUAL VOID RemoveChild(TElement &);


		// INTERFACE METHODS


	protected:

		IUiContainerElement() { }
	};

#pragma endregion


#pragma region [UiElementBase] DEFINITION

	CLASS UiElementBase : public IUiElement
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		UiElementBase(PIUIELEMENT, PCCHAR, CBYTE = MAX_BYTE, CBYTE = 1, CBYTE = 0, CBYTE = 0);
		UiElementBase(PIUIELEMENT, FLASH_STRING, CBYTE = MAX_BYTE, CBYTE = 1, CBYTE = 0, CBYTE = 0);

		VIRTUAL ~UiElementBase();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IUiElement] IMPLEMENTATION

		VIRTUAL PIUIELEMENT Parent() const;

		VIRTUAL CBYTE Width() const;
		VIRTUAL CBYTE Height() const;

		VIRTUAL CBYTE GetLeft() const;
		VIRTUAL VOID SetLeft(CBYTE);

		VIRTUAL CBYTE GetTop() const ;
		VIRTUAL VOID SetTop(CBYTE);

		VIRTUAL PCCHAR GetLabel() const;
		VIRTUAL VOID SetLabel(PCCHAR);

		VIRTUAL PPCCHAR Lines() const;

		VIRTUAL VOID Render(PIUIRENDERER);


		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL CBOOL IsShiftOn() const;
		VIRTUAL VOID ToggleShift();
		VIRTUAL VOID ShiftOn();
		VIRTUAL VOID ShiftOff();

		VIRTUAL CBOOL IsAltOn() const;
		VIRTUAL VOID ToggleAlt();
		VIRTUAL VOID AltOn();
		VIRTUAL VOID AltOff();

		VIRTUAL VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		PIUIELEMENT _Parent = NULL;

		CBYTE _Width = 0;
		CBYTE _Height = 0;

		CBYTE _Left = 0;
		CBYTE _Top = 0;

		PCCHAR _Label = NULL;
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
		VIRTUAL VOID SetAllowMultipleSelections(CBOOL = TRUE) = 0;


	protected:

		IUiListElement() { }
	};

#pragma endregion
};

#endif
