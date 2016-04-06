/**********************************************************************************
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_bytes.h"
#include "IttyBitty_registers.h"


#define TRISTATE_INPUT INPUT

#define L LOW		// I/O low state; 0x0
#define H HIGH		// I/O high state; 0x1

#define HIGH_Z 0x0	// (Tri-state) input high impedance / disconnected state
#define DISCONNECTED HIGH_Z


namespace IttyBitty
{
	typedef SIZE PIN_NUMBER;
	
	template<PIN_NUMBER pin_number = 0>
	struct _Pin;
	template<PIN_NUMBER pin_number = 0>
	using _pin_t = volatile struct _Pin<pin_number>;
	template<PIN_NUMBER pin_number = 0>
	using Pin = volatile struct _Pin<pin_number>;
	template<PIN_NUMBER pin_number = 0>
	using PIN = volatile struct _Pin<pin_number>;
	template<PIN_NUMBER pin_number = 0>
	using PPIN = volatile struct _Pin<pin_number> *;
	template<PIN_NUMBER pin_number = 0>
	using RPIN = volatile struct _Pin<pin_number> &;
	template<PIN_NUMBER pin_number = 0>
	using PPPIN = volatile struct _Pin<pin_number> **;
	template<PIN_NUMBER pin_number = 0>
	using CPIN = const struct _Pin<pin_number>;
	template<PIN_NUMBER pin_number = 0>
	using PCPIN = const struct _Pin<pin_number> *;
	template<PIN_NUMBER pin_number = 0>
	using RCPIN = const struct _Pin<pin_number> &;
	template<PIN_NUMBER pin_number = 0>
	using PPCPIN = const struct _Pin<pin_number> **;

	struct _PortRegisters;
	typedef volatile struct _PortRegisters _portregisters_t, PortReg, PORTREG, * PPORTREG, & RPORTREG, ** PPPORTREG;
	typedef const struct _PortRegisters CPORTREG, * PCPORTREG, & RCPORTREG, ** PPCPORTREG;

	struct _Port;
	typedef struct _Port _port_t, Port, PORT, * PPORT, & RPORT, ** PPPORT;
	typedef const struct _Port CPORT, * PCPORT, & RCPORT, ** PPCPORT;
	
	struct GPIO;
	typedef GPIO _gpio_t, * PGPIO, & RGPIO, ** PPGPIO;
	typedef const GPIO CGPIO, * PCGPIO, & RCGPIO, ** PPCGPIO;


	template<PIN_NUMBER pin_number>
	STRUCT _Pin
	{
	public:

		ENUM PinMode : BYTE
		{
			Input	= INPUT,
			Output	= OUTPUT,
			PullUp	= INPUT_PULLUP
		};

		ENUM PinState : BYTE
		{
			// Input mode states
			TriStateInput	= 0x0,	// 00b; PinMode::Input OR HIGH_Z << PinMode::Input
			BinaryInput		= 0x2,	// 10b; PinMode::Input OR INPUT_PULLUP << PinMode::Input

			// Output mode states
			CurrentSink		= 0x1,	// 01b; PinMode::Output OR LOW << PinMode::Output
			CurrentSource	= 0x3,	// 11b; PinMode::Output OR HIGH << PinMode::Output
		};
	};

	typedef _Pin<0x0>::PinMode PinMode;
	typedef _Pin<0x0>::PinState PinState;


	STRUCT _PortRegisters
	{
	public:

		RREG8 Direction;
		RREG8 Output;
		RREG8 Input;
	};


	STRUCT _Port
	{
	public:

		_Port(RREG8, RREG8, RREG8);

		~_Port();

		VOID SetPinMode(PinMode = PinMode::Output);



	protected:

		PORTREG _PortReg;
	};


	STRUCT GPIO FINAL
	{
	 public:

		GPIO();

	 private:

		 PPCPORT _Ports;
	};

	//using GPIO::GPIO;
}


#endif
