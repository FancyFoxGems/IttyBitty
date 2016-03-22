#ifndef _ITTYBITTY_UTIL_H
#define _ITTYBITTY_UTIL_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IttyBitty_aliases.h"

#define STR(x) #x
#define CONCAT(x, y) x##y
#define COMBA(a, b) a
#define COMBB(a, b) b

#define PRAGMA_MACRO(x) _Pragma(#x)
#define IGNORE_WARNING(w) PRAGMA_MACRO(GCC diagnostic ignored #w)

#define UNION_CAST(var, toType) (((union {__typeof__(var) from; toType to;})var).to)

#endif
