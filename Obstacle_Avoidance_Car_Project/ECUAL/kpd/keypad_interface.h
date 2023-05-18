/*
 * keypad_interface.h
 *
 * Created: 5/16/2023 10:55:15 AM
 *  Author: Sarah
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
#include "../../LIB/std.h"
#include "../../MCAL/dio/dio_interface.h"
#include "../../ECUAL/delay/delay_interface.h"

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/

#define LOW 0
#define HIGH 1
#define OUTPUT 0
#define INPUT 1

#define KPD_DEBOUNCE_DELAY 20

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
#define KEYPAD_PORT DIO_PORTC

#define KEYPAD_COLUMN_0 DIO_PIN_5
#define KEYPAD_COLUMN_1 DIO_PIN_6


#define KEYPAD_ROW_0 DIO_PIN_2
#define COL_INIT 0
#define COL_FINAL 1

#define ROW_INIT   4
#define ROW_FINAL  4

#define KPD_KEY_NOT_PRESSED 0
#define KPD_KEY_START 1
#define KPD_KEY_STOP 2

const u8 keypadKeys[2] =
{
        KPD_KEY_START,
        KPD_KEY_STOP
};

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/


/**
 * @brief This function initialize keypad
 *
 * @param void
 *
 * @return Returns void
 */
void KEYPAD_init(void);


/**
 * @brief This function gets keypad value pressed or not pressed
 *
 * @param void
 *
 * @return Returns u8 value of keypad key
 */
u8 KEYPAD_getButton(void);
 



#endif /* KEYPAD_INTERFACE_H_ */