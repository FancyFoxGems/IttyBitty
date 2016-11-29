/***********************************************************************************************
* [IttyBitty_LCD_I2C.h]: SUPPORT FOR DRIVING HD44780-COMPATIBLE LCD DISPLAYS VIA I2C EXPANDERS
*
* This file is part of the Itty Bitty Arduino library.
* Copyright © 2016 Thomas J. Biuso III  ALL RIGHTS RESERVED...WHATEVER THAT MEANS.
* RELEASED UNDER THE GPL v3.0 LICENSE; SEE <LICENSE> FILE WITHIN DISTRIBUTION ROOT FOR TERMS.
***********************************************************************************************/

#ifndef _ITTYBITTY_LCD_I2C_H
#define _ITTYBITTY_LCD_I2C_H


#include "IttyBitty_bits.h"

#ifndef NO_ITTYBITTY_LCD_CHARS
	#include "IttyBitty_LCD_chars.h"
#endif

#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
	#include "IttyBitty_LCD_extensions.h"
#endif

#ifndef NO_ITTYBITTY_LCD_BIG_EXTENSIONS
	#include "IttyBitty_LCD_extensions_big.h"
#endif

#include "Print.h"
#include "Wire.h"


#pragma region MACROS/ALIASES

#ifdef ARDUINO_SAM_DUE
	#define Wire		Wire1
#endif

#if ARDUINO >= 100
	#define WIRE_WRITE	Wire.write
#else
	#define WIRE_WRITE	Wire.send
#endif

#pragma endregion


#pragma region DEFINES

// LCD OPTIONS/CONSTANTS

#define LCD_DEFAULT_I2C_ADDRESS			0x27

#define LCD_DEFAULT_COLS				16
#define LCD_DEFAULT_ROWS				2

#define LCD_CHAR_HEIGHT					8
#define LCD_CHAR_WIDTH					5


// COMMAND BYTES

#define LCD_CMD_DISPLAY_CLEAR			0x01
#define LCD_CMD_CURSOR_HOME				0x02
#define LCD_CMD_ENTRY_MODE_SET			0x04
#define LCD_CMD_DISPLAY_CONTROL			0x08
#define LCD_CMD_SHIFT_CURSOR			0x10
#define LCD_CMD_FUNCTION_SET			0x20
#define LCD_CMD_SET_CGRAM_ADDR			0x40
#define LCD_CMD_SET_DDRAM_ADDR			0x80



// DISPLAY CONTROL BITS

#define LCD_CONTROL_CURSOR_BLINK		0x0
#define LCD_CONTROL_CURSOR				0x1
#define LCD_CONTROL_DISPLAY				0x2
#define LCD_CONTROL_BACKLIGHT			0x3


// ENTRY MODE FLAGS

#define LCD_ENTRY_CURSOR_SCROLL			0x0
#define LCD_ENTRY_LEFT_TO_RIGHT			0x1


// CURSOR/CONTENTS SHIFT TYPE/VALUE FLAGS

#define LCD_SHIFT_CURSOR				0x0
#define LCD_SHIFT_DISPLAY				0x8

#define LCD_SHIFT_LEFT					0x0
#define LCD_SHIFT_RIGHT					0x4


// MODE/OPTION FLAGS

#define LCD_DOTS_5x8					0x00
#define LCD_DOTS_5x10					0x04
#define LCD_ROWS_SINGLE					0x00
#define LCD_ROWS_MULTI					0x08
#define LCD_INTERFACE_DATA_4_BIT		0x00
#define LCD_INTERFACE_DATA_8_BIT		0x10


// I2C INTERFACE BIT-FLAGS

#define LCD_RS		0x0  // Register select
#define LCD_RW		0x1  // Read/write
#define LCD_EN		0x2  // Enable


// GROVE RGB LCD SUPPORT

#define LCD_RGB_DISPLAY_ADDRESS			0x3E
#define LCD_RGB_BACKLIGHT_ADDRESS		0xE2

#define LCD_RGB_COMMAND					0x80
#define LCD_RGB_DATA					0x40

#define LCD_RGB_REG_RED					0x4
#define LCD_RGB_REG_GREEN				0x3
#define LCD_RGB_REG_BLUE				0x2

#define LCD_RGB_REG_MODE_1				0x0
#define LCD_RGB_REG_MODE_2				0x1
#define LCD_RGB_REG_BLINK_LED_RATIO		0x6
#define LCD_RGB_REG_BLINK_LED_PERIOD	0x7
#define LCD_RGB_REG_OUTPUT				0x8

#define LCD_RGB_PWM_AND_GRPPWM			0xFF

#define LCD_BLINK_PERIOD_OFF			0x00
#define LCD_BLINK_PERIOD_QUARTER_S		0x05
#define LCD_BLINK_PERIOD_HALF_S			0x0B
#define LCD_BLINK_PERIOD_ONE_S			0x17
#define LCD_BLINK_PERIOD_TWO_S			0x2F

#define LCD_BLINK_RATIO_OFF				0xFF
#define LCD_BLINK_RATIO_QUARTER			0x3F
#define LCD_BLINK_RATIO_HALF			0x7F
#define LCD_BLINK_RATIO_THREE_QUARTERS	0xBF

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	#define LCDI2C_T_CLAUSE_DEF	<CBYTE Cols, CBYTE Rows, CBYTE I2CAddr>
	#define LCDI2C_T_CLAUSE		<CBYTE Cols = LCD_DEFAULT_COLS, CBYTE Rows = LCD_DEFAULT_ROWS, CBYTE I2CAddr = LCD_DEFAULT_I2C_ADDRESS>
	#define LCDI2C_T_ARGS		<Cols, Rows, I2CAddr>

	template LCDI2C_T_CLAUSE
	class LCD_I2C;
	TEMPLATE_CLASS_USING_ALIASES(CSL(LCDI2C_T_CLAUSE), CSL(LCDI2C_T_ARGS), LCD_I2C, LCDI2C);

#pragma endregion


#pragma region [LCD_I2C] DEFINITION

	template LCDI2C_T_CLAUSE_DEF
	class LCD_I2C : public Print
	{
	protected:

		// PROTECTED STATIC CONSTANT ARRAY FUNCTION

		STATIC PCBYTE LCD_ROW_OFFSETS()
		{
			STATIC CBYTE ROW_OFFSETS[4] = { 0x00, 0x40, 0x14, 0x54 };
			return ROW_OFFSETS;
		}


		// INSTANCE VARIABLES

		BYTE _CursorRow = 0;
		BYTE _CursorCol = 0;

		BOOL _BacklightOn = FALSE;

		BYTE _DisplayFunction = 0;
		BYTE _DisplayControl = 0;
		BYTE _EntryMode = 0;

		BOOL _IsGroveRgbLcd = FALSE;


		// HELPER FUNCTIONS

		VOID StrobeEnable(BYTE value)
		{
			WireWrite(SET_BIT(value, LCD_EN));
			delayMicroseconds(1);

			WireWrite(CLEAR_BIT(value, LCD_EN));
			delayMicroseconds(50);
		}

		VOID WireWrite(BYTE value)
		{
			Wire.beginTransmission(I2CAddr);

			if (_BacklightOn)
				SET_BIT(value, LCD_CONTROL_BACKLIGHT);

			WIRE_WRITE((INT)value);

			Wire.endTransmission();
		}

		VOID WriteNybble(BYTE value)
		{
			WireWrite(value);

			this->StrobeEnable(value);
		}

		VOID SendCommand(CBYTE data, CBOOL regSelect = FALSE)
		{
			if (_IsGroveRgbLcd)
			{
				this->WriteNybble(HIGH_NYBBLE(data) BOR(regSelect ? B(LCD_RS) : 0x0));
				this->WriteNybble((LOW_NYBBLE(data) SHL BITS_PER_NYBBLE) BOR(regSelect ? B(LCD_RS) : 0x0));
			}
			else
			{
				this->WriteNybble(HIGH_NYBBLE(data) BOR(regSelect ? B(LCD_RS) : 0x0));
				this->WriteNybble((LOW_NYBBLE(data) SHL BITS_PER_NYBBLE) BOR(regSelect ? B(LCD_RS) : 0x0));
			}
		}

		VOID SetDisplayFunction()
		{
			this->SendCommand(LCD_CMD_FUNCTION_SET | _DisplayFunction);
		}

		VOID SetDisplayControl()
		{
			this->SendCommand(LCD_CMD_DISPLAY_CONTROL | _DisplayControl);
		}

		VOID SetEntryMode()
		{
			this->SendCommand(LCD_CMD_ENTRY_MODE_SET | _EntryMode);
		}

		VOID SetBacklight()
		{
			this->WireWrite(0);
		}

		// GROVE RGB LCD HELPER FUNCTIONS

		VOID SendRgbLcdCommand(CBYTE data, CBYTE mode = 0)
		{
			this->WriteNybble(HIGH_NYBBLE(data) BOR mode);
			this->WriteNybble(LOW_NYBBLE(data) BOR mode);
		}

		VOID SetRgbReg(CBYTE regAddr, CBYTE data)
		{
			Wire.beginTransmission(LCD_RGB_BACKLIGHT_ADDRESS);

			WIRE_WRITE(regAddr);
			WIRE_WRITE(data);

			Wire.endTransmission();
		}


	public:

		// CONSTRUCTOR & INITIALIZATION FUNCTION

		LCD_I2C(CBOOL isGroveRgbLcd = FALSE) : _IsGroveRgbLcd(isGroveRgbLcd)
		{
			Wire.begin();

			this->Init();
		}

		VOID Init(CBYTE charSize = LCD_DOTS_5x8)
		{
			_DisplayFunction = LCD_INTERFACE_DATA_4_BIT |
				(Rows > 1 ? LCD_ROWS_MULTI : LCD_ROWS_SINGLE) | charSize;

			delay(50);

			WireWrite(_BacklightOn);
			delay(1000);

			//put the LCD into 4 bit mode
			// this is according to the hitachi HD44780 datasheet
			// figure 24, pg 46

			  // we start in 8bit mode, try to Set 4 bit mode
			this->WriteNybble(0x03 << 4);
			delayMicroseconds(4500); // wait min 4.1ms

			// second try
			this->WriteNybble(0x03 << 4);
			delayMicroseconds(4500); // wait min 4.1ms

			// third go!
			this->WriteNybble(0x03 << 4);
			delayMicroseconds(150);

			// finally, Set to 4-bit interface
			this->WriteNybble(0x02 << 4);


			this->SendCommand(LCD_CMD_FUNCTION_SET | _DisplayFunction);

			SET_BIT(_DisplayControl, LCD_CONTROL_DISPLAY);
			SET_BIT(_DisplayControl, LCD_CONTROL_BACKLIGHT);
			_BacklightOn = TRUE;
			this->SetDisplayControl();

			SET_BIT(_EntryMode, LCD_ENTRY_LEFT_TO_RIGHT);
			CLEAR_BIT(_EntryMode, LCD_ENTRY_CURSOR_SCROLL);
			this->SetEntryMode();

			if (_IsGroveRgbLcd)
				this->InitRgbLcd();

			this->Home();
			this->Clear();
		}


		// DISPLAY CONTROL FUNCTIONS

		VOID DisplayOn()
		{
			SET_BIT(_DisplayControl, LCD_CONTROL_DISPLAY);
			this->SetDisplayControl();
		}

		VOID DisplayOff()
		{
			CLEAR_BIT(_DisplayControl, LCD_CONTROL_DISPLAY);
			this->SetDisplayControl();
		}

		VOID BacklightOn()
		{
			_BacklightOn = TRUE;

			SET_BIT(_DisplayControl, LCD_CONTROL_BACKLIGHT);
			this->SetBacklight();
		}

		VOID BacklightOff()
		{
			_BacklightOn = FALSE;

			CLEAR_BIT(_DisplayControl, LCD_CONTROL_BACKLIGHT);
			this->SetBacklight();
		}

		VOID CursorOn()
		{
			SET_BIT(_DisplayControl, LCD_CONTROL_CURSOR);
			this->SetDisplayControl();
		}

		VOID CursorOff()
		{
			CLEAR_BIT(_DisplayControl, LCD_CONTROL_CURSOR);
			this->SetDisplayControl();
		}

		VOID CursorBlinkOn()
		{
			SET_BIT(_DisplayControl, LCD_CONTROL_CURSOR_BLINK);
			this->SetDisplayControl();
		}

		VOID CursorBlinkOff()
		{
			CLEAR_BIT(_DisplayControl, LCD_CONTROL_CURSOR_BLINK);
			this->SetDisplayControl();
		}


		// ENTRY MODE FUNCTIONS

		VOID CursorScrollOn()
		{
			SET_BIT(_EntryMode, LCD_ENTRY_CURSOR_SCROLL);
			this->SetEntryMode();
		}

		VOID CursorScrollOff()
		{
			CLEAR_BIT(_EntryMode, LCD_ENTRY_CURSOR_SCROLL);
			this->SetEntryMode();
		}

		VOID LeftToRight()
		{
			SET_BIT(_EntryMode, LCD_ENTRY_LEFT_TO_RIGHT);
			this->SetEntryMode();
		}

		VOID RightToLeft()
		{
			CLEAR_BIT(_EntryMode, LCD_ENTRY_LEFT_TO_RIGHT);
			this->SetEntryMode();
		}


		// BASIC LCD CONTROL FUNCTIONS

		VOID Clear()
		{
			this->SendCommand(LCD_CMD_DISPLAY_CLEAR);
			delayMicroseconds(2000);
		}

		VOID Home()
		{
			_CursorCol = 0;
			_CursorRow = 0;

			this->SendCommand(LCD_CMD_CURSOR_HOME);
			delayMicroseconds(2000);
		}

		VOID MoveCursor(CBYTE col, CBYTE row)
		{
			_CursorCol = col;
			_CursorRow = row;

			this->SendCommand(LCD_CMD_SET_DDRAM_ADDR BOR (col + LCD_ROW_OFFSETS()[row]));
		}

		VOID ScrollLeft()
		{
			this->SendCommand(LCD_SHIFT_CURSOR | LCD_SHIFT_DISPLAY | LCD_SHIFT_LEFT);
		}

		VOID ScrollRight()
		{
			this->SendCommand(LCD_SHIFT_CURSOR | LCD_SHIFT_DISPLAY | LCD_SHIFT_RIGHT);
		}


		// CUSTOM CHARACTER FUNCTIONS

		VOID LoadCustomChar(BYTE charIndex, PCBYTE charData)
		{
			charIndex = MASK(charIndex, 0x7);
			this->SendCommand(LCD_CMD_SET_CGRAM_ADDR BOR (charIndex << 3));

			for (BYTE i = 0; i < LCD_CHAR_HEIGHT; i++)
				this->write(charData[i]);
		}

		VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
		{
			charIndex = MASK(charIndex, 0x7);
			this->SendCommand(LCD_CMD_SET_CGRAM_ADDR BOR (charIndex << 3));

			for (BYTE i = 0; i < 8; i++)
				this->write(pgm_read_byte_near(charDataAddr++));
		}


		// CHARACTER/STRING PRINTING FUNCTIONS

		VIRTUAL SIZE write(BYTE value)
		{
			this->SendCommand(value, TRUE);
			return 1;
		}

		CBYTE PrintStr(PCCHAR str, BYTE col = MAX_OF(BYTE), BYTE row = MAX_OF(BYTE))
		{
			if (col == MAX_OF(BYTE))
				col = _CursorCol;

			if (row == MAX_OF(BYTE))
				row = _CursorRow;

			BYTE charsPrinted = 0;

			while (*str != '\0')
			{
				this->MoveCursor(col + charsPrinted++, row);
				this->write(*str++);
			}

			return charsPrinted;
		}

		CBYTE PrintStr_P(FLASH_STRING flashStr, BYTE col = MAX_OF(BYTE), BYTE row = MAX_OF(BYTE))
		{
			if (col == MAX_OF(BYTE))
				col = _CursorCol;

			if (row == MAX_OF(BYTE))
				row = _CursorRow;

			BYTE charsPrinted = 0;

			PCCHAR strAddr = reinterpret_cast<PCCHAR>(flashStr);
			CHAR c = pgm_read_byte_near(strAddr++);

			while (c != '\0')
			{
				this->MoveCursor(col + charsPrinted++, row);
				this->write(c);

				c = pgm_read_byte_near(strAddr++);
			}

			return charsPrinted;
		}


		// GROVE RGB LCD SUPPORT FUNCTIONS

		VOID InitRgbLcd()
		{
			this->SetRgbReg(LCD_RGB_REG_MODE_1, 0x0);
			this->SetRgbReg(LCD_RGB_REG_OUTPUT, LCD_RGB_PWM_AND_GRPPWM);
			this->SetRgbReg(LCD_RGB_REG_MODE_1, 0x0);

			this->SetRgbBacklightColorWhite();
		}

		VOID SetRgbBacklightColor(CBYTE r, CBYTE g, CBYTE b)
		{
			this->SetRgbReg(LCD_RGB_REG_RED, r);
			this->SetRgbReg(LCD_RGB_REG_GREEN, g);
			this->SetRgbReg(LCD_RGB_REG_BLUE, b);
		}

		VOID SetRgbBacklightColorWhite(CBYTE brightness = MAX_OF(BYTE))
		{
			this->SetRgbBacklightColor(
				(BYTE)((WORD)brightness * (WORD)MAX_OF(BYTE) / 100),
				(BYTE)((WORD)brightness * (WORD)MAX_OF(BYTE) / 100),
				(BYTE)((WORD)brightness * (WORD)MAX_OF(BYTE) / 100));
		}

		VOID RgbBlinkOn(CBYTE period = LCD_BLINK_PERIOD_OFF, CBYTE ratio = LCD_BLINK_RATIO_HALF)
		{
			// Period (s) = (period + 1) / 24
			this->SetRgbReg(LCD_RGB_REG_BLINK_LED_PERIOD, period);

			// Ratio (%) = (ratio + 1) / 256
			this->SetRgbReg(LCD_RGB_REG_BLINK_LED_RATIO, ratio);
		}

		VOID RgbLedBlinkOff()
		{
			this->SetRgbReg(LCD_RGB_REG_BLINK_LED_PERIOD, LCD_BLINK_PERIOD_OFF);
			this->SetRgbReg(LCD_RGB_REG_BLINK_LED_RATIO, LCD_BLINK_RATIO_OFF);
		}


	#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
		#include "IttyBitty_LCD_extensions_decl.h"
	#endif

	#ifndef NO_ITTYBITTY_LCD_BIG_EXTENSIONS
		#include "IttyBitty_LCD_extensions_big_decl.h"
	#endif
	};

#pragma endregion
};

#endif
