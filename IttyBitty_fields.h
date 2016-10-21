/***********************************************************************************************
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_FIELDS_H
#define _ITTYBITTY_FIELDS_H


#include "Printable.h"

#include "IttyBitty_bits.h"

using namespace IttyBitty;


namespace IttyBitty
{
#pragma region GLOBAL CONSTANTS & VARIABLES

	EXTERN CBYTE DATA_SIZE_MASK;
		
	// Field::ToBytes() / ToString() BUFFER POINTER
	EXTERN PBYTE __field_buffer;

#pragma endregion


#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	typedef union Datum DATUM, * PDATUM, & RDATUM, ** PPDATUM, && RRDATUM;
	typedef const union Datum CDATUM, * PCDATUM, & RCDATUM, ** PPCDATUM;

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

#pragma endregion


#pragma region Datum DECLARATION: UNIVERSAL 4-BYTE DATA TYPE UNION
	
	UNION PACKED Datum
	{
		// UNION MEMBERS

		PBYTE Bytes;
		PCHAR String;	
		PBITPACK BitFields;
		
		PCHAR CharPtr;
		PBYTE BytePtr;
		PBOOL BoolPtr;
		
		PSHORT ShortPtr;
		PWORD WordPtr;
		
		PLONG LongPtr;
		PDWORD DWordPtr;
		PFLOAT FloatPtr;


		// CONSTRUCTORS

		Datum();

		Datum(RCDATUM other);
		Datum(RRDATUM other);

		EXPLICIT Datum(PBYTE value);
		EXPLICIT Datum(PCHAR value);		
		EXPLICIT Datum(PBITPACK value);

		EXPLICIT Datum(RCHAR value);
		EXPLICIT Datum(RBYTE value);
		EXPLICIT Datum(RBOOL value);
		EXPLICIT Datum(RSHORT value);
		EXPLICIT Datum(RWORD value);
		EXPLICIT Datum(RLONG value);
		EXPLICIT Datum(RDWORD value);
		EXPLICIT Datum(RFLOAT value);


		//OPERATORS

		RDATUM operator =(RCDATUM other);
		RDATUM operator =(RRDATUM other);

		RDATUM operator =(PBYTE other);
		RDATUM operator =(PCHAR other);
		RDATUM operator =(PBITPACK other);

		RDATUM operator =(RCCHAR other);
		RDATUM operator =(RCBYTE other);
		RDATUM operator =(RCBOOL other);
		RDATUM operator =(RCSHORT other);
		RDATUM operator =(RCWORD other);
		RDATUM operator =(RCLONG other);
		RDATUM operator =(RCDWORD other);
		RDATUM operator =(RCFLOAT other);
		
		operator PCBYTE() const;
		operator PBYTE();
		operator PCCHAR() const;
		operator PCHAR();
		operator PCBITPACK() const;
		operator PBITPACK();

		operator RCCHAR() const;
		operator RCHAR();
		operator RCBYTE() const;
		operator RBYTE();
		operator RCBOOL() const;
		operator RBOOL();
		operator RCSHORT() const;
		operator RSHORT();
		operator RCWORD() const;
		operator RWORD();
		operator RCLONG() const;
		operator RLONG();
		operator RCDWORD() const;
		operator RDWORD();
		operator RCFLOAT() const;
		operator RFLOAT();


		// USER METHODS

		VOID FreePtr();
		VOID FreeData();
	};

#pragma endregion


#pragma region INTERFACES

	// ISerializable DECLARATION

	CLASS ISerializable : public Printable
	{
	public:

		// INTERFACE METHODS

		VIRTUAL CSIZE Size() const = 0;		
		VIRTUAL CSIZE ByteWidth() const = 0;

		VIRTUAL PCBYTE ToBytes() const = 0;
		VIRTUAL PCCHAR ToString() const = 0;

		VIRTUAL VOID LoadFromBytes(PCBYTE) = 0;
		VIRTUAL VOID LoadFromString(PCCHAR) = 0;

	protected:

		ISerializable() { }
	};


	// IField DECLARATION

	CLASS IField : public ISerializable
	{
	public:

		// INTERFACE METHODS

		VIRTUAL CONST DataSize GetDataSize() const = 0;
		VIRTUAL CONST DataType GetDataType() const = 0;

	protected:

		IField() { }
	};

#pragma endregion


#pragma region FieldBase DECLARATION

	CLASS FieldBase : public virtual IField
	{
	public:

		// /DESTRUCTOR

		VIRTUAL ~FieldBase();
		
		
		// ISerializable IMPLEMENTATION

		VIRTUAL CSIZE Size() const;		
		VIRTUAL CSIZE ByteWidth() const;

		VIRTUAL PCBYTE ToBytes() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID LoadFromBytes(PCBYTE);
		VIRTUAL VOID LoadFromString(PCCHAR);
		
		VIRTUAL SIZE printTo(Print&) const;


		// IField IMPLEMENTATION

		VIRTUAL CONST DataSize GetDataSize() const;
		VIRTUAL CONST DataType GetDataType() const;
		

	protected:

		// INSTANCE VARIABLES
		
		BOOL _Dispose = FALSE;

		Datum _Value;
		DataType _DataType;
	};

#pragma endregion


#pragma region Field DECLARATION

	CLASS Field : public FieldBase
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		Field(DataType = DataType::BYTE_FIELD);

		Field(RCFIELD);
		Field(RRFIELD);

		Field(RCDATUM, DataType = DataType::BYTE_FIELD);

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

		VIRTUAL RFIELD operator =(RCDATUM);

		operator RCCHAR() const;
		operator RCHAR();
		operator RCBYTE() const;
		operator RBYTE();
		operator RCBOOL() const;
		operator RBOOL();
		operator RCSHORT() const;
		operator RSHORT();
		operator RCWORD() const;
		operator RWORD();
		operator RCLONG() const;
		operator RLONG();
		operator RCDWORD() const;
		operator RDWORD();
		operator RCFLOAT() const;
		operator RFLOAT();
	};

#pragma endregion


#pragma region VarLengthField DECLARATION

	CLASS VarLengthField : public Field
	{
	public:

		// CONSTRUCTORS/DESTRUCTOR

		VarLengthField(CSIZE = 0, DataType = DataType::BYTES_FIELD);

		VarLengthField(RCVARLENGTHFIELD);
		VarLengthField(RRVARLENGTHFIELD);

		VarLengthField(RCDATUM, DataType = DataType::BYTES_FIELD);

		EXPLICIT VarLengthField(PBYTE, CSIZE = 0);
		EXPLICIT VarLengthField(PCHAR);
		EXPLICIT VarLengthField(PBITPACK, CSIZE = 0);

		VIRTUAL ~VarLengthField();
		
		
		// OPERATORS

		VIRTUAL RVARLENGTHFIELD operator =(RCVARLENGTHFIELD);
		VIRTUAL RVARLENGTHFIELD operator =(RRVARLENGTHFIELD);
		
		operator PCBYTE() const;
		operator PBYTE();
		operator PCCHAR() const;
		operator PCHAR();
		operator PCBITPACK() const;
		operator PBITPACK();


		// Field OVERRIDES

		VIRTUAL CSIZE Size() const;
		VIRTUAL CSIZE ByteWidth() const;
		
		VIRTUAL PCBYTE ToBytes() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID LoadFromBytes(PCBYTE);
		VIRTUAL VOID LoadFromString(PCCHAR);

		VIRTUAL SIZE printTo(Print&) const;
		

	protected:

		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region TypedField DEFINITION
	
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
			new (this) TypedField<T>(other._Value);
		}

		TypedField(RCDATUM value)
		{
			_Value = value;
			_DataType = TypedField<T>::FindDataType();
		}

		EXPLICIT TypedField(T & value)
		{
			new (this) TypedField<T>(value);
		}

		EXPLICIT TypedField(SIGNED_TYPE(T &) value)
		{
			new (this) TypedField<T>(value);
		}


		// STATIC METHODS

		STATIC RTYPEDFIELD<T> NULL_OBJECT()
		{
			STATIC TypedField<T> NULL_TYPEDFIELD;
			return NULL_TYPEDFIELD;
		}
		
		
		// OPERATORS

		VIRTUAL RTYPEDFIELD<T> operator =(RCVARLENGTHFIELD rValue)
		{
			*this = TypedField<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDFIELD<T> operator =(RRVARLENGTHFIELD rValue)
		{
			*this = TypedField<T>(rValue);
			return *this;
		}

		VIRTUAL RTYPEDFIELD<T> operator =(RCDATUM rValue)
		{
			_Value = rValue;
			return *this;
		}


		VIRTUAL operator UNSIGNED_TYPE(CONST T&)() const
		{
			return (UNSIGNED_TYPE(CONST T&))_Value;
		}

		VIRTUAL operator UNSIGNED_TYPE(T&)()
		{
			return (UNSIGNED_TYPE(T&))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(CONST T&)() const
		{
			return (SIGNED_TYPE(CONST T&))_Value;
		}

		VIRTUAL operator SIGNED_TYPE(T&)()
		{
			return (SIGNED_TYPE(T&))_Value;
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

	
#pragma region VarLengthTypedField DEFINITION

	template<typename T>
	CLASS VarLengthTypedField : public TypedField<T>
	{
	public:

		// CONSTRUYCTORS/DESTRUCTOR

		VarLengthTypedField(CSIZE length = 0)
		{
			_Dispose = TRUE;

			_Value = new T[length];
			_DataType = VarLengthTypedField<T>::FindDataType();
			_Length = length;
		}

		VarLengthTypedField(RCVARLENGTHTYPEDFIELD<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		VarLengthTypedField(RRVARLENGTHTYPEDFIELD<T> other)
		{
			new (this) VarLengthTypedField<T>(other._Value);
		}

		VarLengthTypedField(RCDATUM value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = VarLengthTypedField<T>::FindDataType();

			if (_DataType == DataType::STRING_FIELD)
				_Length = strlen((PCCHAR)_Value);
			else
				_Length = length;
		}

		EXPLICIT VarLengthTypedField(T & value)
		{
			new (this) VarLengthTypedField<T>(value);
		}

		VIRTUAL ~VarLengthTypedField()
		{
			if (_Dispose)
			{
				if (_Length > 0)
					_Value.FreeData();
				else
					_Value.FreePtr();
			}
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
				
		VIRTUAL CSIZE Size() const
		{
			return sizeof(_Length) + TypedField<T>::Size();
		}

		VIRTUAL CSIZE ByteWidth() const
		{
			if (_Length > 0)
				return _Length;

			return TypedField<T>::Size();
		}

		VIRTUAL PCCHAR ToBytes() const
		{
			CSIZE size = this->Size();

			if (__field_buffer)
				delete[] __field_buffer;

			__field_buffer = new BYTE[size];
	
			memcpy(__field_buffer, &_Length, SIZEOF(_Length));
			memcpy(&__field_buffer[SIZEOF(_Length)], &_DataType, SIZEOF(DataType));
			memcpy(&__field_buffer[SIZEOF(_Length) + SIZEOF(DataType)], _Value.Bytes, this->ByteWidth());

			return __field_buffer;
		}

		VIRTUAL PCCHAR ToString() const
		{
			if (_DataType == DataType::STRING_FIELD)
				return _Value.String;
			
			return Field::ToString();
		}
		
		VIRTUAL VOID LoadFromBytes(PCBYTE data)
		{
			_Length = static_cast<SIZE>(*data++);
			TypedField<T>::LoadFromBytes(data);
		}
		
		VIRTUAL VOID LoadFromString(PCCHAR data)
		{
			_Length = static_cast<SIZE>(*data++);
			TypedField<T>::LoadFromString(data);
		}

		VIRTUAL SIZE printTo(Print& printer) const
		{
			SIZE printed = printer.print(_Length);
			printed += printer.print(_DataType);
			printed += printer.print(reinterpret_cast<PCCHAR>(_Value.Bytes));
	
			return printed;
		}


	protected:

		using TypedField<T>::_Dispose;
		using TypedField<T>::_Value;
		using TypedField<T>::_DataType;
		using TypedField<T>::__field_buffer;

		
		// PROTECTED STATIC FUNCTIONS

		STATIC CONSTEXPR const DataType FindDataType()
		{
			return DataType::BYTES_FIELD;
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
}


#endif
