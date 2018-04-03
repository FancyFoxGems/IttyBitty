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
	class UiFieldBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), UiFieldBase, UIFIELDBASE);

	template DEFAULT_T_CLAUSE
	class UiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), UiField, UIFIELD);

	template DEFAULT_T_CLAUSE
	class VarLengthUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), VarLengthUiField, VARLENGTHUIFIELD);

	class BooleanUiField;
	TYPEDEF_CLASS_ALIASES(BooleanUiField, BOOLEANUIFIELD);

	class AlphaUiField;
	TYPEDEF_CLASS_ALIASES(AlphaUiField, ALPHAUIFIELD);

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
	TYPEDEF_CLASS_ALIASES(FloatUiField, FLOATUIFIELD);


	template DEFAULT_T_CLAUSE
	class ListUiFieldBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), ListUiFieldBase, LISTUIFIELDBASE);

	template DEFAULT_T_CLAUSE
	class ListUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), ListUiField, LISTUIFIELD);

	template DEFAULT_T_CLAUSE
	class MultiListUiField;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), MultiListUiField, MULTILISTUIFIELD);

	template DEFAULT_T_CLAUSE
	class ListUiFieldChoice;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DEFAULT_T_CLAUSE), \
		CSL(DEFAULT_T_ARGS), ListUiFieldChoice, LISTUIFIELDCHOICE);

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

		VIRTUAL CBOOL Prompt(RIUIRENDERER) = 0;


	protected:

		IUiField() { }
	};

#pragma endregion


#pragma region [UiFieldBase] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS UiFieldBase : public UiElement//, public IUiField<T>
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt(RIUIRENDERER);


	protected:

		// INSTANCE VARIABLES

		BOOL _ShowLabel = TRUE;
	};

#pragma endregion


#pragma region [UiField] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS UiField : public UiFieldBase<T>
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL CONST T & Value() const;
		VIRTUAL T & Value();

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt(RIUIRENDERER);


	protected:

		// INSTANCE VARIABLES

		PTYPEDFIELD<T> _Field = NULL;
	};

#pragma endregion


#pragma region [UiField] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS VarLengthUiField : public UiFieldBase<T>
	{
	public:

		// [IUiField] IMPLEMENTATION

		VIRTUAL CONST T & Value() const;
		VIRTUAL T & Value();

		VIRTUAL CBOOL ShowLabel() const;

		VIRTUAL CBOOL Prompt(RIUIRENDERER);


	protected:

		// INSTANCE VARIABLES

		PVARLENGTHTYPEDFIELD<T> _Field = NULL;
	};

#pragma endregion


#pragma region [BooleanUiField] DEFINITION

	CLASS BooleanUiField : public UiField<BOOL>
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [AlphaUiField] DEFINITION

	CLASS AlphaUiField : public VarLengthUiField<CHAR>
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

	CLASS CharUiField : public AlphaUiField
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [StringUiField] DEFINITION

	CLASS StringUiField : public AlphaUiField
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
	CLASS NumericUiField : public UiField<T>
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


#pragma region [ListUiFieldBase] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS ListUiFieldBase : public UiField<T>, public UiContainerElement<ListUiFieldChoice<T>>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		ListUiFieldBase(CBYTE, PPLISTUIFIELDCHOICE<T>, CBOOL = FALSE);
		ListUiFieldBase(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_LIST_CAPACITY);

		VIRTUAL ~ListUiFieldBase();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE = CLICK);
		VOID Down(CUIACTIONSTATE = CLICK);
		VOID Left(CUIACTIONSTATE = CLICK);
		VOID Right(CUIACTIONSTATE = CLICK);
		VOID Return(CUIACTIONSTATE = CLICK);
		VOID Select(CUIACTIONSTATE = CLICK);


	protected:
	};

#pragma endregion


#pragma region [ListUiField] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS ListUiField : public ListUiFieldBase<T>, public IUiListElement<T>
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

		// [IUiListElement] IMPLEMENTATION

		VIRTUAL CONST T & GetSelectedItem() const;
		VIRTUAL VOID SetSelectedItem(CONST T &);


		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE = CLICK);
		VOID Down(CUIACTIONSTATE = CLICK);
		VOID Left(CUIACTIONSTATE = CLICK);
		VOID Right(CUIACTIONSTATE = CLICK);
		VOID Return(CUIACTIONSTATE = CLICK);
		VOID Select(CUIACTIONSTATE = CLICK);
	};

#pragma endregion


#pragma region [MultiListUiField] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS MultiListUiField : public ListUiFieldBase<T>, public IUiMultiListElement<T>
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		MultiListUiField(CBYTE, PPLISTUIFIELDCHOICE<T>, CBOOL = FALSE);
		MultiListUiField(CBOOL = FALSE, CBYTE = MENUI_DEFAULT_LIST_CAPACITY);

		VIRTUAL ~MultiListUiField();


	protected:

		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:

		// [IUiMultiListElement] IMPLEMENTATION

		VIRTUAL CBYTE NumSelected() const;

		VIRTUAL CONST T * GetSelectedItems() const;
		VIRTUAL VOID SetSelectedItems(CONST T * &, CBYTE);


		// [IUiNavigationListener] OVERRIDES

		VOID Up(CUIACTIONSTATE = CLICK);
		VOID Down(CUIACTIONSTATE = CLICK);
		VOID Left(CUIACTIONSTATE = CLICK);
		VOID Right(CUIACTIONSTATE = CLICK);
		VOID Return(CUIACTIONSTATE = CLICK);
		VOID Select(CUIACTIONSTATE = CLICK);
	};

#pragma endregion


#pragma region [UiFieldChoice] DEFINITION

	template DEFAULT_T_CLAUSE
	CLASS ListUiFieldChoice : public UiField<T>, public IUiChoice<ListUiField<T>>
	{
	public:

		// [IUiChildElement] IMPLEMENTATION

		VIRTUAL PLISTUIFIELD<T> Parent() const;
		VIRTUAL VOID SetParent(PLISTUIFIELD<T>);


		// [IUiChoice] IMPLEMENTATION

		VIRTUAL CBOOL IsSelected() const;
		VIRTUAL VOID SetSelected(CBOOL);


		// [IUiElement] OVERRIDES

		VOID Render(RIUIRENDERER, CBYTE = 0, CBYTE = 0);


	protected:

		// INSTANCE VARIABLES

		BOOL _Selected = FALSE;

	};

#pragma endregion
};

#endif
