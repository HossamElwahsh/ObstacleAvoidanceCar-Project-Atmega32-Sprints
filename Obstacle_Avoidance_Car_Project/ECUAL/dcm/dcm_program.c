/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
 *
 *         @Date:  	5:14 PM Monday, May 15, 2023
 *		   @File:  	dcm_program.c         
 *		 @Module:  	DC Motor
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Linking configuration file for DC Motor module     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dcm_interface.h"
#include "dcm_cfg.h"
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const st_DCM_config_t st_DCM_config [NUMBER_OF_DCMS_USED];
 
 /**********************************************************************************************************************
 *  GLOBAL FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/
en_DCM_error_t DCM_init	(void)
{
	en_DCM_error_t returnValue = DCM_OK;
	for (u8 counter = 0; counter < NUMBER_OF_DCMS_USED; counter++)
	{
		if (DIO_setPinDir( st_DCM_config[counter].dcmPortNumber_0, st_DCM_config[counter].dcmPinNumber_0, OUTPUT))
		{
			returnValue = DCM_NOK;
			break;
		}
		else
		{
			/*returnValue = DCM_OK*/
		}
		if (DIO_setPinDir(st_DCM_config[counter].dcmPortNumber_1, st_DCM_config[counter].dcmPinNumber_1, OUTPUT))
		{
			returnValue = DCM_NOK;
			break;
		}
		else
		{
			/*returnValue = DCM_OK*/	
		}
	}
	if (PWM_init())
	{
		returnValue = DCM_NOK;
	}
	else
	{
		/*returnValue = DCM_OK*/
	}
	
	return returnValue;
	
}


en_DCM_error_t DCM_setDirection		(en_DCM_number_t en_a_dcmNumber, en_DCM_direction_t en_a_direction)
{
	en_DCM_error_t returnValue = DCM_OK;
	
	for (u8 counter = 0; counter < NUMBER_OF_DCMS_USED; counter++)
	{
		returnValue = DCM_WRONG_DCM_NUMBER;
		if (en_a_dcmNumber == st_DCM_config[counter].dcmNumber)
		{
			returnValue = DCM_OK;
			switch(en_a_direction)
			{
				
				case DCM_CW:
				if (DIO_setPinVal(st_DCM_config[counter].dcmPortNumber_0, st_DCM_config[counter].dcmPinNumber_0,HIGH))
				{
					returnValue = DCM_NOK;
				}
				else
				{
					/*returnValue = DCM_OK*/
				}
				if (DIO_setPinVal(st_DCM_config[counter].dcmPortNumber_1, st_DCM_config[counter].dcmPinNumber_1,LOW))
				{
					returnValue = DCM_NOK;
				}
				else
				{
					/*returnValue = DCM_OK*/
				}
				break;
				case DCM_ACW:
				if (DIO_setPinVal(st_DCM_config[counter].dcmPortNumber_0, st_DCM_config[counter].dcmPinNumber_0,LOW))
				{
					returnValue = DCM_NOK;
				}
				else
				{
					/*returnValue = DCM_OK*/
				}
				if (DIO_setPinVal(st_DCM_config[counter].dcmPortNumber_1, st_DCM_config[counter].dcmPinNumber_1,HIGH))
				{
					returnValue = DCM_NOK;
				}
				else
				{
					/*returnValue = DCM_OK*/
				}
				break;
				default:
				returnValue = DCM_WRONG_DIRECTION;
				break;
			}
			break;
		}
	}
	return returnValue;
}


en_DCM_error_t DCM_speed (u8 u8_a_speed)
{
	en_DCM_error_t returnValue = DCM_OK;
	
	if (u8_a_speed <= 100)
	{
		if(PWM_setDutyCycle(u8_a_speed))
		{
			returnValue = DCM_NOK;
		}
		else
		{
			/*returnValue = DCM_OK*/
		}
	}
	else
	{
		returnValue = DCM_NOK;
	}
	
	return returnValue;
}


en_DCM_error_t DCM_start (void)
{
	en_DCM_error_t returnValue = DCM_OK;
	
	if (PWM_start())
	{
		returnValue = DCM_NOK;
	}
	else
	{
		/*returnValue = DCM_OK*/
	}
	return returnValue;
}


en_DCM_error_t DCM_stop	(void)
{
	en_DCM_error_t returnValue = DCM_OK;
	
	if (PWM_stop())
	{
		returnValue = DCM_NOK;
	}
	else
	{
		/*returnValue = DCM_OK*/
	}
	
	return returnValue;
}
/**********************************************************************************************************************
 *  END OF FILE: dcm_cfg.c
 *********************************************************************************************************************/
