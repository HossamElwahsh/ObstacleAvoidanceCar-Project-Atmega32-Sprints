/*
 * lcd.c
 *
 * Created: 5/16/2023 12:51:06 PM
 *  Author: Sarah
 */ 
#include "lcd_interface.h"
#include "lcd_config.h"
/**************************************************************************************************
 * 										Macros
 *************************************************************************************************/

#define LCD_CLEAR_DISPLAY					0x01
#define LCD_CURSOR_HOME					0x02
#define LCD_ENTRY_MODE_CURSOR_INCREMENT	0x06
#define LCD_DISPLAY_ON_CURSOR_ON_NO_BLINK	0x0E
#define LCD_4_BIT_MODE_SELECTION			0x28
#define LCD_8_BIT_MODE_SELECTION			0x38
#define LCD_DISPLAY_SHIFT_LEFT				0x18
#define LCD_DISPLAY_SHIFT_RIGHT			0x1C
#define LCD_SET_CGRAM_ADDR_CMD				0x40

#define INDEX		10
/**************************************************************************************************
 * 										Global Variables
 *************************************************************************************************/
#if LCD_MODE == LCD_4_BIT_MODE

extern en_DIO_pin_t dataPin[4];

#elif LCD_MODE == LCD_8_BIT_MODE

extern en_DIO_pin_t dataPin[8];


#endif

/**
 * @brief This function  to set LCD initialization
 *
 * @param void
 *
 * @return Returns void
 */

void LCD_vidInit(void)
{
	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinDir(LCD_DATA_PORT,dataPin[i],OUTPUT);
	}

	DIO_setPinDir(LCD_CONTROL_PORT,LCD_RS_PIN,OUTPUT);
	DIO_setPinDir(LCD_CONTROL_PORT,LCD_RW_PIN,OUTPUT);
	DIO_setPinDir(LCD_CONTROL_PORT,LCD_EN_PIN,OUTPUT);

	 DELAY_setTime(40);

	LCD_vidWritecmd(LCD_CURSOR_HOME);
	DELAY_setTime (1);
#if LCD_MODE == LCD_4_BIT_MODE

	LCD_vidWritecmd(LCD_4_BIT_MODE_SELECTION);
	DELAY_setTime (1);

#elif LCD_MODE == LCD_8_BIT_MODE
	LCD_vidWritecmd(LCD_8_BIT_MODE_SELECTION);
	DELAY_setTime (1);
#endif
	LCD_vidWritecmd(LCD_CLEAR_DISPLAY);
	DELAY_setTime (4);

	LCD_vidWritecmd(LCD_ENTRY_MODE_CURSOR_INCREMENT);
	DELAY_setTime (1);

	LCD_vidWritecmd(LCD_DISPLAY_ON_CURSOR_ON_NO_BLINK);
	DELAY_setTime (1);
}

/**
 * @brief This function to configure some commands on lcd
 *
 * @param u8commandCopy --> take lcd cmd instructions from instruction table
 *
 * @return Returns void
 */


void LCD_vidWritecmd(u8 u8commandCopy)
{
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_RW_PIN, LOW); // WRITE
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_RS_PIN, LOW); // CMD

#if LCD_MODE == LCD_4_BIT_MODE

	u8 loc_u8DataReg = 0;
	loc_u8DataReg = (u8commandCopy & 0xF0);
	loc_u8DataReg >>= 4;

	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinVal(LCD_DATA_PORT,dataPin[i], ((loc_u8DataReg >> i)&1) );
	}

	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, HIGH); //ENABLE high
	DELAY_setTime (1);
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, LOW); //ENABLE low

	DELAY_setTime (2);

	loc_u8DataReg = (u8commandCopy & 0x0F);

	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinVal(LCD_DATA_PORT,dataPin[i], ((loc_u8DataReg >> i)&1) );
	}

	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, HIGH); //ENABLE high
	DELAY_setTime (1);
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, LOW); //ENABLE low
	DELAY_setTime (2);


#elif LCD_MODE == LCD_8_BIT_MODE
	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinVal(dataPin[i].en_dataPin, ((u8commandCopy >> i)&1) );
	}

	DIO_setPinVal(LCD_EN_PIN, HIGH); //ENABLE high
	DELAY_setTime (2);
	DIO_setPinVal(LCD_EN_PIN, LOW); //ENABLE low
	DELAY_setTime (2);
#endif


}

/**
 * @brief This function write char on lcd
 *
 * @param u8CharCopy -> take ascii code of char   or   char address on CGROM
 *
 * @return Returns void
 */


void LCD_vidWriteChar(u8 u8CharCopy)
{
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_RW_PIN, LOW); // WRITE
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_RS_PIN, HIGH); // DATA

#if LCD_MODE == LCD_4_BIT_MODE

	u8 loc_u8DataReg = 0;
	loc_u8DataReg = (u8CharCopy & 0xF0);
	loc_u8DataReg >>= 4;

	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinVal(LCD_DATA_PORT, dataPin[i], ((loc_u8DataReg >> i)&1) );
	}

	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, HIGH); //ENABLE high
	DELAY_setTime (1);
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, LOW); //ENABLE low

	DELAY_setTime (2);

	loc_u8DataReg = (u8CharCopy & 0x0F);

	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinVal(LCD_DATA_PORT, dataPin[i], ((loc_u8DataReg >> i)&1) );
	}

	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, HIGH); //ENABLE high
	DELAY_setTime (1);
	DIO_setPinVal(LCD_CONTROL_PORT,LCD_EN_PIN, LOW); //ENABLE low
	DELAY_setTime (2);


#elif LCD_MODE == LCD_8_BIT_MODE
	for (u8 i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_setPinVal(dataPin[i].en_dataPin, ((u8CharCopy >> i)&1) );
	}

	DIO_setPinVal(LCD_EN_PIN, HIGH); //ENABLE high
	DELAY_setTime (2);
	DIO_setPinVal(LCD_EN_PIN, LOW); //ENABLE low
#endif

}


/**
 * @brief This function clears anything on lcd
 *
 * @param void
 *
 * @return Returns void
 */
void LCD_ClrDisplay(void)
{
	LCD_vidWritecmd(LCD_CLEAR_DISPLAY);
	DELAY_setTime (4);
	LCD_vidWritecmd(LCD_CURSOR_HOME);
	DELAY_setTime (4);

}


/**
 * @brief This function  to shift the lcd display from right to left
 *
 * @param void
 *
 * @return Returns void
 */

void LCD_ShiftLeft(void)
{
	LCD_vidWritecmd(LCD_DISPLAY_SHIFT_LEFT);
	DELAY_setTime (1);

}


/**
 * @brief This function  to determine position which char print at this position on lcd
 *
 * @param  row -> take row number 0 or 1
 *         pos -> take colom number from 0 ~ 15
 * @return Returns void
 */


void LCD_gotoXY(u8 row, u8 pos)
{
	if (row==0 && pos < 16)
	{
		LCD_vidWritecmd((pos & 0x0F)| 0x80);
	}
	else if (row==1 && pos < 16)
	{
		LCD_vidWritecmd((pos & 0x0F)| 0xC0);
	}
}



/**
 * @brief This function to write string on lcd
 *
 * @param  str --> which take string as argument
 *
 * @return Returns void
 */


void LCD_WriteString(u8* str)
{
	u16 count = 0;
	u8 string = str[count];
	while(string)
	{
		LCD_vidWriteChar(string);
		string = str[++count];
	}
}

/**
 * @brief This function to write integer number on lcd
 *
 * @param  number --> which take number as argument
 *
 * @return Returns void
 */


void LCD_WriteInt(u32 number)
{
	u8 STR[INDEX];
	itoa(number, STR, 10);
	LCD_WriteString(STR);
}

/**
 * @brief This function to write Arabic string on lcd
 *
 * @param  u8ArCharCopy --> which take string as argument
 *
 * @return Returns void
 */

void LCD_WriteArabic(u8 u8ArCharCopy)
{
	LCD_vidWritecmd(0x04);
	LCD_vidWriteChar(u8ArCharCopy);
}

/**
 * @brief This function to store new pattern on CGRAM
 *
 * @param  pu8custom  -> take pointer to array which having LCD Custom Character Generated data ### take only 8 characters
 * 		   u8Location -> determine location on CGRAM [0 ~ 8]
 *
 * @return Returns void
 */


void LCD_vidCreatCustomChar(u8* pu8custom, u8 u8Location)
{
	if (u8Location < 8)  // CGRAM only store 8 characters
	{
		LCD_vidWritecmd(LCD_SET_CGRAM_ADDR_CMD + (u8Location*8));
		DELAY_setTime (1);
		for (u8 i = 0; i < 8 ; i++)
		{
			LCD_vidWriteChar(pu8custom[i]);
		}
	}
}

/**************************************************************************************************
 * 											END
 *************************************************************************************************/
