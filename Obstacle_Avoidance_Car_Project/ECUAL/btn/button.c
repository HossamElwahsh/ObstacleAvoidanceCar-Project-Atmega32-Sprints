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
    DELAY_init();
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
u8 BUTTON_read(en_DIO_port_t en_a_portNumber, u8 u8_a_pinNumber, en_buttonPosition_t * u8Ptr_a_returnedBtnState) {
    /* Define local variable to set the error state = OK */

    /* Check 1: MBTN is in the valid range, and Pointer is not equal to NULL */
    if ((u8_a_pinNumber <= MAX_PIN_NUMBER) && (en_a_portNumber <= MAX_PORT_NUMBER) && (u8Ptr_a_returnedBtnState != NULL))
    {

        u8 u8_l_mBtnState = LOW;
        DIO_getPinVal(en_a_portNumber, u8_a_pinNumber, &u8_l_mBtnState);
        if(u8_l_mBtnState == HIGH)
        {
            DELAY_setTime(BTN_DELAY_BTN_DEBOUNCE);
            DIO_getPinVal(en_a_portNumber, u8_a_pinNumber, &u8_l_mBtnState);
            if(u8_l_mBtnState == HIGH)
            {
                while(u8_l_mBtnState == HIGH)
                {
                    DIO_getPinVal(en_a_portNumber, u8_a_pinNumber, &u8_l_mBtnState);
                }
                DELAY_setTime(BTN_DELAY_BTN_DEBOUNCE);
                DIO_getPinVal(en_a_portNumber, u8_a_pinNumber, &u8_l_mBtnState);
                if(u8_l_mBtnState == LOW)
                {
                    *u8Ptr_a_returnedBtnState = BTN_RELEASED;
                }
                return STD_OK;
            }
        }
        *u8Ptr_a_returnedBtnState = BTN_NOT_PRESSED;
        return STD_OK;
    }
    else {
        /* Update error state = NOK, wrong BTNId or Pointer is NULL! */
        return STD_NOK;
    }
}