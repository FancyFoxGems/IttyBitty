/***********************************************************************************************
* [IttyBitty_aliases.h]: TYPEDEFS FOR WIN32 API-STYLE TYPE REFERENCES
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_ALIASES_H
#define _ITTYBITTY_ALIASES_H


#ifdef ARDUINO
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
#else
	#include <stdlib.h>
	#include <stddef.h>
	#include <inttypes.h>
	#include <string.h>
	#include <avr/pgmspace.h>
	typedef decltype(nullptr) nullptr_t;
#endif

//using namespace std;


/* C++ KEYWORD/SPECIFIER/MODIFIER ALIASES */

#ifndef null
	#define null		0
#endif

#ifndef NULL
	#define NULL		null
#endif

#ifndef nil
	#define nil			null
#endif

#ifndef TRUE
	#define TRUE		true
#endif

#ifndef FALSE
	#define FALSE		false
#endif

#define EXTERN			extern
#define INLINE			inline
#define EXPLICIT		explicit
#define STATIC			static
#define FINAL			final
#define VIRTUAL			virtual

#define CONSTEXPR		constexpr	// NOTE: Only supported by Arduino 1.[?]+..?

#define CONST			const
#define CONSTREF		const &
#define CONSTPTR		const *
#define VOLATILE		volatile
#define CONST_VOLATILE	const volatile
#define CONSTVOL 		const volatile
#define cv				const volatile

#define ENUM			enum class
#define UNION			union
#define STRUCT			struct
#define CLASS			class
#define INTERFACE		class

#define TEMPLATE(T_clause, structure_type) TEMPLATE_##structure_type(T_clause)
#define TEMPLATE_STRUCT(T_clause)		template T_clause STRUCT
#define TEMPLATE_CLASS(T_clause)		template T_clause CLASS
#define TEMPLATE_INTERFACE(T_clause)	template T_clause INTERFACE


/* MACRO EXPANSION MACROS (META-MACROS) */

#define NULL_MACRO(x)
#define EXPAND(x)					x
#define STR(x)						#x
#define EXPAND_STR(x)				STR(x)
#define CONCAT(x, y)				x##y
#define EXPAND_CONCAT(x, y)			CONCAT(x, y)
#define CSL(...)					__VA_ARGS__

#define __VA_MACRO(MACRO, _0, _1, _2, _3, _4, ARGS...) MACRO##_##_4
#define _VA_MACRO(MACRO, ARGS...)	__VA_MACRO(MACRO, ##ARGS, 4, 3, 2, 1, 0)
#define VA_MACRO(MACRO, ARGS...)	_VA_MACRO(MACRO, ##ARGS)(, ##ARGS)


/* TYPEDEF & TEMPLATED USING ALIAS MACROS */

#define TYPEDEF_MODIFIER_ALIASES(modified_type_name, TYPE_ALIAS)		\
	typedef modified_type_name TYPE_ALIAS, * P##TYPE_ALIAS, & R##TYPE_ALIAS
#define TYPEDEF_ALIASES_NOMODIFIER(type_name, TYPE_ALIAS)		TYPEDEF_MODIFIER_ALIASES(type_name, TYPE_ALIAS)

#define TYPEDEF_CONST_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_MODIFIER_ALIASES(const type_name, C##TYPE_ALIAS)
#define TYPEDEF_VOLATILE_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_MODIFIER_ALIASES(volatile type_name, V##TYPE_ALIAS)
#define TYPEDEF_CONST_VOLATILE_ALIASES(type_name, TYPE_ALIAS)	TYPEDEF_MODIFIER_ALIASES(const volatile type_name, CV##TYPE_ALIAS)

#define TYPEDEF_PROGMEM_ALIAS(type_name, TYPE_ALIAS)			typedef type_name PROGMEM type_name##_P

#define TYPEDEF_ALIASES_PP(type_name, TYPE_ALIAS)						\
	typedef type_name ** PP##TYPE_ALIAS, && RR##TYPE_ALIAS;				\
	typedef const type_name ** PPC##TYPE_ALIAS, && RRC##TYPE_ALIAS

#define TYPEDEF_ALIASES(type_name, TYPE_ALIAS)							\
	TYPEDEF_ALIASES_NOMODIFIER(type_name, TYPE_ALIAS);					\
	TYPEDEF_CONST_ALIASES(type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_AS_VOLATILE(type_name, TYPE_ALIAS)				\
	TYPEDEF_MODIFIER_ALIASES(volatile type_name, TYPE_ALIAS);			\
	TYPEDEF_CONST_ALIASES(volatile type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(type_name, TYPE_ALIAS)		\
	TYPEDEF_ALIASES_AS_VOLATILE(type_name, TYPE_ALIAS);					\
	TYPEDEF_ALIASES_PP(volatile type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_WITH_VOLATILE(type_name, TYPE_ALIAS)			\
	TYPEDEF_ALIASES(type_name, TYPE_ALIAS);								\
	TYPEDEF_VOLATILE_ALIASES(type_name, TYPE_ALIAS);					\
	TYPEDEF_CONST_VOLATILE_ALIASES(type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_WITH_PROGMEM(type_name, TYPE_ALIAS)				\
	TYPEDEF_ALIASES(type_name, TYPE_ALIAS);								\
	TYPEDEF_PROGMEM_ALIAS(type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_WITH_PP(type_name, TYPE_ALIAS)					\
	TYPEDEF_ALIASES_NOMODIFIER(type_name, TYPE_ALIAS);					\
	TYPEDEF_CONST_ALIASES(type_name, TYPE_ALIAS);						\
	TYPEDEF_ALIASES_PP(type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_WITH_VOLATILE_AND_PP(type_name, TYPE_ALIAS)		\
	TYPEDEF_ALIASES_WITH_PP(type_name, TYPE_ALIAS);						\
	TYPEDEF_VOLATILE_ALIASES(type_name, TYPE_ALIAS);					\
	TYPEDEF_CONST_VOLATILE_ALIASES(type_name, TYPE_ALIAS);				\
	typedef volatile type_name ** PPV##TYPE_ALIAS, && RRV##TYPE_ALIAS;	\
	typedef const volatile type_name ** PPCV##TYPE_ALIAS, && RRCV##TYPE_ALIAS

#define TYPEDEF_ALIASES_WITH_PP_AND_PROGMEM(type_name, TYPE_ALIAS)		\
	TYPEDEF_ALIASES_WITH_PP(type_name, TYPE_ALIAS);						\
	TYPEDEF_PROGMEM_ALIAS(type_name, TYPE_ALIAS)

#define TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(type_name, TYPE_ALIAS)	\
	TYPEDEF_ALIASES_WITH_VOLATILE_AND_PP(type_name, TYPE_ALIAS);		\
	TYPEDEF_PROGMEM_ALIAS(type_name, TYPE_ALIAS)

#define TYPEDEF_ENUM_ALIASES(type_name, TYPE_ALIAS)				TYPEDEF_ALIASES(enum type_name, TYPE_ALIAS)

#define TYPEDEF_UNION_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_ALIASES_WITH_PP(union type_name, TYPE_ALIAS)
#define TYPEDEF_VOLATILE_UNION_ALIASES(type_name, TYPE_ALIAS)	TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(union type_name, TYPE_ALIAS)

#define TYPEDEF_CLASS_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_ALIASES_WITH_PP(class type_name, TYPE_ALIAS)
#define TYPEDEF_VOLATILE_CLASS_ALIASES(type_name, TYPE_ALIAS)	TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(class type_name, TYPE_ALIAS)

#define TYPEDEF_STRUCT_ALIASES(type_alias, lower_type_alias, UPPER_TYPE_ALIAS)			\
	typedef struct EXPAND_CONCAT(_, type_alias) EXPAND_CONCAT(EXPAND_CONCAT(_, lower_type_alias),_t), type_alias;			\
	TYPEDEF_ALIASES_WITH_PP(struct EXPAND_CONCAT(_, type_alias), UPPER_TYPE_ALIAS)

#define TYPEDEF_VOLATILE_STRUCT_ALIASES(type_alias, lower_type_alias, UPPER_TYPE_ALIAS)	\
	typedef volatile struct EXPAND_CONCAT(_, type_alias) EXPAND_CONCAT(EXPAND_CONCAT(_, lower_type_alias),_t), type_alias;	\
	TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(struct EXPAND_CONCAT(_, type_alias), UPPER_TYPE_ALIAS)

#define TEMPLATE_CLASS_USING_ALIASES(T_clause, T_args, type_name, TYPE_ALIAS)			\
	template T_clause																	\
	using TYPE_ALIAS = type_name T_args;												\
	template T_clause																	\
	using P##TYPE_ALIAS = type_name T_args *;											\
	template T_clause																	\
	using R##TYPE_ALIAS = type_name T_args &;											\
	template T_clause																	\
	using PP##TYPE_ALIAS = type_name T_args **;											\
	template T_clause																	\
	using RR##TYPE_ALIAS = type_name T_args &&;											\
	template T_clause																	\
	using C##TYPE_ALIAS = const type_name T_args;										\
	template T_clause																	\
	using PC##TYPE_ALIAS = const type_name T_args *;									\
	template T_clause																	\
	using RC##TYPE_ALIAS = const type_name T_args &;									\
	template T_clause																	\
	using PPC##TYPE_ALIAS = const type_name T_args **;									\
	template T_clause																	\
	using RRC##TYPE_ALIAS = const type_name T_args &&

#define TEMPLATE_STRUCT_USING_ALIASES(T_clause, T_args, type_alias, lower_type_alias, UPPER_TYPE_ALIAS)			\
	template T_clause																	\
	using EXPAND_CONCAT(EXPAND_CONCAT(_, lower_type_alias),_t) = struct EXPAND_CONCAT(_, type_alias) T_args;	\
	template T_clause																	\
	using type_alias = struct EXPAND_CONCAT(_, type_alias) T_args;						\
	template T_clause																	\
	using UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_args;				\
	template T_clause																	\
	using P##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_args *;			\
	template T_clause																	\
	using R##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_args &;			\
	template T_clause																	\
	using PP##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_args **;			\
	template T_clause																	\
	using RR##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_args &&;			\
	template T_clause																	\
	using C##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_args;		\
	template T_clause																	\
	using PC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_args *;	\
	template T_clause																	\
	using RC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_args &;	\
	template T_clause																	\
	using PPC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_args **;	\
	template T_clause																	\
	using RRC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_args &&




/* (NATIVE) FUNDAMENTAL DATA TYPE ALIASES FOR WIN32 API-STYLE TYPE REFERENCES  */

typedef void VOID, * PTR, * PVOID, ** PPVOID, * PROGMEM PVOID_P;
typedef const void * PCVOID, ** PPCVOID;

typedef bool bit, BIT, * PBIT, & RBIT, ** PPBIT, BOOL, * PBOOL, & RBOOL, ** PPBOOL, PROGMEM BOOL_P;
typedef const bool CBIT, * PCBIT, & RCBIT, ** PPCBIT, CBOOL, * PCBOOL, & RCBOOL, ** PPCBOOL;
typedef volatile bool VBIT, * PVBIT, & RVBIT, ** PPVBIT, VBOOL, * PVBOOL, & RVBOOL, ** PPVBOOL;

typedef char int8, INT8, i8, I8, CHAR, * PCHAR, & RCHAR, ** PPCHAR, PROGMEM CHAR_P;
typedef const char CCHAR, * PCCHAR, & RCCHAR, ** PPCCHAR, * PROGMEM CSTR_P;
typedef volatile char V8, VCHAR, * PVCHAR, & RVCHAR, ** PPVCHAR;

typedef unsigned char uint8, UINT8, u8, U8, BYTE, * PBYTE, & RBYTE, ** PPBYTE, PROGMEM BYTE_P;
typedef const unsigned char CBYTE, * PCBYTE, & RCBYTE, ** PPCBYTE;
typedef volatile unsigned char VU8, VBYTE, * PVBYTE, & RVBYTE, ** PPVBYTE;
typedef const volatile unsigned char CVU8, CVBYTE, * PCVBYTE, & RCVBYTE, ** PPCVBYTE;

typedef short int16, INT16, i16, I16, SHORT, * PSHORT, & RSHORT, ** PPSHORT, PROGMEM SHORT_P;
typedef const short CSHORT, * PCSHORT, & RCSHORT, ** PPCSHORT;
typedef volatile short V16, VSHORT, * PVSHORT, & RVSHORT, ** PPVSHORT;

typedef unsigned short uint16, UINT16, u16, U16, WORD, * PWORD, & RWORD, ** PPWORD, PROGMEM WORD_P;
typedef const unsigned short CWORD, * PCWORD, & RCWORD, ** PPCWORD;
typedef volatile unsigned short VU16, VWORD, * PVWORD, & RVWORD, ** PPVWORD;

typedef wchar_t wchar, WCHAR, * PWCHAR, & RWCHAR, ** PPWCHAR, PROGMEM WCHAR_P;
typedef const wchar_t CWCHAR, * PCWCHAR, & RCWCHAR, ** PPCWCHAR;
typedef volatile wchar_t VWCHAR, * PVWCHAR, & RVWCHAR, ** PPVWCHAR;

typedef long int32, INT32, i32, I32, LONG, * PLONG, & RLONG, ** PPLONG, PROGMEM LONG_P;
typedef const long CLONG, * PCLONG, & RCLONG, ** PPCLONG;
typedef volatile long V32, VLONG, * PVLONG, & RVLONG, ** PPVLONG;

typedef unsigned long uint32, UINT32, u32, U32, dword, DWORD, * PDWORD, & RDWORD, ** PPDWORD, PROGMEM DWORD_P;
typedef const unsigned long CDWORD, * PCDWORD, & RCDWORD, ** PPCDWORD;
typedef volatile unsigned long VU32, VDWORD, * PVDWORD, & RVDWORD, ** PPVDWORD;

typedef long long int64, INT64, i64, I64, verylong, VERYLONG, longlong, LONGLONG, * PLONGLONG, & RLONGLONG, ** PPLONGLONG, PROGMEM LONGLONG_P;
typedef const long long CLONGLONG, * PCLONGLONG, & RCLONGLONG, ** PPCLONGLONG;
typedef volatile long long V64, VLONGLONG, * PVLONGLONG, & RVLONGLONG, ** PPVLONGLONG;

typedef unsigned long long uint64, UINT64, u64, U64, qword, QWORD, * PQWORD, & RQWORD, ** PPQWORD, PROGMEM QWORD_P;
typedef const unsigned long long CQWORD, * PCQWORD, & RCQWORD, ** PPCQWORD;
typedef volatile unsigned long long VU64, VQWORD, * PVQWORD, & RVQWORD, ** PPVQWORD;

typedef int INT, * PINT, & RINT, ** PPINT, PROGMEM INT_P;
typedef const int CINT, * PCINT, & RCINT, ** PPCINT;
typedef volatile int VINT, * PVINT, & RVINT, ** PPVINT;

typedef unsigned int UINT, * PUINT, & RUINT, ** PPUINT, PROGMEM UINT_P;
typedef const unsigned int CUINT, * PCUINT, & RCUINT, ** PPCUINT;
typedef volatile unsigned int VUINT, * PVUINT, & RVUINT, ** PPVUINT;
typedef float FLOAT, * PFLOAT, & RFLOAT, ** PPFLOAT, PROGMEM FLOAT_P;
typedef const float CFLOAT, * PCFLOAT, & RCFLOAT, ** PPCFLOAT;
typedef volatile float VFLOAT, * PVFLOAT, & RVFLOAT, ** PPVFLOAT;

typedef double DOUBLE, * PDOUBLE, & RDOUBLE, ** PPDOUBLE, PROGMEM DOUBLE_P;
typedef const double CDOUBLE, * PCDOUBLE, & RCDOUBLE, ** PPCDOUBLE;
typedef volatile double VDOUBLE, * PVDOUBLE, & RVDOUBLE, ** PPVDOUBLE;

typedef size_t SIZE, * PSIZE, & RSIZE, ** PPSIZE, PROGMEM SIZE_P;
typedef const size_t CSIZE, * PCSIZE, & RCSIZE, ** PPCSIZE;

typedef ptrdiff_t PTRDIFF, * PPTRDIFF, & RPTRDIFF, ** PPPTRDIFF;
typedef const ptrdiff_t CPTRDIFF, * PCPTRDIFF, & RCPTRDIFF, ** PPCPTRDIFF;

typedef nullptr_t NULLPTR, * PNULLPTR, & RNULLPTR, ** PPNULLPTR;
typedef const nullptr_t CNULLPTR, * PCNULLPTR, & RCNULLPTR, ** PPCNULLPTR;


/* DATA TYPE ALIAS MACROS FOR SIGNAGE */

#define SIGNED(T) SIGNED_##T
#define SIGNED_BYTE			CHAR
#define SIGNED_WORD			SHORT
#define SIGNED_LONG			LONG
#define SIGNED_QWORD		LONGLONG

#define UNSIGNED(T) UNSIGNED_##T
#define UNSIGNED_CHAR		BYTE
#define UNSIGNED_SHORT		WORD
#define UNSIGNED_LONG		DWORD
#define UNSIGNED_LONGLONG	QWORD


#endif
