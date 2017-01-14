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


	#define UI_CONTAINER_ELEMENT_T_CLAUSE_DEF	<class TChild = IUiElement>
	#define UI_CONTAINER_ELEMENT_T_CLAUSE		<class TChild>
	#define UI_CONTAINER_ELEMENT_T_ARGS			<TChild>

	template UI_CONTAINER_ELEMENT_T_CLAUSE
	interface IUiContainerElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_T_ARGS), IUiContainerElement, IUICONTAINERELEMENT);

	template UI_CONTAINER_ELEMENT_T_CLAUSE
	interface IUiListElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_T_ARGS), IUiListElement, IUILISTELEMENT);

	template UI_CONTAINER_ELEMENT_T_CLAUSE
	interface IUiMultiListElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_T_ARGS), IUiMultiListElement, IUIMULTILISTELEMENT);


	#define UI_CHILD_ELEMENT_T_CLAUSE_DEF	<class TParent>
	#define UI_CHILD_ELEMENT_T_CLAUSE		<class TParent>
	#define UI_CHILD_ELEMENT_T_ARGS			<TParent>

	template UI_CHILD_ELEMENT_T_CLAUSE
	interface IUiChildElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CHILD_ELEMENT_T_CLAUSE), \
		CSL(UI_CHILD_ELEMENT_T_ARGS), IUiChildElement, IUICHILDELEMENT);

	template UI_CHILD_ELEMENT_T_CLAUSE
	interface IUiChoice;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CHILD_ELEMENT_T_CLAUSE), \
		CSL(UI_CHILD_ELEMENT_T_ARGS), IUiChoice, IUICHOICE);


	class UiElementBase;
	TYPEDEF_CLASS_ALIASES(UiElement, UIELEMENT);

	template UI_CONTAINER_ELEMENT_T_CLAUSE
	interface UiContainerElementBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_T_ARGS), UiContainerElementBase, UICONTAINERELEMENTBASE);

#pragma endregion


#pragma region [IUiElement] DEFINITION

	INTERFACE IUiElement : public virtual IUiNavigationListener
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiElement() { }


		// OPERATORS

		VIRTUAL CBOOL operator >(RCIUIELEMENT) const = 0;


		// ACCESSORS/MUTATORS

		VIRTUAL FLASH_STRING Label() const = 0;
		VIRTUAL PCCHAR LabelString() const = 0;

		VIRTUAL CBYTE Width() const = 0;
		VIRTUAL CBYTE Height() const = 0;


		// INTERFACE METHODS

		VIRTUAL VOID Render(RIUIRENDERER, CBYTE = 0, CBYTE = 0) = 0;


	protected:

		IUiElement() { }
	};

#pragma endregion


#pragma region [IUiContainerElement] DEFINITION

	template UI_CONTAINER_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiContainerElement : public IUiElement
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiContainerElement() { }


		// OPERATORS

		VIRTUAL CONST TChild * operator[](CBYTE) const = 0;
		VIRTUAL TChild * operator[](CBYTE) = 0;


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE ChildCount() const = 0;

		VIRTUAL CONST TChild & Child(CBYTE = 0) const = 0;
		VIRTUAL TChild & Child(CBYTE = 0) = 0;

		VIRTUAL TChild & AddChild(TChild &) = 0;

		VIRTUAL VOID RemoveChild(CBYTE) = 0;
		VIRTUAL VOID RemoveChild(TChild &) = 0;


		// INTERFACE METHODS

		VIRTUAL VOID DrawScreen(RIUIRENDERER) = 0;


	protected:

		IUiContainerElement() { }
	};

#pragma endregion


#pragma region [IUiListElement] DEFINITION

	template UI_CONTAINER_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiListElement : public IUiContainerElement<TChild>
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiListElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CONST TChild & GetSelectedItem() const = 0;
		VIRTUAL VOID SetSelectedItem(CONST TChild &) = 0;


	protected:

		IUiListElement() { }
	};

#pragma endregion


#pragma region [IUiMultiListElement] DEFINITION

	template UI_CONTAINER_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiMultiListElement : public IUiContainerElement<TChild>
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiMultiListElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE NumSelected() const = 0;

		VIRTUAL CONST TChild * GetSelectedItems() const = 0;
		VIRTUAL VOID SetSelectedItems(CONST TChild * &, CBYTE) = 0;


	protected:

		IUiMultiListElement() { }
	};

#pragma endregion


#pragma region [IUiChildElement] DEFINITION

	template UI_CHILD_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiChildElement : public virtual IUiElement
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiChildElement() { }


		// ACCESSORS

		//VIRTUAL TParent * Parent() const = 0;
		//VIRTUAL VOID SetParent(TParent *) = 0;


	protected:

		IUiChildElement() { }
	};

#pragma endregion


#pragma region [IUiChoice] DEFINITION

	template UI_CHILD_ELEMENT_T_CLAUSE_DEF
	INTERFACE IUiChoice : public IUiChildElement UI_CHILD_ELEMENT_T_ARGS
	{
	public:

		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL IsSelected() const = 0;
		VIRTUAL VOID SetSelected(CBOOL) = 0;


		// INTERFACE METHODS


	protected:

		IUiChoice() { }
	};

#pragma endregion


#pragma region [UiElementBase] DEFINITION

	CLASS UiElementBase : public virtual IUiElement
	{
	public:

		// CONSTRUCTOR

		UiElementBase(FLASH_STRING = NULL);


		// [IUiElement] IMPLEMENTATION

		VIRTUAL CBOOL operator >(RCIUIELEMENT) const;

		VIRTUAL FLASH_STRING Label() const;
		VIRTUAL PCCHAR LabelString() const;

		VIRTUAL CBYTE Width() const;
		VIRTUAL CBYTE Height() const;

		VIRTUAL VOID Render(RIUIRENDERER, CBYTE = 0, CBYTE = 0);


		// [IUiNavigationListener] IMPLEMENTATION

		VIRTUAL VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


	protected:

		FLASH_STRING _Label = NULL;
	};

#pragma endregion


#pragma region [UiContainerElementBase] IMPLEMENTATION

	template UI_CONTAINER_ELEMENT_T_CLAUSE_DEF
	CLASS UiContainerElementBase : public UiElementBase, public IUiContainerElement UI_CONTAINER_ELEMENT_T_ARGS
	{
	public:

		// CONSTRUCTOR/DESTRUCTOR

		UiContainerElementBase(FLASH_STRING label = NULL, CBYTE childCount = 0, TChild ** children = NULL)
			: UiElementBase(label), _ChildCount(childCount), _Children(children)
		{
			if (!_Children)
				_Dispose = TRUE;
		}

		VIRTUAL ~UiContainerElementBase()
		{
			this->Dispose();
		}


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose(CBOOL forceDispose = FALSE)
		{
			if (!_Children)
				return;

			if (_Dispose OR forceDispose)
			{
				for (BYTE i = 0; i < _ChildCount; i++)
				{
					if (_Children[i])
					{
						delete _Children[i];
						_Children[i] = NULL;
					}
				}
			}

			delete _Children;
			_Children = NULL;
		}


	public:

		// [IUiContainerElement] IMPLEMENTATION

		VIRTUAL CONST TChild * operator[](CBYTE i) const
		{
			if (!_Children)
				return NULL;

			return _Children[i];
		}

		VIRTUAL TChild * operator[](CBYTE i)
		{
			if (!_Children)
				return NULL;

			return _Children[i];
		}

		VIRTUAL CBYTE ChildCount() const
		{
			return _ChildCount;
		}

		VIRTUAL CONST TChild & Child(CBYTE i) const
		{
			return *this->operator[](i);
		}

		VIRTUAL TChild & Child(CBYTE i)
		{
			return *this->operator[](i);
		}

		VIRTUAL TChild & AddChild(TChild &)
		{
		}

		VIRTUAL VOID RemoveChild(CBYTE)
		{
		}

		VIRTUAL VOID RemoveChild(TChild &)
		{
		}

		VIRTUAL VOID DrawScreen(RIUIRENDERER)
		{
		}


		// [IUiElement] OVERRIDES

		CBYTE Width() const
		{
			return PtrGreatestOf<TChild>(MAKE_CONST(_Children), _ChildCount).Width();
		}

		CBYTE Height() const
		{
			return _ChildCount;
		}

		VOID Render(RIUIRENDERER renderer, CBYTE col = 0, CBYTE row = 0)
		{
			this->DrawScreen(renderer);
		}


		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE state = UiActionState::CLICK)
		{
		}

		VOID Down(CUIACTIONSTATE state = UiActionState::CLICK)
		{
		}

		VOID Left(CUIACTIONSTATE state = UiActionState::CLICK)
		{
		}

		VOID Right(CUIACTIONSTATE state = UiActionState::CLICK)
		{
		}

		VOID Return(CUIACTIONSTATE state = UiActionState::CLICK)
		{
		}

		VOID Select(CUIACTIONSTATE state = UiActionState::CLICK)
		{
		}


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		TChild ** _Children = NULL;
		BYTE _ChildCount = 0;
	};

#pragma endregion
};

#endif
