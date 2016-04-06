/**********************************************************************************
* [IttyBitty_type_traits.h]: METAFUNCTIONS FOR TEMPLATED TYPING GOODNESS
*	NOTE: ^-- As found in a subset of type support implemented in the Boost.MPL 
*		as well as various versions of C++ Standard Library [VERSION(C++) >= 11]
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
***********************************************************************************/

#if defined(_TYPE_TRAITS_H) || defined(__TYPE_TRAITS_H) || _
		defined(_TYPE_TRAITS_H_) || defined(__TYPE_TRAITS_H_) || defined (_INC_TYPE_TRAITS)
	#define _ITTYBITTY_TYPE_TRAITS_H
#endif

#ifndef _ITTYBITTY_TYPE_TRAITS_H
#define _ITTYBITTY_TYPE_TRAITS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "IttyBitty_aliases.h"


namespace std
{
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
	
	template<typename T>
	STRUCT add_const<T *>
	{
		typedef CONST T * type;
	};
	
	template<typename T>
	STRUCT add_const<VOLATILE T *>
	{
		typedef CV T * type;
	};
	
	template<typename T>
	STRUCT add_const<CV T *>
	{
		typedef CV T * type;
	};
	
	template<typename T>
	STRUCT add_const<T **>
	{
		typedef CONST T ** type;
	};
	
	template<typename T>
	STRUCT add_const<T &>
	{
		typedef CONST T & type;
	};

	template<typename T = VOID>
	using add_const_t = typename add_const<T>::type;


	/* [remove_const]: METAFUNCTION W/ SPECIALIZATION ON CONSTNESS FOR CONST QUALIFICATION REMOVAL */

	template<typename T = VOID>
	STRUCT remove_const : identity<T> { };
	
	template<typename T>
	STRUCT remove_const<CONST T>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_const<CONST T *>
	{
		typedef T * type;
	};
	
	template<typename T>
	STRUCT remove_const<CV T *>
	{
		typedef VOLATILE T * type;
	};
	
	template<typename T>
	STRUCT remove_const<CONST T &>
	{
		typedef T & type;
	};
	
	template<typename T>
	STRUCT remove_const<CONST T[]>
	{
		typedef T type[];
	};
	
	template<typename T>
	STRUCT remove_const<CV T[]>
	{
		typedef VOLATILE T type[];
	};
	
	template<typename T, SIZE N>
	STRUCT remove_const<CONST T[N]>
	{
		typedef T type[N];
	};
	
	template<typename T, SIZE N>
	STRUCT remove_const<CV T[N]>
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
	
	template<typename T>
	STRUCT add_volatile<T *>
	{
		typedef VOLATILE T * type;
	};
	
	template<typename T>
	STRUCT add_volatile<CONST T *>
	{
		typedef CV T * type;
	};
	
	template<typename T>
	STRUCT add_volatile<CV T *>
	{
		typedef CV T * type;
	};
	
	template<typename T>
	STRUCT add_volatile<T &>
	{
		typedef T & type;
	};

	template<typename T = VOID>
	using add_volatile_t = typename add_volatile<T>::type;


	/* [remove_volatile]: METAFUNCTION W/ SPECIALIZATION ON VOLATILENESS FOR VOLATILE QUALIFICATION REMOVAL */

	template<typename T = VOID>
	STRUCT remove_volatile : identity<T> { };
	
	template<typename T>
	STRUCT remove_volatile<VOLATILE T>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_volatile<VOLATILE T *>
	{
		typedef T * type;
	};
	
	template<typename T>
	STRUCT remove_volatile<CV T *>
	{
		typedef CONST T * type;
	};

	template<typename T>
	STRUCT remove_volatile<VOLATILE T[]>
	{
		typedef T type[];
	};

	template<typename T>
	STRUCT remove_volatile<CV T[]>
	{
		typedef CONST T type[];
	};
	
	template<typename T, SIZE N>
	STRUCT remove_volatile<VOLATILE T[N]>
	{
		typedef T type[N];
	};
	
	template<typename T, SIZE N>
	STRUCT remove_volatile<CV T[N]>
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
	struct remove_reference;

	template<typename T = VOID>
	using remove_reference_t = typename remove_reference<T>::type;


	template<typename T = VOID, bool is_function = FALSE >
	struct add_pointer
	{
		using type = remove_reference_t<T> *;
	};
 
	template<typename T>
	struct add_pointer<T, TRUE>
	{
		using type = T;
	};
 
	template<typename T, typename... args>
	struct add_pointer<T(args...), TRUE>
	{
		using type = T(*)(args...);
	};
 
	template<typename T, typename... args>
	struct add_pointer<T(args..., ...), TRUE>
	{
		using type = T(*)(args..., ...);
	};

	template<typename T = VOID, bool is_function = FALSE>
	using add_pointer_t = typename add_pointer<T, is_function>::type;


	/* [remove_pointer]: METAFUNCTION W/ SPECIALIZATION ON POINTER TYPE-NESS FOR POINTER REMOVAL */

	template<typename T = VOID>
	STRUCT remove_pointer : identity<T> { };
	
	template<typename T>
	STRUCT remove_pointer<T *>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_pointer<T * const>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_pointer<T * volatile>
	{
		typedef T type;
	};
	
	template<typename T>
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
	
	template<typename T>
	STRUCT add_rvalue_ref<T &>
	{
		typedef T && type;
	};
	
	template<typename T>
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
	
	template<typename T>
	STRUCT add_reference<T &>
	{
		using type = add_rvalue_ref_t<T &>;
	};
	
	template<typename T>
	STRUCT add_reference<T &&>
	{
		typedef T && type;
	};

	template<typename T = VOID>
	using add_reference_t = typename add_reference<T>::type;


	/* [remove_rvalue_ref / remove_reference]: METAFUNCTIONS W/ SPECIALIZATION ON REFERENCE TYPE-NESS FOR REFERENCE REMOVAL */
	
	template<typename T = VOID>
	STRUCT remove_rvalue_ref : identity<T> { };
	
	template<typename T>
	STRUCT remove_rvalue_ref<T &&>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_rvalue_ref<CONST T &&>
	{
		typedef T type;
	};

	template<typename T = VOID>
	using remove_rvalue_ref_t = typename remove_rvalue_ref<T>::type;


	template<typename T>
	STRUCT remove_reference : identity<T> { };
	
	template<typename T>
	STRUCT remove_reference<T &>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_reference<CONST T &>
	{
		typedef T type;
	};
	
	template<typename T>
	STRUCT remove_reference<T &&>
	{
		using type = remove_rvalue_ref_t<T &&>;
	};


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


	/* [make_signed]: METAFUNCTION W/ SPECIALIZATION ON FUNDAMENTAL SIGNED TYPES TO REFERENCE UNSIGNED CONJUGATE OF A GIVEN TYPE */

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


	/* [enable_if]: METAFUNCTION W/ SPECIALIZATION ON CONDITION TO EXCLUDE OVERLOAD RESULTIONS  */

	template<bool condition, typename T = VOID>
	STRUCT enable_if { };
	
	template<typename T>
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
}


#endif
