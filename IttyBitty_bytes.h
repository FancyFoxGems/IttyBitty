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


IGNORE_WARNING(-Wstrict-aliasing)
IGNORE_WARNING(-Wpointer-arith)


/* BIT-PACKING / BIT REFERENCE MACROS */

#define BIT_SIZE(type) static_cast<SIZE>(SIZEOF(type) * 8)

#define PACK_BYTE(byte) (*reinterpret_cast<IttyBitty::PBITPACK>(&byte))
#define _B(byte, i) (BIT)(PACK_BYTE(byte).b##i)

#define BIT0(byte) _B(byte, 0)
#define BIT1(byte) _B(byte, 1)
#define BIT2(byte) _B(byte, 2)
#define BIT3(byte) _B(byte, 3)
#define BIT4(byte) _B(byte, 4)
#define BIT5(byte) _B(byte, 5)
#define BIT6(byte) _B(byte, 6)
#define BIT7(byte) _B(byte, 7)


namespace IttyBitty
{
	/* NYBBLE, BYTE, & WORD MASKS */

	#define LOW_NYBBLE(byte_addr) MASK(byte_addr, WORD_BYTE_MASKS[0])
	#define HIGH_NYBBLE(byte_addr) MASK(byte_addr, WORD_BYTE_MASKS[1])

	#define WORD_LOW_BYTE WORD_BYTE_MASKS[0]
	#define WORD_HIGH_BYTE WORD_BYTE_MASKS[0]


	/* BIT OFFSET, L/H NYBBLE, BYTE, & WORD MASK MAPS */

	CBYTE BYTE_BIT_MASKS[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }; // Primarily for reference
	CBYTE BYTE_NYBBLE_MASKS[] = { 0x0F, 0xF0 };

	CWORD WORD_BIT_MASKS[] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 
		0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };
	CWORD WORD_BYTE_MASKS[] = { 0x00FF, 0xFF00 };

	CDWORD DWORD_BYTE_MASKS[] = { 0x000000FF, 0x00FF0000, 0x0000FF00, 0xFF000000 };
	CDWORD DWORD_WORD_MASKS[] = { 0x0000FFFF, 0xFFFF0000 };
	

	/* [BITPACK]: BITFIELD STRUCT FOR BIT-PACKING / BIT-REFERENCING OF MEMORY BYTES */

	struct _BitPack;
	typedef struct _BitPack _bitpack_t, BitPack, BITPACK, * PBITPACK, & RBITPACK;
	typedef const struct _BitPack CBITPACK, * PCBITPACK, & RCBITPACK;

	BITFIELD _BitPack
	{
	public:

		BIT b0 : 1;
		BIT b1 : 1;
		BIT b2 : 1;
		BIT b3 : 1;
		BIT b4 : 1;
		BIT b5 : 1;
		BIT b6 : 1;
		BIT b7 : 1;

		_BitPack(RCBITPACK other);

		STATIC RCBITPACK NULL_OBJECT();

		STATIC CSIZE Size();
		
		BIT operator[](SIZE i) const;
		
		BIT Bit(SIZE i) const;
	};
	

	/* [BYTEFIELD]: CLASS TO ENCAPSULATE BIT-PACKED BYTE REFERENCES */

	class ByteField;
	typedef class ByteField _bytefield_t, BYTEFIELD, * PBYTEFIELD, & RBYTEFIELD;
	typedef const class ByteField CBYTEFIELD, * PCBYTEFIELD, & RCBYTEFIELD;

	class ByteField
	{
	public:

		struct __BitProxy;
		typedef struct __BitProxy BitRef, BITREF, * PBITREF, & RBITREF;
		typedef const struct __BitProxy CBITREF, * PCBITREF, & RCBITREF;
		
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

		operator RCBITPACK() const;
		operator PBITPACK();

		BIT operator[](SIZE) const;
		BITREF operator[](SIZE);

		BIT Bit(SIZE) const;
		BITREF Bit(SIZE);

		PBYTE ByteRef() const;

		BYTE ByteValue() const;
		PBYTEFIELD SetByteValue(BYTE);

		PBYTEFIELD CopyByte(PBYTE);
		PBYTEFIELD PointTo(PBYTE);

		BYTE Mask(BYTE) const;

		BYTE LowNybble() const;
		PBYTEFIELD SetLowNybble(BYTE);
		BYTE HighNybble() const;
		PBYTEFIELD SetHighNybble(BYTE);

	protected:

		VOLATILE UNION
		{
			PBYTE _pByte;
			PBITPACK _pBitPack;
		}
		PACKED;

		BOOL _DestroyByte;

		typedef struct __BitProxy __bitproxy_t, BITPROXY, * PBITPROXY, & RBITPROXY;
		typedef const struct __BitProxy CBITPROXY, * PCBITPROXY, & RCBITPROXY;
	};
	
	typedef ByteField::BitRef BITREF;
	

	/* [MAPPEDBITS]: BASE CLASS TO ENCAPSULATE BIT-PACKED MEMORY OF ARBITRARY BYTE-WIDTH */

	class MappedBits;
	typedef class MappedBits _mappedbits_t, MAPPEDBITS, * PMAPPEDBITS, & RMAPPEDBITS;
	typedef const class MappedBits CMAPPEDBITS, * PCMAPPEDBITS, & RCMAPPEDBITS;

	CLASS MappedBits
	{
	public:
		
		MappedBits();
		MappedBits(SIZE);
		MappedBits(PVOID, SIZE);
		MappedBits(PBYTEFIELD, SIZE);
		MappedBits(BYTE[], SIZE);
		MappedBits(PBYTE[], SIZE);		// NOTE: BYTEs are copied - not referenced.)
		MappedBits(PBYTEFIELD[], SIZE);	// NOTE: BYTEs are copied - not referenced.)
		
		MappedBits(RCMAPPEDBITS);

		~MappedBits();

		STATIC RCMAPPEDBITS NULL_OBJECT();
		
		CSIZE BitWidth() const;
		CSIZE ByteSize() const;
		CSIZE WordSize() const;
		
		operator PPBYTE() const;

		BIT operator[](SIZE) const;
		BITREF operator[](SIZE);

		BIT Bit(SIZE) const;
		BITREF Bit(SIZE);

		PBYTEFIELD Bytes() const;

		BYTE Byte(SIZE) const;
		virtual PBYTEFIELD Byte(SIZE);

	protected:

		PBYTEFIELD _ByteFields;
		SIZE _ByteSize;
		
		BOOL _DisposeByteFields;
		BOOL _DisposeByteFieldsPtr;
	};
	

	/* [WORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 16-BIT (WORD) MEMORY BLOCKS */

	class WordField;
	typedef class WordField _wordfield_t, WORDFIELD, * PWORDFIELD, & RWORDFIELD;
	typedef const class WordField CWORDFIELD, * PCWORDFIELD, & RCWORDFIELD;

	CLASS WordField : public MappedBits
	{
	public:
		
		WordField();
		WordField(WORD);
		WordField(PWORD);
		WordField(PBYTEFIELD);
		
		WordField(RCWORDFIELD);

		STATIC RCWORDFIELD NULL_OBJECT();

		operator WORD() const;
		operator SHORT() const;
		
		PBYTEFIELD LowByte();
		PBYTEFIELD HighByte();
	};
	

	/* [DWORDFIELD]: CLASS TO ENCAPSULATE BIT-PACKED 32-BIT (DOUBLE WORD) MEMORY BLOCKS */

	class DWordField;
	typedef class DWordField _dwordfield_t, DWORDFIELD, * PDWORDFIELD, & RDWORDFIELD;
	typedef const class DWordField CDWORDFIELD, * PCDWORDFIELD, & RCDWORDFIELD;

	CLASS DWordField : public MappedBits
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

		operator DWORD() const;
		operator LONG() const;
		
		PBYTEFIELD Byte(SIZE);

		WORD Word(SIZE) const;
		RWORDFIELD Word(SIZE);
		
		RWORDFIELD LowWord();
		RWORDFIELD HighWord();

	protected:

		PWORDFIELD _WordFields;
	};
}


#endif
