/***********************************************************************************************
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
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


#pragma region Value DECLARATION: UNIVERSAL 4-BYTE DATA TYPE UNION
	
	UNION PACKED Value
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

		Value();

		Value(RCVALUE other);
		Value(RRVALUE other);

		EXPLICIT Value(PBYTE value);
		EXPLICIT Value(PCHAR value);		
		EXPLICIT Value(PBITPACK value);

		EXPLICIT Value(RCHAR value);
		EXPLICIT Value(RBYTE value);
		EXPLICIT Value(RBOOL value);
		EXPLICIT Value(RSHORT value);
		EXPLICIT Value(RWORD value);
		EXPLICIT Value(RLONG value);
		EXPLICIT Value(RDWORD value);
		EXPLICIT Value(RFLOAT value);


		//OPERATORS

		RVALUE operator =(RCVALUE other);
		RVALUE operator =(RRVALUE other);

		RVALUE operator =(PBYTE other);
		RVALUE operator =(PCHAR other);
		RVALUE operator =(PBITPACK other);

		RVALUE operator =(RCCHAR other);
		RVALUE operator =(RCBYTE other);
		RVALUE operator =(RCBOOL other);
		RVALUE operator =(RCSHORT other);
		RVALUE operator =(RCWORD other);
		RVALUE operator =(RCLONG other);
		RVALUE operator =(RCDWORD other);
		RVALUE operator =(RCFLOAT other);
		
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


#pragma region Datum DECLARATION: UNIVERSAL 4-BYTE DATA TYPE UNION
	
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

		Datum(RCDATUM other);
		Datum(RRDATUM other);

		EXPLICIT Datum(PBYTE value);
		EXPLICIT Datum(PCHAR value);		
		EXPLICIT Datum(PBITPACK value);

		EXPLICIT Datum(RCHAR value);
		EXPLICIT Datum(RBYTE value);
		EXPLICIT Datum(RBOOL value);
		EXPLICIT Datum(RSHORT value);
		EXPLICIT Datum(RWORD value);
		EXPLICIT Datum(RLONG value);
		EXPLICIT Datum(RDWORD value);
		EXPLICIT Datum(RFLOAT value);


		//OPERATORS

		RDATUM operator =(RCDATUM other);
		RDATUM operator =(RRDATUM other);

		RDATUM operator =(PBYTE other);
		RDATUM operator =(PCHAR other);
		RDATUM operator =(PBITPACK other);

		RDATUM operator =(RCCHAR other);
		RDATUM operator =(RCBYTE other);
		RDATUM operator =(RCBOOL other);
		RDATUM operator =(RCSHORT other);
		RDATUM operator =(RCWORD other);
		RDATUM operator =(RCLONG other);
		RDATUM operator =(RCDWORD other);
		RDATUM operator =(RCFLOAT other);
		
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
