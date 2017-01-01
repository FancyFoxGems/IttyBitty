/***********************************************************************************************
* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES, WORDS, DWORDS, ...
*	NOTE: ^-- Base option (NO_ITTYBITTY_FULL_BYTES) excludes data structures for larger blocks
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_BYTES_H
#define _ITTYBITTY_BYTES_H


#include "IttyBitty_bits.h"


/* SUPRESS COMPILER WARNINGS RELATED TO POINTER ARITHMETIC */

IGNORE_WARNING(pointer-arith)


/* (BYTE) ENDIANNESS DEFINES & TEST MACRO */

#define LITTLE_ENDIANNESS			0
#define BIG_ENDIANNESS				1
#define NETWORK_ORDER_ENDIANNESS	BIG_ENDIANNESS

#ifdef __AVR_ARCH__
	#if __AVR_ARCH__ <= 60		// AVR architecture 1-6
		#define MCU_ENDIANNESS LITTLE_ENDIANNESS
	#elif __AVR_ARCH__ >= 100	// AVR architecture 10 (Xmega)
		#define MCU_ENDIANNESS BIG_ENDIANNESS
	#else
		#define TEST_ENDIANNESS
	#endif
#else
	#define TEST_ENDIANNESS
#endif

#ifdef TEST_ENDIANNESS
	#undef TEST_ENDIANNESS
	#define MCU_ENDIANNESS (*(uint16_t *)"\0\xff" < 0x100)
#endif

#define IS_LITTLE_ENDIAN	MCU_ENDIANNESS == LITTLE_ENDIANNESS
#define IS_BIG_ENDIAN		MCU_ENDIANNESS == BIG_ENDIANNESS


/* ENDIANNESS SWAPPING MACROS */

#define REVERSE_ENDIANNESS_16(var)		__builtin_bswap16(var)
#define REVERSE_ENDIANNESS_32(var)		__builtin_bswap32(var)
#define REVERSE_ENDIANNESS_64(var)		__builtin_bswap64(var)
#define REVERSE_ENDIANNESS(var)			REVERSE_ENDIANNESS_16(var)


namespace IttyBitty
{

	/* TYPE (FORWARD) DECLARATIONS WITH TYPEDEFS */

	struct _BitProxy;
	typedef struct _BitProxy BitRef;
	TYPEDEF_STRUCT_ALIASES(BitProxy, bitproxy, BITREF);


#ifndef NO_ITTYBITTY_FULL_BYTES

	#define IBITFIELD_T_CLAUSE		<typename T = BYTE>

	template IBITFIELD_T_CLAUSE
	interface IBitField;
	TEMPLATE_CLASS_USING_ALIASES(IBITFIELD_T_CLAUSE, DEFAULT_T_ARGS, IBitField, IBITFIELD);

#endif	// #ifndef NO_ITTYBITTY_FULL_BYTES


	interface IByteField;
	TYPEDEF_CLASS_ALIASES(IByteField, IBYTEFIELD);


#ifndef NO_ITTYBITTY_FULL_BYTES

	interface IWordField;
	TYPEDEF_CLASS_ALIASES(IWordField, IWORDFIELD);


	#define IMANYBITFIELD_T_CLAUSE	<typename T = DWORD>

	template IMANYBITFIELD_T_CLAUSE
	interface IManyBitField;
	TEMPLATE_CLASS_USING_ALIASES(IMANYBITFIELD_T_CLAUSE, DEFAULT_T_ARGS, IManyBitField, IMANYBITFIELD);


	interface IDWordField;
	TYPEDEF_CLASS_ALIASES(IDWordField, IDWORDFIELD);


	#define BITFIELD_T_CLAUSE		<typename T = BYTE>

	template BITFIELD_T_CLAUSE
	class BitField;
	TEMPLATE_CLASS_USING_ALIASES(BITFIELD_T_CLAUSE, DEFAULT_T_ARGS, BitField, BITFIELD);

#endif	// #ifndef NO_ITTYBITTY_FULL_BYTES


	class ByteField;
	TYPEDEF_CLASS_ALIASES(ByteField, BYTEFIELD);


#ifndef NO_ITTYBITTY_FULL_BYTES

	class WordField;
	TYPEDEF_CLASS_ALIASES(WordField, WORDFIELD);


	#define MANYBITFIELD_T_CLAUSE	<typename T = DWORD>

	template MANYBITFIELD_T_CLAUSE
	class ManyBitField;
	TEMPLATE_CLASS_USING_ALIASES(MANYBITFIELD_T_CLAUSE, DEFAULT_T_ARGS, ManyBitField, MANYBITFIELD);


	class DWordField;
	TYPEDEF_CLASS_ALIASES(DWordField, DWORDFIELD);

#endif	// #ifndef NO_ITTYBITTY_FULL_BYTES


	/* [_BitProxy]: STRUCTURE FOR BIT-/BYTE-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	STRUCT _BitProxy
	{
	public:

	#ifndef NO_ITTYBITTY_FULL_BYTES
		_BitProxy(PIBYTEFIELD, SIZE);
	#else
		_BitProxy(PBYTEFIELD, SIZE);
	#endif
		_BitProxy(RCBITREF);

		VIRTUAL ~_BitProxy();

		STATIC RBITREF NULL_OBJECT();

		VIRTUAL operator BIT() const;

		VIRTUAL RBITREF operator =(RCBITREF);
		VIRTUAL RBITREF operator =(BIT);

		VIRTUAL BIT Flip();

	protected:

	#ifndef NO_ITTYBITTY_FULL_BYTES
		PIBYTEFIELD Parent() const;
	#else
		PBYTEFIELD Parent() const;
	#endif
		BYTE BitMask() const;

	private:

	#ifndef NO_ITTYBITTY_FULL_BYTES
		VOLATILE PIBYTEFIELD _Parent;
	#else
		VOLATILE PBYTEFIELD _Parent;
	#endif
		BYTE _BitMask;
	};


#ifndef NO_ITTYBITTY_FULL_BYTES

	/* [IBITFIELD]: INTERFACE FOR BIT-/BYTE-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template DEFAULT_T_CLAUSE
	INTERFACE IBitField
	{
	public:

		VIRTUAL ~IBitField() { }

		RIBITFIELD<T> operator =(RRIBITFIELD<T>) { return *this; };
		RIBITFIELD<T> operator =(RCIBITFIELD<T>) { return *this; };

		VIRTUAL operator CONST T() const = 0;
		VIRTUAL operator SIGNED_TYPE(CONST T)() const = 0;

		VIRTUAL operator PCBYTE() const = 0;
		VIRTUAL operator PPVBYTE() = 0;

		VIRTUAL operator PCCHAR() const = 0;
		VIRTUAL operator PPVCHAR() = 0;

		VIRTUAL operator PBYTEFIELD() const = 0;
		VIRTUAL operator PPBYTEFIELD() = 0;

		VIRTUAL BIT operator[](SIZE) const = 0;
		VIRTUAL BITREF operator[](SIZE) = 0;

		VIRTUAL CSIZE Size() const = 0;

		VIRTUAL SIZE BitWidth() const = 0;
		VIRTUAL SIZE ByteSize() const = 0;

		VIRTUAL BIT Bit(SIZE) const = 0;
		VIRTUAL BITREF Bit(SIZE) = 0;
		VIRTUAL BIT Flip(SIZE) = 0;

		VIRTUAL PPCBYTEFIELD Bytes() const = 0;
		VIRTUAL BYTE Byte(SIZE) const = 0;
		VIRTUAL RIBYTEFIELD Byte(SIZE) = 0;

		VIRTUAL T Value() const = 0;
		VIRTUAL VOID SetValue(T) = 0;
		VIRTUAL VOID CopyFrom(RCIBITFIELD<T>) = 0;

		VIRTUAL VOLATILE T * Pointer() const = 0;
		VIRTUAL VOID PointTo(VOLATILE T *) = 0;
		VIRTUAL VOID ReferenceFrom(RCIBITFIELD<T>) = 0;

		VIRTUAL T Mask(T) const = 0;
		VIRTUAL T Mask(RCIBITFIELD<T>) const = 0;

		VIRTUAL PIBITFIELD<T> CloneByValue() const = 0;
		VIRTUAL PIBITFIELD<T> CloneByReference() const = 0;

	protected:

		ENUM DisposalLevel : BYTE
		{
			None		= 0,
			FieldPtrPtr = 1,
			FieldPtrs	= 2,
			FieldData	= 3
		};

		IBitField() { };
	};


	/* [IByteField]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IByteField : public IBitField<BYTE>
	{
	public:

	#ifdef NO_ITTYBITTY_FULL_BYTES

		VIRTUAL ~IByteField() { }

		VIRTUAL operator CBYTE() const = 0;
		VIRTUAL operator CCHAR() const = 0;

		VIRTUAL operator PCBYTE() const = 0;
		VIRTUAL operator PPVBYTE() = 0;

		VIRTUAL operator PCCHAR() const = 0;
		VIRTUAL operator PPVCHAR() = 0;

		VIRTUAL operator PBYTEFIELD() const = 0;
		VIRTUAL operator PPBYTEFIELD() = 0;

		VIRTUAL BIT operator[](SIZE) const = 0;
		VIRTUAL BITREF operator[](SIZE) = 0;

		VIRTUAL CSIZE Size() const = 0;

		VIRTUAL SIZE BitWidth() const = 0;
		VIRTUAL SIZE ByteSize() const = 0;

		VIRTUAL BIT Bit(SIZE) const = 0;
		VIRTUAL BITREF Bit(SIZE) = 0;
		VIRTUAL BIT Flip(SIZE) = 0;

		VIRTUAL PPCBYTEFIELD Bytes() const = 0;
		VIRTUAL BYTE Byte(SIZE) const = 0;
		VIRTUAL RIBYTEFIELD Byte(SIZE) = 0;

		VIRTUAL BYTE Value() const = 0;
		VIRTUAL VOID SetValue(BYTE) = 0;
		VIRTUAL VOID CopyFrom(RCIBYTEFIELD) = 0;

		VIRTUAL PVBYTE Pointer() const = 0;
		VIRTUAL VOID PointTo(PVBYTE) = 0;
		VIRTUAL VOID ReferenceFrom(RCIBYTEFIELD) = 0;

		VIRTUAL BYTE Mask(BYTE) const = 0;
		VIRTUAL BYTE Mask(RCIBYTEFIELD) const = 0;

		VIRTUAL PIBYTEFIELD CloneByValue() const = 0;
		VIRTUAL PIBYTEFIELD CloneByReference() const = 0;

	#endif

		RIBYTEFIELD operator =(RRIBYTEFIELD) { return *this; };
		RIBYTEFIELD operator =(RCIBYTEFIELD) { return *this; };

		VIRTUAL operator PVBYTE() = 0;
		VIRTUAL operator RVBYTE() = 0;

		VIRTUAL operator PVCHAR() = 0;
		VIRTUAL operator RVCHAR() = 0;

		VIRTUAL operator PCBITPACK() const = 0;
		VIRTUAL operator PBITPACK() = 0;

		VIRTUAL BYTE LowNybble() const = 0;
		VIRTUAL RIBYTEFIELD SetLowNybble(BYTE) = 0;
		VIRTUAL BYTE HighNybble() const = 0;
		VIRTUAL RIBYTEFIELD SetHighNybble(BYTE) = 0;
	};


	/* [IWordField]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IWordField : public virtual IBitField<WORD>
	{
	public:

		RIWORDFIELD operator =(RRIWORDFIELD) { return *this; };
		RIWORDFIELD operator =(RCIWORDFIELD) { return *this; };

		VIRTUAL BYTE LowByte() const = 0;
		VIRTUAL RIBYTEFIELD SetLowByte(BYTE) = 0;
		VIRTUAL BYTE HighByte() const = 0;
		VIRTUAL RIBYTEFIELD SetHighByte(BYTE) = 0;
	};


	/* [IMANYBITFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template DEFAULT_T_CLAUSE
	INTERFACE IManyBitField : public virtual IBitField<T>
	{
	public:

		RIMANYBITFIELD<T> operator =(RRIMANYBITFIELD<T>) { return *this; };
		RIMANYBITFIELD<T> operator =(RCIMANYBITFIELD<T>) { return *this; };

		VIRTUAL operator PPVWORD() const = 0;
		VIRTUAL operator PPVSHORT() const = 0;

		VIRTUAL SIZE WordSize() const = 0;

		VIRTUAL PPCWORDFIELD Words() const = 0;
		VIRTUAL WORD Word(SIZE) const = 0;
		VIRTUAL RIWORDFIELD Word(SIZE) = 0;
	};


	/* [IDWORDFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	INTERFACE IDWordField : public virtual IManyBitField<DWORD>
	{
	public:

		RIDWORDFIELD operator =(RRIDWORDFIELD) { return *this; };
		RIDWORDFIELD operator =(RCIDWORDFIELD) { return *this; };

		VIRTUAL WORD LowWord() const = 0;
		VIRTUAL RIWORDFIELD SetLowWord(WORD) = 0;
		VIRTUAL WORD HighWord() const = 0;
		VIRTUAL RIWORDFIELD SetHighWord(WORD) = 0;
	};

#endif	// #ifndef NO_ITTYBITTY_FULL_BYTES


	/* [BYTEFIELD]: CLASS TO ENCAPSULATE BIT-PACKED SINGLE BYTE REFERENCES */

	CLASS ByteField
	#ifndef NO_ITTYBITTY_FULL_BYTES
		: public virtual IByteField
	#endif
	{
	public:

		ByteField();
		EXPLICIT ByteField(RCBYTE);
		EXPLICIT ByteField(RVBYTE);
		EXPLICIT ByteField(PVBYTE);

		ByteField(RRBYTEFIELD);
		ByteField(RCBYTEFIELD);

		~ByteField();

		STATIC RBYTEFIELD NULL_OBJECT();

		VIRTUAL RBYTEFIELD operator =(RRBYTEFIELD);
		VIRTUAL RBYTEFIELD operator =(RCBYTEFIELD);

		// IBitField<BYTE>

		VIRTUAL operator CBYTE() const;
		VIRTUAL operator CCHAR() const;

		VIRTUAL operator PCBYTE() const;
		VIRTUAL operator PPVBYTE();

		VIRTUAL operator PCCHAR() const;
		VIRTUAL operator PPVCHAR();

		VIRTUAL operator PBYTEFIELD() const;
		VIRTUAL operator PPBYTEFIELD();

		VIRTUAL BIT operator[](SIZE) const;
		VIRTUAL BITREF operator[](SIZE);

		VIRTUAL CSIZE Size() const;

		VIRTUAL SIZE BitWidth() const;
		VIRTUAL SIZE ByteSize() const;

		VIRTUAL BIT Bit(SIZE) const;
		VIRTUAL BITREF Bit(SIZE);
		VIRTUAL BIT Flip(SIZE);

		VIRTUAL PPCBYTEFIELD Bytes() const;
		VIRTUAL BYTE Byte(SIZE) const;
	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL RIBYTEFIELD Byte(SIZE);
	#else
		VIRTUAL RBYTEFIELD Byte(SIZE);
	#endif

		VIRTUAL BYTE Value() const;
		VIRTUAL VOID SetValue(BYTE);
	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL VOID CopyFrom(RCIBITFIELD<BYTE>);
	#else
		VIRTUAL VOID CopyFrom(RCBYTEFIELD);
	#endif

		VIRTUAL PVBYTE Pointer() const;
		VIRTUAL VOID PointTo(PVBYTE);
	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL VOID ReferenceFrom(RCIBITFIELD<BYTE>);
	#else
		VIRTUAL VOID ReferenceFrom(RCBYTEFIELD);
	#endif

		VIRTUAL BYTE Mask(BYTE) const;
	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL BYTE Mask(RCIBITFIELD<BYTE>) const;
	#else
		VIRTUAL BYTE Mask(RCBYTEFIELD) const;
	#endif

		// IByteField

		VIRTUAL operator PVBYTE();
		VIRTUAL operator RVBYTE();

		VIRTUAL operator PVCHAR();
		VIRTUAL operator RVCHAR();

		VIRTUAL operator PCBITPACK() const;
		VIRTUAL operator PBITPACK();

	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL PIBYTEFIELD CloneByValue() const;
		VIRTUAL PIBYTEFIELD CloneByReference() const;
	#else
		VIRTUAL PBYTEFIELD CloneByValue() const;
		VIRTUAL PBYTEFIELD CloneByReference() const;
	#endif

		VIRTUAL BYTE LowNybble() const;
	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL RIBYTEFIELD SetLowNybble(BYTE);
	#else
		VIRTUAL RBYTEFIELD SetLowNybble(BYTE);
	#endif

		VIRTUAL BYTE HighNybble() const;
	#ifndef NO_ITTYBITTY_FULL_BYTES
		VIRTUAL RIBYTEFIELD SetHighNybble(BYTE);
	#else
		VIRTUAL RBYTEFIELD SetHighNybble(BYTE);
	#endif

	protected:

		typedef struct __BitProxy __bitproxy_t, BITPROXY, * PBITPROXY, & RBITPROXY;
		typedef const struct __BitProxy CBITPROXY, * PCBITPROXY, & RCBITPROXY;

		VOLATILE PACKED_UNION
		{
			PVBYTE _pByte;
			PBITPACK _pBitPack;
		};

		BOOL _DisposeByte = FALSE;
	};


#ifndef NO_ITTYBITTY_FULL_BYTES

	/* [BitField]: [IBitField] BASE IMPLEMENTATION TO ENCAPSULATE BIT-PACKED BYTE REFERENCES */

	template DEFAULT_T_CLAUSE
	CLASS BitField : public virtual IBitField<T>
	{
	public:

		BitField() : _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = (PBYTEFIELD)NULL;
		}

		BitField(T tVal)
			: _DisposalLevel(DisposalLevel::None)
		{
			this->SetValue(tVal);
		}

		EXPLICIT BitField(PTR memAddr, SIZE byteWidth = T_SIZE)
			: _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
			{
				if (i < byteWidth)
			#if IS_BIG_ENDIANNESS
					_ByteFieldPtrs[i] = new ByteField((PVBYTE)memAddr + T_SIZE - 1 - i);
			#else
					_ByteFieldPtrs[i] = new ByteField((PVBYTE)memAddr + i);
			#endif
				else
					_ByteFieldPtrs[i] = new ByteField((BYTE)0);
			}
		}

		BitField(BYTE byteVals[T_SIZE])
			: _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = new ByteField((BYTE)byteVals[i]);
		}

		BitField(PVBYTE bytePtrs[T_SIZE])
			: _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = new ByteField(bytePtrs[i]);
		}

		BitField(BYTEFIELD byteFields[T_SIZE])
			: _DisposalLevel(DisposalLevel::FieldPtrPtr)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = &byteFields[i];
		}

		BitField(PBYTEFIELD byteFieldPtrs[T_SIZE])
			: _DisposalLevel(DisposalLevel::None)
		{
			_ByteFieldPtrs = byteFieldPtrs;
		}

		BitField(RRBITFIELD<T> other)
		{
			this->~BitField<T>();
			new (this) BitField<T>((PTR)other.Bytes(), T_SIZE);

			other._DisposalLevel = DisposalLevel::None;
		}

		BitField(RCBITFIELD<T> other)
		{
			this->~BitField<T>();
			new (this) BitField<T>((PTR)other.Bytes(), T_SIZE);
		}

		VIRTUAL ~BitField()
		{
			switch (_DisposalLevel)
			{
			case DisposalLevel::FieldData:

				for (SIZE i = 0; i < T_SIZE; i++)
					delete _ByteFieldPtrs[i];

			case DisposalLevel::FieldPtrs:

				delete[] _ByteFieldPtrs;
				break;

			case DisposalLevel::FieldPtrPtr:

				delete _ByteFieldPtrs;
				break;

			case DisposalLevel::None:

				break;
			}
		}

		STATIC RBITFIELD<T> NULL_OBJECT()
		{
			STATIC BITFIELD<T> NULL_BITFIELD((T)0);
			return NULL_BITFIELD;
		}

		VIRTUAL RBITFIELD<T> operator =(RRBITFIELD<T> other)
		{
			*this = BitField<T>(other);

			return *this;
		}

		VIRTUAL RBITFIELD<T> operator =(RCBITFIELD<T> other)
		{
			*this = BitField<T>(other);

			return *this;
		}

		VIRTUAL operator CONST T() const
		{
			return this->Value();
		}

		VIRTUAL operator SIGNED_TYPE(CONST T)() const
		{
			return (SIGNED_TYPE(T))this->Value();
		}

		VIRTUAL operator PCBYTE() const
		{
			STATIC BYTE bytes[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i ++)
				bytes[i] = _ByteFieldPtrs[i]->Value();

			return bytes;
		}

		VIRTUAL operator PPVBYTE()
		{
			STATIC PPVBYTE bytePtrs[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i ++)
				(*bytePtrs)[i] = _ByteFieldPtrs[i]->Pointer();

			return *bytePtrs;
		}

		VIRTUAL operator PCCHAR() const
		{
			return (PCCHAR)this->operator PCBYTE();
		}

		VIRTUAL operator PPVCHAR()
		{
			return (PPVCHAR)this->operator PPVBYTE();
		}

		VIRTUAL operator PBYTEFIELD() const
		{
			return *_ByteFieldPtrs;
		}

		VIRTUAL operator PPBYTEFIELD()
		{
			return _ByteFieldPtrs;
		}

		VIRTUAL BIT operator[](SIZE i) const
		{
			return this->Bit(i);
		}

		VIRTUAL BITREF operator[](SIZE i)
		{
			return this->Bit(i);
		}

		VIRTUAL CSIZE Size() const
		{
			return sizeof(TYPEOF(*this));
		}

		VIRTUAL SIZE BitWidth() const
		{
			return this->ByteSize() * BitPack::BitSize();
		}

		VIRTUAL SIZE ByteSize() const
		{
			return T_SIZE;
		}

		VIRTUAL BIT Bit(SIZE i) const
		{
			return (BIT)this->Bit(i);
		}

		VIRTUAL BITREF Bit(SIZE i)
		{
			if (i >= this->BitWidth())
				return BitRef::NULL_OBJECT();

			BYTE byteIdx = i / T_SIZE;
			BYTE bitIdx = i % T_SIZE;

			return this->Byte(byteIdx).Bit(bitIdx);
		}

		VIRTUAL BIT Flip(SIZE i)
		{
			if (i >= this->BitWidth())
				return BitRef::NULL_OBJECT();

			return this->Bit(i).Flip();
		}

		VIRTUAL PPCBYTEFIELD Bytes() const
		{
			return MAKE_CONST_PP(_ByteFieldPtrs);
		}

		VIRTUAL BYTE Byte(SIZE i) const
		{
			return _ByteFieldPtrs[i]->Value();
		}

		VIRTUAL RIBYTEFIELD Byte(SIZE i)
		{
			if (i >= this->ByteSize())
				return ByteField::NULL_OBJECT();

			return *_ByteFieldPtrs[i];
		}

		VIRTUAL T Value() const
		{
			T tVal = 0;

			for (SIZE i = 0; i < T_SIZE; i++)
				tVal += _ByteFieldPtrs[i]->Value() * (256 << i);

			return tVal;
		}

		VIRTUAL VOID SetValue(T tVal)
		{
			this->~BitField<T>();

			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < this->ByteSize(); i ++)
			#if IS_BIG_ENDIANNESS
				_ByteFieldPtrs[i] = new ByteField(*((PVBYTE)&tVal + T_SIZE - 1 - i));
			#else
				_ByteFieldPtrs[i] = new ByteField(*((PVBYTE)&tVal + i));
			#endif

			_DisposalLevel = DisposalLevel::FieldData;
		}

		VIRTUAL VOID CopyFrom(RCIBITFIELD<T> other)
		{
			this->SetValue(other.Value());
		}

		VOLATILE T * Pointer() const
		{
			return (T *)_ByteFieldPtrs[0]->Pointer();
		}

		VIRTUAL VOID PointTo(VOLATILE T * tPtr)
		{
			this->~BitField<T>();

			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < this->ByteSize(); i ++)
			#if IS_BIG_ENDIANNESS
				_ByteFieldPtrs[i] = new ByteField((PVBYTE)tPtr + T_SIZE - 1 - i);
			#else
				_ByteFieldPtrs[i] = new ByteField((PVBYTE)tPtr + i);
			#endif

			_DisposalLevel = DisposalLevel::FieldData;
		}

		VIRTUAL VOID ReferenceFrom(RCIBITFIELD<T> other)
		{
			this->~BitField<T>();

			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];
			*_ByteFieldPtrs = (PBYTEFIELD)other;

			_DisposalLevel = DisposalLevel::FieldPtrs;
		}

		VIRTUAL T Mask(T tMask) const
		{
			return MASK(this->Value(), tMask);
		}

		VIRTUAL T Mask(RCIBITFIELD<T> other) const
		{
			return MASK(this->Value(), other.Value());
		}

		VIRTUAL PIBITFIELD<T> CloneByValue() const
		{
			return new BitField<T>(this->Value());
		}

		VIRTUAL PIBITFIELD<T> CloneByReference() const
		{
			return new BitField<T>((PTR)_ByteFieldPtrs, T_SIZE);
		}


	protected:

		typedef typename IBitField<T>::DisposalLevel DisposalLevel;

		PPBYTEFIELD _ByteFieldPtrs;

		DisposalLevel _DisposalLevel;
	};


	/* [WORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 16-BIT (WORD) MEMORY BLOCKS */

	CLASS WordField : public BitField<WORD>, public virtual IWordField
	{
	public:

		//using BitField<WORD>::BitField;

		//using BitField<WORD>::Size;

		//using BitField<WORD>::BitWidth;
		//using BitField<WORD>::ByteSize;

		//using BitField<WORD>::operator const WORD;

		//using BitField<WORD>::operator PCBYTE;
		//using BitField<WORD>::operator PPBYTE;

		//using BitField<WORD>::operator PCCHAR;
		//using BitField<WORD>::operator PPCHAR;
		//
		//using BitField<WORD>::operator IttyBitty::PBYTEFIELD;
		//using BitField<WORD>::operator IttyBitty::PPBYTEFIELD;

		//using BitField<WORD>::operator[];

		//using BitField<WORD>::Bit;
		//using BitField<WORD>::Flip;

		//using BitField<WORD>::Bytes;
		//using BitField<WORD>::Byte;

		//using BitField<WORD>::Value;
		//using BitField<WORD>::SetValue;
		//using BitField<WORD>::CopyFrom;

		//using BitField<WORD>::Pointer;
		//using BitField<WORD>::PointTo;
		//using BitField<WORD>::ReferenceFrom;

		//using BitField<WORD>::Mask;

		//using BitField<WORD>::CloneByValue;
		//using BitField<WORD>::CloneByReference;

		WordField() : BitField<WORD>() { }

		WordField(WORD wordVal) : BitField<WORD>()
		{
			this->SetValue(wordVal);
		}

		WordField(RWORD rWord) : BitField<WORD>((PTR)&rWord, 2) { }

		WordField(PWORD pWord) : BitField<WORD>((PTR)pWord, 2) { }

		WordField(BYTEFIELD byteFields[2]) : BitField<WORD>(byteFields) { }

		WordField(PBYTEFIELD byteFieldPtrs[2]) : BitField<WORD>(byteFieldPtrs) { }

		WordField(RCWORDFIELD other) : BitField<WORD>(other) { }

		STATIC RWORDFIELD NULL_OBJECT()
		{
			STATIC WORDFIELD NULL_WORDFIELD((WORD)0);
			return NULL_WORDFIELD;
		}

		BYTE LowByte() const
		{
			return this->Byte(0);
		}

		RIBYTEFIELD SetLowByte(BYTE byteVal)
		{
			RIBYTEFIELD byteField = this->Byte(0);
			byteField.SetValue(byteVal);
			return byteField;
		}

		BYTE HighByte() const
		{
			return this->Byte(1);
		}

		RIBYTEFIELD SetHighByte(BYTE byteVal)
		{
			RIBYTEFIELD byteField = this->Byte(1);
			byteField.SetValue(byteVal);
			return byteField;
		}
	};


	/* [MANYBITFIELD]: TEMPLATED BASE CLASS TO ENCAPSULATE BIT-PACKED MEMORY OF ARBITRARY BYTE-WIDTH */

	template DEFAULT_T_CLAUSE
	CLASS ManyBitField : public BitField<T>, public virtual IManyBitField<T>
	{
	public:

		ManyBitField() : BitField<T>()
		{
			this->InitWordFields();
		}

		ManyBitField(T tVal) : BitField<T>((PVBYTE)&tVal)
		{
			this->InitWordFields();
		}

		EXPLICIT ManyBitField(PTR memAddr, SIZE byteWidth = T_SIZE) : BitField<T>(memAddr, byteWidth)
		{
			this->InitWordFields();
		}

		ManyBitField(BYTE byteVals[T_SIZE]) : BitField<T>(byteVals)
		{
			this->InitWordFields();
		}

		ManyBitField(PVBYTE bytePtrs[T_SIZE]) : BitField<T>(bytePtrs)
		{
			this->InitWordFields();
		}

		ManyBitField(BYTEFIELD byteFields[T_SIZE]) : BitField<T>(byteFields)
		{
			this->InitWordFields();
		}

		ManyBitField(PBYTEFIELD byteFieldPtrs[T_SIZE]) : BitField<T>(byteFieldPtrs)
		{
			this->InitWordFields();
		}

		ManyBitField(WORDFIELD wordFields[T_SIZE / 2])
		{
			PBYTEFIELD byteFieldPtrs[T_SIZE];

			for (SIZE i = 0; i < T_SIZE / 2; i ++)
			{
			#if IS_BIG_ENDIANNESS
				byteFieldPtrs[i * 2] = ((PWORDFIELD)(&wordFields + i))->Byte(T_SIZE - 2 - i * 2);
				byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(&wordFields + i))->Byte(T_SIZE - 1 - i * 2);
			#else
				byteFieldPtrs[i * 2] = ((PWORDFIELD)(&wordFields + i))->Byte(i * 2);
				byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(&wordFields + i))->Byte(i * 2 + 1);
			#endif
			}

			new (this) ManyBitField(byteFieldPtrs);
		}

		ManyBitField(PWORDFIELD wordFields[T_SIZE / 2])
		{
			PBYTEFIELD byteFieldPtrs[T_SIZE];

			for (SIZE i = 0; i < T_SIZE / 2; i ++)
			{
			#if IS_BIG_ENDIANNESS
				byteFieldPtrs[i * 2] = ((PWORDFIELD)(wordFields + i))->Byte(T_SIZE - 2 - i * 2);
				byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(wordFields + i))->Byte(T_SIZE - 1 - i * 2);
			#else
				byteFieldPtrs[i * 2] = ((PWORDFIELD)(wordFields + i))->Byte(i * 2);
				byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(wordFields + i))->Byte(i * 2 + 1);
			#endif
			}

			new (this) ManyBitField(byteFieldPtrs);
		}

		ManyBitField(RCMANYBITFIELD<T> other) : BitField<T>(other)
		{
			this->InitWordFields();
		}

		VIRTUAL ~ManyBitField()
		{
			switch (_DisposalLevel)
			{
			case DisposalLevel::FieldData:

				for (SIZE i = 0; i < T_SIZE; i++)
					delete _WordFieldPtrs[i];

			case DisposalLevel::FieldPtrs:

				delete[] _WordFieldPtrs;
				break;

			case DisposalLevel::FieldPtrPtr:

				delete _WordFieldPtrs;
				break;

			case DisposalLevel::None:

				break;
			}
		}

		STATIC RMANYBITFIELD<T> NULL_OBJECT()
		{
			STATIC MANYBITFIELD<T> NULL_MANYBITFIELD((T)0);
			return NULL_MANYBITFIELD;
		}

		VIRTUAL RMANYBITFIELD<T> operator =(RCMANYBITFIELD<T> other)
		{
			*this = ManyBitField<T>(other);

			return *this;
		}

		VIRTUAL operator PPVWORD() const
		{
			STATIC PPVWORD wordPtrs[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i ++)
				(*wordPtrs)[i] = _WordFieldPtrs[i]->Pointer();

			return *wordPtrs;
		}

		VIRTUAL operator PPVSHORT() const
		{
			return (PPVSHORT)this->operator PPVWORD();
		}

		VIRTUAL SIZE WordSize() const
		{
			return T_SIZE / 2;
		}

		VIRTUAL PPCWORDFIELD Words() const
		{
			return MAKE_CONST_PP(_WordFieldPtrs);
		}

		VIRTUAL WORD Word(SIZE i) const
		{
			return (WORD)this->Word(i);
		}

		VIRTUAL RIWORDFIELD Word(SIZE i)
		{
			if (i > this->ByteSize() / 2)
				return WordField::NULL_OBJECT();

			return *_WordFieldPtrs[i];
		}


	protected:

		typedef typename IBitField<T>::DisposalLevel DisposalLevel;

		using BitField<T>::_DisposalLevel;

		PPWORDFIELD _WordFieldPtrs;


		VIRTUAL VOID InitWordFields()
		{
			if (_WordFieldPtrs)
				delete[] _WordFieldPtrs;

			_WordFieldPtrs = new PWORDFIELD[this->WordSize()];

			for (SIZE i = 0; i < this->WordSize(); i++)
			#if IS_BIG_ENDIANNESS
				_WordFieldPtrs[i] = new WordField((PBYTEFIELD)(this->Bytes() + T_SIZE - 2 - i * 2));
			#else
				_WordFieldPtrs[i] = new WordField((PBYTEFIELD)(this->Bytes() + i * 2));
			#endif
		}
	};


	/* [DWORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 32-BIT (DOUBLE WORD) MEMORY BLOCKS */

	CLASS DWordField : public ManyBitField<DWORD>, public virtual IDWordField
	{
	public:

		DWordField() : ManyBitField<DWORD>() { }

		DWordField(DWORD wordVal) : ManyBitField<DWORD>()
		{
			this->SetValue(wordVal);
		}

		DWordField(RDWORD rDWord) : ManyBitField<DWORD>((PTR)&rDWord, 4) { }

		DWordField(PDWORD pDWord) : ManyBitField<DWORD>((PTR)pDWord, 4) { }

		DWordField(BYTEFIELD byteFields[4]) : ManyBitField<DWORD>(byteFields) { }

		DWordField(PBYTEFIELD byteFieldPtrs[4]) : ManyBitField<DWORD>(byteFieldPtrs) { }

		DWordField(WORDFIELD wordFields[2]) : ManyBitField<DWORD>(wordFields) { }

		DWordField(PWORDFIELD wordFieldPtrs[2]) : ManyBitField<DWORD>(wordFieldPtrs) { }

		DWordField(RCDWORDFIELD other) : ManyBitField<DWORD>(other) { }

		STATIC RDWORDFIELD NULL_OBJECT()
		{
			STATIC DWORDFIELD NULL_DWORDFIELD((DWORD)0);
			return NULL_DWORDFIELD;
		}

		WORD LowWord() const
		{
			return this->Word(0);
		}

		RIWORDFIELD SetLowWord(WORD wordVal)
		{
			RIWORDFIELD wordField = this->Word(0);
			wordField.SetValue(wordVal);
			return wordField;
		}

		WORD HighWord() const
		{
			return this->Word(1);
		}

		RIWORDFIELD SetHighWord(WORD wordVal)
		{
			RIWORDFIELD wordField = this->Word(1);
			wordField.SetValue(wordVal);
			return wordField;
		}
	};

#endif	// #ifndef NO_ITTYBITTY_FULL_BYTES
}


#endif
