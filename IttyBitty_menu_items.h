/***********************************************************************************************
* [IttyBitty_menu_items.h]: STRUCTURES FOR DEFINING MENU HIERARCHY AND BEHAVIOR
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_ITEMS_H
#define _ITTYBITTY_MENU_ITEMS_H


#include "IttyBitty_menu_fields.h"


#pragma region DEFINES

#define MENUI_DEFAULT_MENU_CAPACITY				5

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IMenuItem;
	TYPEDEF_CLASS_ALIASES(IMenuItem, IMENUITEM);

	class MenuItemBase;
	TYPEDEF_CLASS_ALIASES(MenuItemBase, MENUITEMBASE);

	class CustomMenuItem;
	TYPEDEF_CLASS_ALIASES(CustomMenuItem, CUSTOMMENUITEM);

	class FieldMenuItem;
	TYPEDEF_CLASS_ALIASES(FieldMenuItem, FIELDMENUITEM);

	class MenuField;
	TYPEDEF_CLASS_ALIASES(MenuField, MENUFIELD);

	class MenuChoice;
	TYPEDEF_CLASS_ALIASES(MenuChoice, MENUCHOICE);


	class Menu;
	TYPEDEF_CLASS_ALIASES(Menu, MENU);

	class ListMenu;
	TYPEDEF_CLASS_ALIASES(ListMenu, LISTMENU);

#pragma endregion


#pragma region [IMenuItem] DEFINITION

	INTERFACE IMenuItem : public IUiElement	// TODO: Remove IUiElement parent?
	{
	public:

		// INTERFACE METHODS

		VIRTUAL BOOL Action(PTR = NULL, CPTR = NULL) = 0;


	protected:

		IMenuItem() { }
	};

#pragma endregion


#pragma region [MenuItemBase] DEFINITION

	CLASS MenuItemBase : public UiElementBase, public IMenuItem
	{
	public:

		// [IMenuItem] IMPLEMENTATION


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [CustomMenuItem] DEFINITION

	CLASS CustomMenuItem : public MenuItemBase
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		VIRTUAL BOOL Action(PTR = NULL, CPTR = NULL);


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [FieldMenuItem] DEFINITION

	CLASS FieldMenuItem : public MenuItemBase, public IUiField
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		VIRTUAL BOOL Action(PTR = NULL, CPTR = NULL);


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [MenuField] DEFINITION

	CLASS MenuField : public FieldMenuItem
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		BOOL Action(PTR = NULL, CPTR = NULL);
	};

#pragma endregion


#pragma region [MenuChoice] DEFINITION

	CLASS MenuChoice : public UiFieldChoice, public IMenuItem //public MenuItemBase, public IUiChoice
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		VIRTUAL BOOL Action(PTR = NULL, CPTR = NULL);
	};

#pragma endregion


#pragma region [Menu] DEFINITION

	CLASS Menu : public MenuItemBase, public IUiListElement<IMenuItem>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		Menu(PPCIMENUITEM menuHierarchy = NULL, BYTE numChildren = 0);
		Menu(CBYTE initMenuCapacity = MENUI_DEFAULT_MENU_CAPACITY);


	protected:

		// INSTANCE VARIABLES

		BYTE _Capacity = 0;
		BYTE _NumChildren = 0;
		PPIMENUITEM _Children = NULL;
	};

#pragma endregion


#pragma region [ListMenu] DEFINITION

	CLASS ListMenu : public Menu, public IUiListElement<MenuChoice>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ListMenu(PPCIMENUITEM menuHierarchy = NULL);
		ListMenu(CBYTE initMenuCapacity = 0);


	protected:

		// INSTANCE VARIABLES

		BOOL _AllowMultipleSelections = FALSE;
	};

#pragma endregion
};

#endif
