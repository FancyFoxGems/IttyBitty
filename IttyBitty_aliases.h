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
	#define null		((void *)0)
#endif

#ifndef NULL
	#define NULL		null
#endif

#ifndef nil
	#define nil			null
#endif

#ifndef NIL
	#define NIL			null
#endif

#ifndef TRUE
	#define TRUE		true
#endif

#ifndef FALSE
	#define FALSE		false
#endif

#define INLINE			inline
#define EXPLICIT		explicit
#define STATIC			static
#define FINAL			final
#define VIRTUAL			virtual

#define EXTERN			extern
#define EXTERN_C		EXTERN "C"
#define C_DECL			EXTERN_C

#define CONSTEXPR		constexpr	// NOTE: Only supported by Arduino 1.[?]+ (AVR GCC ?.XX)..?

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
#define interface		class
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

#define TYPEDEF_FUNCTION_ALIASES(return_type, parameter_clause, function_name, FUNCTION_ALIAS)					\
	typedef return_type function_name(parameter_clause), return_type FUNCTION_ALIAS(parameter_clause)			\
		return_type (*P##FUNCTION_ALIAS)(parameter_clause), return_type (&R##FUNCTION_ALIAS)(parameter_clause)

#define TYPEDEF_MODIFIER_ALIASES(modified_type_name, TYPE_ALIAS)		\
	typedef modified_type_name TYPE_ALIAS, * P##TYPE_ALIAS, & R##TYPE_ALIAS

#define TYPEDEF_ALIASES_NOMODIFIER(type_name, TYPE_ALIAS)		TYPEDEF_MODIFIER_ALIASES(type_name, TYPE_ALIAS)
#define TYPEDEF_CONST_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_MODIFIER_ALIASES(const type_name, C##TYPE_ALIAS)
#define TYPEDEF_VOLATILE_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_MODIFIER_ALIASES(volatile type_name, V##TYPE_ALIAS)
#define TYPEDEF_CONST_VOLATILE_ALIASES(type_name, TYPE_ALIAS)	TYPEDEF_MODIFIER_ALIASES(const volatile type_name, CV##TYPE_ALIAS)

#define TYPEDEF_PROGMEM_ALIAS(type_name, TYPE_ALIAS)			typedef type_name PROGMEM TYPE_ALIAS##_P

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
	TYPEDEF_ALIASES_WITH_VOLATILE_AND_PP(type_name, TYPE_ALIAS);			\
	TYPEDEF_PROGMEM_ALIAS(type_name, TYPE_ALIAS)

#define TYPEDEF_ENUM_ALIASES(type_name, TYPE_ALIAS)				TYPEDEF_ALIASES_WITH_PP(enum type_name, TYPE_ALIAS)
#define TYPEDEF_UNION_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_ALIASES_WITH_PP(union type_name, TYPE_ALIAS)
#define TYPEDEF_VOLATILE_UNION_ALIASES(type_name, TYPE_ALIAS)	TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(union type_name, TYPE_ALIAS)

#define TYPEDEF_CLASS_ALIASES(type_name, TYPE_ALIAS)			TYPEDEF_ALIASES_WITH_PP(class type_name, TYPE_ALIAS)
#define TYPEDEF_VOLATILE_CLASS_ALIASES(type_name, TYPE_ALIAS)	TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(class type_name, TYPE_ALIAS)

#define TYPEDEF_SINGLETON_CLASS_ALIASES(type_name, TYPE_ALIAS)			\
	typedef const type_name & RC##TYPE_ALIAS

#define TYPEDEF_STRUCT_ALIASES(type_alias, lower_type_alias, UPPER_TYPE_ALIAS)			\
	typedef struct EXPAND_CONCAT(_, type_alias) EXPAND_CONCAT(EXPAND_CONCAT(_, lower_type_alias),_t), type_alias;			\
	TYPEDEF_ALIASES_WITH_PP(struct EXPAND_CONCAT(_, type_alias), UPPER_TYPE_ALIAS)

#define TYPEDEF_VOLATILE_STRUCT_ALIASES(type_alias, lower_type_alias, UPPER_TYPE_ALIAS)	\
	typedef volatile struct EXPAND_CONCAT(_, type_alias) EXPAND_CONCAT(EXPAND_CONCAT(_, lower_type_alias),_t), type_alias;	\
	TYPEDEF_ALIASES_AS_VOLATILE_WITH_PP(struct EXPAND_CONCAT(_, type_alias), UPPER_TYPE_ALIAS)

#define TYPEDEF_SINGLETON_STRUCT_ALIASES(type_alias, TYPE_ALIAS)		\
	typedef struct EXPAND_CONCAT(_, type_alias)  TYPE_ALIAS;			\
	typedef const struct EXPAND_CONCAT(_, type_alias) & RC##TYPE_ALIAS

#define TEMPLATE_CLASS_USING_ALIASES(T_clause, T_params, type_name, TYPE_ALIAS)				\
	template T_clause																		\
	using TYPE_ALIAS = type_name T_params;													\
	template T_clause																		\
	using P##TYPE_ALIAS = type_name T_params *;												\
	template T_clause																		\
	using R##TYPE_ALIAS = type_name T_params &;												\
	template T_clause																		\
	using PP##TYPE_ALIAS = type_name T_params **;											\
	template T_clause																		\
	using RR##TYPE_ALIAS = type_name T_params &&;											\
	template T_clause																		\
	using C##TYPE_ALIAS = const type_name T_params;											\
	template T_clause																		\
	using PC##TYPE_ALIAS = const type_name T_params *;										\
	template T_clause																		\
	using RC##TYPE_ALIAS = const type_name T_params &;										\
	template T_clause																		\
	using PPC##TYPE_ALIAS = const type_name T_params **;									\
	template T_clause																		\
	using RRC##TYPE_ALIAS = const type_name T_params &&

#define TEMPLATE_STRUCT_USING_ALIASES(T_clause, T_params, type_alias, lower_type_alias, UPPER_TYPE_ALIAS)		\
	template T_clause																		\
	using EXPAND_CONCAT(EXPAND_CONCAT(_, lower_type_alias),_t) = struct EXPAND_CONCAT(_, type_alias) T_params;	\
	template T_clause																		\
	using type_alias = struct EXPAND_CONCAT(_, type_alias) T_params;						\
	template T_clause																		\
	using UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_params;					\
	template T_clause																		\
	using P##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_params *;				\
	template T_clause																		\
	using R##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_params &;				\
	template T_clause																		\
	using PP##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_params **;			\
	template T_clause																		\
	using RR##UPPER_TYPE_ALIAS = struct EXPAND_CONCAT(_, type_alias) T_params &&;			\
	template T_clause																		\
	using C##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_params;			\
	template T_clause																		\
	using PC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_params *;		\
	template T_clause																		\
	using RC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_params &;		\
	template T_clause																		\
	using PPC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_params **;	\
	template T_clause																		\
	using RRC##UPPER_TYPE_ALIAS = const struct EXPAND_CONCAT(_, type_alias) T_params &&



/* FLAG ENUMERATION DEFINITION ALIASES */

#define DEFINE_FLAG_ENUM_OPERATORS(enum_type, TYPE_ALIAS)	\
	INLINE CONST TYPE_ALIAS operator ~(CONST TYPE_ALIAS a) {							\
		return TYPE_ALIAS(INV static_cast<CBYTE>(a)); }									\
	INLINE CONST TYPE_ALIAS operator &(CONST TYPE_ALIAS a, CONST TYPE_ALIAS b) {		\
		return TYPE_ALIAS(BAND(static_cast<CBYTE>(a), static_cast<CBYTE>(b))); }		\
	INLINE CONST TYPE_ALIAS operator |(CONST TYPE_ALIAS a, CONST TYPE_ALIAS b) {		\
		return TYPE_ALIAS(BOR(static_cast<CBYTE>(a), static_cast<CBYTE>(b))); }			\
	INLINE CONST TYPE_ALIAS operator ^(CONST TYPE_ALIAS a, CONST TYPE_ALIAS b) {		\
		return TYPE_ALIAS(BXOR(static_cast<CBYTE>(a), static_cast<CBYTE>(b))); }		\
	INLINE TYPE_ALIAS & operator &=(TYPE_ALIAS & a, CONST TYPE_ALIAS b) {				\
		return reinterpret_cast<TYPE_ALIAS &>(											\
			MASK_BITS(reinterpret_cast<RBYTE>(a), static_cast<CBYTE>(b))); }			\
	INLINE TYPE_ALIAS & operator |=(TYPE_ALIAS & a, CONST TYPE_ALIAS b) {				\
		return reinterpret_cast<TYPE_ALIAS &>(											\
			SET_BITS(reinterpret_cast<RBYTE>(a), static_cast<CBYTE>(b))); }				\
	INLINE TYPE_ALIAS & operator ^=(TYPE_ALIAS & a, CONST TYPE_ALIAS b) {				\
		return reinterpret_cast<TYPE_ALIAS &>(											\
			FLIP_BITS(reinterpret_cast<RBYTE>(a), static_cast<CBYTE>(b))); }			\
	INLINE CONST TYPE_ALIAS enum_type##Has(CONST TYPE_ALIAS a, CONST TYPE_ALIAS b) {	\
		return MASK(a, b); }															\

#define DECLARE_ENUM_AS_FLAGS(enum_type, TYPE_ALIAS)		\
	TYPEDEF_ENUM_ALIASES(enum_type, TYPE_ALIAS);			\
	DEFINE_FLAG_ENUM_OPERATORS(enum_type, TYPE_ALIAS);



/* (NATIVE) FUNDAMENTAL DATA TYPE ALIASES FOR WIN32 API-STYLE TYPE REFERENCES  */

typedef void VOID, * PTR, ** PPTR, * PVOID, ** PPVOID, * PROGMEM PVOID_P;
typedef const void * CPTR, ** PCPTR, * PCVOID, ** PPCVOID;


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(bool, BOOL);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(bool, BIT);

typedef bool bit;

#ifndef ARDUINO
typedef bool boolean;
#endif


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(char, NYBBLE);

typedef char nybble;


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(char, CHAR);

// NOTE: No CONST aliases for INT8 because {PCINT8} is an identifier reserved for an AVR interrupt vector constant...
TYPEDEF_ALIASES_NOMODIFIER(char, INT8);
TYPEDEF_VOLATILE_ALIASES(char, INT8);
TYPEDEF_CONST_VOLATILE_ALIASES(char, INT8);
TYPEDEF_ALIASES_PP(char, INT8);

typedef char int8, I8;
typedef char * cstring, * CSTRING, * CSTRING_P PROGMEM;
typedef const char * CCSTRING;
typedef volatile char V8;

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned char, BYTE);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned char, UINT8);

typedef unsigned char uint8, U8;
typedef volatile unsigned char VU8;

#ifndef ARDUINO
typedef unsigned char byte;
#endif


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(short, SHORT);

// ...and same for {PCINT16}.
TYPEDEF_ALIASES_NOMODIFIER(short, INT16);
TYPEDEF_VOLATILE_ALIASES(short, INT16);
TYPEDEF_CONST_VOLATILE_ALIASES(short, INT16);
TYPEDEF_ALIASES_PP(short, INT16);

typedef short int16, I16;
typedef volatile short V16;

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned short, WORD);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned short, UINT16);

typedef unsigned short uint16, U16;
typedef volatile unsigned short VU16;

#ifndef ARDUINO
typedef unsigned short word;
#endif

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(wchar_t, WCHAR);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(wchar_t, CHAR16);


typedef wchar_t wchar, unicode, UNICODE, unicode16, UNICODE16;
typedef wchar_t * widestring, * WIDE_STRING, * UNICODE_STRING, * UNICODE16_STRING;
typedef wchar_t * WIDE_STRING_STRING_P PROGMEM, * UNICODE_STRING_P PROGMEM, * UNICODE16_STRING_P PROGMEM;
typedef const wchar_t * CWIDE_STRING, * CUNICODE_STRING, * CUNICODE16_STRING;


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(long, LONG);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(long, INT32);

typedef long int32, I32;
typedef volatile long V32;

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned long, DWORD);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned long, UINT32);

typedef unsigned long dword, uint32, U32;
typedef volatile unsigned long VU32;


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(long long, LONGLONG);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(long long, INT64);

typedef long long int64, I64, verylong, VERYLONG, muchlong, somuchslong;
typedef volatile long long V64;

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned long long, QWORD);
TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned long long, UINT64);

typedef unsigned long long qword, uint64, U64;
typedef volatile unsigned long long VU64;


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(int, INT);

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(unsigned int, UINT);


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(size_t, SIZE);
typedef size_t size;

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(ptrdiff_t, PTRDIFF);
typedef ptrdiff_t ptrdiff;


TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(float, FLOAT);

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(double, DOUBLE);


#ifndef nullptr_t
typedef decltype(nullptr) nullptr_t;
#endif

TYPEDEF_ALIASES_WITH_VOLATILE_PP_AND_PROGMEM(nullptr_t, NULLPTR);


#ifdef ARDUINO
#include "WString.h"
typedef const __FlashStringHelper * FLASH_STRING, * FSTRING, * PROGMEM_STRING, * PROG_STRING;
#endif


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
