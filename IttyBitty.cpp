/**********************************************************************************************
* This file is part of the Itty Bitty Arduino library.                                        *
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.            *
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS. *
***********************************************************************************************/

#ifndef __AVR__
	#define _ITTYBITTY_		"OH NO! ; ("	// NOTE: AVR architecture compatibility only!
#endif

#ifndef _ITTYBITTY_
#define _ITTYBITTY_			"FTW"


// Disable modules depending on the Arduino framework
#ifndef ARDUINO
	#define NO_ITTYBITTY_PRINT
	#define NO_ITTYBITTY_INFO
	#define NO_ITTYBITTY_STORAGE_ADAPTER_SD
	#define NO_ITTYBITTY_EEPROM_I2C
	#define NO_ITTYBITTY_LCD_I2C
	#define NO_ITTYBITTY_UI_NAV_ADAPTERS
	#define NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
#endif


// Slim build of library
#ifdef ITTYBITTY_SLIM
	#define NO_ITTYBITTY_PRINT
	#define NO_ITTYBITTY_BYTES
	#define NO_ITTYBITTY_INFO
	#define NO_ITTYBITTY_LED
	#define NO_ITTYBITTY_VALUES
#endif


// Basic build of library
#ifdef ITTYBITTY_BASE

	#ifndef NO_ITTYBITTY_BYTES
		#define NO_ITTYBITTY_FULL_BYTES
	#endif

	#define NO_ITTYBITTY_STORAGE
	#define NO_ITTYBITTY_EEPROM_I2C
	#define NO_ITTYBITTY_DB
	#define NO_ITTYBITTY_LCD_I2C
	#define NO_ITTYBITTY_MENUI

#endif


// GPIO Module

#ifdef NO_ITTYBITTY_GPIO
	#define NO_ITTYBITTY_LED
#endif


// For Params & Fields; used by Messages, DB, & Settings modules

#ifdef NO_ITTYBITTY_VALUES
	#define NO_ITTYBITTY_DATUM
#endif

#ifdef NO_ITTYBITTY_DATUM
	#define NO_ITTYBITTY_PARAMS
	#define NO_ITTYBITTY_FIELDS
#endif


// MESSAGES Module

#ifdef NO_ITTYBITTY_PARAMS
	#define NO_ITTYBITTY_MESSAGES
#endif


// STORAGE Module

#ifdef NO_ITTYBITTY_STORAGE
	#define NO_ITTYBITTY_STORAGE_ADAPTERS
#endif

#ifdef NO_ITTYBITTY_STORAGE_ADAPTERS
	#define NO_ITTYBITTY_STORAGE_ADAPTER_SD
#endif

#ifdef NO_ITTYBITTY_SD
	#define NO_ITTYBITTY_STORAGE_ADAPTER_SD
#endif


// EEPROM I2C Module

#ifdef NO_ITTYBITTY_EEPROM
	#define NO_ITTYBITTY_EEPROM_I2C
#endif


// DB (Database) Module

#ifdef NO_ITTYBITTY_STORAGE
	#define NO_ITTYBITTY_DB_TABLE_DEFS
#endif

#ifdef NO_ITTYBITTY_DB_TABLE_DEFS
	#define NO_ITTYBITTY_DB_TABLES
#endif

#ifdef NO_ITTYBITTY_DB_TABLES
	#define NO_ITTYBITTY_DB
#endif


// LCD I2C Module

#ifdef NO_ITTYBITTY_LCD
	#define NO_ITTYBITTY_LCD_I2C
#endif

#ifdef NO_ITTYBITTY_LCD_I2C
	#define NO_ITTYBITTY_LCD_CHARS
	#define NO_ITTYBITTY_LCD_EXTENSIONS
	#define NO_ITTYBITTY_LCD_BIG
#elif defined(NO_ITTYBITTY_LCD_CHARS)
	#define NO_ITTYBITTY_LCD_EXTENSIONS
#endif


// MENUI Module

#ifdef NO_ITTYBITTY_MENUI
	#define NO_ITTYBITTY_UI_NAV_ADAPTERS
	#define NO_ITTYBITTY_UI_DISPLAY_ADAPTERS
#endif

#endif
