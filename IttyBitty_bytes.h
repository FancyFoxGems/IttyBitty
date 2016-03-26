/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#ifndef _ITTYBITTY_BYTES_H
#define _ITTYBITTY_BYTES_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_bits.h"


/* BIT-PACKING / BIT REFERENCE MACROS */

#define BIT_SIZE(type) (sizeof(type) * 8)

IGNORE_WARNING(-Wstrict-aliasing)
#define PACK_BYTE(byte) (*((IttyBitty::PBITPACK)&byte))
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

	#define LOW_NYBBLE(byte_addr) BMASK(byte_addr, WORD_BYTE_MASKS[0])
	#define HIGH_NYBBLE(byte_addr) WORD_BYTE_MASKS[0]

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
	

	struct _BitPack;
	typedef struct _BitPack bitpack_t, BitPack, BITPACK, * PBITPACK, & RBITPACK;
	typedef const struct _BitPack CBITPACK, * PCBITPACK, & RCBITPACK;

	PACKED_STRUCT _BitPack
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

		CSIZE Size() const;
		
		BIT operator[](SIZE i) const;
		
		BIT Bit(SIZE i) const;
	};
	

	class ByteField;
	typedef class ByteField bytefield_t, BYTEFIELD, * PBYTEFIELD, & RBYTEFIELD;
	typedef const class ByteField CBYTEFIELD, * PCBYTEFIELD, & RCBYTEFIELD;

	class ByteField
	{
	public:

		struct __BitProxy;
		typedef struct __BitProxy BitRef, BITREF;
		typedef const struct __BitProxy CBITREF;

		ByteField(BYTE);
		ByteField(RBYTE);
		ByteField(PBYTE);

		~ByteField();

		CSIZE Size() const;

		operator BYTE() const;
		operator BYTE();
		
		operator CHAR() const;
		operator CHAR();

		operator BitPack();

		BIT operator[](SIZE) const;
		BITREF operator[](SIZE);

		BIT Bit(SIZE) const;
		BITREF Bit(SIZE);

		BYTE ByteValue() const;
		PBYTEFIELD SetByteValue(BYTE);

		PBYTEFIELD CopyByte(PBYTE);
		PBYTEFIELD PointTo(PBYTE);

		BYTE Mask(BYTE) const;

		BYTE LowNybble() const;
		PBYTEFIELD SetLowNybble(BYTE);
		BYTE HighNybble() const;
		PBYTEFIELD SetHighNybble(BYTE);

	private:

		STATIC CBITREF NULL_BITREF;

		VOLATILE UNION
		{
			PBYTE _Byte;
			PBITPACK _Bits;
		}
		PACKED;

		BOOL _DestroyPtr;

		typedef struct __BitProxy _bitproxy_t, BITPROXY, * PBITPROXY, & RBITPROXY;
		typedef const struct __BitProxy CBITPROXY, * PCBITPROXY, & RCBITPROXY;
	};
	
	typedef ByteField::BitRef BITREF;


	class MappedBits;
	typedef class MappedBits mappedbits_t, MAPPEDBITS, * PMAPPEDBITS, & RMAPPEDBITS;
	typedef const class MappedBits CMAPPEDBITS, * PCMAPPEDBITS, & RCMAPPEDBITS;

	CLASS MappedBits
	{
	protected:

		MappedBits(BYTE);
		MappedBits(BYTE[]);
		MappedBits(PBYTE[]);

	public:

		~MappedBits();

		CSIZE Size() const;

		BIT operator[](SIZE) const;
		BITREF operator[](SIZE);

		BIT Bit(SIZE) const;
		BITREF Bit(SIZE);

		CONST RBYTEFIELD Byte(SIZE i) const;
		RBYTEFIELD Byte(SIZE i);

	protected:

		STATIC CBYTEFIELD NULL_BYTEFIELD;

		PBYTEFIELD _Bits;
	};
	

	class WordField;
	typedef class WordField wordfield_t, WORDFIELD, * PWORDFIELD, & RWORDFIELD;
	typedef const class WordField CWORDFIELD, * PCWORDFIELD, & RCWORDFIELD;

	CLASS WordField : MappedBits
	{
	public:

		operator WORD() const;
		operator WORD();
		
		operator SHORT() const;
		operator SHORT();
		
		CONST RBYTEFIELD LowByte() const;
		CONST RBYTEFIELD HighByte() const;
	};


	class DWordField;
	typedef class DWordField dwordfield_t, DWORDFIELD, * PDWORDFIELD, & RDWORDFIELD;
	typedef const class DWordField CDWORDFIELD, * PCDWORDFIELD, & RCDWORDFIELD;

	CLASS DWordField : MappedBits
	{
	public:

		operator DWORD() const;
		operator DWORD();
		
		operator LONG() const;
		operator LONG();

		CONST RWORDFIELD Word(SIZE i) const;
		RWORDFIELD Word(SIZE i);
		
		CONST RWORDFIELD LowWord() const;
		CONST RWORDFIELD HighWord() const;
	};
}


#endif
