/************************************************************************************
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.  *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT. *
************************************************************************************/

#if defined(ITTYBITTY_SLIM) && !defined(EXCLUDE_ITTYBITTY_BYTES)
	#define EXCLUDE_ITTYBITTY_BYTES
#endif

#include "IttyBitty_gpio.h"


using namespace IttyBitty;


#ifndef EXCLUDE_ITTYBITTY_BYTES


#define _INITIALIZE_PORT(port_letter) PORT Port##port_letter((RVBYTE)DDR##port_letter, (RVBYTE)PORT##port_letter, (RVBYTE)PIN##port_letter);
#define _GPIO_INITIALIZE_PORT(port_letter) RPORT GPIO::P##port_letter = Port##port_letter;

#ifdef PORTA
	_INITIALIZE_PORT(A)
	_GPIO_INITIALIZE_PORT(A)
#endif

#ifdef PORTB
	_INITIALIZE_PORT(B)
	_GPIO_INITIALIZE_PORT(B)
#endif

#ifdef PORTC
	_INITIALIZE_PORT(C)
	_GPIO_INITIALIZE_PORT(C)
#endif

#ifdef PORTD
	_INITIALIZE_PORT(D)
	_GPIO_INITIALIZE_PORT(D)
#endif

#ifdef PORTE
	_INITIALIZE_PORT(E)
	_GPIO_INITIALIZE_PORT(E)
#endif

#ifdef PORTF
	_INITIALIZE_PORT(F)
	_GPIO_INITIALIZE_PORT(F)
#endif

#ifdef PORTG
	_INITIALIZE_PORT(G)
	_GPIO_INITIALIZE_PORT(G)
#endif

#ifdef PORTH
	_INITIALIZE_PORT(H)
	_GPIO_INITIALIZE_PORT(H)
#endif


#else	// #ifdef EXCLUDE_ITTYBITTY_BYTES


#define _INITIALIZE_PORT_REGISTERS(port_letter) RCBITPACK P##port_letter##_DDR = *MAKE_CONST(PACK_BYTE_REF((RVBYTE)DDR##port_letter)); \
	RCBITPACK P##port_letter##_PORT = *MAKE_CONST(PACK_BYTE_REF((RVBYTE)PORT##port_letter)); \
	RCBITPACK P##port_letter##_PIN = *MAKE_CONST(PACK_BYTE_REF((RVBYTE)PIN##port_letter)); \

#ifdef PORTA
	_INITIALIZE_PORT_REGISTERS(A)
#endif

#ifdef PORTB
	_INITIALIZE_PORT_REGISTERS(B)
#endif

#ifdef PORTC
	_INITIALIZE_PORT_REGISTERS(C)
#endif

#ifdef PORTD
	_INITIALIZE_PORT_REGISTERS(D)
#endif

#ifdef PORTE
	_INITIALIZE_PORT_REGISTERS(E)
#endif

#ifdef PORTF
	_INITIALIZE_PORT_REGISTERS(F)
#endif

#ifdef PORTG
	_INITIALIZE_PORT_REGISTERS(G)
#endif

#ifdef PORTH
	_INITIALIZE_PORT_REGISTERS(H)
#endif


#endif	// #ifndef EXCLUDE_ITTYBITTY_BYTES
