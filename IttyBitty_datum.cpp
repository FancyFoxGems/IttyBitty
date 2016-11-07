/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef EXCLUDE_ITTYBITTY_DATUM


#include "IttyBitty_datum.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANT & VARIABLE DEFINITIONS

#ifdef ARDUINO
CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;
#endif

CBYTE IttyBitty::DATA_SIZE_MASK = 0xF0;

PBYTE IttyBitty::__datum_buffer = NULL;

#pragma endregion


namespace IttyBitty
{
#pragma region HELPER GLOBAL FUNCTION DEFINITIONS

	template<typename T>
	PCHAR StringInsertValue(CONST T value, PCHAR buffer, CBYTE radix = 0x10)
	{
		CHAR valStr[2 * T_SIZE + 1];
		
		valStr[2 * T_SIZE] = '\0';
		
		itoa(value, valStr, radix);

		BYTE lenDiff = 2 * T_SIZE - strlen(valStr);
		for (SIZE i = 0; i < lenDiff; i++)
		{
			valStr[i + lenDiff] = valStr[i];
			valStr[i] = '0';
		}

		memcpy(buffer, valStr, 2 * T_SIZE);

		return (PCHAR)(buffer + 2 * T_SIZE);
	}

	template<typename T>
	PCCHAR StringReadValue(T & value, PCCHAR data, CBYTE radix = 0x10)
	{
		CHAR valStr[2 * T_SIZE + 1];

		valStr[2 * T_SIZE] = '\0';

		memcpy(valStr, data, 2 * T_SIZE);
		valStr[2 * T_SIZE] = '\0';

		value = static_cast<T>(strtol(valStr, NULL, 0x10));
		
		return (PCCHAR)(data + 2 * T_SIZE);
	}

#pragma endregion
};

#endif	// #ifndef EXCLUDE_ITTYBITTY_DATUM
