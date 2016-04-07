/************************************************************************************
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.  *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT. *
************************************************************************************/

#include "IttyBitty_gpio.h"

using namespace IttyBitty;


#define _INITIALIZE_PORT(port_letter) PORT Port##port_letter((RVBYTE)DDR##port_letter, (RVBYTE)PORT##port_letter, (RVBYTE)PIN##port_letter);

#ifdef PORTA
	_INITIALIZE_PORT(A)
#endif

#ifdef PORTB
	_INITIALIZE_PORT(B)
#endif

#ifdef PORTC
	_INITIALIZE_PORT(C)
#endif

#ifdef PORTD
	_INITIALIZE_PORT(D)
#endif

#ifdef PORTE
	_INITIALIZE_PORT(E)
#endif

#ifdef PORTF
	_INITIALIZE_PORT(F)
#endif

#ifdef PORTG
	_INITIALIZE_PORT(G)
#endif

#ifdef PORTH
	_INITIALIZE_PORT(H)
#endif


//RCIOPORTS GPIO_PORTS = IOPorts::Instance();