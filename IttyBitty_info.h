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
#include <avr/pgmspace.h>


#pragma region DEFINES

#define ROM_USED_DETECTION_TOLERANCE_DWORDS	4

#define BOOTSZ0 _BV(1)
#define BOOTSZ1 _BV(2)

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
#pragma region GENERAL CPU & ARDUINO INFO GLOBAL FUNCTION DECLARATIONS

	CONSTEXPR PCCHAR CPUType();

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

	CONSTEXPR CWORD SramTotalSize();
	CWORD SramUsed();
	CWORD SramFree();

	CONSTEXPR WORD XramTotalSize();
	CWORD XramUsed();
	CWORD XramFree();

	CONSTEXPR CWORD TotalRamSize();
	CWORD TotalRamUsed();
	CWORD TotalRamFree();

	EXTERN CWORD (*MemorySize)();
	EXTERN CWORD (*MemoryUsed)();
	EXTERN CWORD (*MemoryFree)();

#pragma endregion


#pragma region ROM (EEPROM/FLASH ROM) INFO GLOBAL FUNCTION DECLARATIONS

	template<typename T = WORD, typename P = T>
	CONST T DetectRomUsed(DWORD (&rom_read_dword)(P), CWORD romSize)
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

	CONSTEXPR CDWORD EepromTotalSize();
	CDWORD EepromUsed();
	CDWORD EepromFree();

	CONSTEXPR CWORD FlashRomTotalSize();
	CWORD FlashRomUsed();
	CWORD FlashRomFree();

	EXTERN CWORD (*ProgMemTotalSize)();
	EXTERN CWORD (*ProgMemUsed)();
	EXTERN CWORD (*ProgMemFree)();

#pragma endregion


#pragma region BOOTLOADER/SKETCH SPACE INFO GLOBAL FUNCTION DECLARATIONS

	CWORD BootloaderAllocatedSize();

	EXTERN CWORD (*BootloaderSize)();

	CWORD SketchSpaceTotalSize();
	CWORD SketchSpaceUsed();
	CWORD SketchSpaceFree();

	EXTERN CWORD (*SketchSize)();

#pragma endregion
}


#endif
