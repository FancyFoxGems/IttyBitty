/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#include "IttyBitty_bytes.h"

using namespace IttyBitty;


/* [BITPROXY/BITREF]: PROXY CLASS TO ALLOW FOR INDIVIDUAL BIT-ADDRESSED MEMORY WRITES */

_BitProxy::_BitProxy(PIBYTEFIELD pParent, SIZE i) : _Parent(pParent), _BitMask(BIT_MASK(i)) { }

_BitProxy::_BitProxy(RCBITREF other) : _Parent(other.Parent()), _BitMask(other.BitMask()) { }

_BitProxy::~_BitProxy() { }

RCBITREF _BitProxy::NULL_OBJECT()
{
	static CBITREF NULL_BITREF(NULL, 0);
	return NULL_BITREF;
}

_BitProxy::operator BIT() const
{
	return _Parent->Mask(_BitMask) != 0;
}

RBITREF _BitProxy::operator=(RCBITREF crRValue)
{
	*this = (BIT)crRValue;
	return *this;
}

RBITREF _BitProxy::operator=(BIT bit)
{
	_Parent->SetValue(_Parent->Mask(NOT _BitMask) | (bit ? _BitMask : (BYTE)0));
	return *this;
}

BIT _BitProxy::Flip()
{
	return this->operator=(NOT (BIT)this);
}

PIBYTEFIELD _BitProxy::Parent() const
{
	return _Parent;
}

BYTE _BitProxy::BitMask() const
{
	return _BitMask;
}


/* [BYTEIELD] DEFINITION */

ByteField::ByteField()
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField((BYTE)0);
	new (this) ByteField((BYTE)0);
}

ByteField::ByteField(RCBYTE byteVal) : _pByte(new BYTE(byteVal)), _DisposeByte(true) { }

ByteField::ByteField(RBYTE byteRef) : _pByte(&byteRef), _DisposeByte(false) { }

ByteField::ByteField(PBYTE pByte) : _pByte(pByte), _DisposeByte(false) { }

ByteField::ByteField(RCBYTEFIELD other)
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField(other.ByteRef());
	new (this) ByteField((RBYTE)other);
}
	
ByteField::~ByteField()
{
	if (_DisposeByte)
		delete _pByte;
}

RCBYTEFIELD ByteField::NULL_OBJECT()
{
	static CBYTEFIELD NULL_BYTEFIELD((BYTE)0);
	return NULL_BYTEFIELD;
}

CSIZE ByteField::Size() const
{
	return sizeof(ByteField);

}

SIZE ByteField::BitWidth() const
{
	return this->ByteSize() * BitPack::BitSize();
}

SIZE ByteField::ByteSize() const
{
	return 1;
}

SIZE ByteField::WordSize() const
{
	return 0;
}

ByteField::operator CBYTE() const
{
	return MAKE_CONST(*_pByte);
}

ByteField::operator CCHAR() const
{
	return (CCHAR)this->operator CBYTE();
}

ByteField::operator PCBYTE() const
{
	return MAKE_CONST(_pByte);
}

ByteField::operator PPBYTE()
{
	return &_pByte;
}
		
ByteField::operator PCCHAR() const
{
	return (PCCHAR)this->operator PCBYTE();
}

ByteField::operator PPCHAR()
{
	return (PPCHAR)this->operator PPBYTE();
}
		
ByteField::operator PCIBYTEFIELD() const
{
	return this;
}

ByteField::operator PPIBYTEFIELD()
{
	static PIBYTEFIELD thisClone = this;
	return &thisClone;
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
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();

	return BitRef(this, i);
}

BIT ByteField::Flip(SIZE i)
{
	return this->Bit(i).Flip();
}

PPCIBYTEFIELD ByteField::Bytes() const
{
	static PCIBYTEFIELD thisClone = this;
	return &thisClone;
}

BYTE ByteField::Byte(SIZE i) const
{
	if (i >= this->ByteSize())
		return ByteField::NULL_OBJECT();

	return *_pByte;
}

RIBYTEFIELD ByteField::Byte(SIZE i)
{
	return *this;
}

BYTE ByteField::Value() const
{
	return *_pByte;
}

VOID ByteField::SetValue(BYTE value)
{
	*_pByte = value;
}

VOID ByteField::CopyFrom(RCIBITFIELD<BYTE> other)
{
	*_pByte = other.Value();
}

PBYTE ByteField::Pointer() const
{
	return _pByte;
}

VOID ByteField::PointTo(PBYTE pByte)
{
	_pByte = pByte;
}

VOID ByteField::ReferenceFrom(RCIBITFIELD<BYTE> other)
{
	_pByte = other.Pointer();
}

BYTE ByteField::Mask(BYTE byteMask) const
{
	return MASK(this->Value(), byteMask);
}

BYTE ByteField::Mask(RCIBITFIELD<BYTE> other) const
{
	return MASK(this->Value(), other.Value());
}

ByteField::operator PBYTE()
{
	return _pByte;
}

ByteField::operator RBYTE()
{
	return *_pByte;
}

ByteField::operator PCHAR()
{
	return (PCHAR)_pByte;
}

ByteField::operator RCHAR()
{
	return (RCHAR)*_pByte;
}

ByteField::operator PCBITPACK() const
{
	return MAKE_CONST(_pBitPack);
}

ByteField::operator PBITPACK()
{
	return _pBitPack;
}

PIBYTEFIELD ByteField::CloneByValue() const
{
	return new ByteField(this->Value());
}

PIBYTEFIELD ByteField::CloneByReference() const
{
	return new ByteField(_pByte);
}

BYTE ByteField::LowNybble() const
{
	return LOW_NYBBLE(this->Value());
}

PIBYTEFIELD ByteField::SetLowNybble(BYTE nybbleVal)
{
	*_pByte = (this->HighNybble() << 4) | LOW_NYBBLE(nybbleVal);
	return this;
}

BYTE ByteField::HighNybble() const
{
	return HIGH_NYBBLE(this->Value());
}

PIBYTEFIELD ByteField::SetHighNybble(BYTE nybbleVal)
{
	*_pByte = HIGH_NYBBLE(nybbleVal) | this->LowNybble();
	return this;
}


/* [BITFIELD] DEFINITION */

template<typename T>
BitField<T>::BitField() : _DisposalLevel(DisposalLevel::ByteFieldsData)
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = (PBYTEFIELD)NULL;
}

template<typename T>
BitField<T>::BitField(PVOID memAddr, SIZE byteWidth) : _DisposalLevel(DisposalLevel::ByteFieldsData)
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

template<typename T>
BitField<T>::BitField(BYTE byteVals[T_SIZE]) : _DisposalLevel(DisposalLevel::ByteFieldsData)
{
	_ByteFieldPtrs = new ByteField[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = new ByteField((BYTE)byteVals[i]);
}

template<typename T>
BitField<T>::BitField(PBYTE bytePtrs[T_SIZE]) : _DisposalLevel(DisposalLevel::ByteFieldsData)
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = new ByteField(bytePtrs[i]);
}

template<typename T>
BitField<T>::BitField(BYTEFIELD byteFields[T_SIZE]) : _DisposalLevel(DisposalLevel::ByteFieldsPtr)
{
	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];
	
	for (SIZE i = 0; i < T_SIZE; i++)
		_ByteFieldPtrs[i] = &byteFields[i];
}

template<typename T>
BitField<T>::BitField(PBYTEFIELD byteFieldPtrs[T_SIZE]) : _DisposalLevel(DisposalLevel::None)
{
	_ByteFieldPtrs = byteFieldPtrs;
}

template<typename T>
BitField<T>::BitField(RCBITFIELD<T> other)
{
	this->~ByteField();

	// TODO: Use placement new or explicit reference assignment?
	//*this = ByteField((PVOID)other.Bytes(), other.ByteSize());
	new (this) ByteField((PVOID)other.Bytes(), other.ByteSize());
}

template<typename T>
BitField<T>::~BitField()
{
	switch (_DisposalLevel)
	{
	case DisposalLevel::ByteFieldsData:

		for (SIZE i = 0; i < T_SIZE; i++)
			delete _ByteFieldPtrs[i];

	case DisposalLevel::ByteFieldsPtrs:

		delete[] _ByteFieldPtrs;
		break;
		
	case DisposalLevel::ByteFieldsPtr:

		delete _ByteFieldPtrs;
		break;

	case DisposalLevel::None:

		break;
	}
}

template<typename T>
RCBITFIELD<T> BitField<T>::NULL_OBJECT()
{
	static CBITFIELD<T> NULL_BITFIELD((BYTE)0);
	return NULL_BITFIELD;
}

template<typename T>
CSIZE BitField<T>::Size() const
{
	return sizeof(TYPEOF(*this));
}

template<typename T>
SIZE BitField<T>::BitWidth() const
{
	return this->ByteSize() * BitPack::BitSize();
}

template<typename T>
SIZE BitField<T>::ByteSize() const
{
	return T_SIZE;
}

template<typename T>
SIZE BitField<T>::WordSize() const
{
	return T_SIZE / 2;
}

template<typename T>
BitField<T>::operator CONST T() const
{
	return this->Value();
}

template<typename T>
BitField<T>::operator MAKE_SIGNED(CONST T)() const
{
	return (MAKE_SIGNED(T))this->Value();
}

template<typename T>
BitField<T>::operator PCBYTE() const
{
	BYTE bytes[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i ++)
		bytes[i] = _ByteFieldPtrs[i]->Value();

	return MAKE_CONST(bytes);
}

template<typename T>
BitField<T>::operator PPBYTE()
{
	PBYTE bytePtrs[T_SIZE];

	for (SIZE i = 0; i < T_SIZE; i ++)
		bytePtrs[i] = _ByteFieldPtrs[i]->Pointer();

	return bytePtrs;
}

template<typename T>
BitField<T>::operator PCCHAR() const
{
	return (PCCHAR)this->operator PCBYTE();
}

template<typename T>
BitField<T>::operator PPCHAR()
{
	return (PPCHAR)this->operator PPBYTE();
}

template<typename T>
BitField<T>::operator PCIBYTEFIELD() const
{
	return MAKE_CONST(*_ByteFieldPtrs);
}

template<typename T>
BitField<T>::operator PPIBYTEFIELD()
{
	return _ByteFieldPtrs;
}

template<typename T>
BIT BitField<T>::operator[](SIZE i) const
{
	return this->Bit(i);
}

template<typename T>
BITREF BitField<T>::operator[](SIZE i)
{
	return this->Bit(i);
}

template<typename T>
BIT BitField<T>::Bit(SIZE i) const
{
	return (BIT)this->Bit(i);
}

template<typename T>
BITREF BitField<T>::Bit(SIZE i)
{
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();
	
	BYTE byteIdx = i / T_SIZE;
	BYTE bitIdx = i % T_SIZE;

	return this->Byte(byteIdx).Bit(bitIdx);
}

template<typename T>
BIT BitField<T>::Flip(SIZE i)
{
	if (i >= this->BitWidth())
		return BitRef::NULL_OBJECT();
	
	return this->Bit(i).Flip();
}

template<typename T>
PPCIBYTEFIELD BitField<T>::Bytes() const
{
	return MAKE_CONST(_ByteFieldPtrs);
}

template<typename T>
BYTE BitField<T>::Byte(SIZE i) const
{
	return _ByteFieldPtrs[i]->Value();
}

template<typename T>
RIBYTEFIELD BitField<T>::Byte(SIZE i)
{
	if (i >= this->ByteSize())
		return NULL;
	
	return *_ByteFieldPtrs[i];
}

template<typename T>
T BitField<T>::Value() const
{
	T tVal = 0;

	for (SIZE i = 0; i < T_SIZE; i++)
		tVal += _ByteFieldPtrs[i]->Value() * (256 << i);

	return tVal;
}

template<typename T>
VOID BitField<T>::SetValue(T tVal)
{
	this->~ByteField();

	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < this->ByteSize(); i ++)
		_ByteFieldPtrs[i] = new ByteField(*((PBYTE)&tVal + i));

	_DisposalLevel = DisposalLevel::ByteFieldsData;
}

template<typename T>
VOID BitField<T>::CopyFrom(RCIBITFIELD<T> other)
{	
	this->SetValue(other.Value());
}

template<typename T>
T * BitField<T>::Pointer() const
{
	return _ByteFieldPtrs[0]->Pointer();
}

template<typename T>
VOID BitField<T>::PointTo(T * tPtr)
{
	this->~ByteField();

	_ByteFieldPtrs = new PBYTEFIELD[T_SIZE];

	for (SIZE i = 0; i < this->ByteSize(); i ++)
		_ByteFieldPtrs[i] = new ByteField((PBYTE)tPtr + i);

	_DisposalLevel = DisposalLevel::ByteFieldsData;
}

template<typename T>
VOID BitField<T>::ReferenceFrom(RCIBITFIELD<T> other)
{
	this->~ByteField();
	
	_ByteFieldPtrs = other.Bytes();
	_DisposalLevel = DisposalLevel::None;
}

template<typename T>
T BitField<T>::Mask(T tMask) const
{
	return MASK(this->Value(), tMask);
}

template<typename T>
T BitField<T>::Mask(RCIBITFIELD<T> other) const
{
	return MASK(this->Value(), other.Value());
}

template<typename T>
PIBITFIELD<T> BitField<T>::CloneByValue() const
{
	return new PIBITFIELD<T>(this->Value());
}

template<typename T>
PIBITFIELD<T> BitField<T>::CloneByReference() const
{
	return new PIBITFIELD<T>((PBYTEFIELD[T_SIZE])_ByteFieldPtrs);
}


/* [WORDFIELD] DEFINITION */

//WordField::WordField() : ByteField(2) { }
//
//WordField::WordField(WORD wordVal) : ByteField((PBYTE)&wordVal, 2) { }
//
//WordField::WordField(PWORD pWord) : ByteField((PPBYTE)pWord, 2) { }
//
//WordField::WordField(PBYTEFIELD byteFields) : ByteField(byteFields, 2) { }
//		
//WordField::WordField(RCWORDFIELD other) : ByteField(other) { }
//
//RCWORDFIELD WordField::NULL_OBJECT()
//{
//	static CWORDFIELD NULL_WORDFIELD((WORD)0);
//	return NULL_WORDFIELD;
//}
//
//WordField::operator WORD() const
//{
//	return (WORD)this->operator SHORT();
//}
//		
//WordField::operator SHORT() const
//{
//	return (((SHORT)(BYTE)this->Byte(1)) << 8) OR (BYTE)this->Byte(0);
//}
//		
//PBYTEFIELD WordField::LowByte()
//{
//	return this->Byte(0);
//}
//
//PBYTEFIELD WordField::HighByte()
//{
//	return this->Byte(1);
//}


/* [DWORDFIELD] DEFINITION */

//DWordField::DWordField() : ByteField(4)
//{
//	this->InitWordFields();
//}
//
//DWordField::DWordField(DWORD dwordVal) : ByteField((PBYTE)&dwordVal, 4)
//{
//	this->InitWordFields();
//}
//
//DWordField::DWordField(PDWORD pDWord) : ByteField((PPBYTE)pDWord, 4)
//{
//	this->InitWordFields();
//}
//
//DWordField::DWordField(PBYTEFIELD byteFields) : ByteField(byteFields, 4)
//{
//	this->InitWordFields();
//}
//
//DWordField::DWordField(PWORDFIELD wordFields)
//{
//	PBYTEFIELD byteFieldPtrs[4];
//
//	for (SIZE i = 0; i < 2; i ++)
//	{
//		byteFieldPtrs[i * 2] = ((PWORDFIELD)(wordFields + i))->LowByte();
//		byteFieldPtrs[i * 2 + 1] = ((PWORDFIELD)(wordFields + i))->HighByte();
//	}
//	
//	this->~DWordField();
//
//	// TODO: Use placement new or explicit reference assignment?
//	//*this = ByteField(byteFieldPtrs, 4);
//	new (this) ByteField(byteFieldPtrs, 4);
//	
//	this->InitWordFields();
//}
//		
//DWordField::DWordField(RCDWORDFIELD other) : ByteField(other) { }
//
//DWordField::~DWordField()
//{
//	delete[] _WordFields;
//}
//
//VOID DWordField::InitWordFields()
//{
//	if (_WordFields != NULL)
//		delete[] _WordFields;
//	
//	_WordFields = new WordField[this->WordSize()];
//
//	for (SIZE i = 0; i < this->WordSize(); i++)
//		_WordFields[i] = WordField((PBYTEFIELD)(this->Bytes() + i));
//}
//
//DWordField::operator DWORD() const
//{
//	return (DWORD)this->operator LONG();
//}
//		
//DWordField::operator LONG() const
//{
//	return (((LONG)(SHORT)this->Word(1)) << 16) OR (SHORT)this->Word(0);
//}
//
//WORD DWordField::Word(SIZE i) const
//{
//	return (WORD)this->Word(i);
//}
//
//RWORDFIELD DWordField::Word(SIZE i)
//{
//	if (i > this->ByteSize() / 2)
//		return UNCONST(WordField::NULL_OBJECT());
//
//	return _WordFields[i];
//	//return WordField(&_ByteFieldPtrs[i * 2]);
//}
//		
//RWORDFIELD DWordField::LowWord()
//{
//	return this->Word(0);
//}
//
//RWORDFIELD DWordField::HighWord()
//{
//	return this->Word(1);
//}
