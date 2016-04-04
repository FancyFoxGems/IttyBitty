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

		STATIC RCBITREF NULL_OBJECT();

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

		virtual operator CONST T() const = 0;
		virtual operator MAKE_SIGNED(CONST T)() const = 0;

		virtual operator PCBYTE() const = 0;
		virtual operator PPBYTE() = 0;

		virtual operator PCCHAR() const = 0;
		virtual operator PPCHAR() = 0;
		
		virtual operator PCIBYTEFIELD() const = 0;
		virtual operator PPIBYTEFIELD() = 0;

		virtual BIT operator[](SIZE) const = 0;
		virtual BITREF operator[](SIZE) = 0;

		virtual BIT Bit(SIZE) const = 0;
		virtual BITREF Bit(SIZE) = 0;
		virtual BIT Flip(SIZE) = 0;

		virtual PPCIBYTEFIELD Bytes() const = 0;
		virtual BYTE Byte(SIZE) const = 0;
		virtual RIBYTEFIELD Byte(SIZE) = 0;

		virtual T Value() const = 0;
		virtual VOID SetValue(T) = 0;
		virtual VOID CopyFrom(RCIBITFIELD<T>) = 0;

		virtual T * Pointer() const = 0;
		virtual VOID PointTo(T *) = 0;
		virtual VOID PointFrom(RCIBITFIELD<T>) = 0;
		
		virtual T & Reference() const = 0;
		virtual VOID SetReference(T &) = 0;
		virtual VOID ReferenceFrom(RCIBITFIELD<T>) = 0;

		virtual T Mask(T) const = 0;
		virtual T Mask(RCIBITFIELD<T>) const = 0;

		virtual PIBITFIELD<T> CloneByValue() const = 0;
		virtual PIBITFIELD<T> CloneByReference() const = 0;

	protected:

		ENUM DisposalLevel : BYTE
		{
			None = 0,
			ByteFieldsPtr = 1,
			//ByteFieldsPtrs = 2,
			ByteFieldsData = 2
		};
	};
	

	/* [IBYTEFIELD]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IByteField : public IBitField<BYTE>
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
		virtual PIBYTEFIELD SetLowNybble(BYTE) = 0;
		virtual BYTE HighNybble() const = 0;
		virtual PIBYTEFIELD SetHighNybble(BYTE) = 0;
	};
	

	/* [IWORDFIELD]: SPECIALIZED TEMPLATE IMPLEMENTATION FOR BIT-PACKED SINGLE-BYTE REFERENCES */

	INTERFACE IWordField : public IBitField<WORD>
	{
	public:
		
		virtual operator PWORD() = 0;
		virtual operator RWORD() = 0;
		
		virtual operator PSHORT() = 0;
		virtual operator RSHORT() = 0;

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

	INTERFACE IDWordField : public IManyBitField<DWORD>
	{
	public:
		
		virtual operator PDWORD() = 0;
		virtual operator RDWORD() = 0;
		
		virtual operator PLONG() = 0;
		virtual operator RLONG() = 0;

		virtual WORD LowWord() const = 0;
		virtual PIWORDFIELD SetLowWord(DWORD) = 0;
		virtual WORD HighWord() const = 0;
		virtual PIWORDFIELD SetHighWord(DWORD) = 0;
	};

	/* [BYTEFIELD]: CLASS TO ENCAPSULATE BIT-PACKED SINGLE BYTE REFERENCES */

	CLASS ByteField : public IByteField
	{
	public:

		ByteField();
		ByteField(RCBYTE);
		ByteField(RBYTE);
		ByteField(PBYTE);

		ByteField(RCBYTEFIELD);

		~ByteField();

		STATIC RCBYTEFIELD NULL_OBJECT();
		
		// IBitField<BYTE>

		virtual CSIZE Size() const;

		virtual SIZE BitWidth() const;
		virtual SIZE ByteSize() const;
		virtual SIZE WordSize() const;

		virtual operator CBYTE() const;
		virtual operator CCHAR() const;

		virtual operator PCBYTE() const;
		virtual operator PPBYTE();
		
		virtual operator PCCHAR() const;
		virtual operator PPCHAR();
		
		virtual operator PCIBYTEFIELD() const;
		virtual operator PPIBYTEFIELD();

		virtual BIT operator[](SIZE) const;
		virtual BITREF operator[](SIZE);

		virtual BIT Bit(SIZE) const;
		virtual BITREF Bit(SIZE);
		virtual BIT Flip(SIZE);

		virtual PPCIBYTEFIELD Bytes() const;
		virtual BYTE Byte(SIZE) const;
		virtual RIBYTEFIELD Byte(SIZE);

		virtual BYTE Value() const;
		virtual VOID SetValue(BYTE);
		virtual VOID CopyFrom(RCIBITFIELD<BYTE>);

		virtual PBYTE Pointer() const;
		virtual VOID PointTo(PBYTE);
		virtual VOID PointFrom(RCIBITFIELD<BYTE>);
		
		virtual RBYTE Reference() const;
		virtual VOID SetReference(RBYTE);
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


	/* [BITFIELD]: [IBYTEFIELD] BASE IMPLEMENTATION TO ENCAPSULATE BIT-PACKED BYTE REFERENCES */

	template<typename T>
	CLASS BitField : public IBitField<T>
	{
	public:

		BitField();
		explicit BitField(PVOID, SIZE = SIZEOF(T));
		BitField(BYTE[SIZEOF(T)]);
		BitField(PBYTE[SIZEOF(T)]);
		BitField(BYTEFIELD[SIZEOF(T)]);
		BitField(PBYTEFIELD[SIZEOF(T)]) ;

		BitField(RCBITFIELD<T>);

		virtual ~BitField();

		STATIC RCBITFIELD<T> NULL_OBJECT();

		virtual CSIZE Size() const;

		virtual SIZE BitWidth() const;
		virtual SIZE ByteSize() const;
		virtual SIZE WordSize() const;

		virtual operator CONST T() const;
		virtual operator MAKE_SIGNED(CONST T)() const;

		virtual operator PCBYTE() const;	// NOTE: NOT thread-safe
		virtual operator PPBYTE();			// NOTE: NOT thread-safe

		virtual operator PCCHAR() const;	// NOTE: NOT thread-safe
		virtual operator PPCHAR();			// NOTE: NOT thread-safe
		
		virtual operator PCIBYTEFIELD() const;
		virtual operator PPIBYTEFIELD();

		virtual BIT operator[](SIZE) const;
		virtual BITREF operator[](SIZE);

		virtual BIT Bit(SIZE) const;
		virtual BITREF Bit(SIZE);
		virtual BIT Flip(SIZE);

		virtual PPCIBYTEFIELD Bytes() const;
		virtual BYTE Byte(SIZE) const;
		virtual RIBYTEFIELD Byte(SIZE);

		virtual T Value() const;
		virtual VOID SetValue(T);
		virtual VOID CopyFrom(RCIBITFIELD<T>);

		virtual T * Pointer() const;
		virtual VOID PointTo(T *);
		virtual VOID PointFrom(RCIBITFIELD<T>);
		
		virtual T & Reference() const;
		virtual VOID SetReference(T &);
		virtual VOID ReferenceFrom(RCIBITFIELD<T>);

		virtual T Mask(T) const;
		virtual T Mask(RCIBITFIELD<T>) const;

		virtual PIBITFIELD<T> CloneByValue() const;
		virtual PIBITFIELD<T> CloneByReference() const;

	protected:

		typedef typename IBitField<T>::DisposalLevel DisposalLevel;

		PPIBYTEFIELD _pByteFields;

		DisposalLevel _DisposalLevel;
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
		
		virtual operator PWORD();
		virtual operator RWORD();
		
		virtual operator PSHORT();
		virtual operator RSHORT();

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
		ManyBitField(SIZE);
		ManyBitField(PVOID, SIZE);
		ManyBitField(PBYTEFIELD, SIZE);
		ManyBitField(BYTE[], SIZE);
		ManyBitField(PBYTE[], SIZE);		// NOTE: BYTEs are copied - not referenced.)
		ManyBitField(PBYTEFIELD[], SIZE);	// NOTE: BYTEs are copied - not referenced.)

		ManyBitField(RCBITFIELD<T>);

		~ManyBitField();

		STATIC RCMANYBITFIELD<T> NULL_OBJECT();

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
		
		virtual operator PDWORD();
		virtual operator RDWORD();
		
		virtual operator PLONG();
		virtual operator RLONG();

		virtual WORD LowWord() const;
		virtual PIWORDFIELD SetLowWord(DWORD);
		virtual WORD HighWord() const;
		virtual PIWORDFIELD SetHighWord(DWORD);
	};
}


#endif
