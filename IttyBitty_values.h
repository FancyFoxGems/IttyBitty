/***********************************************************************************************
* [IttyBitty_values.h]: UNIVERSAL TYPE (TAGGED) UNIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_VALUES_H
#define _ITTYBITTY_VALUES_H


#include "IttyBitty_bits.h"


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	typedef union Value VALUE, * PVALUE, & RVALUE, ** PPVALUE, && RRVALUE;
	typedef const union Value CVALUE, * PCVALUE, & RCVALUE, ** PPCVALUE;

	typedef union Datum DATUM, * PDATUM, & RDATUM, ** PPDATUM, && RRDATUM;
	typedef const union Datum CDATUM, * PCDATUM, & RCDATUM, ** PPCDATUM;

#pragma endregion


#pragma region [Value] DEFINITION: IMMUTABLE, VALUE-BASED UNIVERSAL 4-BYTE DATA TYPE UNION
	
	UNION PACKED Value
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

		Value();

		Value(RCVALUE);
		Value(RRVALUE);

		EXPLICIT Value(PCBYTE);
		EXPLICIT Value(PCCHAR);		
		EXPLICIT Value(PCBITPACK);

		EXPLICIT Value(RCCHAR);
		EXPLICIT Value(RCBYTE);
		EXPLICIT Value(RCBOOL);
		EXPLICIT Value(RCSHORT);
		EXPLICIT Value(RCWORD);
		EXPLICIT Value(RCLONG);
		EXPLICIT Value(RCDWORD);
		EXPLICIT Value(RCFLOAT);


		//OPERATORS

		RVALUE operator =(RCVALUE);
		RVALUE operator =(RRVALUE);

		RVALUE operator =(PCBYTE);
		RVALUE operator =(PCCHAR);
		RVALUE operator =(PCBITPACK);

		RVALUE operator =(RCCHAR);
		RVALUE operator =(RCBYTE);
		RVALUE operator =(RCBOOL);
		RVALUE operator =(RCSHORT);
		RVALUE operator =(RCWORD);
		RVALUE operator =(RCLONG);
		RVALUE operator =(RCDWORD);
		RVALUE operator =(RCFLOAT);
		
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

		VOID FreePtr();
		VOID FreeData();
	};

#pragma endregion


#pragma region [Datum] DEFINITION: MUTABLE, REFERENCE-BASED UNIVERSAL 4-BYTE DATA TYPE UNION
	
	UNION PACKED Datum
	{
		// UNION MEMBERS

		PBYTE Bytes;
		PCHAR String;	
		PBITPACK BitFields;
		
		PCHAR CharPtr;
		PBYTE BytePtr;
		PBOOL BoolPtr;
		
		PSHORT ShortPtr;
		PWORD WordPtr;
		
		PLONG LongPtr;
		PDWORD DWordPtr;
		PFLOAT FloatPtr;


		// CONSTRUCTORS

		Datum();

		Datum(RCDATUM);
		Datum(RRDATUM);

		EXPLICIT Datum(PBYTE);
		EXPLICIT Datum(PCHAR);		
		EXPLICIT Datum(PBITPACK);

		EXPLICIT Datum(RCHAR);
		EXPLICIT Datum(RBYTE);
		EXPLICIT Datum(RBOOL);
		EXPLICIT Datum(RSHORT);
		EXPLICIT Datum(RWORD);
		EXPLICIT Datum(RLONG);
		EXPLICIT Datum(RDWORD);
		EXPLICIT Datum(RFLOAT);


		//OPERATORS

		RDATUM operator =(RCDATUM);
		RDATUM operator =(RRDATUM);

		RDATUM operator =(PBYTE);
		RDATUM operator =(PCHAR);
		RDATUM operator =(PBITPACK);

		RDATUM operator =(RCHAR);
		RDATUM operator =(RBYTE);
		RDATUM operator =(RBOOL);
		RDATUM operator =(RSHORT);
		RDATUM operator =(RWORD);
		RDATUM operator =(RLONG);
		RDATUM operator =(RDWORD);
		RDATUM operator =(RFLOAT);
		
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

		VOID FreePtr();
		VOID FreeData();
	};

#pragma endregion
}


#endif
