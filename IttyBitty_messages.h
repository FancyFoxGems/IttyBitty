/***********************************************************************************************
* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES
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

	EXTERN PCCHAR MESSAGE_MARKER;
		
	// Message::ToBytes() / ToString() BUFFER POINTER
	EXTERN PBYTE __message_buffer;

#pragma endregion


#pragma region ENUMS

#ifdef COMPILE_STANDALONE

	enum MessageCode : BYTE
	{
		// Primary types
		REQUEST_TYPE		= 0x0,
		RESPONSE_TYPE		= 0x80,


		// Categories
		ANGLE_TYPE			= 0x10,
		NEWANGLE_TYPE		= 0x20,
		STATUS_TYPE			= 0x40,


		// Request types
		ANGLE_REQUEST		= REQUEST_TYPE | ANGLE_TYPE,
		NEWANGLE_REQUEST	= REQUEST_TYPE | NEWANGLE_TYPE,
		STATUS_REQUEST		= REQUEST_TYPE | STATUS_TYPE,

		// Response types
		ANGLE_RESPONSE		= RESPONSE_TYPE | 0x1,
		NEWANGLE_RESPONSE	= RESPONSE_TYPE | 0x2,
		STATUS_RESPONSE		= RESPONSE_TYPE | STATUS_TYPE,
		CONTROLLER_STATUS	= STATUS_RESPONSE | 0x1,
		DRIVER_STATUS		= STATUS_RESPONSE | 0x2
	};

#else

	EXTERN enum MessageCode;

#endif	// #ifdef COMPILE_STANDALONE
	
#pragma endregion 

	
#pragma region FORWARD DECLARATIONS & TYPE ALIASES


	//  Message

	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	class Message;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using MESSAGE = Message<TMessage, MsgCode, ParamCnt>;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using PMESSAGE = Message<TMessage, MsgCode, ParamCnt> *;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using RMESSAGE = Message<TMessage, MsgCode, ParamCnt> &;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using PPMESSAGE = Message<TMessage, MsgCode, ParamCnt> **;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using RRMESSAGE = Message<TMessage, MsgCode, ParamCnt> &&;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using CMESSAGE = const Message<TMessage, MsgCode, ParamCnt>;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using PCMESSAGE = const Message<TMessage, MsgCode, ParamCnt> *;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using RCMESSAGE = const Message<TMessage, MsgCode, ParamCnt> &;
	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt>
	using PPCMESSAGE = const Message<TMessage, MsgCode, ParamCnt> **;

#pragma endregion
	

#pragma region Message DECLARATION

	template<class TMessage, MessageCode MsgCode, CSIZE ParamCnt = 0>
	CLASS Message : public ISerializable
	{
	public:

		// STATIC CONSTEXPR METHODS

		STATIC CONSTEXPR MessageCode MESSAGE_CODE();
		STATIC CONSTEXPR CSIZE PARAM_COUNT();


		// CONSTRUCTORS/DESTRUCTOR

		Message();
		Message(RIFIELD);
		Message(PIFIELD);

		VIRTUAL ~Message();


		// OPERATORS

		VIRTUAL RCIFIELD operator[](CSIZE) const;
		VIRTUAL RIFIELD operator[](CSIZE);


		// USER METHODS

		VIRTUAL RIFIELD Param(CSIZE = 0);
		

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
}


#endif
