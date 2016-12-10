/***********************************************************************************************
* [IttyBitty_menu_items.h]: STRUCTURES FOR DEFINING MENU HIERARCHY AND BEHAVIOR
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_ITEMS_H
#define _ITTYBITTY_MENU_ITEMS_H


#include "IttyBitty_menu_nav.h"
#include "IttyBitty_menu_display.h"


#pragma region DEFINES

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IUiElement;
	TYPEDEF_CLASS_ALIASES(UiElement, UIELEMENT);

	class UiElementBase;
	TYPEDEF_CLASS_ALIASES(UiElement, UIELEMENT);


	class IMenuItem;
	TYPEDEF_CLASS_ALIASES(IMenuItem, IMENUITEM);

	class MenuItemBase;
	TYPEDEF_CLASS_ALIASES(MenuItemBase, MENUITEMBASE);

	class CustomMenuItem;
	TYPEDEF_CLASS_ALIASES(CustomMenuItem, CUSTOMMENUITEM);

	class FieldMenuItem;
	TYPEDEF_CLASS_ALIASES(FieldMenuItem, FIELDMENUITEM);

	class MenuField;
	TYPEDEF_CLASS_ALIASES(MenuField, MENUFIELD);


	class Menu;
	TYPEDEF_CLASS_ALIASES(Menu, MENU);

#pragma endregion


#pragma region ENUMS

	enum UiOrientation : BYTE
	{
		VERTICAL	= 0x0,
		HORIZONTAL	= 0x1
	};

	TYPEDEF_ENUM_ALIASES(UiOrientation, UIORIENTATION);


	ENUM UiDirection : BYTE
	{
		TOP_TO_BOTTOM	= VERTICAL | 0x0,
		BOTTOM_TO_TOP	= VERTICAL | 0x1,
		LEFT_TO_RIGHT	= HORIZONTAL | 0x0,
		RIGHT_TO_LEFT	= HORIZONTAL | 0x1
	};

	TYPEDEF_ENUM_ALIASES(UiDirection, UIDIRECTION);

	#define UI_DIRECTION_ORIENTATION_BIT	0x0
	#define UI_DIRECTION_BACKWARDS_BIT		0x1

	STATIC CBOOL UiDirectionIsHorizontal(CUIDIRECTION layoutDirection)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)layoutDirection, UI_DIRECTION_ORIENTATION_BIT));
	}

	STATIC CBOOL UiDirectionIsBackwards(CUIDIRECTION layoutDirection)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)layoutDirection, UI_DIRECTION_BACKWARDS_BIT));
	}


	enum UiLayoutCols : BYTE
	{
		COLS_1	= 0x2,
		COLS_2	= 0x4,
		COLS_3	= 0xC,
		COLS_4	= 0x10,
		COLS_5	= 0x14,
		COLS_6	= 0x18,
		COLS_7	= 0x1C,
		COLS_8	= 0x20
	};

	TYPEDEF_ENUM_ALIASES(UiLayoutCols, UILAYOUTCOLS);

	ENUM UiLayout : BYTE
	{
		VERTICAL_1_COL		= VERTICAL | COLS_1,
		HORIZONTAL_1_COL	= HORIZONTAL | COLS_1,
		VERTICAL_2_COL		= VERTICAL | COLS_2,
		HORIZONTAL_2_COL	= HORIZONTAL | COLS_2,
		VERTICAL_3_COL		= VERTICAL | COLS_3,
		HORIZONTAL_3_COL	= HORIZONTAL | COLS_3,
		VERTICAL_4_COL		= VERTICAL | COLS_4,
		HORIZONTAL_4_COL	= HORIZONTAL | COLS_4,
		VERTICAL_5_COL		= VERTICAL | COLS_5,
		HORIZONTAL_5_COL	= HORIZONTAL | COLS_5,
		VERTICAL_6_COL		= VERTICAL | COLS_6,
		HORIZONTAL_6_COL	= HORIZONTAL | COLS_6,
		VERTICAL_7_COL		= VERTICAL | COLS_7,
		HORIZONTAL_7_COL	= HORIZONTAL | COLS_7,
		VERTICAL_8_COL		= VERTICAL | COLS_8,
		HORIZONTAL_8_COL	= HORIZONTAL | COLS_8,
	};

	TYPEDEF_ENUM_ALIASES(UiLayout, UILAYOUT);

	#define UI_LAYOUT_COLS_OFFSET		0x2

	STATIC CBOOL UiLayoutIsHorizontal(CUILAYOUT layout)
	{
		return static_cast<CBOOL>(CHECK_BIT((CBYTE)layout, UI_DIRECTION_ORIENTATION_BIT));
	}

	STATIC CBYTE UiLayoutToNumCols(CUILAYOUT layout)
	{
		return (CBYTE)layout SHR UI_LAYOUT_COLS_OFFSET;
	}


	enum UiSelectionStatusFlags : BYTE
	{
		UI_STATUS_NONE			= 0x0,
		UI_STATUS_SCROLLBAR		= 0x1,
		UI_STATUS_INDEX			= 0x2,
		UI_STATUS_TOTAL			= 0x4
	};

	TYPEDEF_ENUM_ALIASES(UiSelectionStatusFlags, UISELECTIONSTATUSFLAGS);

#pragma endregion


#pragma region [IUiElement] DEFINITION

	INTERFACE IUiElement
	{
	public:

		VIRTUAL CBOOL Check() const = 0;


	protected:

		IUiElement() { }
	};

#pragma endregion


#pragma region [UiElementBase] DEFINITION

	CLASS UiElementBase : public IUiElement
	{
	};

#pragma endregion


#pragma region [IMenuItem] DEFINITION

	INTERFACE IMenuItem
	{
	public:

		VIRTUAL CBOOL Check() const = 0;


	protected:

		IMenuItem() { }
	};

#pragma endregion


#pragma region [MenuItemBase] DEFINITION

	CLASS MenuItemBase : public IMenuItem
	{
	};

#pragma endregion


#pragma region [CustomMenuItem] DEFINITION

	CLASS CustomMenuItem : public MenuItemBase
	{
	};

#pragma endregion


#pragma region [FieldMenuItem] DEFINITION

	CLASS FieldMenuItem : public MenuItemBase
	{
	};

#pragma endregion


#pragma region [MenuField] DEFINITION

	CLASS MenuField : public FieldMenuItem
	{
	};

#pragma endregion


#pragma region [Menu] DEFINITION

	CLASS Menu : public UiElementBase, IMenuItem
	{
		// CONSTRUCTORS/DESTRUCTOR

		Menu(CBYTE cols, CBYTE rows, PPCIMENUITEM menuHierarchy = NULL);
		Menu(CBYTE cols, CBYTE rows, CBYTE initMenuCapacity = 0);
	};

#pragma endregion
};

#endif
