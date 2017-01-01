/***********************************************************************************************
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_UTIL_H
#define _ITTYBITTY_UTIL_H


/* GCC WARNING SUPPRESSIONS */

#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"


#include "IttyBitty_type_traits.h"


/* STATEMENT ATTRIBUTE ALIASES */

#define FALLTHROUGH()				__attribute__((fallthrough));


/* MULTI-PURPOSE TYPE, VARIABLE, and/or FUNCTION ATTRIBUTE ALIASES */

#define NO_REORDER					__attribute__((no_reorder))
#define WEAK						__attribute__((weak))

#define USED						__attribute__((used))
#define UNUSED						__attribute__((unused))

#define DEPRECATED					__attribute__((deprecated))
#define DEPRECATED_MSG(msg)			__attribute__((deprecated(msg)))
#define DEPRECATED_1(msg)			DEPRECATED_MSG(deprecated(msg)

#define DEFAULT_ALIGNED				__attribute__((aligned))
#define ALIGN						DEFAULT_ALIGNED
#define ALIGNED(alignment_bytes)	__attribute__((aligned(alignment_bytes)))

#define VISIBILITY(scope)			__attribute__((visibility(EXPAND_STR(scope))))
#define DEFAULT_VISIBILIITY			VISIBILITY(default)
#define HIDDEN_VISIBILIITY			VISIBILITY(hidden)
#define INTERNAL_VISIBILIITY		VISIBILITY(internal)
#define PROTECTED_VISIBILIITY		VISIBILITY(protected)

#define SECTION(section_name)				__attribute__((section("." EXPAND_STR(section_name))))
#define MEMORY_SECTION(section_name)		SECTION(section_name)


/* TYPE ATTRIBUTE ALIASES */

#define MAY_ALIAS					__attribute__((may_alias))

#define TRANSPARENT_UNION			UNION __attribute__((transparent))

#define DESIGNATED_UNIT				__attribute__((designated_unit))
#define DESIGNATED_UNIT_STRUCT		STRUCT DESIGNATED_UNIT

#define VARIABLE_SIZE				__attribute__((bnd_variable_size))
#define VARIABLE_SIZE_STRUCT		STRUCT VARIABLE_SIZE


#define SCALAR_STORAGE_ORDER(endianness)	__attribute__((scalar_storage_order (EXPAND_STR(endianness))))
#define ENDIANNESS(endianness)				SCALAR_STORAGE_ORDER(endianness)
#define LITTLE_ENDIAN						SCALAR_STORAGE_ORDER(little-endian)
#define BIG_ENDIAN							SCALAR_STORAGE_ORDER(big-endian)
#define NETWORK_ORDER						BIG_ENDIAN

#define PACKED						__attribute__((packed))
#define PACKED_UNION				UNION PACKED
#define PACKED_STRUCT				STRUCT PACKED
#define BITFIELD_STRUCT				PACKED_STRUCT MAY_ALIAS


/* VARIABLE ATTRIBUTE ALIASES */

#define NOINIT_VAR					SECTION(noinit)
#define EEPROM_VAR					SECTION(eeprom)
#define FLASH_VAR					PROGMEM

#define IO(addr)					__attribute__((io(addr)))
#define IO_VAR(addr)				IO(addr)
#define IO_LOW(addr)				__attribute__((io_low(addr)))
#define IO_LOW_VAR(addr)			IO_LOW(addr)
#define ADDRESS(addr)				__attribute__((address(addr)))
#define ADDRESS_VAR(addr)			ADDRESS(addr)

#define CLEANUP(func)				__attribute__((cleanup(func)))
#define FUNC_CLEANUP(func)			CLEANUP(func)


/* FUNCTION ATTRIBUTE ALIASES */

#define USED_FUNC					USED
#define UNUSED_FUNC					UNUSED
#define WEAK_FUNC					WEAK

#define DEPRECATED_FUNC				DEPRECATED
#define DEPRECATED_FUNC_MSG(msg)	DEPRECATED(msg)
#define DEPRECATED_FUNC_1(msg)		DEPRECATED(msg)


#define ERROR_FUNC(msg)				__attribute__((error(EXPAND_STR(msg))))
#define WARNING_FUNC(msg)			__attribute__((warning(EXPAND_STR(msg))))

#define OPTIMIZE(level)				__attribute__((optimize(EXPAND_STR(level))))

#define FLATTEN						__attribute__((flatten))

#define CONST_FUNC					__attribute__((const))

#define NAKED						__attribute__((naked))
#define NAKED_FUNC					NAKED
#define PURE						__attribute__((pure))
#define PURE_FUNC					PURE
#define NORETURN					__attribute__((noreturn))
#define NORETURN_FUNC				NORETURN

#define ALWAYS_INLINE				__attribute__((always_inline))
#define INLINE_FUNC					ALWAYS_INLINE
#define GNU_INLINE					__attribute__((gnu_inline))
#define GNU_INLINE_FUNC				GNU_INLINE
#define NO_INLINE					__attribute__((no_inline))
#define NO_INLINE_FUNC				NO_INLINE

#define COLD						__attribute__((cold))
#define COLD_FUNC					COLD
#define HOT							__attribute__((hot))
#define HOT_FUNC					HOT

#define RETURNS_NONNULL				__attribute__((returns_nonnull))
#define NONNULL_RESULT				RETURNS_NONNULL
#define WARN_UNUSED_RESULT			__attribute__((warn_unused_result))
#define MUST_USE_RESULT				WARN_UNUSED_RESULT

#define WEAK_REF(ref_func_name)		__attribute__((weakref(EXPAND_STR(ref_func_name))))
#define ALIAS_FUNC(ref_func_name)	WEAK_REF(ref_func_name)
#define ALIAS(ref_func_name)		WEAK_REF(ref_func_name)

#define IFUNC(resolver_func_name)			__attribute__((ifunc(EXPAND_STR(resolver_func_name))))
#define RESOLVER_FUNC(resolver_func_name)	IFUNC(resolver_func_name)
#define RESOLVER(resolver_func_name)		IFUNC(resolver_func_name)

#define FORMAT(archetype_func, format_param_idx, first_arg_idx)			\
	__attribute__((format(archetype_func, format_param_idx, first_arg_idx)))
#define FORMAT_FUNC(archetype_func, format_param_idx, first_arg_idx)	\
	FORMAT(archetype_func, format_param_idx, first_arg_idx)
#define PRINTF_FORMAT(format_param_idx, first_arg_idx)					\
	__attribute__((format(printf, format_param_idx, first_arg_idx)))
#define PRINTF_FORMAT_FUNC(format_param_idx, first_arg_idx)				\
	PRINTF_FORMAT(format_param_idx, first_arg_idx)

#define FORMAT_ARG(format_param_idx)		__attribute__((format_arg(format_param_idx)))

#define NONNULL_ARG(ptr_param_idx)			__attribute__((nonnull_arg(ptr_param_idx)))
#define NONNULL_ARGS(ptr_param_idx_1, ptr_param_idx_2)		NONNULL_ARG(ptr_param_idx_1, ptr_param_idx_2)
#define NONNULL_ARG_2(ptr_param_idx_1, ptr_param_idx_2)		NONNULL_ARG(ptr_param_idx_1, ptr_param_idx_2)

#define ALLOC_ALIGN(align_param_idx)		__attribute__((alloc_align(align_param_idx)))
#define ALLOC_ALIGNED(align_param_idx)		ALLOC_ALIGN(align_param_idx)
#define RESULT_ALIGN_PARAM(align_param_idx)	ALLOC_ALIGN(align_param_idx)

#define ASSUME_ALIGNED(alignment_bytes)		__attribute__((assume_aligned(alignment_bytes)))
#define RESULT_ALIGNED(alignment_bytes)		ASSUME_ALIGNED(alignment_bytes)
#define ASSUME_ALIGNED_2(alignment_bytes, misalignment_offset)			\
	ASSUME_ALIGNED(assume_aligned(alignment_bytes, misalignment_offset)
#define RESULT_ALIGNED_2(alignment_bytes, misalignment_offset)			\
	ASSUME_ALIGNED(alignment_bytes, misalignment_offset)

#define ALLOC_SIZE(size_param_idx)			__attribute__((alloc_size(size_param_idx)))
#define RESULT_SIZE_PARAM(size_param_idx)	ALLOC_SIZE(size_param_idx)
#define ALLOC_SIZES(size_param_idx_1, size_param_idx_2)					\
	ALLOC_SIZE((size_param_idx_1, size_param_idx_2)
#define ALLOC_SIZE_2(size_param_idx_1, size_param_idx_2)				\
	ALLOC_SIZE(alloc_size(size_param_idx_1, size_param_idx_2)
#define RESULT_SIZE_PARAMS(size_param_idx_1, size_param_idx_2)			\
	ALLOC_SIZE(size_param_idx_1, size_param_idx_2)
#define RESULT_SIZE_PARAMS_2(size_param_idx_1, size_param_idx_2)		\
	ALLOC_SIZE(size_param_idx_1, size_param_idx_2)

#define CONSTRUCTOR					__attribute__((constructor))
#define CONSTRUCTOR_FUNC			CONSTRUCTOR
#define INIT_FUNC					CONSTRUCTOR

#define CONSTRUCTOR_PRIORITY(priority)			__attribute__((constructor(priority)))
#define CONSTRUCTOR_FUNC_PRIORITY(priority)		CONSTRUCTOR_PRIORITY(priority)
#define INIT_FUNC_PRIORITY(priority)			CONSTRUCTOR_PRIORITY(priority)

#define DESTRUCTOR					__attribute__((destructor))
#define DESTRUCTOR_FUNC				DESTRUCTOR
#define EXIT_FUNC					DESTRUCTOR

#define DESTRUCTOR_PRIORITY(priority)			__attribute__((destructor(priority)))
#define DESTRUCTOR_FUNC_PRIORITY(priority)		DESTRUCTOR_PRIORITY(priority)
#define EXIT_FUNC_PRIORITY(priority)			DESTRUCTOR_PRIORITY(priority)

#define FUNC_SECTION(section_name)	SECTION(section_name) INTERNAL_VISIBILIITY NAKED_FUNC USED

#define INIT_SECTION(init_num)		FUNC_SECTION(init##init_num)
#define INIT0						INIT_SECTION(0)
#define INIT1						INIT_SECTION(1)
#define INIT2						INIT_SECTION(2)
#define INIT3						INIT_SECTION(3)
#define INIT4						INIT_SECTION(4)
#define INIT5						INIT_SECTION(5)
#define INIT6						INIT_SECTION(6)
#define INIT7						INIT_SECTION(7)
#define INIT8						INIT_SECTION(8)
#define INIT9						INIT_SECTION(9)

#define FINI_SECTION(fini_num)		FUNC_SECTION(fini##fini_num)
#define FINI9						FINI_SECTION(9)
#define FINI8						FINI_SECTION(8)
#define FINI7						FINI_SECTION(7)
#define FINI6						FINI_SECTION(6)
#define FINI5						FINI_SECTION(5)
#define FINI4						FINI_SECTION(4)
#define FINI3						FINI_SECTION(3)
#define FINI2						FINI_SECTION(2)
#define FINI1						FINI_SECTION(1)
#define FINI0						FINI_SECTION(0)


/* DATA TYPE SIZES */

#define BITS_PER_NYBBLE		4
#define NYBBLE_BITS			BITS_PER_NYBBLE
#define NYBBLE_BITWIDTH		BITS_PER_NYBBLE
#define BITS_PER_BYTE		(2 * BITS_PER_NYBBLE)
#define BYTE_BITS			BITS_PER_BYTE
#define BYTE_BITWIDTH		BITS_PER_BYTE
#define BITS_PER_WORD		(2 * BITS_PER_BYTE)
#define WORD_BITS			BITS_PER_WORD
#define WORD_BITWIDTH		BITS_PER_WORD
#define BITS_PER_DWORD		(2 * BITS_PER_WORD)
#define DWORD_BITS			BITS_PER_DWORD
#define DWORD_BITWIDTH		BITS_PER_DWORD
#define BITS_PER_QWORD		(2 * BITS_PER_DWORD)
#define QWORD_BITWIDTH		BITS_PER_QWORD
#define QWORD_BITS			BITS_PER_QWORD

#define kilo				1000
#define kilobit_BITS		kilo
#define kilobit				kilobit_BITS

#define KILO				1024
#define KILObit_BITS		KILO
#define KILObit				KILObit_BITS
#define KILOBYTE_BITS		KILO * BITS_PER_BYTE
#define KILOBYTE			KILOBYTE_BITS

#define mega				kilo * kilo
#define megabit_BITS		mega
#define megabit				megabit_BITS

#define MEGA				KILO * KILO
#define MEGAbit_BITS		MEGA
#define MEGAbit				MEGAbit_BITS
#define MEGABYTE_BITS		MEGA * BITS_PER_BYTE
#define MEGABYTE			MEGABYTE_BITS


/* TYPE INFO ALIASES */

#define typeof(var)					decltype(var)
#define TYPEOF(var)					typeof(var)

#define OFFSETOF(type, member_var)	offsetof(type, member_var)

#define SIZEOF(var)					sizeof(var)


/* COMPILER MACROS */

#define ASM(expr)						__asm__ __volatile__(expr)

#define NOP()							ASM("nop")

#define COMPILER_BARRIER()				ASM("" : : : "memory")
#define MEMORY_BARRIER()				COMPILER_BARRIER()
#define BARRIER()						COMPILER_BARRIER()

#define PREFETCH(addr, ARGS...)			VA_MACRO(PREFETCH, addr, ##ARGS)
#define PREFETCH_1(addr)				__builtin_prefetch (addr)
#define PREFETCH_2(addr, rw)			__builtin_prefetch (addr, rw)
#define PREFETCH_3(addr, rw, locality)	__builtin_prefetch (addr, rw, locality)

#define EXPECT(expr, val)				__builtin_expect(expr, val)
#define EXPECTED(expr)					EXPECT(expr, TRUE)
#define NOT_EXPECTED(expr)				EXPECT(expr, FALSE)

#define PRAGMA_MACRO(pragma_clause)		_Pragma(#pragma_clause)
#define IGNORE_WARNING(gcc_warning)		PRAGMA_MACRO(GCC diagnostic ignored "-W" #gcc_warning)

#define CODE_FILE_NAME()				_builtin_FILE()
#define CODE_LINE_NUMBER()				_builtin_LINE()
#define CODE_FUNCTION_NAME()			_builtin_FUNCTION()
#define CODE_FUNCTION_SIGNATURE()		__PRETTY_FUNCTION__

#define CODE_FILE_NAME_P()				F(CODE_FILE_NAME())
#define CODE_LINE_NUMBER_P()			F(CODE_LINE_NUMBER())
#define CODE_FUNCTION_NAME_P()			F(CODE_FUNCTION_NAME())
#define CODE_FUNCTION_SIGNATURE_P()		F(CODE_FUNCTION_SIGNATURE())

#define VAR_NAME_VALUE(var)				#var " = " EXPAND_STR(var)
#define PRINT_VAR(var)					PRAGMA_MACRO(message(#var " = " EXPAND_STR(var)))

#define PRINT_COMPILE_CONST(var)											\
	std::overflow<TYPEOF(var), var> _PRINT_COMPILE_CONST_##var;				\
	TYPEOF(var) __PRINT_COMPILE_CONST_##var = _PRINT_COMPILE_CONST_##var()


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
using std::forward;

#define IDENTITY(T)						identity_t<T>

#define CONST_TYPE(T)					add_const_t<T>
#define CONST_TYPEOF(var)				CONST_TYPE(TYPEOF(var))

#define UNCONST_TYPE(T)					remove_const_t<T>
#define UNCONST_TYPEOF(var)				UNCONST_TYPE(TYPEOF(var))

#define VOLATILE_TYPE(T)				add_volatile_t<T>
#define UNVOLATILE_TYPE(T)				remove_volatile_t<T>

#define CV_TYPE(T)						add_cv_t<T>
#define CV_TYPEOF(var)					CV_TYPE(TYPEOF(var))

#define UNCV_TYPE(T)					remove_cv_t<T>
#define UNCV_TYPEOF(var)				UNCV_TYPE(TYPEOF(var))

#define ONLY_CONST_TYPE(T)				CONST_TYPE(UNVOLATILE_TYPE(T))
#define ONLY_CONST_TYPEOF(var)			ONLY_CONST_TYPE(TYPEOF(var))

#define ONLY_VOLATILE_TYPE(T)			VOLATILE_TYPE(UNCONST_TYPE(T))
#define ONLY_VOLATILE_TYPEOF(var)		ONLY_VOLATILE_TYPE(TYPEOF(var))

#define POINTER_TYPE(T)					add_pointer_t<T, FALSE>
#define ONLY_VOLATILE_TYPEOF(var)		ONLY_VOLATILE_TYPE(TYPEOF(var))

#define UNPOINTER_TYPE(T)				remove_pointer_t<T>
#define UNPOINTER_TYPEOF(var)			UNPOINTER_TYPE(TYPEOF(var))

#define RVALUE_TYPE(T)					add_rvalue_ref_t<T>
#define RVALUE_TYPEOF(var)				RVALUE_TYPE(TYPEOF(var))

#define UNRVALUE_TYPE(T)				remove_rvalue_ref_t<T>
#define UNRVALUE_TYPEOF(var)			UNRVALUE_TYPE(TYPEOF(var))

#define REFERENCE_TYPE(T)				add_pointer_t<T>
#define REFERENCE_TYPEOF(var)			REFERENCE_TYPE(TYPEOF(var))

#define UNREFERENCE_TYPE(T)				remove_pointer_t<T>
#define UNREFERENCE_TYPEOF(var)			UNREFERENCE_TYPE(TYPEOF(var))

#define UNSIGNED_TYPE(T)				make_unsigned_t<T>
#define UNSIGNED_TYPEOF(var)			UNSIGNED_TYPE(TYPEOF(var))

#define SIGNED_TYPE(T)					make_signed_t<T>
#define SIGNED_TYPEOF(var)				SIGNED_TYPE(TYPEOF(var))

#define MAKE_UNSIGNED(var)				static_cast<UNSIGNED_TYPEOF(var)>(var)
#define MAKE_SIGNED(var)				static_cast<SIGNED_TYPEOF(var)>(var)

#define ENABLE_IF(condition, T)			enable_if_t<condition, T>
#define TYPE_IF(condition, T, F)		conditional_t<condition, T, F>

#define CAPACITY(var)					extent<TYPEOF(var)>::value

#define FORWARD(T, arg)					forward<T>(arg)


/* CASTING MACROS */

#define MAKE_CONST(var)				const_cast<ONLY_CONST_TYPEOF(var)>(var)
#define MAKE_CONST_2D(var)			((ONLY_CONST_TYPEOF((var)[0][0])(*)[CAPACITY((var)[0])])(var))
#define MAKE_CONST_PP(var)			((ONLY_CONST_TYPE(UNPOINTER_TYPE(UNPOINTER_TYPE(TYPEOF(var)))) **)(var))

#define FORCE_CONST(var)			(*const_cast<ONLY_CONST_TYPEOF(var) *>(&(var)))
#define FORCE_UNCONST(var)			(*const_cast<UNCONST_TYPEOF(var) *>(&(var)))
#define MAKE_UNCONST(var)			FORCE_UNCONST(var)
#define UNCONST(var)				MAKE_UNCONST(var)

#define UNION_CAST(var, to_type)	(((UNION {TYPEOF(var) from; to_type to;})(var)).to)


/* TYPE INFO MACROS */

#define TO_UNSIGNED_TYPE_OF_SIZE(var, size)		\
	((size == 1) ? BYTE(var) : (size == 2) ? WORD(var) : (size == 4) ? DWORD(var) : QWORD(var))
#define TO_SIGNED_TYPE_OF_SIZE(var, size)		MAKE_SIGNED(TO_UNSIGNED_TYPE_OF_SIZE(var, size))

#define BYTE_SIZE(T)				SIZEOF(T)
#define BYTE_SIZEOF(var)			BYTE_SIZE(TYPEOF(var))

#define BIT_SIZE(T)					static_cast<SIZE>(SIZEOF(T) * BITS_PER_BYTE)
#define BIT_SIZEOF(var)				BIT_SIZE(TYPEOF(var))

#define countof(var)				(SIZEOF(var) / SIZEOF(0[var]))
#define COUNTOF(var)				countof(var)

#define IS_SIGNED(T)				(T(~T(0)) < 0)
#define IS_UNSIGNED(T)				!IS_SIGNED(T)

#define MAX_UNSIGNED_VALUE(T)		((T)(T(0) - 0b1))
#define MAX_UNSIGNED_VALUE_OF(var)	MAX_UNSIGNED_VALUE(TYPEOF(var))

#define MAX_BYTE					MAX_UNSIGNED_VALUE(BYTE)
#define MAX_WORD					MAX_UNSIGNED_VALUE(WORD)
#define MAX_DWORD					MAX_UNSIGNED_VALUE(DWORD)
#define MAX_QWORD					MAX_UNSIGNED_VALUE(QWORD)

#define MAX_SIGNED_VALUE(T)			((T)(MAX_UNSIGNED_VALUE(UNSIGNED_TYPE(T)) / 2))
#define MAX_SIGNED(T)				MAX_SIGNED_VALUE(T)

#define MAX_CHAR					MAX_SIGNED(CHAR)
#define MAX_SHORT					MAX_SIGNED(SHORT)
#define MAX_LONG					MAX_SIGNED(LONG)
#define MAX_LONGLONG				MAX_SIGNED(LONGLONG)

#define MAX_VALUE(T)				(IS_SIGNED(T) ? MAX_UNSIGNED_VALUE(T) : MAX_SIGNED_VALUE(T))
#define MAX_VALUE_OF(var)			MAX_VALUE(TYPEOF(var))
#define MAXOF(var)					MAX_VALUE_OF(var)

#define VALUE_RANGE(T)				(static_cast<DWORD>(BIT_SIZE(T)) * static_cast<DWORD>(BIT_SIZE(T)))
#define RANGE(T)					VALUE_RANGE(T)
#define VALUE_RANGE_OF(var)			VALUE_RANGE(TYPEOF(var))
#define RANGEOF(var)				VALUE_RANGE_OF(var)

#define T_SIZE						SIZEOF(T)
#define T_RANGE						RANGE(T)
#define T_MAX						MAX_VALUE(T)


/* FLASH DATA ADDRESSING MACROS */

#ifndef F
	class __FlashStringHelper;
	#define F(string_literal)					(reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))
#endif

#define FLASH_STRING_ADDRESS(string_addr)		((PCCHAR)(string_addr))
#define CSTR_P(string_addr)						FLASH_STRING_ADDRESS(string_addr)
#define FSTR(string_addr)						FLASH_STRING_ADDRESS(string_addr)

#define FLASH_FUNCTION_VARIATION(func)			EXPAND_CONCAT(func, _P)
#define FLASH_FUNC(func)						FLASH_FUNCTION_VARIATION(func)
#define PASS_FLASH_STRING(func, flash_string)	(FLASH_FUNCTION_VARIATION(func)(F(EXPAND_STR(flash_string))))
#define CALL_FLASH_FUNC(func, flash_string)		PASS_FLASH_STRING(func, flash_string)


/* MISCELLANEOUS GENERAL PURPOSE MACROS */

#define ever		(;;)
#define forever		for ever

#define FORCE_ANONYMOUS_CONSTRUCTION(constructor_expr)	(constructor_expr)
#define _CONSTRUCT(constructor_expr)					FORCE_ANONYMOUS_CONSTRUCTION(constructor_expr)


/* MISCELLANEOUS AVR-SPECIFIC MACROS */

#define SOFT_RESET()			\
	do							\
	{							\
		wdt_enable(WDTO_15MS);	\
		for (;;)				\
		{						\
		}						\
	} while(0)					\


/* PLACEMENT NEW IMPLEMENTATION */

#if !defined(ARDUINO) || ARDUINO < 20000 // NOTE: Assume Arduino 2.0+ will define placement new??

INLINE PTR operator new(SIZE size, PTR ptr)
{
	return ptr;
}

INLINE PTR operator new[](SIZE size, PTR ptr)
{
	return ptr;
}

#endif	// if !defined(ARDUINO). || ARDUINO < 20000

#endif
