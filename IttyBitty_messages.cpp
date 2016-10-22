/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef EXCLUDE_ITTYBITTY_MESSAGES

#include "IttyBitty_messages.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;

PCCHAR IttyBitty::MESSAGE_MARKER = "FOX";

#pragma endregion


#pragma region Message DEFINITION


// CONSTRUCTORS/DESTRUCTOR

Message::Message(CBYTE messageCode, CBYTE paramCount) : _MessageCode(messageCode), _ParamCount(paramCount), _Dispose(TRUE)
{
	_Params = new Field[paramCount];
}

Message::Message(CBYTE messageCode, CBYTE paramCount, RIFIELD param) : _MessageCode(messageCode), _ParamCount(paramCount), _Dispose(TRUE)
{
	_Params = new Field[paramCount];
	_Params[0] = param;
}

Message::Message(CBYTE messageCode, CBYTE paramCount, PIFIELD params) : _MessageCode(messageCode), _ParamCount(paramCount), _Params(params) { }

Message::~Message()
{
	if (_Dispose && _Params != NULL)
		delete[] _Params;
}


// OPERATORS

RCIFIELD Message::operator[](CBYTE i) const
{
	return _Params[i];
}

RIFIELD Message::operator[](CBYTE i)
{
	return this->Param(i);
}


// ACCESSORS

CBYTE Message::GetMessageCode() const
{
	return _MessageCode;
}

CBYTE Message::GetParamCount() const
{
	return _ParamCount;
}


// USER METHODS

RIFIELD Message::Param(CBYTE i)
{
	if (_Params == NULL)
		return Field::NULL_OBJECT();

	return _Params[i];
}
				

// ISerializable IMPLEMENTATION

CSIZE Message::Size() const
{
	return 2 * SIZEOF(CBYTE) + SIZEOF(CSIZE) + this->ParamsSize();
}

CSIZE Message::ByteWidth() const
{
	return 2 * SIZEOF(CBYTE) + SIZEOF(CSIZE) + this->ParamsStringSize();
}
		
PCBYTE Message::ToBytes() const
{
	CSIZE size = this->Size();

	if (__message_buffer)
		delete[] __message_buffer;

	__message_buffer = new BYTE[strlen(MESSAGE_MARKER) + SIZEOF(CSIZE) + size];

	PBYTE bufferPtr = __message_buffer;
		
	memcpy(bufferPtr, &MESSAGE_MARKER, strlen(MESSAGE_MARKER));
	bufferPtr += strlen(MESSAGE_MARKER);

	memcpy(bufferPtr++, &size, SIZEOF(CSIZE));

	CBYTE msgCode = this->GetMessageCode();
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));
	
	CBYTE paramCount = this->GetParamCount();
	memcpy(bufferPtr++, &paramCount, SIZEOF(CBYTE));
	
	CSIZE paramsSize = this->ParamsSize();
	memcpy(bufferPtr, &paramsSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	PIFIELD param;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < paramCount; i++)
	{
		param = &_Params[i];
		paramSize = param->Size();

		memcpy(bufferPtr, param->ToBytes(), paramSize);
		bufferPtr += paramSize;
	}

	return __message_buffer;
}

PCCHAR Message::ToString() const
{
	CSIZE size = this->ByteWidth();

	if (__message_buffer)
		delete[] __message_buffer;

	__message_buffer = new BYTE[strlen(MESSAGE_MARKER) + SIZEOF(CSIZE) + size];

	PBYTE bufferPtr = __message_buffer;
		
	memcpy(bufferPtr, &MESSAGE_MARKER, strlen(MESSAGE_MARKER) - 1);
	bufferPtr += strlen(MESSAGE_MARKER) - 1;
	
	memcpy(bufferPtr++, &size, SIZEOF(CSIZE));

	CBYTE msgCode = this->GetMessageCode();
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));
	
	CBYTE paramCount = this->GetParamCount();
	memcpy(bufferPtr++, &paramCount, SIZEOF(CBYTE));
	
	CSIZE paramsSize = this->ParamsStringSize();
	memcpy(bufferPtr, &paramsSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);
	
	PIFIELD param;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < paramCount; i++)
	{
		param = &_Params[i];
		paramSize = param->ByteWidth();
		if (param->GetDataType() == DataType::STRING_FIELD)
			paramSize -= 1;

		memcpy(bufferPtr, param->ToString(), paramSize);
		bufferPtr += paramSize;
	}

	__message_buffer[size] = '\0';

	return reinterpret_cast<PCCHAR>(__message_buffer);
}

VOID Message::LoadFromBytes(PCBYTE data)
{
	//_DataType = static_cast<DataType>(*data++);

	//PBYTE bufferPtr = data;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
	{
		_Params[i] = Field();
	}

	//SIZE paramsSize = 
}

VOID Message::LoadFromString(PCCHAR data)
{
	LoadFromBytes(reinterpret_cast<PCBYTE>(data));
}


SIZE Message::printTo(Print & printer) const
{
	SIZE printed = printer.print(MESSAGE_MARKER);
	printed += printer.print(this->Size());
	printed += printer.print(this->GetMessageCode());
	printed += printer.print(this->GetParamCount());
	printed += printer.print(this->ParamsStringSize());
	
	for (SIZE i = 0; i < this->GetParamCount(); i++)
		printed += _Params[i].printTo(printer);

	return printed;
}


// HELPER METHODS

CSIZE Message::ParamsSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
		size += _Params[i].Size();

	return size;
}

CSIZE Message::ParamsStringSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
	{
		size += _Params[i].ByteWidth();

		if (_Params[i].GetDataType() == DataType::STRING_FIELD)
			--size;
	}

	return size;
}

#pragma endregion


#pragma region GenericMessage DEFINITION


// STATIC CONSTEXPR METHODS

template<CBYTE MsgCode, CBYTE ParamCnt>
CONSTEXPR CBYTE GenericMessage<MsgCode, ParamCnt>::MESSAGE_CODE()
{
	return MsgCode;
}

template<CBYTE MsgCode, CBYTE ParamCnt>
CONSTEXPR CSIZE GenericMessage<MsgCode, ParamCnt>::PARAM_COUNT()
{
	return ParamCnt;
}


// CONSTRUCTORS/DESTRUCTOR

template<CBYTE MsgCode, CBYTE ParamCnt>
GenericMessage<MsgCode, ParamCnt>::GenericMessage()
{
	_Dispose = TRUE;
	_Params = new Field[ParamCnt];
}

template<CBYTE MsgCode, CBYTE ParamCnt>
GenericMessage<MsgCode, ParamCnt>::GenericMessage(RIFIELD param)
{
	_Dispose = TRUE;
	_Params = new Field[ParamCnt];
	_Params[0] = param;
}

template<CBYTE MsgCode, CBYTE ParamCnt>
GenericMessage<MsgCode, ParamCnt>::GenericMessage(PIFIELD params)
{
	_Params = params;
}


// MESSAGE OVERRIDES

template<CBYTE MsgCode, CBYTE ParamCnt>
CBYTE GenericMessage<MsgCode, ParamCnt>::GetParamCount() const
{
	return PARAM_COUNT();
}

template<CBYTE MsgCode, CBYTE ParamCnt>
CBYTE GenericMessage<MsgCode, ParamCnt>::GetMessageCode() const
{
	return MESSAGE_CODE();
}

#pragma endregion

#endif // #ifndef EXCLUDE_ITTYBITTY_MESSAGES
