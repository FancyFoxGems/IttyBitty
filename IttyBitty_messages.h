/***********************************************************************************************
* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MESSAGES_H
#define _ITTYBITTY_MESSAGES_H


#include "IttyBitty_params.h"

#ifdef DEBUG_MESSAGES
	#include "IttyBitty_print.h"
#endif


/* SUPRESS COMPILER WARNINGS RELATED TO PARAM REORDERING */

IGNORE_WARNING(-Wreorder)


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

	EXTERN PCCHAR MESSAGE_MARKER;
		
	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __message_buffer;

#pragma endregion

	
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IMessage;
	typedef IMessage IMESSAGE, * PIMESSAGE, & RIMESSAGE, ** PPIMESSAGE, && RRIMESSAGE;
	typedef const IMessage CIMESSAGE, * PCIMESSAGE, & RCIMESSAGE, ** PPCIMESSAGE;

	class Message;
	typedef Message MESSAGE, * PMESSAGE, & RMESSAGE, ** PPMESSAGE, && RRMESSAGE;
	typedef const Message CMESSAGE, * PCMESSAGE, & RCMESSAGE, ** PPCMESSAGE;

	template<CBYTE MsgCode, CBYTE ParamCnt>
	class GenericMessage;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using GENERICMESSAGE = GenericMessage<MsgCode, ParamCnt>;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> *;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> &;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PPGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> **;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RRGENERICMESSAGE = GenericMessage<MsgCode, ParamCnt> &&;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using CGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt>;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PCGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt> *;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RCGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt> &;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PPCGENERICMESSAGE = const GenericMessage<MsgCode, ParamCnt> **;

#pragma endregion
	
	
#ifdef ARDUINO

#pragma region SERIAL/STREAM READING GLOBAL FUNCTION DECLARATIONS/DEFINITIONS

	CBOOL operator >(Stream & stream, PBYTE b);
	CBOOL ReadBuffer(Stream & stream, PBYTE buffer, CSIZE length = 1);

	template<typename T>
	INLINE CONST T & Read(Stream & stream, PBYTE buffer)
	{
		CBOOL result = ReadBuffer(stream, buffer, T_SIZE);
		
		STATIC T NULL_T = (T)0;
		if (!result)
			return NULL_T;

		return *((T *)buffer);
	}

#pragma endregion
	

#pragma region [Message] PARSING GLOBAL FUNCTION DECLARATIONS
	
	typedef VOID MessageHandler(PIMESSAGE), MESSAGEHANDLER(PIMESSAGE), (*PMESSAGEHANDLER)(PIMESSAGE);


	PIMESSAGE MessageFromBytes(Stream & stream);
	PIMESSAGE MessageFromString(Stream & stream);
	
	VOID WaitForMessage(Stream & stream, PMESSAGEHANDLER msgHandler);

#pragma endregion

#endif	// #ifdef ARDUINO
	

#pragma region [IMessage] DEFINITION

	INTERFACE IMessage : public ITransmittable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IMessage() { }

		// OPERATORS

		VIRTUAL PCIPARAM operator[](CBYTE) const = 0;
		VIRTUAL PIPARAM operator[](CBYTE) = 0;
		

		// ACCESSORS

		VIRTUAL CBYTE ParamCount() const = 0;

		VIRTUAL CBYTE GetMessageCode() const = 0;
		
		VIRTUAL RCIPARAM Param(CBYTE = 0) const = 0;
		VIRTUAL RIPARAM Param(CBYTE = 0) = 0;


		// INTERFACE METHODS

		VIRTUAL BOOL Handle(PVOID = NULL, PCVOID = NULL) = 0;


	protected:
		
		// HELPER METHODS

		VIRTUAL CSIZE ParamsByteSize() const = 0;
		VIRTUAL CSIZE ParamsStringSize() const = 0;


		IMessage() { }
	};

#pragma endregion
	

#pragma region [Message] DEFINITION

	CLASS Message : public IMessage
	{
	public:
		
		// CONSTRUCTORS/DESTRUCTOR

		Message(CBYTE messageCode = 0, CBYTE paramCount = 0);

		Message(RCMESSAGE);
		Message(RRMESSAGE);

		EXPLICIT Message(PCBYTE);
		EXPLICIT Message(PCCHAR);

		Message(CBYTE, RCIPARAM);
		Message(CBYTE, CBYTE, PPIPARAM);

		VIRTUAL ~Message();


	protected:
		
		// PROTECTED DISPOSAL METHOD

		VIRTUAL VOID Dispose();


	public:
		
		// OPERATORS

		VIRTUAL RMESSAGE operator=(RCMESSAGE);
		VIRTUAL RMESSAGE operator=(RRMESSAGE);

		VIRTUAL PCIPARAM operator[](CBYTE) const;
		VIRTUAL PIPARAM operator[](CBYTE);
		

		// ACCESSORS
		
		VIRTUAL CBYTE ParamCount() const;

		VIRTUAL CBYTE GetMessageCode() const;
		
		VIRTUAL RCIPARAM Param(CBYTE = 0) const;
		VIRTUAL RIPARAM Param(CBYTE = 0);


		// [IMessage] IMPLEMENTATION

		VIRTUAL BOOL Handle(PVOID = NULL, PCVOID = NULL);
		

		// [ISerializable] IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		

		// [ITransmittable] IMPLEMENTATION
		
	#ifdef ARDUINO

		VIRTUAL BOOL Transmit(HardwareSerial & = SERIAL_PORT_HARDWARE);
		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & = Wire);
		
		VIRTUAL SIZE printTo(Print &) const;

	#endif


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;
		
		BYTE _MessageCode;
		BYTE _ParamCount;

		PPIPARAM _Params;

		
		// [IMessage] HELPER METHODS

		VIRTUAL CSIZE ParamsByteSize() const;
		VIRTUAL CSIZE ParamsStringSize() const;
	};

#pragma endregion
	

#pragma region [GenericMessage] DEFINITION
	
	template<CBYTE MsgCode, CBYTE ParamCnt = 0>
	CLASS GenericMessage : public Message
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE MESSAGE_CODE()
		{
			return MsgCode;
		}

		STATIC CONSTEXPR CSIZE PARAM_COUNT()
		{
			return ParamCnt;
		}


		// CONSTRUCTORS

		GenericMessage() : Message(MsgCode, ParamCnt) { }

		GenericMessage(PIPARAM param) : Message(MsgCode, param) { }

		GenericMessage(RCIPARAM param) : Message(MsgCode, param) { }

		GenericMessage(PPIPARAM params) : Message(MsgCode, ParamCnt, params) { }


		// [Message] OVERRIDES

		VOID Handle(...) { }

		CBYTE GetMessageCode() const
		{
			return MESSAGE_CODE();
		}

		CBYTE ParamCount() const
		{
			return PARAM_COUNT();
		}
	};
	
#pragma endregion
}


#endif
