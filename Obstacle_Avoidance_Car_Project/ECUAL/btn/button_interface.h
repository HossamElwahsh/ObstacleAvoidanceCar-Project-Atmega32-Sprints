/*
 * button_interface.h
 *
 * Created: 5/16/2023 11:01:09 AM
 *  Author: Sarah
 */ 


#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_
#include "../../LIB/std.h"
#include "../../MCAL/dio/dio_interface.h"

#define BTN_DELAY_BTN_POLL      50

#define BTN_DELAY_LONG_PRESS    2000
typedef enum buttonErrors{
	BUTTON_OK,
	WRONG_BUTTON_PORT,
	WRONG_BUTTON_PIN
}en_buttonError_t;
typedef enum buttonPosition{
	PRESSED,
	NOTPRESSED,
	LONGRELEASED
	
}en_buttonPosition_t;
/* 
* Parameters
*       	 u8_a_buttonPort:  read port number.
*       	 u8_a_buttonPin :  read pin number .
* Return
*   	en_buttonError_t if the button state was read successfully, 
*/
en_buttonError_t BUTTON_init(u8 u8_a_buttonPort, u8 u8_a_buttonPin);
/*
* Parameters
*       	 u8_a_buttonPort:  read port number.
*       	 u8_a_buttonPin :  read pin number .
             u8_a_buttonState: pionter to read button state
* Return
*   	en_buttonError_t if the button state was read successfully,
*/
en_buttonError_t BUTTON_read(u8 u8_a_buttonPort, u8 u8_a_buttonPin, u8 *u8_a_buttonState);



#endif /* BUTTON_INTERFACE_H_ */