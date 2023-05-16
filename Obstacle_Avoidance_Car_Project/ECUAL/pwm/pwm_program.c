/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
 *
 *         @Date:  	11:53 PM Monday, May 15, 2023
 *		   @File:  	pwm_program.c         
 *		 @Module:  	PWM generated by timer on normal mode
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Program file for PWM generated by timer on normal mode
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "pwm_interface.h"
#include "pwm_cfg.h"
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 extern const st_PWM_config_t st_PWM_config [NUMBER_OF_PWM_PINS];
/**********************************************************************************************************************
 *  GLOBAL FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/
en_PWM_error_t PWM_init	(void)
{
	en_PWM_error_t returnValue = PWM_OK;
	
	for (u8 counter = 0; counter < NUMBER_OF_PWM_PINS; counter++)
	{
		if (DIO_setPinDir( st_PWM_config[counter].pwmPortNumber, st_PWM_config[counter].pwmPinNumber, OUTPUT))
		{
			 returnValue = PWM_NOK;
			 break;
		}
		else
		{
			 /*returnValue = PWM_OK;*/
		}
	}
	
	 
	if ( TIMER_init() )
	{
		returnValue = PWM_NOK;
	}
	else
	{
		/*returnValue = PWM_OK;*/
	}
	if ( TIMER_enableInterrupt(PWM_TIMER_USED) )
	{
		returnValue = PWM_NOK;
	}
	else
	{
		/*returnValue = PWM_OK;*/
	}
	if ( TIMER_pause(PWM_TIMER_USED) )
	{
		returnValue = PWM_NOK;
	}
	else
	{
		/*returnValue = PWM_OK;*/
	}
	return returnValue;
}

en_PWM_error_t PWM_setDutyCycle (u8 u8_a_speed)
{
	u16 u16_a_onTime = 0, u16_a_offTime	= 0;
	en_PWM_error_t returnValue = PWM_OK;
	
	u16_a_onTime	 = (((u32)u8_a_speed * 256)/100);
	u16_a_offTime	 = 256 - u16_a_onTime;
	
	if ( TIMER_pwmGenerator(PWM_TIMER_USED , u16_a_onTime, u16_a_offTime) )
	{
		returnValue = PWM_NOK;
	}
	else
	{
		/*returnValue = PWM_OK;*/
	}
	return returnValue;
}

en_PWM_error_t PWM_start (void)
{
	en_PWM_error_t returnValue = PWM_OK;
	
	if ( TIMER_resume(PWM_TIMER_USED) )
	{
		returnValue = PWM_NOK;
	}
	else
	{
		/*returnValue = PWM_OK;*/
	}
	
	return returnValue;
}

en_PWM_error_t PWM_stop (void)
{
	en_PWM_error_t returnValue = PWM_OK;
	
	if ( TIMER_stop(PWM_TIMER_USED) )
	{
		returnValue = PWM_NOK;
	}
	else
	{
		/*returnValue = PWM_OK;*/
	}
	
	for (u8 counter = 0; counter < NUMBER_OF_PWM_PINS; counter++)
	{
		if (DIO_setPinVal( st_PWM_config[counter].pwmPortNumber, st_PWM_config[counter].pwmPinNumber, LOW))
		{
			returnValue = PWM_NOK;
			break;
		}
		else
		{
			/*returnValue = PWM_OK;*/
		}
	}
	
	return returnValue;
}
/**********************************************************************************************************************
 *  END OF FILE: pwm_program.c
 *********************************************************************************************************************/
