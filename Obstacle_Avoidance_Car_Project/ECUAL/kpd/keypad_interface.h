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


/*************************************************************************************************************
 *
 Name : KEYPAD_init() 
 Description : This Function Initializes keypad pins (Rows are outputs & Columns are inputs).
 ARGS : void
 return : void   
 ************************************************************************************************************/
void KEYPAD_Init(void);


/*************************************************************************************************************
 *
 Name : KEYPAD_GetButton 
 Description : This Function loops over other three functions (Checks (R1,R2,R3)).
 ARGS : void
 return : the pressed key or Nothing pressed   
 ************************************************************************************************************/
u8 KEYPAD_GetValue(void);
 



#endif /* KEYPAD_INTERFACE_H_ */