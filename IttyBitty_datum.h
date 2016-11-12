/***********************************************************************************************
* [IttyBitty_datum.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE DATUM
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_DATUM_H
#define _ITTYBITTY_DATUM_H


#ifdef ARDUINO
	#include "Printable.h"
	#include "HardwareSerial.h"
	#include "Wire.h"
#endif

#include "IttyBitty_values.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANT & VARIABLE DECLARATIONS

#ifdef ARDUINO
	EXTERN CWORD SERIAL_DEFAULT_TIMEOUT_MS;
#endif

	EXTERN CBYTE DATA_SIZE_MASK;

	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __datum_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class ISerializable;
	TYPEDEF_CLASS_ALIASES(ISerializable, ISERIALIZABLE);

#ifdef ARDUINO

	class ITransmittable;
	TYPEDEF_CLASS_ALIASES(ITransmittable, ITRANSMITTABLE);

#endif

	class IDatum;
	TYPEDEF_CLASS_ALIASES(IDatum, IDATUM);


	#define DATUMBASE_T_CLAUSE_DEF	<typename TVal>
	#define DATUMBASE_T_CLAUSE		<typename TVal = CONSTVALUE>
	#define DATUMBASE_T_ARGS		<TVal>

	template DATUMBASE_T_CLAUSE
	class DatumBase;
	TEMPLATE_CLASS_USING_ALIASES(CSL(DATUMBASE_T_CLAUSE), CSL(DATUMBASE_T_ARGS), DatumBase, DATUMBASE);

#pragma endregion


#pragma region ENUMS

	enum DataSize : BYTE
	{
		WHO_KNOWS	= 0x0,
		ONE_BYTE	= 0x10,
		TWO_BYTES	= 0x20,
		THREE_BYTES	= 0x40,
		FOUR_BYTES	= 0x80
	};

	TYPEDEF_ENUM_ALIASES(DataSize, DATASIZE);


	enum DataTypeFormat : BYTE
	{
		UNSIGNED_DATA_TYPE	= 0x0,
		SIGNED_DATA_TYPE	= 0x1,
		SPECIAL_DATA_TYPE	= 0x2
	};

	TYPEDEF_ENUM_ALIASES(DataTypeFormat, DATATYPEFORMAT);


	ENUM DataType : BYTE
	{
		BYTES_DATUM		= WHO_KNOWS | UNSIGNED_DATA_TYPE,
		STRING_DATUM	= WHO_KNOWS | SIGNED_DATA_TYPE,
		BIT_DATUM		= WHO_KNOWS | SPECIAL_DATA_TYPE,

		BYTE_DATUM		= ONE_BYTE | UNSIGNED_DATA_TYPE,
		CHAR_DATUM		= ONE_BYTE | SIGNED_DATA_TYPE,
		BOOL_DATUM		= ONE_BYTE | SPECIAL_DATA_TYPE,

		WORD_DATUM		= TWO_BYTES | UNSIGNED_DATA_TYPE,
		SHORT_DATUM		= TWO_BYTES | SIGNED_DATA_TYPE,

		DWORD_DATUM		= FOUR_BYTES | UNSIGNED_DATA_TYPE,
		LONG_DATUM		= FOUR_BYTES | SIGNED_DATA_TYPE,
		FLOAT_DATUM		= FOUR_BYTES | SPECIAL_DATA_TYPE
	};

	TYPEDEF_ENUM_ALIASES(DataType, DATATYPE);


	INLINE CDATASIZE DataTypeToDataSize(CDATATYPE dataType)
	{
		return static_cast<CDATASIZE>(MASK((CBYTE)dataType, DATA_SIZE_MASK));
	}

#pragma endregion


#pragma region HELPER GLOBAL FUNCTION DEFINITIONS

	template DEFAULT_T_CLAUSE
	INLINE PCHAR StringInsertValue(CONST T & value, PCHAR buffer, CBYTE radix = 0x10)
	{
		CHAR valStr[2 * T_SIZE + 1];

		valStr[2 * T_SIZE] = '\0';

		itoa(value, valStr, radix);

		BYTE lenDiff = 2 * T_SIZE - strlen(valStr);
		for (SIZE i = 0; i < lenDiff; i++)
		{
			valStr[i + lenDiff] = valStr[i];
			valStr[i] = '0';
		}

		memcpy(buffer, valStr, 2 * T_SIZE);

		return (PCHAR)(buffer + 2 * T_SIZE);
	}

	template DEFAULT_T_CLAUSE
	INLINE PCCHAR StringReadValue(T & value, PCCHAR data, CBYTE radix = 0x10)
	{
		CHAR valStr[2 * T_SIZE + 1];

		valStr[2 * T_SIZE] = '\0';

		memcpy(valStr, data, 2 * T_SIZE);
		valStr[2 * T_SIZE] = '\0';

		value = static_cast<T>(strtol(valStr, NULL, 0x10));

		return (PCCHAR)(data + 2 * T_SIZE);
	}

#pragma endregion


#pragma region INTERFACE DEFINITIONS

	// [ISerializable] DEFINITION

	INTERFACE ISerializable
	#ifdef ARDUINO
		: public Printable
	#endif
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~ISerializable() { }


		// INTERFACE METHODS

		VIRTUAL CSIZE BinarySize() const = 0;
		VIRTUAL CSIZE StringSize() const = 0;

		VIRTUAL PCBYTE ToBinary() const = 0;
		VIRTUAL PCCHAR ToString() const = 0;

		VIRTUAL VOID FromBinary(PCBYTE) = 0;
		VIRTUAL VOID FromString(PCCHAR) = 0;


	protected:

		// HELPER METHODS

		VIRTUAL VOID FreeBuffer() const = 0;


		ISerializable() { }
	};



#ifdef ARDUINO

	// [ITransmittable] DEFINITION

	INTERFACE ITransmittable : public ISerializable
	{
	public:

		// INTERFACE METHODS

		VIRTUAL BOOL Transmit(HardwareSerial & = SERIAL_PORT_HARDWARE) = 0;
		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & = Wire) = 0;
	};

#endif


	// [IDatum] DEFINITION

	INTERFACE IDatum : public ITransmittable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDatum() { }

		// INTERFACE METHODS

		VIRTUAL CSIZE ByteWidth() const = 0;
		VIRTUAL CSIZE StringLength() const = 0;

		VIRTUAL CDATASIZE GetDataSize() const = 0;
		VIRTUAL CDATATYPE GetDataType() const = 0;


	protected:

		IDatum() { }
	};

#pragma endregion


#pragma region [DatumBase] DEFINITION - TAGGED UNION BASE

	template DATUMBASE_T_CLAUSE_DEF
	CLASS DatumBase : public IDatum
	{
	public:

		// /DESTRUCTOR

		VIRTUAL ~DatumBase()
		{
			if (_Dispose && (_DataType == DataType::BYTES_DATUM
					|| _DataType == DataType::STRING_DATUM || _DataType == DataType::BIT_DATUM))
				_Value.FreeData();
			else
				_Value.FreeReference();
		}


		// [ISerializable] IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const
		{
			return SIZEOF(CSIZE) + SIZEOF(DataType) + this->ByteWidth();
		}

		VIRTUAL CSIZE StringSize() const
		{
			return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(DataType) + this->StringLength() + 1;
		}

	#ifdef ARDUINO

		VIRTUAL SIZE printTo(Print & printer) const
		{
		#ifdef _DEBUG
			SIZE size = this->StringSize();
			PCCHAR buffer = this->ToString();
		#else
			SIZE size = this->BinarySize();
			PCBYTE buffer = this->ToBinary();
		#endif

			for (SIZE i = 0; i < size; i++)
				printer.print(buffer[i]);

			this->FreeBuffer();

			return size;
		}


		// [ITransmittable] IMPLEMENTATION

		VIRTUAL BOOL Transmit(HardwareSerial & serial = SERIAL_PORT_HARDWARE)
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

		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & twi = Wire)
		{
			twi.beginTransmission(i2cAddr);

			if (!this->printTo(twi))
				return FALSE;

			twi.flush();

			if (twi.endTransmission())
				return FALSE;

			return TRUE;
		}

	#endif


		// [IDatum] IMPLEMENTATION

		VIRTUAL CSIZE ByteWidth() const
		{
			return TRAILING_ZERO_BITS(static_cast<BYTE>(this->GetDataSize())) - 0x3;
		}

		VIRTUAL CSIZE StringLength() const
		{
			return 2 * this->ByteWidth();
		}

		VIRTUAL CDATASIZE GetDataSize() const
		{
			return DataTypeToDataSize(_DataType);
		}

		VIRTUAL CDATATYPE GetDataType() const
		{
			return _DataType;
		}


	protected:

		// INSTANCE VARIABLES

		BOOL _Dispose = FALSE;

		TVal _Value;
		DATATYPE _DataType;


		// [ISerializable] HELPER METHODS

		VIRTUAL VOID FreeBuffer() const
		{
			if (!__datum_buffer)
				return;

			delete[] __datum_buffer;
			__datum_buffer = NULL;
		}
	};

#pragma endregion
};


#endif
