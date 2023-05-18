/*
 * lcd_interface.h
 *
 * Created: 5/16/2023 10:54:37 AM
 *  Author: Sarah
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

 #include "../../LIB/std.h"
#include "../../MCAL/dio/dio_interface.h"
#include "../../ECUAL/delay/delay_interface.h"
 /**************************************************************************************************
 * 											Macros
 *************************************************************************************************/
#define LCD_8_BIT_MODE				0
#define LCD_4_BIT_MODE				1

#define LCD_POS_0 0
#define LCD_POS_1 1
#define LCD_POS_2 2 
#define LCD_POS_3 3
#define LCD_POS_4 4
#define LCD_POS_5 5
#define LCD_POS_6 6
#define LCD_POS_7 7
#define LCD_POS_8 8
#define LCD_POS_9 9
#define LCD_POS_10 10
#define LCD_POS_11 11
#define LCD_POS_12 12
#define LCD_POS_13 13
#define LCD_POS_14 14
#define LCD_POS_15 15

#define LCD_ROW_0 0
#define LCD_ROW_1 1

#define LCD_MAX_U32_DIGITS 10
/**************************************************************************************************
 * 											functions prototype
 *************************************************************************************************/
/**
 * @brief This function  to set LCD initialization
 *
 * @param void
 *
 * @return Returns void
 */
void LCD_vidInit(void);

/**
 * @brief This function to configure some commands on lcd
 *
 * @param u8commandCopy --> take lcd cmd instructions from instruction table
 *
 * @return Returns void
 */
void LCD_vidWritecmd(u8 u8commandCopy);




/**
 * @brief This function write char on lcd
 *
 * @param u8CharCopy -> take ascii code of char   or   char address on CGROM
 *
 * @return Returns void
 */
void LCD_vidWriteChar(u8 u8CharCopy);


/**
 * @brief This function clears anything on lcd
 *
 * @param void
 *
 * @return Returns void
 */
void LCD_ClrDisplay(void);


/**
 * @brief This function  to shift the lcd display from right to left
 *
 * @param void
 *
 * @return Returns void
 */
void LCD_ShiftLeft(void);


/**
 * @brief This function  to determine position which char print at this position on lcd
 *
 * @param  row -> take row number 0 or 1
 *         pos -> take colom number from 0 ~ 15
 * @return Returns void
 */
void LCD_gotoXY(u8 row, u8 pos);



/**
 * @brief This function to write string on lcd
 *
 * @param  str --> which take string as argument
 *
 * @return Returns void
 */
void LCD_WriteString(u8* str);



/**
 * @brief This function to write integer number on lcd
 *
 * @param  number --> which take number as argument
 *
 * @return Returns void
 */
void LCD_WriteInt(u32 u32_a_number);



/**
 * @brief This function to write Arabic string on lcd
 *
 * @param  u8ArCharCopy --> which take string as argument
 *
 * @return Returns void
 */

void LCD_WriteArabic(u8 u8ArCharCopy);




/**
 * @brief This function to store new pattern on CGRAM
 *
 * @param  pu8custom  -> take pointer to array which having LCD Custom Character Generated data ### take only 8 characters
 * 		   u8Location -> determine location on CGRAM [0 ~ 8]
 *
 * @return Returns void
 */
void LCD_vidCreatCustomChar(u8* pu8custom, u8 u8Location);



#endif /* LCD_INTERFACE_H_ */