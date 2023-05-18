/*
 * lcd_config.c
 *
 * Created: 5/16/2023 12:45:32 PM
 *  Author: Sarah
 */ 
#include "lcd_config.h"
//#include "lcd_interface.h"
/**************************************************************************************************
 * 											User Defined Pins
 *************************************************************************************************/
#if LCD_MODE == LCD_4_BIT_MODE


en_DIO_pin_t dataPin[4] = {
		DIO_PIN_4,
		DIO_PIN_5,
		DIO_PIN_6,
		DIO_PIN_7
};

#elif LCD_MODE == LCD_8_BIT_MODE

en_DIO_pin_t dataPin[8] = {
		DIO_PIN_0,
		DIO_PIN_1,
		DIO_PIN_2,
		DIO_PIN_3,
		DIO_PIN_4,
		DIO_PIN_5,
		DIO_PIN_6,
		DIO_PIN_7
};


#endif

/**************************************************************************************************
 * 											END
 *************************************************************************************************/