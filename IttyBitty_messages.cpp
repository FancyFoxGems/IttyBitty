/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef EXCLUDE_ITTYBITTY_MESSAGES

#include "IttyBitty_messages.h"

using namespace IttyBitty;


#pragma region Message DEFINITION

// GLOBAL VARIABLES

PCCHAR IttyBitty::MESSAGE_MARKER = "!!";


// STATIC CONSTEXPR METHODS

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
CONSTEXPR CBYTE Message<TMessage, MsgCode, ParamCnt>::MESSAGE_CODE()
{
	return MsgCode;
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
CONSTEXPR CSIZE Message<TMessage, MsgCode, ParamCnt>::PARAM_COUNT()
{
	return ParamCnt;
}


// CONSTRUCTORS/DESTRUCTOR

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
Message<TMessage, MsgCode, ParamCnt>::Message() : _Dispose(TRUE)
{
	_Params = new Field[ParamCnt];
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
Message<TMessage, MsgCode, ParamCnt>::Message(RIFIELD param) : _Dispose(TRUE)
{
	_Params = new Field[ParamCnt];
	_Params[0] = param;
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
Message<TMessage, MsgCode, ParamCnt>::Message(PIFIELD params) : _Params(params) { }

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
Message<TMessage, MsgCode, ParamCnt>::~Message()
{
	if (_Params != NULL)
		delete[] _Params;
}


// OPERATORS

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
RCIFIELD Message<TMessage, MsgCode, ParamCnt>::operator[](CSIZE i) const
{
	return _Params[i];
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
RIFIELD Message<TMessage, MsgCode, ParamCnt>::operator[](CSIZE i)
{
	return this->Param(i);
}


// USER METHODS

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
RIFIELD Message<TMessage, MsgCode, ParamCnt>::Param(CSIZE i)
{
	if (_Params == NULL)
		return Field::NULL_OBJECT();

	return _Params[i];
}
				

// ISerializable IMPLEMENTATION

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
CSIZE Message<TMessage, MsgCode, ParamCnt>::Size() const
{
	return strlen(MESSAGE_MARKER) + SIZEOF(CBYTE) + SIZEOF(CSIZE) + this->ParamsSize();
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
CSIZE Message<TMessage, MsgCode, ParamCnt>::ByteWidth() const
{
	return strlen(MESSAGE_MARKER) + SIZEOF(CBYTE) + SIZEOF(CSIZE) + this->ParamsStringSize();
}
		
template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
PCBYTE Message<TMessage, MsgCode, ParamCnt>::ToBytes() const
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
	
	CSIZE paramsSize = this->ParamsSize();
	memcpy(bufferPtr, &paramsSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);

	PIFIELD param;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < this->PARAM_COUNT(); i++)
	{
		param = &_Params[i];
		paramSize = param->Size();

		memcpy(bufferPtr, param->ToBytes(), paramSize);
		bufferPtr += paramSize;
	}

	return __message_buffer;
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
PCCHAR Message<TMessage, MsgCode, ParamCnt>::ToString() const
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
	
	CSIZE paramsSize = this->ParamsStringSize();
	memcpy(bufferPtr, &paramsSize, SIZEOF(CSIZE));
	bufferPtr += SIZEOF(CSIZE);
	
	PIFIELD param;
	SIZE paramSize = 0;
	

	for (SIZE i = 0; i < this->PARAM_COUNT(); i++)
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

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
VOID Message<TMessage, MsgCode, ParamCnt>::LoadFromBytes(PCBYTE data)
{
	//_DataType = static_cast<DataType>(*data++);
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
VOID Message<TMessage, MsgCode, ParamCnt>::LoadFromString(PCCHAR data)
{
	LoadFromBytes(reinterpret_cast<PCBYTE>(data));
}


template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
SIZE Message<TMessage, MsgCode, ParamCnt>::printTo(Print& printer) const
{
	SIZE printed = printer.print(MESSAGE_MARKER);
	printed += printer.print(MsgCode);
	printed += printer.print(this->ParamsStringSize());
	
	for (SIZE i = 0; i < this->PARAM_COUNT(); i++)
		printed += _Params[i].printTo(printer);

	return printed;
}


// HELPER METHODS

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
CSIZE Message<TMessage, MsgCode, ParamCnt>::ParamsSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->PARAM_COUNT(); i++)
		size += _Params[i].Size();

	return size;
}

template<class TMessage, CBYTE MsgCode, CSIZE ParamCnt>
CSIZE Message<TMessage, MsgCode, ParamCnt>::ParamsStringSize() const
{
	SIZE size = 0;

	for (SIZE i = 0; i < this->PARAM_COUNT(); i++)
	{
		size += _Params[i].ByteWidth();

		if (_Params[i].GetDataType() == DataType::STRING_FIELD)
			--size;
	}

	return size;
}

#pragma endregion

#endif // #ifndef EXCLUDE_ITTYBITTY_MESSAGES
