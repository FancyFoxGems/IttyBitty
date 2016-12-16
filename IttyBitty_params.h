/***********************************************************************************************
* [IttyBitty_params.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE PARAMS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_PARAMS_H
#define _ITTYBITTY_PARAMS_H


#include "IttyBitty_datum.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	interface IParam;
	TYPEDEF_CLASS_ALIASES(IParam, IPARAM);

	class ParamBase;
	TYPEDEF_CLASS_ALIASES(ParamBase, PARAMBASE);

	class Param;
	TYPEDEF_CLASS_ALIASES(Param, PARAM);

	class VarLengthParam;
	TYPEDEF_CLASS_ALIASES(VarLengthParam, VARLENGTHPARAM);


	#define TYPEDPARAM_T_CLAUSE				<typename T = BYTE>

	template TYPEDPARAM_T_CLAUSE
	class TypedParam;
	TEMPLATE_CLASS_USING_ALIASES(TYPEDPARAM_T_CLAUSE, DEFAULT_T_ARGS, TypedParam, TYPEDPARAM);


	#define VARLENGTHTYPEDPARAM_T_CLAUSE	<typename T = PBYTE>

	template VARLENGTHTYPEDPARAM_T_CLAUSE
	class VarLengthTypedParam;
	TEMPLATE_CLASS_USING_ALIASES(VARLENGTHTYPEDPARAM_T_CLAUSE, DEFAULT_T_ARGS, VarLengthTypedParam, VARLENGTHTYPEDPARAM);

#pragma endregion


#pragma region [IParam] DEFINITION

	INTERFACE IParam : public IDatum { };

#pragma endregion


#pragma region [ParamBase] DEFINITION - TAGGED UNION BASE

	CLASS ParamBase : public DatumBase<ConstValue>, public IParam
	{
	public:

		// [IDatum] IMPLEMENTATION

		VIRTUAL CSIZE ByteWidth() const
		{
			return DatumBase<ConstValue>::ByteWidth();
		}
		VIRTUAL CSIZE StringLength() const
		{
			return DatumBase<ConstValue>::StringLength();
		}

		VIRTUAL CDATASIZE GetDataSize() const
		{
			return DatumBase<ConstValue>::GetDataSize();
		}

		VIRTUAL CDATATYPE GetDataType() const
		{
			return DatumBase<ConstValue>::GetDataType();
		}


		// [ITransmittable] IMPLEMENTATION

	#ifdef ARDUINO

		VIRTUAL BOOL Transmit(HardwareSerial & serial = SERIAL_PORT_HARDWARE)
		{
			return DatumBase<ConstValue>::Transmit(serial);
		}

		VIRTUAL BOOL Transmit(BYTE i2cAddr, TwoWire & twi = Wire)
		{
			return DatumBase<ConstValue>::Transmit(i2cAddr, twi);
		}

	#endif


		// [ISerializable] IMPLEMENTATION

		VIRTUAL PCBYTE ToBinary() const;
		VIRTUAL PCCHAR ToString() const;

		VIRTUAL VOID FromBinary(PCBYTE);
		VIRTUAL VOID FromString(PCCHAR);

		VIRTUAL CSIZE BinarySize() const
		{
			return DatumBase<ConstValue>::BinarySize();
		}

		VIRTUAL CSIZE StringSize() const
		{
			return DatumBase<ConstValue>::StringSize();
		}

		VIRTUAL VOID FreeBuffer() const
		{
			DatumBase<ConstValue>::FreeBuffer();
		}

	#ifdef ARDUINO

		VIRTUAL SIZE printTo(Print & printer) const
		{
			return DatumBase<ConstValue>::printTo(printer);
		}

	#endif
	};

#pragma endregion


#pragma region [Param] DEFINITION - TAGGED UNION

	CLASS Param : public ParamBase
	{
	public:

		// CONSTRUCTORS

		EXPLICIT Param(CDATATYPE = DataType::BYTE_DATUM);

		Param(RCPARAM);
		Param(RRPARAM);

		EXPLICIT Param(RCCONSTVALUE, CDATATYPE = DataType::BYTE_DATUM);

		EXPLICIT Param(RCCHAR);
		EXPLICIT Param(RCBYTE);
		EXPLICIT Param(RCBOOL);
		EXPLICIT Param(RCSHORT);
		EXPLICIT Param(RCWORD);
		EXPLICIT Param(RCLONG);
		EXPLICIT Param(RCDWORD);
		EXPLICIT Param(RCFLOAT);


		// STATIC FUNCTIONS

		STATIC RPARAM NULL_OBJECT();


		// OPERATORS

		RPARAM operator =(RCPARAM);
		RPARAM operator =(RRPARAM);

		RPARAM operator =(RCCONSTVALUE);

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


#pragma region VarLengthParam DECLARATION - VARIABLE-LENGTH TAGGED UNION

	CLASS VarLengthParam : public Param
	{
	public:

		// CONSTRUCTORS

		EXPLICIT VarLengthParam(CDATATYPE = DataType::BYTES_DATUM, CSIZE = 0);

		VarLengthParam(RCVARLENGTHPARAM);
		VarLengthParam(RRVARLENGTHPARAM);

		EXPLICIT VarLengthParam(RCCONSTVALUE, CDATATYPE = DataType::BYTES_DATUM, CSIZE = 0);

		EXPLICIT VarLengthParam(PCBYTE, CSIZE = 0);
		EXPLICIT VarLengthParam(PCCHAR);
		EXPLICIT VarLengthParam(PCBITPACK, CSIZE = 0);


		// OPERATORS

		RVARLENGTHPARAM operator =(RCVARLENGTHPARAM);
		RVARLENGTHPARAM operator =(RRVARLENGTHPARAM);

		VIRTUAL operator PCBYTE() const;
		VIRTUAL operator PCCHAR() const;
		VIRTUAL operator PCBITPACK() const;


		// [Param] OVERRIDES

		CSIZE ByteWidth() const override;

		VOID FromBinary(PCBYTE) override;
		VOID FromString(PCCHAR) override;


	protected:

		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region [TypedParam] DEFINITION - TEMPLATED TAGGED UNION

	template DEFAULT_T_CLAUSE
	CLASS TypedParam : public ParamBase
	{
	public:

		// CONSTRUYCTORS

		TypedParam()
		{
			_Dispose = TRUE;

			_DataType = FindDataType<T>();
		}

		TypedParam(RCTYPEDPARAM<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
		}

		TypedParam(RRTYPEDPARAM<T> other)
		{
			this->~ParamBase();
			new (this) TypedParam<T>(other._Value);
		}

		TypedParam(RCCONSTVALUE value)
		{
			_Value = value;
			_DataType = FindDataType<T>();
		}

		EXPLICIT TypedParam(CONST T & value)
		{
			this->~ParamBase();
			new (this) TypedParam<T>(value);
		}


		// STATIC FUNCTIONS

		STATIC RTYPEDPARAM<T> NULL_OBJECT()
		{
			STATIC TypedParam<T> NULL_TYPEDPARAM;
			return NULL_TYPEDPARAM;
		}


		// OPERATORS

		RTYPEDPARAM<T> operator =(RCTYPEDPARAM<T> rValue)
		{
			*this = TypedParam<T>(rValue);
			return *this;
		}

		RTYPEDPARAM<T> operator =(RRTYPEDPARAM<T> rValue)
		{
			*this = TypedParam<T>(rValue);
			return *this;
		}

		RTYPEDPARAM<T> operator =(RCCONSTVALUE rValue)
		{
			_Value = rValue;
			return *this;
		}

		operator UNSIGNED_TYPE(CONST T &)() const
		{
			return (UNSIGNED_TYPE(CONST T &))_Value;
		}

		operator SIGNED_TYPE(CONST T &)() const
		{
			return (SIGNED_TYPE(CONST T &))_Value;
		}


		// META-MEMBERS

		typedef T ParamType;
	};

#pragma endregion


#pragma region [VarLengthTypedParam] DEFINITION - TEMPLATED, VARIABLE-LENGTH TAGGED UNION

	template DEFAULT_T_CLAUSE
	CLASS VarLengthTypedParam : public TypedParam<T>
	{
	public:

		// CONSTRUYCTORS

		VarLengthTypedParam(CSIZE length = 0) : TypedParam<T>()
		{
			_Value = new T[length];
			_DataType = FindVarLengthDataType<T>();
			_Length = length;
		}

		VarLengthTypedParam(RCVARLENGTHTYPEDPARAM<T> other)
		{
			_Dispose = other._Dispose;

			_Value = other._Value;
			_DataType = other._DataType;
			_Length = other._Length;
		}

		VarLengthTypedParam(RRVARLENGTHTYPEDPARAM<T> other)
		{
			this->~VarLengthTypedParam<T>();
			new (this) VarLengthTypedParam<T>(other._Value);
		}

		VarLengthTypedParam(RCCONSTVALUE value, CSIZE length = 0)
		{
			_Value = value;
			_DataType = FindVarLengthDataType<T>();

			if (_DataType == DataType::STRING_DATUM)
			{
				if (!value.String)
					_Length = 0;
				else
					_Length = strlen((PCCHAR)_Value);
			}
			else
			{
				_Length = length;
			}
		}

		EXPLICIT VarLengthTypedParam(CONST T & value)
		{
			new (this) VarLengthTypedParam<T>(value);
		}


		// OPERATORS

		operator CONST T() const
		{
			return (CONST T)_Value;
		}

		operator T()
		{
			return (T)_Value;
		}


		//  [Param] OVERRIDES

		CSIZE ByteWidth() const override
		{
			if (_Length > 0)
				return _Length;

			return DatumBase<ConstValue>::ByteWidth();
		}

		VOID FromBinary(PCBYTE data) override
		{
			PCBYTE bufferPtr = data;

			_Length = *reinterpret_cast<PCSIZE>(bufferPtr);

			ParamBase::FromBinary(data);
		}

		VOID FromString(PCCHAR data) override
		{
			PCCHAR bufferPtr = data;

			bufferPtr = StringReadValue<SIZE>(_Length, bufferPtr);

			ParamBase::FromString(data);
		}


	protected:

		using TypedParam<T>::_Dispose;
		using TypedParam<T>::_Value;
		using TypedParam<T>::_DataType;
		using TypedParam<T>::IttyBitty::__datum_buffer;


		// INSTANCE VARIABLES

		SIZE _Length = 0;
	};

#pragma endregion


#pragma region [Param] PARSING GLOBAL FUNCTION DEFINITIONS

	INLINE PIPARAM ParamFromBytes(PCBYTE data)
	{
		PIPARAM datum = NULL;

		SIZE length = static_cast<SIZE>(*data);

		if (length == 0 OR length > 4)
			datum = new VarLengthParam();
		else
			datum = new Param();

		datum->FromBinary(data);

		return datum;
	}

	INLINE PIPARAM ParamFromString(PCCHAR data)
	{
		PIPARAM datum = NULL;
		SIZE length = 0;

		StringReadValue<SIZE>(length, data);

		if (length == 0 OR length > 4)
			datum = new VarLengthParam();
		else
			datum = new Param();

		datum->FromString(data);

		return datum;
	}

#pragma endregion
}


#endif
