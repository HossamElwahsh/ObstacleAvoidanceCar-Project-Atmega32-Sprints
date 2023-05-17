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

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/

#define LOW 0
#define HIGH 1
#define OUTPUT 0
#define INPUT 1

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
const u8 keypad[1][2] =
{
	{'start','stop'},
	
};

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/


/**
 * @brief This function inialize keypad
 *
 * @param void
 *
 * @return Returns void
 */
void KEYPAD_Init(void);


/**
 * @brief This function gets keypad value pressed or not pressed
 *
 * @param void
 *
 * @return Returns u8 : value of keypad
 */
u8 KEYPAD_GetValue(void);
 



#endif /* KEYPAD_INTERFACE_H_ */