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
/**************************************************************************************************
 * 											functions prototype
 *************************************************************************************************/
/*
 * function		: HLCD_vidInit
 * description 	: func to set LCD initialization
 * input param 	: void
 * return		: void
 * */
void LCD_vidInit(void);

/*
 * function		: HLCD_vidWritecmd
 * description 	: func to configure some commands on lcd
 * input param 	:
 * 					u8commandCopy --> take lcd cmd instructions from instruction table <https://components101.com/sites/default/files/component_datasheet/16x2%20LCD%20Datasheet.pdf>
 * return		: void
 * */
void HLCD_vidWritecmd(u8 u8commandCopy);



/*
 * function		: HLCD_vidWriteChar
 * description 	: func to write char on lcd
 * input param 	: u8CharCopy -> take ascii code of char   or   char address on CGROM
 * return		: void
 * */
void LCD_vidWriteChar(u8 u8CharCopy);


/*
 * function		: HLCD_ClrDisplay
 * description 	: func to clear anything on lcd
 * input param 	: void
 * return		: void
 * */
void LCD_ClrDisplay(void);


/*
 * function		: HLCD_ShiftLeft
 * description 	: func to shift the lcd display from right to left
 * input param 	: void
 * return		: void
 * */
void LCD_ShiftLeft(void);


/*
 * function		: HLCD_gotoXY
 * description 	: func to determine position which char print at this position on lcd  ### NOTE : (2rows x 16coloms)
 * input param 	:
 * 				  row -> take row number 0 or 1
 * 				  pos -> take colom number from 0 ~ 15
 * return		: void
 * */
void HLCD_gotoXY(u8 row, u8 pos);


/*
 * function		: HLCD_WriteString
 * description 	: func to write string on lcd
 * input param 	: str --> which take string as argument
 * return		: void
 * */
void LCD_WriteString(u8* str);



/*
 * function		: HLCD_WriteInt
 * description 	: func to write integer number on lcd
 * input param 	: number --> which take number as argument
 * return		: void
 * */
void LCD_WriteInt(u32 number);



/*
 * function		: HLCD_WriteArabic
 * description 	: func to write Arabic string on lcd
 * input param 	: u8ArCharCopy --> which take string as argument
 * return		: void
 * */
void LCD_WriteArabic(u8 u8ArCharCopy);




/*
 * function		: HLCD_vidCreatCustomChar
 * description 	: func to store new patterm on CGRAM
 * input param 	:
 * 				  pu8custom  -> take pointer to array which having LCD Custom Character Generated data ### take only 8 characters
 * 				  u8Location -> determine location on CGRAM [0 ~ 8]
 * return		: void
 * */
void LCD_vidCreatCustomChar(u8* pu8custom, u8 u8Location);



#endif /* LCD_INTERFACE_H_ */