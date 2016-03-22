/********************************************
 Name:		IttyBitty Library
 Created:	3/20/2016
 Author:	Tom Biuso <tjbtech@yahoo.com>
********************************************/

#ifndef _IttyBittyLib_H
#define _IttyBittyLib_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IttyBitty_gpio.h"
#include "IttyBitty_interrupts.h"

#endif
