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


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES
	
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

	class DatumBase;
	typedef DatumBase DATUMBASE, * PDATUMBASE, & RDATUMBASE, ** PPDATUMBASE, && RRDATUMBASE;
	typedef const DatumBase CDATUMBASE, * PCDATUMBASE, & RCDATUMBASE, ** PPCDATUMBASE;

	class Datum;
	typedef Datum DATUM, * PDATUM, & RDATUM, ** PPDATUM, && RRDATUM;
	typedef const Datum CDATUM, * PCDATUM, & RCDATUM, ** PPCDATUM;

	class VarLengthDatum;
	typedef VarLengthDatum VARLENGTHDATUM, * PVARLENGTHDATUM, & RVARLENGTHDATUM, ** PPVARLENGTHDATUM, && RRVARLENGTHDATUM;
	typedef const VarLengthDatum CVARLENGTHDATUM, * PCVARLENGTHDATUM, & RCVARLENGTHDATUM, ** PPCVARLENGTHDATUM;

	template<typename T = BYTE>
	class TypedDatum;
	template<typename T = BYTE>
	using TYPEDDATUM = TypedDatum<T>;
	template<typename T = BYTE>
	using PTYPEDDATUM = TypedDatum<T> *;
	template<typename T = BYTE>
	using RTYPEDDATUM = TypedDatum<T> &;
	template<typename T = BYTE>
	using PPTYPEDDATUM = TypedDatum<T> **;
	template<typename T = BYTE>
	using RRTYPEDDATUM = TypedDatum<T> &&;
	template<typename T = BYTE>
	using CTYPEDDATUM = const TypedDatum<T>;
	template<typename T = BYTE>
	using PCTYPEDDATUM = const TypedDatum<T> *;
	template<typename T = BYTE>
	using RCTYPEDDATUM = const TypedDatum<T> &;
	template<typename T = BYTE>
	using PPCTYPEDDATUM = const TypedDatum<T> **;

	template<typename T = PBYTE>
	class VarLengthTypedDatum;
	template<typename T = PBYTE>
	using VARLENGTHTYPEDDATUM = VarLengthTypedDatum<T>;
	template<typename T = PBYTE>
	using PVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T> *;
	template<typename T = PBYTE>
	using RVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T> &;
	template<typename T = PBYTE>
	using PPVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T> **;
	template<typename T = PBYTE>
	using RRVARLENGTHTYPEDDATUM = VarLengthTypedDatum<T> &&;
	template<typename T = PBYTE>
	using CVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T>;
	template<typename T = PBYTE>
	using PCVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T> *;
	template<typename T = PBYTE>
	using RCVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T> &;
	template<typename T = PBYTE>
	using PPCVARLENGTHTYPEDDATUM = const VarLengthTypedDatum<T> **;

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

	CLASS DatumBase : public IDatum
	{
	public:

		// /DESTRUCTOR

		VIRTUAL ~DatumBase();
		
		
		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE BinarySize() const;
		VIRTUAL CSIZE StringSize() const;
		VIRTUAL CSIZE ByteWidth() const;
		VIRTUAL CSIZE StringLength() const;

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

	#ifdef ARDUINO

		VIRTUAL BOOL Transmit(HardwareSerial & = SERIAL_PORT_HARDWARE);
		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & = Wire);
				
		VIRTUAL SIZE printTo(Print &) const;

	#endif


		// IDatum IMPLEMENTATION

		VIRTUAL CONST DataSize GetDataSize() const;
		VIRTUAL CONST DataType GetDataType() const;
		

	protected:

		// INSTANCE VARIABLES
		
		BOOL _Dispose = FALSE;

		ConstValue _Value;
		DataType _DataType;
	};

#pragma endregion


#pragma region [Datum] DEFINITION - TAGGED UNION

	CLASS Datum : public DatumBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT Datum(CONST DataType = DataType::BYTE_DATUM);

		Datum(RCDATUM);
		Datum(RRDATUM);

		EXPLICIT Datum(RCCONSTVALUE, CONST DataType = DataType::BYTE_DATUM);

		EXPLICIT Datum(RCCHAR);
		EXPLICIT Datum(RCBYTE);
		EXPLICIT Datum(RCBOOL);
		EXPLICIT Datum(RCSHORT);
		EXPLICIT Datum(RCWORD);
		EXPLICIT Datum(RCLONG);
		EXPLICIT Datum(RCDWORD);
		EXPLICIT Datum(RCFLOAT);


		// STATIC FUNCTIONS

		STATIC RDATUM NULL_OBJECT();
		
		
		// OPERATORS

		VIRTUAL RDATUM operator =(RCDATUM);
		VIRTUAL RDATUM operator =(RRDATUM);

		VIRTUAL RDATUM operator =(RCCONSTVALUE);

		VIRTUAL operator RCCHAR() const;
		VIRTUAL operator RCBYTE() const;
		VIRTUAL operator RCBOOL() const;
		VIRTUAL operator RCSHORT() const;
		VIRTUAL operator RCWORD() const;
		VIRTUAL operator RCLONG() const;
		VIRTUAL operator RCDWORD() const;
		VIRTUAL operator RCFLOAT() const;
	};

#pragma endregion


#pragma region VarLengthDatum DECLARATION - VARIABLE-LENGTH TAGGED UNION

	CLASS VarLengthDatum : public Datum
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT VarLengthDatum(CONST DataType = DataType::BYTES_DATUM, CSIZE = 0);

		VarLengthDatum(RCVARLENGTHDATUM);
		VarLengthDatum(RRVARLENGTHDATUM);

		EXPLICIT VarLengthDatum(RCCONSTVALUE, CONST DataType = DataType::BYTES_DATUM, CSIZE = 0);

		EXPLICIT VarLengthDatum(PCBYTE, CSIZE = 0);
		EXPLICIT VarLengthDatum(PCCHAR);
		EXPLICIT VarLengthDatum(PCBITPACK, CSIZE = 0);

		VIRTUAL ~VarLengthDatum();
		
		
		// OPERATORS

		VIRTUAL RVARLENGTHDATUM operator =(RCVARLENGTHDATUM);
		VIRTUAL RVARLENGTHDATUM operator =(RRVARLENGTHDATUM);
		
		VIRTUAL operator PCBYTE() const;
		VIRTUAL operator PCCHAR() const;
		VIRTUAL operator PCBITPACK() const;


		// Datum OVERRIDES

		VIRTUAL CSIZE ByteWidth() const final;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		

	protected:

		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region [TypedDatum] DEFINITION - TEMPLATED TAGGED UNION
	
	template<typename T>
	CLASS TypedDatum : public DatumBase
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		TypedDatum()
		{
			_Dispose = TRUE;

			_DataType = TypedDatum<T>::FindDataType();
		}

		TypedDatum(RCTYPEDDATUM<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		TypedDatum(RRTYPEDDATUM<T> other)
		{
			this->~DatumBase();
			new (this) TypedDatum<T>(other._Value);
		}

		TypedDatum(RCCONSTVALUE value)
		{
			_Value = value;
			_DataType = TypedDatum<T>::FindDataType();
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

		STATIC RTYPEDDATUM<T> NULL_OBJECT()
		{
			STATIC TypedDatum<T> NULL_TYPEDDATUM;
			return NULL_TYPEDDATUM;
		}
		
		
		// OPERATORS

		VIRTUAL RTYPEDDATUM<T> operator =(RCTYPEDDATUM<T> rValue)
		{
			*this = TypedDatum<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDDATUM<T> operator =(RRTYPEDDATUM<T> rValue)
		{
			*this = TypedDatum<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDDATUM<T> operator =(RCCONSTVALUE rValue)
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

	template<>
	class TypedDatum<CHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::CHAR_DATUM;
			}
	};

	template<>
	class TypedDatum<BYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTE_DATUM;
			}
	};

	template<>
	class TypedDatum<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BOOL_DATUM;
			}
	};

	template<>
	class TypedDatum<SHORT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::SHORT_DATUM;
			}
	};

	template<>
	class TypedDatum<WORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::WORD_DATUM;
			}
	};

	template<>
	class TypedDatum<LONG>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::LONG_DATUM;
			}
	};

	template<>
	class TypedDatum<DWORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::DWORD_DATUM;
			}
	};

	template<>
	class TypedDatum<FLOAT>
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

	template<typename T>
	PCCHAR StringReadValue(T &, PCCHAR, CBYTE = 0x10);

	template<typename T>
	CLASS VarLengthTypedDatum : public TypedDatum<T>
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		VarLengthTypedDatum(CSIZE length = 0) : TypedDatum<T>()
		{
			_Value = new T[length];
			_DataType = VarLengthTypedDatum<T>::FindDataType();
			_Length = length;
		}

		VarLengthTypedDatum(RCVARLENGTHTYPEDDATUM<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
			_Length = other._Length;
		}

		VarLengthTypedDatum(RRVARLENGTHTYPEDDATUM<T> other)
		{
			this->~VarLengthTypedDatum<T>();
			new (this) VarLengthTypedDatum<T>(other._Value);
		}

		VarLengthTypedDatum(RCCONSTVALUE value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = VarLengthTypedDatum<T>::FindDataType();

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
			new (this) VarLengthTypedDatum<T>(value);
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

			return DatumBase::ByteWidth();
		}
		
		VIRTUAL VOID FromBinary(PCBYTE data) final
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
			DatumBase::FromBinary(data);
		}
		
		VIRTUAL VOID FromString(PCCHAR data) final
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			DatumBase::FromString(data);
			
			// TODO
			//bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
	
			//BYTE bytes[this->ByteWidth()];

			//for (BYTE i = 0; i < this->ByteWidth(); i++)
			//	bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);
		}


	protected:

		using TypedDatum<T>::_Dispose;
		using TypedDatum<T>::_Value;
		using TypedDatum<T>::_DataType;
		using TypedDatum<T>::IttyBitty::__datum_buffer;

		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return TypedDatum<T>::FindDataType();
		}


		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region VarLengthTypedDatum PARTIAL SPECIALIZATIONS

	template<>
	class VarLengthTypedDatum<PBYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTES_DATUM;
			}
	};

	template<>
	class VarLengthTypedDatum<PCHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::STRING_DATUM;
			}
	};

	template<>
	class VarLengthTypedDatum<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BIT_DATUM;
			}
	};

#pragma endregion
	

#pragma region HELPER METHODS

	template<typename T>
	INLINE PCHAR StringInsertValue(CONST T value, PCHAR buffer, CBYTE radix = 0x10)
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

	template<typename T>
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
	

#pragma region DATUM PARSING METHODS
	
	INLINE PIDATUM DatumFromBytes(PCBYTE data)
	{
		PIDATUM datum = NULL;

		SIZE length = static_cast<SIZE>(*data);

		if (length == 0 || length > 4)
			datum = new VarLengthDatum();
		else
			datum = new Datum();

		datum->FromBinary(data);

		return datum;
	}
	
	INLINE PIDATUM DatumFromString(PCCHAR data)
	{
		PIDATUM datum = NULL;
		SIZE length = 0;

		StringReadValue<SIZE>(length, data);

		if (length == 0 || length > 4)
			datum = new VarLengthDatum();
		else
			datum = new Datum();

		datum->FromString(data);

		return datum;
	}

#pragma endregion
}


#endif
