/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

/* NOTE: UNCOMMENT THE FOLLOWING LINE OUT TO DISABLE A FULLY FEATURED / FULL BUILD OF THE LIBRARY */
//#define ITTYBITTY_BASE

/* NOTE: UNCOMMENT THE FOLLOWING LINE OUT TO ENABLE A MINIMAL BUILD OF THE LIBRARY */
//#define ITTYBITTY_SLIM

#ifdef ITTYBITTY_SLIM
	#define ITTYBITTY_BASE
#endif

#ifdef ITTYBITTY_SLIM
	#define NO_ITTYBITTY_BYTES
#elif defined(ITTYBITTY_BASE)
	#define NO_ITTYBITTY_FULL_BYTES
#endif

#ifndef NO_ITTYBITTY_GPIO


#include "IttyBitty_GPIO.h"

using namespace IttyBitty;


#ifdef ARDUINO

#pragma region ARDUINO PORT/PIN MAPPING GLOBAL VARIABLE DEFINITIONS

PVBYTE ARDUINO_PORT_TO_MODE[NUM_PORTS];
PVBYTE ARDUINO_PORT_TO_OUTPUT[NUM_PORTS];
PVBYTE ARDUINO_PORT_TO_INPUT[NUM_PORTS];

BYTE ARDUINO_PIN_TO_PORT[NUM_DIGITAL_PINS];
BYTE ARDUINO_PIN_TO_MASK[NUM_DIGITAL_PINS];

#pragma endregion


#pragma region ARDUINO INITIALIZATION GLOBAL FUNCTION DEFINITIONS

namespace IttyBitty
{
	VOID _InitializeGPIO()
	{
		_InitializeArduinoPortTables();
		_InitializeArduinoPinTables();
	}

	VOID _InitializeArduinoPortTables()
	{
		for (SIZE i = 0; i < NUM_PORTS; i++)
		{
			if (i == 9) ++i;
			ARDUINO_PORT_TO_MODE[i]		= reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_mode_PGM[i + ARDUINO_PORT_INDEX_CORRECTION]));
			ARDUINO_PORT_TO_OUTPUT[i]	= reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_output_PGM[i + ARDUINO_PORT_INDEX_CORRECTION]));
			ARDUINO_PORT_TO_INPUT[i]	= reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_input_PGM[i + ARDUINO_PORT_INDEX_CORRECTION]));
		}
	}

	VOID _InitializeArduinoPinTables()
	{
		for (SIZE i = 0; i < NUM_DIGITAL_PINS; i++)
		{
			ARDUINO_PIN_TO_PORT[i] = pgm_read_byte(&digital_pin_to_port_PGM[i]) - ARDUINO_PORT_INDEX_CORRECTION;
			ARDUINO_PIN_TO_MASK[i] = pgm_read_byte(&digital_pin_to_bit_mask_PGM[i]);
		}
	}
};

#pragma endregion


#pragma region ARDUINO PIN GLOBAL FUNCTION DEFINITIONS

CPINMODE GetPinMode(PIN_NUMBER p)
{
	return GET_ARDUINO_PIN_MODE(p);
}

VOID SetPinMode(PIN_NUMBER p, CPINMODE mode)
{
	SET_ARDUINO_PIN_MODE(p, mode);
}

VOID SetPinMode(PIN_NUMBER p, CBYTE arduinoMode)
{
	SET_ARDUINO_PIN_MODE(p, arduinoMode);
}

CBIT ReadPin(PIN_NUMBER p)
{
	return READ_ARDUINO_PIN(p);
}

CBIT (&CheckPinSet)(PIN_NUMBER) = ReadPin;

CBIT CheckPinUnset(PIN_NUMBER p)
{
	return CHECK_ARDUINO_PIN_UNSET(p);
}

VOID WritePin(PIN_NUMBER p, CBIT state)
{
	WRITE_ARDUINO_PIN(p, state);
}

VOID SetPin(PIN_NUMBER p)
{
	SET_ARDUINO_PIN(p);
}

VOID ClearPin(PIN_NUMBER p)
{
	CLEAR_ARDUINO_PIN(p);
}

VOID TogglePin(PIN_NUMBER p)
{
	TOGGLE_ARDUINO_PIN(p);
}

VOID ResetPin(PIN_NUMBER p)
{
	RESET_ARDUINO_PIN(p);
}

#pragma endregion

#endif	// #ifdef ARDUINO


#pragma region BIT-PACKED PORT VARIABLE DEFINITION MACROS

#ifndef NO_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter)	\
		RBITPACK P##port_letter##_DDR	= *(PACK_BYTE_REF((RVBYTE)DDR##port_letter));	\
		RBITPACK P##port_letter##_PORT	= *(PACK_BYTE_REF((RVBYTE)PORT##port_letter));	\
		RBITPACK P##port_letter##_PIN	= *(PACK_BYTE_REF((RVBYTE)PIN##port_letter));	\
		REG8 DDR##port_letter##_REG(&DDR##port_letter);									\
		REG8 PORT##port_letter##_REG(&PORT##port_letter);								\
		REG8 PIN##port_letter##_REG(&PIN##port_letter);									\
		PORT Port##port_letter(DDR##port_letter##_REG, PORT##port_letter##_REG, PIN##port_letter##_REG);

#else	// #ifdef NO_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter)	\
		RBITPACK P##port_letter##_DDR	= *(PACK_BYTE_REF((RVBYTE)DDR##port_letter));	\
		RBITPACK P##port_letter##_PORT	= *(PACK_BYTE_REF((RVBYTE)PORT##port_letter));	\
		RBITPACK P##port_letter##_PIN	= *(PACK_BYTE_REF((RVBYTE)PIN##port_letter));	\

#endif	// #ifndef NO_ITTYBITTY_BYTES

#pragma endregion


#pragma region BIT-PACKED PORT-SPECIFIC VARIABLE DEFINITION CALLS

#ifdef PORTA
	_INITIALIZE_PORT_STRUCTS(A)
#endif

#ifdef PORTB
	_INITIALIZE_PORT_STRUCTS(B)
#endif

#ifdef PORTC
	_INITIALIZE_PORT_STRUCTS(C)
#endif

#ifdef PORTD
	_INITIALIZE_PORT_STRUCTS(D)
#endif

#ifdef PORTE
	_INITIALIZE_PORT_STRUCTS(E)
#endif

#ifdef PORTF
	_INITIALIZE_PORT_STRUCTS(F)
#endif

#ifdef PORTG
	_INITIALIZE_PORT_STRUCTS(G)
#endif

#ifdef PORTH
	_INITIALIZE_PORT_STRUCTS(H)
#endif

#ifdef PORTJ
	_INITIALIZE_PORT_STRUCTS(J)
#endif

#ifdef PORTK
	_INITIALIZE_PORT_STRUCTS(K)
#endif

#ifdef PORTL
	_INITIALIZE_PORT_STRUCTS(L)
#endif

#pragma endregion


#ifndef NO_ITTYBITTY_BYTES

#pragma region PORT-SPECIFIC STRUCTURE DEFINITION CALLS

	#define _GPIO_INITIALIZE_PORT(port_letter) RPORT GPIO::P##port_letter = Port##port_letter;

	#ifdef PORTA
		_GPIO_INITIALIZE_PORT(A)
	#endif

	#ifdef PORTB
		_GPIO_INITIALIZE_PORT(B)
	#endif

	#ifdef PORTC
		_GPIO_INITIALIZE_PORT(C)
	#endif

	#ifdef PORTD
		_GPIO_INITIALIZE_PORT(D)
	#endif

	#ifdef PORTE
		_GPIO_INITIALIZE_PORT(E)
	#endif

	#ifdef PORTF
		_GPIO_INITIALIZE_PORT(F)
	#endif

	#ifdef PORTG
		_GPIO_INITIALIZE_PORT(G)
	#endif

	#ifdef PORTH
		_GPIO_INITIALIZE_PORT(H)
	#endif

	#ifdef PORTJ
		_GPIO_INITIALIZE_PORT(J)
	#endif

	#ifdef PORTK
		_GPIO_INITIALIZE_PORT(K)
	#endif

	#ifdef PORTL
		_GPIO_INITIALIZE_PORT(L)
	#endif

#pragma endregion

#endif	// #ifndef NO_ITTYBITTY_BYTES

#endif	// #ifndef NO_ITTYBITTY_GPIO
