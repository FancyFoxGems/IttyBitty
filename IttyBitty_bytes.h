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
	/* [IBYTE]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	class IByte;
	typedef class IByte _ibyte_t, IByte, IBYTE, * PIBYTE, & RIBYTE, ** PPIBYTE;;
	typedef const class IByte CIBYTE, * PCIBYTE, & RCIBYTE, ** PPCIBYTE;

	class ByteField;
	typedef class ByteField _bytefield_t, ByteField, BYTEFIELD, * PBYTEFIELD, & RBYTEFIELD, ** PPBYTEFIELD;
	typedef const class ByteField CBYTEFIELD, * PCBYTEFIELD, & RCBYTEFIELD, ** PPCBYTEFIELD;

	template<typename T = BYTE>
	class IBitField;
	template<typename T = BYTE>
	using _ibitfield_t = IBitField<T>;
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

	typedef class IBitField<BYTE> IBYTEFIELD, * PIBYTEFIELD, & RIBYTEFIELD, ** PPIBYTEFIELD;
	typedef const class IBitField<BYTE> CIBYTEFIELD, * PCIBYTEFIELD, & RCIBYTEFIELD, ** PPCIBYTEFIELD;

	template<typename T = BYTE>
	class BitField;
	template<typename T = BYTE>
	using _bitfield_t = BitField<T>;
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

/*	typedef class BitField<BYTE> BYTEFIELD, * PBYTEFIELD, & RBYTEFIELD, ** PPBYTEFIELD;
	typedef const class BitField<BYTE> CBYTEFIELD, * PCBYTEFIELD, & RCBYTEFIELD, ** PPCBYTEFIELD;*/
/*
	template<typename T = BYTE>
	class BitField;
	template<typename T = BYTE>
	typedef class BitField _bitfield_t, BITFIELD, * PBITFIELD, & RBITFIELD;
	template<typename T = BYTE>
	typedef const class BitField CBITFIELD, * PCBITFIELD, & RCBITFIELD;*/

	template<typename T = WORD>
	class IManyBitField;
	template<typename T = WORD>
	using _imanybytefield_t = IManyBitField<T>;
	template<typename T = WORD>
	using IMANYBYTEFIELD = IManyBitField<T>;
	template<typename T = WORD>
	using PIMANYBYTEFIELD = IManyBitField<T> *;
	template<typename T = WORD>
	using RIMANYBYTEFIELD = IManyBitField<T> &;
	template<typename T = WORD>
	using CIMANYBYTEFIELD =  const IManyBitField<T>;
	template<typename T = WORD>
	using PCIMANYBYTEFIELD = const IManyBitField<T> *;
	template<typename T = WORD>
	using RCIMANYBYTEFIELD = const IManyBitField<T> &;

	typedef class IManyBitField<WORD> IWORDFIELD, * PIWORDFIELD, & RIWORDFIELD, ** PPIWORDFIELD;
	typedef const class IManyBitField<WORD> CIWORDFIELD, * PCIWORDFIELD, & RCIWORDFIELD, ** PPCIWORDFIELD;
	
	class WordField;
	typedef class WordField _wordfield_t, WORDFIELD, * PWORDFIELD, & RWORDFIELD;
	typedef const class WordField CWORDFIELD, * PCWORDFIELD, & RCWORDFIELD;

	class DWordField;
	typedef class DWordField _dwordfield_t, DWORDFIELD, * PDWORDFIELD, & RDWORDFIELD;
	typedef const class DWordField CDWORDFIELD, * PCDWORDFIELD, & RCDWORDFIELD;


	INTERFACE IByte
	{
	public:

		virtual ~IByte() = 0;

		virtual BYTE LowNybble() const = 0;
		virtual PIBYTE SetLowNybble(BYTE) = 0;
		virtual BYTE HighNybble() const = 0;
		virtual PIBYTE SetHighNybble(BYTE) = 0;
	};


	/* [BITTYBYTE]: CLASS TO ENCAPSULATE BIT-PACKED SINGLE BYTE REFERENCES */

	CLASS ByteField : IByte
	{
	public:

		struct __BitProxy;
		typedef struct __BitProxy BitRef, BITREF, * PBITREF, & RBITREF;
		typedef const struct __BitProxy CBITREF, * PCBITREF, & RCBITREF;

		/*struct __BitProxy
		{
			operator BIT() const;

			__BitProxy& operator=(RCBITREF);
			__BitProxy& operator=(BIT);

			BIT Flip();
		};
*/
		ByteField();
		ByteField(RCBYTE);
		ByteField(RBYTE);
		ByteField(PBYTE);

		ByteField(RCBYTEFIELD);

		~ByteField();

		STATIC RCBITREF NULL_BITREF();
		STATIC RCBYTEFIELD NULL_OBJECT();

		STATIC CSIZE Size();
		STATIC CSIZE ByteSize();

		operator BYTE() const;
		operator PBYTE();
		operator RBYTE();

		operator CHAR() const;
		operator PCHAR();
		operator RCHAR();

		operator PCBITPACK() const;
		operator PBITPACK();

		BIT operator[](SIZE) const;
		BITREF operator[](SIZE);

		BIT Bit(SIZE) const;
		BITREF Bit(SIZE);
		BITREF Flip(SIZE);

		PBYTE ByteRef() const;

		BYTE ByteValue() const;
		PBYTEFIELD SetByteValue(BYTE);

		PBYTEFIELD CopyByte(PBYTE);
		PBYTEFIELD PointTo(PBYTE);

		BYTE Mask(BYTE) const;

		BYTE LowNybble() const;
		PIBYTE SetLowNybble(BYTE);
		BYTE HighNybble() const;
		PIBYTE SetHighNybble(BYTE);

	protected:

		typedef struct __BitProxy __bitproxy_t, BITPROXY, * PBITPROXY, & RBITPROXY;
		typedef const struct __BitProxy CBITPROXY, * PCBITPROXY, & RCBITPROXY;

		VOLATILE UNION
		{
			PBYTE _pByte;
			PBITPACK _pBitPack;
		}
		PACKED;

		BOOL _DestroyByte;
	};

	typedef ByteField::BitRef BITREF;


	/* [IBITFIELD]: INTERFACE FOR BIT-/BYTE-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template<typename T>
	INTERFACE IBitField
	{
	public:

		virtual ~IBitField() { }

		virtual CSIZE Size() const = 0;

		virtual SIZE BitWidth() const = 0;
		virtual SIZE ByteSize() const = 0;
		virtual SIZE WordSize() const = 0;

		virtual operator T() const = 0;
		virtual operator T*() = 0;
		virtual operator T&() = 0;

		virtual operator MAKE_SIGNED(BYTE)*() const = 0;
		virtual operator MAKE_SIGNED(BYTE)*() = 0;
		virtual operator MAKE_SIGNED(BYTE)&() = 0;
		
		virtual operator PCBYTEFIELD() const = 0;
		virtual operator PBYTEFIELD() const = 0;
		virtual operator PPBYTEFIELD() = 0;
		virtual operator PVOID() = 0;

		virtual BIT operator[](SIZE) const = 0;
		virtual BITREF operator[](SIZE) = 0;

		virtual BIT Bit(SIZE) const = 0;
		virtual BITREF Bit(SIZE) = 0;
		virtual BITREF Flip(SIZE) = 0;

		virtual T Value() const = 0;
		virtual VOID SetValue(T) = 0;
		virtual VOID SetValueFrom(T*) = 0;
		virtual VOID CopyFrom(PCIBITFIELD<T>) = 0;

		virtual PVOID Memory() const = 0;
		virtual VOID SetReference(T&) = 0;
		virtual VOID PointTo(T*) = 0;
		virtual VOID ReferenceFrom(RCIBITFIELD<T>) = 0;

		virtual PCIBYTEFIELD Bytes() const = 0;
		virtual BYTE Byte(SIZE) const = 0;
		virtual PIBYTEFIELD Byte(SIZE) = 0;

		virtual T Mask(T) const = 0;
		virtual T Mask(RCIBITFIELD<T>) const = 0;

		virtual PIBITFIELD<T> CloneByReference() = 0;
		virtual PIBITFIELD<T> CloneByValue() = 0;
	};

	template<>
	INTERFACE IBitField<BYTE> : IByte
	{
	public:

		virtual BYTE LowNybble() const = 0;
		virtual PIBYTE SetLowNybble(BYTE) = 0;
		virtual BYTE HighNybble() const = 0;
		virtual PIBYTE SetHighNybble(BYTE) = 0;
	};


	/* [BITFIELD]: [IBYTEFIELD] BASE IMPLEMENTATION TO ENCAPSULATE BIT-PACKED BYTE REFERENCES */

	template<typename T>
	CLASS BitField : IBitField<T>
	{
	public:

		BitField();
		BitField(SIZE);
		BitField(PVOID, SIZE);
		BitField(BYTEFIELD[], SIZE);
		BitField(PBYTEFIELD[], SIZE) ;

		virtual ~BitField();

		virtual CSIZE Size() const;

		virtual SIZE BitWidth() const;
		virtual SIZE ByteSize() const;
		virtual SIZE WordSize() const;

		virtual operator T() const;
		virtual operator T*();
		virtual operator T&();

		virtual operator MAKE_SIGNED(BYTE)*() const;
		virtual operator MAKE_SIGNED(BYTE)*();
		virtual operator MAKE_SIGNED(BYTE)&();
		
		virtual operator PCBYTEFIELD() const;
		virtual operator PBYTEFIELD() const;
		virtual operator PPBYTEFIELD();
		virtual operator PVOID();

		virtual BIT operator[](SIZE) const;
		virtual BITREF operator[](SIZE);

		virtual BIT Bit(SIZE) const;
		virtual BITREF Bit(SIZE);
		virtual BITREF Flip(SIZE);

		virtual T Value() const;
		virtual VOID SetValue(T);
		virtual VOID SetValueFrom(T*);
		virtual VOID CopyFrom(PCIBITFIELD<T>);

		virtual PVOID Memory() const;
		virtual VOID SetReference(T&);
		virtual VOID PointTo(T*);
		virtual VOID ReferenceFrom(RCIBITFIELD<T>);

		virtual PCIBYTEFIELD Bytes() const;
		virtual BYTE Byte(SIZE) const;
		virtual PIBYTEFIELD Byte(SIZE);

		virtual T Mask(T) const;
		virtual T Mask(RCIBITFIELD<T>) const;

		virtual PIBITFIELD<T> CloneByReference();
		virtual PIBITFIELD<T> CloneByValue();

	protected:

		PBYTEFIELD _ByteFields;
		SIZE _ByteSize;

		BOOL _DisposeBitFields;
		BOOL _DisposeBitFieldsPtr;
	};


	/* [BITFIELD<BYTE>]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	template<>
	CLASS BitField<BYTE> : IBitField<BYTE>
	{
	public:

		BitField();
		BitField(SIZE);
		BitField(PVOID, SIZE);
		BitField(BYTEFIELD[], SIZE);
		BitField(PBYTEFIELD[], SIZE) ;

		BYTE LowNybble() const;
		PIBYTE SetLowNybble(BYTE);
		BYTE HighNybble() const;
		PIBYTE SetHighNybble(BYTE);
	};


	/* [BITFIELD]: TEMPLATED BASE CLASS TO ENCAPSULATE BIT-PACKED MEMORY OF ARBITRARY BYTE-WIDTH */

	//template<typename T>
	//CLASS BitField : public IBitField<T>
	//{
	//public:

	//	BitField();
	//	explicit BitField(SIZE);
	//	BitField(PVOID, SIZE);
	//	BitField(PBYTEFIELD, SIZE);
	//	BitField(BYTE[], SIZE);
	//	BitField(PBYTE[], SIZE);		// NOTE: BYTEs are copied - not referenced.)
	//	BitField(PBYTEFIELD[], SIZE);	// NOTE: BYTEs are copied - not referenced.)

	//	BitField(RCBITFIELD);

	//	~BitField();

	//	STATIC RCBITFIELD NULL_OBJECT();

	//	CSIZE BitWidth() const;
	//	CSIZE ByteSize() const;
	//	CSIZE WordSize() const;

	//	operator PPBYTE() const;

	//	BIT operator[](SIZE) const;
	//	BITREF operator[](SIZE);

	//	BIT Bit(SIZE) const;
	//	BITREF Bit(SIZE);

	//	PBYTEFIELD Bytes() const;

	//	BYTE Byte(SIZE) const;
	//	virtual PBYTEFIELD Byte(SIZE);

	//	virtual PBYTE Mask(RCBITFIELD) const;

	//protected:

	//	PBYTEFIELD _BitFields;
	//	SIZE _ByteSize;

	//	BOOL _DisposeBitFields;
	//	BOOL _DisposeBitFieldsPtr;
	//};


	/* [IMANYBYTEFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template<typename T>
	INTERFACE IManyBitField : public IBitField<T>
	{
	public:

		virtual SIZE WordSize() const = 0;

		virtual PCIWORDFIELD Words() const = 0;
		virtual WORD Word(SIZE) const = 0;
		virtual PIWORDFIELD Word(SIZE) = 0;
	};

	INTERFACE IWord
	{
	public:

		virtual PIBYTEFIELD LowByte() = 0;
		virtual PIBYTEFIELD HighByte() = 0;
	};


	/* [WORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 16-BIT (WORD) MEMORY BLOCKS */

	CLASS WordField : public BitField<WORD>//, public IManyBitField<WORD>, public IWord
	{
	public:

		WordField();
		WordField(WORD);
		WordField(PWORD);
		WordField(PBYTEFIELD);

		WordField(RCWORDFIELD);

		STATIC RCWORDFIELD NULL_OBJECT();

		virtual PIBYTEFIELD LowByte();
		virtual PIBYTEFIELD HighByte();

	protected:

		PWORDFIELD _WordFields;
	};


	/* [DWORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 32-BIT (DOUBLE WORD) MEMORY BLOCKS */

	CLASS DWordField : public BitField<DWORD>, public IManyBitField<DWORD>
	{
	public:

		DWordField();
		DWordField(DWORD);
		DWordField(PDWORD);
		DWordField(PBYTEFIELD);
		DWordField(PWORDFIELD);
		DWordField(PWORDFIELD[]);

		DWordField(RCDWORDFIELD);

		~DWordField();

	private:

		VOID InitWordFields();

	public:

		WORD Word(SIZE) const;
		PIWORDFIELD Word(SIZE);

		RWORDFIELD LowWord();
		RWORDFIELD HighWord();
	};
}


#endif
