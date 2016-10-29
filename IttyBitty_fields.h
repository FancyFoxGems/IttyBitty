/***********************************************************************************************
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_FIELDS_H
#define _ITTYBITTY_FIELDS_H


		
#ifdef ARDUINO
	#include "Printable.h"
#endif

#include "IttyBitty_values.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES

	EXTERN CBYTE DATA_SIZE_MASK;
		
	// Field::ToBytes() / ToString() BUFFER POINTER
	EXTERN PBYTE __field_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class ISerializable;
	typedef ISerializable ISERIALIZABLE, * PISERIALIZABLE, & RISERIALIZABLE, ** PPISERIALIZABLE, && RRISERIALIZABLE;
	typedef const ISerializable CISERIALIZABLE, *PCISERIALIZABLE, & RCISERIALIZABLE, ** PPCISERIALIZABLE;

	class IField;
	typedef IField IFIELD, * PIFIELD, & RIFIELD, ** PPIFIELD, && RRIFIELD;
	typedef const IField CIFIELD, *PCIFIELD, & RCIFIELD, ** PPCIFIELD;

	class FieldBase;
	typedef FieldBase FIELDBASE, * PFIELDBASE, & RFIELDBASE, ** PPFIELDBASE, && RRFIELDBASE;
	typedef const FieldBase CFIELDBASE, * PCFIELDBASE, & RCFIELDBASE, ** PPCFIELDBASE;

	class Field;
	typedef Field FIELD, * PFIELD, & RFIELD, ** PPFIELD, && RRFIELD;
	typedef const Field CFIELD, * PCFIELD, & RCFIELD, ** PPCFIELD;

	class VarLengthFieldBase;
	typedef VarLengthFieldBase VARLENGTHFIELDBASE, * PVARLENGTHFIELDBASE, & RVARLENGTHFIELDBASE, ** PPVARLENGTHFIELDBASE, && RRVARLENGTHFIELDBASE;
	typedef const VarLengthFieldBase CVARLENGTHFIELDBASE, * PCVARLENGTHFIELDBASE, & RCVARLENGTHFIELDBASE, ** PPCVARLENGTHFIELDBASE;

	class VarLengthField;
	typedef VarLengthField VARLENGTHFIELD, * PVARLENGTHFIELD, & RVARLENGTHFIELD, ** PPVARLENGTHFIELD, && RRVARLENGTHFIELD;
	typedef const VarLengthField CVARLENGTHFIELD, * PCVARLENGTHFIELD, & RCVARLENGTHFIELD, ** PPCVARLENGTHFIELD;

	template<typename T = BYTE>
	class TypedField;
	template<typename T = BYTE>
	using TYPEDFIELD = TypedField<T>;
	template<typename T = BYTE>
	using PTYPEDFIELD = TypedField<T> *;
	template<typename T = BYTE>
	using RTYPEDFIELD = TypedField<T> &;
	template<typename T = BYTE>
	using PPTYPEDFIELD = TypedField<T> **;
	template<typename T = BYTE>
	using RRTYPEDFIELD = TypedField<T> &&;
	template<typename T = BYTE>
	using CTYPEDFIELD = const TypedField<T>;
	template<typename T = BYTE>
	using PCTYPEDFIELD = const TypedField<T> *;
	template<typename T = BYTE>
	using RCTYPEDFIELD = const TypedField<T> &;
	template<typename T = BYTE>
	using PPCTYPEDFIELD = const TypedField<T> **;

	template<typename T = PBYTE>
	class VarLengthTypedField;
	template<typename T = PBYTE>
	using VARLENGTHTYPEDFIELD = VarLengthTypedField<T>;
	template<typename T = PBYTE>
	using PVARLENGTHTYPEDFIELD = VarLengthTypedField<T> *;
	template<typename T = PBYTE>
	using RVARLENGTHTYPEDFIELD = VarLengthTypedField<T> &;
	template<typename T = PBYTE>
	using PPVARLENGTHTYPEDFIELD = VarLengthTypedField<T> **;
	template<typename T = PBYTE>
	using RRVARLENGTHTYPEDFIELD = VarLengthTypedField<T> &&;
	template<typename T = PBYTE>
	using CVARLENGTHTYPEDFIELD = const VarLengthTypedField<T>;
	template<typename T = PBYTE>
	using PCVARLENGTHTYPEDFIELD = const VarLengthTypedField<T> *;
	template<typename T = PBYTE>
	using RCVARLENGTHTYPEDFIELD = const VarLengthTypedField<T> &;
	template<typename T = PBYTE>
	using PPCVARLENGTHTYPEDFIELD = const VarLengthTypedField<T> **;

#pragma endregion


#pragma region ENUMS
	
	enum DataSize : BYTE
	{
		WHO_KNOWS	= 0x0,
		ONE_BYTE	= 0x10,
		TWO_BYTES	= 0x20,
		THREE_BYTES	= 0x40,
		FOUR_BYTES	= 0x80,
	};

	enum DataType : BYTE
	{
		BYTES_FIELD		= WHO_KNOWS | 0x0,
		STRING_FIELD	= WHO_KNOWS | 0x1,
		BIT_FIELD		= WHO_KNOWS | 0x2,

		BYTE_FIELD		= ONE_BYTE | 0x1,
		CHAR_FIELD		= ONE_BYTE | 0x2,
		BOOL_FIELD		= ONE_BYTE | 0x4,

		WORD_FIELD		= TWO_BYTES | 0x1,
		SHORT_FIELD		= TWO_BYTES | 0x2,

		DWORD_FIELD		= FOUR_BYTES | 0x1,
		LONG_FIELD		= FOUR_BYTES | 0x2,
		FLOAT_FIELD		= FOUR_BYTES | 0x4
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

		VIRTUAL CSIZE ByteSize() const = 0;
		VIRTUAL CSIZE StringSize() const = 0;
		VIRTUAL CSIZE ByteWidth() const = 0;
		VIRTUAL CSIZE StringLength() const = 0;

		VIRTUAL PCBYTE ToBytes() const = 0;
		VIRTUAL PCCHAR ToString() const = 0;

		VIRTUAL VOID FromBytes(PCBYTE) = 0;
		VIRTUAL VOID FromString(PCCHAR) = 0;

	protected:

		ISerializable() { }
	};


	// [IField] DEFINITION

	INTERFACE IField : public ISerializable
	{
	public:

		// DESTRUCTOR

		VIRTUAL ~IField() { }

		// INTERFACE METHODS

		VIRTUAL CONST DataSize GetDataSize() const = 0;
		VIRTUAL CONST DataType GetDataType() const = 0;

	protected:

		IField() { }
	};

#pragma endregion


#pragma region [FieldBase] DEFINITION - TAGGED UNION BASE

	CLASS FieldBase : public IField
	{
	public:

		// /DESTRUCTOR

		VIRTUAL ~FieldBase();
		
		
		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE ByteSize() const;
		VIRTUAL CSIZE StringSize() const;
		VIRTUAL CSIZE ByteWidth() const;
		VIRTUAL CSIZE StringLength() const;

		VIRTUAL PCBYTE ToBytes() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBytes(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
				
	#ifdef ARDUINO
		VIRTUAL SIZE printTo(Print &) const;
	#endif


		// IField IMPLEMENTATION

		VIRTUAL CONST DataSize GetDataSize() const;
		VIRTUAL CONST DataType GetDataType() const;
		

	protected:

		// INSTANCE VARIABLES
		
		BOOL _Dispose = FALSE;

		Value _Value;
		DataType _DataType;
	};

#pragma endregion


#pragma region [Field] DEFINITION - TAGGED UNION

	CLASS Field : public FieldBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		Field(CONST DataType = DataType::BYTE_FIELD);

		Field(RCFIELD);
		Field(RRFIELD);

		Field(RCVALUE, CONST DataType = DataType::BYTE_FIELD);

		EXPLICIT Field(RCCHAR);
		EXPLICIT Field(RCBYTE);
		EXPLICIT Field(RCBOOL);
		EXPLICIT Field(RCSHORT);
		EXPLICIT Field(RCWORD);
		EXPLICIT Field(RCLONG);
		EXPLICIT Field(RCDWORD);
		EXPLICIT Field(RCFLOAT);


		// STATIC FUNCTIONS

		STATIC RFIELD NULL_OBJECT();
		
		
		// OPERATORS

		VIRTUAL RFIELD operator =(RCFIELD);
		VIRTUAL RFIELD operator =(RRFIELD);

		VIRTUAL RFIELD operator =(RCVALUE);

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


#pragma region VarLengthField DECLARATION - VARIABLE-LENGTH TAGGED UNION

	CLASS VarLengthField : public Field
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		VarLengthField(CONST DataType = DataType::BYTES_FIELD, CSIZE = 0);

		VarLengthField(RCVARLENGTHFIELD);
		VarLengthField(RRVARLENGTHFIELD);

		VarLengthField(RCVALUE, CONST DataType = DataType::BYTES_FIELD, CSIZE = 0);

		EXPLICIT VarLengthField(PCBYTE, CSIZE = 0);
		EXPLICIT VarLengthField(PCCHAR);
		EXPLICIT VarLengthField(PCBITPACK, CSIZE = 0);

		VIRTUAL ~VarLengthField();
		
		
		// OPERATORS

		VIRTUAL RVARLENGTHFIELD operator =(RCVARLENGTHFIELD);
		VIRTUAL RVARLENGTHFIELD operator =(RRVARLENGTHFIELD);
		
		VIRTUAL operator PCBYTE() const;
		VIRTUAL operator PCCHAR() const;
		VIRTUAL operator PCBITPACK() const;


		// Field OVERRIDES

		CSIZE ByteSize() const;				
		CSIZE StringSize() const;
		CSIZE ByteWidth() const;
		CSIZE StringLength() const;

		VOID FromBytes(PCBYTE);
		VOID FromString(PCCHAR);
		

	protected:

		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region [TypedField] DEFINITION - TEMPLATED TAGGED UNION
	
	template<typename T>
	CLASS TypedField : public FieldBase
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		TypedField()
		{
			_Dispose = TRUE;

			_DataType = TypedField<T>::FindDataType();
		}

		TypedField(RCTYPEDFIELD<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		TypedField(RRTYPEDFIELD<T> other)
		{
			this->~FieldBase();
			new (this) TypedField<T>(other._Value);
		}

		TypedField(RCVALUE value)
		{
			_Value = value;
			_DataType = TypedField<T>::FindDataType();
		}

		EXPLICIT TypedField(T & value)
		{
			this->~FieldBase();
			new (this) TypedField<T>(value);
		}

		EXPLICIT TypedField(SIGNED_TYPE(T &) value)
		{
			this->~FieldBase();
			new (this) TypedField<T>(value);
		}


		// STATIC METHODS

		STATIC RTYPEDFIELD<T> NULL_OBJECT()
		{
			STATIC TypedField<T> NULL_TYPEDFIELD;
			return NULL_TYPEDFIELD;
		}
		
		
		// OPERATORS

		VIRTUAL RTYPEDFIELD<T> operator =(RCTYPEDFIELD<T> rValue)
		{
			*this = TypedField<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDFIELD<T> operator =(RRTYPEDFIELD<T> rValue)
		{
			*this = TypedField<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDFIELD<T> operator =(RCVALUE rValue)
		{
			_Value = rValue;
			return *this;
		}


		VIRTUAL operator UNSIGNED_TYPE(CONST T&)() const
		{
			return (UNSIGNED_TYPE(CONST T&))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(CONST T&)() const
		{
			return (SIGNED_TYPE(CONST T&))_Value;
		}


		// META-MEMBERS

		typedef T FieldType;


	protected:
		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return DataType::BYTE_FIELD;
		}
	};

#pragma endregion


#pragma region TypedField PARTIAL SPECIALIZATIONS

	template<>
	class TypedField<CHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::CHAR_FIELD;
			}
	};

	template<>
	class TypedField<BYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTE_FIELD;
			}
	};

	template<>
	class TypedField<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BOOL_FIELD;
			}
	};

	template<>
	class TypedField<SHORT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::SHORT_FIELD;
			}
	};

	template<>
	class TypedField<WORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::WORD_FIELD;
			}
	};

	template<>
	class TypedField<LONG>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::LONG_FIELD;
			}
	};

	template<>
	class TypedField<DWORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::DWORD_FIELD;
			}
	};

	template<>
	class TypedField<FLOAT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::FLOAT_FIELD;
			}
	};

#pragma endregion

	
#pragma region [VarLengthTypedField] DEFINITION - TEMPLATED, VARIABLE-LENGTH TAGGED UNION

	template<typename T>
	PCCHAR StringReadValue(T &, PCCHAR, CBYTE = 0x10);

	template<typename T>
	CLASS VarLengthTypedField : public TypedField<T>
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		VarLengthTypedField(CSIZE length = 0) : TypedField<T>()
		{
			_Value = new T[length];
			_DataType = VarLengthTypedField<T>::FindDataType();
			_Length = length;
		}

		VarLengthTypedField(RCVARLENGTHTYPEDFIELD<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
			_Length = other._Length;
		}

		VarLengthTypedField(RRVARLENGTHTYPEDFIELD<T> other)
		{
			this->~VarLengthTypedField<T>();
			new (this) VarLengthTypedField<T>(other._Value);
		}

		VarLengthTypedField(RCVALUE value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = VarLengthTypedField<T>::FindDataType();

			if (_DataType == DataType::STRING_FIELD)
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

		EXPLICIT VarLengthTypedField(T & value)
		{
			new (this) VarLengthTypedField<T>(value);
		}

		VIRTUAL ~VarLengthTypedField()
		{
			if (!_Dispose)
				return;

			if (_Length > 0)
				_Value.FreeData();
			else if (_DataType == DataType::BYTES_FIELD || _DataType == DataType::STRING_FIELD || _DataType == DataType::BIT_FIELD)
				_Value.FreePtr();
		}
		
		
		// OPERATORS

		VIRTUAL operator CONST T() const
		{
			return (CONST T)_Value;
		}

		VIRTUAL operator UNSIGNED_TYPE(T&)()
		{
			return (T)_Value;
		}


		//  IField OVERRIDES
				
		CSIZE ByteSize() const
		{
			return sizeof(_Length) + TypedField<T>::ByteSize();
		}
				
		CSIZE StringSize() const
		{
			return 2 * sizeof(_Length) + TypedField<T>::StringSize();
		}

		CSIZE ByteWidth() const
		{
			if (_Length > 0)
				return _Length;

			return TypedField<T>::ByteWidth();
		}

		CSIZE StringLength() const
		{
			if (_DataType == DataType::STRING_FIELD)
				return _Length;
			
			return 2 * this->ByteWidth();
		}
		
		VOID FromBytes(PCBYTE data)
		{
			PCBYTE bufferPtr = data;

			_Length = static_cast<DataType>(*reinterpret_cast<PCSIZE>(bufferPtr));
			bufferPtr += SIZEOF(CSIZE);

			_DataType = static_cast<DataType>(*bufferPtr++);

			_Value = bufferPtr;
		}
		
		VOID FromString(PCCHAR data)
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);
			bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
	
			BYTE bytes[this->ByteWidth()];

			for (BYTE i = 0; i < this->ByteWidth(); i++)
				bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);
		}


	protected:

		using TypedField<T>::_Dispose;
		using TypedField<T>::_Value;
		using TypedField<T>::_DataType;
		using TypedField<T>::IttyBitty::__field_buffer;

		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return TypedField<T>::FindDataType();
		}


		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region VarLengthTypedField PARTIAL SPECIALIZATIONS

	template<>
	class VarLengthTypedField<PBYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTES_FIELD;
			}
	};

	template<>
	class VarLengthTypedField<PCHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::STRING_FIELD;
			}
	};

	template<>
	class VarLengthTypedField<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BIT_FIELD;
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
	

#pragma region FIELD PARSING METHODS
	
	INLINE PIFIELD FieldFromBytes(PCBYTE data)
	{
		PIFIELD field = NULL;

		SIZE length = static_cast<SIZE>(*data);

		if (length == 0 || length > 4)
			field = new VarLengthField();
		else
			field = new Field();

		field->FromBytes(data);

		return field;
	}
	
	INLINE PIFIELD FieldFromString(PCCHAR data)
	{
		PIFIELD field = NULL;
		SIZE length = 0;

		StringReadValue<SIZE>(length, data);

		if (length == 0 || length > 4)
			field = new VarLengthField();
		else
			field = new Field();

		field->FromString(data);

		return field;
	}

#pragma endregion
}


#endif
