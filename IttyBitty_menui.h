/***********************************************************************************************
* [IttyBitty_menui.h]: MENU-BASED UI SYSTEM W/ INPUT FIELDS AND EXTENSIBLE NAVIGATION/DISPLAY
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MENUI_H
#define _ITTYBITTY_MENUI_H


#include "IttyBitty_menu_field_decorators.h"


#pragma region DEFINES

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class MenUI;
	TYPEDEF_CLASS_ALIASES(MenUI, MENUI);

#pragma endregion


#pragma region [MenUI] DEFINITION

	CLASS MenUI : public Menu
	{
		// CONSTRUCTORS/DESTRUCTOR

		MenUI(CBYTE cols, CBYTE rows, PPCIMENUITEM menuHierarchy = NULL);
		MenUI(CBYTE cols, CBYTE rows, CBYTE initMenuCapacity = 0);

		template<typename T>
		CONST T Prompt(RCIUIFIELD field)
		{
			return T(0);
		}
	};

#pragma endregion
};

#endif
