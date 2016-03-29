/*******************************************************************************
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
*
* Copyright © 2016 Thomas J. Biuso III ALL RIGHTS RESERVED.
*******************************************************************************/

#ifndef _ITTYBITTY_UTIL_H
#define _ITTYBITTY_UTIL_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_aliases.h"
#include "remove_const.cpp"


/* MACRO EXPANSION MACROS */

#define STR(x) #x
#define CONCAT(x, y) x##y
#define COMBA(a, b) a
#define COMBB(a, b) b


/* COMPILER MACROS */

#define PRAGMA_MACRO(x) _Pragma(#x)
#define IGNORE_WARNING(w) PRAGMA_MACRO(GCC diagnostic ignored #w)


/* ATTRIBUTES & META FUNCTION ALIASES */

#define PACKED __attribute__ ((packed))
#define BITFIELD STRUCT PACKED

#define TYPEOF(var) __typeof__(var)
#define SIZEOF(var) sizeof(var)
#define countof(var) (SIZEOF(var) / SIZEOF(0[var]))
#define CAPACITY(var) countof(var)


/* CASTING MACROS */

#define CONST_TYPE(type) CONST type
#define CONST_TYPEOF(var) CONST_TYPE(TYPEOF(var))

#define MAKE_CONST(var) const_cast<CONST_TYPEOF(var)>(var)
#define MAKE_CONST_2D(var) ((CONST_TYPEOF((var)[0][0])(*)[CAPACITY((var)[0])])(var))
#define MAKE_CONST_PP(var) ((CONST_TYPEOF(**(var))**)(var))
#define FORCE_CONST(var) (*const_cast<CONST_TYPEOF(var) *>(&(var)))

#define UNCONST(var) (*const_cast<typename remove_const<TYPEOF(var)>::type *>(&(var)))

#define UNION_CAST(var, to_type) (((UNION {TYPEOF(var) from; to_type to;})(var)).to)


#endif
