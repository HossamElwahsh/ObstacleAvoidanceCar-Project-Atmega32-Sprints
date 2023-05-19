/*
 * lcd_config.h
 *
 * Created: 5/16/2023 12:43:33 PM
 *  Author: Sarah
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
#include "lcd_interface.h"
/**************************************************************************************************
  * 											Macros
  *************************************************************************************************/
/*
 * Choosing LCD mode:
 *
 * 		LCD_4_BIT_MODE  for 4 bit mode
 * 		LCD_8_BIT_MODE  for 8 bit mode
 */
#define LCD_PORT        DIO_PORTD

#define LCD_MODE		LCD_4_BIT_MODE
/*************************************************************************************************/
#define LOW 0
#define HIGH 1

#define LCD_DATA_PORT		DIO_PORTA
#define LCD_CONTROL_PORT	DIO_PORTA

#define LCD_RS_PIN			DIO_PIN_1
#define LCD_RW_PIN			DIO_PIN_2
#define LCD_EN_PIN			DIO_PIN_3
/*************************************************************************************************/

#if LCD_MODE == LCD_4_BIT_MODE

#define DATA_PIN_NUMBER		4

#elif LCD_MODE == LCD_8_BIT_MODE

#define DATA_PIN_NUMBER		8


#endif
/*************************************************************************************************/


 /**************************************************************************************************
  * 									User Defined Data types
  *************************************************************************************************/
// typedef struct
// { 
// 	en_DIO_pin_t en_dataPin;
// 
// }st_lcdDataPin_t;



#endif /* LCD_CONFIG_H_ */