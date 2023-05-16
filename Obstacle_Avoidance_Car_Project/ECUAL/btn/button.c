/*
 * button.c
 *
 * Created: 5/16/2023 1:09:55 PM
 *  Author: Sarah
 */ 
#include "button_interface.h"
en_buttonError_t BUTTON_init(u8 u8_a_buttonPort, u8 u8_a_buttonPin)
{
	en_buttonError_t en_a_error = BUTTON_OK;
	if (u8_a_buttonPort > DIO_PORTD)
	{
		en_a_error = WRONG_BUTTON_PORT;
	}
	else if (u8_a_buttonPin > 7)
	{
		en_a_error = WRONG_BUTTON_PIN;
	}
	else
	{

          DIO_setPinDir (DIO_PORTB,DIO_PIN_2,INPUT);
		en_a_error = BUTTON_OK;
	}
	
	return en_a_error;
}

en_buttonError_t BUTTON_read(u8 u8_a_buttonPort, u8 u8_a_buttonPin, u8 *u8_a_buttonState)
{
	en_buttonError_t en_a_error = BUTTON_OK;
	if (u8_a_buttonPort > DIO_PORTD)
	{
		en_a_error = WRONG_BUTTON_PORT;
	}
	else if (u8_a_buttonPin > 7)
	{
		en_a_error = WRONG_BUTTON_PIN;
	}
	else
	{
		DIO_getPinVal(u8_a_buttonPort, u8_a_buttonPin, u8_a_buttonState);
		en_a_error = BUTTON_OK;
	}
	
	return en_a_error;
}