/**********************************************************************************
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_registers.h"


#define TRISTATE_INPUT INPUT

#define L LOW		// I/O low state; 0x0
#define H HIGH		// I/O high state; 0x1

#define HIGH_Z 0x0	// (Tri-state) input high impedance / disconnected state
#define DISCONNECTED HIGH_Z


#ifdef EXCLUDE_ITTYBITTY_BYTES

#include "IttyBitty_bits.h"

#endif


namespace IttyBitty
{
	ENUM PinModeBasic : BYTE
	{
		Input	= INPUT,
		Output	= OUTPUT,
		PullUp	= INPUT_PULLUP
	};

	ENUM PinMode : BYTE
	{
		// Input mode states
		TriStateInput	= 0x0,	// 00b; PinModeBasic::Input OR HIGH_Z << PinModeBasic::Input
		BinaryInput		= 0x2,	// 10b; PinModeBasic::Input OR INPUT_PULLUP << PinModeBasic::Input

		// Output mode states
		CurrentSink		= 0x1,	// 01b; PinModeBasic::Output OR LOW << PinModeBasic::Output
		CurrentSource	= 0x3,	// 11b; PinModeBasic::Output OR HIGH << PinModeBasic::Output
	};
}


#ifndef EXCLUDE_ITTYBITTY_BYTES


namespace IttyBitty
{
	typedef SIZE PIN_NUMBER;

	struct _PortRegisters;
	typedef struct _PortRegisters _portregisters_t, PortReg, PORTREG, * PPORTREG, & RPORTREG, ** PPPORTREG, && RRPORTREG;
	typedef const struct _PortRegisters CPORTREG, * PCPORTREG, & RCPORTREG, ** PPCPORTREG;

	struct _Port;
	typedef struct _Port _port_t, Port, PORT, * PPORT, & RPORT, ** PPPORT, && RRPORT;
	typedef const struct _Port CPORT, * PCPORT, & RCPORT, ** PPCPORT;
	
	struct _GPIO;
	typedef _GPIO _gpio_t, GPIO, * PGPIO, & RGPIO, ** PPGPIO, && RRGPIO;
	typedef const _GPIO CGPIO, * PCGPIO, & RCGPIO, ** PPCGPIO;


	STRUCT _PortRegisters
	{
	private:

		_PortRegisters()  : DirectionReg(ByteField::NULL_OBJECT()), OutputReg(ByteField::NULL_OBJECT()), InputReg(ByteField::NULL_OBJECT()) { }


	public:

		_PortRegisters(RREG8 directionReg, RREG8 outputReg, RREG8 inputReg) 
			: DirectionReg(directionReg), OutputReg(outputReg), InputReg(inputReg) { }

		_PortRegisters(RVBYTE directionRegAddr, RVBYTE outputRegAddr, RVBYTE inputRegAddr) 
		{
			this->DirectionReg	= ByteField((RBYTE)directionRegAddr);
			this->OutputReg 	= ByteField((RBYTE)outputRegAddr);
			this->InputReg		= ByteField((RBYTE)inputRegAddr);
		}

		_PortRegisters(RCPORTREG other)  : DirectionReg(other.DirectionReg), OutputReg(other.OutputReg), InputReg(other.InputReg) { }

		VIRTUAL ~_PortRegisters() { }

		STATIC RPORTREG NULL_OBJECT()
		{
			STATIC PORTREG NULL_PORTREG = _PortRegisters();
			return NULL_PORTREG;
		}

		VIRTUAL RPORTREG operator=(RCPORTREG other) 
		{
			this->DirectionReg	= ByteField(other.DirectionReg);
			this->OutputReg 	= ByteField(other.OutputReg);
			this->InputReg		= ByteField(other.InputReg);

			return *this;
		}


		RREG8 DirectionReg	= ByteField::NULL_OBJECT();
		RREG8 OutputReg 	= ByteField::NULL_OBJECT();
		RREG8 InputReg		= ByteField::NULL_OBJECT();
	};


	STRUCT _Port
	{
	public:	

		_Port() : Registers(PortReg::NULL_OBJECT()) { }
		
		_Port(RREG8 directionReg, RREG8 outputReg, RREG8 inputReg) 
		{
			 this->Registers = PortReg(directionReg, outputReg, inputReg);
		}

		_Port(RVBYTE directionRegAddr, RVBYTE outputRegAddr, RVBYTE inputRegAddr) 
		{
			 this->Registers = PortReg(directionRegAddr, outputRegAddr, inputRegAddr);
		}

		_Port(RCPORT other)
		{
			this->Registers = other.Registers;
		}

		VIRTUAL ~_Port() { }

		STATIC RPORT NULL_OBJECT()
		{
			STATIC PORT NULL_PORT = _Port();
			return NULL_PORT;
		}

		VIRTUAL RPORT operator=(RCPORT other) 
		{
			this->Registers = other.Registers;

			return *this;
		}

		VIRTUAL BIT operator[](PIN_NUMBER p) const
		{
			return this->CheckPin(p);
		}

		VIRTUAL BITREF operator[](PIN_NUMBER p)
		{
			return this->PinState(p);
		}

		VIRTUAL PinMode GetPinMode(PIN_NUMBER p) const
		{
			return (PinMode)((BIT)Registers.DirectionReg[p] OR (BIT)Registers.OutputReg[p] SHL 1);
		}

		VIRTUAL VOID SetPinMode(PIN_NUMBER p, PinMode mode = PinMode::CurrentSink)
		{
			Registers.DirectionReg[p]	= MASK((BYTE)mode, OUTPUT);
			Registers.OutputReg[p]		= MASK((BYTE)mode, INPUT_PULLUP);
		}

		VIRTUAL VOID SetPinModeBasic(PIN_NUMBER p, PinModeBasic basicMode = PinModeBasic::Output)
		{
			this->SetPinMode(p, (PinMode)basicMode);
		}

		VIRTUAL BIT CheckPin(PIN_NUMBER p) const
		{
			return Registers.InputReg[p];
		}

		VIRTUAL BIT CheckPinSet(PIN_NUMBER p) const
		{
			return Registers.InputReg[p];
		}

		VIRTUAL BIT CheckPinUnset(PIN_NUMBER p) const
		{
			return ~Registers.InputReg[p];
		}

		VIRTUAL BITREF PinState(PIN_NUMBER p) const
		{
			return Registers.OutputReg[p];
		}

		VIRTUAL VOID SetPin(PIN_NUMBER p)
		{
			Registers.OutputReg[p] = 1;
		}

		VIRTUAL VOID ResetPin(PIN_NUMBER p)
		{
			Registers.OutputReg[p] = 0;
		}
		

	protected:

		RPORTREG Registers = PortReg::NULL_OBJECT();
	};

	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	struct _Pin;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using _pin_t = struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using Pin = struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using PIN = struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using PPIN = struct _Pin<pin_number, port> *;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using RPIN = struct _Pin<pin_number, port> &;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using PPPIN = struct _Pin<pin_number, port> **;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using RRPIN = struct _Pin<pin_number, port> &&;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using CPIN = const struct _Pin<pin_number, port>;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using PCPIN = const struct _Pin<pin_number, port> *;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using RCPIN = const struct _Pin<pin_number, port> &;
	template<PIN_NUMBER pin_number = 0x0, PPORT port = NULL>
	using PPCPIN = const struct _Pin<pin_number, port> **;


	template<PIN_NUMBER pin_number, PPORT port>
	STRUCT _Pin
	{
	public:

		_Pin() { }

		VIRTUAL ~_Pin() { }

		STATIC PinMode Mode()
		{
			return port->GetPinMode(pin_number);
		}

		STATIC VOID Mode(PinMode mode)
		{
			port->SetPinMode(pin_number, mode);
		}

		STATIC VOID BasicMode(PinModeBasic basicMode)
		{
			port->SetPinModeBasic(pin_number, basicMode);
		}

		STATIC BIT Read()
		{
			return port->CheckPin(pin_number);
		}

		STATIC BIT CheckSet()
		{
			return port->CheckPinSet(pin_number);
		}

		STATIC BIT CheckUnset()
		{
			return port->CheckPinUnset(pin_number);
		}

		STATIC VOID Set()
		{
			return port->SetPin(pin_number);
		}

		STATIC VOID Reset()
		{
			return port->ResetPin(pin_number);
		}

		STATIC VOID Clear()
		{
			return port->ResetPin(pin_number);
		}
	};
	
	
	#define _GPIO_DECLARE_PORT_STRUCTS(port_letter) STATIC RPORT P##port_letter;

	STRUCT _GPIO FINAL
	{
	private:
		
		_GPIO() { }


	public:

		~_GPIO() { }

		STATIC RCGPIO Instance()
		{
			STATIC GPIO INSTANCE = _GPIO();
			return INSTANCE;
		}
	

	#ifdef PORTA
		_GPIO_DECLARE_PORT_STRUCTS(A)
	#endif

	#ifdef PORTB
		_GPIO_DECLARE_PORT_STRUCTS(B)
	#endif

	#ifdef PORTC
		_GPIO_DECLARE_PORT_STRUCTS(C)
	#endif

	#ifdef PORTD
		_GPIO_DECLARE_PORT_STRUCTS(D)
	#endif

	#ifdef PORTE
		_GPIO_DECLARE_PORT_STRUCTS(E)
	#endif

	#ifdef PORTF
		_GPIO_DECLARE_PORT_STRUCTS(F)
	#endif

	#ifdef PORTG
		_GPIO_DECLARE_PORT_STRUCTS(G)
	#endif

	#ifdef PORTH
		_GPIO_DECLARE_PORT_STRUCTS(H)
	#endif
	};
}


	#define _DECLARE_PORT_STRUCTS(port_letter) EXTERN IttyBitty::PORT Port##port_letter;


#else	// #ifdef EXCLUDE_ITTYBITTY_BYTES


	#include "IttyBitty_bits.h"


	#define _DECLARE_PORT_STRUCTS(port_letter) EXTERN IttyBitty::RBITPACK P##port_letter##_DDR; \
		EXTERN IttyBitty::RBITPACK P##port_letter##_PORT; \
		EXTERN IttyBitty::RBITPACK P##port_letter##_PIN;


#endif


#ifdef PORTA
		
	CSIZE __DUMMY_PORTA = __COUNTER__;

	_DECLARE_PORT_STRUCTS(A)

#endif

#ifdef PORTB
		
	CSIZE __DUMMY_PORTB = __COUNTER__;
	
	_DECLARE_PORT_STRUCTS(B)

#endif

#ifdef PORTC
		
	CSIZE __DUMMY_PORTC = __COUNTER__;

	_DECLARE_PORT_STRUCTS(C)

#endif

#ifdef PORTD
		
	CSIZE __DUMMY_PORTD = __COUNTER__;

	_DECLARE_PORT_STRUCTS(D)

#endif

#ifdef PORTE
		
	CSIZE __DUMMY_PORTE = __COUNTER__;

	_DECLARE_PORT_STRUCTS(E)

#endif

#ifdef PORTF
		
	CSIZE __DUMMY_PORTF = __COUNTER__;

	_DECLARE_PORT_STRUCTS(F)

#endif

#ifdef PORTG
		
	CSIZE __DUMMY_PORTG = __COUNTER__;

	_DECLARE_PORT_STRUCTS(G)

#endif

#ifdef PORTH
		
	CSIZE __DUMMY_PORTH = __COUNTER__;

	_DECLARE_PORT_STRUCTS(H)

#endif


#ifndef EXCLUDE_ITTYBITTY_BYTES

	#define _TYPEDEF_PINS(port_letter) typedef IttyBitty::PIN<0, &Port##port_letter> Pin##port_letter##1; \
		typedef IttyBitty::PIN<1, &Port##port_letter> Pin##port_letter##2; \
		typedef IttyBitty::PIN<2, &Port##port_letter> Pin##port_letter##3; \
		typedef IttyBitty::PIN<3, &Port##port_letter> Pin##port_letter##4; \
		typedef IttyBitty::PIN<4, &Port##port_letter> Pin##port_letter##5; \
		typedef IttyBitty::PIN<5, &Port##port_letter> Pin##port_letter##6; \
		typedef IttyBitty::PIN<6, &Port##port_letter> Pin##port_letter##7; \
		typedef IttyBitty::PIN<7, &Port##port_letter> Pin##port_letter##8;

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

#endif	// #ifdef EXCLUDE_ITTYBITTY_BYTES


namespace std
{
}


CSIZE _PORT_ARRAY_SIZE = CAPACITY(port_to_mode_PGM);
CSIZE NUM_PORTS = __COUNTER__;

EXTERN PVBYTE DDR_PORTS[_PORT_ARRAY_SIZE];
EXTERN PVBYTE OUT_PORTS[_PORT_ARRAY_SIZE];
EXTERN PVBYTE PIN_PORTS[_PORT_ARRAY_SIZE];

EXTERN SIZE ARDUINO_PIN_TO_PORT[NUM_DIGITAL_PINS];
EXTERN BYTE ARDUINO_PIN_TO_MASK[NUM_DIGITAL_PINS];


INLINE VOID _InitializePortTables()
{
	// reinterpret_cast<PVBYTE>(pgm_read_byte(&port_to_mode_PGM[2]))
}

INLINE VOID _InitializeArduinoPinTables()
{

}


#define SET_ARDUINO_PIN(arduino_pin) 


#define PIN_REF(port_ref, pin_number) reinterpret_cast<PVBYTE>(port_ref)[pin_number]

#define PORT_PIN_PAIR(port_ref, pin_number) port_ref, pin_number	// NOTE: For use with XXXXXX_PAIR bit manipulation macros

#define CHECK_PIN(port_ref, pin_number) CHECK_SET(port_ref, pin_number)
#define CHECK_PIN_SET(port_ref, pin_number) CHECK_PIN(port_ref, pin_number)
#define CHECK_PIN_UNSET(port_ref, pin_number) CHECK_UNSET(port_ref, pin_number)

#define SET_PIN(port_ref, pin_number) SET_BIT(port_ref, pin_number)
#define CLEAR_PIN(port_ref, pin_number) CLEAR_BIT(port_ref, pin_number)
#define TOGGLE_PIN(port_ref, pin_number) TOGGLE_BIT(port_ref, pin_number)

#define PIN_IN_CHECK(port_letter, pin_number) CHECK_SET(PIN##port_letter, pin_number)
#define PIN_IN_CHECK_SET(port_letter, pin_number) PIN_IN(PIN##port_letter, pin_number)
#define PIN_IN_CHECK_UNSET(port_letter, pin_number) CHECK_UNSET(PIN##port_letter, pin_number)

#define PIN_OUT_SET(port_letter, pin_number) SET_BIT(PORT##port_letter, pin_number)
#define PIN_OUT_CLEAR(port_letter, pin_number) CLEAR_BIT(PORT##port_letter, pin_number)
#define PIN_OUT_TOGGLE(port_letter, pin_number) TOGGLE_BIT(PORT##port_letter, pin_number)

#define PIN_GET_MODE(port_letter, pin_number) ((PinMode)(CHECK_SET(DDR##port_letter, pin_number) OR CHECK_SET(PORT##port_letter, pin_number) SHL 1))
#define PIN_SET_MODE(port_letter, pin_number, mode) \
	if (MASK((BYTE)(IttyBitty::PinMode)mode, OUTPUT)) SET_PIN(DDR##port_letter, pin_number) else CLEAR_PIN(DDR##port_letter, pin_number); \
	if (MASK((BYTE)(IttyBitty::PinMode)mode, INPUT_PULLUP)) SET_PIN(POR##port_letter, pin_number) else CLEAR_PIN(POR##port_letter, pin_number);


#include "IttyBitty_gpio_portpins.h"


#endif
