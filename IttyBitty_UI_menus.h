/***********************************************************************************************
* [IttyBitty_UI_menus.h]: STRUCTURES FOR DEFINING MENU HIERARCHY AND BEHAVIOR
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_MENUS_H
#define _ITTYBITTY_UI_MENUS_H


#include "IttyBitty_UI_fields.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IMenuItem;
	TYPEDEF_CLASS_ALIASES(IMenuItem, IMENUITEM);

	class MenuItemBase;
	TYPEDEF_CLASS_ALIASES(MenuItemBase, MENUITEMBASE);

	class CustomMenuItem;
	TYPEDEF_CLASS_ALIASES(CustomMenuItem, CUSTOMMENUITEM);

	template DEFAULT_T_CLAUSE
	class FieldMenuItem;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), CSL(DEFAULT_T_ARGS), FieldMenuItem, FIELDMENUITEM);

	template DEFAULT_T_CLAUSE
	class MenuField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), CSL(DEFAULT_T_ARGS), MenuField, MENUFIELD);


	#define MENU_BASE_T_CLAUSE_DEF		<typename TMenuItem = IMenuItem>
	#define MENU_BASE_T_CLAUSE			<typename TMenuItem>
	#define MENU_BASE_T_ARGS			<TMenuItem>

	template MENU_BASE_T_CLAUSE
	class MenuBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(MENU_BASE_T_CLAUSE), CSL(MENU_BASE_T_ARGS), MenuBase, MENUBASE);

	class Menu;
	TYPEDEF_CLASS_ALIASES(Menu, MENU);


	class ListMenuBase;
	TYPEDEF_CLASS_ALIASES(ListMenuBase, LISTMENUBASE);

	class ListMenu;
	TYPEDEF_CLASS_ALIASES(ListMenu, LISTMENU);

	class MultiListMenu;
	TYPEDEF_CLASS_ALIASES(MultiListMenu, MULTILISTMENU);

	class ListMenuChoice;
	TYPEDEF_CLASS_ALIASES(ListMenuChoice, LISTMENUCHOICE);


	interface IUiDialog;
	TYPEDEF_CLASS_ALIASES(IUiDialog, IUIDIALOG);

	class UiDialog;
	TYPEDEF_CLASS_ALIASES(UiDialog, UIDIALOG);

#pragma endregion


#pragma region [IMenuItem] DEFINITION

	INTERFACE IMenuItem : public IUiChildElement<Menu>
	{
	public:

		// INTERFACE METHODS

		//VIRTUAL CBOOL Action(PTR = NULL, CPTR = NULL) = 0;


	protected:

		IMenuItem() { }
	};

#pragma endregion


#pragma region [MenuItemBase] DEFINITION

	CLASS MenuItemBase : public UiElementBase, public IMenuItem
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MenuItemBase(FLASH_STRING label, PMENU parent) : UiElementBase(label) { }


		// [IUiChildElement] IMPLEMENTATION

		//VIRTUAL PMENU Parent() const;
		//VIRTUAL VOID SetParent(PMENU);


		// [IMenuItem] IMPLEMENTATION

		//VIRTUAL CBOOL Action(PTR = NULL, CPTR = NULL);


	protected:

		// INSTANCE VARIABLES

		PMENU _Parent = NULL;
	};

#pragma endregion


#pragma region [CustomMenuItem] DEFINITION

	CLASS CustomMenuItem : public MenuItemBase
	{
	public:

		// [IMenuItem] OVERRIDE

		CBOOL Action(PTR = NULL, CPTR = NULL);


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [FieldMenuItem] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS FieldMenuItem : public UiFieldBase<T>, public IMenuItem //public MenuItemBase, public IUiField<T>
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		VIRTUAL CBOOL Action(PTR = NULL, CPTR = NULL);


	protected:

		// INSTANCE VARIABLES

		PIUIFIELD<T> _Field = NULL;
	};

#pragma endregion


#pragma region [MenuField] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS MenuField : public FieldMenuItem<T>
	{
	public:

		// [IMenuItem] OVERRIDE

		CBOOL Action(PTR = NULL, CPTR = NULL);
	};

#pragma endregion


#pragma region [MenuBase] DEFINITION

	template MENU_BASE_T_CLAUSE_DEF
	CLASS MenuBase : public MenuItemBase, public UiContainerElementBase<TMenuItem>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MenuBase(FLASH_STRING label, PMENU parent, CBYTE childCount = 0, PPIMENUITEM children = NULL)
			: MenuItemBase(label, parent), UiContainerElementBase<TMenuItem>(label, childCount, children) { }


	public:

		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE = UiActionState::CLICK)
		{
		}

		VOID Down(CUIACTIONSTATE = UiActionState::CLICK)
		{
		}

		VOID Left(CUIACTIONSTATE = UiActionState::CLICK)
		{
		}

		VOID Right(CUIACTIONSTATE = UiActionState::CLICK)
		{
		}

		VOID Return(CUIACTIONSTATE = UiActionState::CLICK)
		{
		}

		VOID Select(CUIACTIONSTATE = UiActionState::CLICK)
		{
		}


		// [IUiElement] IMPLEMENTATION

		VIRTUAL CBOOL operator >(RCIUIELEMENT other) const
		{
			//return UiContainerElementBase<TMenuItem>::operator >(other);

		}

		VIRTUAL FLASH_STRING Label() const
		{
			//return UiContainerElementBase<TMenuItem>::Label();

		}

		VIRTUAL PCCHAR LabelString() const
		{
			//return UiContainerElementBase<TMenuItem>::LabelString();
		}

		VIRTUAL CBYTE Width() const
		{
			//return UiContainerElementBase<TMenuItem>::Width();

		}
		VIRTUAL CBYTE Height() const
		{
			//return UiContainerElementBase<TMenuItem>::Height();
		}

		VIRTUAL VOID Render(RIUIRENDERER renderer, CBYTE col = 0, CBYTE row = 0)
		{
			//UiContainerElementBase<TMenuItem>::Render(renderer, col, row);
		}
	};

#pragma endregion


#pragma region [Menu] DEFINITION

	CLASS Menu : public MenuBase<IMenuItem>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		Menu(FLASH_STRING label, PMENU parent, CBYTE childCount = 0, PPIMENUITEM children = NULL)
			: MenuBase(label, parent, childCount, children) { }


	protected:

		// INSTANCE VARIABLES
	};

#pragma endregion


#pragma region [ListMenuBase] DEFINITION

	CLASS ListMenuBase : public MenuBase<ListMenuChoice>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ListMenuBase(CBYTE, PPLISTMENUCHOICE, CBOOL = FALSE);
		ListMenuBase(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~ListMenuBase();
	};

#pragma endregion


#pragma region [ListMenu] DEFINITION

	CLASS ListMenu : public ListMenuBase, public IUiListElement<ListMenuChoice>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ListMenu(CBYTE, PPLISTMENUCHOICE, CBOOL = FALSE);
		ListMenu(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~ListMenu();


		// [IUiListElement] IMPLEMENTATION

		VIRTUAL RCLISTMENUCHOICE GetSelectedItem() const;
		VIRTUAL VOID SetSelectedItem(RCLISTMENUCHOICE);
	};

#pragma endregion


#pragma region [MultiListMenu] DEFINITION

	CLASS MultiListMenu : public ListMenuBase, public IUiMultiListElement<ListMenuChoice>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MultiListMenu(CBYTE, PPLISTMENUCHOICE, CBOOL = FALSE);
		MultiListMenu(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~MultiListMenu();


		// [IUiMultiListElement] IMPLEMENTATION

		VIRTUAL CBYTE NumSelected() const;

		VIRTUAL PCLISTMENUCHOICE GetSelectedItems() const;
		VIRTUAL VOID SetSelectedItems(PCLISTMENUCHOICE &, CBYTE);
	};

#pragma endregion

#pragma region [ListMenuChoice] DEFINITION

	CLASS ListMenuChoice : public MenuItemBase, public IUiChoice<ListMenu>
	{
	public:

		// [IUiChoice] IMPLEMENTATION

		VIRTUAL CBOOL IsSelected() const;
		VIRTUAL VOID SetSelected(CBOOL);


		// [IMenuItem] OVERRIDE

		CBOOL Action(PTR = NULL, CPTR = NULL);


	protected:

		// INSTANCE VARIABLES

		BOOL _Selected = FALSE;
	};

#pragma endregion


#pragma region [IUiDialog] DEFINITION

	INTERFACE IUiDialog : public IUiElement
	{
	public:


		// ACCESSORS/MUTATORS

		VIRTUAL CBOOL ShowMessage() const = 0;


		// INTERFACE METHODS

		VIRTUAL VOID Prompt(RIUIRENDERER) = 0;


	protected:

		IUiDialog() { }
	};

#pragma endregion


#pragma region [UiDialog] DEFINITION

	CLASS UiDialog : public UiElementBase, public IUiDialog
	{
	public:

		// [IUiDialog] IMPLEMENTATION

		VIRTUAL CBOOL ShowMessage() const;


		// INTERFACE METHODS

		VIRTUAL VOID Prompt(RIUIRENDERER);


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion
};

#endif
