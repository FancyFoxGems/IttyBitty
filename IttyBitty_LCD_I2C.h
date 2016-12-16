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
#include "IttyBitty_LCD_chars.h"

#ifndef NO_ITTYBITTY_LCD_BIG
	#include "IttyBitty_LCD_big.h"
#endif

#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
	#include "IttyBitty_LCD_extensions.h"
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


// LCD CONTROLLER POWER-ON/INIT, STROBE, and COMMAND WAIT TIMES

#define LCD_WAIT_STROBE_EN_PULSE_uS		1		// > 450 ns: minimum pulse sustain time

#define LCD_WAIT_CMD_EXECUTE_uS			40		// ... + LCD_WAIT_STROBE_EN_PULSE_uS > 37 us: minumum (write) command time

#define LCD_WAIT_POWER_ON_MS			200		// > 15 ms @ LCD Vcc = 4.5 V; > 40 ms @ LCD Vcc = 2.7 V

#define LCD_WAIT_INIT_1_uS				4500	// > 4.1 ms: minimum time for delay after first init command
#define LCD_WAIT_INIT_2_uS				150		// > 100 us: minimum time for delay after second init command

#define LCD_WAIT_CMD_HOME_CLEAR_uS		1483	// > (1,520 us - 37 us) = > 1,483 us: minimum execution time of "cursor home" and "clear display" commands

#define LCD_WAIT_BUSY_DELAY_uS			10		// Delay period when Busy Flag is set (before checking again)
#define LCD_WAIT_AC_UPDATE_DELAY_uS		4		// Delay period after Busy Flag is unset until Address Counter is updated


// LCD CONTROLLER / I2C INTERFACE BIT-FLAGS & MASKS (HD44780-based display pins, relative to I2C I/O expander bits)

#define LCD_RS		0x0		// Register Select (RS) pin; LOW: COMMAND / HIGH: DATA
#define LCD_RW		0x1		// Read/Write (RW) pin; LOW: WRITE / HIGH: READ
#define LCD_En		0x2		// Enable (E) pin; strobed to clock in instructions and data; LOW: PULSE END / HIGH: PULSE START
#define LCD_LED		0x3		// Backlight anode (LED+) pin; backlight on when HIGH
#define LCD_D4		0x4		// Pin 4 bit (D4 pin)
#define LCD_D5		0x5		// Pin 5 bit (D5 pin)
#define LCD_D6		0x6		// Pin 6 bit (D6 pin)
#define LCD_D7		0x7		// Pin 7 bit (D7 pin)
#define LCD_BF		0x7		// Busy Flag bit (D7 pin); LOW: AVAILABLE / HIGH: BUSY (executing write command)

//#define LCD_


// COMMAND BYTE MASKS

#define LCD_CMD_INIT					0x30	// LCD_CMD_FUNCTION_SET | B(LCD_FUNCTION_INTERFACE_8_BIT)
#define LCD_CMD_INIT_4_BIT				0x20	// LCD_CMD_FUNCTION_SET

#define LCD_CMD_READ					0xF0	// B(LCD_D4) | ... | B(LCD_D7) | B(LCD_RW)

#define LCD_CMD_CLEAR_DISPLAY			0x01
#define LCD_CMD_CURSOR_HOME				0x02
#define LCD_CMD_ENTRY_MODE_SET			0x04
#define LCD_CMD_DISPLAY_CONTROL			0x08
#define LCD_CMD_CURSOR_DISPLAY_SHIFT	0x10
#define LCD_CMD_FUNCTION_SET			0x20
#define LCD_CMD_SET_CGRAM_ADDR			0x40
#define LCD_CMD_SET_DDRAM_ADDR			0x80


// ADDRESS INDEX & DATA BYTE MASKS

#define LCD_8_BIT_SEND_DATA				0x40
#define LCD_8_BIT_SEND_COMMAND			0x80

#define LCD_8_BIT_ADDR_OFFSET			0x80

#define LCD_ADDRESS_COUNTER_MASK		0x7F

#define LCD_CUSTOM_CHAR_IDX_MASK_5x8	0x7
#define LCD_CUSTOM_CHAR_IDX_MASK_5x10	0x3


//  FUNCTION (SET) BIT-FLAGS

#define LCD_FUNCTION_DOTS_5x10			0x2
#define LCD_FUNCTION_ROWS_MULTI			0x3
#define LCD_FUNCTION_INTERFACE_8_BIT	0x4


// DISPLAY CONTROL BIT-FLAGS

#define LCD_CONTROL_CURSOR_BLINK		0x0
#define LCD_CONTROL_CURSOR				0x1
#define LCD_CONTROL_DISPLAY				0x2


// ENTRY MODE BIT-FLAGS

#define LCD_ENTRY_AUTO_SCROLL			0x0
#define LCD_ENTRY_LEFT_TO_RIGHT			0x1


// SHIFT CURSOR/DISPLAY BIT-FLAGS

#define LCD_SHIFT_INCREMENT				0x2
#define LCD_SHIFT_DISPLAY				0x3


#ifndef NO_ITTYBITTY_LCD_RGB

	// GROVE RGB LCD SUPPORT

	#define LCD_RGB_DISPLAY_ADDRESS			0x3E
	#define LCD_RGB_BACKLIGHT_ADDRESS		0xE2

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

#endif

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

		STATIC PCBYTE ROW_ADDR_OFFSETS()
		{
			STATIC CBYTE LCD_ROW_ADDR_OFFSETS[4] = { 0x00, 0x40, 0x14, 0x54 };
			return LCD_ROW_ADDR_OFFSETS;
		}


		// INSTANCE VARIABLES

		BOOL _WrapLines = FALSE;

		BOOL _Use8BitInterface = FALSE;

	#ifndef NO_ITTYBITTY_LCD_RGB
		BOOL _IsGroveRgbLcd = FALSE;
	#endif

		BOOL _IsInitializing = TRUE;

		BOOL _BacklightOn = FALSE;

		BYTE _DisplayFunction = 0x0;
		BYTE _DisplayControl = 0x0;
		BYTE _EntryMode = 0x0;

		BYTE _CursorRow = 0;
		BYTE _CursorCol = 0;

	#ifndef NO_ITTYBITTY_LCD_BIG
		BOOL _BigFontLoaded = FALSE;
	#endif


		// HELPER METHODS

		VOID PulseEnRising(CBYTE data)
		{
			this->WriteI2C(WITH_BIT(data, LCD_En));
			delayMicroseconds(LCD_WAIT_STROBE_EN_PULSE_uS);
		}

		VOID PulseEnFalling(CBYTE data)
		{
			this->WriteI2C(WITHOUT_BIT(data, LCD_En));
			delayMicroseconds(LCD_WAIT_STROBE_EN_PULSE_uS);
		}

		CBYTE ReadI2C()
		{
			Wire.requestFrom(I2CAddr, (BYTE)1);

			return (CBYTE)WIRE_READ();
		}

		CBYTE ClockInRead(CBYTE data)
		{
			this->WriteI2C(data);
			this->PulseEnRising(data);

			BYTE result = this->ReadI2C();

			if (!_Use8BitInterface)
			{
				result = HIGH_NYBBLE(result);

				this->PulseEnFalling(data);
				this->PulseEnRising(data);

				result |= HIGH_NYBBLE(this->ReadI2C()) SHR BITS_PER_NYBBLE;
			}

			this->PulseEnFalling(data);

			return result;
		}

		CBYTE SendReadCommand(CBYTE data)
		{
			return this->ClockInRead(WITH_BIT(data, LCD_RW));
		}

		CBYTE Receive(CBOOL readData = FALSE)
		{
			if (_Use8BitInterface)
			{
				// ???
				if (readData)
					this->WriteI2C(LCD_8_BIT_SEND_DATA);
				else
					this->WriteI2C(LCD_8_BIT_SEND_COMMAND);

				return this->SendReadCommand(LCD_CMD_READ);
			}
			else
			{
				BYTE result = this->SendReadCommand(LCD_CMD_READ | (readData ? B(LCD_RS) : 0x0));
				return result;
			}
		}

		CBOOL IsBusy()
		{
			return CHECK_BIT(this->Receive(), LCD_BF);
		}

		VOID WriteI2C(CBYTE data)
		{
			Wire.beginTransmission(I2CAddr);

			if (_Use8BitInterface)
				WIRE_WRITE((INT)(data));
			else
				WIRE_WRITE((INT)(data | (_BacklightOn ? B(LCD_LED) : 0x0)));

			Wire.endTransmission();
		}

		VOID ClockInWrite(CBYTE data)
		{
			this->WriteI2C(data);
			this->PulseEnRising(data);
			this->PulseEnFalling(data);

			delayMicroseconds(LCD_WAIT_CMD_EXECUTE_uS);
		}

		VOID SendWriteCommand(CBYTE data)
		{
			this->ClockInWrite(data);
		}

		VOID Send(BYTE cmdOrData, CBOOL sendData = FALSE)
		{
			if (!_IsInitializing)
			{
				if (this->IsBusy())
				{
					while (this->IsBusy())
						delayMicroseconds(LCD_WAIT_BUSY_DELAY_uS);

					delayMicroseconds(LCD_WAIT_AC_UPDATE_DELAY_uS);
				}
			}

			if (_Use8BitInterface)
			{
				if (sendData)
					this->WriteI2C(LCD_8_BIT_SEND_DATA);
				else
					this->WriteI2C(LCD_8_BIT_SEND_COMMAND);

				this->SendWriteCommand(cmdOrData);
			}
			else
			{
				this->SendWriteCommand(HIGH_NYBBLE(cmdOrData) |
					(sendData ? B(LCD_RS) : 0x0));
				this->SendWriteCommand((LOW_NYBBLE(cmdOrData) SHL BITS_PER_NYBBLE) |
					(sendData ? B(LCD_RS) : 0x0));
			}
		}

		VOID SetBacklight()
		{
			this->WriteI2C(0);
		}

		VOID SetDisplayFunction()
		{
			this->Send(LCD_CMD_FUNCTION_SET | _DisplayFunction);
		}

		VOID SetDisplayControl()
		{
			this->Send(LCD_CMD_DISPLAY_CONTROL | _DisplayControl);
		}

		VOID SetEntryMode()
		{
			this->Send(LCD_CMD_ENTRY_MODE_SET | _EntryMode);
		}

		VOID ShiftCursorOrDisplay(CBYTE shiftOptions = 0x0)
		{
			this->Send(LCD_CMD_CURSOR_DISPLAY_SHIFT | shiftOptions);
		}

		VOID SetDdramAddr(CBYTE ddramAddr)
		{
			this->Send(LCD_CMD_SET_DDRAM_ADDR | ddramAddr);
		}

		VOID SetDdramAddrByColAndRow(CBYTE col, CBYTE row)
		{
			this->SetDdramAddr(col + ((ROW_ADDR_OFFSETS())[row] |
				(_Use8BitInterface ? LCD_8_BIT_ADDR_OFFSET : 0x0)));
		}

		VOID SetCgramAddr(CBYTE cgramAddr)
		{
			this->Send(LCD_CMD_SET_CGRAM_ADDR | cgramAddr);
		}

		VOID SetCgramAddrByCharIndex(BYTE charIndex)
		{
			CHOOSE_BITS(charIndex, Use5x10Chars ?
				LCD_CUSTOM_CHAR_IDX_MASK_5x10 : LCD_CUSTOM_CHAR_IDX_MASK_5x8);
			this->SetCgramAddr(Use5x10Chars ? charIndex * CHAR_HEIGHT() : charIndex SHL 0x3);
		}

		CBYTE GetDdramData()
		{
			return this->Receive(TRUE);
		}

		CBYTE GetCgramData(PBYTE resultCharData)
		{
			for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
				resultCharData[i] = this->Receive(TRUE);

			return CHAR_HEIGHT();
		}


	#ifndef NO_ITTYBITTY_LCD_RGB

		// GROVE RGB LCD HELPER METHODS

		VOID SetRgbReg(CBYTE regAddr, CBYTE data)
		{
			Wire.beginTransmission(LCD_RGB_BACKLIGHT_ADDRESS);

			WIRE_WRITE(regAddr);
			WIRE_WRITE(data);

			Wire.endTransmission();
		}

	#endif


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

		LCD_I2C(CBOOL wrapLines = FALSE, CBOOL use8BitInterface = FALSE
		#ifndef NO_ITTYBITTY_LCD_RGB
			, CBOOL isGroveRgbLcd = FALSE)
		#endif
			: _WrapLines(wrapLines), _Use8BitInterface(use8BitInterface)
		#ifndef NO_ITTYBITTY_LCD_RGB
			, _IsGroveRgbLcd(isGroveRgbLcd)
		#endif
		{
		#ifndef NO_ITTYBITTY_LCD_RGB
			if (_IsGroveRgbLcd)
				_Use8BitInterface = TRUE;
		#endif

			Wire.begin();

			this->Reset();
		}

		VOID Reset()
		{
			_IsInitializing = TRUE;

			delay(LCD_WAIT_POWER_ON_MS);

			this->BacklightOff();

			this->SendWriteCommand(LCD_CMD_INIT);

			delayMicroseconds(LCD_WAIT_INIT_1_uS);
			this->SendWriteCommand(LCD_CMD_INIT);

			delayMicroseconds(LCD_WAIT_INIT_2_uS);
			this->SendWriteCommand(LCD_CMD_INIT);

			_DisplayFunction = 0x0;

			if (_Use8BitInterface)
				SET_BIT(_DisplayFunction, LCD_FUNCTION_INTERFACE_8_BIT);
			else
				this->SendWriteCommand(LCD_CMD_INIT_4_BIT);

			if (Rows > 1)
				SET_BIT(_DisplayFunction, LCD_FUNCTION_ROWS_MULTI);

			if (Use5x10Chars)
				SET_BIT(_DisplayFunction, LCD_FUNCTION_DOTS_5x10);

			this->SetDisplayFunction();

			_DisplayControl = 0x0;
			this->SetDisplayControl();

			this->Clear();

			_EntryMode = B(LCD_ENTRY_LEFT_TO_RIGHT);
			this->SetEntryMode();

			this->BacklightOn();

			this->DisplayOn();

			_IsInitializing = FALSE;

			this->Home();

		#ifndef NO_ITTYBITTY_LCD_RGB
			if (_IsGroveRgbLcd)
				this->InitRgbLcd();
		#endif
		}


		// ACCESSORS/MUTATORS

		CBOOL IsLineWrapEnabled()
		{
			return _WrapLines;
		}

		VOID SetLineWrap(CBOOL wrapLines = TRUE)
		{
			_WrapLines = wrapLines;
		}

		CBOOL IsBacklightOn()
		{
			return _BacklightOn;
		}

		CBYTE CursorCol()
		{
			return _CursorCol;
		}

		CBYTE CursorRow()
		{
			return _CursorRow;
		}


		// READ METHODS

		CBYTE GetLastCharacterWritten()
		{
			this->CursorPrev();

			BYTE resultChar = this->GetDdramData();

			this->CursorNext();

			return resultChar;
		}

		CBYTE GetDisplayedCharacter(BYTE col = MAX_BYTE, BYTE row = MAX_BYTE)
		{
			if (col != MAX_BYTE OR row != MAX_BYTE)
			{
				BYTE currCol = _CursorCol;
				BYTE currRow = _CursorRow;

				this->MoveCursor(col, row);

				BYTE resultChar = this->GetDdramData();

				this->MoveCursor(currCol, currRow);

				return resultChar;
			}
			else
			{
				return this->GetDdramData();
			}
		}

		CBYTE GetDisplayedString(PBYTE resultStr, BYTE length, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE)
		{
			BYTE currCol = _CursorCol;
			BYTE currRow = _CursorRow;

			this->MoveCursor(col, row);

			for (BYTE i = 0; i < length; i ++)
			{
				resultStr[i] = this->GetDdramData();

				this->CursorNext();
			}

			this->MoveCursor(currCol, currRow);

			resultStr[length - 1] = '\0';

			return length;
		}

		CBYTE GetCustomChar(PBYTE resultCharData, BYTE charIndex)
		{
			this->SetCgramAddrByCharIndex(charIndex);

			return this->GetCgramData(resultCharData);
		}


		// BACKLIGHT CONTROL METHODS

		VOID BacklightOn()
		{
			_BacklightOn = TRUE;
			this->SetBacklight();
		}

		VOID BacklightOff()
		{
			_BacklightOn = FALSE;
			this->SetBacklight();
		}


		// DISPLAY CONTROL METHODS

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


		// ENTRY MODE METHODS

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


		// SHIFT CURSOR/DISPLAY METHODS

		VOID CursorPrev()
		{
			if (--_CursorCol == MAX_BYTE)
			{
				_CursorCol = Cols - 1;

				if (_WrapLines AND --_CursorRow == MAX_BYTE)
						_CursorRow = Rows - 1;

				this->MoveCursor(_CursorCol, _CursorRow);
			}
			else
			{
				this->ShiftCursorOrDisplay();
			}
		}

		VOID CursorNext()
		{
			if (++_CursorCol >= Cols)
			{
				_CursorCol = 0;

				if (_WrapLines AND ++_CursorRow >= Rows)
						_CursorRow = 0;

				this->MoveCursor(_CursorCol, _CursorRow);
			}
			else
			{
				this->ShiftCursorOrDisplay(B(LCD_SHIFT_INCREMENT));
			}
		}

		VOID ScrollLeft()
		{
			if (--_CursorCol == MAX_BYTE)
				_CursorCol = Cols - 1;

			this->ShiftCursorOrDisplay(B(LCD_SHIFT_DISPLAY));
		}

		VOID ScrollRight()
		{
			if (++_CursorCol >= Cols)
				_CursorCol = 0;

			this->ShiftCursorOrDisplay(B(LCD_SHIFT_DISPLAY) | B(LCD_SHIFT_INCREMENT));
		}


		// BASIC LCD CONTROL METHODS

		VOID Clear()
		{
			this->Send(LCD_CMD_CLEAR_DISPLAY);

			delayMicroseconds(LCD_WAIT_CMD_HOME_CLEAR_uS);
		}

		VOID Home()
		{
			_CursorCol = 0;
			_CursorRow = 0;

			this->Send(LCD_CMD_CURSOR_HOME);

			delayMicroseconds(LCD_WAIT_CMD_HOME_CLEAR_uS);
		}

		VOID MoveCursor(BYTE col, BYTE row)
		{
			if (col >= Cols)
			{
				if (_WrapLines)
				{
					col = (col + 1) % Cols - 1;
					row += col / Cols;
				}
				else
				{
					col = Cols - 1;
				}
			}

			if (row >= Rows)
				row = Rows - 1;

			_CursorCol = col;
			_CursorRow = row;

			this->SetDdramAddrByColAndRow(col, row);
		}


		// CUSTOM CHARACTER METHODS

		VOID LoadCustomChar(BYTE charIndex, PCBYTE charData)
		{
			this->SetCgramAddrByCharIndex(charIndex);

			for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
				this->write(charData[i]);
		}

		VOID LoadCustomChar_P(BYTE charIndex, PCBYTE charDataAddr)
		{
			this->SetCgramAddrByCharIndex(charIndex);

			for (BYTE i = 0; i < CHAR_HEIGHT(); i++)
				this->write(pgm_read_byte_near(charDataAddr++));
		}


		// CHARACTER/STRING PRINTING METHODS

		VIRTUAL SIZE write(BYTE value)
		{
			this->Send(value, TRUE);

			return 1;
		}

		CBYTE WriteAt(CBYTE value, CBYTE col, CBYTE row)
		{
		#ifndef NO_ITTYBITTY_LCD_BIG
			_BigFontLoaded = FALSE;
		#endif

			this->MoveCursor(col, row);
			return (CBYTE)this->write(value);
		}

		VOID ClearCol(CBYTE col = MAX_BYTE)
		{
			if (col == MAX_BYTE)
				col = _CursorCol;

			for (BYTE i = 0; i < Rows; i++)
				this->WriteAt(LCD_SYMBOL_BLANK, col, i);
		}

		VOID ClearRow(CBYTE row = MAX_BYTE)
		{
			if (row == MAX_BYTE)
				row = _CursorRow;

			for (BYTE i = 0; i < Cols; i++)
				this->WriteAt(LCD_SYMBOL_BLANK, i, row);
		}

		CBYTE PrintString(PCCHAR str, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE
		#ifndef NO_ITTYBITTY_LCD_BIG
			, CBYTE (LCD_I2C::*writeCallback)(CBYTE, CBYTE, CBYTE) = &LCD_I2C::WriteAt
		#endif
		)
		{
			if (col == MAX_BYTE)
				col = _CursorCol;

			if (row == MAX_BYTE)
				row = _CursorRow;

			BYTE charsPrinted = 0;

			while (*str != '\0')
				charsPrinted += (this->*writeCallback)((BYTE)*str++, col + charsPrinted, row);

			return charsPrinted;
		}

		CBYTE PrintString_P(FLASH_STRING flashStr, BYTE col = MAX_BYTE, BYTE row = MAX_BYTE
		#ifndef NO_ITTYBITTY_LCD_BIG
			, CBYTE (LCD_I2C::*writeCallback)(CBYTE, CBYTE, CBYTE) = &LCD_I2C::WriteAt
		#endif
		)
		{
			if (col == MAX_BYTE)
				col = _CursorCol;

			if (row == MAX_BYTE)
				row = _CursorRow;

			BYTE charsPrinted = 0;

			PCCHAR strAddr = reinterpret_cast<PCCHAR>(flashStr);
			BYTE c = pgm_read_byte_near(strAddr++);

			while (c != '\0')
			{
				charsPrinted += (this->*writeCallback)(c, col + charsPrinted, row);

				c = pgm_read_byte_near(strAddr++);
			}

			return charsPrinted;
		}


	#ifndef NO_ITTYBITTY_LCD_RGB

		// GROVE RGB LCD SUPPORT METHODS

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

		VOID SetRgbBacklightColorWhite(CBYTE brightness = MAX_BYTE)
		{
			this->SetRgbBacklightColor(
				(BYTE)((WORD)brightness * (WORD)MAX_BYTE / 100),
				(BYTE)((WORD)brightness * (WORD)MAX_BYTE / 100),
				(BYTE)((WORD)brightness * (WORD)MAX_BYTE / 100));
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

	#endif


	#ifndef NO_ITTYBITTY_LCD_BIG
		#include "IttyBitty_LCD_big_decl.h"
	#endif

	#ifndef NO_ITTYBITTY_LCD_EXTENSIONS
		#include "IttyBitty_LCD_extensions_decl.h"
	#endif
	};

#pragma endregion
};

#endif
