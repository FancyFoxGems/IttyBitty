/***********************************************************************************************
* [IttyBitty_GPIO.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_GPIO_ARDUINO_H
#define _ITTYBITTY_GPIO_ARDUINO_H


#include "IttyBitty_GPIO.h"


#ifdef PORTA
	CSIZE __DUMMY_PORTA = __COUNTER__;
#endif

#ifdef PORTB
	CSIZE __DUMMY_PORTB = __COUNTER__;
#endif

#ifdef PORTC
	CSIZE __DUMMY_PORTC = __COUNTER__;
#endif

#ifdef PORTD
	CSIZE __DUMMY_PORTD = __COUNTER__;
#endif

#ifdef PORTE
	CSIZE __DUMMY_PORTE = __COUNTER__;
#endif

#ifdef PORTF
	CSIZE __DUMMY_PORTF = __COUNTER__;
#endif

#ifdef PORTG
	CSIZE __DUMMY_PORTG = __COUNTER__;
#endif

#ifdef PORTH
	CSIZE __DUMMY_PORTH = __COUNTER__;
#endif

#ifdef PORTJ
	CSIZE __DUMMY_PORTJ = __COUNTER__;
#endif

#ifdef PORTK
	CSIZE __DUMMY_PORTK = __COUNTER__;
#endif

#ifdef PORTL
	CSIZE __DUMMY_PORTL = __COUNTER__;
#endif


CSIZE NUM_PORTS = __COUNTER__;

EXTERN PVBYTE ARDUINO_PORT_TO_MODE[NUM_PORTS];
EXTERN PVBYTE ARDUINO_PORT_TO_OUTPUT[NUM_PORTS];
EXTERN PVBYTE ARDUINO_PORT_TO_INPUT[NUM_PORTS];

EXTERN BYTE ARDUINO_PIN_TO_PORT[NUM_DIGITAL_PINS];
EXTERN BYTE ARDUINO_PIN_TO_MASK[NUM_DIGITAL_PINS];

#ifndef PORTA
	CONSTEXPR CSIZE ARDUINO_PORT_INDEX_CORRECTION = 2;
#else
	CONSTEXPR CSIZE ARDUINO_PORT_INDEX_CORRECTION = 1;
#endif


INLINE VOID _InitializeArduinoPortTables()
{
	for (SIZE i = 0; i < NUM_PORTS; i++)
	{
		if (i == 9) ++i;
		ARDUINO_PORT_TO_MODE[i]		= reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_mode_PGM[i + ARDUINO_PORT_INDEX_CORRECTION]));
		ARDUINO_PORT_TO_OUTPUT[i]	= reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_output_PGM[i + ARDUINO_PORT_INDEX_CORRECTION]));
		ARDUINO_PORT_TO_INPUT[i]	= reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_input_PGM[i + ARDUINO_PORT_INDEX_CORRECTION]));
	}
}

INLINE VOID _InitializeArduinoPinTables()
{
	for (SIZE i = 0; i < NUM_DIGITAL_PINS; i++)
	{
		ARDUINO_PIN_TO_PORT[i] = pgm_read_byte(&digital_pin_to_port_PGM[i]) - ARDUINO_PORT_INDEX_CORRECTION;
		ARDUINO_PIN_TO_MASK[i] = pgm_read_byte(&digital_pin_to_bit_mask_PGM[i]);
	}
}


namespace IttyBitty
{
	INLINE VOID InitGPIO()
	{
		_InitializeArduinoPortTables();
		_InitializeArduinoPinTables();
	}


	// ARDUINO PIN GLOBAL FUNCTIONS
	
	PinMode GetPinMode(PIN_NUMBER);
	VOID SetPinMode(PIN_NUMBER, PinMode = PinMode::CurrentSink);
	VOID SetPinMode(PIN_NUMBER, PinModeBasic = PinModeBasic::Output);
	VOID SetPinMode(PIN_NUMBER, RCBYTE = OUTPUT);

	CBIT CheckPinSet(PIN_NUMBER);
	CBIT CheckPinUnset(PIN_NUMBER);
	
	CBIT (*ReadPin)(PIN_NUMBER) = &CheckPinSet;
	CBIT (*CheckPin)(PIN_NUMBER) = &CheckPinSet;
	
	VOID WritePin(PIN_NUMBER, RCBIT = HIGH);
	VOID SetPin(PIN_NUMBER);
	VOID ClearPin(PIN_NUMBER);
	VOID TogglePin(PIN_NUMBER);
	
	VOID ResetPin(PIN_NUMBER);
};


#define ARDUINO_PIN_MODE_REF(arduino_pin)		(*ARDUINO_PORT_TO_MODE[ARDUINO_PIN_TO_PORT[arduino_pin]])
#define ARDUINO_PIN_OUT_REF(arduino_pin)		(*ARDUINO_PORT_TO_OUTPUT[ARDUINO_PIN_TO_PORT[arduino_pin]])
#define ARDUINO_PIN_IN_REF(arduino_pin)			(*ARDUINO_PORT_TO_INPUT[ARDUINO_PIN_TO_PORT[arduino_pin]])

#define CHECK_ARDUINO_PIN_SET(arduino_pin)		CHECK_BITS_SET(ARDUINO_PIN_IN_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin])
#define READ_ARDUINO_PIN(arduino_pin)			CHECK_ARDUINO_PIN_SET(arduino_pin)
#define CHECK_ARDUINO_PIN(arduino_pin)			CHECK_ARDUINO_PIN_SET(arduino_pin)
#define CHECK_ARDUINO_PIN_UNSET(arduino_pin)	CHECK_BITS_UNSET(ARDUINO_PIN_IN_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin])

#define WRITE_ARDUINO_PIN(arduino_pin, state)	(state ? SET_ARDUINO_PIN(arduino_pin) : CLEAR_ARDUINO_PIN(arduino_pin))
#define SET_ARDUINO_PIN(arduino_pin)			SET_BITS(ARDUINO_PIN_OUT_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin])
#define CLEAR_ARDUINO_PIN(arduino_pin)			CLEAR_BITS(ARDUINO_PIN_OUT_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin])
#define TOGGLE_ARDUINO_PIN(arduino_pin)			TOGGLE_BITS(ARDUINO_PIN_IN_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin])

#define RESET_ARDUINO_PIN(arduino_pin)  \
	SET_BIT(ARDUINO_PIN_OUT_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]);	\
	SET_BIT(ARDUINO_PIN_MODE_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]);	\
	CLEAR_BIT(ARDUINO_PIN_OUT_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]);	\
	CLEAR_BIT(ARDUINO_PIN_MODE_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin])

#define GET_ARDUINO_PIN_MODE(arduino_pin)	\
	(IttyBitty::PinMode)(CHECK_SET(ARDUINO_PIN_MODE_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]) OR	\
		CHECK_SET(ARDUINO_PIN_OUT_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]) SHL 0b1)

#define SET_ARDUINO_PIN_MODE(arduino_pin, mode)	\
	if (MASK((BYTE)(IttyBitty::PinMode)mode, OUTPUT)) SET_PIN(ARDUINO_PIN_MODE_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]);	\
		else CLEAR_PIN(ARDUINO_PIN_MODE_REF(arduino_pin), ARDUINO_PIN_TO_MASK[arduino_pin]);										\
	if (MASK((BYTE)(IttyBitty::PinMode)mode, INPUT_PULLUP)) SET_ARDUINO_PIN(arduino_pin); else CLEAR_ARDUINO_PIN(arduino_pin)


#endif
