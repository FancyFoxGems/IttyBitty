/***********************************************************************************************
* [IttyBitty_menu_fields.h]: SPECIALIZED MENU ITEM TYPES TO ALLOW FOR DATA ENTRY AND DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_FIELDS_H
#define _ITTYBITTY_MENU_FIELDS_H


#include "IttyBitty_fields.h"
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

	class IUiListElement;
	TYPEDEF_CLASS_ALIASES(IUiListElement, IUILISTELEMENT);


	class IUiField;
	TYPEDEF_CLASS_ALIASES(IUiField, IUIFIELD);

	class UiFieldBase;
	TYPEDEF_CLASS_ALIASES(UiFieldBase, UIFIELDBASE);

	class BooleanUiField;
	TYPEDEF_CLASS_ALIASES(BooleanUiField, BOOLEANUIFIELD);

	class AlphaUiFieldBase;
	TYPEDEF_CLASS_ALIASES(AlphaUiFieldBase, ALPHAUIFIELDBASE);

	class CharUiField;
	TYPEDEF_CLASS_ALIASES(CharUiField, CHARUIFIELD);

	class StringUiField;
	TYPEDEF_CLASS_ALIASES(StringUiField, STRINGUIFIELD);

	class MaskedStringUiField;
	TYPEDEF_CLASS_ALIASES(MaskedStringUiField, MASKEDSTRINGUIFIELD);

	class DateUiField;
	TYPEDEF_CLASS_ALIASES(DateUiField, DATEUIFIELD);

	class TimeUiField;
	TYPEDEF_CLASS_ALIASES(TimeUiField, TIMEUIFIELD);

	#define NUMERIC_UI_FIELD_T_CLAUSE_DEF	<typename T>
	#define NUMERIC_UI_FIELD_T_CLAUSE		<typename T>
	#define NUMERIC_UI_FIELD_T_ARGS			<T>

	template NUMERIC_UI_FIELD_T_CLAUSE
	class NumericUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(NUMERIC_UI_FIELD_T_CLAUSE), \
		CSL(NUMERIC_UI_FIELD_T_ARGS), NumericUiField, NUMERICUIFIELD);

	class FloatUiField;
	TYPEDEF_CLASS_ALIASES(UiField, UIFIELD);

	class ListUiField;
	TYPEDEF_CLASS_ALIASES(ListUiField, LISTUIFIELD);

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
		COLS_AUTO	= 0x0,
		COLS_1		= 0x2,
		COLS_2		= 0x4,
		COLS_3		= 0xC,
		COLS_4		= 0x10,
		COLS_5		= 0x14,
		COLS_6		= 0x18,
		COLS_7		= 0x1C,
		COLS_8		= 0x20
	};

	TYPEDEF_ENUM_ALIASES(UiLayoutCols, UILAYOUTCOLS);

	ENUM UiLayout : BYTE
	{
		VERTICAL_AUTO		= VERTICAL | COLS_AUTO,
		HORIZONTAL_AUTO		= HORIZONTAL | COLS_AUTO,
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


	enum UiStatusIndicatorFlags : BYTE
	{
		UI_STATUS_NONE				= 0x0,
		UI_STATUS_SCROLLBAR			= 0x1,
		UI_STATUS_ITEM_INDEX		= 0x2,
		UI_STATUS_PAGE_INDEX		= 0x4,
		UI_STATUS_SHOW_TOTAL		= 0x8
	};

	TYPEDEF_ENUM_ALIASES(UiStatusIndicatorFlags, UISELECTIONSTATUSFLAGS);


	enum AllowedCharFlags : BYTE
	{
		ALLOWED_CHARS_ALL		= 0x0,
		ALLOWED_CHARS_NUMERIC	= 0x1,
		ALLOWED_CHARS_UPPER		= 0x2,
		ALLOWED_CHARS_LOWER		= 0x4
	};

	TYPEDEF_ENUM_ALIASES(UiStatusIndicatorFlags, UISELECTIONSTATUSFLAGS);

#pragma endregion


#pragma region [IUiElement] DEFINITION

	INTERFACE IUiElement : public IUiActions
	{
	public:

		// ACCESSORS/MUTATORS

		VIRTUAL CBYTE Height() const = 0;
		VIRTUAL CBYTE Width() const = 0;
		VIRTUAL CBYTE Top() const = 0;
		VIRTUAL CBYTE Left() const = 0;



		// INTERFACE METHODS

		VIRTUAL VOID Render(RCIUIRENDERER renderer) = 0;


	protected:

		IUiElement() { }
	};

#pragma endregion


#pragma region [UiElementBase] DEFINITION

	CLASS UiElementBase : public IUiElement
	{
	public:

		// [IUiActions] Implementation

		VIRTUAL VOID Up();
		VIRTUAL VOID Down();
		VIRTUAL VOID Left();
		VIRTUAL VOID Right();
		VIRTUAL VOID Escape();
		VIRTUAL VOID Select();
		VIRTUAL VOID IsShiftOn();
		VIRTUAL VOID IsAltOn();


		// [IUiElement] Implementation

		VIRTUAL CBYTE Height() const;
		VIRTUAL CBYTE Width() const;
		VIRTUAL CBYTE Top() const;
		VIRTUAL CBYTE Left() const;

		VIRTUAL VOID Render(RCIUIRENDERER renderer);
	};

#pragma endregion


#pragma region [IUiListElement] DEFINITION

	INTERFACE IUiListElement : public IUiElement
	{
	public:

		// ACCESSORS/MUTATORS


		// INTERFACE METHODS


	protected:

		IUiListElement() { }
	};

#pragma endregion


#pragma region [IUiField] DEFINITION

	INTERFACE IUiField : public IUiElement
	{
	public:

		// ACCESSORS/MUTATORS

		VIRTUAL RCVALUE Value() const = 0;
		VIRTUAL RVALUE Value() = 0;

		VIRTUAL CBOOL ShowLabel() const = 0;


		// INTERFACE METHODS

		VIRTUAL CBOOL Prompt() = 0;


	protected:

		IUiField() { }
	};

#pragma endregion


#pragma region [UiFieldBase] DEFINITION

	CLASS UiFieldBase : public UiElementBase, public IUiField
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL RCVALUE Value() const;
		VIRTUAL RVALUE Value();

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt();


	protected:

		// INSTANCE VARIABLES

		PFIELD _Field = NULL;

		BOOL _ShowLabel = TRUE;
	};

#pragma endregion


#pragma region [BooleanUiField] DEFINITION

	CLASS BooleanUiField : public UiFieldBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [AlphaUiField] DEFINITION

	CLASS AlphaUiFieldBase : public UiFieldBase
	{
	public:


	protected:

		// INSTANCE VARIABLES

		BYTE _Length = 0;

		AllowedCharFlags _AllowedChars = AllowedCharFlags::ALLOWED_CHARS_ALL;
		PCCHAR _ExtraChars = NULL;
	};

#pragma endregion


#pragma region [CharUiField] DEFINITION

	CLASS CharUiField : public AlphaUiFieldBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [StringUiField] DEFINITION

	CLASS StringUiField : public AlphaUiFieldBase
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [MaskedStringUiField] DEFINITION

	CLASS MaskedStringUiField : public StringUiField
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [DateUiField] DEFINITION

	CLASS DateUiField : public MaskedStringUiField
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [TimeUiField] DEFINITION

	CLASS TimeUiField : public MaskedStringUiField
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [NumericUiField] DEFINITION

	template NUMERIC_UI_FIELD_T_CLAUSE_DEF
	CLASS NumericUiField : public UiFieldBase
	{
	public:


	protected:

		// INSTANCE VARIABLES

		T _MinValue = 0;
		T _MaxValue = T_MAX;
		T _Step = T(1);
		T _StepLarge = T(10);
	};

#pragma endregion


#pragma region [FloatUiField] DEFINITION

	CLASS FloatUiField : public NumericUiField<WORD>
	{
	public:


	protected:

		// INSTANCE VARIABLES

		BYTE _DecimalDigits = 1;

		WORD _DecimalStep = 1;
		WORD _DecimalStepLarge = 10;
	};

#pragma endregion


#pragma region [ListUiField] DEFINITION

	CLASS ListUiField : public UiFieldBase, public IUiListElement
	{
	public:


	protected:

		// INSTANCE VARIABLES

		BYTE _NumChoices = 0;
		PPCCHAR _Choices = NULL;

		BOOL _AllowMultipleSelections = FALSE;
	};

#pragma endregion
};

#endif
