/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE
{
} SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifdef ITTYBITTY_BASE
	#define NO_ITTYBITTY_MENUI
#endif

#ifndef NO_ITTYBITTY_MENUI

#include "IttyBitty_UI_elements.h"

using namespace IttyBitty;


#pragma region [UiElementBase] IMPLEMENTATION

// CONSTRUCTOR

UiElementBase::UiElementBase(FLASH_STRING label) : _Label(label) { }


// [IUiElement] IMPLEMENTATION

CBOOL UiElementBase::operator >(RCIUIELEMENT other) const
{
	return this->Width() > other.Width();
}

FLASH_STRING UiElementBase::Label() const
{
	return _Label;
}

PCCHAR UiElementBase::LabelString() const
{
	PGM_P pLabel = reinterpret_cast<PGM_P>(_Label);
	PCHAR label = new char[strlen_P(pLabel)];

	strcpy_P(label, pLabel);

	return label;
}

CBYTE UiElementBase::Width() const
{
	return strlen_P(reinterpret_cast<PGM_P>(_Label));
}

CBYTE UiElementBase::Height() const
{
	return 1;
}

VOID UiElementBase::Render(RIUIRENDERER renderer, CBYTE col, CBYTE row)
{
	renderer.PrintString_P(_Label, col, row);
}


// [IUiNavigationListener] IMPLEMENTATION

VOID UiElementBase::Up(CUIACTIONSTATE state) { }

VOID UiElementBase::Down(CUIACTIONSTATE state) { }

VOID UiElementBase::Left(CUIACTIONSTATE state) { }

VOID UiElementBase::Right(CUIACTIONSTATE state) { }

VOID UiElementBase::Return(CUIACTIONSTATE state) { }

VOID UiElementBase::Select(CUIACTIONSTATE state) { }

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
