/***********************************************************************************************
* [IttyBitty_gpio.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H


#include "IttyBitty_registers.h"


#define TRISTATE_INPUT INPUT

#define	L	LOW		// I/O low state; 0x0
#define H	HIGH	// I/O high state; 0x1

#define HIGH_Z			0x0		// (Tri-state) input high impedance / disconnected state
#define DISCONNECTED	HIGH_Z


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

		_PortRegisters() : DirectionReg(ByteField::NULL_OBJECT()), OutputReg(ByteField::NULL_OBJECT()), InputReg(ByteField::NULL_OBJECT()) { }


	public:

		EXPLICIT _PortRegisters(RREG8 directionReg, RREG8 outputReg, RREG8 inputReg)
			: DirectionReg(directionReg), OutputReg(outputReg), InputReg(inputReg) { }

		EXPLICIT _PortRegisters(PREG8 directionReg, PREG8 outputReg, PREG8 inputReg)
			: DirectionReg(*directionReg), OutputReg(*outputReg), InputReg(*inputReg) { }

		_PortRegisters(PVBYTE directionRegAddr, PVBYTE outputRegAddr, PVBYTE inputRegAddr)
		{
			this->DirectionReg	= REG8(directionRegAddr);
			this->OutputReg 	= REG8(outputRegAddr);
			this->InputReg		= REG8(inputRegAddr);
		}

		_PortRegisters(RCPORTREG other)
		{
			this->~_PortRegisters();
			new (this) _PortRegisters((RREG8)other.DirectionReg, (RREG8)other.OutputReg, (RREG8)other.InputReg);
		}

		VIRTUAL ~_PortRegisters() { }

		STATIC RPORTREG NULL_OBJECT()
		{
			STATIC PORTREG NULL_PORTREG = _PortRegisters();
			return NULL_PORTREG;
		}

		VIRTUAL RPORTREG operator=(RCPORTREG other)
		{
			*this = _PortRegisters(other);
			return *this;
		}


		RREG8 DirectionReg	= REG8::NULL_OBJECT();
		RREG8 OutputReg		= REG8::NULL_OBJECT();
		RREG8 InputReg		= REG8::NULL_OBJECT();
	};


	STRUCT _Port
	{
	public:

		_Port() : _Registers(NULL) { }

		EXPLICIT _Port(RREG8 directionReg, RREG8 outputReg, RREG8 inputReg)
		{
			 _Registers = new PortReg(directionReg, outputReg, inputReg);
		}

		_Port(PVBYTE directionRegAddr, PVBYTE outputRegAddr, PVBYTE inputRegAddr)
		{
			_Registers = new PortReg(directionRegAddr, outputRegAddr, inputRegAddr);
		}

		_Port(RCPORT other)
		{
			this->~_Port();
			_Registers = new PortReg(*other._Registers);
		}

		VIRTUAL ~_Port()
		{
			delete _Registers;
		}

		STATIC RPORT NULL_OBJECT()
		{
			STATIC PORT NULL_PORT = _Port();
			return NULL_PORT;
		}

		VIRTUAL RPORT operator=(RCPORT other)
		{
			*this = _Port(other);
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
			return (PinMode)((BIT)_Registers->DirectionReg[p] OR (BIT)_Registers->OutputReg[p] SHL 1);
		}

		VIRTUAL VOID SetPinMode(PIN_NUMBER p, PinMode mode = PinMode::CurrentSink)
		{
			_Registers->DirectionReg[p]	= MASK((BYTE)mode, OUTPUT);
			_Registers->OutputReg[p]	= MASK((BYTE)mode, INPUT_PULLUP);
		}

		VIRTUAL VOID SetPinModeBasic(PIN_NUMBER p, PinModeBasic basicMode = PinModeBasic::Output)
		{
			this->SetPinMode(p, (PinMode)basicMode);
		}

		VIRTUAL BIT CheckPin(PIN_NUMBER p) const
		{
			return _Registers->InputReg[p];
		}

		VIRTUAL BIT CheckPinSet(PIN_NUMBER p) const
		{
			return _Registers->InputReg[p];
		}

		VIRTUAL BIT CheckPinUnset(PIN_NUMBER p) const
		{
			return ~_Registers->InputReg[p];
		}

		VIRTUAL BITREF PinState(PIN_NUMBER p)
		{
			return _Registers->OutputReg[p];
		}

		VIRTUAL VOID SetPin(PIN_NUMBER p)
		{
			_Registers->OutputReg[p] = 1;
		}

		VIRTUAL VOID ClearPin(PIN_NUMBER p)
		{
			_Registers->OutputReg[p] = 0;
		}

		VIRTUAL VOID TogglePin(PIN_NUMBER p)
		{
			_Registers->InputReg[p] = !this->CheckPin(p);
		}

		VIRTUAL VOID ResetPin(PIN_NUMBER p)
		{
			_Registers->OutputReg[p]	= 1;
			_Registers->DirectionReg[p]	= 1;
			_Registers->OutputReg[p]	= 0;
			_Registers->DirectionReg[p]	= 0;
		}


	protected:

		PPORTREG _Registers = NULL;
	};

	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	struct _Pin;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using _pin_t = struct _Pin<PinNum, PortPtr>;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using Pin = struct _Pin<PinNum, PortPtr>;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using PIN = struct _Pin<PinNum, PortPtr>;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using PPIN = struct _Pin<PinNum, PortPtr> *;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using RPIN = struct _Pin<PinNum, PortPtr> &;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using PPPIN = struct _Pin<PinNum, PortPtr> **;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using RRPIN = struct _Pin<PinNum, PortPtr> &&;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using CPIN = const struct _Pin<PinNum, PortPtr>;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using PCPIN = const struct _Pin<PinNum, PortPtr> *;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using RCPIN = const struct _Pin<PinNum, PortPtr> &;
	template<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	using PPCPIN = const struct _Pin<PinNum, PortPtr> **;


	template<PIN_NUMBER PinNum, PPORT PortPtr>
	STRUCT _Pin
	{
	public:

		_Pin() { }

		VIRTUAL ~_Pin() { }

		STATIC PinMode Mode()
		{
			return PortPtr->GetPinMode(PinNum);
		}

		STATIC VOID Mode(PinMode mode)
		{
			PortPtr->SetPinMode(PinNum, mode);
		}

		STATIC VOID BasicMode(PinModeBasic basicMode)
		{
			PortPtr->SetPinModeBasic(PinNum, basicMode);
		}

		STATIC BIT Read()
		{
			return PortPtr->CheckPin(PinNum);
		}

		STATIC BIT CheckSet()
		{
			return PortPtr->CheckPinSet(PinNum);
		}

		STATIC BIT CheckUnset()
		{
			return PortPtr->CheckPinUnset(PinNum);
		}

		STATIC VOID Set()
		{
			return PortPtr->SetPin(PinNum);
		}

		STATIC VOID Clear()
		{
			return PortPtr->ClearPin(PinNum);
		}

		STATIC VOID Toggle()
		{
			return PortPtr->TogglePin(PinNum);
		}

		STATIC VOID Reset()
		{
			return PortPtr->ResetPin(PinNum);
		}
	};


	#define _GPIO_DECLARE_PORT_STRUCTS(port_letter) STATIC RPORT P##port_letter;

	//#define _GPIO_TYPEDEF_PINS(port_letter)						\
	//	typedef PIN<0, &Port##port_letter> Pin##port_letter##0;	\
	//	typedef PIN<1, &Port##port_letter> Pin##port_letter##1;	\
	//	typedef PIN<2, &Port##port_letter> Pin##port_letter##2;	\
	//	typedef PIN<3, &Port##port_letter> Pin##port_letter##3;	\
	//	typedef PIN<4, &Port##port_letter> Pin##port_letter##4;	\
	//	typedef PIN<5, &Port##port_letter> Pin##port_letter##5;	\
	//	typedef PIN<6, &Port##port_letter> Pin##port_letter##6;	\
	//	typedef PIN<7, &Port##port_letter> Pin##port_letter##7;

	STRUCT _GPIO FINAL
	{
	private:

		_GPIO() { }


	public:

		~_GPIO() { }

		STATIC RCGPIO Instance()
		{
			STATIC GPIO INSTANCE;
			return INSTANCE;
		}


	#ifdef PORTA
		_GPIO_DECLARE_PORT_STRUCTS(A)
		_GPIO_TYPEDEF_PINS(A)
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

	#ifdef PORTJ
		_GPIO_DECLARE_PORT_STRUCTS(J)
	#endif

	#ifdef PORTK
		_GPIO_DECLARE_PORT_STRUCTS(K)
	#endif

	#ifdef PORTL
		_GPIO_DECLARE_PORT_STRUCTS(L)
	#endif
	};
}


	#define _DECLARE_PORT_STRUCTS(port_letter)	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_DDR;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PORT;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PIN;	\
		EXTERN IttyBitty::REG8 DDR##port_letter##_REG;		\
		EXTERN IttyBitty::REG8 PORT##port_letter##_REG;		\
		EXTERN IttyBitty::REG8 PIN##port_letter##_REG;		\
		EXTERN IttyBitty::PORT Port##port_letter;


#else	// #ifdef EXCLUDE_ITTYBITTY_BYTES


	#include "IttyBitty_bits.h"


	#define _DECLARE_PORT_STRUCTS(port_letter)	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_DDR;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PORT;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PIN;


#endif


#ifdef PORTA
	_DECLARE_PORT_STRUCTS(A)
#endif

#ifdef PORTB
	_DECLARE_PORT_STRUCTS(B)
#endif

#ifdef PORTC
	_DECLARE_PORT_STRUCTS(C)
#endif

#ifdef PORTD
	_DECLARE_PORT_STRUCTS(D)
#endif

#ifdef PORTE
	_DECLARE_PORT_STRUCTS(E)
#endif

#ifdef PORTF
	_DECLARE_PORT_STRUCTS(F)
#endif

#ifdef PORTG
	_DECLARE_PORT_STRUCTS(G)
#endif

#ifdef PORTH
	_DECLARE_PORT_STRUCTS(H)
#endif

#ifdef PORTJ
	_DECLARE_PORT_STRUCTS(J)
#endif

#ifdef PORTK
	_DECLARE_PORT_STRUCTS(K)
#endif

#ifdef PORTL
	_DECLARE_PORT_STRUCTS(L)
#endif

//
//#ifndef EXCLUDE_ITTYBITTY_BYTES
//
//	#define _TYPEDEF_PINS(port_letter)										\
//		typedef IttyBitty::PIN<0, &Port##port_letter> Pin##port_letter##0;	\
//		typedef IttyBitty::PIN<1, &Port##port_letter> Pin##port_letter##1;	\
//		typedef IttyBitty::PIN<2, &Port##port_letter> Pin##port_letter##2;	\
//		typedef IttyBitty::PIN<3, &Port##port_letter> Pin##port_letter##3;	\
//		typedef IttyBitty::PIN<4, &Port##port_letter> Pin##port_letter##4;	\
//		typedef IttyBitty::PIN<5, &Port##port_letter> Pin##port_letter##5;	\
//		typedef IttyBitty::PIN<6, &Port##port_letter> Pin##port_letter##6;	\
//		typedef IttyBitty::PIN<7, &Port##port_letter> Pin##port_letter##7;
//
//	#ifdef PORTA
//		_TYPEDEF_PINS(A)
//	#endif
//
//	#ifdef PORTB
//		_TYPEDEF_PINS(B)
//	#endif
//
//	#ifdef PORTC
//		_TYPEDEF_PINS(C)
//	#endif
//
//	#ifdef PORTD
//		_TYPEDEF_PINS(D)
//	#endif
//
//	#ifdef PORTE
//		_TYPEDEF_PINS(E)
//	#endif
//
//	#ifdef PORTF
//		_TYPEDEF_PINS(F)
//	#endif
//
//	#ifdef PORTG
//		_TYPEDEF_PINS(G)
//	#endif
//
//	#ifdef PORTH
//		_TYPEDEF_PINS(H)
//	#endif
//
//	#ifdef PORTJ
//		_TYPEDEF_PINS(J)
//	#endif
//
//	#ifdef PORTK
//		_TYPEDEF_PINS(K)
//	#endif
//
//	#ifdef PORTL
//		_TYPEDEF_PINS(L)
//	#endif
//
//#endif	// #ifdef EXCLUDE_ITTYBITTY_BYTES


#include "IttyBitty_gpio_arduino.h"


#include "IttyBitty_gpio_portpins.h"


#endif
