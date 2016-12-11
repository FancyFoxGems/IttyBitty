/***********************************************************************************************
* [IttyBitty_UI_field_decorators.h]: STRUCTURES FOR ADDED-VALUE UI FIELD BEHAVIOR
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UI_FIELD_DECORATORS_H
#define _ITTYBITTY_UI_FIELD_DECORATORS_H


#include "IttyBitty_UI_fields.h"


#pragma region DEFINES

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	#define UI_FIELD_DECORATOR_T_CLAUSE_DEF		<class TUiField>
	#define UI_FIELD_DECORATOR_T_CLAUSE			<class TUiField>
	#define UI_FIELD_DECORATOR_T_ARGS			<TUiField>

	template UI_FIELD_DECORATOR_T_CLAUSE
	class UiFieldDecoratorBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_FIELD_DECORATOR_T_CLAUSE), \
		CSL(UI_FIELD_DECORATOR_T_ARGS), UiFieldDecoratorBase, UIFIELDDECORATORBASE);

	template UI_FIELD_DECORATOR_T_CLAUSE
	class NullUiFieldDecorator;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_FIELD_DECORATOR_T_CLAUSE), \
		CSL(UI_FIELD_DECORATOR_T_ARGS), NullUiFieldDecorator, NULLUIFIELDDECORATOR);

	template UI_FIELD_DECORATOR_T_CLAUSE
	class UnitUiFieldDecorator;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_FIELD_DECORATOR_T_CLAUSE), \
		CSL(UI_FIELD_DECORATOR_T_ARGS), UnitUiFieldDecorator, UNITUIFIELDDECORATOR);


#ifndef NO_ITTYBITTY_LCD_EXTENSIONS

	template UI_FIELD_DECORATOR_T_CLAUSE
	class GraphUiFieldDecorator;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_FIELD_DECORATOR_T_CLAUSE), \
		CSL(UI_FIELD_DECORATOR_T_ARGS), GraphUiFieldDecorator, GRAPHUIFIELDDECORATOR);

	template UI_FIELD_DECORATOR_T_CLAUSE
	class SliderUiFieldDecorator;
	TEMPLATE_CLASS_USING_ALIASES(CSL(UI_FIELD_DECORATOR_T_CLAUSE), \
		CSL(UI_FIELD_DECORATOR_T_ARGS), SliderUiFieldDecorator, SLIDERUIFIELDDECORATOR);

#endif

#pragma endregion


#pragma region [UiFieldDecoratorBase] DEFINITION

	template UI_FIELD_DECORATOR_T_CLAUSE_DEF
	CLASS UiFieldDecoratorBase : public TUiField
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [NullUiFieldDecorator] DEFINITION

	template UI_FIELD_DECORATOR_T_CLAUSE_DEF
	CLASS NullUiFieldDecorator final : public UiFieldDecoratorBase<TUiField>
	{
	public:


	};

#pragma endregion


#pragma region [UnitUiFieldDecorator] DEFINITION

	template UI_FIELD_DECORATOR_T_CLAUSE_DEF
	CLASS UnitUiFieldDecorator : public UiFieldDecoratorBase<TUiField>
	{
	public:


	protected:

		// INSTANCE VARIABLES

		PCCHAR _UnitText = NULL;
	};

#pragma endregion


#ifndef NO_ITTYBITTY_LCD_EXTENSIONS

#pragma region [GraphUiFieldDecorator] DEFINITION

	template UI_FIELD_DECORATOR_T_CLAUSE_DEF
	CLASS GraphUiFieldDecorator : public UiFieldDecoratorBase<TUiField>
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion


#pragma region [SliderUiFieldDecorator] DEFINITION

	template UI_FIELD_DECORATOR_T_CLAUSE_DEF
	CLASS SliderUiFieldDecorator : public UiFieldDecoratorBase<TUiField>
	{
	public:


	protected:

		// INSTANCE VARIABLES


	};

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_LCD_EXTENSIONS
};

#endif
