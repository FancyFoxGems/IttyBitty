/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

/* NOTE: COMMENT THE FOLLOWING LINE OUT TO ENABLE A FULLY FEATURED / FULL BUILD OF THE LIBRARY */
#define ITTYBITTY_SLIM

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_BYTES)
	#define EXCLUDE_ITTYBITTY_BYTES
#endif


#include "IttyBitty_gpio.h"

using namespace IttyBitty;


#ifndef EXCLUDE_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter) PORT Port##port_letter((RVBYTE)DDR##port_letter, (RVBYTE)PORT##port_letter, (RVBYTE)PIN##port_letter);

#else	// #ifdef EXCLUDE_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter) RBITPACK P##port_letter##_DDR = *(PACK_BYTE_REF((RVBYTE)DDR##port_letter)); \
		RBITPACK P##port_letter##_PORT = *(PACK_BYTE_REF((RVBYTE)PORT##port_letter)); \
		RBITPACK P##port_letter##_PIN = *(PACK_BYTE_REF((RVBYTE)PIN##port_letter)); \

#endif	// #ifndef EXCLUDE_ITTYBITTY_BYTES


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


PVBYTE ARDUINO_MODE_PORTS[NUM_PORTS];
PVBYTE ARDUINO_OUT_PORTS[NUM_PORTS];
PVBYTE ARDUINO_IN_PORTS[NUM_PORTS];

BYTE ARDUINO_PIN_TO_PORT[NUM_DIGITAL_PINS];
BYTE ARDUINO_PIN_TO_MASK[NUM_DIGITAL_PINS];


#ifndef EXCLUDE_ITTYBITTY_BYTES

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

#endif	// #ifndef EXCLUDE_ITTYBITTY_BYTES
