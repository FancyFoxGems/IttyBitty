/*******************************************************************************
* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES, WORDS, DWORDS, ...
*
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*******************************************************************************/

#ifndef _ITTYBITTY_BYTES_H
#define _ITTYBITTY_BYTES_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_bits.h"


/* SUPRESS COMPILER WARNINGS RELATED TO POINTER ARITHMETIC */

IGNORE_WARNING(-Wpointer-arith)


namespace IttyBitty
{
	/* TYPE (FORWARD) DECLARATIONS WITH TYPEDEFS */

	struct _BitProxy;
	typedef struct _BitProxy BitRef, BITREF, * PBITREF, & RBITREF, ** PPBITREF;
	typedef const struct _BitProxy CBITREF, * PCBITREF, & RCBITREF, ** PPCBITREF;

	template<typename T = BYTE>
	class IBitField;
	template<typename T = BYTE>
	using IBITFIELD = IBitField<T>;
	template<typename T = BYTE>
	using PIBITFIELD = IBitField<T> *;
	template<typename T = BYTE>
	using RIBITFIELD = IBitField<T> &;
	template<typename T = BYTE>
	using CIBITFIELD =  const IBitField<T>;
	template<typename T = BYTE>
	using PCIBITFIELD = const IBitField<T> *;
	template<typename T = BYTE>
	using RCIBITFIELD = const IBitField<T> &;
	
	class IByteField;
	typedef class IByteField IBYTEFIELD, * PIBYTEFIELD, & RIBYTEFIELD, ** PPIBYTEFIELD;
	typedef const class IByteField CIBYTEFIELD, * PCIBYTEFIELD, & RCIBYTEFIELD, ** PPCIBYTEFIELD;

	class IWordField;
	typedef class IWordField IWORDFIELD, * PIWORDFIELD, & RIWORDFIELD, ** PPIWORDFIELD;
	typedef const class IWordField CIWORDFIELD, * PCIWORDFIELD, & RCIWORDFIELD, ** PPCIWORDFIELD;

	template<typename T = DWORD>
	class IManyBitField;
	template<typename T = DWORD>
	using IMANYBITFIELD = IManyBitField<T>;
	template<typename T = DWORD>
	using PIMANYBITFIELD = IManyBitField<T> *;
	template<typename T = DWORD>
	using RIMANYBITFIELD = IManyBitField<T> &;
	template<typename T = DWORD>
	using CIMANYBITFIELD =  const IManyBitField<T>;
	template<typename T = DWORD>
	using PCIMANYBITFIELD = const IManyBitField<T> *;
	template<typename T = DWORD>
	using RCIMANYBITFIELD = const IManyBitField<T> &;
	
	class IDWordField;
	typedef class IDWordField IDWORDFIELD, * PIDWORDFIELD, & RIDWORDFIELD, ** PPIDWORDFIELD;
	typedef const class IDWordField CIDWORDFIELD, * PCIDWORDFIELD, & RCIDWORDFIELD, ** PPCIDWORDFIELD;

	template<typename T = BYTE>
	class BitField;
	template<typename T = BYTE>
	using BITFIELD = BitField<T>;
	template<typename T = BYTE>
	using PBITFIELD = BitField<T> *;
	template<typename T = BYTE>
	using RBITFIELD = BitField<T> &;
	template<typename T = BYTE>
	using CBITFIELD =  const BitField<T>;
	template<typename T = BYTE>
	using PCBITFIELD = const BitField<T> *;
	template<typename T = BYTE>
	using RCBITFIELD = const BitField<T> &;
	
	class ByteField;
	typedef class ByteField BYTEFIELD, * PBYTEFIELD, & RBYTEFIELD, ** PPBYTEFIELD;
	typedef const class ByteField CBYTEFIELD, * PCBYTEFIELD, & RCBYTEFIELD, ** PPCBYTEFIELD;

	class WordField;
	typedef class WordField WORDFIELD, * PWORDFIELD, & RWORDFIELD, ** PPWORDFIELD;
	typedef const class WordField CWORDFIELD, * PCWORDFIELD, & RCWORDFIELD, ** PPCWORDFIELD;

	template<typename T = DWORD>
	class ManyBitField;
	template<typename T = DWORD>
	using MANYBITFIELD = ManyBitField<T>;
	template<typename T = DWORD>
	using PMANYBITFIELD = ManyBitField<T> *;
	template<typename T = DWORD>
	using RMANYBITFIELD = ManyBitField<T> &;
	template<typename T = DWORD>
	using CMANYBITFIELD =  const ManyBitField<T>;
	template<typename T = DWORD>
	using PCMANYBITFIELD = const ManyBitField<T> *;
	template<typename T = DWORD>
	using RCMANYBITFIELD = const ManyBitField<T> &;
	
	class DWordField;
	typedef class DWordField DWORDFIELD, * PDWORDFIELD, & RDWORDFIELD, ** PPDWORDFIELD;
	typedef const class DWordField CDWORDFIELD, * PCDWORDFIELD, & RCDWORDFIELD, ** PPCDWORDFIELD;
	

	/* [BITPROXY]: STRUCTURE FOR BIT-/BYTE-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */
			
	STRUCT _BitProxy
	{
	public:
		
		_BitProxy(PIBYTEFIELD, SIZE);
		_BitProxy(RCBITREF);
		
		~_BitProxy();

		STATIC RBITREF NULL_OBJECT();

		operator BIT() const;

		RBITREF operator=(RCBITREF);
		RBITREF operator=(BIT);

		BIT Flip();

	protected:

		PIBYTEFIELD Parent() const;
		BYTE BitMask() const;

	private:

		VOLATILE PIBYTEFIELD _Parent;
		BYTE _BitMask;
	};


	/* [IBITFIELD]: INTERFACE FOR BIT-/BYTE-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template<typename T>
	INTERFACE IBitField
	{
	public:
		
		virtual ~IBitField() { }

		virtual CSIZE Size() const = 0;

		virtual SIZE BitWidth() const = 0;
		virtual SIZE ByteSize() const = 0;

		virtual operator CONST T() const = 0;
		virtual operator SIGNED_TYPE(CONST T)() const = 0;

		virtual operator PCBYTE() const = 0;
		virtual operator PPBYTE() = 0;

		virtual operator PCCHAR() const = 0;
		virtual operator PPCHAR() = 0;
		
		virtual operator PBYTEFIELD() const = 0;
		virtual operator PPBYTEFIELD() = 0;

		virtual BIT operator[](SIZE) const = 0;
		virtual BITREF operator[](SIZE) = 0;

		virtual BIT Bit(SIZE) const = 0;
		virtual BITREF Bit(SIZE) = 0;
		virtual BIT Flip(SIZE) = 0;

		virtual PPCBYTEFIELD Bytes() const = 0;
		virtual BYTE Byte(SIZE) const = 0;
		virtual RIBYTEFIELD Byte(SIZE) = 0;

		virtual T Value() const = 0;
		virtual VOID SetValue(T) = 0;
		virtual VOID CopyFrom(RCIBITFIELD<T>) = 0;

		virtual T * Pointer() const = 0;
		virtual VOID PointTo(T *) = 0;
		virtual VOID ReferenceFrom(RCIBITFIELD<T>) = 0;

		virtual T Mask(T) const = 0;
		virtual T Mask(RCIBITFIELD<T>) const = 0;

		virtual PIBITFIELD<T> CloneByValue() const = 0;
		virtual PIBITFIELD<T> CloneByReference() const = 0;

	protected:

		IBitField() { };

		ENUM DisposalLevel : BYTE
		{
			None = 0,
			FieldPtrPtr = 1,
			FieldPtrs = 2,
			FieldData = 3
		};
	};
	

	/* [IBYTEFIELD]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IByteField : public virtual IBitField<BYTE>
	{
	public:
		
		virtual operator PBYTE() = 0;
		virtual operator RBYTE() = 0;
		
		virtual operator PCHAR() = 0;
		virtual operator RCHAR() = 0;

		virtual operator PCBITPACK() const = 0;
		virtual operator PBITPACK() = 0;

		virtual PIBYTEFIELD CloneByValue() const = 0;
		virtual PIBYTEFIELD CloneByReference() const = 0;

		virtual BYTE LowNybble() const = 0;
		virtual RIBYTEFIELD SetLowNybble(BYTE) = 0;
		virtual BYTE HighNybble() const = 0;
		virtual RIBYTEFIELD SetHighNybble(BYTE) = 0;
	};
	

	/* [IWORDFIELD]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IWordField : public virtual IBitField<WORD>
	{
	public:

		virtual BYTE LowByte() const = 0;
		virtual RIBYTEFIELD SetLowByte(BYTE) = 0;
		virtual BYTE HighByte() const = 0;
		virtual RIBYTEFIELD SetHighByte(BYTE) = 0;
	};


	/* [IMANYBITFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template<typename T>
	INTERFACE IManyBitField : public virtual IBitField<T>
	{
	public:

		virtual SIZE WordSize() const = 0;

		virtual PPCWORDFIELD Words() const = 0;
		virtual WORD Word(SIZE) const = 0;
		virtual RIWORDFIELD Word(SIZE) = 0;
	};


	/* [IDWORDFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	INTERFACE IDWordField : public virtual IManyBitField<DWORD>
	{
	public:

		virtual WORD LowWord() const = 0;
		virtual RIWORDFIELD SetLowWord(WORD) = 0;
		virtual WORD HighWord() const = 0;
		virtual RIWORDFIELD SetHighWord(WORD) = 0;
	};


	/* [BYTEFIELD]: CLASS TO ENCAPSULATE BIT-PACKED SINGLE BYTE REFERENCES */

	CLASS ByteField : public virtual IByteField
	{
	public:

		ByteField();
		ByteField(RCBYTE);
		ByteField(RBYTE);
		ByteField(PBYTE);

		ByteField(RCBYTEFIELD);

		~ByteField();

		STATIC RBYTEFIELD NULL_OBJECT();
		
		// IBitField<BYTE>

		virtual CSIZE Size() const;

		virtual SIZE BitWidth() const;
		virtual SIZE ByteSize() const;

		virtual operator CBYTE() const;
		virtual operator CCHAR() const;

		virtual operator PCBYTE() const;
		virtual operator PPBYTE();
		
		virtual operator PCCHAR() const;
		virtual operator PPCHAR();
		
		virtual operator PBYTEFIELD() const;
		virtual operator PPBYTEFIELD();

		virtual BIT operator[](SIZE) const;
		virtual BITREF operator[](SIZE);

		virtual BIT Bit(SIZE) const;
		virtual BITREF Bit(SIZE);
		virtual BIT Flip(SIZE);

		virtual PPCBYTEFIELD Bytes() const;
		virtual BYTE Byte(SIZE) const;
		virtual RIBYTEFIELD Byte(SIZE);

		virtual BYTE Value() const;
		virtual VOID SetValue(BYTE);
		virtual VOID CopyFrom(RCIBITFIELD<BYTE>);

		virtual PBYTE Pointer() const;
		virtual VOID PointTo(PBYTE);
		virtual VOID ReferenceFrom(RCIBITFIELD<BYTE>);

		virtual BYTE Mask(BYTE) const;
		virtual BYTE Mask(RCIBITFIELD<BYTE>) const;

		// IByteField
		
		virtual operator PBYTE();
		virtual operator RBYTE();
		
		virtual operator PCHAR();
		virtual operator RCHAR();

		virtual operator PCBITPACK() const;
		virtual operator PBITPACK();
		
		virtual PIBYTEFIELD CloneByValue() const;
		virtual PIBYTEFIELD CloneByReference() const;

		virtual BYTE LowNybble() const;
		virtual RIBYTEFIELD SetLowNybble(BYTE);
		virtual BYTE HighNybble() const;
		virtual RIBYTEFIELD SetHighNybble(BYTE);

	protected:

		typedef struct __BitProxy __bitproxy_t, BITPROXY, * PBITPROXY, & RBITPROXY;
		typedef const struct __BitProxy CBITPROXY, * PCBITPROXY, & RCBITPROXY;

		VOLATILE UNION
		{
			PBYTE _pByte;
			PBITPACK _pBitPack;
		}
		PACKED;

		BOOL _DisposeByte;
	};


	/* [BITFIELD]: [IBYTEFIELD] BASE IMPLEMENTATION TO ENCAPSULATE BIT-PACKED BYTE REFERENCES */

	template<typename T>
	CLASS BitField : public virtual IBitField<T>
	{
	public:

		BitField() : _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = (PBYTEFIELD)NULL;
		}

		BitField(T tVal) : _DisposalLevel(DisposalLevel::None)
		{
			this->SetValue(tVal);
		}

		EXPLICIT BitField(PVOID memAddr, SIZE byteWidth = T_SIZE) : _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
			{
				if (i < byteWidth)
					_ByteFieldPtrs[i] = new ByteField((PBYTE)memAddr + i);
				else
					_ByteFieldPtrs[i] = new ByteField((BYTE)0);
			}
		}

		BitField(BYTE byteVals[T_SIZE]) : _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = new ByteField((BYTE)byteVals[i]);
		}

		BitField(PBYTE bytePtrs[T_SIZE]) : _DisposalLevel(DisposalLevel::FieldData)
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = new ByteField(bytePtrs[i]);
		}

		BitField(BYTEFIELD byteFields[T_SIZE]) : _DisposalLevel(DisposalLevel::FieldPtrPtr) // TODO: FieldPtrs?
		{
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];
	
			for (SIZE i = 0; i < T_SIZE; i++)
				_ByteFieldPtrs[i] = &byteFields[i];
		}

		BitField(PBYTEFIELD byteFieldPtrs[T_SIZE]) : _DisposalLevel(DisposalLevel::None)
		{
			_ByteFieldPtrs = byteFieldPtrs;
		}

		BitField(RCBITFIELD<T> other)
		{
			this->~BitField<T>();

			// TODO: Use placement new or EXPLICIT reference assignment?
			//*this = ByteField((PVOID)other.Bytes(), other.ByteSize());
			new (this) BitField<T>((PVOID)other.Bytes(), T_SIZE);
		}

		virtual ~BitField()
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

		virtual CSIZE Size() const
		{
			return sizeof(TYPEOF(*this));
		}

		virtual SIZE BitWidth() const
		{
			return this->ByteSize() * BitPack::BitSize();
		}

		virtual SIZE ByteSize() const
		{
			return T_SIZE;
		}

		virtual operator CONST T() const
		{
			return this->Value();
		}

		virtual operator SIGNED_TYPE(CONST T)() const
		{
			return (SIGNED_TYPE(T))this->Value();
		}

		virtual operator PCBYTE() const
		{
			STATIC BYTE bytes[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i ++)
				bytes[i] = _ByteFieldPtrs[i]->Value();

			return bytes;
		}

		virtual operator PPBYTE()
		{
			STATIC PPBYTE bytePtrs[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i ++)
				(*bytePtrs)[i] = _ByteFieldPtrs[i]->Pointer();

			return *bytePtrs;
		}

		virtual operator PCCHAR() const
		{
			return (PCCHAR)this->operator PCBYTE();
		}

		virtual operator PPCHAR()
		{
			return (PPCHAR)this->operator PPBYTE();
		}

		virtual operator PBYTEFIELD() const
		{
			return *_ByteFieldPtrs;
		}

		virtual operator PPBYTEFIELD()
		{
			return _ByteFieldPtrs;
		}

		virtual BIT operator[](SIZE i) const
		{
			return this->Bit(i);
		}

		virtual BITREF operator[](SIZE i)
		{
			return this->Bit(i);
		}

		virtual BIT Bit(SIZE i) const
		{
			return (BIT)this->Bit(i);
		}

		virtual BITREF Bit(SIZE i)
		{
			if (i >= this->BitWidth())
				return BitRef::NULL_OBJECT();
	
			BYTE byteIdx = i / T_SIZE;
			BYTE bitIdx = i % T_SIZE;

			return this->Byte(byteIdx).Bit(bitIdx);
		}

		virtual BIT Flip(SIZE i)
		{
			if (i >= this->BitWidth())
				return BitRef::NULL_OBJECT();
	
			return this->Bit(i).Flip();
		}

		virtual PPCBYTEFIELD Bytes() const
		{
			return MAKE_CONST_PP(_ByteFieldPtrs);
		}

		virtual BYTE Byte(SIZE i) const
		{
			return _ByteFieldPtrs[i]->Value();
		}

		virtual RIBYTEFIELD Byte(SIZE i)
		{
			if (i >= this->ByteSize())
				return ByteField::NULL_OBJECT();
	
			return *_ByteFieldPtrs[i];
		}

		virtual T Value() const
		{
			T tVal = 0;

			for (SIZE i = 0; i < T_SIZE; i++)
				tVal += _ByteFieldPtrs[i]->Value() * (256 << i);

			return tVal;
		}
				
		virtual VOID SetValue(T tVal)
		{
			this->~BitField<T>();

			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < this->ByteSize(); i ++)
				_ByteFieldPtrs[i] = new ByteField(*((PBYTE)&tVal + i));

			_DisposalLevel = DisposalLevel::FieldData;
		}
		
		virtual VOID CopyFrom(RCIBITFIELD<T> other)
		{	
			this->SetValue(other.Value());
		}
		
		T * Pointer() const
		{
			return (T *)_ByteFieldPtrs[0]->Pointer();
		}
		
		virtual VOID PointTo(T * tPtr)
		{
			this->~BitField<T>();

			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

			for (SIZE i = 0; i < this->ByteSize(); i ++)
				_ByteFieldPtrs[i] = new ByteField((PBYTE)tPtr + i);

			_DisposalLevel = DisposalLevel::FieldData;
		}
		
		virtual VOID ReferenceFrom(RCIBITFIELD<T> other)
		{
			this->~BitField<T>();
	
			_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];
			*_ByteFieldPtrs = (PBYTEFIELD)other;

			_DisposalLevel = DisposalLevel::FieldPtrs;
		}
		
		virtual T Mask(T tMask) const
		{
			return MASK(this->Value(), tMask);
		}
		
		virtual T Mask(RCIBITFIELD<T> other) const
		{
			return MASK(this->Value(), other.Value());
		}
		
		virtual PIBITFIELD<T> CloneByValue() const
		{
			return new BitField<T>(this->Value());
		}
		
		virtual PIBITFIELD<T> CloneByReference() const
		{
			return new BitField<T>((PVOID)_ByteFieldPtrs, T_SIZE);
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

		WordField(RWORD rWord) : BitField<WORD>((PVOID)&rWord, 2) { }

		WordField(PWORD pWord) : BitField<WORD>((PVOID)pWord, 2) { }

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

	template<typename T>
	CLASS ManyBitField : public BitField<T>, public virtual IManyBitField<T>
	{
	public:

		ManyBitField() : BitField<T>()
		{
			this->InitWordFields();
		}

		ManyBitField(T tVal) : BitField<T>((PBYTE)&tVal)
		{
			this->InitWordFields();
		}

		EXPLICIT ManyBitField(PVOID memAddr, SIZE byteWidth = T_SIZE) : BitField<T>(memAddr, byteWidth)
		{
			this->InitWordFields();
		}

		ManyBitField(BYTE byteVals[T_SIZE]) : BitField<T>(byteVals)
		{
			this->InitWordFields();
		}

		ManyBitField(PBYTE bytePtrs[T_SIZE]) : BitField<T>(bytePtrs)
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
			PBYTEFIELD byteFieldPtrs[4];

			for (SIZE i = 0; i < 2; i ++)
			{
				byteFieldPtrs[i * 2] = ((PWORDFIELD)(&wordFields + i))->Byte(i * 2);
				byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(&wordFields + i))->Byte(i * 2 + 1);
			}
	
			this->~ManyBitField();

			// TODO: Use placement new or EXPLICIT reference assignment?
			//*this = ManyBitField(byteFieldPtrs);
			new (this) ManyBitField(byteFieldPtrs);
	
			this->InitWordFields();
		}

		ManyBitField(PWORDFIELD wordFields[T_SIZE / 2])
		{
			PBYTEFIELD byteFieldPtrs[4];

			for (SIZE i = 0; i < 2; i ++)
			{
				byteFieldPtrs[i * 2] = ((PWORDFIELD)(wordFields + i))->Byte(i * 2);
				byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(wordFields + i))->Byte(i * 2 + 1);
			}
	
			this->~ManyBitField();

			// TODO: Use placement new or EXPLICIT reference assignment?
			//*this = ManyBitField(byteFieldPtrs;
			new (this) ManyBitField(byteFieldPtrs);
	
			this->InitWordFields();
		}

		ManyBitField(RCMANYBITFIELD<T> other) : BitField<T>(other)
		{
			this->InitWordFields();
		}

		virtual ~ManyBitField()
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

		virtual SIZE WordSize() const
		{
			return T_SIZE / 2;
		}

		virtual operator PPWORD() const
		{
			STATIC PPWORD wordPtrs[T_SIZE];

			for (SIZE i = 0; i < T_SIZE; i ++)
				(*wordPtrs)[i] = _WordFieldPtrs[i]->Pointer();

			return *wordPtrs;
		}

		virtual operator PPSHORT() const
		{
			return (PPSHORT)this->operator PPWORD();
		}

		virtual PPCWORDFIELD Words() const
		{
			return MAKE_CONST_PP(_WordFieldPtrs);
		}

		virtual WORD Word(SIZE i) const
		{
			return (WORD)this->Word(i);
		}

		virtual RIWORDFIELD Word(SIZE i)
		{
			if (i > this->ByteSize() / 2)
				return WordField::NULL_OBJECT();

			return *_WordFieldPtrs[i];
		}


	protected:

		typedef typename IBitField<T>::DisposalLevel DisposalLevel;

		using BitField<T>::_DisposalLevel;

		PPWORDFIELD _WordFieldPtrs;
		

		virtual VOID InitWordFields()
		{
			if (_WordFieldPtrs != NULL)
				delete[] _WordFieldPtrs;
	
			_WordFieldPtrs = new PWORDFIELD[this->WordSize()];

			for (SIZE i = 0; i < this->WordSize(); i++)
				_WordFieldPtrs[i] = new WordField((PBYTEFIELD)(this->Bytes() + i * 2));
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

		DWordField(RDWORD rDWord) : ManyBitField<DWORD>((PVOID)&rDWord, 4) { }

		DWordField(PDWORD pDWord) : ManyBitField<DWORD>((PVOID)pDWord, 4) { }

		DWordField(BYTEFIELD byteFields[4]) : ManyBitField<DWORD>(byteFields) { }

		DWordField(PBYTEFIELD byteFieldPtrs[4]) : ManyBitField<DWORD>(byteFieldPtrs) { }

		DWordField(WORDFIELD wordFields[2]) : ManyBitField<DWORD>(wordFields) { }

		DWordField(PWORDFIELD wordFieldPtrs[2]) : ManyBitField<DWORD>(wordFieldPtrs) { }
		
		DWordField(RCDWORDFIELD other) : ManyBitField<DWORD>(other) { }

		/*STATIC RDWORDFIELD NULL_OBJECT()
		{
			STATIC DWORDFIELD NULL_DWORDFIELD((DWORD)0);
			return NULL_DWORDFIELD;
		}*/

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
}


#endif
