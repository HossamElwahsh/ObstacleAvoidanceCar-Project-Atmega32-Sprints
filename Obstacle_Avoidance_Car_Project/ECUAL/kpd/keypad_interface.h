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
typedef enum EN_KEYPAD_BTNS
{
	KEY_INCREAMENT=0,
	KEY_DECREAMENT,
	KEY_SET,
	KEY_ADJUST,
	KEY_RESET,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_NOTHING
	
}EN_KEYPAD_BTNS;

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

void KEYPAD_init(void);


/*************************************************************************************************************
 *
 Name : KEYPAD_GetButton 
 Description : This Function loops over other three functions (Checks (R1,R2,R3)).
 ARGS : void
 return : the pressed key or Nothing pressed   
 ************************************************************************************************************/

EN_KEYPAD_BTNS KEYPAD_GetButton(void);
/*************************************************************************************************************
 *
 Name : KEYPAD_checkR1 ,  KEYPAD_checkR2, KEYPAD_checkR3
 Description : functions are checking the entire row if it pressed or not.
 ARGS : void
 return : the pressed key or Nothing pressed   
 ************************************************************************************************************/

EN_KEYPAD_BTNS KEYPAD_checkR1(void);
EN_KEYPAD_BTNS KEYPAD_checkR2(void);
EN_KEYPAD_BTNS KEYPAD_checkR3(void);


#endif /* KEYPAD_INTERFACE_H_ */