/***********************************************************************************************
* [IttyBitty_GPIO.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_GPIO_H
#define _ITTYBITTY_GPIO_H


#include "IttyBitty_registers.h"


#pragma region DEFINES

#define TRISTATE_INPUT INPUT

#define	L	LOW		// I/O low state; 0x0
#define H	HIGH	// I/O high state; 0x1

#define HIGH_Z			0x0		// (Tri-state) input high impedance / disconnected state
#define DISCONNECTED	HIGH_Z

#pragma endregion


#ifdef NO_ITTYBITTY_BYTES
	#include "IttyBitty_bits.h"
#endif


#pragma region GLOBAL TYPEDEFS

typedef CSIZE PIN_NUMBER;

#pragma endregion


namespace IttyBitty
{
#pragma region ENUMS

	ENUM PinMode : BYTE
	{
		// Input mode states
		TriStateInput	= 0x0,	// 00b; PinModeBasic::Input OR HIGH_Z << PinModeBasic::Input
		BinaryInput		= 0x2,	// 10b; PinModeBasic::Input OR INPUT_PULLUP << PinModeBasic::Input

		// Output mode states
		CurrentSink		= 0x1,	// 01b; PinModeBasic::Output OR LOW << PinModeBasic::Output
		CurrentSource	= 0x3,	// 11b; PinModeBasic::Output OR HIGH << PinModeBasic::Output
	};

	TYPEDEF_ENUM_ALIASES(PinMode, PINMODE);


	ENUM PinModeBasic : BYTE
	{
		Input	= INPUT,
		Output	= OUTPUT,
		PullUp	= INPUT_PULLUP
	};

	TYPEDEF_ENUM_ALIASES(PinModeBasic, PINMODEBASIC);

#pragma endregion
}


#ifndef NO_ITTYBITTY_BYTES

namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	struct _PortRegisters;
	typedef struct _PortRegisters PortReg;
	TYPEDEF_STRUCT_ALIASES(PortRegisters, portregisters, PORTREG);

	struct _Port;
	TYPEDEF_STRUCT_ALIASES(Port, port, PORT);

	struct _GPIO;
	TYPEDEF_SINGLETON_STRUCT_ALIASES(GPIO, GPIO);


	#define _PIN_T_CLAUSE_DEF	<PIN_NUMBER PinNum, PPORT PortPtr>
	#define _PIN_T_CLAUSE		<PIN_NUMBER PinNum = 0x0, PPORT PortPtr = NULL>
	#define _PIN_T_ARGS			<PinNum, PortPtr>

	template _PIN_T_CLAUSE
	struct _Pin;
	TEMPLATE_STRUCT_USING_ALIASES(CSL(_PIN_T_CLAUSE), CSL(_PIN_T_ARGS), Pin, pin, PIN);

#pragma endregion


#pragma region [_PortRegisters] DEFINITION

	STRUCT _PortRegisters
	{
	private:

		_PortRegisters() : DirectionReg(ByteField::NULL_OBJECT()),
			OutputReg(ByteField::NULL_OBJECT()), InputReg(ByteField::NULL_OBJECT()) { }


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

#pragma endregion


#pragma region [_Port] DEFINITION

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

		VIRTUAL INLINE BIT operator[](PIN_NUMBER p) const ALWAYS_INLINE
		{
			return this->CheckPinSet(p);
		}

		VIRTUAL INLINE BITREF operator[](PIN_NUMBER p) ALWAYS_INLINE
		{
			return this->PinState(p);
		}

		VIRTUAL CPINMODE GetPinMode(PIN_NUMBER p) const
		{
			return (CPINMODE)((BIT)_Registers->DirectionReg[p] OR (BIT)_Registers->OutputReg[p] SHL 0b1);
		}

		VIRTUAL VOID SetPinMode(PIN_NUMBER p, CPINMODE mode = PinMode::CurrentSink)
		{
			_Registers->DirectionReg[p]	= MASK((BYTE)mode, OUTPUT);
			_Registers->OutputReg[p]	= MASK((BYTE)mode, INPUT_PULLUP);
		}

		VIRTUAL VOID SetPinMode(PIN_NUMBER p, CPINMODEBASIC basicMode = PinModeBasic::Output)
		{
			this->SetPinMode(p, (PinMode)basicMode);
		}

		VIRTUAL VOID SetPinMode(PIN_NUMBER p, CBYTE arduinoMode = OUTPUT)
		{
			this->SetPinMode(p, (PinModeBasic)arduinoMode);
		}

		VIRTUAL CBIT CheckPinSet(PIN_NUMBER p) const
		{
			return _Registers->InputReg[p];
		}

		VIRTUAL INLINE CBIT ReadPin(PIN_NUMBER p) const ALWAYS_INLINE
		{
			return this->CheckPinSet(p);
		}

		VIRTUAL INLINE CBIT CheckPin(PIN_NUMBER p) const ALWAYS_INLINE
		{
			return this->CheckPinSet(p);
		}

		VIRTUAL INLINE CBIT CheckPinUnset(PIN_NUMBER p) const ALWAYS_INLINE
		{
			return NOT this->CheckPinSet(p);
		}

		VIRTUAL BITREF PinState(PIN_NUMBER p)
		{
			return _Registers->OutputReg[p];
		}

		VIRTUAL VOID WritePin(PIN_NUMBER p, CBIT state = HIGH)
		{
			_Registers->OutputReg[p] = state;
		}

		VIRTUAL INLINE VOID SetPin(PIN_NUMBER p) ALWAYS_INLINE
		{
			this->WritePin(p, HIGH);
		}

		VIRTUAL INLINE VOID ClearPin(PIN_NUMBER p) ALWAYS_INLINE
		{
			this->WritePin(p, LOW);
		}

		VIRTUAL VOID TogglePin(PIN_NUMBER p)
		{
			_Registers->InputReg[p] = !_Registers->InputReg[p];
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

#pragma endregion


#pragma region [_Pin] DEFINITION

	template _PIN_T_CLAUSE_DEF
	STRUCT _Pin
	{
	public:

		_Pin() { }

		VIRTUAL ~_Pin() { }

		STATIC CPINMODE GetMode()
		{
			return PortPtr->GetPinMode(PinNum);
		}

		STATIC VOID SetMode(CPINMODE mode)
		{
			PortPtr->SetPinMode(PinNum, mode);
		}

		STATIC VOID SetMode(CPINMODEBASIC basicMode)
		{
			PortPtr->SetPinMode(PinNum, basicMode);
		}

		STATIC VOID SetMode(CBYTE arduinoMode)
		{
			PortPtr->SetPinMode(PinNum, (CPINMODEBASIC)arduinoMode);
		}

		STATIC CBIT CheckSet()
		{
			return PortPtr->CheckPinSet(PinNum);
		}

		STATIC CBIT Read() ALIAS(CheckSet);
		STATIC CBIT Check() ALIAS(CheckSet);

		STATIC CBIT CheckUnset()
		{
			return PortPtr->CheckPinUnset(PinNum);
		}

		STATIC VOID Write(CBIT state = HIGH)
		{
			return PortPtr->WritePin(PinNum, state);
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

#pragma endregion
}


#pragma region PORT-SPECIFIC STRUCTURE DECLARATION MACROS

	#define _DECLARE_PORT_STRUCTS(port_letter)	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_DDR;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PORT;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PIN;	\
		EXTERN IttyBitty::REG8 DDR##port_letter##_REG;		\
		EXTERN IttyBitty::REG8 PORT##port_letter##_REG;		\
		EXTERN IttyBitty::REG8 PIN##port_letter##_REG;		\
		EXTERN IttyBitty::PORT Port##port_letter;

#else	// #ifdef NO_ITTYBITTY_BYTES

	#include "IttyBitty_bits.h"


	#define _DECLARE_PORT_STRUCTS(port_letter)	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_DDR;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PORT;	\
		EXTERN IttyBitty::RBITPACK P##port_letter##_PIN;

#endif

#pragma endregion


#pragma region PORT-SPECIFIC STRUCTURE GLOBAL VARIABLE DECLARATION CALLS

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

#pragma endregion


#ifndef NO_ITTYBITTY_BYTES

namespace IttyBitty
{
#pragma region PIN STRUCTURE GLOBAL VARIABLE TYPEDEF MACRO & PORT-SPECIFIC CALLS

	#define _TYPEDEF_PINS(port_letter)				\
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

#pragma endregion


#pragma region [_GPIO] SINGLETON STRUCT / MODULE DEFINITION (w/ PORT-SPECIFIC STRUCTURE / PIN TYPEDEF MACROS & PORT-SPECIFIC CALLS)

	#define _GPIO_DECLARE_PORT_STRUCTS(port_letter) STATIC RPORT P##port_letter;

	#define _GPIO_TYPEDEF_PINS(port_letter)				\
		typedef PIN<0, &Port##port_letter> Pin##port_letter##0;	\
		typedef PIN<1, &Port##port_letter> Pin##port_letter##1;	\
		typedef PIN<2, &Port##port_letter> Pin##port_letter##2;	\
		typedef PIN<3, &Port##port_letter> Pin##port_letter##3;	\
		typedef PIN<4, &Port##port_letter> Pin##port_letter##4;	\
		typedef PIN<5, &Port##port_letter> Pin##port_letter##5;	\
		typedef PIN<6, &Port##port_letter> Pin##port_letter##6;	\
		typedef PIN<7, &Port##port_letter> Pin##port_letter##7;


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
		_GPIO_TYPEDEF_PINS(B)
	#endif

	#ifdef PORTC
		_GPIO_DECLARE_PORT_STRUCTS(C)
		_GPIO_TYPEDEF_PINS(C)
	#endif

	#ifdef PORTD
		_GPIO_DECLARE_PORT_STRUCTS(D)
		_GPIO_TYPEDEF_PINS(D)
	#endif

	#ifdef PORTE
		_GPIO_DECLARE_PORT_STRUCTS(E)
		_GPIO_TYPEDEF_PINS(E)
	#endif

	#ifdef PORTF
		_GPIO_DECLARE_PORT_STRUCTS(F)
		_GPIO_TYPEDEF_PINS(F)
	#endif

	#ifdef PORTG
		_GPIO_DECLARE_PORT_STRUCTS(G)
		_GPIO_TYPEDEF_PINS(G)
	#endif

	#ifdef PORTH
		_GPIO_DECLARE_PORT_STRUCTS(H)
		_GPIO_TYPEDEF_PINS(H)
	#endif

	#ifdef PORTJ
		_GPIO_DECLARE_PORT_STRUCTS(J)
		_GPIO_TYPEDEF_PINS(J)
	#endif

	#ifdef PORTK
		_GPIO_DECLARE_PORT_STRUCTS(K)
		_GPIO_TYPEDEF_PINS(K)
	#endif

	#ifdef PORTL
		_GPIO_DECLARE_PORT_STRUCTS(L)
		_GPIO_TYPEDEF_PINS(L)
	#endif
	};
}

#endif	// #ifndef NO_ITTYBITTY_BYTES


#include "IttyBitty_GPIO_arduino.h"


#include "IttyBitty_GPIO_portpins.h"


#endif
