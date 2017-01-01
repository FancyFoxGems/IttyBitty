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


	#define MENU_BASE_T_CLAUSE_DEF		<typename TMenuItem>
	#define MENU_BASE_T_CLAUSE			<typename TMenuItem>
	#define MENU_BASE_T_ARGS			<TMenuItem>

	template MENU_BASE_T_CLAUSE
	class MenuBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(MENU_BASE_T_CLAUSE), CSL(MENU_BASE_T_ARGS), MenuBase, MENUBASE);

	class Menu;
	TYPEDEF_CLASS_ALIASES(Menu, MENU);

	class ListMenuChoice;
	TYPEDEF_CLASS_ALIASES(ListMenuChoice, LISTMENUCHOICE);

	class ListMenu;
	TYPEDEF_CLASS_ALIASES(ListMenu, LISTMENU);


	interface IUiDialog;
	TYPEDEF_CLASS_ALIASES(IUiDialog, IUIDIALOG);

	class UiDialog;
	TYPEDEF_CLASS_ALIASES(UiDialog, UIDIALOG);

#pragma endregion


#pragma region [IMenuItem] DEFINITION

	INTERFACE IMenuItem : public IUiElement
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

		PCCHAR _Label = NULL;
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

	template DEFAULT_T_CLAUSE
	CLASS FieldMenuItem : public UiFieldBase<T>, public IMenuItem //public MenuItemBase, public IUiField<T>
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		VIRTUAL BOOL Action(PTR = NULL, CPTR = NULL);


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

		// [IMenuItem] IMPLEMENTATION

		BOOL Action(PTR = NULL, CPTR = NULL);
	};

#pragma endregion


#pragma region [MenuBase] DEFINITION

	template MENU_BASE_T_CLAUSE_DEF
	CLASS MenuBase : public MenuItemBase, public IUiContainerElement<TMenuItem>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MenuBase(CBYTE, PPIMENUITEM);
		MenuBase(CBYTE, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~MenuBase();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IUiContainerElement] IMPLEMENTATION

		VIRTUAL CONST TMenuItem * operator[](CBYTE) const;
		VIRTUAL TMenuItem * operator[](CBYTE);

		VIRTUAL CBYTE ChildCount() const;

		VIRTUAL CONST TMenuItem & Child(CBYTE = 0) const;
		VIRTUAL TMenuItem & Child(CBYTE = 0);

		VIRTUAL TMenuItem & AddChild(TMenuItem &);

		VIRTUAL VOID RemoveChild(CBYTE);
		VIRTUAL VOID RemoveChild(TMenuItem &);


		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Down(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Left(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Right(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Return(CUIACTIONSTATE = UiActionState::CLICK);
		VOID Select(CUIACTIONSTATE = UiActionState::CLICK);


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		PPIMENUITEM _Children = NULL;
		BYTE _ChildCount = 0;
		BYTE _Capacity = 0;
	};

#pragma endregion


#pragma region [Menu] DEFINITION

	CLASS Menu : public MenuBase<IMenuItem>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		Menu(CBYTE, PPIMENUITEM);
		Menu(CBYTE, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~Menu();


	protected:

		// INSTANCE VARIABLES
	};

#pragma endregion


#pragma region [ListMenuChoice] DEFINITION

	CLASS ListMenuChoice : public MenuItemBase, public IUiChoice
	{
	public:

		// [IMenuItem] IMPLEMENTATION

		VIRTUAL BOOL Action(PTR = NULL, CPTR = NULL);
	};

#pragma endregion


#pragma region [ListMenu] DEFINITION

	CLASS ListMenu : public MenuBase<ListMenuChoice>, public IUiListElement<ListMenuChoice>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ListMenu(CBYTE, PPLISTMENUCHOICE, CBOOL = FALSE);
		ListMenu(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_MENU_CAPACITY);

		VIRTUAL ~ListMenu();


		// [IUiListElement] IMPLEMENTATION

		VIRTUAL CBOOL MultipleSelectionsAllowed() const;
		VIRTUAL VOID SetAllowMultipleSelections(CBOOL = TRUE);


	protected:

		// INSTANCE VARIABLES

		BOOL _AllowMultipleSelections = FALSE;
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
