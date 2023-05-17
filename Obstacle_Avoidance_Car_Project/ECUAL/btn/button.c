/*
 * button.c
 *
 * Created: 5/16/2023 1:09:55 PM
 *  Author: Sarah
 */ 
#include "button_interface.h"
/**
 * @brief This function to inialize button
 *
 * @param  u8_a_buttonPort -> define port of button
 * 		   u8_a_buttonPin -> define pins of button
 *
 * @return Returns void
 */
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

          DIO_setPinDir (u8_a_buttonPort,u8_a_buttonPin,INPUT);//argument 
		en_a_error = BUTTON_OK;
	}
	
	return en_a_error;
}
/**
 * @brief This function to read button state
 *
 * @param  u8_a_buttonPort -> define port of button
 * 		   u8_a_buttonPin -> define pins of button
 *         *u8_a_buttonState -> pointer to get button state
 *
 * @return Returns void
 */
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
		        
		 u8 en_buttonPosition_t = NOTPRESSED;
		 u16 u16_l_elapsedTime = 0;
		DIO_getPinVal(u8_a_buttonPort, u8_a_buttonPin, &u8_a_buttonState);
		if(en_buttonPosition_t == PRESSED)
		{
			while(en_buttonPosition_t != NOTPRESSED)
			{
				DELAY_setTime (BTN_DELAY_BTN_POLL);// wait 50ms
				u16_l_elapsedTime += BTN_DELAY_BTN_POLL;
				DIO_getPinVal(u8_a_buttonPort, u8_a_buttonPin, &en_buttonPosition_t);
				if(en_buttonPosition_t == NOTPRESSED && u16_l_elapsedTime < BTN_DELAY_LONG_PRESS)
				{
					// short press
					*u8_a_buttonState = PRESSED;
				}
				if(u16_l_elapsedTime > BTN_DELAY_LONG_PRESS) // long press
				{
					// long press
					*u8_a_buttonState = LONGRELEASED;
					break; // break from state check loop
				}
			}
			}else{
			// not pressed at all
			*u8_a_buttonState = NOTPRESSED;
		}
		en_a_error = BUTTON_OK;
	}
	
	return en_a_error;
}