/***********************************************************************************************
* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#if defined(NO_ITTYBITTY_INFO) && !defined(_ITTYBITTY_INFO_H)
	#define _ITTYBITTY_INFO_H
#endif

#ifndef _ITTYBITTY_INFO_H
#define _ITTYBITTY_INFO_H


#include "IttyBitty_bits.h"

#ifdef ARDUINO
	#include "Arduino.h"
#endif

#ifndef _AVR_CPU_NAME_
	#include "avr_cpunames.h"
#endif

#include <avr/boot.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>


#pragma region DEFINES

#define ROM_USED_DETECTION_TOLERANCE_DWORDS	4

#define BOOTSZ0		_BV(1)
#define BOOTSZ1		_BV(2)

#pragma endregion


#pragma region MACROS

#define WDR()		ASM("wdr")

#pragma endregion

#pragma region MEMORY AREA/ALLOCATION VARIABLES (FROM AVR LibC & COMPILER, e.g. AVR-GCC)

EXTERN PCHAR __data_start;
EXTERN PCHAR __data_end;
EXTERN PCHAR __bss_start;
EXTERN INT __bss_end;		// NOTE: "INT" because SD Library says so..!
EXTERN PCHAR __heap_start;
EXTERN PCHAR __heap_end;

EXTERN PINT __brkval;

EXTERN PCHAR _etext;
EXTERN PCHAR _edata;

EXTERN SIZE __malloc_margin;
EXTERN PCHAR __malloc_heap_start;
EXTERN PCHAR __malloc_heap_end;

EXTERN BYTE __fuse_byte_high_or_extended;

#pragma endregion


namespace IttyBitty
{
#pragma region GLOBAL VARIABLE DECLARATIONS

	EXTERN BYTE _MCUSR NOINIT_VAR;

#pragma endregion


#pragma region ENUMS

	enum ResetSource : NYBBLE
	{
		POWER_ON		= 0x1,
		EXTERNAL_RESET	= 0x2,
		BROWN_OUT		= 0x4,
		WDT_TIMEOUT		= 0x8
	};

	DECLARE_ENUM_AS_FLAGS(ResetSource, RESETSOURCE);


	enum WdtInterval : BYTE
	{
		WDT_15MS	= WDTO_15MS,
		WDT_30MS	= WDTO_30MS,
		WDT_60MS	= WDTO_60MS,
		WDT_120MS	= WDTO_120MS,
		WDT_250MS	= WDTO_250MS,
		WDT_500MS	= WDTO_500MS,
		WDT_1S		= WDTO_1S,
		WDT_2S		= WDTO_2S,
		WDT_4S		= WDTO_4S,
		WDT_8S		= WDTO_8S
	};

	DECLARE_ENUM_AS_FLAGS(WdtInterval, WDTINTERVAL);

#pragma endregion


#pragma region WATCHDOG TIMER GLOBAL FUNCTION DECLARATIONS

	VOID DisableWdt() __attribute__((naked)) __attribute__((section(".init3")));
	CRESETSOURCE GetResetSource();
	VOID SetWdtInterval(CWDTINTERVAL);

#pragma endregion


#pragma region GENERAL CPU & ARDUINO INFO GLOBAL FUNCTION DECLARATIONS

	CONSTEXPR PCCHAR CPUType()
	{
		return _AVR_CPU_NAME_;
	}

#pragma endregion


#pragma region STACK/HEAP INFO GLOBAL FUNCTION DECLARATIONS

	PVUINT StackPointer();

	CWORD StackSpaceTotal();
	CWORD StackSpaceUsed();
	CWORD StackSpaceFree();


	PCHAR HeapPointer();

	CWORD HeapSpaceTotal();
	CWORD HeapSpaceUsed();
	CWORD HeapSpaceFree();

#pragma endregion


#pragma region RAM (SRAM & XRAM) INFO GLOBAL FUNCTION DECLARATIONS

	CONSTEXPR CWORD SramTotalSize()
	{
		return static_cast<CWORD>(RAMEND) + 1 - static_cast<CWORD>(RAMSTART);
	}

	CWORD SramUsed();
	CWORD SramFree();


	CONSTEXPR WORD XramTotalSize()
	{
		return static_cast<CWORD>(XRAMSIZE);
	}

	CWORD XramUsed();
	CWORD XramFree();


	CONSTEXPR CWORD TotalRamSize()
	{
		return SramTotalSize() + XramTotalSize();
	}

	CWORD TotalRamUsed();
	CWORD TotalRamFree();


	EXTERN CWORD (&MemorySize)();
	EXTERN CWORD (&MemoryUsed)();
	EXTERN CWORD (&MemoryFree)();

#pragma endregion


#pragma region ROM (EEPROM/FLASH ROM) INFO GLOBAL FUNCTION DECLARATIONS

	template<typename T = WORD, typename P = T>
	CONST T DetectRomUsed(DWORD (&rom_read_dword)(P), CONST T romSize)
	{
		T lastUsedAddr = 0x0;
		DWORD value = 0;
		BYTE consecutiveBlanks = 0;

		for (lastUsedAddr = 0x0; lastUsedAddr < romSize; lastUsedAddr++)
		{
			value = rom_read_dword(reinterpret_cast<P>(lastUsedAddr));

			if (value == 0xFFFFFFFF)
			{
				if (++consecutiveBlanks == ROM_USED_DETECTION_TOLERANCE_DWORDS)
					break;
			}
			else
			{
				consecutiveBlanks = 0;
			}
		}

		return static_cast<CONST T>(lastUsedAddr + 1);
	}


	CONSTEXPR CDWORD EepromTotalSize()
	{
	#if E2END == 0
		return 0;
	#else
		return static_cast<CWORD>(E2END) + 1;
	#endif
	}

	CDWORD EepromUsed();
	CDWORD EepromFree();


	CONSTEXPR CDWORD FlashRomTotalSize()
	{
		return static_cast<CDWORD>(FLASHEND) + 1;
	}

	CDWORD FlashRomUsed();
	CDWORD FlashRomFree();

	EXTERN CDWORD (&ProgMemTotalSize)();
	EXTERN CDWORD (&ProgMemUsed)();
	EXTERN CDWORD (&ProgMemFree)();

#pragma endregion


#pragma region BOOTLOADER/SKETCH SPACE INFO GLOBAL FUNCTION DECLARATIONS

	CDWORD BootloaderAllocatedSize();

	EXTERN CDWORD (&BootloaderSize)();


	CDWORD SketchSpaceTotalSize();
	CDWORD SketchSpaceUsed();
	CDWORD SketchSpaceFree();

	EXTERN CDWORD (&SketchSize)();

#pragma endregion
}


#endif
