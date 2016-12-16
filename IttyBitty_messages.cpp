/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#if defined(ITTYBITTY_SLIM) || defined(NO_ITTYBITTY_PARAMS)
	#define NO_ITTYBITTY_MESSAGES
#endif

#ifndef NO_ITTYBITTY_MESSAGES


#include "IttyBitty_messages.h"

using namespace IttyBitty;


#pragma region GLOBAL CONSTANT & VARIABLE DEFINITIONS

PCCHAR IttyBitty::MESSAGE_MARKER = "FOX";

PBYTE IttyBitty::__message_buffer = NULL;

#pragma endregion


namespace IttyBitty
{
#ifdef ARDUINO

#pragma region SERIAL/STREAM READING GLOBAL FUNCTION DEFINITIONS

	CBOOL operator >(Stream & stream, PBYTE b)
	{
		return stream.readBytes(b, 1);
	}

	CBOOL ReadBuffer(Stream & stream, PBYTE buffer, CSIZE length)
	{
		SIZE i = length;

		while (i > 0)
		{
			if (!stream.available())
			{
				delay(SERIAL_DEFAULT_TIMEOUT_MS);

				if (!stream.available())
					return FALSE;
			}

			INT result = stream.read();
			if (result < 0)
				return FALSE;

			buffer[length - i--] = (CBYTE)result;
		}

		return TRUE;
	}

#pragma endregion


#pragma region [Message] PARSING/HANDLING GLOBAL FUNCTION DEFINITIONS


	PIMESSAGE ReceiveMessageAsBytes(Stream & stream)
	{
		if (!stream.find(UNCONST(MESSAGE_MARKER), strlen(MESSAGE_MARKER)))
			return NULL;

		SIZE msgSize = 0;
		msgSize = Read<CSIZE>(stream, (PBYTE)&msgSize);
		if (msgSize == 0)
			return NULL;

		if (__message_buffer)
			delete[] __message_buffer;

		CSIZE bufferSize = msgSize - SIZEOF(CSIZE);
		__message_buffer = new byte[bufferSize];

		if (!ReadBuffer(stream, __message_buffer, bufferSize))
			return NULL;

		PIMESSAGE message = new Message(__message_buffer);

		message->FreeBuffer();

		return message;
	}

	PIMESSAGE ReceiveMessageAsString(Stream & stream)
	{
		if (!stream.find(UNCONST(MESSAGE_MARKER), strlen(MESSAGE_MARKER)))
			return NULL;

	#ifdef DEBUG_MESSAGES
		PrintString(F("MESSAGE INCOMING [SIZE="));
	#endif

		CHAR valStr[4];
		ReadBuffer(stream, reinterpret_cast<PBYTE>(valStr), 2 * SIZEOF(CSIZE));

		SIZE msgSize = 0;
		StringReadValue<SIZE>(msgSize, valStr);
		if (msgSize == 0)
			return NULL;

	#ifdef DEBUG_MESSAGES
		PrintVal(msgSize);
		PrintLine("].");
	#endif

		if (__message_buffer)
			delete[] __message_buffer;

		CSIZE bufferSize = msgSize - 2 * SIZEOF(CSIZE);
		__message_buffer = new byte[bufferSize];
		__message_buffer[bufferSize - 1] = '\0';

	#ifdef DEBUG_MESSAGES
		PrintVal(bufferSize);
		PrintLine(F(" BYTES ALLOCATED.  READING DATA..."));
	#endif

		if (!ReadBuffer(stream, __message_buffer, bufferSize - 1))
			return NULL;

	#ifdef DEBUG_MESSAGES
		PrintString(F("RAW DATA: "));
		PrintLine((PCCHAR)__message_buffer);
		PrintLine(F("BUFFER FILLED.  LOADING..."));
	#endif

		PIMESSAGE message = new Message(reinterpret_cast<PCCHAR>(__message_buffer));

	#ifdef DEBUG_MESSAGES
		PrintLine(F("MESSAGE LOADED.\n"));
	#endif

		message->FreeBuffer();

		return message;
	}

	VOID WaitForMessage(Stream & stream, PMESSAGEHANDLER msgHandler)
	{
		PIMESSAGE message = NULL;

	#ifdef _DEBUG
		message = ReceiveMessageAsString(stream);
	#else
		message = ReceiveMessageAsBytes(stream);
	#endif

		if (!message)
			return;

		msgHandler(message);

		if (message)
			delete message;
	}

#pragma endregion

#endif	// #ifdef ARDUINO
};


#pragma region [Message] IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

Message::Message(CBYTE messageCode, CBYTE paramCount)
	: _Dispose(TRUE), _MessageCode(messageCode), _ParamCount(paramCount), _Params(NULL)
{
	if (_ParamCount > 0)
		_Params = new PIPARAM[_ParamCount];
}

Message::Message(RCMESSAGE other)
{
	this->~Message();

	_Dispose = FALSE;

	_MessageCode = other._MessageCode;
	_ParamCount = other._ParamCount;
	_Params = other._Params;
}

Message::Message(RRMESSAGE other)
{
	this->~Message();

	new (this) Message(other._MessageCode, other._ParamCount, other._Params);
}

Message::Message(PCBYTE data)
{
	this->FromBinary(data);
}

Message::Message(PCCHAR data)
{
	this->FromString(data);
}

Message::Message(CBYTE messageCode, RCIPARAM param)
	: _Dispose(TRUE), _MessageCode(messageCode), _ParamCount(1), _Params(NULL)
{
	_Params = new PIPARAM[_ParamCount];

#ifdef _DEBUG
	_Params[0] = ParamFromString(param.ToString());
#else
	_Params[0] = ParamFromBytes(param.ToBinary());
#endif
}

Message::Message(CBYTE messageCode, CBYTE paramCount, PPIPARAM params)
	: _MessageCode(messageCode), _ParamCount(paramCount), _Params(params)
{
	if (!_Params)
		_Params = new PIPARAM[_ParamCount];
}

Message::~Message()
{
	this->Dispose();
}


// PROTECTED DISPOSAL METHOD

VOID Message::Dispose()
{
	if (!_Params)
		return;

	if (_Dispose)
	{
		for (BYTE i = 0; i < _ParamCount; i++)
		{
			if (_Params[i])
			{
				delete _Params[i];
				_Params[i] = NULL;
			}
		}
	}

	delete[] _Params;
	_Params = NULL;
}


// OPERATORS

RMESSAGE Message::operator=(RRMESSAGE other)
{
	*this = Message(other);

	return *this;
}

RMESSAGE Message::operator=(RCMESSAGE other)
{
	*this = Message(other);

	return *this;
}

PCIPARAM Message::operator[](CBYTE i) const
{
	if (!_Params)
		return NULL;

	return _Params[i];
}

PIPARAM Message::operator[](CBYTE i)
{
	if (!_Params)
		return NULL;

	return _Params[i];
}


// ACCESSORS

CBYTE Message::ParamCount() const
{
	return _ParamCount;
}

CBYTE Message::GetMessageCode() const
{
	return _MessageCode;
}

RCIPARAM Message::Param(CBYTE i) const
{
	return *this->operator[](i);
}

RIPARAM Message::Param(CBYTE i)
{
	return *this->operator[](i);
}


// [IMessage] IMPLEMENTATION

BOOL Message::Handle(PTR results, CPTR state)
{
#ifdef DEBUG_MESSAGES
	PrintLine(F("Message::Handle"));
#endif

	return TRUE;
}


// [ITransmittable] IMPLEMENTATION

#ifdef ARDUINO

BOOL Message::Transmit(HardwareSerial & serial)
{
	if (!serial.availableForWrite())
		delay(SERIAL_DEFAULT_TIMEOUT_MS);
	if (!serial.availableForWrite())
		return FALSE;

	if (!this->printTo(serial))
		return FALSE;

	serial.flush();

	return TRUE;
}

BOOL Message::Transmit(BYTE i2cAddr, TwoWire & twi)
{
	twi.beginTransmission(i2cAddr);

	if (!this->printTo(twi))
		return FALSE;

	twi.flush();

	if (twi.endTransmission())
		return FALSE;

	return TRUE;
}

#endif	// #ifdef ARDUINO


// [ISerializable] IMPLEMENTATION

CSIZE Message::BinarySize() const
{
	return SIZEOF(CSIZE) + 2 * SIZEOF(CBYTE) + this->ParamsBinarySize();
}

CSIZE Message::StringSize() const
{
	return 2 * SIZEOF(CSIZE) + 4 * SIZEOF(CBYTE) + this->ParamsStringSize() + 1;
}

PCBYTE Message::ToBinary() const
{
	CSIZE size = this->BinarySize();

	this->FreeBuffer();

	__message_buffer = new byte[size];

	PBYTE bufferPtr = __message_buffer;

	memcpy(bufferPtr++, &size, SIZEOF(CSIZE));

	CBYTE msgCode = this->GetMessageCode();
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));

	memcpy(bufferPtr++, &_ParamCount, SIZEOF(CBYTE));

	PIPARAM param = NULL;
	PCBYTE paramBytes = NULL;
	SIZE paramSize = 0;

	for (SIZE i = 0; i < _ParamCount; i++)
	{
		param = _Params[i];
		paramBytes = param->ToBinary();
		paramSize = param->BinarySize();

		memcpy(bufferPtr, paramBytes, paramSize);

		param->FreeBuffer();

		bufferPtr += paramSize;
	}

	return __message_buffer;
}

PCCHAR Message::ToString() const
{
	CSIZE size = this->StringSize();

	this->FreeBuffer();

	__message_buffer = new byte[size];
	__message_buffer[size - 1] = '\0';

	PCHAR bufferPtr = reinterpret_cast<PCHAR>(__message_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(this->GetMessageCode(), bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(_ParamCount, bufferPtr);

	PIPARAM param = NULL;
	PCCHAR paramStr = NULL;
	SIZE paramSize = 0;

	for (SIZE i = 0; i < _ParamCount; i++)
	{
		param = _Params[i];
		paramStr = param->ToString();
		paramSize = param->StringSize() - 1;

		memcpy(bufferPtr, paramStr, paramSize);

		param->FreeBuffer();

		// TODO: Why..?
		if (i == 0)
			bufferPtr = StringInsertValue<CBYTE>(_ParamCount, bufferPtr - 2);

		bufferPtr += paramSize;
	}


	return reinterpret_cast<PCCHAR>(__message_buffer);
}

VOID Message::FromBinary(PCBYTE data)
{
	PCBYTE bufferPtr = data;

	_MessageCode = *bufferPtr++;
	_ParamCount = *bufferPtr++;

	this->Dispose();

	if (_ParamCount > 0)
		_Params = new PIPARAM[_ParamCount];

	_Dispose = TRUE;

	for (SIZE i = 0; i < _ParamCount; i++)
	{
		_Params[i] = ParamFromBytes(bufferPtr);

		bufferPtr += _Params[i]->ByteWidth();
	}
}

VOID Message::FromString(PCCHAR data)
{
	PCCHAR bufferPtr = data;

	bufferPtr = StringReadValue<BYTE>(_MessageCode, bufferPtr);
	bufferPtr = StringReadValue<BYTE>(_ParamCount, bufferPtr);

	this->Dispose();

	if (_ParamCount > 0)
		_Params = new PIPARAM[_ParamCount];

	_Dispose = TRUE;

	for (BYTE i = 0; i < _ParamCount; i++)
	{
		_Params[i] = ParamFromString(bufferPtr);

		bufferPtr += _Params[i]->StringSize() - 1;
	}
}

VOID Message::FreeBuffer() const
{
	if (!__message_buffer)
		return;

	delete[] __message_buffer;
	__message_buffer = NULL;
}

#ifdef ARDUINO

SIZE Message::printTo(Print & printer) const
{
	SIZE size = strlen(MESSAGE_MARKER);

#ifdef _DEBUG
	SIZE msgSize = this->StringSize();
	PCCHAR buffer = this->ToString();
#else
	SIZE msgSize = this->BinarySize();
	PCBYTE buffer = this->ToBinary();
#endif

	for (BYTE i = 0; i < size; i++)
		printer.print(MESSAGE_MARKER[i]);

	for (SIZE i = 0; i < msgSize; i++)
		printer.print(buffer[i]);

	size += msgSize;

	return size;
}

#endif	// #ifdef ARDUINO


// [IMessage] HELPER METHODS

CSIZE Message::ParamsBinarySize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _ParamCount; i++)
		size += _Params[i]->BinarySize();

	return size;
}

CSIZE Message::ParamsStringSize() const
{
	SIZE size = 0;

	for (BYTE i = 0; i < _ParamCount; i++)
		size += _Params[i]->StringSize() - 1;

	return size;
}

#pragma endregion

#endif // #ifndef NO_ITTYBITTY_MESSAGES
