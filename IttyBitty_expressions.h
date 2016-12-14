/***********************************************************************************************
* [IttyBitty_expressions.h]: TYPE-AGNOSTIC EXPRESSION FUNCTIONS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_EXPRESSIONS_H
#define _ITTYBITTY_EXPRESSIONS_H


#include "IttyBitty_util.h"

#include "stdarg.h"


#pragma region [Apply] EXPRESSION FUNCTION DEFINITIONS (Calls an objects method)

template<typename TInstance, typename ...TParams, typename ...TArgs>
INLINE VOID Apply(TInstance & instance, VOID (TInstance::*function)(TParams...), TArgs && ...args)
{
	(instance.*function)(FORWARD(TArgs, args)...);
}

template<typename TInstance, typename ...TParams, typename ...TArgs>
INLINE VOID PtrApply(TInstance * instance, VOID (TInstance::*function)(TParams...), TArgs && ...args)
{
	(instance->*function)(FORWARD(TArgs, args)...);
}

#pragma endregion


#pragma region [Call] EXPRESSION FUNCTION DEFINITIONS (Store result of member function call)

template<typename TInstance, typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID Call(TInstance & instance, TResult & result,
	TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	result = (instance.*function)(FORWARD(TArgs, args)...);
}

template<typename TInstance, typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID Call(TInstance & instance, TResult & result,
	TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	result = (instance.*function)(FORWARD(TArgs, args)...);
}

template<typename TInstance, typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID PtrCall(TInstance * instance, TResult & result,
	TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	result = (instance->*function)(FORWARD(TArgs, args)...);
}

template<typename TInstance, typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID PtrCall(TInstance * instance, TResult & result,
	TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	result = (instance->*function)(FORWARD(TArgs, args)...);
}

#pragma endregion


#pragma region [ApplyAll] EXPRESSION FUNCTION DEFINITIONS (Calls a method on a collection of objects)

template<typename TCount, typename TInstance, typename ...TParams, typename ...TArgs>
INLINE VOID ApplyAll(CONST TCount instanceCount, TInstance * instances,
	VOID (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
		(instances[i].*function)(FORWARD(TArgs, args)...);
}

template<typename TCount, typename TInstance, typename ...TParams, typename ...TArgs>
INLINE VOID PtrApplyAll(CONST TCount instanceCount, TInstance ** instances,
	VOID (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
		(instances[i]->*function)(FORWARD(TArgs, args)...);
}

#pragma endregion


#pragma region [CallAll] EXPRESSION FUNCTION DEFINITIONS (Store results of member function calls)

template<typename TCount, typename TInstance,
	typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID CallAll(CONST TCount instanceCount, TInstance * instances,
	UNCONST_TYPE(TResult) * results, TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
		results[i] = (instances[i].*function)(FORWARD(TArgs, args)...);
}

template<typename TCount, typename TInstance,
	typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID CallAll(CONST TCount instanceCount, TInstance * instances,
	UNCONST_TYPE(TResult) * results, TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
		results[i] = (instances[i].*function)(FORWARD(TArgs, args)...);
}

template<typename TCount, typename TInstance,
	typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID PtrCallAll(CONST TCount instanceCount, TInstance ** instances,
	UNCONST_TYPE(TResult) * results, TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
		results[i] = (instances[i]->*function)(FORWARD(TArgs, args)...);
}

template<typename TCount, typename TInstance,
	typename TResult, typename ...TParams, typename ...TArgs>
INLINE VOID PtrCallAll(CONST TCount instanceCount, TInstance ** instances,
	UNCONST_TYPE(TResult) * results, TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
		results[i] = (instances[i]->*function)(FORWARD(TArgs, args)...);
}

#pragma endregion


#pragma region [Any] EXPRESSION FUNCTION DEFINITIONS (TRUE if ANY call returns TRUE)

template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL Any(CONST TCount instanceCount, TInstance * instances,
	TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if ((instances[i].*function)(FORWARD(TArgs, args)...))
			return TRUE;
	}

	return FALSE;
}


template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL Any(CONST TCount instanceCount, TInstance * instances,
	TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if ((instances[i].*function)(FORWARD(TArgs, args)...))
			return TRUE;
	}

	return FALSE;
}

template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL PtrAny(CONST TCount instanceCount, TInstance ** instances,
	TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if ((instances[i]->*function)(FORWARD(TArgs, args)...))
			return TRUE;
	}

	return FALSE;
}

template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL PtrAny(CONST TCount instanceCount, TInstance ** instances,
	TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if ((instances[i]->*function)(FORWARD(TArgs, args)...))
			return TRUE;
	}

	return FALSE;
}

#pragma endregion


#pragma region [All] EXPRESSION FUNCTION DEFINITIONS (TRUE if ALL calls return TRUE)

template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL All(CONST TCount instanceCount, TInstance * instances,
	TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if (!(instances[i].*function)(FORWARD(TArgs, args)...))
			return FALSE;
	}

	return TRUE;
}


template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL All(CONST TCount instanceCount, TInstance * instances,
	TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if (!(instances[i].*function)(FORWARD(TArgs, args)...))
			return FALSE;
	}

	return TRUE;
}

template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL PtrAll(CONST TCount instanceCount, TInstance ** instances,
	TResult (TInstance::*function)(TParams...), TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if (!(instances[i]->*function)(FORWARD(TArgs, args)...))
			return FALSE;
	}

	return TRUE;
}

template<typename TCount, typename TInstance,
	typename TResult = CBOOL, typename ...TParams, typename ...TArgs>
INLINE CBOOL PtrAll(CONST TCount instanceCount, TInstance ** instances,
	TResult (TInstance::*function)(TParams...) const, TArgs && ...args)
{
	for (TCount i = 0; i < instanceCount; i++)
	{
		if (!(instances[i]->*function)(FORWARD(TArgs, args)...))
			return FALSE;
	}

	return TRUE;
}

#pragma endregion

#endif
