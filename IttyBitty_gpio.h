/*******************************************************************************
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*******************************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_bytes.h"
#include "IttyBitty_registers.h"


namespace IttyBitty
{
	struct _Port;
	typedef struct _Port _port_t, Port, PORT, * PPORT, & RPORT, ** PPPORT;
	typedef const struct _Port CPORT, * PCPORT, & RCPORT, ** PPCPORT;


	STRUCT _Port
	{
	public:



	protected:

		REG8 _DirectionReg;
		REG8 _OutputReg;
		REG8 _InputReg;
	};


	class GPIO;
	typedef GPIO _gpio_t, * PGPIO, & RGPIO, ** PPGPIO;
	typedef const GPIO CGPIO, * PCGPIO, & RCGPIO, ** PPCGPIO;

	CLASS GPIO
	{
	 public:

		GPIO();

	 protected:
	};

	//using GPIO::GPIO;
}


#endif
