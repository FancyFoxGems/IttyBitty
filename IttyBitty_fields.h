/***********************************************************************************************
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright � 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_FIELDS_H
#define _ITTYBITTY_FIELDS_H


#include "IttyBitty_datum.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	class IField;
	TYPEDEF_CLASS_ALIASES(IField, IFIELD);

	class FieldBase;
	TYPEDEF_CLASS_ALIASES(FieldBase, FIELDBASE);

	class Field;
	TYPEDEF_CLASS_ALIASES(Field, FIELD);

	class VarLengthField;
	TYPEDEF_CLASS_ALIASES(VarLengthField, VARLENGTHFIELD);


	#define TYPEDFIELD_T_CLAUSE				<typename T = PBYTE>

	template TYPEDFIELD_T_CLAUSE
	class TypedField;
	TEMPLATE_CLASS_USING_ALIASES(TYPEDFIELD_T_CLAUSE, DEFAULT_T_ARGS, TypedField, TYPEDFIELD);


	#define VARLENGTHTYPEDFIELD_T_CLAUSE	<typename T = PBYTE>

	template VARLENGTHTYPEDFIELD_T_CLAUSE
	class VarLengthTypedField;
	TEMPLATE_CLASS_USING_ALIASES(VARLENGTHTYPEDFIELD_T_CLAUSE, DEFAULT_T_ARGS, VarLengthTypedField, VARLENGTHTYPEDFIELD);

#pragma endregion


#pragma region [Field] PARSING GLOBAL FUNCTION DECLARATIONS

	PIFIELD FieldFromBytes(PCBYTE);
	PIFIELD FieldFromString(PCCHAR);

#pragma endregion


#pragma region [IField] DEFINITION

	INTERFACE IField : public IDatum
	{
	public:

		// INTERFACE METHODS

		VIRTUAL PCBYTE MetadataToBinary() const = 0;
		VIRTUAL PCBYTE ValueToBinary() const = 0;

		VIRTUAL PCCHAR MetadataToString() const = 0;
		VIRTUAL PCCHAR ValueToString() const = 0;

		VIRTUAL VOID MetadataFromBinary(PCBYTE) = 0;
		VIRTUAL VOID ValueFromBinary(PCBYTE) = 0;

		VIRTUAL VOID MetadataFromString(PCCHAR) = 0;
		VIRTUAL VOID ValueFromString(PCCHAR) = 0;
	};

#pragma endregion


#pragma region [FieldBase] DEFINITION - TAGGED UNION BASE

	CLASS FieldBase : public DatumBase<Value>, public IField
	{
	public:

		// [ISerializable] IMPLEMENTATION

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

		VIRTUAL CSIZE BinarySize() const
		{
			return DatumBase<Value>::BinarySize();
		}

		VIRTUAL CSIZE StringSize() const
		{
			return DatumBase<Value>::StringSize();
		}


		// [ITransmittable] IMPLEMENTATION

	#ifdef ARDUINO

		VIRTUAL BOOL Transmit(HardwareSerial & serial = SERIAL_PORT_HARDWARE)
		{
			return DatumBase<Value>::Transmit(serial);
		}

		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & twi = Wire)
		{
			return DatumBase<Value>::Transmit(i2cAddr, twi);
		}

		VIRTUAL SIZE printTo(Print & printer) const
		{
			return DatumBase<Value>::printTo(printer);
		}

	#endif


		// [IDatum] IMPLEMENTATION

		VIRTUAL CSIZE ByteWidth() const
		{
			return DatumBase<Value>::ByteWidth();
		}
		VIRTUAL CSIZE StringLength() const
		{
			return DatumBase<Value>::StringLength();
		}

		VIRTUAL CDATASIZE GetDataSize() const
		{
			return DatumBase<Value>::GetDataSize();
		}

		VIRTUAL CDATATYPE GetDataType() const
		{
			return DatumBase<Value>::GetDataType();
		}

		VIRTUAL PCBYTE MetadataToBinary() const;
		VIRTUAL PCBYTE ValueToBinary() const;

		VIRTUAL PCCHAR MetadataToString() const;
		VIRTUAL PCCHAR ValueToString() const;

		VIRTUAL VOID MetadataFromBinary(PCBYTE);
		VIRTUAL VOID ValueFromBinary(PCBYTE);

		VIRTUAL VOID MetadataFromString(PCCHAR);
		VIRTUAL VOID ValueFromString(PCCHAR);


	protected:

		// [ISerializable] HELPER METHODS

		VIRTUAL VOID FreeBuffer() const
		{
			DatumBase<Value>::FreeBuffer();
		}
	};

#pragma endregion


#pragma region [Field] DEFINITION - TAGGED UNION

	CLASS Field : public FieldBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		EXPLICIT Field(CDATATYPE = DataType::BYTE_DATUM);

		Field(RCFIELD);
		Field(RRFIELD);

		EXPLICIT Field(RVALUE, CDATATYPE = DataType::BYTE_DATUM);

		EXPLICIT Field(RCHAR);
		EXPLICIT Field(RBYTE);
		EXPLICIT Field(RBOOL);
		EXPLICIT Field(RSHORT);
		EXPLICIT Field(RWORD);
		EXPLICIT Field(RLONG);
		EXPLICIT Field(RDWORD);
		EXPLICIT Field(RFLOAT);


		// STATIC FUNCTIONS

		STATIC RFIELD NULL_OBJECT();


		// OPERATORS

		VIRTUAL RFIELD operator =(RCFIELD);
		VIRTUAL RFIELD operator =(RRFIELD);

		VIRTUAL RFIELD operator =(RVALUE);

		VIRTUAL operator RCCHAR() const;
		VIRTUAL operator RCHAR();
		VIRTUAL operator RCBYTE() const;
		VIRTUAL operator RBYTE();
		VIRTUAL operator RCBOOL() const;
		VIRTUAL operator RBOOL();
		VIRTUAL operator RCSHORT() const;
		VIRTUAL operator RSHORT();
		VIRTUAL operator RCWORD() const;
		VIRTUAL operator RWORD();
		VIRTUAL operator RCLONG() const;
		VIRTUAL operator RLONG();
		VIRTUAL operator RCDWORD() const;
		VIRTUAL operator RDWORD();
		VIRTUAL operator RCFLOAT() const;
		VIRTUAL operator RFLOAT();
	};

#pragma endregion


#pragma region VarLengthField DECLARATION - VARIABLE-LENGTH TAGGED UNION

	CLASS VarLengthField : public Field
	{
	public:

		// CONSTRUCTORS

		EXPLICIT VarLengthField(CDATATYPE = DataType::BYTES_DATUM, CSIZE = 0);

		VarLengthField(RCVARLENGTHFIELD);
		VarLengthField(RRVARLENGTHFIELD);

		EXPLICIT VarLengthField(RVALUE, CDATATYPE = DataType::BYTES_DATUM, CSIZE = 0);

		EXPLICIT VarLengthField(PBYTE, CSIZE = 0);
		EXPLICIT VarLengthField(PCHAR);
		EXPLICIT VarLengthField(PBITPACK, CSIZE = 0);


		// OPERATORS

		VIRTUAL RVARLENGTHFIELD operator =(RCVARLENGTHFIELD);
		VIRTUAL RVARLENGTHFIELD operator =(RRVARLENGTHFIELD);

		VIRTUAL operator PCBYTE() const;
		VIRTUAL operator PBYTE();
		VIRTUAL operator PCCHAR() const;
		VIRTUAL operator PCHAR();
		VIRTUAL operator PCBITPACK() const;
		VIRTUAL operator PBITPACK();


		// [Field] OVERRIDES

		CSIZE ByteWidth() const override;

		VOID MetadataFromBinary(PCBYTE) override;

		VOID MetadataFromString(PCCHAR) override;


	protected:

		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region [TypedField] DEFINITION - TEMPLATED TAGGED UNION

	template DEFAULT_T_CLAUSE
	CLASS TypedField : public FieldBase
	{
	public:

		// CONSTRUYCTORS

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

		TypedField(RVALUE value)
		{
			_Value = value;
			_DataType = TypedField<T>::FindDataType();
		}

		EXPLICIT TypedField(T & value)
		{
			this->~FieldBase();
			new (this) TypedField<T>(value);
		}


		// STATIC FUNCTIONS

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

		VIRTUAL RTYPEDFIELD<T> operator =(RVALUE rValue)
		{
			_Value = rValue;
			return *this;
		}

		VIRTUAL operator UNSIGNED_TYPE(CONST T &)() const
		{
			return (UNSIGNED_TYPE(CONST T &))_Value;
		}

		VIRTUAL operator UNSIGNED_TYPE(T &)()
		{
			return (UNSIGNED_TYPE(T &))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(CONST T &)() const
		{
			return (SIGNED_TYPE(CONST T &))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(T &)()
		{
			return (SIGNED_TYPE(T &))_Value;
		}


		// META-MEMBERS

		typedef T FieldType;


	protected:

		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR CDATATYPE FindDataType()
		{
			return DataType::BYTE_DATUM;
		}
	};

#pragma endregion


#pragma region TypedField PARTIAL SPECIALIZATIONS

	template<>
	CLASS TypedField<CHAR>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::CHAR_DATUM;
			}
	};

	template<>
	CLASS TypedField<BYTE>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::BYTE_DATUM;
			}
	};

	template<>
	CLASS TypedField<BOOL>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::BOOL_DATUM;
			}
	};

	template<>
	CLASS TypedField<SHORT>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::SHORT_DATUM;
			}
	};

	template<>
	CLASS TypedField<WORD>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::WORD_DATUM;
			}
	};

	template<>
	CLASS TypedField<LONG>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::LONG_DATUM;
			}
	};

	template<>
	CLASS TypedField<DWORD>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::DWORD_DATUM;
			}
	};

	template<>
	CLASS TypedField<FLOAT>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::FLOAT_DATUM;
			}
	};

#pragma endregion


#pragma region [VarLengthTypedField] DEFINITION - TEMPLATED, VARIABLE-LENGTH TAGGED UNION

	template DEFAULT_T_CLAUSE
	CLASS VarLengthTypedField : public TypedField<T>
	{
	public:

		// CONSTRUYCTORS

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

			if (_DataType == DataType::STRING_DATUM)
			{
				if (value.StringRef == NULL)
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


		// OPERATORS

		VIRTUAL operator UNSIGNED_TYPE(CONST T &)() const
		{
			return (UNSIGNED_TYPE(CONST T &))_Value;
		}

		VIRTUAL operator UNSIGNED_TYPE(T &)()
		{
			return (UNSIGNED_TYPE(T &))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(CONST T &)() const
		{
			return (SIGNED_TYPE(CONST T &))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(T &)()
		{
			return (SIGNED_TYPE(T &))_Value;
		}


		//  [Field] OVERRIDES

		CSIZE ByteWidth() const override
		{
			if (_Length > 0)
				return _Length;

			return DatumBase<Value>::ByteWidth();
		}

		VOID MetadataFromBinary(PCBYTE data) override
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);

			FieldBase::MetadataFromBinary(data);
		}

		VOID MetadataFromString(PCCHAR data) override
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			FieldBase::MetadataFromString(data);
		}


	protected:

		using TypedField<T>::_Dispose;
		using TypedField<T>::_Value;
		using TypedField<T>::_DataType;
		using TypedField<T>::IttyBitty::__datum_buffer;


		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR CDATATYPE FindDataType()
		{
			return TypedField<T>::FindDataType();
		}


		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region VarLengthTypedField PARTIAL SPECIALIZATIONS

	template<>
	CLASS VarLengthTypedField<PBYTE>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::BYTES_DATUM;
			}
	};

	template<>
	CLASS VarLengthTypedField<PCHAR>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
			{
				return DataType::STRING_DATUM;
			}
	};

	template<>
	CLASS VarLengthTypedField<BOOL>
	{
	protected:

			// PROTECTED STATIC FUNCTIONS

			STATIC CONSTEXPR CDATATYPE FindDataType()
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
