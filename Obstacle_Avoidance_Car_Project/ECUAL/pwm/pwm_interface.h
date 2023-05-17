/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *-------------------------------------------------------------------------------------------------------------------
 *		   @Date:  	6:27 PM Sunday, May 14, 2023
 *		   @File:  	pwm_interface.h         
 *		 @Module:  	PWM using normal Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Interfacing file for PWM using normal Timer
 *  
 *********************************************************************************************************************/
#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/timer/timer_interface.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/***************************************_ERROR_TYPES_***************************************/
typedef enum
{
	PWM_OK = 0,
	PWM_NOK
}en_PWM_error_t;

typedef struct
{
	u8	pwmNumber;
	u8	pwmPortNumber; 
	u8	pwmPinNumber;
}st_PWM_config_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
en_PWM_error_t PWM_init	(void);

en_PWM_error_t PWM_setDutyCycle (u8 u8_a_speed);

en_PWM_error_t PWM_start (void);

en_PWM_error_t PWM_stop (void);

void PWM_onTask (void);

void PWM_offTask (void);

#endif /* PWM_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: pwm_interface.h
 *********************************************************************************************************************/