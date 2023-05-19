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
#include "../../ECUAL/delay/delay_interface.h"

/* Macros */
#define MAX_PIN_NUMBER  7
#define MAX_PORT_NUMBER 3

#define BTN_DELAY_BTN_DEBOUNCE      50

#define BTN_DELAY_LONG_PRESS    2000
typedef enum buttonErrors{
	BUTTON_OK,
	WRONG_BUTTON_PORT,
	WRONG_BUTTON_PIN
}en_buttonError_t;
typedef enum buttonPosition{
    BTN_NOT_PRESSED,
    BTN_RELEASED,

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
 * @return Returns Button error
 */
u8 BUTTON_read(en_DIO_port_t en_a_portNumber, u8 u8_a_pinNumber, en_buttonPosition_t * u8Ptr_a_returnedBtnState);



#endif /* BUTTON_INTERFACE_H_ */