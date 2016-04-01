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


#include "IttyBitty_type_traits.h"
//#include "placement_new.cpp"


/* MACRO EXPANSION MACROS */

#define STR(x) #x
#define CONCAT(x, y) x##y
#define COMBA(a, b) a
#define COMBB(a, b) b


/* COMPILER MACROS */

#define PRAGMA_MACRO(x) _Pragma(#x)
#define IGNORE_WARNING(w) PRAGMA_MACRO(GCC diagnostic ignored #w)


/* ATTRIBUTE, QUALIFIER, & METAFUNCTION ALIASES */

#define PACKED __attribute__ ((packed))
#define BITFIELD_STRUCT STRUCT PACKED

#define SIZEOF(var) sizeof(var)

#define countof(var) (SIZEOF(var) / SIZEOF(0[var]))
#define CAPACITY(var) countof(var)

#define TYPE(T) identity_t<T>

#define CONST_TYPE(T) add_const_t<T>
#define UNCONST_TYPE(T) remove_const_t<T>

#define VOLATILE_TYPE(T) add_volatile_t<T>
#define UNVOLATILE_TYPE(T) remove_volatile_t<T>

#define CV_TYPE(T) add_cv_t<T>
#define UNCV_TYPE(T) remove_cv_t<T>

#define ONLY_CONST_TYPE(T) CONST_TYPE(UNVOLATILE_TYPE(T))
#define ONLY_VOLATILE_TYPE(T) VOLATILE_TYPE(UNCONST_TYPE(T))

#define TYPEOF(var) decltype(var)
#define CONST_TYPEOF(var) CONST_TYPE(TYPEOF(var))
#define UNCONST_TYPEOF(var) UNCONST_TYPE(TYPEOF(var))
#define CV_TYPEOF(var) CV_TYPE(TYPEOF(var))

#define ONLY_CONST_TYPEOF(var) ONLY_CONST_TYPE(TYPEOF(var))
#define ONLY_VOLATILE_TYPEOF(var) ONLY_VOLATILE_TYPE(TYPEOF(var))

#define POINTER_TYPE(T) add_pointer_t<T, FALSE>
#define UNPOINTER_TYPE(T) remove_pointer_t<T>

#define RVALUE_TYPE(T) add_rvalue_ref_t<T>
#define UNRVALUE_TYPE(T) remove_rvalue_ref_t<T>

#define REFERENCE_TYPE(T) add_pointer_t<T>
#define UNREFERENCE_TYPE(T) remove_pointer_t<T>

#define MAKE_SIGNED(T) make_signed_t<T>
#define MAKE_UNSIGNED(T) make_unsigned_t<T>

#define ENABLE_IF(condition, T) enable_if_t<condition, T>
#define TYPE_IF(condition, T, F) conditional_t<condition, T, F>


/* CASTING MACROS */

#define MAKE_CONST(var) const_cast<ONLY_CONST_TYPEOF(var)>(var)
#define MAKE_CONST_2D(var) ((ONLY_CONST_TYPEOF((var)[0][0])(*)[CAPACITY((var)[0])])(var))
#define MAKE_CONST_PP(var) ((ONLY_CONST_TYPEOF(**(var))**)(var))
#define FORCE_CONST(var) (*const_cast<ONLY_CONST_TYPEOF(var) *>(&(var)))

#define UNCONST(var) (*const_cast<UNCONST_TYPEOF(var)>::type *>(&(var)))

#define UNION_CAST(var, to_type) (((UNION {TYPEOF(var) from; to_type to;})(var)).to)


#endif
