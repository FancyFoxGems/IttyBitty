/************************************************************
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED. *
*************************************************************/

#ifndef _ITTYBITTY_ALIASES_H
#define _ITTYBITTY_ALIASES_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


/* C/C++ KEYWORD ALIASES */

#define STATIC static
#define VOLATILE volatile
#define CONST const
#define ENUM enum
#define STRUCT struct
#define UNION union
#define CLASS class


/* ATTRIBUTES & META FUNCTION ALIASES */

#define PACKED __attribute__ ((packed))
#define PACKED_STRUCT STRUCT PACKED
#define TYPEOF(var) __typeof__(var)


/* NATIVE DATA TYPE ALIASES */

typedef bool BIT, * PBIT, & RBIT, BOOL, * PBOOL, & RBOOL;
typedef const bool CBIT, * PCBIT, & RCBIT, CBOOL, * PCBOOL, & RCBOOL;
typedef volatile bool VBIT, * PVBIT, & RVBIT, VBOOL, * PVBOOL, & RVBOOL;

typedef void VOID, * PVOID;
typedef const void * PCVOID;

typedef char INT8, I8, CHAR, * PCHAR, & RCHAR;
typedef const char CCHAR, * PCCHAR, & RCCHAR;
typedef volatile char V8, VCHAR, * PVCHAR, & RVCHAR;

typedef unsigned char UINT8, U8, BYTE, * PBYTE, & RBYTE;
typedef const unsigned char CBYTE, * PCBYTE, & RCBYTE;
typedef volatile unsigned char VU8, VBYTE, * PVBYTE, & RVBYTE;

typedef short INT16, I16, SHORT, * PSHORT, & RSHORT;
typedef const short CSHORT, * PCSHORT, & RCSHORT;
typedef volatile short V16, VSHORT, * PVSHORT, & RVSHORT;

typedef unsigned short UINT16, U16, WORD, * PWORD, & RWORD;
typedef const unsigned short CWORD, * PCWORD, & RCWORD;
typedef volatile unsigned short VU16, VWORD, * PVWORD, & RVWORD;

typedef wchar_t WCHAR, * PWCHAR, & RWCHAR;
typedef const wchar_t CWCHAR, * PCWCHAR, & RCWCHAR;
typedef volatile wchar_t VWCHAR, * PVWCHAR, & RVWCHAR;

typedef long INT32, I32, LONG, * PLONG, & RLONG;
typedef const long CLONG, * PCLONG, & RCLONG;
typedef volatile long V32, VLONG, * PVLONG, & RVLONG;

typedef unsigned long UINT32, U32, DWORD, * PDWORD, & RDWORD;
typedef const unsigned long CDWORD, * PCDWORD, & RCDWORD;
typedef volatile unsigned long VU32, VDWORD, * PVDWORD, & RVDWORD;

typedef long long INT64, I64, LONGLONG, * PLONGLONG, & RLONGLONG;
typedef const long long CLONGLONG, * PCLONGLONG, & RCLONGLONG;
typedef volatile long long V64, VLONGLONG, * PVLONGLONG, & RVLONGLONG;

typedef unsigned long long UINT64, U64, QWORD, * PQWORD, & RQWORD;
typedef const unsigned long long CQWORD, * PCQWORD, & RCQWORD;
typedef volatile unsigned long long VU64, VQWORD, * PVQWORD, & RVQWORD;

typedef float FLOAT, * PFLOAT, & RFLOAT;
typedef const float CFLOAT, * PCFLOAT, & RCFLOAT;
typedef volatile float VFLOAT, * PVFLOAT, & RVFLOAT;

typedef double DOUBLE, * PDOUBLE, & RDOUBLE;
typedef const double CDOUBLE, * PCDOUBLE, & RCDOUBLE;
typedef volatile double VDOUBLE, * PVDOUBLE, & RVDOUBLE;

typedef int INT, * PINT, & RINT;
typedef const int CINT, * PCINT, & RCINT;
typedef volatile int VINT, * PVINT, & RVINT;

typedef size_t SIZE, * PSIZE, & RSIZE;
typedef const size_t CSIZE, * PCSIZE, & RCSIZE;

typedef ptrdiff_t PTRDIFF, * PPTRDIFF, & RPTRDIFF;


#endif
