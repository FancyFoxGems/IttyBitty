/**********************************************************************************
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_UTIL_H
#define _ITTYBITTY_UTIL_H


#include "IttyBitty_type_traits.h"


/* MACRO EXPANSION MACROS */

#define NULL_MACRO(x) 
#define EXPAND(x) x
#define STR(x) #x
#define EXPAND_STR(x) STR(x)
#define CONCAT(x, y) x##y
#define EXPAND_CONCAT(x, y) CONCAT(x, y)


/* COMPILER MACROS */

#define PRAGMA_MACRO(x) _Pragma(#x)
#define IGNORE_WARNING(w) PRAGMA_MACRO(GCC diagnostic ignored #w)

#define VAR_NAME_VALUE(var) #var " = " EXPAND_STR(var)
#define PRINT_VAR(var) PRAGMA_MACRO(message(#var " = " EXPAND_STR(var)))


/* ATTRIBUTE & TYPE INFO ALIASES */

#define PACKED __attribute__ ((packed))
#define PACKED_UNION UNION PACKED
#define PACKED_STRUCT STRUCT PACKED
#define BITFIELD_STRUCT PACKED_STRUCT

#define SIZEOF(var) sizeof(var)

#define countof(var) (SIZEOF(var) / SIZEOF(0[var]))


/* METAFUNCTION ALIASES */

using std::identity_t;
using std::add_const_t;
using std::remove_const_t;
using std::add_volatile_t;
using std::remove_volatile_t;
using std::add_cv_t;
using std::remove_cv_t;
using std::add_pointer_t;
using std::remove_pointer_t;
using std::add_rvalue_ref_t;
using std::remove_rvalue_ref_t;
using std::make_signed_t;
using std::make_unsigned_t;
using std::enable_if_t;
using std::conditional_t;
using std::extent;

#define TYPE(T) identity_t<T>
#define TYPEOF(var) decltype(var)

#define CONST_TYPE(T) add_const_t<T>
#define CONST_TYPEOF(var) CONST_TYPE(TYPEOF(var))

#define UNCONST_TYPE(T) remove_const_t<T>
#define UNCONST_TYPEOF(var) UNCONST_TYPE(TYPEOF(var))

#define VOLATILE_TYPE(T) add_volatile_t<T>
#define UNVOLATILE_TYPE(T) remove_volatile_t<T>

#define CV_TYPE(T) add_cv_t<T>
#define CV_TYPEOF(var) CV_TYPE(TYPEOF(var))

#define UNCV_TYPE(T) remove_cv_t<T>
#define UNCV_TYPEOF(var) UNCV_TYPE(TYPEOF(var))

#define ONLY_CONST_TYPE(T) CONST_TYPE(UNVOLATILE_TYPE(T))
#define ONLY_CONST_TYPEOF(var) ONLY_CONST_TYPE(TYPEOF(var))

#define ONLY_VOLATILE_TYPE(T) VOLATILE_TYPE(UNCONST_TYPE(T))
#define ONLY_VOLATILE_TYPEOF(var) ONLY_VOLATILE_TYPE(TYPEOF(var))

#define POINTER_TYPE(T) add_pointer_t<T, FALSE>
#define ONLY_VOLATILE_TYPEOF(var) ONLY_VOLATILE_TYPE(TYPEOF(var))

#define UNPOINTER_TYPE(T) remove_pointer_t<T>
#define UNPOINTER_TYPEOF(var) UNPOINTER_TYPE(TYPEOF(var))

#define RVALUE_TYPE(T) add_rvalue_ref_t<T>
#define RVALUE_TYPEOF(var) RVALUE_TYPE(TYPEOF(var))

#define UNRVALUE_TYPE(T) remove_rvalue_ref_t<T>
#define UNRVALUE_TYPEOF(var) UNRVALUE_TYPE(TYPEOF(var))

#define REFERENCE_TYPE(T) add_pointer_t<T>
#define REFERENCE_TYPEOF(var) REFERENCE_TYPE(TYPEOF(var))

#define UNREFERENCE_TYPE(T) remove_pointer_t<T>
#define UNREFERENCE_TYPEOF(var) UNREFERENCE_TYPE(TYPEOF(var))

#define SIGNED_TYPE(T) make_signed_t<T>
#define SIGNED_TYPEOF(var) SIGNED_TYPE(TYPEOF(var))

#define UNSIGNED_TYPE(T) make_unsigned_t<T>
#define UNSIGNED_TYPEOF(var) UNSIGNED_TYPE(TYPEOF(var))

#define MAKE_SIGNED(var) static_cast<SIGNED_TYPEOF(var)>(var)
#define MAKE_UNSIGNED(var) static_cast<UNSIGNED_TYPEOF(var)>(var)

#define ENABLE_IF(condition, T) enable_if_t<condition, T>
#define TYPE_IF(condition, T, F) conditional_t<condition, T, F>

#define CAPACITY(var) extent<TYPEOF(var)>::value


/* DATA TYPE SIZES */

#define BITS_PER_BYTE 8

#define BYTE_SIZE(T) SIZEOF(T)
#define BYTE_SIZEOF(var) BYTE_SIZE(TYPEOF(var))

#define BIT_SIZE(type) static_cast<SIZE>(SIZEOF(type) * BITS_PER_BYTE)
#define BIT_SIZEOF(var) BIT_SIZE(TYPEOF(var))


/* CASTING MACROS */

#define MAKE_CONST(var) const_cast<ONLY_CONST_TYPEOF(var)>(var)
#define MAKE_CONST_2D(var) ((ONLY_CONST_TYPEOF((var)[0][0])(*)[CAPACITY((var)[0])])(var))
#define MAKE_CONST_PP(var) ((ONLY_CONST_TYPE(UNPOINTER_TYPE(UNPOINTER_TYPE(TYPEOF(var)))) **)(var))
#define FORCE_CONST(var) (*const_cast<ONLY_CONST_TYPEOF(var) *>(&(var)))

#define UNCONST(var) (*const_cast<UNCONST_TYPEOF(var) *>(&(var)))

#define UNION_CAST(var, to_type) (((UNION {TYPEOF(var) from; to_type to;})(var)).to)


/* MISCELLANEOUS GENERAL PURPOSE MACROS */

#define ASM(expr) __asm__(expr)

#define T_SIZE SIZEOF(T)

#define FORCE_ANONYMOUS_CONSTRUCTION(constructor_expr) (constructor_expr)
#define _CONSTRUCT(constructor_expr) FORCE_ANONYMOUS_CONSTRUCTION(constructor_expr)

#define FLASH_STRING(string_addr) ((CSTR_P)(string_addr))
#define _CSTR_P(string_addr) FLASH_STRING(string_addr)

template<typename T, T N> 
struct overflow { char operator()() { return N + 256; } };

#define PRINT_COMPILE_CONST(var) char(overflow<TYPEOF(var), var>())


/* PLACEMENT NEW IMPLEMENTATION */

#if !defined(ARDUINO) || ARDUINO < 20000 // NOTE: Assume Arduino 2.0+ will define placement new??

	INLINE PVOID operator new(SIZE size, PVOID ptr)
	{
		return ptr;
	}

	INLINE PVOID operator new[](SIZE size, PVOID ptr)
	{
		return ptr;
	}
		
#endif	// if !defined(ARDUINO)...


/* MISCELLANEOUS GENERAL PURPOSE FUNCTIONS */

template<typename T, typename R = VOID, typename ... args>
INLINE R Apply(T * tInstance, R (T::*function)(args...), args ... params)
{
	return (tInstance->*function)(&params...);
}


#endif
