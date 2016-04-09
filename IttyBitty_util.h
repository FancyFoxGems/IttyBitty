/**********************************************************************************
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#ifndef _ITTYBITTY_UTIL_H
#define _ITTYBITTY_UTIL_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include <stdlib.h>

#include "IttyBitty_type_traits.h"
#include "placement_new.cpp"


/* MACRO EXPANSION MACROS */

#define STR(x) #x
#define CONCAT(x, y) x##y
#define COMBA(a, b, c) a
#define COMBB(a, b, c) b
#define COMBC(a, b, c) c


/* COMPILER MACROS */

#define PRAGMA_MACRO(x) _Pragma(#x)
#define IGNORE_WARNING(w) PRAGMA_MACRO(GCC diagnostic ignored #w)


/* ATTRIBUTE & TYPE INFO ALIASES */

#define PACKED __attribute__ ((packed))
#define PACKED_UNION UNION PACKED
#define PACKED_STRUCT STRUCT PACKED
#define BITFIELD_STRUCT PACKED_STRUCT

#define SIZEOF(var) sizeof(var)

#define countof(var) (SIZEOF(var) / SIZEOF(0[var]))
#define CAPACITY(var) countof(var)


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

#define T_SIZE SIZEOF(T)

#define FORCE_ANONYMOUS_CONSTRUCTION(constructor_expr) (constructor_expr)
#define _CONSTRUCT(constructor_expr) FORCE_ANONYMOUS_CONSTRUCTION(constructor_expr)

#define FLASH_STRING(string_addr) ((CSTR_P)(string_addr))
#define _CSTR_P(string_addr) FLASH_STRING(string_addr)


/* MEMORY SECTION/ALLOCATION VARIABLES & FUNCTIONS */

extern PCHAR __data_start;
extern PCHAR __data_end;
extern PCHAR __bss_start;
extern PCHAR __bss_end;
extern PCHAR __heap_start;
extern PCHAR __heap_end;

extern PVOID __brkval;

extern PCHAR __malloc_heap_start;
extern PCHAR __malloc_heap_end;
extern SIZE __malloc_margin;

CONSTEXPR PVUINT StackPointer()
{
	return &static_cast<RVUINT>(SP);
}

INLINE WORD StackSpaceTotal()
{
	WORD stackEnd = reinterpret_cast<WORD>(__heap_end);

	if (stackEnd > RAMEND)
		stackEnd = reinterpret_cast<WORD>(__bss_end);

	return static_cast<WORD>(RAMEND) + 1 - stackEnd - __malloc_margin;
}

INLINE WORD StackSpaceUsed()
{
	return static_cast<WORD>(RAMEND) + 1 - reinterpret_cast<WORD>(StackPointer());
}

INLINE WORD StackSpaceAvailable()
{
	return StackSpaceTotal() - reinterpret_cast<WORD>(StackPointer());
}

INLINE PCHAR HeapPointer()
{
	if (reinterpret_cast<WORD>(__brkval) == 0)
		return __heap_start;

	return reinterpret_cast<PCHAR>(__brkval);
}

INLINE WORD HeapSpaceTotal()
{
	return reinterpret_cast<WORD>(__heap_end) - reinterpret_cast<WORD>(__heap_start);
}

INLINE WORD HeapSpaceUsed()
{
	return reinterpret_cast<WORD>(HeapPointer()) - reinterpret_cast<WORD>(__heap_start);
}

INLINE WORD HeapSpaceAvailable()
{
	return reinterpret_cast<WORD>(__heap_end) - reinterpret_cast<WORD>(HeapPointer());
}

CONSTEXPR WORD SRAMTotalSize()
{
	return static_cast<WORD>(RAMEND) + 1 - static_cast<WORD>(RAMSTART);
}

INLINE WORD SRAMUsed()
{
#ifdef XRAMSTART
	if (reinterpret_cast<WORD>(__heap_start) > RAMEND)
		return StackSpaceUsed();
#endif

	return StackSpaceUsed() + HeapSpaceUsed();
}

INLINE WORD SRAMAvailable()
{
#ifdef XRAMSTART
	if (reinterpret_cast<WORD>(__heap_start) > RAMEND)
		return StackSpaceAvailable();
#endif

	return StackSpaceAvailable() + HeapSpaceAvailable();
}

CONSTEXPR WORD XRAMTotalSize()
{
	return static_cast<WORD>(XRAMSIZE);
}


#ifdef XRAMSTART

INLINE WORD XRAMUsed()
{
	WORD stackEnd = reinterpret_cast<WORD>(__heap_end);

	if (stackEnd > RAMEND)
		stackEnd = reinterpret_cast<WORD>(__bss_end);

	return static_cast<WORD>(RAMEND) + 1 - stackEnd - __malloc_margin;
}

INLINE WORD XRAMAvailable()
{
	return XRAMTotalSize() - XRAMUsed();
}

INLINE WORD TotalRAMUsed()
{
	return SRAMUsed() + XRAMUsed();
}

INLINE WORD TotalRAMAvailable()
{
	return SRAMAvailable() + XRAMAvailable();
}

#else	// #ifndef XRAMSTART

INLINE WORD TotalRAMUsed()
{
	return SRAMUsed();
}

INLINE WORD TotalRAMAvailable()
{
	return SRAMAvailable();
}

#endif	// #ifdef XRAMSTART


CONSTEXPR WORD TotalRAMSize()
{
	return SRAMTotalSize() + XRAMTotalSize();
}

CONSTEXPR WORD EEPROMTotalSize()
{
	return static_cast<WORD>(E2END) + 1;
}

CONSTEXPR WORD FlashTotalSize()
{
	return static_cast<WORD>(FLASHEND) + 1;
}

CONSTEXPR WORD (*ProgMemTotalSize)() = &FlashTotalSize;


/* MISCELLANEOUS GENERAL PURPOSE FUNCTIONS */

template<typename T, typename R = VOID, typename ... args>
INLINE R Apply(T * tInstance, R (T::*function)(args...), args ... params)
{
	return (tInstance->*function)(&params...);
}


#endif
