/*******************************************************************************
* [IttyBitty_aliases.h]: TYPEDEFS FOR WIN32 API-STYLE TYPE REFERENCES
*
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*******************************************************************************/

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
#define ENUM enum class
#define STRUCT struct
#define UNION union
#define CLASS class
#define INTERFACE class


/* NATIVE DATA TYPE ALIASES FOR WIN32 API-STYLE TYPE REFERENCES  */

typedef bool BIT, * PBIT, & RBIT, ** PPBIT, BOOL, * PBOOL, & RBOOL, ** PPBOOL;
typedef const bool CBIT, * PCBIT, & RCBIT, ** PPCBIT, CBOOL, * PCBOOL, & RCBOOL, ** PPCBOOL;
typedef volatile bool VBIT, * PVBIT, & RVBIT, ** PPVBIT, VBOOL, * PVBOOL, & RVBOOL, ** PPVBOOL;

typedef void VOID, * PVOID, ** PPVOID;
typedef const void * PCVOID, ** PPCVOID;

typedef char INT8, I8, CHAR, * PCHAR, & RCHAR, ** PPCHAR;
typedef const char CCHAR, * PCCHAR, & RCCHAR, ** PPCCHAR;
typedef volatile char V8, VCHAR, * PVCHAR, & RVCHAR, ** PPVCHAR;

typedef unsigned char UINT8, U8, BYTE, * PBYTE, & RBYTE, ** PPBYTE;
typedef const unsigned char CBYTE, * PCBYTE, & RCBYTE, ** PPCBYTE;
typedef volatile unsigned char VU8, VBYTE, * PVBYTE, & RVBYTE, ** PPVBYTE;

typedef short INT16, I16, SHORT, * PSHORT, & RSHORT, ** PPSHORT;
typedef const short CSHORT, * PCSHORT, & RCSHORT, ** PPCSHORT;
typedef volatile short V16, VSHORT, * PVSHORT, & RVSHORT, ** PPVSHORT;

typedef unsigned short UINT16, U16, WORD, * PWORD, & RWORD, ** PPWORD;
typedef const unsigned short CWORD, * PCWORD, & RCWORD, ** PPCWORD;
typedef volatile unsigned short VU16, VWORD, * PVWORD, & RVWORD, ** PPVWORD;

typedef wchar_t WCHAR, * PWCHAR, & RWCHAR, ** PPWCHAR;
typedef const wchar_t CWCHAR, * PCWCHAR, & RCWCHAR, ** PPCWCHAR;
typedef volatile wchar_t VWCHAR, * PVWCHAR, & RVWCHAR, ** PPVWCHAR;

typedef long INT32, I32, LONG, * PLONG, & RLONG, ** PPLONG;
typedef const long CLONG, * PCLONG, & RCLONG, ** PPCLONG;
typedef volatile long V32, VLONG, * PVLONG, & RVLONG, ** PPVLONG;

typedef unsigned long UINT32, U32, DWORD, * PDWORD, & RDWORD, ** PPDWORD;
typedef const unsigned long CDWORD, * PCDWORD, & RCDWORD, ** PPCDWORD;
typedef volatile unsigned long VU32, VDWORD, * PVDWORD, & RVDWORD, ** PPVDWORD;

typedef long long INT64, I64, LONGLONG, * PLONGLONG, & RLONGLONG, ** PPLONGLONG;
typedef const long long CLONGLONG, * PCLONGLONG, & RCLONGLONG, ** PPCLONGLONG;
typedef volatile long long V64, VLONGLONG, * PVLONGLONG, & RVLONGLONG, ** PPVLONGLONG;

typedef unsigned long long UINT64, U64, QWORD, * PQWORD, & RQWORD, ** PPQWORD;
typedef const unsigned long long CQWORD, * PCQWORD, & RCQWORD, ** PPCQWORD;
typedef volatile unsigned long long VU64, VQWORD, * PVQWORD, & RVQWORD, ** PPVQWORD;

typedef float FLOAT, * PFLOAT, & RFLOAT, ** PPFLOAT;
typedef const float CFLOAT, * PCFLOAT, & RCFLOAT, ** PPCFLOAT;
typedef volatile float VFLOAT, * PVFLOAT, & RVFLOAT, ** PPVFLOAT;

typedef double DOUBLE, * PDOUBLE, & RDOUBLE, ** PPDOUBLE;
typedef const double CDOUBLE, * PCDOUBLE, & RCDOUBLE, ** PPCDOUBLE;
typedef volatile double VDOUBLE, * PVDOUBLE, & RVDOUBLE, ** PPVDOUBLE;

typedef int INT, * PINT, & RINT, ** PPINT;
typedef const int CINT, * PCINT, & RCINT, ** PPCINT;
typedef volatile int VINT, * PVINT, & RVINT, ** PPVINT;

typedef size_t SIZE, * PSIZE, & RSIZE, ** PPSIZE;
typedef const size_t CSIZE, * PCSIZE, & RCSIZE, ** PPCSIZE;

typedef ptrdiff_t PTRDIFF, * PPTRDIFF, & RPTRDIFF, ** PPPTRDIFF;

/* DATA TYPE MACROS FOR SIGNAGE */

#define SIGNED(type) SIGNED_##type()
#define SIGNED_BYTE() CHAR
#define SIGNED_WORD() SHORT
#define SIGNED_QWORD() LONGLONG

#define UNSIGNED(type) UNSIGNED_##type()
#define UNSIGNED_CHAR() BYTE
#define UNSIGNED_SHORT() WORD
#define UNSIGNED_LONG() DWORD
#define UNSIGNED_LONGLONG() QWORD


#endif
