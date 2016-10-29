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

PBYTE IttyBitty::__message_buffer = NULL;

#pragma endregion


#pragma region Message IMPLEMENTATION

// CONSTRUCTORS/DESTRUCTOR

Message::Message(CBYTE messageCode, CBYTE paramCount)
	: _MessageCode(messageCode), _ParamCount(paramCount), _Dispose(TRUE), _Params(NULL)
{
	if (_ParamCount > 0)
		_Params = new PIFIELD[_ParamCount];
}

Message::Message(RCMESSAGE other)
{
	this->~Message();

#ifdef _DEBUG
	_Params[0] = FieldFromString(other.ToString());
#else
	_Params[0] = FieldFromBytes(other.ToBytes());
#endif
}

Message::Message(RRMESSAGE other)
{
	this->~Message();
	
	new (this) Message(other._MessageCode, other._ParamCount, other._Params);
}

Message::Message(PCBYTE data)
{
	this->FromBytes(data);
}

Message::Message(PCCHAR data)
{
	this->FromString(data);
}

Message::Message(CBYTE messageCode, PIFIELD param)
	: _MessageCode(messageCode), _ParamCount(1), _Dispose(TRUE), _Params(NULL)
{
	_Params = new PIFIELD[_ParamCount];
	_Params[0] = param;
}

Message::Message(CBYTE messageCode, RCIFIELD param)
	: _MessageCode(messageCode), _ParamCount(1), _Dispose(TRUE), _Params(NULL)
{
	_Params = new PIFIELD[_ParamCount];

#ifdef _DEBUG
	_Params[0] = FieldFromString(param.ToString());
#else
	_Params[0] = FieldFromBytes(param.ToBytes());
#endif
}

Message::Message(CBYTE messageCode, CBYTE paramCount, PPIFIELD params)
	: _MessageCode(messageCode), _ParamCount(paramCount), _Params(params) { }

Message::~Message()
{
	this->Dispose();
}

VOID Message::Dispose()
{
	if (_Params == NULL)
		return;

	if (_Dispose)
	{
		for (BYTE i = 0; i < this->GetParamCount(); i++)
		{
			if (_Params[i] != NULL)
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

PCIFIELD Message::operator[](CBYTE i) const
{
	if (_Params == NULL)
		return NULL;

	return _Params[i];
}

PIFIELD Message::operator[](CBYTE i)
{
	if (_Params == NULL)
		return NULL;

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

RCIFIELD Message::Param(CBYTE i) const
{
	return *this->operator[](i);
}

RIFIELD Message::Param(CBYTE i)
{
	return *this->operator[](i);
}


// USER METHODS

//VOID Message::Handle(...)
BOOL Message::Handle(PVOID results, PCVOID state)
{
	//va_list args;
	//va_start(args, 0);
	//va_end(args);
#ifdef DEBUG_MESSAGES
	PrintLineAndFlush(F("Message::Handle"));
#endif

	return TRUE;
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

	STATIC PBYTE bufferPtr = NULL;
	bufferPtr = __message_buffer;

	memcpy(bufferPtr++, &size, SIZEOF(CSIZE));

	CBYTE msgCode = this->GetMessageCode();
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));

	CBYTE paramCount = this->GetParamCount();
	memcpy(bufferPtr++, &paramCount, SIZEOF(CBYTE));

	PIFIELD param = NULL;
	STATIC PCBYTE paramBytes = NULL;
	SIZE paramSize = 0;


	for (SIZE i = 0; i < paramCount; i++)
	{
		param = _Params[i];
		paramBytes = param->ToBytes();
		paramSize = param->ByteSize();

		memcpy(bufferPtr, paramBytes, paramSize);

		delete[] paramBytes;
		paramBytes = NULL;

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
	__message_buffer[size - 1] = '\0';

	STATIC PCHAR bufferPtr = NULL;
	bufferPtr = reinterpret_cast<PCHAR>(__message_buffer);

	bufferPtr = StringInsertValue<CSIZE>(size, bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(this->GetMessageCode(), bufferPtr);
	bufferPtr = StringInsertValue<CBYTE>(paramCount, bufferPtr);

	PIFIELD param = NULL;
	STATIC PCCHAR paramStr = NULL;
	SIZE paramSize = 0;

	for (SIZE i = 0; i < paramCount; i++)
	{

		param = _Params[i];
		paramStr = param->ToString();
		paramSize = param->StringSize() - 1;

		memcpy(bufferPtr, paramStr, paramSize);

		delete[] paramStr;
		paramStr = NULL;

		if (i == 0)
			bufferPtr = StringInsertValue<CBYTE>(paramCount, bufferPtr - 2);

		bufferPtr += paramSize;
	}

	return reinterpret_cast<PCCHAR>(__message_buffer);
}

VOID Message::FromBytes(PCBYTE data)
{
	STATIC PCBYTE bufferPtr = NULL;
	bufferPtr = data;

	_MessageCode = *bufferPtr++;
	_ParamCount = *bufferPtr++;

	this->Dispose();

	if (_ParamCount > 0)
		_Params = new PIFIELD[_ParamCount];

	_Dispose = TRUE;

	for (SIZE i = 0; i < _ParamCount; i++)
	{
		_Params[i] = FieldFromBytes(bufferPtr);

		bufferPtr += _Params[i]->ByteWidth();
	}
}

VOID Message::FromString(PCCHAR data)
{
	STATIC PCCHAR bufferPtr = NULL;
	bufferPtr = data;

	bufferPtr = StringReadValue<BYTE>(_MessageCode, bufferPtr);
	bufferPtr = StringReadValue<BYTE>(_ParamCount, bufferPtr);

	this->Dispose();

	if (_ParamCount > 0)
		_Params = new PIFIELD[_ParamCount];

	_Dispose = TRUE;

	for (BYTE i = 0; i < _ParamCount; i++)
	{
		_Params[i] = FieldFromString(bufferPtr);

		bufferPtr += _Params[i]->StringSize() - 1;
	}
}


#ifdef ARDUINO

SIZE Message::printTo(Print & printer) const
{
	SIZE size = strlen(MESSAGE_MARKER);

#ifdef _DEBUG
	SIZE msgSize = this->StringSize();
	STATIC PCCHAR buffer = NULL;
	buffer = this->ToString();
#else
	SIZE msgSize = this->ByteSize();
	STATIC PCBYTE buffer = NULL;
	buffer = this->ToBytes();
#endif

	for (BYTE i = 0; i < size; i++)
		printer.print(MESSAGE_MARKER[i]);

	for (SIZE i = 0; i < msgSize; i++)
		printer.print(buffer[i]);

	delete[] __message_buffer;
	__message_buffer = NULL;

	size += msgSize;

	return size;
}

#endif	// #ifdef ARDUINO


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

#endif // #ifndef EXCLUDE_ITTYBITTY_MESSAGES
