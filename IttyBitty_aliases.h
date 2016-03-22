#ifndef _ITTYBITTY_ALIASES_H
#define _ITTYBITTY_ALIASES_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define CONST const
#define VOLATILE volatile
#define PACKED __attribute__ ((packed))

#define ENUM enum
#define STRUCT struct
#define UNION union

typedef bool BIT, BOOL, * PBOOL, & RBOOL;
typedef const bool CBOOL, * PCBOOL, & RCBOOL;

typedef void VOID, * PVOID;
typedef const void * PCVOID;

typedef char INT8, I8, CHAR, * PCHAR, & RCHAR;
typedef const char CCHAR, * PCCHAR, & RCCHAR;

typedef unsigned char UINT8, U8, BYTE, * PBYTE, & RBYTE;
typedef const unsigned char CBYTE, * PCBYTE, & RCBYTE;

typedef short INT16, I16, SHORT, * PSHORT, & RSHORT;
typedef const short CSHORT, * PCSHORT, & RCSHORT;

typedef unsigned short UINT16, U16, WORD, * PWORD, & RWORD;
typedef const unsigned short CWORD, * PCWORD, & RCWORD;

typedef wchar_t WCHAR, * PWCHAR, & RWCHAR;
typedef const wchar_t CWCHAR, * PCWCHAR, & RCWCHAR;

typedef long INT32, I32, LONG, * PLONG, & RLONG;
typedef const long CLONG, * PCLONG, & RCLONG;

typedef unsigned long UINT32, U32, DWORD, * PDWORD, & RDWORD;
typedef const unsigned long CDWORD, * PCDWORD, & RCDWORD;

typedef long long INT64, I64, LONGLONG, * PLONGLONG, & RLONGLONG;
typedef const long long CLONGLONG, * PCLONGLONG, & RCLONGLONG;

typedef unsigned long long UINT64, U64, QWORD, * PQWORD, & RQWORD;
typedef const unsigned long long CQWORD, * PCQWORD, & RCQWORD;

typedef double DOUBLE, * PDOUBLE, & RDOUBLE;
typedef const double CDOUBLE, * PCDOUBLE, & RCDOUBLE;

typedef float FLOAT, * PFLOAT, & RFLOAT;
typedef const float CFLOAT, * PCFLOAT, & RCFLOAT;

typedef int INT;
typedef size_t SIZE;
typedef ptrdiff_t PTRDIFF;

#endif
