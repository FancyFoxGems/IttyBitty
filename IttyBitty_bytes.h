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

	typedef class IByteField IBYTEFIELD, * PIBYTEFIELD, & RIBYTEFIELD, ** PPIBYTEFIELD;
	typedef const class IByteField CIBYTEFIELD, * PCIBYTEFIELD, & RCIBYTEFIELD, ** PPCIBYTEFIELD;

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

	typedef class ByteField BYTEFIELD, * PBYTEFIELD, & RBYTEFIELD, ** PPBYTEFIELD;
	typedef const class ByteField CBYTEFIELD, * PCBYTEFIELD, & RCBYTEFIELD, ** PPCBYTEFIELD;

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

	typedef class DWordField DWORDFIELD, * PDWORDFIELD, & RDWORDFIELD, ** PPDWORDFIELD;
	typedef const class DWordField CDWORDFIELD, * PCDWORDFIELD, & RCDWORDFIELD, ** PPCDWORDFIELD;


	/* [BITPROXY]: STRUCTURE FOR BIT-/BYTE-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */
			
	STRUCT _BitProxy
	{
	public:
		
		_BitProxy(PIBYTEFIELD, SIZE);
		_BitProxy(RCBITREF);
		
		~_BitProxy();

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
		virtual SIZE WordSize() const = 0;

		virtual operator T() const = 0;
		virtual operator T*() = 0;
		virtual operator T&() = 0;

		virtual operator MAKE_SIGNED(BYTE)() const = 0;
		virtual operator MAKE_SIGNED(BYTE)*() = 0;
		virtual operator MAKE_SIGNED(BYTE)&() = 0;

		virtual operator PPBYTE() const = 0;
		virtual operator PPCHAR() const = 0;
		
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
	

	/* [IBYTEFIELD]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IByteField : public IBitField<BYTE>
	{
	public:

		virtual operator PCBITPACK() const = 0;
		virtual operator PBITPACK() = 0;

		virtual PBYTE ByteRef() const = 0;

		virtual BYTE LowNybble() const = 0;
		virtual PIBYTEFIELD SetLowNybble(BYTE) = 0;
		virtual BYTE HighNybble() const = 0;
		virtual PIBYTEFIELD SetHighNybble(BYTE) = 0;
	};
	

	/* [IWORDFIELD]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IWordField : public IBitField<WORD>
	{
	public:

		virtual BYTE LowByte() const = 0;
		virtual PIBYTEFIELD SetLowByte(BYTE) = 0;
		virtual BYTE HighByte() const = 0;
		virtual PIBYTEFIELD SetHighByte(BYTE) = 0;
	};


	/* [IMANYBITFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	template<typename T>
	INTERFACE IManyBitField : public IBitField<T>
	{
	public:

		virtual SIZE WordSize() const = 0;

		virtual operator PPWORD() const = 0;
		virtual operator PPSHORT() const = 0;

		virtual PCIWORDFIELD Words() const = 0;
		virtual WORD Word(SIZE) const = 0;
		virtual PIWORDFIELD Word(SIZE) = 0;
	};


	/* [IDWORDFIELD]: INTERFACE FOR WORD-ADDRESSABLE BITMAPPED-MEMORY DATA STRUCTURES */

	INTERFACE IDWordField : IManyBitField<DWORD>
	{
	public:

		virtual WORD LowWord() const = 0;
		virtual PIWORDFIELD SetLowWord(DWORD) = 0;
		virtual WORD HighWord() const = 0;
		virtual PIWORDFIELD SetHighWord(DWORD) = 0;
	};


	/* [BITFIELD]: [IBYTEFIELD] BASE IMPLEMENTATION TO ENCAPSULATE BIT-PACKED BYTE REFERENCES */

	template<typename T>
	CLASS BitField : public IBitField<T>
	{
	public:

		BitField();
		BitField(SIZE);
		BitField(PVOID, SIZE);
		//BitField(BYTEFIELD[], SIZE);
		BitField(PBYTEFIELD[], SIZE) ;

		virtual ~BitField();

		virtual CSIZE Size() const;

		virtual SIZE BitWidth() const;
		virtual SIZE ByteSize() const;
		virtual SIZE WordSize() const;

		virtual operator T() const;
		virtual operator T*();
		virtual operator T&();

		virtual operator MAKE_SIGNED(BYTE)() const;
		virtual operator MAKE_SIGNED(BYTE)*();
		virtual operator MAKE_SIGNED(BYTE)&();

		virtual operator PPBYTE() const;
		virtual operator PPCHAR() const;
		
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

		BOOL _DisposeByteFields;
		BOOL _DisposeByteFieldsPtr;
	};

	/* [BYTEFIELD]: CLASS TO ENCAPSULATE BIT-PACKED SINGLE BYTE REFERENCES */

	CLASS ByteField : public BitField<BYTE>, public IByteField
	{
	public:

		/*using BitField<BYTE>::Size;

		using BitField<BYTE>::BitWidth;
		using BitField<BYTE>::ByteSize;
		using BitField<BYTE>::WordSize;

		using BitField<BYTE>::operator BYTE;
		using BitField<BYTE>::operator PBYTE;
		using BitField<BYTE>::operator RBYTE;

		using BitField<BYTE>::operator CHAR;
		using BitField<BYTE>::operator PCHAR;
		using BitField<BYTE>::operator RCHAR;

		using BitField<BYTE>::operator PPBYTE;
		using BitField<BYTE>::operator PPCHAR;
		
		using BitField<BYTE>::operator PCBYTEFIELD;
		using BitField<BYTE>::operator PBYTEFIELD;
		using BitField<BYTE>::operator PPBYTEFIELD;
		using BitField<BYTE>::operator PVOID;

		using BitField<BYTE>::operator[];

		using BitField<BYTE>::Bit;
		using BitField<BYTE>::Flip;

		using BitField<BYTE>::Value;
		using BitField<BYTE>::SetValue;
		using BitField<BYTE>::SetValueFrom;
		using BitField<BYTE>::CopyFrom;

		using BitField<BYTE>::Memory;
		using BitField<BYTE>::SetReference;
		using BitField<BYTE>::PointTo;
		using BitField<BYTE>::ReferenceFrom;

		using BitField<BYTE>::Bytes;
		using BitField<BYTE>::Byte;

		using BitField<BYTE>::Mask;

		using BitField<BYTE>::CloneByReference;
		using BitField<BYTE>::CloneByValue;
*/
		ByteField();
		ByteField(RCBYTE);
		ByteField(RBYTE);
		ByteField(PBYTE);

		ByteField(RCBYTEFIELD);

		~ByteField();

		STATIC RCBITREF NULL_BITREF();
		STATIC RCBYTEFIELD NULL_OBJECT();

		virtual operator PCBITPACK() const;
		virtual operator PBITPACK();

		virtual PBYTE ByteRef() const;

		virtual BYTE LowNybble() const;
		virtual PIBYTEFIELD SetLowNybble(BYTE);
		virtual BYTE HighNybble() const;
		virtual PIBYTEFIELD SetHighNybble(BYTE);

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


	/* [WORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 16-BIT (WORD) MEMORY BLOCKS */

	CLASS WordField : public BitField<WORD>, public IWordField
	{
	public:

		WordField();
		WordField(RCWORD);
		WordField(RWORD);
		WordField(PWORD);
		//WordField(BYTEFIELD[]);

		WordField(RCWORDFIELD);

		STATIC RCWORDFIELD NULL_OBJECT();

		virtual PIBYTEFIELD LowByte();
		virtual PIBYTEFIELD HighByte();

	protected:

		PWORDFIELD _WordFields;
	};


	/* [MANYBITFIELD]: TEMPLATED BASE CLASS TO ENCAPSULATE BIT-PACKED MEMORY OF ARBITRARY BYTE-WIDTH */

	template<typename T>
	CLASS ManyBitField : public BitField<T>, public IManyBitField<T>
	{
	public:

		ManyBitField();
		explicit ManyBitField(SIZE);
		ManyBitField(PVOID, SIZE);
		ManyBitField(PBYTEFIELD, SIZE);
		ManyBitField(BYTE[], SIZE);
		ManyBitField(PBYTE[], SIZE);		// NOTE: BYTEs are copied - not referenced.)
		ManyBitField(PBYTEFIELD[], SIZE);	// NOTE: BYTEs are copied - not referenced.)

		ManyBitField(RCBITFIELD<T>);

		~ManyBitField();

		virtual SIZE WordSize() const;

		virtual operator PPWORD() const;
		virtual operator PPSHORT() const;

		virtual PCIWORDFIELD Words() const;
		virtual WORD Word(SIZE) const;
		virtual PIWORDFIELD Word(SIZE);

	protected:

		VOID InitWordFields();

		PWORDFIELD _WordFields;
	};


	/* [DWORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 32-BIT (DOUBLE WORD) MEMORY BLOCKS */

	CLASS DWordField : public ManyBitField<DWORD>, public IDWordField
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

	public:

		virtual WORD LowWord() const;
		virtual PIWORDFIELD SetLowWord(DWORD);
		virtual WORD HighWord() const;
		virtual PIWORDFIELD SetHighWord(DWORD);
	};
}


#endif
