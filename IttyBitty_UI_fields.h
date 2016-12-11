/***********************************************************************************************
* [IttyBitty_UI_fields.h]: SPECIALIZED MENU ITEM TYPES TO ALLOW FOR DATA ENTRY AND DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_FIELDS_H
#define _ITTYBITTY_UI_FIELDS_H


#include "IttyBitty_fields.h"
#include "IttyBitty_UI_elements.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IUiField;
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


#pragma region [IUiField] DEFINITION

	INTERFACE IUiField : public IUiElement
	{
	public:

		// ACCESSORS/MUTATORS

		VIRTUAL RCVALUE Value() const = 0;
		VIRTUAL RVALUE Value() = 0;

		VIRTUAL CBOOL ShowLabel() const = 0;


		// INTERFACE METHODS

		VIRTUAL CBOOL Prompt(PIUIRENDERER) = 0;


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

		VIRTUAL CBOOL Prompt(PIUIRENDERER);


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

	CLASS FloatUiField : public NumericUiField<DWORD>
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

	CLASS ListUiField : public UiFieldBase, public IUiListElement<IUiChoice>
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
