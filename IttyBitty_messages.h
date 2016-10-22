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


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES

	EXTERN CWORD SERIAL_DEFAULT_TIMEOUT_MS;

	EXTERN PCCHAR MESSAGE_MARKER;
		
	// Message::ToBytes() / ToString() BUFFER POINTER
	EXTERN PBYTE __message_buffer;

#pragma endregion

	
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	//  Message

	template<CBYTE MsgCode, CBYTE ParamCnt>
	class Message;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using MESSAGE = Message<MsgCode, ParamCnt>;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PMESSAGE = Message<MsgCode, ParamCnt> *;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RMESSAGE = Message<MsgCode, ParamCnt> &;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PPMESSAGE = Message<MsgCode, ParamCnt> **;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RRMESSAGE = Message<MsgCode, ParamCnt> &&;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using CMESSAGE = const Message<MsgCode, ParamCnt>;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PCMESSAGE = const Message<MsgCode, ParamCnt> *;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using RCMESSAGE = const Message<MsgCode, ParamCnt> &;
	template<CBYTE MsgCode, CBYTE ParamCnt>
	using PPCMESSAGE = const Message<MsgCode, ParamCnt> **;

#pragma endregion
	

#pragma region Message DECLARATION

	template<CBYTE MsgCode, CBYTE ParamCnt = 0>
	CLASS Message : public ISerializable
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR CBYTE MESSAGE_CODE();
		STATIC CONSTEXPR CSIZE PARAM_COUNT();


		// CONSTRUCTORS/DESTRUCTOR

		Message();
		Message(RIFIELD);
		Message(PIFIELD);

		VIRTUAL ~Message();


		// OPERATORS

		VIRTUAL RCIFIELD operator[](CBYTE) const;
		VIRTUAL RIFIELD operator[](CBYTE);


		// USER METHODS

		VIRTUAL RIFIELD Param(CBYTE = 0);
		

		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE Size() const;
		VIRTUAL CSIZE ByteWidth() const;

		VIRTUAL PCBYTE ToBytes() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID LoadFromBytes(PCBYTE);
		VIRTUAL VOID LoadFromString(PCCHAR);

		VIRTUAL SIZE printTo(Print&) const;

	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		PIFIELD _Params;
		
		// HELPER METHODS

		VIRTUAL CSIZE ParamsSize() const;
		VIRTUAL CSIZE ParamsStringSize() const;
	};

#pragma endregion
	

#pragma region PARSING METHODS

	INLINE CBOOL operator >(Stream & stream, PBYTE b)
	{
		if (!stream.available())
			delay(100);
				
		if (!stream.available())
			return FALSE;
				
		int result = stream.read();
		if (result < 0)
			return FALSE;

		*b = (CBYTE)result;
		return TRUE;
	}

	INLINE CBOOL TimedRead(Stream & stream, PBYTE b, CSIZE length = 1)
	{
		SIZE i = length;

		while (i-- > 0)
		{
			if (!stream.available())
				delay(100);
				
			if (!stream.available())
				return FALSE;
				
			int result = stream.read();
			if (result < 0)
				return FALSE;

			b[i] = (CBYTE)result;
		}

		return TRUE;
	}
	
	INLINE PISERIALIZABLE ParseNextMessage(Stream & stream)
	{
		while (!stream.available()) delay(100);

		if (!stream.find(UNCONST(MESSAGE_MARKER)))
			return NULL;

		BYTE b = 0;

		if (!(stream > &b))
			return NULL;
		CBYTE msgSize = (CBYTE)b;

		while (stream.available())
		{

		}
	}
	
	template<CBYTE MsgCode, CBYTE ParamCnt = 0>
	INLINE PMESSAGE<MsgCode, ParamCnt> ParseMessage(Stream &);

#pragma endregion
}


#endif
