/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef EXCLUDE_ITTYBITTY_MESSAGES

#include "IttyBitty_messages.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANTS & VARIABLES

CWORD IttyBitty::SERIAL_DEFAULT_TIMEOUT_MS = 1000;

PCCHAR IttyBitty::MESSAGE_MARKER = "FOX";

PBYTE IttyBitty::__message_buffer;

#pragma endregion


#pragma region Message DEFINITION


// CONSTRUCTORS/DESTRUCTOR

Message::Message(CBYTE messageCode, CBYTE paramCount) 
	: _MessageCode(messageCode), _ParamCount(paramCount), _Dispose(TRUE)
{
	_Params = new PIFIELD[paramCount];
}

Message::Message(CBYTE messageCode, CBYTE paramCount, PIFIELD param) 
	: _MessageCode(messageCode), _ParamCount(paramCount), _Dispose(TRUE)
{
	_Params = new PIFIELD[paramCount];
	_Params[0] = param;
}

Message::Message(CBYTE messageCode, CBYTE paramCount, PPIFIELD params) 
	: _MessageCode(messageCode), _ParamCount(paramCount), _Params(params) { }

Message::~Message()
{
	if (_Dispose && _Params != NULL)
	{
		for (BYTE i = 0; i < this->GetParamCount(); i++)
			delete _Params[i];
		
		delete[] _Params;
	}
}


// OPERATORS

PCIFIELD Message::operator[](CBYTE i) const
{
	return _Params[i];
}

PIFIELD Message::operator[](CBYTE i)
{
	return _Params[i];
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

RIFIELD Message::Param(CBYTE i)
{
	if (_Params == NULL)
		return Field::NULL_OBJECT();

	return *_Params[i];
}


// USER METHODS

VOID Message::Handle(...)
{
	va_list args;
	va_start(args, 0);
	va_end(args);
}
				

// ISerializable IMPLEMENTATION

CSIZE Message::ByteSize() const
{
	return SIZEOF(CSIZE) + 2 * SIZEOF(CBYTE) + this->GetParamsByteSize();
}

CSIZE Message::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 4 * SIZEOF(CBYTE) + this->GetParamsStringSize() + 1;
}

CSIZE Message::ByteWidth() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
		size += _Params[i]->ByteWidth();

	return size;
}

CSIZE Message::StringLength() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
		size += _Params[i]->StringLength();

	return size;
}
		
PCBYTE Message::ToBytes() const
{
	CSIZE size = this->ByteSize();

	if (__message_buffer)
		delete[] __message_buffer;

	__message_buffer = new BYTE[size];

	PBYTE bufferPtr = __message_buffer;

	memcpy(bufferPtr++, &size, SIZEOF(CSIZE));

	CBYTE msgCode = this->GetMessageCode();
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));
	
	CBYTE paramCount = this->GetParamCount();
	memcpy(bufferPtr++, &paramCount, SIZEOF(CBYTE));

	PIFIELD param = NULL;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < paramCount; i++)
	{
		param = _Params[i];
		paramSize = param->ByteSize();

		memcpy(bufferPtr, param->ToBytes(), paramSize);
		bufferPtr += paramSize;
	}

	return __message_buffer;
}

PCCHAR Message::ToString() const
{
	CSIZE size = this->StringSize();
	CBYTE paramCount = this->GetParamCount();

	if (__message_buffer)
		delete[] __message_buffer;

	__message_buffer = new BYTE[size];

	PBYTE bufferPtr = __message_buffer;	
	CHAR valStr[9];

	ltoa(size, valStr, 0x10);
	memcpy(bufferPtr, valStr, 2 * SIZEOF(CSIZE));
	bufferPtr += 2 * SIZEOF(CSIZE);

	itoa(this->GetMessageCode(), valStr, 0x10);
	memcpy(bufferPtr, valStr, 2 * SIZEOF(CBYTE));
	bufferPtr += 2 * SIZEOF(CBYTE);
	
	itoa(paramCount, valStr, 0x10);
	memcpy(bufferPtr, valStr, 2 * SIZEOF(CBYTE));
	bufferPtr += 2 * SIZEOF(CBYTE);
	
	PIFIELD param = NULL;
	SIZE paramSize = 0;
	
	for (SIZE i = 0; i < paramCount; i++)
	{
		param = _Params[i];
		paramSize = param->StringSize();

		if (param->GetDataType() == DataType::STRING_FIELD)
			paramSize -= 1;

		memcpy(bufferPtr, param->ToString(), paramSize);
		bufferPtr += paramSize;
	}

	__message_buffer[size - 1] = '\0';

	return reinterpret_cast<PCCHAR>(__message_buffer);
}

VOID Message::LoadFromBytes(PCBYTE data)
{
	_MessageCode = *data++;
	_ParamCount = *data++;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
		_Params[i] = FieldFromBytes(data);
}

VOID Message::LoadFromString(PCCHAR data)
{
	CHAR valStr[3];
	valStr[2] = '\0';
	
	memcpy(valStr, data, 2 * SIZEOF(CBYTE));
	_MessageCode = static_cast<CBYTE>(strtol(valStr, NULL, 0x10));
	data += 2 * SIZEOF(CBYTE);
	
	memcpy(valStr, data, 2 * SIZEOF(CBYTE));
	_ParamCount = static_cast<DataType>(strtol(valStr, NULL, 0x10));
	data += 2 * SIZEOF(CBYTE);
	
	for (BYTE i = 0; i < this->ByteWidth(); i++)
		_Params[i] = FieldFromString(data);
}


SIZE Message::printTo(Print & printer) const
{
	SIZE size = printer.print(MESSAGE_MARKER);
	
#ifdef DEBUG
	SIZE msgSize = this->StringSize();
	PCCHAR buffer = this->ToString();
#else
	SIZE msgSize = this->ByteSize();
	PCBYTE buffer = this->ToBytes();
#endif

	for (SIZE i = 0; i < msgSize; i++)
		size += printer.print(buffer[i]);

	size += msgSize;

	return size;
}


// HELPER METHODS

CSIZE Message::GetParamsByteSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
		size += _Params[i]->ByteSize();

	return size;
}

CSIZE Message::GetParamsStringSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->GetParamCount(); i++)
		size += _Params[i]->StringSize() - 1;

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
