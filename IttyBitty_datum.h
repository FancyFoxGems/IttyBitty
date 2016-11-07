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

	template<typename TVal = CONSTVALUE>
	class Datum;
	template<typename TVal = CONSTVALUE>
	using DATUM = Datum<TVal>;
	template<typename TVal = CONSTVALUE>
	using PDATUM = Datum<TVal> *;
	template<typename TVal = CONSTVALUE>
	using RDATUM = Datum<TVal> &;
	template<typename TVal = CONSTVALUE>
	using PPDATUM = Datum<TVal> **;
	template<typename TVal = CONSTVALUE>
	using RRDATUM = Datum<TVal> &&;
	template<typename TVal = CONSTVALUE>
	using CDATUM = const Datum<TVal>;
	template<typename TVal = CONSTVALUE>
	using PCDATUM = const Datum<TVal> *;
	template<typename TVal = CONSTVALUE>
	using RCDATUM = const Datum<TVal> &;
	template<typename TVal = CONSTVALUE>
	using PPCDATUM = const Datum<TVal> **;

	template<typename TVal = CONSTVALUE>
	class VarLengthDatum;
	template<typename TVal = CONSTVALUE>
	using VARLENGTHDATUM = VarLengthDatum<TVal>;
	template<typename TVal = CONSTVALUE>
	using PVARLENGTHDATUM = VarLengthDatum<TVal> *;
	template<typename TVal = CONSTVALUE>
	using RVARLENGTHDATUM = VarLengthDatum<TVal> &;
	template<typename TVal = CONSTVALUE>
	using PPVARLENGTHDATUM = VarLengthDatum<TVal> **;
	template<typename TVal = CONSTVALUE>
	using RRVARLENGTHDATUM = VarLengthDatum<TVal> &&;
	template<typename TVal = CONSTVALUE>
	using CVARLENGTHDATUM = const VarLengthDatum<TVal>;
	template<typename TVal = CONSTVALUE>
	using PCVARLENGTHDATUM = const VarLengthDatum<TVal> *;
	template<typename TVal = CONSTVALUE>
	using RCVARLENGTHDATUM = const VarLengthDatum<TVal> &;
	template<typename TVal = CONSTVALUE>
	using PPCVARLENGTHDATUM = const VarLengthDatum<TVal> **;

	template<typename T = BYTE, typename TVal = CONSTVALUE>
	class TypedDatum;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using TYPEDDATUM = TypedDatum<T, TVal>;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using PTYPEDDATUM = TypedDatum<T, TVal> *;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using RTYPEDDATUM = TypedDatum<T, TVal> &;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using PPTYPEDDATUM = TypedDatum<T, TVal> **;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using RRTYPEDDATUM = TypedDatum<T, TVal> &&;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using CTYPEDDATUM = const TypedDatum<T, TVal>;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using PCTYPEDDATUM = const TypedDatum<T, TVal> *;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using RCTYPEDDATUM = const TypedDatum<T, TVal> &;
	template<typename T = BYTE, typename TVal = CONSTVALUE>
	using PPCTYPEDDATUM = const TypedDatum<T, TVal> **;

	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	class VarLengthTypedDatum;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using VARLENGTHTYPEDDATUM = VarLengthTypedDatum<T, TVal>;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using PVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T, TVal> *;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using RVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T, TVal> &;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using PPVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T, TVal> **;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using RRVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T, TVal> &&;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using CVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T, TVal>;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using PCVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T, TVal> *;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using RCVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T, TVal> &;
	template<typename T = PBYTE, typename TVal = CONSTVALUE>
	using PPCVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T, TVal> **;

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
	

#pragma region DATUM PARSING GLOBAL FUNCTION DECLARATIONS
	
	template<typename TVal = CONSTVALUE>
	PIDATUM DatumFromBytes(PCBYTE);
	
	template<typename TVal = CONSTVALUE>
	PIDATUM DatumFromString(PCCHAR);

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

		VIRTUAL PCBYTE ToBinary() const
		{
			CSIZE size = this->BinarySize();

			if (__datum_buffer)
				delete[] __datum_buffer;

			__datum_buffer = new BYTE[size];

			PBYTE bufferPtr = __datum_buffer;
	
			CSIZE byteWidth = this->ByteWidth();
			memcpy(bufferPtr, &byteWidth, SIZEOF(byteWidth));
			bufferPtr += SIZEOF(byteWidth);

			memcpy(bufferPtr, &_DataType, SIZEOF(DataType));
			bufferPtr += SIZEOF(DataType);

			if (byteWidth > 0)
				memcpy(bufferPtr, _Value.Bytes, this->ByteWidth());

			return __datum_buffer;
		}

		VIRTUAL PCCHAR ToString() const
		{
			CSIZE size = this->StringSize();
			CSIZE byteWidth = this->ByteWidth();
	
			if (__datum_buffer)
				delete[] __datum_buffer;

			__datum_buffer = new BYTE[size];
			__datum_buffer[size - 1] = '\0';

			PCHAR bufferPtr = reinterpret_cast<PCHAR>(__datum_buffer);

			bufferPtr = StringInsertValue<CSIZE>(byteWidth, bufferPtr);
			bufferPtr = StringInsertValue<CBYTE>(static_cast<CBYTE>(this->GetDataType()), bufferPtr);

			PCBYTE bytes = NULL;

			switch (_DataType)
			{
			case DataType::BYTE_DATUM:
			case DataType::CHAR_DATUM:
			case DataType::BOOL_DATUM:

				bytes = (PBYTE)&(_Value.Byte);
				break;
		
			case DataType::WORD_DATUM:
			case DataType::SHORT_DATUM:
		

				bytes = (PBYTE)&(_Value.Word);
				break;
			
			case DataType::DWORD_DATUM:
			case DataType::LONG_DATUM:	
			case DataType::FLOAT_DATUM:

				bytes = (PBYTE)&(_Value.DWord);
				break;

			default:

				bytes = _Value.Bytes;

				for (SIZE i = 0; i < byteWidth; i++)
					bufferPtr = StringInsertValue<CBYTE>(bytes[i], bufferPtr);

				return reinterpret_cast<PCCHAR>(__datum_buffer);
			}
	
			for (SIZE i = 0; i < 4 - byteWidth; i++)
				bufferPtr = StringInsertValue<CBYTE>(bytes[byteWidth - i - 1], bufferPtr);
	
			return reinterpret_cast<PCCHAR>(__datum_buffer);
		}

		VIRTUAL VOID FromBinary(PCBYTE data)
		{
			PCBYTE bufferPtr = data;

			bufferPtr += SIZEOF(CSIZE);

			_DataType = static_cast<DataType>(*bufferPtr++);

			switch (_DataType)
			{
			case DataType::BYTE_DATUM:
			case DataType::CHAR_DATUM:
			case DataType::BOOL_DATUM:

				_Value = *((PBYTE)bufferPtr);
				break;
		
			case DataType::WORD_DATUM:
			case DataType::SHORT_DATUM:
		

				_Value = *((PWORD)bufferPtr);
				break;
		
			case DataType::DWORD_DATUM:
			case DataType::LONG_DATUM:		
			case DataType::FLOAT_DATUM:

				_Value = *((PDWORD)bufferPtr);
				break;

			default:

				_Value = data;
			}
		}

		VIRTUAL VOID FromString(PCCHAR data)
		{
			PCCHAR bufferPtr = data;

			bufferPtr += 2 * SIZEOF(CSIZE);

			bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);

			CBYTE byteWidth = this->ByteWidth();

			PBYTE bytes = NULL;
	
			switch (_DataType)
			{
			case DataType::BYTE_DATUM:
			case DataType::CHAR_DATUM:
			case DataType::BOOL_DATUM:

				bytes = (PBYTE)&(_Value.Byte);
				break;
		
			case DataType::WORD_DATUM:
			case DataType::SHORT_DATUM:		

				bytes = (PBYTE)&(_Value.Word);
				break;
		
			case DataType::DWORD_DATUM:
			case DataType::LONG_DATUM:		
			case DataType::FLOAT_DATUM:

				bytes = (PBYTE)&(_Value.DWord);
				break;

			default:
		
				for (BYTE i = 0; i < byteWidth; i++)
					bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);

				_Value = bytes;

				return;
			}
	
			for (SIZE i = 0 ; i < byteWidth; i++)
				bufferPtr = StringReadValue<BYTE>(bytes[byteWidth - i - 1], bufferPtr);
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


#pragma region [Datum] DEFINITION - TAGGED UNION
	
	template<typename TVal>
	CLASS Datum : public DatumBase<TVal>
	{
	protected:

		// TYPEDEF ALIASES
		typedef TVal TVAL, * PTVAL, & RTVAL;
		typedef const TVal CTVAL, * PCTVAL, & RCTVAL;

		using DatumBase<TVal>::_Dispose;
		using DatumBase<TVal>::_Value;
		using DatumBase<TVal>::_DataType;
		using DatumBase<TVal>::IttyBitty::__datum_buffer;


	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT Datum(CONST DataType dataType = DataType::BYTE_DATUM)
		{
			_Dispose = TRUE;
	
			_DataType = dataType;
		}

		Datum(RCDATUM<TVal> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		Datum(RRDATUM<TVal> other)
		{
			this->~DatumBase();
			new (this) Datum(other._Value, other._DataType);
		}

		EXPLICIT Datum(TVAL value, CONST DataType dataType = DataType::BYTE_DATUM)
		{
			_Value = value;
			_DataType = dataType;
		}

		EXPLICIT Datum(RCCHAR value)
		{
			_Value = value;
			_DataType = DataType::CHAR_DATUM;
		}

		EXPLICIT Datum(RCBYTE value)
		{
			_Value = value;
			_DataType = DataType::BYTE_DATUM;
		}

		EXPLICIT Datum(RCBOOL value)
		{
			_Value = value;
			_DataType = DataType::BOOL_DATUM;
		}

		EXPLICIT Datum(RCSHORT value)
		{
			_Value = value;
			_DataType = DataType::SHORT_DATUM;
		}

		EXPLICIT Datum(RCWORD value)
		{
			_Value = value;
			_DataType = DataType::WORD_DATUM;
		}

		EXPLICIT Datum(RCLONG value)
		{
			_Value = value;
			_DataType = DataType::LONG_DATUM;
		}

		EXPLICIT Datum(RCDWORD value)
		{
			_Value = value;
			_DataType = DataType::DWORD_DATUM;
		}

		EXPLICIT Datum(RCFLOAT value)
		{
			_Value = value;
			_DataType = DataType::FLOAT_DATUM;
		}

		
		// STATIC FUNCTIONS

		STATIC RDATUM<TVal> NULL_OBJECT()
		{
			STATIC Datum NULL_DATUM;
			return NULL_DATUM;
		}
		
		
		// OPERATORS

		VIRTUAL RDATUM<TVal> operator =(RCDATUM<TVal> rValue)
		{
			*this = Datum(rValue);
			return *this;
		}

		VIRTUAL RDATUM<TVal> operator =(RRDATUM<TVal> rValue)
		{
			*this = Datum(rValue);
			return *this;
		}

		VIRTUAL RDATUM<TVal> operator =(RCCONSTVALUE rValue)
		{
			_Value = rValue;
			return *this;
		}

		VIRTUAL operator RCCHAR() const
		{
			return _Value;
		}

		VIRTUAL operator RCBYTE() const
		{
			return _Value;
		}

		VIRTUAL operator RCBOOL() const
		{
			return _Value;
		}

		VIRTUAL operator RCSHORT() const
		{
			return _Value;
		}

		VIRTUAL operator RCWORD() const
		{
			return _Value;
		}

		VIRTUAL operator RCLONG() const
		{
			return _Value;
		}

		VIRTUAL operator RCDWORD() const
		{
			return _Value;
		}

		VIRTUAL operator RCFLOAT() const
		{
			return _Value;
		}
	};

#pragma endregion


#pragma region VarLengthDatum DECLARATION - VARIABLE-LENGTH TAGGED UNION
	
	template<typename TVal>
	CLASS VarLengthDatum : public Datum<TVal>
	{
	protected:
		
		using Datum<TVal>::_Dispose;
		using Datum<TVal>::_Value;
		using Datum<TVal>::_DataType;
		using Datum<TVal>::IttyBitty::__datum_buffer;

		// INSTANCE VARIABLES

		SIZE _Length = 0;


	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT VarLengthDatum(CONST DataType dataType = DataType::BYTES_DATUM, CSIZE length = 0)
			: Datum<TVal>(dataType), _Length(length)
		{
			switch (dataType)
			{
			case DataType::BYTES_DATUM:

				_Value = new BYTE[length];
				break;

			case DataType::STRING_DATUM:

				_Value = new CHAR[length];
				break;

			case DataType::BIT_DATUM:

				_Value = new BITPACK[length];
				break;

			default:
				break;
			}
		}

		VarLengthDatum(RCVARLENGTHDATUM<TVal> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
			_Length = other._Length;
		}

		VarLengthDatum(RRVARLENGTHDATUM<TVal> other)
		{
			this->~VarLengthDatum<TVal>();
			new (this) VarLengthDatum<TVal>(other._Value, other._DataType, other._Length);
		}

		EXPLICIT VarLengthDatum(CONST TVal & value, CONST DataType dataType = DataType::BYTES_DATUM, CSIZE length = 0) 
			: Datum<TVal>(value, dataType)
		{
			if (_DataType == DataType::STRING_DATUM)
			{
				if (value.String == NULL)
					_Length = 0;
				else
					_Length = strlen((PCCHAR)_Value);
			}
			else
			{
				_Length = length;
			}
		}

		EXPLICIT VarLengthDatum(PCBYTE value, CSIZE length) 
			: Datum<TVal>(DataType::BYTES_DATUM), _Length(length)
		{
			_Dispose = FALSE;

			_Value = value;
		}

		EXPLICIT VarLengthDatum(PCCHAR value) 
			: Datum<TVal>(DataType::STRING_DATUM)
		{
			_Dispose = FALSE;
	
			_Value = value;

			if (value == NULL)
				_Length = 0;
			else
				_Length = strlen(value);
		}

		EXPLICIT VarLengthDatum(PCBITPACK value, CSIZE length) 
			: Datum<TVal>(DataType::BIT_DATUM), _Length(length)
		{
			_Dispose = FALSE;

			_Value = value;
		}

		VIRTUAL ~VarLengthDatum()
		{
			if (!_Dispose)
				return;
	
			//if (_Length > 0 || _DataType == DataType::STRING_DATUM)
			//	_Value.FreeData();
		}		
		
		// OPERATORS

		VIRTUAL RVARLENGTHDATUM<TVal> operator =(RCVARLENGTHDATUM<TVal> rValue)
		{
			*this = VarLengthDatum<TVal>(rValue);
			return *this;
		}

		VIRTUAL RVARLENGTHDATUM<TVal> operator =(RRVARLENGTHDATUM<TVal> rValue)
		{
			*this = VarLengthDatum<TVal>(rValue);
			return *this;
		}
		
		VIRTUAL operator PCBYTE() const
		{
			return _Value;
		}

		VIRTUAL operator PCCHAR() const
		{
			return _Value;
		}

		VIRTUAL operator PCBITPACK() const
		{
			return _Value;
		}

		// Datum OVERRIDES

		VIRTUAL CSIZE ByteWidth() const final
		{
			if (_Length > 0)
				return _Length;

			return DatumBase<TVal>::ByteWidth();
		}

		VIRTUAL VOID FromBinary(PCBYTE data)
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
			DatumBase<TVal>::FromBinary(data);
		}
		
		VIRTUAL VOID FromString(PCCHAR data)
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			DatumBase<TVal>::FromString(data);

			// TODO
			//PCCHAR bufferPtr = data;

			//bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			//CBYTE byteWidth = this->ByteWidth();

			//PBYTE bytes = NULL;

			//switch (_DataType)
			//{
			//case DataType::BYTE_DATUM:
			//case DataType::CHAR_DATUM:
			//case DataType::BOOL_DATUM:

			//	bytes = (PBYTE)&(_Value.Byte);
			//	break;
			//	
			//case DataType::WORD_DATUM:
			//case DataType::SHORT_DATUM:
			//	

			//	bytes = (PBYTE)&(_Value.Word);
			//	break;
			//	
			//case DataType::FLOAT_DATUM:
			//case DataType::LONG_DATUM:		
			//case DataType::DWORD_DATUM:

			//	bytes = (PBYTE)&(_Value.DWord);
			//	break;

			//default:

			//	for (BYTE i = 0; i < byteWidth; i++)
			//		bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);

			//	_Value = bytes;

			//	return;
			//}
			//
			//for (SIZE i = 0 ; i < byteWidth; i++)
			//	bufferPtr = StringReadValue<BYTE>(bytes[byteWidth - i - 1], bufferPtr);
		}
	};

#pragma endregion


#pragma region [TypedDatum] DEFINITION - TEMPLATED TAGGED UNION
	
	template<typename T, typename TVal>
	CLASS TypedDatum : public DatumBase<TVal>
	{
	protected:

		using DatumBase<TVal>::_Dispose;
		using DatumBase<TVal>::_Value;
		using DatumBase<TVal>::_DataType;
		using DatumBase<TVal>::IttyBitty::__datum_buffer;


	public:

		// CONSTRUYCTORS/DESTRUCTOR

		TypedDatum()
		{
			_Dispose = TRUE;

			_DataType = TypedDatum<T>::FindDataType();
		}

		TypedDatum(RCTYPEDDATUM<T, TVal> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		TypedDatum(RRTYPEDDATUM<T, TVal> other)
		{
			this->~DatumBase();
			new (this) TypedDatum<T, TVal>(other._Value);
		}

		TypedDatum(CONST TVal & value)
		{
			_Value = value;
			_DataType = TypedDatum<T, TVal>::FindDataType();
		}

		EXPLICIT TypedDatum(T & value)
		{
			this->~DatumBase();
			new (this) TypedDatum<T>(value);
		}

		EXPLICIT TypedDatum(SIGNED_TYPE(T &) value)
		{
			this->~DatumBase();
			new (this) TypedDatum<T>(value);
		}


		// STATIC METHODS

		STATIC RTYPEDDATUM<T, TVal> NULL_OBJECT()
		{
			STATIC TypedDatum<T, TVal> NULL_TYPEDDATUM;
			return NULL_TYPEDDATUM;
		}
		
		
		// OPERATORS

		VIRTUAL RTYPEDDATUM<T, TVal> operator =(RCTYPEDDATUM<T, TVal> rValue)
		{
			*this = TypedDatum<T, TVal>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDDATUM<T, TVal> operator =(RRTYPEDDATUM<T, TVal> rValue)
		{
			*this = TypedDatum<T, TVal>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDDATUM<T, TVal> operator =(CONST TVal & rValue)
		{
			_Value = rValue;
			return *this;
		}


		VIRTUAL operator UNSIGNED_TYPE(CONST T &)() const
		{
			return (UNSIGNED_TYPE(CONST T &))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(CONST T &)() const
		{
			return (SIGNED_TYPE(CONST T &))_Value;
		}


		// META-MEMBERS

		typedef T DatumType;


	protected:
		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return DataType::BYTE_DATUM;
		}
	};

#pragma endregion


#pragma region TypedDatum PARTIAL SPECIALIZATIONS

	template<typename TVal>
	class TypedDatum<CHAR, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::CHAR_DATUM;
			}
	};
	
	template<typename TVal>
	class TypedDatum<BYTE, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTE_DATUM;
			}
	};
	
	template<typename TVal>
	class TypedDatum<BOOL, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BOOL_DATUM;
			}
	};
	
	template<typename TVal>
	class TypedDatum<SHORT, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::SHORT_DATUM;
			}
	};
	
	template<typename TVal>
	class TypedDatum<WORD, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::WORD_DATUM;
			}
	};
	
	template<typename TVal>
	class TypedDatum<LONG, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::LONG_DATUM;
			}
	};

	template<typename TVal>
	class TypedDatum<DWORD, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::DWORD_DATUM;
			}
	};
	
	template<typename TVal>
	class TypedDatum<FLOAT, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::FLOAT_DATUM;
			}
	};

#pragma endregion

	
#pragma region [VarLengthTypedDatum] DEFINITION - TEMPLATED, VARIABLE-LENGTH TAGGED UNION

	template<typename T,  typename TVal>
	CLASS VarLengthTypedDatum : public TypedDatum<T, TVal>
	{
	protected:

		using TypedDatum<T, TVal>::_Dispose;
		using TypedDatum<T, TVal>::_Value;
		using TypedDatum<T, TVal>::_DataType;
		using TypedDatum<T, TVal>::IttyBitty::__datum_buffer;

		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return TypedDatum<T, TVal>::FindDataType();
		}


		// INSTANCE VARIABLES

		SIZE _Length = 0;


	public:

		// CONSTRUYCTORS/DESTRUCTOR

		VarLengthTypedDatum(CSIZE length = 0) : TypedDatum<T, TVal>()
		{
			_Value = new T[length];
			_DataType = VarLengthTypedDatum<T, TVal>::FindDataType();
			_Length = length;
		}

		VarLengthTypedDatum(RCVARLENGTHTYPEDDATUM<T, TVal> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
			_Length = other._Length;
		}

		VarLengthTypedDatum(RRVARLENGTHTYPEDDATUM<T, TVal> other)
		{
			this->~VarLengthTypedDatum<T, TVal>();
			new (this) VarLengthTypedDatum<T, TVal>(other._Value);
		}

		VarLengthTypedDatum(CONST TVal & value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = VarLengthTypedDatum<T, TVal>::FindDataType();

			if (_DataType == DataType::STRING_DATUM)
			{
				if (value.String == NULL)
					_Length = 0;
				else
					_Length = strlen((PCCHAR)_Value);
			}
			else
			{
				_Length = length;
			}
		}

		EXPLICIT VarLengthTypedDatum(T & value)
		{
			new (this) VarLengthTypedDatum<T, TVal>(value);
		}

		VIRTUAL ~VarLengthTypedDatum()
		{
			if (!_Dispose)
				return;

			//if (_Length > 0 || _DataType == DataType::STRING_DATUM)
			//	_Value.FreeData();
		}
		
		
		// OPERATORS

		VIRTUAL operator CONST T() const
		{
			return (CONST T)_Value;
		}

		VIRTUAL operator UNSIGNED_TYPE(T &)()
		{
			return (T)_Value;
		}


		//  IDatum OVERRIDES

		VIRTUAL CSIZE ByteWidth() const final
		{
			if (_Length > 0)
				return _Length;

			return DatumBase<TVal>::ByteWidth();
		}
		
		VIRTUAL VOID FromBinary(PCBYTE data) final
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
			DatumBase<TVal>::FromBinary(data);
		}
		
		VIRTUAL VOID FromString(PCCHAR data) final
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			DatumBase<TVal>::FromString(data);
			
			// TODO
			//bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
	
			//BYTE bytes[this->ByteWidth()];

			//for (BYTE i = 0; i < this->ByteWidth(); i++)
			//	bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);
		}
	};

#pragma endregion


#pragma region VarLengthTypedDatum PARTIAL SPECIALIZATIONS

	template<typename TVal>
	class VarLengthTypedDatum<PBYTE, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTES_DATUM;
			}
	};
	
	template<typename TVal>
	class VarLengthTypedDatum<PCHAR, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::STRING_DATUM;
			}
	};
	
	template<typename TVal>
	class VarLengthTypedDatum<BOOL, TVal>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BIT_DATUM;
			}
	};

#pragma endregion
};


#endif
