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


#pragma region [UiElement] IMPLEMENTATION

// CONSTRUCTOR

UiElement::UiElement(FLASH_STRING label) : _Label(label) { }


// [IUiElement] IMPLEMENTATION

CBOOL UiElement::operator >(RCUIELEMENT other) const
{
	return this->Width() > other.Width();
}

FLASH_STRING UiElement::Label() const
{
	return _Label;
}

PCCHAR UiElement::LabelString() const
{
	PGM_P pLabel = reinterpret_cast<PGM_P>(_Label);
	PCHAR label = new char[strlen_P(pLabel)];

	strcpy_P(label, pLabel);

	return label;
}

CBYTE UiElement::Width() const
{
	return strlen_P(reinterpret_cast<PGM_P>(_Label));
}

CBYTE UiElement::Height() const
{
	return 1;
}

VOID UiElement::Render(RIUIRENDERER renderer, CBYTE col, CBYTE row)
{
	renderer.PrintString_P(_Label, col, row);
}


// [IUiNavigationListener] IMPLEMENTATION

VOID UiElement::Up(CUIACTIONSTATE state) { }

VOID UiElement::Down(CUIACTIONSTATE state) { }

VOID UiElement::Left(CUIACTIONSTATE state) { }

VOID UiElement::Right(CUIACTIONSTATE state) { }

VOID UiElement::Return(CUIACTIONSTATE state) { }

VOID UiElement::Select(CUIACTIONSTATE state) { }

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_MENUI
