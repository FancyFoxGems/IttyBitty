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

#pragma endregion


#pragma region Message DEFINITION


// STATIC CONSTEXPR METHODS

template<CBYTE MsgCode, CBYTE ParamCnt>
CONSTEXPR CBYTE Message<MsgCode, ParamCnt>::MESSAGE_CODE()
{
	return MsgCode;
}

template<CBYTE MsgCode, CBYTE ParamCnt>
CONSTEXPR CSIZE Message<MsgCode, ParamCnt>::PARAM_COUNT()
{
	return ParamCnt;
}


// CONSTRUCTORS/DESTRUCTOR

template<CBYTE MsgCode, CBYTE ParamCnt>
Message<MsgCode, ParamCnt>::Message() : _Dispose(TRUE)
{
	_Params = new Field[ParamCnt];
}

template<CBYTE MsgCode, CBYTE ParamCnt>
Message<MsgCode, ParamCnt>::Message(RIFIELD param) : _Dispose(TRUE)
{
	_Params = new Field[ParamCnt];
	_Params[0] = param;
}

template<CBYTE MsgCode, CBYTE ParamCnt>
Message<MsgCode, ParamCnt>::Message(PIFIELD params) : _Params(params) { }

template<CBYTE MsgCode, CBYTE ParamCnt>
Message<MsgCode, ParamCnt>::~Message()
{
	if (_Dispose && _Params != NULL)
		delete[] _Params;
}


// OPERATORS

template<CBYTE MsgCode, CBYTE ParamCnt>
RCIFIELD Message<MsgCode, ParamCnt>::operator[](CBYTE i) const
{
	return _Params[i];
}

template<CBYTE MsgCode, CBYTE ParamCnt>
RIFIELD Message<MsgCode, ParamCnt>::operator[](CBYTE i)
{
	return this->Param(i);
}


// USER METHODS

template<CBYTE MsgCode, CBYTE ParamCnt>
RIFIELD Message<MsgCode, ParamCnt>::Param(CBYTE i)
{
	if (_Params == NULL)
		return Field::NULL_OBJECT();

	return _Params[i];
}
				

// ISerializable IMPLEMENTATION

template<CBYTE MsgCode, CBYTE ParamCnt>
CSIZE Message<MsgCode, ParamCnt>::Size() const
{
	return strlen(MESSAGE_MARKER) + SIZEOF(CBYTE) + SIZEOF(CBYTE) + SIZEOF(CSIZE) + this->ParamsSize();
}

template<CBYTE MsgCode, CBYTE ParamCnt>
CSIZE Message<MsgCode, ParamCnt>::ByteWidth() const
{
	return strlen(MESSAGE_MARKER) + SIZEOF(CBYTE) + SIZEOF(CBYTE) + SIZEOF(CSIZE) + this->ParamsStringSize();
}
		
template<CBYTE MsgCode, CBYTE ParamCnt>
PCBYTE Message<MsgCode, ParamCnt>::ToBytes() const
{
	CSIZE size = this->Size();

	if (__message_buffer)
		delete[] __message_buffer;

	__message_buffer = new BYTE[size];

	PBYTE bufferPtr = __message_buffer;
		
	memcpy(bufferPtr, &MESSAGE_MARKER, strlen(MESSAGE_MARKER));
	bufferPtr += strlen(MESSAGE_MARKER);

	CBYTE msgCode = MsgCode;
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));
	
	CBYTE paramCount = ParamCnt;
	memcpy(bufferPtr++, &paramCount, SIZEOF(CBYTE));
	
	CSIZE paramsSize = this->ParamsSize();
	memcpy(bufferPtr, &paramsSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	PIFIELD param;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < PARAM_COUNT(); i++)
	{
		param = &_Params[i];
		paramSize = param->Size();

		memcpy(bufferPtr, param->ToBytes(), paramSize);
		bufferPtr += paramSize;
	}

	return __message_buffer;
}

template<CBYTE MsgCode, CBYTE ParamCnt>
PCCHAR Message<MsgCode, ParamCnt>::ToString() const
{
	CSIZE size = this->ByteWidth();

	if (__message_buffer)
		delete[] __message_buffer;

	__message_buffer = new BYTE[size];

	PBYTE bufferPtr = __message_buffer;
		
	memcpy(bufferPtr, &MESSAGE_MARKER, strlen(MESSAGE_MARKER) - 1);
	bufferPtr += strlen(MESSAGE_MARKER) - 1;

	CBYTE msgCode = MsgCode;
	memcpy(bufferPtr++, &msgCode, SIZEOF(CBYTE));
	
	CBYTE paramCount = ParamCnt;
	memcpy(bufferPtr++, &paramCount, SIZEOF(CBYTE));
	
	CSIZE paramsSize = this->ParamsStringSize();
	memcpy(bufferPtr, &paramsSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);
	
	PIFIELD param;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < PARAM_COUNT(); i++)
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

template<CBYTE MsgCode, CBYTE ParamCnt>
VOID Message<MsgCode, ParamCnt>::LoadFromBytes(PCBYTE data)
{
	//_DataType = static_cast<DataType>(*data++);

	PBYTE bufferPtr = data;

	for (SIZE i = 0; i < PARAM_COUNT; i++)
	{
		_Params[i] = Field();
	}

	//SIZE paramsSize = 
}

template<CBYTE MsgCode, CBYTE ParamCnt>
VOID Message<MsgCode, ParamCnt>::LoadFromString(PCCHAR data)
{
	LoadFromBytes(reinterpret_cast<PCBYTE>(data));
}


template<CBYTE MsgCode, CBYTE ParamCnt>
SIZE Message<MsgCode, ParamCnt>::printTo(Print& printer) const
{
	SIZE printed = printer.print(MESSAGE_MARKER);
	printed += printer.print(MsgCode);
	printed += printer.print(this->ParamsStringSize());
	
	for (SIZE i = 0; i < PARAM_COUNT(); i++)
		printed += _Params[i].printTo(printer);

	return printed;
}


// HELPER METHODS

template<CBYTE MsgCode, CBYTE ParamCnt>
CSIZE Message<MsgCode, ParamCnt>::ParamsSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < PARAM_COUNT(); i++)
		size += _Params[i].Size();

	return size;
}

template<CBYTE MsgCode, CBYTE ParamCnt>
CSIZE Message<MsgCode, ParamCnt>::ParamsStringSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < PARAM_COUNT(); i++)
	{
		size += _Params[i].ByteWidth();

		if (_Params[i].GetDataType() == DataType::STRING_FIELD)
			--size;
	}

	return size;
}

#pragma endregion

#endif // #ifndef EXCLUDE_ITTYBITTY_MESSAGES
