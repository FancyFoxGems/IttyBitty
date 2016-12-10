/***********************************************************************************************
* [IttyBitty_menu_fields.h]: SPECIALIZED MENU ITEM TYPES TO ALLOW FOR DATA ENTRY AND DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENU_FIELDS_H
#define _ITTYBITTY_MENU_FIELDS_H


#include "IttyBitty_menu_items.h"


#pragma region DEFINES

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IUiField;
	TYPEDEF_CLASS_ALIASES(IUiField, IUIFIELD);

	class UiFieldBase;
	TYPEDEF_CLASS_ALIASES(UiFieldBase, UIFIELDBASE);

	class AlphaUiFieldBase;
	TYPEDEF_CLASS_ALIASES(AlphaUiFieldBase, ALPHAUIFIELDBASE);

	class CharUiField;
	TYPEDEF_CLASS_ALIASES(CharUiField, CHARUIFIELD);

	class StringUiField;
	TYPEDEF_CLASS_ALIASES(StringUiField, STRINGUIFIELD);

	class BooleanUiField;
	TYPEDEF_CLASS_ALIASES(BooleanUiField, BOOLEANUIFIELD);

	class CustomBooleanUiField;
	TYPEDEF_CLASS_ALIASES(CustomBooleanUiField, CUSTOMBOOLEANUIFIELD);


	#define NUMERIC_UI_FIELD_T_CLAUSE_DEF	<typename T>
	#define NUMERIC_UI_FIELD_T_CLAUSE		<typename T>
	#define NUMERIC_UI_FIELD_T_ARGS			<T>

	template NUMERIC_UI_FIELD_T_CLAUSE
	class NumericUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(NUMERIC_UI_FIELD_T_CLAUSE), \
		CSL(NUMERIC_UI_FIELD_T_ARGS), NumericUiField, NUMERICUIFIELD);

	class FloatUiField;
	TYPEDEF_CLASS_ALIASES(UiField, UIFIELD);

#pragma endregion


#pragma region ENUMS

	enum AllowedCharFlags : BYTE
	{
		ALLOWED_CHARS_ALL		= 0x0,
		ALLOWED_CHARS_NUMERIC	= 0x1,
		ALLOWED_CHARS_UPPER		= 0x2,
		ALLOWED_CHARS_LOWER		= 0x4
	};

	TYPEDEF_ENUM_ALIASES(UiSelectionStatusFlags, UISELECTIONSTATUSFLAGS);

#pragma endregion


#pragma region [IUiField] DEFINITION

	INTERFACE IUiField : IUiElement
	{
	public:

		VIRTUAL CBOOL Check() const = 0;


	protected:

		IUiField() { }
	};

#pragma endregion


#pragma region [UiFieldBase] DEFINITION

	CLASS UiFieldBase : UiElementBase, IUiField
	{
	};

#pragma endregion


#pragma region [AlphaUiField] DEFINITION

	CLASS AlphaUiFieldBase : UiFieldBase
	{
	};

#pragma endregion


#pragma region [CharUiField] DEFINITION

	CLASS CharUiField : AlphaUiFieldBase
	{
	};

#pragma endregion


#pragma region [StringUiField] DEFINITION

	CLASS StringUiField : AlphaUiFieldBase
	{
	};

#pragma endregion


#pragma region [BooleanUiField] DEFINITION

	CLASS BooleanUiField : UiFieldBase
	{
	};

#pragma endregion


#pragma region [CustomBooleanUiField] DEFINITION

	CLASS CustomBooleanUiField : BooleanUiField
	{
	};

#pragma endregion


#pragma region [UiFieldDecoratorBase] DEFINITION

	template NUMERIC_UI_FIELD_T_CLAUSE_DEF
	CLASS NumericUiField : UiFieldBase
	{
	};

#pragma endregion


#pragma region [FloatUiField] DEFINITION

	CLASS FloatUiField : NumericUiField<WORD>
	{
	};

#pragma endregion
};

#endif
