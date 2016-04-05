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


/* SUPRESS COMPILER WARNINGS RELATED TO BITFIELD ALIASING */

IGNORE_WARNING(-Wstrict-aliasing)


/* SUPRESS COMPILER WARNINGS RELATED TO BITFIELD ALIASING AND POINTER ARITHMETIC */

IGNORE_WARNING(-Wstrict-aliasing)
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

		virtual PCIWORDFIELD Words() const = 0;
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

		BitField();
		BitField(T);
		BitField(T *);
		explicit BitField(PVOID, SIZE = T_SIZE);
		BitField(BYTE[T_SIZE]);
		BitField(PBYTE[T_SIZE]);
		BitField(BYTEFIELD[T_SIZE]);
		BitField(PBYTEFIELD[T_SIZE]) ;

		BitField(RCBITFIELD<T>);

		virtual ~BitField();

		STATIC RBITFIELD<T> NULL_OBJECT();

		virtual CSIZE Size() const;

		virtual SIZE BitWidth() const;
		virtual SIZE ByteSize() const;

		virtual operator CONST T() const;
		virtual operator SIGNED_TYPE(CONST T)() const;

		virtual operator PCBYTE() const;	// NOTE: NOT thread-safe
		virtual operator PPBYTE();			// NOTE: NOT thread-safe

		virtual operator PCCHAR() const;	// NOTE: NOT thread-safe
		virtual operator PPCHAR();			// NOTE: NOT thread-safe
		
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

		virtual T Value() const;
		virtual VOID SetValue(T);
		virtual VOID CopyFrom(RCIBITFIELD<T>);

		virtual T * Pointer() const;
		virtual VOID PointTo(T *);
		virtual VOID ReferenceFrom(RCIBITFIELD<T>);

		virtual T Mask(T) const;
		virtual T Mask(RCIBITFIELD<T>) const;

		virtual PIBITFIELD<T> CloneByValue() const;
		virtual PIBITFIELD<T> CloneByReference() const;

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

		INLINE WordField();
		INLINE WordField(WORD);
		INLINE WordField(RWORD);
		INLINE WordField(PWORD);
		INLINE WordField(BYTEFIELD[2]);
		INLINE WordField(PBYTEFIELD[2]);

		INLINE WordField(RCWORDFIELD);

		~WordField();

		STATIC RWORDFIELD NULL_OBJECT();

		virtual BYTE LowByte() const;
		virtual RIBYTEFIELD SetLowByte(BYTE);
		virtual BYTE HighByte() const;
		virtual RIBYTEFIELD SetHighByte(BYTE);

	protected:

		PWORD _pWord;
	};


	/* [MANYBITFIELD]: TEMPLATED BASE CLASS TO ENCAPSULATE BIT-PACKED MEMORY OF ARBITRARY BYTE-WIDTH */

	template<typename T>
	CLASS ManyBitField : public BitField<T>, public virtual IManyBitField<T>
	{
	public:

		INLINE ManyBitField();
		INLINE ManyBitField(T);
		INLINE ManyBitField(T *);
		INLINE explicit ManyBitField(PVOID, SIZE = T_SIZE);
		INLINE ManyBitField(BYTE[T_SIZE]);
		INLINE ManyBitField(PBYTE[T_SIZE]);
		INLINE ManyBitField(BYTEFIELD[T_SIZE]);
		INLINE ManyBitField(PBYTEFIELD[T_SIZE]);
		INLINE ManyBitField(WORDFIELD[T_SIZE / 2]);
		INLINE ManyBitField(PWORDFIELD[T_SIZE / 2]);

		INLINE ManyBitField(RCMANYBITFIELD<T>);

		virtual ~ManyBitField();

		STATIC RMANYBITFIELD<T> NULL_OBJECT();

		virtual SIZE WordSize() const;

		virtual operator PPWORD() const;
		virtual operator PPSHORT() const;

		virtual PCIWORDFIELD Words() const;
		virtual WORD Word(SIZE) const;
		virtual RIWORDFIELD Word(SIZE);

	protected:

		typedef typename IBitField<T>::DisposalLevel DisposalLevel;

		using BitField<T>::_DisposalLevel;

		VOID InitWordFields();

		PPWORDFIELD _WordFieldPtrs;
	};


	/* [DWORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 32-BIT (DOUBLE WORD) MEMORY BLOCKS */

	CLASS DWordField : public ManyBitField<DWORD>, public virtual IDWordField
	{
	public:

		INLINE DWordField();
		INLINE DWordField(DWORD);
		INLINE DWordField(RDWORD);
		INLINE DWordField(PDWORD);
		INLINE DWordField(BYTEFIELD[4]);
		INLINE DWordField(PBYTEFIELD[4]);
		INLINE DWordField(WORDFIELD[2]);
		INLINE DWordField(PWORDFIELD[2]);

		INLINE DWordField(RCDWORDFIELD);

		~DWordField();

		STATIC RDWORDFIELD NULL_OBJECT();

		virtual WORD LowWord() const;
		virtual RIWORDFIELD SetLowWord(WORD);
		virtual WORD HighWord() const;
		virtual RIWORDFIELD SetHighWord(WORD);
	};
}


#endif
