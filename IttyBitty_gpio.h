/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_registers.h"
#include "IttyBitty_bytes.h"


namespace IttyBitty
{
	class GPIO
	{
	 public:
		GPIO();

	 protected:
	};

	typedef GPIO * PGPIO, & RGPIO;
	typedef const GPIO CGPIO, * PCGPIO, & RCGPIO;
}

extern const IttyBitty::GPIO gp;


#endif
