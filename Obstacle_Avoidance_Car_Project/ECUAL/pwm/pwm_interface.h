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
/******************************************************************************
* @Syntax          : en_PWM_error_t PWM_init (void)
* @Description     : Initializes PWM module
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_PWM_error_t			PWM_OK = 0
*											PWM_NOK = 1
*******************************************************************************/
en_PWM_error_t PWM_init	(void);

/******************************************************************************
* @Syntax          : en_PWM_error_t PWM_setDutyCycle (u8 u8_a_speed)
* @Description     : Sets PWM duty cycle
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : u8						u8_a_speed
* @Parameters (out): None
* @Return value:   : en_PWM_error_t			PWM_OK = 0
*											PWM_NOK = 1
*******************************************************************************/
en_PWM_error_t PWM_setDutyCycle (u8 u8_a_speed);

/******************************************************************************
* @Syntax          : en_PWM_error_t PWM_start (void)
* @Description     : Starts PWM
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_PWM_error_t			PWM_OK = 0
*											PWM_NOK = 1
*******************************************************************************/
en_PWM_error_t PWM_start (void);

/******************************************************************************
* @Syntax          : en_PWM_error_t PWM_stop (void)
* @Description     : Stops PWM
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_PWM_error_t			PWM_OK = 0
*											PWM_NOK = 1
*******************************************************************************/
en_PWM_error_t PWM_stop (void);

/******************************************************************************
* @Syntax          : en_PWM_error_t PWM_onTask (void)
* @Description     : task called by the interrupt when the signal is in HIGH phase
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_PWM_error_t			PWM_OK = 0
*											PWM_NOK = 1
*******************************************************************************/
void PWM_onTask (void);

/******************************************************************************
* @Syntax          : en_PWM_error_t PWM_onTask (void)
* @Description     : task called by the interrupt when the signal is in LOW phase
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_PWM_error_t			PWM_OK = 0
*											PWM_NOK = 1
*******************************************************************************/
void PWM_offTask (void);

#endif /* PWM_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: pwm_interface.h
 *********************************************************************************************************************/