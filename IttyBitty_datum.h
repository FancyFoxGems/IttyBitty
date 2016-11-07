/***********************************************************************************************
* [IttyBitty_datum.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE DATUM
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
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
	
// TODO
#include "IttyBitty_print.h"


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
	typedef ISerializable ISERIALIZABLE, * PISERIALIZABLE, & RISERIALIZABLE, ** PPISERIALIZABLE, && RRISERIALIZABLE;
	typedef const ISerializable CISERIALIZABLE, *PCISERIALIZABLE, & RCISERIALIZABLE, ** PPCISERIALIZABLE;

	class IDatum;
	typedef IDatum IDATUM, * PIDATUM, & RIDATUM, ** PPIDATUM, && RRIDATUM;
	typedef const IDatum CIDATUM, *PCIDATUM, & RCIDATUM, ** PPCIDATUM;

	template<typename TVal = CONSTVALUE>
	class DatumBase;
	template<typename TVal = CONSTVALUE>
	using DATUMBASE = DatumBase<TVal>;
	template<typename TVal = CONSTVALUE>
	using PDATUMBASE = DatumBase<TVal> *;
	template<typename TVal = CONSTVALUE>
	using RDATUMBASE = DatumBase<TVal> &;
	template<typename TVal = CONSTVALUE>
	using PPDATUMBASE = DatumBase<TVal> **;
	template<typename TVal = CONSTVALUE>
	using RRDATUMBASE = DatumBase<TVal> &&;
	template<typename TVal = CONSTVALUE>
	using CDATUMBASE = const DatumBase<TVal>;
	template<typename TVal = CONSTVALUE>
	using PCDATUMBASE = const DatumBase<TVal> *;
	template<typename TVal = CONSTVALUE>
	using RCDATUMBASE = const DatumBase<TVal> &;
	template<typename TVal = CONSTVALUE>
	using PPCDATUMBASE = const DatumBase<TVal> **;

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

	enum DataTypeFormat
	{
		UNSIGNED_DATA_TYPE	= 0x0,
		SIGNED_DATA_TYPE	= 0x1,
		SPECIAL_DATA_TYPE	= 0x2
	};

	enum DataType : BYTE
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

	INLINE DataSize DataTypeToDataSize(DataType dataType)
	{
		return static_cast<DataSize>(MASK(dataType, DATA_SIZE_MASK));
	}

#pragma endregion
	

#pragma region HELPER GLOBAL FUNCTION DECLARATIONS

	template<typename T>
	PCHAR StringInsertValue(CONST T, PCHAR, CBYTE = 0x10);
	
	template<typename T>
	PCCHAR StringReadValue(T &, PCCHAR, CBYTE = 0x10);

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
		VIRTUAL CSIZE ByteWidth() const = 0;
		VIRTUAL CSIZE StringLength() const = 0;

		VIRTUAL PCBYTE ToBinary() const = 0;
		VIRTUAL PCCHAR ToString() const = 0;

		VIRTUAL VOID FromBinary(PCBYTE) = 0;
		VIRTUAL VOID FromString(PCCHAR) = 0;
		
	#ifdef ARDUINO

		VIRTUAL BOOL Transmit(HardwareSerial & = SERIAL_PORT_HARDWARE) = 0;
		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & = Wire) = 0;

	#endif

	protected:

		ISerializable() { }
	};


	// [IDatum] DEFINITION

	INTERFACE IDatum : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IDatum() { }

		// INTERFACE METHODS

		VIRTUAL CONST DataSize GetDataSize() const = 0;
		VIRTUAL CONST DataType GetDataType() const = 0;

	protected:

		IDatum() { }
	};

#pragma endregion


#pragma region [DatumBase] DEFINITION - TAGGED UNION BASE
	
	template<typename TVal>
	CLASS DatumBase : public IDatum
	{
	public:

		// /DESTRUCTOR
		
		VIRTUAL ~DatumBase()
		{
			if (!_Dispose)
				return;

			// TODO
			PrintLine(F("~DatumBase"));

			if (_DataType == DataType::BYTES_DATUM || _DataType == DataType::STRING_DATUM || _DataType == DataType::BIT_DATUM)
				_Value.FreeData();
		}
		
		
		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const
		{
			return SIZEOF(CSIZE) + SIZEOF(DataType) + this->ByteWidth();
		}

		VIRTUAL CSIZE StringSize() const
		{
			return 2 * SIZEOF(CSIZE) + 2 * SIZEOF(DataType) + this->StringLength() + 1;
		}

		VIRTUAL CSIZE ByteWidth() const
		{
			return TRAILING_ZERO_BITS(static_cast<BYTE>(this->GetDataSize())) - 0x3;
		}
		VIRTUAL CSIZE StringLength() const
		{
			return 2 * this->ByteWidth();
		}

	#ifdef ARDUINO

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

			delete[] __datum_buffer;
			__datum_buffer = NULL;

			return size;
		}

	#endif


		// IDatum IMPLEMENTATION

		VIRTUAL CONST DataSize GetDataSize() const
		{
			return DataTypeToDataSize(_DataType);
		}

		VIRTUAL CONST DataType GetDataType() const
		{
			return _DataType;
		}
		

	protected:

		// INSTANCE VARIABLES
		
		BOOL _Dispose = FALSE;

		TVal _Value;
		DataType _DataType;
	};

#pragma endregion
};


#endif
