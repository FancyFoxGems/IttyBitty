/***********************************************************************************************
* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_MESSAGES_H
#define _ITTYBITTY_MESSAGES_H


#include "IttyBitty_fields.h"


/* SUPRESS COMPILER WARNINGS RELATED TO FIELD REORDERING */

IGNORE_WARNING(-Wreorder)


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES

	EXTERN CWORD SERIAL_DEFAULT_TIMEOUT_MS;

	EXTERN PCCHAR MESSAGE_MARKER;
		
	// Message::ToBytes() / ToString() BUFFER POINTER
	EXTERN PBYTE __message_buffer;

#pragma endregion

	
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IMessage;
	typedef IMessage IMESSAGE, * PIMESSAGE, & RIMESSAGE, ** PPIMESSAGE, && RRIMESSAGE;
	typedef const IMessage CIMESSAGE, *PCIMESSAGE, & RCIMESSAGE, ** PPCIMESSAGE;

	class Message;
	typedef Message MESSAGE, * PMESSAGE, & RMESSAGE, ** PPMESSAGE, && RRMESSAGE;
	typedef const Message CMESSAGE, *PCMESSAGE, & RCMESSAGE, ** PPCMESSAGE;

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
	

#pragma region IMessage DEFINITION

	INTERFACE IMessage : public virtual ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IMessage() { }

		// OPERATORS

		VIRTUAL PCIFIELD operator[](CBYTE) const = 0;
		VIRTUAL PIFIELD operator[](CBYTE) = 0;
		

		// ACCESSORS

		VIRTUAL CBYTE GetParamCount() const = 0;
		VIRTUAL CBYTE GetMessageCode() const = 0;

		VIRTUAL RIFIELD Param(CBYTE = 0) = 0;


		// USER METHODS

		VIRTUAL VOID Handle(PCVOID, PVOID) = 0;

	protected:

		VIRTUAL CSIZE GetParamsSize() const = 0;
		VIRTUAL CSIZE GetParamsStringSize() const = 0;

		IMessage() { }
	};

#pragma endregion
	

#pragma region Message DECLARATION

	CLASS Message : public virtual IMessage
	{
	public:


		// CONSTRUCTORS/DESTRUCTOR

		Message(CBYTE, CBYTE);
		Message(CBYTE, CBYTE, PIFIELD);
		Message(CBYTE, CBYTE, PPIFIELD);

		VIRTUAL ~Message();


		// OPERATORS

		VIRTUAL PCIFIELD operator[](CBYTE) const;
		VIRTUAL PIFIELD operator[](CBYTE);
		

		// ACCESSORS
		
		VIRTUAL CBYTE GetMessageCode() const;
		VIRTUAL CBYTE GetParamCount() const;

		VIRTUAL RIFIELD Param(CBYTE = 0);


		// USER METHODS

		VIRTUAL VOID Handle(PCVOID, PVOID);
		

		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE Size() const;
		VIRTUAL CSIZE ByteWidth() const;

		VIRTUAL PCBYTE ToBytes() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID LoadFromBytes(PCBYTE);
		VIRTUAL VOID LoadFromString(PCCHAR);

		VIRTUAL SIZE printTo(Print &) const;

	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;
		
		CBYTE _MessageCode;
		CBYTE _ParamCount;
		PPIFIELD _Params;
		
		// HELPER METHODS

		VIRTUAL CSIZE GetParamsSize() const;
		VIRTUAL CSIZE GetParamsStringSize() const;
	};

#pragma endregion
	

#pragma region GenericMessage DECLARATION

	template<CBYTE MsgCode, CBYTE ParamCnt = 0>
	CLASS GenericMessage : public Message, public virtual IMessage
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE MESSAGE_CODE();
		STATIC CONSTEXPR CSIZE PARAM_COUNT();


		// CONSTRUCTORS

		GenericMessage();
		GenericMessage(RIFIELD);
		GenericMessage(PIFIELD);


		// Message OVERRIDES
		
		VIRTUAL CBYTE GetMessageCode() const;
		VIRTUAL CBYTE GetParamCount() const;


	protected:

		using Message::_Dispose;
		using Message::_Params;
	};

#pragma endregion
	

#pragma region SERIAL/STREAM READING METHODS

	INLINE CBOOL operator >(Stream & stream, PBYTE b)
	{
		return stream.readBytes(b, 1);
	}

	INLINE CBOOL ReadBuffer(Stream & stream, PBYTE buffer, CSIZE length = 1)
	{
		SIZE i = length;

		while (i-- > 0)
		{
			if (!stream.available())
				delay(SERIAL_DEFAULT_TIMEOUT_MS);
				
			if (!stream.available())
				return FALSE;
				
			int result = stream.read();
			if (result < 0)
				return FALSE;

			buffer[i] = (CBYTE)result;
		}

		return TRUE;
	}

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
	

#pragma region MESSAGE PARSING METHODS
	
	typedef VOID (* MessageHandler)(PIMESSAGE);
	

	INLINE CBOOL ReadMessage(Stream & stream, PIMESSAGE message)
	{
		if (!stream.find(UNCONST(MESSAGE_MARKER)))
			return FALSE;

		SIZE msgSize = 0;
		msgSize = Read<SIZE>(stream, (PBYTE)&msgSize);
		if (msgSize == 0)
			return FALSE;

		BYTE msgCode = 0;
		if (!(stream > &msgCode))
			return FALSE;
		
		BYTE paramCnt = 0;
		if (!(stream > &paramCnt))
			return FALSE;

		CSIZE bufferSize = msgSize - 2 * SIZEOF(CBYTE);
		__message_buffer = new byte[bufferSize];
		if (!ReadBuffer(stream, __message_buffer, bufferSize))

		message = new Message(msgCode, paramCnt);
		message->LoadFromBytes(__message_buffer);

		delete[] __message_buffer;

		return TRUE;
	}
	
	INLINE VOID WaitForEvent(Stream & stream, MessageHandler handler)
	{
		PIMESSAGE message = NULL;

		if (!ReadMessage(stream, message))
			return;

		handler(message);

		delete message;
	}

#pragma endregion
}


#endif
