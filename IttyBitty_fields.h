/***********************************************************************************************
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_FIELDS_H
#define _ITTYBITTY_FIELDS_H


#include "IttyBitty_datum.h"


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES
		
	// ToBinary() / ToString() BUFFER POINTER
	EXTERN PBYTE __field_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IField;
	typedef IField IFIELD, * PIFIELD, & RIFIELD, ** PPIFIELD, && RRIFIELD;
	typedef const IField CIFIELD, *PCIFIELD, & RCIFIELD, ** PPCIFIELD;

	class FieldBase;
	typedef FieldBase FIELDBASE, * PFIELDBASE, & RFIELDBASE, ** PPFIELDBASE, && RRFIELDBASE;
	typedef const FieldBase CFIELDBASE, * PCFIELDBASE, & RCFIELDBASE, ** PPCFIELDBASE;

	class Field;
	typedef Field FIELD, * PFIELD, & RFIELD, ** PPFIELD, && RRFIELD;
	typedef const Field CFIELD, * PCFIELD, & RCFIELD, ** PPCFIELD;

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


#pragma region INTERFACE DEFINITIONS


	// [IField] DEFINITION

	INTERFACE IField : public IDatum
	{
	public:

		// INTERFACE METHODS
	};

#pragma endregion


#pragma region [FieldBase] DEFINITION - TAGGED UNION BASE

	CLASS FieldBase : public IField
	{
	public:

		// /DESTRUCTOR

		VIRTUAL ~FieldBase();
		
		
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


		// IField IMPLEMENTATION

		VIRTUAL CONST DataSize GetDataSize() const;
		VIRTUAL CONST DataType GetDataType() const;
		

	protected:

		// INSTANCE VARIABLES
		
		BOOL _Dispose = FALSE;

		ConstValue _Value;
		DataType _DataType;
	};

#pragma endregion


#pragma region [Field] DEFINITION - TAGGED UNION

	CLASS Field : public FieldBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT Field(CONST DataType = DataType::BYTE_DATUM);

		Field(RCFIELD);
		Field(RRFIELD);

		EXPLICIT Field(RCCONSTVALUE, CONST DataType = DataType::BYTE_DATUM);

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

		VIRTUAL RFIELD operator =(RCCONSTVALUE);

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

		EXPLICIT VarLengthField(CONST DataType = DataType::BYTES_DATUM, CSIZE = 0);

		VarLengthField(RCVARLENGTHFIELD);
		VarLengthField(RRVARLENGTHFIELD);

		EXPLICIT VarLengthField(RCCONSTVALUE, CONST DataType = DataType::BYTES_DATUM, CSIZE = 0);

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

		VIRTUAL CSIZE ByteWidth() const final;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);
		

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

		TypedField(RCCONSTVALUE value)
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

		VIRTUAL RTYPEDFIELD<T> operator =(RCCONSTVALUE rValue)
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

		typedef T FieldType;


	protected:
		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return DataType::BYTE_DATUM;
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
				return DataType::CHAR_DATUM;
			}
	};

	template<>
	class TypedField<BYTE>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BYTE_DATUM;
			}
	};

	template<>
	class TypedField<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BOOL_DATUM;
			}
	};

	template<>
	class TypedField<SHORT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::SHORT_DATUM;
			}
	};

	template<>
	class TypedField<WORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::WORD_DATUM;
			}
	};

	template<>
	class TypedField<LONG>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::LONG_DATUM;
			}
	};

	template<>
	class TypedField<DWORD>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::DWORD_DATUM;
			}
	};

	template<>
	class TypedField<FLOAT>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::FLOAT_DATUM;
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

		VarLengthTypedField(RCCONSTVALUE value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = VarLengthTypedField<T>::FindDataType();

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

		EXPLICIT VarLengthTypedField(T & value)
		{
			new (this) VarLengthTypedField<T>(value);
		}

		VIRTUAL ~VarLengthTypedField()
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


		//  IField OVERRIDES

		VIRTUAL CSIZE ByteWidth() const final
		{
			if (_Length > 0)
				return _Length;

			return FieldBase::ByteWidth();
		}
		
		VIRTUAL VOID FromBinary(PCBYTE data) final
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);
	
			FieldBase::FromBinary(data);
		}
		
		VIRTUAL VOID FromString(PCCHAR data) final
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			FieldBase::FromString(data);
			
			// TODO
			//bufferPtr = StringReadValue<DataType>(_DataType, bufferPtr);
	
			//BYTE bytes[this->ByteWidth()];

			//for (BYTE i = 0; i < this->ByteWidth(); i++)
			//	bufferPtr = StringReadValue<BYTE>(bytes[i], bufferPtr);
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
				return DataType::BYTES_DATUM;
			}
	};

	template<>
	class VarLengthTypedField<PCHAR>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::STRING_DATUM;
			}
	};

	template<>
	class VarLengthTypedField<BOOL>
	{
	protected:
		
			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR const DataType FindDataType()
			{
				return DataType::BIT_DATUM;
			}
	};

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

		field->FromBinary(data);

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
