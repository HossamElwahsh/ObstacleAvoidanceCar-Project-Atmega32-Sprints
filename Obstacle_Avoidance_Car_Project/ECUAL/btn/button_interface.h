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
/**
 * @brief This function to inialize button
 *
 * @param  u8_a_buttonPort -> define port of button
 * 		   u8_a_buttonPin -> define pins of button
 *
 * @return Returns void
 */
en_buttonError_t BUTTON_init(u8 u8_a_buttonPort, u8 u8_a_buttonPin);
/**
 * @brief This function to read button state
 *
 * @param  u8_a_buttonPort -> define port of button
 * 		   u8_a_buttonPin -> define pins of button
 *         *u8_a_buttonState -> pointer to get button state
 *
 * @return Returns void
 */
en_buttonError_t BUTTON_read(u8 u8_a_buttonPort, u8 u8_a_buttonPin, u8 *u8_a_buttonState);



#endif /* BUTTON_INTERFACE_H_ */