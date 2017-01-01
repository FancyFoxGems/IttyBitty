/***********************************************************************************************
* [IttyBitty_type_traits.h]: METAFUNCTIONS FOR TEMPLATED TYPING GOODNESS
*	NOTE: ^-- As found in a subset of type support implemented in the Boost.MPL
*		as well as various versions of C++ Standard Library [VERSION(C++) >= 11]
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#if defined(_TYPE_TRAITS_H) || defined(__TYPE_TRAITS_H) || _
		defined(_TYPE_TRAITS_H_) || defined(__TYPE_TRAITS_H_) || defined (_INC_TYPE_TRAITS)
	#define _ITTYBITTY_TYPE_TRAITS_H
#endif

#ifndef _ITTYBITTY_TYPE_TRAITS_H
#define _ITTYBITTY_TYPE_TRAITS_H


#include "IttyBitty_aliases.h"


/* TEMPLATE MACROS */

#define DEFAULT_T_CLAUSE	<typename T>
#define DEFAULT_T_ARGS		<T>


/* TYPE TRAIT MACROS */

#define IS_ABSTRACT(type)					__is_abstract(type)
#define IS_BASE_OF(base_type, type)			__is_base_of (base_type, type)
#define IS_CLASS(type)						__is_class(type)
#define IS_EMPTY(type)						__is_empty(type)
#define IS_ENUM(type)						__is_enum(type)
#define IS_LITERAL_TYPE(type)				__is_literal_type(type)
#define IS_POD(type)						__is_pod(type)
#define IS_POLYMORPHIC(type)				__is_polymorphic(type)
#define IS_STANDARD_LAYOUT(type)			__is_standard_layout(type)
#define IS_TRIVIAL(type)					__is_trivial(type)
#define IS_UNION(type)						__is_union(type)

#define ENUM_UNDERLYING_TYPE(type)			__underlying_type(type)

#define HAS_NOTHROW_ASSIGNMENT(type)		__has_nothrow_assign(type)
#define HAS_NOTHROW_COPY(type)				__has_nothrow_copy(type)
#define HAS_NOTHROW_CONSTRUCTOR(type)		__has_nothrow_constructor(type)
#define HAS_TRIVIAL_ASSIGNMENT(type)		__has_trivial_assign(type)
#define HAS_TRIVIAL_COPY(type)				__has_trivial_copy(type)
#define HAS_TRIVIAL_CONSTRUCTOR(type)		__has_trivial_constructor(type)
#define HAS_TRIVIAL_DESTRUCTOR(type)		__has_trivial_destructor(type)
#define HAS_VIRTUAL_DESTRUCTOR(type)		__has_virtual_destructor(type)

#define TYPE_ARG_IS_SAME(T1, T2)			__is_same (T1, T2)


namespace std
{
	/* [overflow]: METAFUNCTION WHICH CAUSES A DATA OVERFLOW AT COMPILE-TIME  (Used to print constants at compile-time) */

	template<typename T, T N>
	STRUCT overflow
	{
		operator T() { return N + ((T)T(0) - 0b1) + 1; }

		operator char() { return 127 + 1; }

		char operator ()() { return N + ((T)T(0) - 0b1) + 1; }
	};


	/* [identity]: METAFUNCTION BASE WHICH ENCAPSULATES ITS OWN TEMPLATED TYPE */

	template<typename T = VOID>
	STRUCT identity
	{
		typedef T type;
	};

	template<typename T, SIZE N>
	STRUCT identity<T[N]>
	{
		typedef T type[N];
	};

	template<typename T = VOID>
	using identity_t = typename identity<T>::type;


	/* [add_const]: METAFUNCTION W/ SPECIALIZATION ON VALUE-NESS FOR CONST QUALIFICATION ADDITION */

	template<typename T = VOID>
	STRUCT add_const
	{
		typedef CONST T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_const<T *>
	{
		typedef CONST T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_const<VOLATILE T *>
	{
		typedef CONSTVOL T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_const<CONSTVOL T *>
	{
		typedef CONSTVOL T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_const<T **>
	{
		typedef CONST T ** type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_const<T &>
	{
		typedef CONST T & type;
	};

	template<typename T = VOID>
	using add_const_t = typename add_const<T>::type;


	/* [remove_const]: METAFUNCTION W/ SPECIALIZATION ON CONSTNESS FOR CONST QUALIFICATION REMOVAL */

	template<typename T = VOID>
	STRUCT remove_const : identity<T> { };

	template DEFAULT_T_CLAUSE
	STRUCT remove_const<CONST T>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_const<CONST T *>
	{
		typedef T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_const<CONSTVOL T *>
	{
		typedef VOLATILE T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_const<CONST T &>
	{
		typedef T & type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_const<CONST T[]>
	{
		typedef T type[];
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_const<CONSTVOL T[]>
	{
		typedef VOLATILE T type[];
	};

	template<typename T, SIZE N>
	STRUCT remove_const<CONST T[N]>
	{
		typedef T type[N];
	};

	template<typename T, SIZE N>
	STRUCT remove_const<CONSTVOL T[N]>
	{
		typedef VOLATILE T type[N];
	};

	template<typename T = VOID>
	using remove_const_t = typename remove_const<T>::type;


	/* [add_volatile]: METAFUNCTION W/ SPECIALIZATION ON VALUE-NESS FOR VOLATILE QUALIFICATION ADDITION */

	template<typename T = VOID>
	STRUCT add_volatile
	{
		typedef VOLATILE T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_volatile<T *>
	{
		typedef VOLATILE T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_volatile<CONST T *>
	{
		typedef CONSTVOL T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_volatile<CONSTVOL T *>
	{
		typedef CONSTVOL T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_volatile<T &>
	{
		typedef T & type;
	};

	template<typename T = VOID>
	using add_volatile_t = typename add_volatile<T>::type;


	/* [remove_volatile]: METAFUNCTION W/ SPECIALIZATION ON VOLATILENESS FOR VOLATILE QUALIFICATION REMOVAL */

	template<typename T = VOID>
	STRUCT remove_volatile : identity<T> { };

	template DEFAULT_T_CLAUSE
	STRUCT remove_volatile<VOLATILE T>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_volatile<VOLATILE T *>
	{
		typedef T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_volatile<CONSTVOL T *>
	{
		typedef CONST T * type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_volatile<VOLATILE T[]>
	{
		typedef T type[];
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_volatile<CONSTVOL T[]>
	{
		typedef CONST T type[];
	};

	template<typename T, SIZE N>
	STRUCT remove_volatile<VOLATILE T[N]>
	{
		typedef T type[N];
	};

	template<typename T, SIZE N>
	STRUCT remove_volatile<CONSTVOL T[N]>
	{
		typedef CONST T type[N];
	};

	template<typename T = VOID>
	using remove_volatile_t = typename remove_volatile<T>::type;


	/* [add_cv]: METAFUNCTION W/ SPECIALIZATION ON VALUE-NESS FOR CONST-VOLATILE QUALIFICATION ADDITION */

	template<typename T = VOID>
	STRUCT add_cv
	{
		typedef add_const_t<add_volatile_t<T>> type;
	};

	template<typename T = VOID>
	using add_cv_t = typename add_cv<T>::type;


	/* [remove_volatile]: METAFUNCTION W/ SPECIALIZATION ON VOLATILE-NESS FOR VOLATILE QUALIFICATION REMOVAL */

	template<typename T = VOID>
	STRUCT remove_cv
	{
		typedef remove_const_t<remove_volatile_t<T>> type;
	};

	template<typename T = VOID>
	using remove_cv_t = typename remove_cv<T>::type;


	/* [add_pointer]: METAFUNCTION W/ SPECIALIZATION ON POINTER TYPE-NESS FOR POINTER TYPE REFERENCE */

	template<typename T = VOID>
	STRUCT remove_reference;

	template<typename T = VOID>
	using remove_reference_t = typename remove_reference<T>::type;


	template<typename T = VOID, bool is_function = FALSE >
	STRUCT add_pointer
	{
		using type = remove_reference_t<T> *;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_pointer<T, TRUE>
	{
		using type = T;
	};

	template<typename T, typename... args>
	STRUCT add_pointer<T(args...), TRUE>
	{
		using type = T(*)(args...);
	};

	template<typename T, typename... args>
	STRUCT add_pointer<T(args..., ...), TRUE>
	{
		using type = T(*)(args..., ...);
	};

	template<typename T = VOID, bool is_function = FALSE>
	using add_pointer_t = typename add_pointer<T, is_function>::type;


	/* [remove_pointer]: METAFUNCTION W/ SPECIALIZATION ON POINTER TYPE-NESS FOR POINTER REMOVAL */

	template<typename T = VOID>
	STRUCT remove_pointer : identity<T> { };

	template DEFAULT_T_CLAUSE
	STRUCT remove_pointer<T *>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_pointer<T * const>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_pointer<T * volatile>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_pointer<T * cv>
	{
		typedef T type;
	};

	template<typename T = VOID>
	using remove_pointer_t = typename remove_pointer<T>::type;


	/* [add_rvalue_ref / add_reference]: METAFUNCTIONS W/ SPECIALIZATION ON REFERENCE TYPE-NESS FOR REFERENCE TYPE REFERENCE */

	template<typename T = VOID>
	STRUCT add_rvalue_ref
	{
		using type = remove_pointer_t<T> &&;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_rvalue_ref<T &>
	{
		typedef T && type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_rvalue_ref<T &&>
	{
		typedef T && type;
	};

	template<typename T = VOID>
	using add_rvalue_ref_t = typename add_rvalue_ref<T>::type;


	template<typename T = VOID>
	STRUCT add_reference
	{
		using type = remove_pointer_t<T> &;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_reference<T &>
	{
		using type = add_rvalue_ref_t<T &>;
	};

	template DEFAULT_T_CLAUSE
	STRUCT add_reference<T &&>
	{
		typedef T && type;
	};

	template<typename T = VOID>
	using add_reference_t = typename add_reference<T>::type;


	/* [remove_rvalue_ref / remove_reference]: METAFUNCTIONS W/ SPECIALIZATION ON REFERENCE TYPE-NESS FOR REFERENCE REMOVAL */

	template<typename T = VOID>
	STRUCT remove_rvalue_ref : identity<T> { };

	template DEFAULT_T_CLAUSE
	STRUCT remove_rvalue_ref<T &&>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_rvalue_ref<CONST T &&>
	{
		typedef T type;
	};

	template<typename T = VOID>
	using remove_rvalue_ref_t = typename remove_rvalue_ref<T>::type;


	template DEFAULT_T_CLAUSE
	STRUCT remove_reference : identity<T> { };

	template DEFAULT_T_CLAUSE
	STRUCT remove_reference<T &>
	{
		typedef T type;
	};

	template DEFAULT_T_CLAUSE
	STRUCT remove_reference<T &&>
	{
		using type = remove_rvalue_ref_t<T &&>;
	};


	/* [make_unsigned]: METAFUNCTION W/ SPECIALIZATION ON FUNDAMENTAL SIGNED TYPES TO REFERENCE UNSIGNED CONJUGATE OF A GIVEN TYPE */

	template<typename T = VOID>
	STRUCT make_unsigned : identity<T> { };

	template<>
	STRUCT make_unsigned<CHAR>
	{
		typedef BYTE type;
	};

	template<>
	STRUCT make_unsigned<SHORT>
	{
		typedef WORD type;
	};

	template<>
	STRUCT make_unsigned<LONG>
	{
		typedef DWORD type;
	};

	template<>
	STRUCT make_unsigned<LONGLONG>
	{
		typedef QWORD type;
	};

	template<>
	STRUCT make_unsigned<INT>
	{
		typedef UINT type;
	};

	template<typename T = VOID>
	using make_unsigned_t = typename make_unsigned<T>::type;


	/* [make_signed]: METAFUNCTION W/ SPECIALIZATION ON FUNDAMENTAL UNSIGNED TYPES TO REFERENCE SIGNED CONJUGATE OF A GIVEN TYPE */

	template<typename T = VOID>
	STRUCT make_signed : identity<T> { };

	template<>
	STRUCT make_signed<BYTE>
	{
		typedef CHAR type;
	};

	template<>
	STRUCT make_signed<WORD>
	{
		typedef SHORT type;
	};

	template<>
	STRUCT make_signed<DWORD>
	{
		typedef LONG type;
	};

	template<>
	STRUCT make_signed<QWORD>
	{
		typedef LONGLONG type;
	};

	template<>
	STRUCT make_signed<UINT>
	{
		typedef INT type;
	};

	template<typename T = VOID>
	using make_signed_t = typename make_signed<T>::type;


	/* [enable_if]: METAFUNCTION W/ SPECIALIZATION ON CONDITION TO EXCLUDE OVERLOAD RESULTIONS  */

	template<bool condition, typename T = VOID>
	STRUCT enable_if { };

	template DEFAULT_T_CLAUSE
	STRUCT enable_if<TRUE, T> : identity<T> { };

	template<bool condition, typename T = VOID>
	using enable_if_t = typename enable_if<condition, T>::type;


	/* [conditional]: METAFUNCTION W/ SPECIALIZATION ON CONDITION TO EXCLUDE OVERLOAD RESULTIONS  */

	template<bool condition, typename T = VOID, typename F = VOID>
	STRUCT conditional : identity<T> { };

	template<typename T, typename F>
	STRUCT conditional<FALSE, T, F> : identity<F> { };

	template<bool condition, typename T = VOID, typename F = VOID>
	using conditional_t = typename conditional<condition, T, F>::type;


	/* [extent]: METAFUNCTION */

	template<typename T, unsigned N = 0>
	STRUCT extent
	{
		STATIC CONSTEXPR T value = N;
	};

	template DEFAULT_T_CLAUSE
	STRUCT extent<T[], 0>
	{
		STATIC CONSTEXPR T value = 0;
	};

	template<typename T, unsigned N>
	STRUCT extent<T[], N>
	{
		STATIC CONSTEXPR T value = N - 1;
	};

	template<typename T, SIZE N>
	STRUCT extent<T[N], 0>
	{
		STATIC CONSTEXPR T value = N;
	};

	template<typename T, unsigned N, SIZE I>
	STRUCT extent<T[I], N>
	{
		STATIC CONSTEXPR T value = N - 1;
	};


	/* [forward]: METAFUNCTION FOR PERFECT FORWARDING */

	template DEFAULT_T_CLAUSE
	CONSTEXPR T && forward(typename remove_reference<T>::type & arg)
	{
		return static_cast<T &&>(arg);
	}

	template DEFAULT_T_CLAUSE
	CONSTEXPR T && forward(typename remove_reference<T>::type && arg)
	{
		return static_cast<T &&>(arg);
	}
};


#endif
