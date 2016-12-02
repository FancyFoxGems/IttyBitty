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
	#define WIRE_READ	Wire.read
#else
	#define WIRE_WRITE	Wire.send
	#define WIRE_READ	Wire.receive
#endif

#pragma endregion


#pragma region DEFINES

// LCD OPTIONS/CONSTANTS

#define LCD_DEFAULT_I2C_ADDRESS			0x27

#define LCD_DEFAULT_COLS				16
#define LCD_DEFAULT_ROWS				2

#define LCD_CHAR_HEIGHT_5x8				8
#define LCD_CHAR_HEIGHT_5x10			10
#define LCD_CHAR_WIDTH					5


// HD77480 LCD CONTROLLER POWER-ON/INIT, STROBE, and COMMAND WAIT TIMES


#define LCD_WAIT_STROBE_EN_PULSE_uS		1		// > 450 ns: minimum pulse sustain time
#define LCD_WAIT_STROBE_EN_SETTLE_uS	40		// > 37 us: minumum (write) command time

#define LCD_WAIT_POWER_ON_MS			100		// > 15 ms @ LCD Vcc = 4.5 V; > 40 ms @ LCD Vcc = 2.7 V

#define LCD_WAIT_INIT_1_uS				5000	// > 4.1 ms: minimum time for delay after first init command
#define LCD_WAIT_INIT_2_uS				150		// > 100 us: minimum time for delay after second init command

#define LCD_WAIT_CMD_HOME_uS			1483	// > (1,520 us - 37 us) = > 1,483 us: minimum execution time of "cursor home" command

#define LCD_WAIT_BUSY_DELAY_uS			10		// Delay period when Busy Flag is set (before checking again)


// LCD BACKLIGHT MASK FLAGS

#define LCD_BACKLIGHT_OFF				0x0
#define LCD_BACKLIGHT_ON				0x8


// LCD CONTROLLER & I2C INTERFACE BIT-FLAGS

#define LCD_HD77480_RS		0x0		// Register select pin, relative to I2C I/O expander connections
#define LCD_HD77480_RW		0x1		// Read/write pin, relative to I2C I/O expander connections; read enabled when HIGH
#define LCD_HD77480_En		0x2		// Enable pin, relative to I2C I/O expander connections

#define LCD_HD77480_BF		0x6		// Busy Flag bit


// COMMAND BYTES

#define LCD_CMD_INIT					0x30	// LCD_CMD_FUNCTION_SET | LCD_FUNCTION_INTERFACE_8_BIT

#define LCD_CMD_CLEAR_DISPLAY			0x01
#define LCD_CMD_CURSOR_HOME				0x02
#define LCD_CMD_ENTRY_MODE_SET			0x04
#define LCD_CMD_DISPLAY_CONTROL			0x08
#define LCD_CMD_CURSOR_DISPLAY_SHIFT	0x10
#define LCD_CMD_FUNCTION_SET			0x20
#define LCD_CMD_SET_CGRAM_ADDR			0x40
#define LCD_CMD_SET_DDRAM_ADDR			0x80


//  DISPLAY FUNCTION MODE FLAG VALUES

#define LCD_FUNCTION_DOTS_5x10			0x2
#define LCD_FUNCTION_ROWS_MULTI			0x3
#define LCD_FUNCTION_INTERFACE_8_BIT	0x4


// DISPLAY CONTROL BITS

#define LCD_CONTROL_CURSOR_BLINK		0x0
#define LCD_CONTROL_CURSOR				0x1
#define LCD_CONTROL_DISPLAY				0x2


// ENTRY MODE BITS

#define LCD_ENTRY_AUTO_SCROLL			0x0
#define LCD_ENTRY_LEFT_TO_RIGHT			0x1


// CURSOR/DISPLAY SHIFT

#define LCD_SHIFT_INCREMENT				0x2
#define LCD_SHIFT_DISPLAY				0x3


// GROVE RGB LCD SUPPORT

#define LCD_RGB_DISPLAY_ADDRESS			0x3E
#define LCD_RGB_BACKLIGHT_ADDRESS		0xE2

#define LCD_RGB_SEND_DATA				0x40
#define LCD_RGB_SEND_COMMAND			0x80

#define LCD_RGB_REG_MODE_1				0x0
#define LCD_RGB_REG_MODE_2				0x1
#define LCD_RGB_REG_BLUE				0x2
#define LCD_RGB_REG_GREEN				0x3
#define LCD_RGB_REG_RED					0x4
#define LCD_RGB_REG_LED_BLINK_RATIO		0x6
#define LCD_RGB_REG_LED_BLINK_PERIOD	0x7
#define LCD_RGB_REG_OUTPUT				0x8

#define LCD_RGB_PWM_AND_GRPPWM			0xFF

#define LCD_RGB_LED_BLINK_PERIOD_OFF				0x00
#define LCD_RGB_LED_BLINK_PERIOD_QUARTER_S			0x05
#define LCD_RGB_LED_BLINK_PERIOD_HALF_S				0x0B
#define LCD_RGB_LED_BLINK_PERIOD_ONE_S				0x17
#define LCD_RGB_LED_BLINK_PERIOD_TWO_S				0x2F

#define LCD_RGB_LED_BLINK_RATIO_OFF					0xFF
#define LCD_RGB_LED_BLINK_RATIO_QUARTER				0x3F
#define LCD_RGB_LED_BLINK_RATIO_HALF				0x7F
#define LCD_RGB_LED_BLINK_RATIO_THREE_QUARTERS		0xBF

#pragma endregion


namespace IttyBitty
{
#pragma region FORWARD DECLARATIONS & TYPE ALIASES

	#define LCDI2C_T_CLAUSE_DEF	<CBYTE Cols, CBYTE Rows, CBYTE I2CAddr, BOOL Use5x10Chars>
	#define LCDI2C_T_CLAUSE		<CBYTE Cols = LCD_DEFAULT_COLS, CBYTE Rows = LCD_DEFAULT_ROWS, \
		CBYTE I2CAddr = LCD_DEFAULT_I2C_ADDRESS, BOOL Use5x10Chars = FALSE>
	#define LCDI2C_T_ARGS		<Cols, Rows, I2CAddr, Use5x10Chars>

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

		STATIC PCBYTE ROW_OFFSETS()
		{
			STATIC CBYTE LCD_ROW_OFFSETS[4] = { 0x00, 0x40, 0x14, 0x54 };
			return LCD_ROW_OFFSETS;
		}


		// INSTANCE VARIABLES

		BOOL _WrapLines = FALSE;

		BOOL _Use8BitMode = FALSE;
		BOOL _IsGroveRgbLcd = FALSE;

		BYTE _BacklightVal = LCD_BACKLIGHT_OFF;

		BYTE _DisplayFunction = 0x0;
		BYTE _DisplayControl = 0x0;
		BYTE _EntryMode = 0x0;

		BYTE _CursorRow = 0;
		BYTE _CursorCol = 0;


		// HELPER FUNCTIONS

		VOID WireWrite(CBYTE data)
		{
			Wire.beginTransmission(I2CAddr);

			WIRE_WRITE((INT)(data | (!_Use8BitMode ? _BacklightVal : 0x0)));

			Wire.endTransmission();
		}

		VOID StrobeEnable(CBYTE data)
		{
			WireWrite(WITH_BIT(data, LCD_HD77480_En));
			delayMicroseconds(LCD_WAIT_STROBE_EN_PULSE_uS);

			WireWrite(WITHOUT_BIT(data, LCD_HD77480_En));
			delayMicroseconds(LCD_WAIT_STROBE_EN_SETTLE_uS);
		}

		CBYTE ReadData(BYTE addr = 0)
		{
			if (_Use8BitMode)
			{
				// ???
				if (addr)
					SET_BIT(addr, LCD_HD77480_RW);
			}
			else if (addr)
			{
				SET_BIT(addr, LCD_HD77480_RW);
			}

			Wire.requestFrom(I2CAddr, addr);

			return (CBYTE)WIRE_READ();
		}

		CBOOL IsBusy()
		{
			return CHECK_BIT(ReadData(), LCD_HD77480_BF);
		}

		VOID WriteCommand(CBYTE data)
		{
			this->WireWrite(data);

			if (!_Use8BitMode)
				this->StrobeEnable(data);
		}

		VOID SendCommand(CBYTE cmdOrData, CBOOL writeData = FALSE)
		{
			while (this->IsBusy())
				delayMicroseconds(LCD_WAIT_BUSY_DELAY_uS);

			if (_Use8BitMode)
			{
				if (writeData)
					this->WireWrite(LCD_RGB_SEND_DATA);
				else
					this->WireWrite(LCD_RGB_SEND_COMMAND);

				this->WriteCommand(cmdOrData);
			}
			else
			{
				this->WriteCommand(HIGH_NYBBLE(cmdOrData) |
					(writeData ? B(LCD_HD77480_RS) : 0x0));
				this->WriteCommand((LOW_NYBBLE(cmdOrData) SHL BITS_PER_NYBBLE) |
					(writeData ? B(LCD_HD77480_RS) : 0x0));
			}
		}

		VOID SetBacklight()
		{
			this->WireWrite(0);
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

		VOID ShiftCursorOrDisplay(CBYTE shiftOptions)
		{
			this->SendCommand(LCD_CMD_CURSOR_DISPLAY_SHIFT | shiftOptions);
		}

		VOID SetCgramAddr(CBYTE cgramAddr)
		{
			this->SendCommand(LCD_CMD_SET_CGRAM_ADDR | cgramAddr);
		}

		VOID SetDdramAddr(CBYTE ddramAddr)
		{
			this->SendCommand(LCD_CMD_SET_DDRAM_ADDR | ddramAddr);
		}


		// GROVE RGB LCD HELPER FUNCTIONS

		VOID SetRgbReg(CBYTE regAddr, CBYTE data)
		{
			Wire.beginTransmission(LCD_RGB_BACKLIGHT_ADDRESS);

			WIRE_WRITE(regAddr);
			WIRE_WRITE(data);

			Wire.endTransmission();
		}


	public:

		// STATIC CONSTEXPR FUNCTIONS

		STATIC CONSTEXPR CBYTE COLS()
		{
			return Cols;
		}

		STATIC CONSTEXPR CBYTE ROWS()
		{
			return Rows;
		}

		STATIC CONSTEXPR CBYTE CHAR_WIDTH()
		{
			return LCD_CHAR_WIDTH;
		}

		STATIC CONSTEXPR CBYTE CHAR_HEIGHT()
		{
			return Use5x10Chars ? LCD_CHAR_HEIGHT_5x10 : LCD_CHAR_HEIGHT_5x8;
		}


		// CONSTRUCTOR & INITIALIZATION/RESET FUNCTION

		LCD_I2C(CBOOL wrapLines = FALSE, CBOOL use8BitMode = FALSE, CBOOL isGroveRgbLcd = FALSE)
			: _WrapLines(wrapLines), _Use8BitMode(use8BitMode), _IsGroveRgbLcd(isGroveRgbLcd)
		{
			if (_IsGroveRgbLcd)
				_Use8BitMode = TRUE;

			Wire.begin();

			this->Reset();
		}

		VOID Reset()
		{
			delay(LCD_WAIT_POWER_ON_MS);

			this->BacklightOff();

			this->WriteCommand(LCD_CMD_INIT);
			delayMicroseconds(LCD_WAIT_INIT_1_uS);

			this->WriteCommand(LCD_CMD_INIT);
			delayMicroseconds(LCD_WAIT_INIT_2_uS);

			_DisplayFunction = (Rows > 1 ? B(LCD_FUNCTION_ROWS_MULTI) : 0x0) |
				(Use5x10Chars ? B(LCD_FUNCTION_DOTS_5x10) : 0x0);

			if (_Use8BitMode)
				SET_BIT(_DisplayFunction, LCD_FUNCTION_INTERFACE_8_BIT);

			this->SetDisplayFunction();

			_DisplayControl = B(LCD_CONTROL_DISPLAY);
			this->SetDisplayControl();

			_EntryMode = B(LCD_ENTRY_LEFT_TO_RIGHT);
			this->SetEntryMode();

			if (_IsGroveRgbLcd)
				this->InitRgbLcd();

			this->Clear();
			this->Home();

			this->BacklightOn();
		}


		// ACCESSORS & MUTATORS

		CBOOL IsBacklightOn()
		{
			return _BacklightVal == LCD_BACKLIGHT_ON;
		}

		CBOOL IsLineWrapEnabled()
		{
			return _WrapLines;
		}

		VOID SetLineWrap(CBOOL wrapLines = TRUE)
		{
			_WrapLines = wrapLines;
		}


		// BACKLIGHT CONTROL FUNCTIONS

		VOID BacklightOn()
		{
			_BacklightVal = LCD_BACKLIGHT_ON;
			this->SetBacklight();
		}

		VOID BacklightOff()
		{
			_BacklightVal = LCD_BACKLIGHT_OFF;
			this->SetBacklight();
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

		VOID AutoScrollOn()
		{
			SET_BIT(_EntryMode, LCD_ENTRY_AUTO_SCROLL);
			this->SetEntryMode();
		}

		VOID AutoScrollOff()
		{
			CLEAR_BIT(_EntryMode, LCD_ENTRY_AUTO_SCROLL);
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


		// CURSOR/DISPLAY SHIFT FUNCTIONS

		VOID CursorPrev()
		{
			if (_CursorCol == 0)
				_CursorCol = Cols - 1;
			else
				--_CursorCol;

			this->ShiftCursorOrDisplay();
		}

		VOID CursorNext()
		{
			if (_CursorCol == Cols - 1)
				_CursorCol = 0;
			else
				++_CursorCol;

			this->ShiftCursorOrDisplay(B(LCD_SHIFT_INCREMENT));
		}

		VOID ScrollLeft()
		{
			if (_CursorCol == 0)
				_CursorCol = Cols - 1;
			else
				--_CursorCol;

			this->ShiftCursorOrDisplay(B(LCD_SHIFT_DISPLAY));
		}

		VOID ScrollRight()
		{
			if (_CursorCol == Cols - 1)
				_CursorCol = 0;
			else
				++_CursorCol;

			this->ShiftCursorOrDisplay(B(LCD_SHIFT_DISPLAY) | B(LCD_SHIFT_INCREMENT));
		}


		// BASIC LCD CONTROL FUNCTIONS

		VOID Clear()
		{
			this->SendCommand(LCD_CMD_CLEAR_DISPLAY);
		}

		VOID Home()
		{
			_CursorCol = 0;
			_CursorRow = 0;

			this->SendCommand(LCD_CMD_CURSOR_HOME);

			delayMicroseconds(LCD_WAIT_CMD_HOME_uS);
		}

		VOID MoveCursor(BYTE col, BYTE row)
		{
			if (col >= Cols)
			{
				if (_WrapLines)
				{
					col = col % Cols;
					row += col / Cols;
				}
				else
				{
					col = Cols - 1;
				}
			}

			_CursorCol = col;
			_CursorRow = row;

			this->SetDdramAddr(col + (ROW_OFFSETS())[row]);
		}


		// CUSTOM CHARACTER FUNCTIONS

		VOID LoadCustomChar(BYTE charIndex, PCBYTE charData)
		{
			charIndex = MASK(charIndex, (Use5x10Chars ? 0xf : 0x7));
			this->SetCgramAddr(Use5x10Chars ? charIndex * CHAR_HEIGHT() : charIndex SHL 0x3);

			for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
				this->write(charData[i]);
		}

		VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
		{
			charIndex = MASK(charIndex, (Use5x10Chars ? 0xf : 0x7));
			this->SetCgramAddr(Use5x10Chars ? charIndex * CHAR_HEIGHT() : charIndex SHL 0x3);

			for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
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
			this->SetRgbReg(LCD_RGB_REG_MODE_2, 0x0);

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

		VOID RgbBlinkOn(CBYTE period = LCD_RGB_LED_BLINK_PERIOD_OFF, CBYTE ratio = LCD_RGB_LED_BLINK_RATIO_HALF)
		{
			// Period (s) = (period + 1) / 24
			this->SetRgbReg(LCD_RGB_REG_LED_BLINK_PERIOD, period);

			// Ratio (%) = (ratio + 1) / 256
			this->SetRgbReg(LCD_RGB_REG_LED_BLINK_RATIO, ratio);
		}

		VOID RgbLedBlinkOff()
		{
			this->SetRgbReg(LCD_RGB_REG_LED_BLINK_PERIOD, LCD_RGB_LED_BLINK_PERIOD_OFF);
			this->SetRgbReg(LCD_RGB_REG_LED_BLINK_RATIO, LCD_RGB_LED_BLINK_RATIO_OFF);
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
