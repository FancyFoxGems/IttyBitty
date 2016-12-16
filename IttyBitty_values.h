/***********************************************************************************************
* [IttyBitty_values.h]: UNIVERSAL TYPE (TAGGED) UNIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_CONSTVALUES_H
#define _ITTYBITTY_CONSTVALUES_H


#include "IttyBitty_bits.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	union ConstValue;
	TYPEDEF_UNION_ALIASES(ConstValue, CONSTVALUE);

	union Value;
	TYPEDEF_UNION_ALIASES(Value, VALUE);

#pragma endregion


#pragma region [ConstValue] DEFINITION: IMMUTABLE, VALUE-BASED UNIVERSAL 4-BYTE DATA TYPE UNION

	PACKED_UNION ConstValue
	{
		// UNION MEMBERS

		PCBYTE Bytes;
		PCCHAR String;
		PCBITPACK BitFields;

		CHAR Char;
		BYTE Byte;
		BOOL Bool;

		SHORT Short;
		WORD Word;

		LONG Long;
		DWORD DWord;
		FLOAT Float;


		// CONSTRUCTORS

		ConstValue();

		ConstValue(RCCONSTVALUE);
		ConstValue(RRCONSTVALUE);

		EXPLICIT ConstValue(PCBYTE);
		EXPLICIT ConstValue(PCCHAR);
		EXPLICIT ConstValue(PCBITPACK);

		EXPLICIT ConstValue(RCCHAR);
		EXPLICIT ConstValue(RCBYTE);
		EXPLICIT ConstValue(RCBOOL);
		EXPLICIT ConstValue(RCSHORT);
		EXPLICIT ConstValue(RCWORD);
		EXPLICIT ConstValue(RCLONG);
		EXPLICIT ConstValue(RCDWORD);
		EXPLICIT ConstValue(RCFLOAT);


		//OPERATORS

		RCONSTVALUE operator =(RCCONSTVALUE);
		RCONSTVALUE operator =(RRCONSTVALUE);

		RCONSTVALUE operator =(PCBYTE);
		RCONSTVALUE operator =(PCCHAR);
		RCONSTVALUE operator =(PCBITPACK);

		RCONSTVALUE operator =(RCCHAR);
		RCONSTVALUE operator =(RCBYTE);
		RCONSTVALUE operator =(RCBOOL);
		RCONSTVALUE operator =(RCSHORT);
		RCONSTVALUE operator =(RCWORD);
		RCONSTVALUE operator =(RCLONG);
		RCONSTVALUE operator =(RCDWORD);
		RCONSTVALUE operator =(RCFLOAT);

		operator PCBYTE() const;
		operator PCCHAR() const;
		operator PCBITPACK() const;

		operator RCCHAR() const;
		operator RCBYTE() const;
		operator RCBOOL() const;
		operator RCSHORT() const;
		operator RCWORD() const;
		operator RCLONG() const;
		operator RCDWORD() const;
		operator RCFLOAT() const;


		// USER METHODS

		VOID FreeData();
		VOID FreeReference();
	};

#pragma endregion


#pragma region [Value] DEFINITION: MUTABLE, REFERENCE-BASED UNIVERSAL 4-BYTE DATA TYPE UNION

	PACKED_UNION Value
	{
		// UNION MEMBERS

		PPBYTE BytesRef;
		PPCHAR StringRef;
		PPBITPACK BitFieldsRef;

		PCHAR CharRef;
		PBYTE ByteRef;
		PBOOL BoolRef;

		PSHORT ShortRef;
		PWORD WordRef;

		PLONG LongRef;
		PDWORD DWordRef;
		PFLOAT FloatRef;


		// CONSTRUCTORS

		Value();

		Value(RCVALUE);
		Value(RRVALUE);

		EXPLICIT Value(PBYTE);
		EXPLICIT Value(PCHAR);
		EXPLICIT Value(PBITPACK);

		EXPLICIT Value(RCHAR);
		EXPLICIT Value(RBYTE);
		EXPLICIT Value(RBOOL);
		EXPLICIT Value(RSHORT);
		EXPLICIT Value(RWORD);
		EXPLICIT Value(RLONG);
		EXPLICIT Value(RDWORD);
		EXPLICIT Value(RFLOAT);


		//OPERATORS

		RVALUE operator =(RCVALUE);
		RVALUE operator =(RRVALUE);

		RVALUE operator =(PBYTE);
		RVALUE operator =(PCHAR);
		RVALUE operator =(PBITPACK);

		RVALUE operator =(RCCHAR);
		RVALUE operator =(RCBYTE);
		RVALUE operator =(RCBOOL);
		RVALUE operator =(RCSHORT);
		RVALUE operator =(RCWORD);
		RVALUE operator =(RCLONG);
		RVALUE operator =(RCDWORD);
		RVALUE operator =(RCFLOAT);

		operator PCBYTE() const;
		operator PBYTE();
		operator PCCHAR() const;
		operator PCHAR();
		operator PCBITPACK() const;
		operator PBITPACK();

		operator RCCHAR() const;
		operator RCHAR();
		operator RCBYTE() const;
		operator RBYTE();
		operator RCBOOL() const;
		operator RBOOL();
		operator RCSHORT() const;
		operator RSHORT();
		operator RCWORD() const;
		operator RWORD();
		operator RCLONG() const;
		operator RLONG();
		operator RCDWORD() const;
		operator RDWORD();
		operator RCFLOAT() const;
		operator RFLOAT();


		// USER METHODS

		VOID FreeData();
		VOID FreeReference();
	};

#pragma endregion
}


#endif
