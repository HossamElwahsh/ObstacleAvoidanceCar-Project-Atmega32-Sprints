/*
 * lcd_interface.h
 *
 * Created: 5/16/2023 10:54:37 AM
 *  Author: Sarah
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

 
 void LCD_Init(void);
 void LCD_PinsInit ();

 void LCD_WriteChar(u8 u8_a_ch);
 void LCD_WriteString(u8 *u8_a_str);
 void LCD_WriteNumber(i32 i32_a_num);
 void LCD_SetCursor(u8 u8_a_line,u8 u8_a_cell);
 void LCD_Clear(void);
 void LCD_ClearLoc(u8 u8_a_line ,u8 u8_a_cell,u8 u8_a_num);
 void LCD_CustomChar(u8 u8_a_loc,u8 *u8_a_pattern);




#endif /* LCD_INTERFACE_H_ */