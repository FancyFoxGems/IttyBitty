/************************************************************************************
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.  *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT. *
************************************************************************************/

#ifndef _ITTYBITTY_PLACEMENT_NEW
#define _ITTYBITTY_PLACEMENT_NEW

#if !defined(ARDUINO) || ARDUINO < 20000 // NOTE: Assume Arduino 2.0+ will define placement new??

	#include "IttyBitty_aliases.h"


	/* PLACEMENT NEW IMPLEMENTATION */

	INLINE PVOID operator new(SIZE size, PVOID ptr)
	{
		return ptr;
	}

	INLINE PVOID operator new[](SIZE size, PVOID ptr)
	{
		return ptr;
	}

	
#endif	// if !defined(ARDUINO)...
	
#endif
