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

	template DEFAULT_T_CLAUSE
	interface IUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), IUiField, IUIFIELD);

	template DEFAULT_T_CLAUSE
	class BaseUiFieldBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), BaseUiFieldBase, BASEUIFIELDBASE);

	template DEFAULT_T_CLAUSE
	class UiFieldBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), UiFieldBase, UIFIELDBASE);

	template DEFAULT_T_CLAUSE
	class VarLengthUiFieldBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), VarLengthUiFieldBase, VARLENGTHUIFIELDBASE);

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

	template DEFAULT_T_CLAUSE
	class NumericUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), NumericUiField, NUMERICUIFIELD);

	class FloatUiField;
	TYPEDEF_CLASS_ALIASES(UiField, UIFIELD);


	template DEFAULT_T_CLAUSE
	class ListUiFieldChoice;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), ListUiFieldChoice, LISTUIFIELDCHOICE);

	template DEFAULT_T_CLAUSE
	class ListUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), ListUiField, LISTUIFIELD);

#pragma endregion


#pragma region [IUiField] DEFINITION

	template DEFAULT_T_CLAUSE
	INTERFACE IUiField : public IUiElement
	{
	public:

		// ACCESSORS/MUTATORS

		VIRTUAL CONST T & Value() const = 0;
		VIRTUAL T & Value() = 0;

		VIRTUAL CBOOL ShowLabel() const = 0;


		// INTERFACE METHODS

		VIRTUAL CBOOL Prompt(PIUIRENDERER) = 0;


	protected:

		IUiField() { }
	};

#pragma endregion


#pragma region [BaseUiFieldBase] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS BaseUiFieldBase : public UiElementBase, public IUiField<T>
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt(PIUIRENDERER);


	protected:

		// INSTANCE VARIABLES

		BOOL _ShowLabel = TRUE;
	};

#pragma endregion


#pragma region [UiFieldBase] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS UiFieldBase : public BaseUiFieldBase<T>
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL CONST T & Value() const;
		VIRTUAL T & Value();

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt(PIUIRENDERER);


	protected:

		// INSTANCE VARIABLES

		PTYPEDFIELD<T> _Field = NULL;
	};

#pragma endregion


#pragma region [UiFieldBase] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS VarLengthUiFieldBase : public BaseUiFieldBase<T>
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL CONST T & Value() const;
		VIRTUAL T & Value();

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt(PIUIRENDERER);


	protected:

		// INSTANCE VARIABLES

		PVARLENGTHTYPEDFIELD<T> _Field = NULL;
	};

#pragma endregion


#pragma region [BooleanUiField] DEFINITION

	CLASS BooleanUiField : public UiFieldBase<BOOL>
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [AlphaUiField] DEFINITION

	CLASS AlphaUiFieldBase : public VarLengthUiFieldBase<CHAR>
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

	template DEFAULT_T_CLAUSE
	CLASS NumericUiField : public UiFieldBase<T>
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


#pragma region [UiFieldChoice] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS ListUiFieldChoice : public UiFieldBase<T>, public IUiChoice
	{
	public:


		// [IUiElement] OVERRIDES

		VIRTUAL VOID Render(PIUIRENDERER);

	protected:

		// INSTANCE VARIABLES

	};

#pragma endregion


#pragma region [ListUiField] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS ListUiField : public UiFieldBase<T>, public IUiListElement<ListUiFieldChoice<T>>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ListUiField(CBYTE, PPLISTUIFIELDCHOICE<T>, CBOOL = FALSE);
		ListUiField(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_LIST_CAPACITY);

		VIRTUAL ~ListUiField();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IUiContainerElement] IMPLEMENTATION

		VIRTUAL PCLISTUIFIELDCHOICE<T> operator[](CBYTE i) const;
		VIRTUAL PLISTUIFIELDCHOICE<T> operator[](CBYTE i);

		VIRTUAL CBYTE ChildCount() const;

		VIRTUAL RCLISTUIFIELDCHOICE<T> Child(CBYTE i = 0) const;
		VIRTUAL RLISTUIFIELDCHOICE<T> Child(CBYTE i = 0);

		VIRTUAL RLISTUIFIELDCHOICE<T> AddChild(RLISTUIFIELDCHOICE<T> child);

		VIRTUAL VOID RemoveChild(CBYTE i);
		VIRTUAL VOID RemoveChild(RLISTUIFIELDCHOICE<T> child);


		// [IUiListElement] IMPLEMENTATION

		VIRTUAL CBOOL MultipleSelectionsAllowed() const;
		VIRTUAL VOID SetAllowMultipleSelections(CBOOL multipleSelectionsAllowed = TRUE);


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

		BOOL _AllowMultipleSelections = FALSE;

		PPLISTUIFIELDCHOICE<T> _Choices = NULL;
		BYTE _ChoiceCount = 0;
	};

#pragma endregion
};

#endif
