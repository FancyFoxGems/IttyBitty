/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/


#if !defined(ARDUINO) || ARDUINO < 20000 // NOTE: Assume Arduino 2.0+ will define placement new?!?


	#include "IttyBitty_aliases.h"


	/* PLACEMENT NEW IMPLEMENTATION */

	PVOID operator new(SIZE size, PVOID ptr)
	{
		return ptr;
	}

	PVOID operator new[](SIZE size, PVOID ptr)
	{
		return ptr;
	}

	
#endif
