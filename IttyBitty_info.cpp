/***********************************************************************************************
* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#if defined(NO_ITTYBITTY_SLIM) && !defined(NO_ITTYBITTY_INFO)
	#define NO_ITTYBITTY_INFO
#endif

#ifndef NO_ITTYBITTY_INFO


#include "IttyBitty_info.h"

#ifdef ARDUINO
	#include "Arduino.h"
#endif

#ifndef _AVR_CPU_NAME_
	#include "avr_cpunames.h"
#endif

#include <avr/boot.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>


namespace IttyBitty
{
#pragma region GLOBAL VARIABLE DEFINITIONS

	BYTE _MCUSR;

#pragma endregion


#pragma region WATCHDOG TIMER GLOBAL FUNCTION DEFINITIONS

	VOID DisableWdt()
	{
		_MCUSR = MCUSR;
		MCUSR = 0;

		wdt_disable();
	}

	CRESETSOURCE GetResetSource()
	{
		if (_MCUSR > ResetSource::POWER_ON)
			_MCUSR &= ~0x1;

		return (CRESETSOURCE)_MCUSR;
	}

	VOID SetWdtInterval(CWDTINTERVAL wdtInterval)
	{
		wdt_enable(wdtInterval);
		WDR();
	}

#pragma endregion


#pragma region GENERAL CPU & ARDUINO INFO GLOBAL FUNCTION DEFINITIONS

	CONSTEXPR PCCHAR CPUType()
	{
		return _AVR_CPU_NAME_;
	}

#pragma endregion


#pragma region STACK/HEAP INFO GLOBAL FUNCTION DEFINITIONS

	// STACK SPACE FUNCTIONS

	PVUINT StackPointer()
	{
		return &static_cast<RVUINT>(SP);
	}

	CWORD StackSpaceTotal()
	{
		WORD stackEnd = reinterpret_cast<WORD>(__heap_end);

		if (stackEnd > RAMEND)
			stackEnd = static_cast<WORD>(__bss_end);

		return static_cast<CWORD>(RAMEND + 1 - stackEnd - __malloc_margin);
	}

	CWORD StackSpaceUsed()
	{
		return static_cast<CWORD>(RAMEND) + 1 - reinterpret_cast<CWORD>(StackPointer());
	}

	CWORD StackSpaceFree()
	{
		return StackSpaceTotal() - reinterpret_cast<WORD>(StackPointer());
	}


	// HEAP SPACE FUNCTIONS

	PCHAR HeapPointer()
	{
		if (reinterpret_cast<WORD>(__brkval) == 0)
			return __heap_start;

		return reinterpret_cast<PCHAR>(__brkval);
	}

	CWORD HeapSpaceTotal()
	{
		return reinterpret_cast<CWORD>(__heap_end) - reinterpret_cast<CWORD>(__heap_start);
	}

	CWORD HeapSpaceUsed()
	{
		return reinterpret_cast<CWORD>(HeapPointer()) - reinterpret_cast<CWORD>(__heap_start);
	}

	CWORD HeapSpaceFree()
	{
		return reinterpret_cast<CWORD>(__heap_end) - reinterpret_cast<CWORD>(HeapPointer());
	}

#pragma endregion


#pragma region RAM (SRAM & XRAM) INFO GLOBAL FUNCTION DEFINITIONS

	// SRAM FUNCTIONS

	CONSTEXPR CWORD SramTotalSize()
	{
		return static_cast<CWORD>(RAMEND) + 1 - static_cast<CWORD>(RAMSTART);
	}

	CWORD SramUsed()
	{
	#ifdef XRAMSTART

		if (reinterpret_cast<WORD>(__heap_start) > RAMEND)
			return StackSpaceUsed();

	#endif

		return StackSpaceUsed() + HeapSpaceUsed();
	}

	CWORD SramFree()
	{
	#ifdef XRAMSTART

		if (reinterpret_cast<WORD>(__heap_start) > RAMEND)
			return StackSpaceFree();

	#endif

		//return StackSpaceFree() + HeapSpaceFree();

		CWORD dummyWord = 0;
		return reinterpret_cast<CWORD>(&dummyWord) - (__brkval == 0 ? reinterpret_cast<CWORD>(&__heap_start) : reinterpret_cast<CWORD>(__brkval));
	}


	// XRAM  & TOTAL RAM FUNCTIONS

	CONSTEXPR WORD XramTotalSize()
	{
		return static_cast<CWORD>(XRAMSIZE);
	}

	#ifdef XRAMSTART

	WORD XramUsed()
	{
		WORD stackEnd = reinterpret_cast<WORD>(__heap_end);

		if (stackEnd > RAMEND)
			stackEnd = static_cast<WORD>(__bss_end);

		return static_cast<CWORD>(static_cast<WORD>(RAMEND) + 1 - stackEnd - __malloc_margin);
	}

	CWORD XramFree()
	{
		return XramTotalSize() - XramUsed();
	}

	CWORD TotalRamUsed()
	{
		return SramUsed() + XramUsed();
	}

	CWORD TotalRamFree()
	{
		return SramFree() + XramFree();
	}

	#else	// #ifndef XRAMSTART

	CWORD TotalRamUsed()
	{
		return SramUsed();
	}

	CWORD TotalRamFree()
	{
		return SramFree();
	}

	#endif	// #ifdef XRAMSTART

	CONSTEXPR CWORD TotalRamSize()
	{
		return SramTotalSize() + XramTotalSize();
	}


	// TOTAL RAM FUNCTION ALIASES

	CWORD (*MemorySize)() = TotalRamSize;
	CWORD (*MemoryUsed)() = &TotalRamUsed;
	CWORD (*MemoryFree)() = &TotalRamFree;

#pragma endregion



#pragma region ROM (EEPROM/FLASH ROM) INFO GLOBAL FUNCTION DEFINITIONS

	// EPPROM FUNCTIONS

	CONSTEXPR CDWORD EepromTotalSize()
	{
	#if E2END == 0
		return 0;
	#else
		return static_cast<CWORD>(E2END) + 1;
	#endif
	}

	CDWORD EepromUsed()
	{
	#if E2END == 0
		return 0;
	#else
		return DetectRomUsed<DWORD, PCDWORD>(eeprom_read_dword, EepromTotalSize());
	#endif
	}

	CDWORD EepromFree()
	{
	#if E2END == 0
		return 0;
	#else
		return EepromTotalSize() - EepromUsed();
	#endif
	}


	// (NAND) FLASH ROM FUNCTIONS

	CONSTEXPR CWORD FlashRomTotalSize()
	{
		return static_cast<CWORD>(FLASHEND) + 1;
	}

	//STATIC DWORD __pgm_read_dword(WORD dwordPtr)
	//{
	//	return pgm_read_dword(dwordPtr);
	//}

	CWORD FlashDetectRomUsed()
	{
		//return DetectRomUsed<>(__pgm_read_dword, FlashRomTotalSize());
		return BootloaderSize() + SketchSpaceUsed();
	}

	CWORD FlashRomFree()
	{
		return FlashRomTotalSize() - FlashDetectRomUsed();
	}


	// FLASH ROM FUNCTION ALIASES

	CWORD (*ProgMemTotalSize)() = &FlashRomTotalSize;
	CWORD (*ProgMemUsed)() = &FlashDetectRomUsed;
	CWORD (*ProgMemFree)() = &FlashRomFree;

#pragma endregion




#pragma region BOOTLOADER/SKETCH SPACE INFO GLOBAL FUNCTION DEFINITIONS

	// BOOTLOADER SPACE FUNCTIONS & ALIASES

	CWORD BootloaderAllocatedSize()
	{
		#ifndef SPM_PAGESIZE

			return 0;

		#else

			STATIC WORD BOOTLOADER_SIZE = 0;

		#if defined (__AVR_ATmega88__) || defined (__AVR_ATmega168__)
			#define BOOTSIZE_FACTOR_FUSE_BYTE	GET_EXTENDED_FUSE_BITS
			#define BOOTSIZE_FACTOR_FACTOR		5
		#else
			#define BOOTSIZE_FACTOR_FUSE_BYTE	GET_HIGH_FUSE_BITS
			#define BOOTSIZE_FACTOR_FACTOR		4
		#endif

			__fuse_byte_high_or_extended = boot_lock_fuse_bits_get(BOOTSIZE_FACTOR_FUSE_BYTE);
			STATIC BYTE bootSizeFactor = CHECK_BITS(__fuse_byte_high_or_extended, BOOTSZ1 OR BOOTSZ0) SHR 0b1;

			BOOTLOADER_SIZE = 2 ^ (BOOTSIZE_FACTOR_FACTOR - bootSizeFactor) * SPM_PAGESIZE;

			return static_cast<CWORD>(BOOTLOADER_SIZE);

		#endif
	}

	CWORD (*BootloaderSize)() = &BootloaderAllocatedSize;


	// SKETCH SPACE FUNCTIONS & ALIASES

	CWORD SketchSpaceTotalSize()
	{
		return FlashRomTotalSize() - BootloaderSize();
	}

	CWORD SketchSpaceUsed()
	{
		WORD textAndDataSize = reinterpret_cast<WORD>(&_etext) + reinterpret_cast<WORD>(&_edata);

		#ifndef SPM_PAGESIZE
			STATIC CONST CWORD FLASH_PAGE_SIZE = 0;
		#else
			STATIC CONST CWORD FLASH_PAGE_SIZE = SPM_PAGESIZE;
		#endif

		return static_cast<CWORD>(textAndDataSize) + FLASH_PAGE_SIZE;
	}

	CWORD SketchSpaceFree()
	{
		return SketchSpaceTotalSize() - SketchSpaceUsed();
	}

	CWORD (*SketchSize)() = &SketchSpaceUsed;

#pragma endregion
}

#endif	// #ifndef NO_ITTYBITTY_INFO
