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

	interface IUiScreenElement;
	TYPEDEF_CLASS_ALIASES(IUiScreenElement, IUISCREENELEMENT);

	interface IUiChildElement;
	TYPEDEF_CLASS_ALIASES(IUiChildElement, IUICHILDELEMENT);

	interface IUiChoice;
	TYPEDEF_CLASS_ALIASES(IUiChoice, IUICHOICE);


	#define UI_CONTAINER_ELEMENT_BASE_T_CLAUSE_DEF	<class TItem = IUiChildElement>
	#define UI_CONTAINER_ELEMENT_BASE_T_CLAUSE		<class TItem>
	#define UI_CONTAINER_ELEMENT_BASE_T_ARGS		<TItem>

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE
	interface IUiContainerElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_BASE_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_BASE_T_ARGS), IUiContainerElement, IUICONTAINERELEMENT);

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE
	interface IUiListElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_BASE_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_BASE_T_ARGS), IUiListElement, IUILISTELEMENT);

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE
	interface IUiMultiListElement;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_BASE_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_BASE_T_ARGS), IUiMultiListElement, IUIMULTILISTELEMENT);


	class UiElementBase;
	TYPEDEF_CLASS_ALIASES(UiElementBase, UIELEMENTBASE);

	class UiScreenElementBase;
	TYPEDEF_CLASS_ALIASES(UiScreenElementBase, UISCREENELEMENTBASE);

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE
	interface UiContainerElementBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_CONTAINER_ELEMENT_BASE_T_CLAUSE), \
		CSL(UI_CONTAINER_ELEMENT_BASE_T_ARGS), UiContainerElementBase, UICONTAINERELEMENTBASE);

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


		// INTERFACE METHODS

		VIRTUAL CBYTE Width() const = 0;
		VIRTUAL CBYTE Height() const = 0;

		VIRTUAL VOID Render(RIUIRENDERER, CBYTE = 0, CBYTE = 0) = 0;


	protected:

		IUiElement() { }
	};

#pragma endregion


#pragma region [IUiScreenElement] DEFINITION

	INTERFACE IUiScreenElement : public IUiElement
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiScreenElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL IsActive() const = 0;
		VIRTUAL VOID SetActive(BOOL = TRUE) = 0;


		// INTERFACE METHODS

		VIRTUAL VOID DrawScreen(RIUIRENDERER) = 0;


	protected:

		IUiScreenElement() { }
	};

#pragma endregion


#pragma region [IUiChildElement] DEFINITION

	INTERFACE IUiChildElement : public IUiElement
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiChildElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL PIUICONTAINERELEMENT<IUICHILDELEMENT> GetParent() const = 0;
		VIRTUAL VOID SetParent(PIUICONTAINERELEMENT<IUICHILDELEMENT>) = 0;

		VIRTUAL CCHAR GetInputTag() const = 0;
		VIRTUAL VOID SetInputTag(CCHAR) = 0;


	protected:

		IUiChildElement() { }
	};

#pragma endregion


#pragma region [IUiChoice] DEFINITION

	INTERFACE IUiChoice : public IUiChildElement
	{
	public:

		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL IsSelected() const = 0;
		VIRTUAL VOID SetSelected(CBOOL) = 0;


	protected:

		IUiChoice() { }
	};

#pragma endregion


#pragma region [IUiContainerElement] DEFINITION

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE_DEF
	INTERFACE IUiContainerElement : public IUiScreenElement
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiContainerElement() { }


		// OPERATORS

		VIRTUAL CONST TItem * operator[](CBYTE) const = 0;
		VIRTUAL TItem * operator[](CBYTE) = 0;


		// ACCESSORS/MUTATORS

		VIRTUAL CUISTATUSFLAGS StatusFlags() const = 0;

		VIRTUAL VOID SetLayout(UILAYOUT) = 0;
		VIRTUAL CUILAYOUT GetLayout() const = 0;

		VIRTUAL VOID SetItems(CBYTE, TItem *) = 0;

		VIRTUAL CBYTE ItemCount() const = 0;

		VIRTUAL CONST TItem & Item(CBYTE = 0) const = 0;
		VIRTUAL TItem & Item(CBYTE = 0) = 0;

		VIRTUAL VOID ClearItems() = 0;

		VIRTUAL CBOOL AddItem(TItem &) = 0;

		VIRTUAL VOID RemoveItem(TItem &) = 0;
		VIRTUAL VOID RemoveItem(CBYTE) = 0;

		VIRTUAL CBYTE GetCurrentIndex() const = 0;
		VIRTUAL VOID SetCurrentIndex(CBYTE) = 0;


	protected:

		IUiContainerElement() { }
	};

#pragma endregion


#pragma region [IUiListElement] DEFINITION

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE_DEF
	INTERFACE IUiListElement : public IUiContainerElement<TItem>
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiListElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE GetSelectedNumber() const = 0;
		VIRTUAL VOID SetSelectedNumber(CBYTE) = 0;

		VIRTUAL TItem & GetSelectedItem() const = 0;
		VIRTUAL VOID SetSelectedItem(CONST TItem &) = 0;


	protected:

		IUiListElement() { }
	};

#pragma endregion


#pragma region [IUiMultiListElement] DEFINITION

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE_DEF
	INTERFACE IUiMultiListElement : public IUiContainerElement<TItem>
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IUiMultiListElement() { }


		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE NumSelected() const = 0;

		VIRTUAL PCBYTE GetSelectedNumbers() const = 0;
		VIRTUAL VOID SetSelectedNumbers(CBYTE, PCBYTE) = 0;

		VIRTUAL TItem * GetSelectedItems() const = 0;
		VIRTUAL VOID SetSelectedItems(CBYTE, CONST TItem *) = 0;


	protected:

		IUiMultiListElement() { }
	};

#pragma endregion


#pragma region [UiElementBase] DEFINITION

	CLASS UiElementBase : public IUiElement
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

		VIRTUAL VOID Up(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Down(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Left(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Right(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Return(CUIACTIONSTATE = CLICK);
		VIRTUAL VOID Select(CUIACTIONSTATE = CLICK);

		VIRTUAL VOID Value(RIUIINPUTVALUERESOLVER, CBYTE);


	protected:

		FLASH_STRING _Label = NULL;
	};

#pragma endregion


#pragma region [UiScreenElementBase] DEFINITION

	CLASS UiScreenElementBase : public UiElementBase
	{
	public:

		// CONSTRUCTOR

		UiScreenElementBase(FLASH_STRING = NULL);


		// [IUiScreenElement] IMPLEMENTATION

		VIRTUAL CBOOL IsActive() const;
		VIRTUAL VOID SetActive(BOOL = TRUE);


	protected:

		BOOL _Active = FALSE;
	};

#pragma endregion


#pragma region [UiContainerElementBase] IMPLEMENTATION

	template UI_CONTAINER_ELEMENT_BASE_T_CLAUSE_DEF
	CLASS UiContainerElementBase : public UiScreenElementBase, public IUiContainerElement UI_CONTAINER_ELEMENT_BASE_T_ARGS
	{
	protected:		

		// META-TYPEDEF ALIAS

		typedef TItem TITEM, * PTITEM, ** PPTITEM;


	public:

		// CONSTRUCTOR/DESTRUCTOR

		UiContainerElementBase(UILAYOUT layout, FLASH_STRING label = NULL, CBYTE itemCount = 0, TItem ** items = NULL)
			: UiScreenElementBase(label), _Layout(layout), _ItemCount(itemCount), _Items(items)
		{
			if (_Items)
				_DisposeItems = TRUE;
		}

		UiContainerElementBase(FLASH_STRING label = NULL, CBYTE itemCount = 0, TItem ** items = NULL)
			: UiContainerElementBase(UiLayout::TOP_TO_BOTTOM_JUSTIFIED_1_COL)
		{
			if (_Items)
				_DisposeItems = TRUE;
		}

		VIRTUAL ~UiContainerElementBase()
		{
			this->Dispose();
		}


	protected:

		// PROTECTED DISPOSAL METHOD

		VOID Dispose(CBOOL forceDispose = FALSE)
		{
			if (!_Items)
				return;

			if (_DisposeItems OR forceDispose)
			{
				for (BYTE i = 0; i < _ItemCount; i++)
				{
					if (_Items[i])
					{
						delete _Items[i];
						_Items[i] = NULL;
					}
				}

				_DisposeItems = FALSE;
			}

			delete _Items;
			_Items = NULL;
		}


	public:

		// [IUiContainerElement] IMPLEMENTATION

		VIRTUAL CUISTATUSFLAGS StatusFlags() const
		{
			return MUI::Options.ListStatus;
		}

		VIRTUAL VOID SetLayout(UILAYOUT layout)
		{
			_Layout = layout;
		}

		VIRTUAL CUILAYOUT GetLayout() const
		{
			return _Layout;
		}

		VIRTUAL CONST TItem * operator[](CBYTE i) const
		{
			if (!_Items)
				return NULL;

			return _Items[i];
		}

		VIRTUAL TItem * operator[](CBYTE i)
		{
			if (!_Items)
				return NULL;

			return _Items[i];
		}

		VIRTUAL VOID SetItems(CBYTE itemCount, TItem * items)
		{
			this->Dispose();

			_ItemCount = itemCount;
			_Items = &items;
		}

		VIRTUAL CBYTE ChildCount() const
		{
			return _ItemCount;
		}

		VIRTUAL CONST TItem & Child(CBYTE i) const
		{
			return *this->operator[](i);
		}

		VIRTUAL TItem & Child(CBYTE i)
		{
			return *this->operator[](i);
		}

		VIRTUAL VOID ClearItems()
		{
			this->Dispose();

			_ItemCount = 0;
		}

		VIRTUAL CBOOL AddChild(TItem & item)
		{
			if (_DisposeItems)
				return FALSE;

			TItem ** newItems = new PTITEM[++_ItemCount];

			for (BYTE i = 0; i < _ItemCount - 1; i++)
				newItems[i] = _Items[i];

			newItems[_ItemCount - 1] = &item;

			this->Dispose();

			_Items = newItems;

			return TRUE;
		}

		VIRTUAL VOID RemoveChild(CBYTE itemIndex)
		{
			if (itemIndex >= _ItemCount)
				return;

			PPTITEM newItems = new PTITEM[--_ItemCount];
			BYTE currIdx = 0;

			for (BYTE i = 0; i < _ItemCount; i++)
			{
				if (currIdx != itemIndex)
					newItems[currIdx++] = _Items[i];
			}

			if (_DisposeItems)
			{
				delete _Items[itemIndex];
				_Items[itemIndex] = NULL;
			}

			delete[] _Items;

			_Items = newItems;
		}

		VIRTUAL VOID RemoveChild(TItem & item)
		{
			if (!_Items)
				return;

			for (BYTE i = 0; i < _ItemCount; i++)
			{
				if (_Items[i] != &item)
				{
					this->RemoveChild(i);
					break;
				}
			}
		}

		VIRTUAL CBYTE GetCurrentIndex() const
		{
			return _CurrentIdx;
		}

		VIRTUAL VOID SetCurrentIndex(CBYTE currentIdx)
		{
			if (currentIdx >= _ItemCount)
				_CurrentIdx = _ItemCount - 1;
			else
				_CurrentIdx = currentIdx;
		}


		// [IUiScreenElement] IMPLEMENTATION

		VIRTUAL VOID DrawScreen(RIUIRENDERER)
		{

		}


		// [IUiElement] OVERRIDES

		VIRTUAL CBYTE Width() const
		{
			return PtrGreatestOf<TItem>(MAKE_CONST(_Items), _ItemCount).Width();
		}

		VIRTUAL CBYTE Height() const
		{
			if (UiStatusFlagsShowStatusRow(this->StatusFlags()))
				return _ItemCount + 1;

			return _ItemCount;
		}

		VIRTUAL VOID Render(RIUIRENDERER renderer, CBYTE col = 0, CBYTE row = 0)
		{
			this->DrawScreen(renderer);
		}


		// [IUiNavigationListener] OVERRIDES

		VIRTUAL VOID Up(CUIACTIONSTATE state = CLICK)
		{
		}

		VIRTUAL VOID Down(CUIACTIONSTATE state = CLICK)
		{
		}

		VIRTUAL VOID Left(CUIACTIONSTATE state = CLICK)
		{
		}

		VIRTUAL VOID Right(CUIACTIONSTATE state = CLICK)
		{
		}

		VIRTUAL VOID Return(CUIACTIONSTATE state = CLICK)
		{
		}

		VIRTUAL VOID Select(CUIACTIONSTATE state = CLICK)
		{
		}


	protected:

		// INSTANCE VARIABLES

		BOOL _DisposeItems = FALSE;

		UILAYOUT _Layout = UiLayout::TOP_TO_BOTTOM_JUSTIFIED_1_COL;

		TItem ** _Items = NULL;
		BYTE _ItemCount = 0;

		BYTE _CurrentIdx = 0;
	};

#pragma endregion
};

#endif
