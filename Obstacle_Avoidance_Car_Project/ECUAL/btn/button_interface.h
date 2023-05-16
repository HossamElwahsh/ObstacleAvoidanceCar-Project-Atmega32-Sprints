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

#define BUTTON_1_PORT	PORT_B
#define BUTTON_1_Pin	2

typedef enum buttonErrors{
	BUTTON_OK,
	WRONG_BUTTON_PORT,
	WRONG_BUTTON_PIN
}en_buttonError_t;

en_buttonError_t BUTTON_init(u8 u8_a_buttonPort, u8 u8_a_buttonPin);

en_buttonError_t BUTTON_read(u8 u8_a_buttonPort, u8 u8_a_buttonPin, u8 *u8_a_buttonState);



#endif /* BUTTON_INTERFACE_H_ */