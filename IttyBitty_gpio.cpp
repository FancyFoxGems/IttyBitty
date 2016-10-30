/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/


/* NOTE: COMMENT THE FOLLOWING LINE OUT TO ENABLE A FULLY FEATURED / FULL BUILD OF THE LIBRARY */
//#define ITTYBITTY_SLIM


#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_BYTES)
	#define EXCLUDE_ITTYBITTY_BYTES
#endif

#ifndef EXCLUDE_ITTYBITTY_GPIO

#include "IttyBitty_gpio.h"

using namespace IttyBitty;


#ifndef EXCLUDE_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter)	\
		RBITPACK P##port_letter##_DDR	= *(PACK_BYTE_REF((RVBYTE)DDR##port_letter));	\
		RBITPACK P##port_letter##_PORT	= *(PACK_BYTE_REF((RVBYTE)PORT##port_letter));	\
		RBITPACK P##port_letter##_PIN	= *(PACK_BYTE_REF((RVBYTE)PIN##port_letter));	\
		REG8 DDR##port_letter##_REG(&DDR##port_letter);									\
		REG8 PORT##port_letter##_REG(&PORT##port_letter);								\
		REG8 PIN##port_letter##_REG(&PIN##port_letter);									\
		PORT Port##port_letter(DDR##port_letter##_REG, PORT##port_letter##_REG, PIN##port_letter##_REG);

#else	// #ifdef EXCLUDE_ITTYBITTY_BYTES

	#define _INITIALIZE_PORT_STRUCTS(port_letter)	\
		RBITPACK P##port_letter##_DDR	= *(PACK_BYTE_REF((RVBYTE)DDR##port_letter));	\
		RBITPACK P##port_letter##_PORT	= *(PACK_BYTE_REF((RVBYTE)PORT##port_letter));	\
		RBITPACK P##port_letter##_PIN	= *(PACK_BYTE_REF((RVBYTE)PIN##port_letter));	\

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


PVBYTE ARDUINO_PORT_TO_MODE[NUM_PORTS];
PVBYTE ARDUINO_PORT_TO_OUTPUT[NUM_PORTS];
PVBYTE ARDUINO_PORT_TO_INPUT[NUM_PORTS];

BYTE ARDUINO_PIN_TO_PORT[NUM_DIGITAL_PINS];
BYTE ARDUINO_PIN_TO_MASK[NUM_DIGITAL_PINS];


#ifndef EXCLUDE_ITTYBITTY_BYTES


namespace IttyBitty
{
	#define _TYPEDEF_PINS(port_letter)							\
		typedef PIN<0, &Port##port_letter> Pin##port_letter##0;	\
		typedef PIN<1, &Port##port_letter> Pin##port_letter##1;	\
		typedef PIN<2, &Port##port_letter> Pin##port_letter##2;	\
		typedef PIN<3, &Port##port_letter> Pin##port_letter##3;	\
		typedef PIN<4, &Port##port_letter> Pin##port_letter##4;	\
		typedef PIN<5, &Port##port_letter> Pin##port_letter##5;	\
		typedef PIN<6, &Port##port_letter> Pin##port_letter##6;	\
		typedef PIN<7, &Port##port_letter> Pin##port_letter##7;

	#ifdef PORTA
		_TYPEDEF_PINS(A)
	#endif

	#ifdef PORTB
		_TYPEDEF_PINS(B)
	#endif

	#ifdef PORTC
		_TYPEDEF_PINS(C)
	#endif

	#ifdef PORTD
		_TYPEDEF_PINS(D)
	#endif

	#ifdef PORTE
		_TYPEDEF_PINS(E)
	#endif

	#ifdef PORTF
		_TYPEDEF_PINS(F)
	#endif

	#ifdef PORTG
		_TYPEDEF_PINS(G)
	#endif

	#ifdef PORTH
		_TYPEDEF_PINS(H)
	#endif

	#ifdef PORTJ
		_TYPEDEF_PINS(J)
	#endif

	#ifdef PORTK
		_TYPEDEF_PINS(K)
	#endif

	#ifdef PORTL
		_TYPEDEF_PINS(L)
	#endif
}

#endif	// #ifdef EXCLUDE_ITTYBITTY_BYTES


#ifndef EXCLUDE_ITTYBITTY_BYTES

	#define _GPIO_INITIALIZE_PORT(port_letter) RPORT GPIO::P##port_letter = Port##port_letter;

	#define _GPIO_TYPEDEF_PINS(port_letter)						\
		typedef PIN<0, &Port##port_letter> Pin##port_letter##0;	\
		typedef PIN<1, &Port##port_letter> Pin##port_letter##1;	\
		typedef PIN<2, &Port##port_letter> Pin##port_letter##2;	\
		typedef PIN<3, &Port##port_letter> Pin##port_letter##3;	\
		typedef PIN<4, &Port##port_letter> Pin##port_letter##4;	\
		typedef PIN<5, &Port##port_letter> Pin##port_letter##5;	\
		typedef PIN<6, &Port##port_letter> Pin##port_letter##6;	\
		typedef PIN<7, &Port##port_letter> Pin##port_letter##7;

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

#endif	// #ifndef EXCLUDE_ITTYBITTY_GPIO
