/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *-------------------------------------------------------------------------------------------------------------------
 *		   @Date:  	6:46 PM Sunday, May 14, 2023
 *		   @File:  	delay_interface.h         
 *		 @Module:  	delay using normal Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Interfacing file for generating Delay using normal Timer
 *  
 *********************************************************************************************************************/
#ifndef DELAY_INTERFACE_H_
#define DELAY_INTERFACE_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
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
	DELAY_OK = 0,
	DELAY_NOK
}en_DELAY_error_t;


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* @Syntax          : en_DELAY_error_t DELAY_init (void)
* @Description     : Initializes delay module
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_DELAY_error_t		DELAY_OK = 0
*											DELAY_NOK = 1
*******************************************************************************/
en_DELAY_error_t DELAY_init	(void);

/******************************************************************************
* @Syntax          : en_DELAY_error_t DELAY_setTime (f32 f32_a_timeInMS)
* @Description     : Sets blocking delay time
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : f32					f32_a_timeInMS
* @Parameters (out): None
* @Return value:   : en_DELAY_error_t		DELAY_OK = 0
*											DELAY_NOK = 1
*******************************************************************************/
en_DELAY_error_t DELAY_setTime (f32 f32_a_timeInMS);

/******************************************************************************
* @Syntax          : en_DELAY_error_t DELAY_setTime (f32 f32_a_timeInMS)
* @Description     : Sets non-blocking delay time
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : f32					f32_a_timeInMS
* @Parameters (out): None
* @Return value:   : en_DELAY_error_t		DELAY_OK = 0
*											DELAY_NOK = 1
*******************************************************************************/
en_DELAY_error_t DELAY_setTimeNonBlocking (f32 f32_a_timeInMs);

/******************************************************************************
* @Syntax          : en_DELAY_error_t DELAY_setCallBack (void (*funPtr)(void))
* @Description     : Sets call back for the function which gonna be performed
*					 when the nonblocking delay times out
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : void					(*funPtr)(void)
* @Parameters (out): None
* @Return value:   : en_DELAY_error_t		DELAY_OK = 0
*											DELAY_NOK = 1
*******************************************************************************/
en_DELAY_error_t DELAY_setCallBack (void (*funPtr)(void));
#endif /* DELAY_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: delay_interface.h
 *********************************************************************************************************************/




