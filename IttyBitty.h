/************************************************************************************************
* Name:		Itty Bitty (Arduino Library)
* Created:	3/20/2016
* Author:	Tom Biuso <tjbtech@yahoo.com>
*
* Target Architecture:	Atmel AVR, especially ATmega series 8-bit MCUs
* Supported Platforms:	Arduino, AVR LibC, (AVR GCC)
*
* This file is the root, primary source code file for the Itty Bitty Arduino Library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
*
* Itty Bitty is free software: you can redistribute it and/or modify it under the terms of the
* GNU General Public License as published by the Free Software Foundation, either version 3 of
* the License, or (at your option) any later version.
*
* Itty Bitty is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* See the included GNU General Public License text for more details.
*
*************************************************************************************************
*
* [IttyBitty.h]
*
*	LIBRARY - FULL BUNDLE
*
*				Memory Usage:	~6.99 KB Program Memory (Flash ROM) / 815 B SRAM
*	w/NO_ITTYBITTY_FULL_BYTES:		~6.66 KB Program Memory (Flash ROM) / 659 B SRAM
*	NOTE: ^-- w/o full IttyBitty_bytes module
*
* INCLUDES:
*
* [IttyBitty_aliases.h]: TYPEDEFS FOR WIN32 API-STYLE TYPE REFERENCES
*
* [IttyBitty_type_traits.h]: METAFUNCTIONS FOR TEMPLATED TYPING GOODNESS
*	NOTE: ^-- As found in a subset of type support implemented in the Boost.MPL
*		as well as various versions of C++ Standard Library [VERSION(C++) >= 11]
*
* [IttyBitty_util.h]: MISCELLANEOUS HELPER MACROS, ETC.
*
* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS
*
* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE
*
* [IttyBitty_bits.h]: BIT-TWIDDLING MACROS FOR YOUR CODING PLEASURE
*	NOTE: ^-- The fastest method of register data manipulation for ATmegas
*
* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES (ONLY)
*	NOTE: ^-- Base bundle excludes data structures for larger blocks
*
* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY
*
* [IttyBitty_GPIO.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS
*
* [IttyBitty_values.h]: UNIVERSAL TYPE (TAGGED) UNIONS
*
* [IttyBitty_fields.h]: UNIVERSAL DATA STRUCTURES FOR STORING SETTINGS & MESSAGE FIELDS
*
* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC
*
* [IttyBitty_storage.h]: DATA PERSISTENCE TO NON-VOLATILE MEDIA
* [IttyBitty_storage_adapters.h]: LONG-TERM DATA STORAGE IMPLEMENTATIONS
*
* [IttyBitty_EEPROM_I2C.h]: EXTERNAL EEPROM CHIP SUPPORT
*	(i.e. Atmel AT24CXXX /  Microchip 24LCXXX Series)
*
* [IttyBitty_DB.h]: STRUCTURED DATA STORAGE SUPPORT
* [IttyBitty_DB_tables.h]: TABLE DATA STRUCTURES FOR STRUCTURED DATA STORAGE SUPPORT
* [IttyBitty_DB_table_defs.h]: HEADERS/TABLE DEFINITIONS FOR STRUCTURED DATA STORAGE SUPPORT
*
* [IttyBitty_LCD_I2C.h]: SUPPORT FOR DRIVING HD44780-COMPATIBLE LCD DISPLAYS VIA I2C EXPANDERS
* [IttyBitty_LCD_chars.h]: VALUE-ADDED SYMBOLS & ICONS FOR HD44780-COMPATIBLE LCD DISPLAYS
* [IttyBitty_LCD_extensions.h]: EXTENDED FUNCTIONALITY FOR I2C-DRIVEN HD44780-COMPATIBLE
* 	LCD DISPLAYS, SUCH AS CHARACTER MANIPULATION, SCROLL BARS, GRAPHS, AND SLIDERS
* [IttyBitty_LCD_big.h]: ADDED SUPPORT FOR LARGE (TWO-ROW, MULTI-COLUMN)
*	CHARACTER PRINTING ON I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS
*
*
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT.
************************************************************************************************/

#ifndef __AVR__
	#define _ITTYBITTY_H	"OH NO! ; ("	// NOTE: AVR architecture compatibility only!
#endif

#ifndef _ITTYBITTY_H
#define _ITTYBITTY_H		"FTW"


// Disable modules depending on the Arduino framework
#ifndef ARDUINO
	 #define NO_ITTYBITTY_INFO
	 #define NO_ITTYBITTY_STORAGE_ADAPTERS
	 #define NO_ITTYBITTY_EEPROM_I2C
	 #define NO_ITTYBITTY_LCD_I2C
	 #define NO_ITTYBITTY_PRINT
#endif


/* [IttyBitty_bytes.h]: DATA STRUCTURES FOR BIT-PACKING BYTES, WORDS, DWORDS, ... */

#ifndef NO_ITTYBITTY_BYTES
	#include "IttyBitty_bytes.h"
#else
	#include "IttyBitty_bits.h"			// Included by [IttyBitty_bytes.h] otherwise
#endif


//#include "IttyBitty_util.h"					// Included by [IttyBitty_bits.h]
//#include "IttyBitty_type_traits.h"			// Included by [IttyBitty_util.h]
//#include "IttyBitty_aliases.h"				// Included by [IttyBitty_type_traits.h]


/* [IttyBitty_print.h]: STREAM PRINTING UTILITY FUNCTIONS */

#ifndef NO_ITTYBITTY_PRINT
	#include "IttyBitty_print.h"
#endif


/* [IttyBitty_info.h]: UTILITY FUNCTIONS RELATED TO BOARD SPECS & MEMORY USAGE */

#ifndef NO_ITTYBITTY_INFO
	#include "IttyBitty_info.h"
	//#include "avr_cpunames.h"				// Included by [IttyBitty_info.h]
#endif


/* [IttyBitty_registers.h]: REGISTER ABSTRACTIONS FOR CONVENIENCE AND CLARITY */

#ifndef NO_ITTYBITTY_REGISTERS
	#include "IttyBitty_registers.h"
#endif


/* [IttyBitty_GPIO.h]: STRUCTURED BIT-MAPPING OF GENERAL-PURPOSE IO PORTS/PINS */

#ifndef NO_ITTYBITTY_GPIO
	#include "IttyBitty_GPIO.h"
#endif


/* [IttyBitty_interrupts.h]:  */

#ifndef NO_ITTYBITTY_INTERRUPTS
	#include "IttyBitty_interrupts.h"
#endif


/* [IttyBitty_timers.h]:  */

#ifndef NO_ITTYBITTY_TIMERS
	#include "IttyBitty_timers.h"
#endif


/* [IttyBitty_LED.h]: DATA TYPE FOR DEAD-EASY ON-BOARD & EXTERNAL LED BLINKING */

#ifdef NO_ITTYBITTY_GPIO
	#define NO_ITTYBITTY_LED
#endif

#ifndef NO_ITTYBITTY_LED

	#include "IttyBitty_LED.h"
	//#include "IttyBitty_gpio.h"				// Included by [IttyBitty_LED.h]

#else

	#ifndef NO_ITTYBITTY_GPIO
		#include "IttyBitty_gpio.h"
	#endif

#endif


// For Params & Fields; used by Messages, DB, & Settings modules

#ifdef NO_ITTYBITTY_VALUES
	#define NO_ITTYBITTY_DATUM
#endif

#ifdef NO_ITTYBITTY_DATUM
	#define NO_ITTYBITTY_PARAMS
	#define NO_ITTYBITTY_FIELDS
#endif


/* [IttyBitty_messages.h]: BASE SERIAL PROTOCOL DATA STRUCTURES & PARSING LOGIC */

#ifdef NO_ITTYBITTY_PARAMS
	#define NO_ITTYBITTY_MESSAGES
#endif

#ifndef NO_ITTYBITTY_MESSAGES

	#include "IttyBitty_messages.h"

	//#include "IttyBitty_params.h"			// Included by [IttyBitty_messages.h]
	//#include "IttyBitty_datum.h"			// Included by [IttyBitty_params.h]
	//#include "IttyBitty_values.h"			// Included by [IttyBitty_datum.h]

#else

	#define NO_ITTYBITTY_PARAMS

	#ifndef NO_ITTYBITTY_DATUM

		#include "IttyBitty_datum.h"

	#else

		#ifndef NO_ITTYBITTY_VALUES
			#include "IttyBitty_values.h"
		#endif

	#endif

#endif


/* [IttyBitty_storage.h]: DATA PERSISTENCE TO NON-VOLATILE MEDIA */

#ifndef NO_ITTYBITTY_STORAGE

	/* [IttyBitty_storage_adapters.h]: LONG-TERM DATA STORAGE IMPLEMENTATIONS */
	#ifndef NO_ITTYBITTY_STORAGE_ADAPTERS
		#include "IttyBitty_storage_adapters.h"
	#else
		#include "IttyBitty_storage.h"
	#endif

#endif


/* [IttyBitty_EEPROM_I2C.h]: EXTERNAL EEPROM CHIP SUPPORT (i.e. Atmel AT24CXXX /  Microchip 24LCXXX Series) */

#ifdef NO_ITTYBITTY_EEPROM
	#define NO_ITTYBITTY_EEPROM_I2C
#endif

#ifndef NO_ITTYBITTY_EEPROM_I2C
	#include "IttyBitty_EEPROM_I2C.h"
#endif


/* [IttyBitty_DB.h]: STRUCTURED DATA STORAGE SUPPORT */

#ifdef NO_ITTYBITTY_STORAGE
	#define NO_ITTYBITTY_DB_TABLE_DEFS
#endif

#ifdef NO_ITTYBITTY_DB_TABLE_DEFS
	#define NO_ITTYBITTY_DB_TABLES
#endif

#ifdef NO_ITTYBITTY_DB_TABLES
	#define NO_ITTYBITTY_DB
#endif

#ifndef NO_ITTYBITTY_DB

	#include "IttyBitty_DB.h"

	//#include "IttyBitty_DB_tables.h"			// Included by [IttyBitty_DB.h]
	//#include "IttyBitty_DB_table_defs.h"		// Included by [IttyBitty_DB_tables.h]
	//#include "IttyBitty_fields.h"			// Included by [IttyBitty_DB_table_defs.h]

#else

	#ifndef NO_ITTYBITTY_FIELDS
		#include "IttyBitty_fields.h"
	#endif

#endif



/* [IttyBitty_LCD_I2C.h]: SUPPORT FOR DRIVING HD44780-COMPATIBLE LCD DISPLAYS VIA I2C EXPANDERS */

#ifdef NO_ITTYBITTY_LCD
	#define NO_ITTYBITTY_LCD_I2C
#endif

#ifdef NO_ITTYBITTY_LCD_CHARS
	#define NO_ITTYBITTY_LCD_EXTENSIONS
#endif

#ifndef NO_ITTYBITTY_LCD_I2C

	#include "IttyBitty_LCD_I2C.h"

	/* [IttyBitty_LCD_chars.h]: VALUE-ADDED SYMBOLS & ICONS FOR HD44780-COMPATIBLE LCD DISPLAYS */

	#ifndef NO_ITTYBITTY_LCD_CHARS
		#include "IttyBitty_LCD_chars.h"
	#endif

	/* [IttyBitty_LCD_extensions.h]: EXTENDED FUNCTIONALITY FOR I2C-DRIVEN HD44780-COMPATIBLE
		LCD DISPLAYS, SUCH AS CHARACTER MANIPULATION, SCROLL BARS, GRAPHS, AND SLIDERS */

	#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
		#include "IttyBitty_LCD_extensions.h"
	#endif

	/* [IttyBitty_LCD_big.h]: ADDED SUPPORT FOR LARGE (TWO-ROW, MULTI-COLUMN)
		CHARACTER PRINTING ON I2C-DRIVEN HD44780-COMPATIBLE LCD DISPLAYS */

	#ifndef NO_ITTYBITTY_LCD_BIG
		#include "IttyBitty_LCD_big.h"
	#endif

#endif

#endif
