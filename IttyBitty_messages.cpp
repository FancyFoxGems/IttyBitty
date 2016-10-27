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
	}
		
	delete[] _Params;
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

PIFIELD Message::Param(CBYTE i)
{
	if (_Params == NULL)
		return NULL;

	return _Params[i];
}


// USER METHODS

VOID Message::Handle(...)
{
	//va_list args;
	//va_start(args, 0);
	//va_end(args);
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

	bufferPtr = NULL;

	return __message_buffer;
}

int ram()
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

PCCHAR Message::ToString() const
{
	CSIZE size = this->StringSize();
	CBYTE paramCount = this->GetParamCount();

	if (__message_buffer)
	{
		Serial.println(ram());
		Serial.flush();
		delete[] __message_buffer;
		Serial.println("deleted");
		Serial.println(ram());
		Serial.flush();
	}
	
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
	_MessageCode = *data++;
	_ParamCount = *data++;
	
	for (SIZE i = 0; i < _ParamCount; i++)
		_Params[i] = FieldFromBytes(data);
}

VOID Message::FromString(PCCHAR data)
{
	data = StringReadValue<BYTE>(_MessageCode, data);
	data = StringReadValue<BYTE>(_ParamCount, data);

	for (BYTE i = 0; i < _ParamCount; i++)
		_Params[i] = FieldFromString(data);
}


SIZE Message::printTo(Print & printer) const
{
	SIZE size = strlen(MESSAGE_MARKER);
	
#ifdef _DEBUG
	SIZE msgSize = this->StringSize();
	STATIC PCCHAR buffer = NULL;
	buffer = this->ToString();
#else
	SIZE msgSize = this->ByteSize();
	STATIC PCBYTE buffer = this->ToBytes();
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
