/************************************************************
* Copyright � 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#include "IttyBitty_bytes.h"

using namespace IttyBitty;


/* [BITPACK] DEFINITION */

#define __BIT(i) (this->b##i)

_BitPack::_BitPack(RCBITPACK other)
{
	*this = other;
}

CSIZE _BitPack::Size()
{
	return BIT_SIZE(_BitPack);
}

BIT _BitPack::operator[](SIZE i) const
{
	return this->Bit(i);
}

BIT _BitPack::Bit(SIZE i) const
{
	if (i >= Size())
		return NULL;
	
	switch (i)
	{
	case 0:
		return __BIT(0);
	case 1:
		return __BIT(1);
	case 2:
		return __BIT(2);
	case 3:
		return __BIT(3);
	case 4:
		return __BIT(4);
	case 5:
		return __BIT(5);
	case 6:
		return __BIT(6);
	case 7:
		return __BIT(7);
	default:
		return NULL;
	}
}


/* [BITPROXY/BITREF]: NESTED PROXY CLASS TO ALLOW FOR INDIVIDUAL BIT-ADDRESSED MEMORY WRITES */

STRUCT ByteField::__BitProxy
{
public:

	__BitProxy(PBYTEFIELD pParent, SIZE i) : _Parent(pParent), _BitMask(BITMASK(i)) { }

	__BitProxy(RCBITREF other) : _Parent(other.Parent()), _BitMask(other.BitMask()) { }

	~__BitProxy() { }

	operator BIT() const
	{
		return MASK(_Parent->ByteValue(), _BitMask) != 0;
	}
				
	__BitProxy& operator=(CONST RBITPROXY crRValue)
	{
		*this = (BIT)crRValue;
		return *this;
	}
				
	__BitProxy& operator=(BIT bit)
	{
		_Parent->SetByteValue(_Parent->Mask(~_BitMask) | (bit ? _BitMask : (BYTE)0));
		return *this;
	}

	PBYTEFIELD Parent() const
	{
		return _Parent;
	}

	BYTE BitMask() const
	{
		return _BitMask;
	}

private:

	VOLATILE PBYTEFIELD _Parent;
	BYTE _BitMask;
};


/* [BYTEIELD] DEFINITION */

ByteField::ByteField()
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField((BYTE)0);
	new (this) ByteField((BYTE)0);
}

ByteField::ByteField(RCBYTE byteVal) : _pByte(new BYTE(byteVal)), _DestroyByte(true) { }
	
ByteField::ByteField(RBYTE byteRef) : _pByte(&byteRef), _DestroyByte(false) { }
	
ByteField::ByteField(PBYTE pByte) : _pByte(pByte), _DestroyByte(false) { }

ByteField::ByteField(RCBYTEFIELD other)
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField(other.ByteRef());
	new (this) ByteField(other.ByteRef());
}
	
ByteField::~ByteField()
{
	if (_DestroyByte)
		delete _pByte;
}

ByteField::RCBITREF ByteField::NULL_BITREF()
{
	static CBITREF NULL_BITREF(NULL, 0);
	return NULL_BITREF;
}

RCBYTEFIELD ByteField::NULL_OBJECT()
{
	static CBYTEFIELD NULL_BYTEFIELD((BYTE)0);
	return NULL_BYTEFIELD;
}

CSIZE ByteField::Size()
{
	return SIZEOF(ByteField);
}

CSIZE ByteField::ByteSize()
{
	return 1;
}

ByteField::operator BYTE() const
{
	return this->ByteValue();
}

ByteField::operator RBYTE()
{
	return *_pByte;
}

ByteField::operator CHAR() const
{
	return (CHAR)this->ByteValue();
}

ByteField::operator RCHAR()
{
	return (RCHAR)*_pByte;
}

ByteField::operator RCBITPACK() const
{
	return *_pBitPack;
}

ByteField::operator PBITPACK()
{
	return _pBitPack;
}

BIT ByteField::operator[](SIZE i) const
{
	return this->Bit(i);
}

BITREF ByteField::operator[](SIZE i)
{
	return this->Bit(i);
}

BIT ByteField::Bit(SIZE i) const
{
	return MAKE_CONST(_pBitPack)->Bit(i);
}

BITREF ByteField::Bit(SIZE i)
{
	if (i >= _pBitPack->Size())
		return ByteField::NULL_BITREF();

	return BitRef(this, i);
}

PBYTE ByteField::ByteRef() const
{
	return _pByte;
}

BYTE ByteField::ByteValue() const
{
	return *_pByte;
}

PBYTEFIELD ByteField::SetByteValue(BYTE byteVal)
{
	*_pByte = byteVal;
	return this;
}

PBYTEFIELD ByteField::CopyByte(PBYTE pByte)
{
	return this->SetByteValue(*pByte);
}

PBYTEFIELD ByteField::PointTo(PBYTE pByte)
{
	_pByte = pByte;
	return this;
}

BYTE ByteField::Mask(BYTE bitMask) const
{
	return MASK(this->ByteValue(), bitMask);
}

BYTE ByteField::LowNybble() const
{
	return LOW_NYBBLE(this->ByteValue());
}

PBYTEFIELD ByteField::SetLowNybble(BYTE nybbleVal)
{
	*_pByte = (this->HighNybble() << 4) | LOW_NYBBLE(nybbleVal);
	return this;
}

BYTE ByteField::HighNybble() const
{
	return HIGH_NYBBLE(this->ByteValue());
}

PBYTEFIELD ByteField::SetHighNybble(BYTE nybbleVal)
{
	*_pByte = HIGH_NYBBLE(nybbleVal) | this->LowNybble();
	return this;
}



/* [MAPPEDBITS] DEFINITION */

MappedBits::MappedBits() : _DisposeByteFields(false), _DisposeByteFieldsPtr(true)
{
	this->~MappedBits();

	// TODO: Use placement new or explicit reference assignment?
	//*this = MappedBits((BYTE)0);
	new (this) MappedBits((SIZE)0);
}

MappedBits::MappedBits(SIZE byteWidth) : _ByteSize(byteWidth), _DisposeByteFields(true), _DisposeByteFieldsPtr(true)
{
	_ByteFields = new ByteField[_ByteSize];
}

MappedBits::MappedBits(PVOID memAddr, SIZE byteWidth) : _ByteSize(byteWidth), _DisposeByteFields(true), _DisposeByteFieldsPtr(true)
{
	_ByteFields = new ByteField[_ByteSize];

	for (SIZE i = 0; i < _ByteSize; i++)
		_ByteFields[i] = ByteField((PBYTE)memAddr + i);
}

MappedBits::MappedBits(PBYTEFIELD byteFields, SIZE byteWidth) : _ByteSize(byteWidth), _DisposeByteFields(false), _DisposeByteFieldsPtr(false)
{
	_ByteFields = byteFields;
}

MappedBits::MappedBits(BYTE byteVals[], SIZE byteWidth) : _ByteSize(byteWidth), _DisposeByteFields(true), _DisposeByteFieldsPtr(true)
{
	_ByteFields = new ByteField[_ByteSize];

	for (SIZE i = 0; i < _ByteSize; i++)
		_ByteFields[i] = ByteField((BYTE)byteVals[i]);
}

MappedBits::MappedBits(PBYTE pBytes[], SIZE byteWidth) : _ByteSize(byteWidth), _DisposeByteFields(true), _DisposeByteFieldsPtr(true)
{
	_ByteFields = new ByteField[_ByteSize];

	for (SIZE i = 0; i < _ByteSize; i++)
		_ByteFields[i] = ByteField(pBytes[i]);
}

MappedBits::MappedBits(PBYTEFIELD pByteFields[], SIZE byteWidth): _ByteSize(byteWidth), _DisposeByteFields(false), _DisposeByteFieldsPtr(true)
{
	_ByteFields = new ByteField[_ByteSize];

	for (SIZE i = 0; i < _ByteSize; i++)
		_ByteFields[i] = *pByteFields[i];

}

MappedBits::MappedBits(RCMAPPEDBITS other)
{
	this->~MappedBits();

	// TODO: Use placement new or explicit reference assignment?
	//*this = MappedBits((PVOID)other.Bytes(), other.ByteSize());
	new (this) MappedBits((PVOID)other.Bytes(), other.ByteSize());
}

MappedBits::~MappedBits()
{
	if (_DisposeByteFields)
		delete[] _ByteFields;
	else if (_DisposeByteFieldsPtr)
		delete _ByteFields;
}

RCMAPPEDBITS MappedBits::NULL_OBJECT()
{
	static CMAPPEDBITS NULL_MAPPEDBITS((BYTE)0);
	return NULL_MAPPEDBITS;
}
		
CSIZE MappedBits::BitWidth() const
{
	return BITPACK::Size() * this->ByteSize();
}

CSIZE MappedBits::ByteSize() const
{
	return _ByteSize;
}

CSIZE MappedBits::WordSize() const
{
	return _ByteSize / 2;
}

MappedBits::operator PPBYTE() const
{
	static PPBYTE BYTES = new PBYTE[_ByteSize];		// NOTE: NOT thread-safe

	for (SIZE i = 0; i < this->ByteSize(); i ++)
		BYTES[i] = (PBYTE)_ByteFields[i];

	return BYTES;
}

BIT MappedBits::operator[](SIZE i) const
{
	return this->Bit(i);
}

BITREF MappedBits::operator[](SIZE i)
{
	return this->Bit(i);
}

BIT MappedBits::Bit(SIZE i) const
{
	return (BIT)this->Bit(i);
}

BITREF MappedBits::Bit(SIZE i)
{
	if (i >= this->BitWidth())
		return ByteField::NULL_BITREF();
	
	BYTE byteIdx = i / _ByteSize;
	BYTE bitIdx = i % _ByteSize;

	return this->Byte(byteIdx)->Bit(bitIdx);
}

PBYTEFIELD MappedBits::Bytes() const
{
	return _ByteFields;
}

BYTE MappedBits::Byte(SIZE i) const
{
	return ((BYTEFIELD)this->Byte(i)).ByteValue();
}

PBYTEFIELD MappedBits::Byte(SIZE i)
{
	if (i >= this->ByteSize())
		return NULL;
	
	return &_ByteFields[i];
}


/* [WORDFIELD] DEFINITION */

WordField::WordField() : MappedBits(2) { }

WordField::WordField(WORD wordVal) : MappedBits((PBYTE)&wordVal, 2) { }

WordField::WordField(PWORD pWord) : MappedBits((PPBYTE)pWord, 2) { }

WordField::WordField(PBYTEFIELD byteFields) : MappedBits(byteFields, 2) { }
		
WordField::WordField(RCWORDFIELD other) : MappedBits(other) { }

RCWORDFIELD WordField::NULL_OBJECT()
{
	static CWORDFIELD NULL_WORDFIELD((WORD)0);
	return NULL_WORDFIELD;
}

WordField::operator WORD() const
{
	return (WORD)this->operator SHORT();
}
		
WordField::operator SHORT() const
{
	return (((SHORT)(BYTE)this->Byte(1)) << 8) OR (BYTE)this->Byte(0);
}
		
PBYTEFIELD WordField::LowByte()
{
	return this->Byte(0);
}

PBYTEFIELD WordField::HighByte()
{
	return this->Byte(1);
}


/* [DWORDFIELD] DEFINITION */

DWordField::DWordField() : MappedBits(4)
{
	this->InitWordFields();
}

DWordField::DWordField(DWORD dwordVal) : MappedBits((PBYTE)&dwordVal, 4)
{
	this->InitWordFields();
}

DWordField::DWordField(PDWORD pDWord) : MappedBits((PPBYTE)pDWord, 4)
{
	this->InitWordFields();
}

DWordField::DWordField(PBYTEFIELD byteFields) : MappedBits(byteFields, 4)
{
	this->InitWordFields();
}

DWordField::DWordField(PWORDFIELD wordFields)
{
	PBYTEFIELD byteFieldPtrs[4];

	for (SIZE i = 0; i < 2; i ++)
	{
		byteFieldPtrs[i * 2] = ((PWORDFIELD)(wordFields + i))->LowByte();
		byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(wordFields + i))->HighByte();
	}
	
	this->~DWordField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = MappedBits(byteFieldPtrs, 4);
	new (this) MappedBits(byteFieldPtrs, 4);
	
	this->InitWordFields();
}
		
DWordField::DWordField(RCDWORDFIELD other) : MappedBits(other) { }

DWordField::~DWordField()
{
	delete[] _WordFields;
}

VOID DWordField::InitWordFields()
{
	if (_WordFields != NULL)
		delete[] _WordFields;

	_WordFields = new WordField[this->WordSize()];

	for (SIZE i = 0; i < this->WordSize(); i++)
		_WordFields[i] = WordField((PBYTEFIELD)(this->Bytes() + i));
}

DWordField::operator DWORD() const
{
	return (DWORD)this->operator LONG();
}
		
DWordField::operator LONG() const
{
	return (((LONG)(SHORT)this->Word(1)) << 16) OR (SHORT)this->Word(0);
}

WORD DWordField::Word(SIZE i) const
{
	return (WORD)this->Word(i);
}

RWORDFIELD DWordField::Word(SIZE i)
{
	if (i > this->ByteSize() / 2)
		return UNCONST(WordField::NULL_OBJECT());

	return _WordFields[i];
	//return WordField(&_ByteFields[i * 2]);
}
		
RWORDFIELD DWordField::LowWord()
{
	return this->Word(0);
}

RWORDFIELD DWordField::HighWord()
{
	return this->Word(1);
}
