/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *-------------------------------------------------------------------------------------------------------------------
 *
 *		   @Date:  	5:34 PM Monday, May 15, 2023
 *		   @File:  	timer_interface.h         
 *		 @Module:  	Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Interfacing file for Timer module     
 *  
 *********************************************************************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/interrupts.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/std.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 
/**************************************_CLOCK_FREQUENCY_USED_************************************/
#define XTAL_FREQ								(F_CPU / 1000000UL)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum timerError{
	TIMER_OK = 0,
	TIMER_WRONG_TIMER_USED,
	TIMER_WRONG_DESIRED_TIME,
	TIMER_NOK
}en_TIMER_error_t;
	
typedef enum
{
	TIMER_0 = 0,
	TIMER_1,
    TIMER_2
}en_TIMER_number_t;

typedef enum
{
	TIMER_OV = 0,
	TIMER_PWM,
    TIMER_CTC
}en_TIMER_waveformUsed_t;

typedef enum
{	
	TIMER_NO_CLK		= 0,
	TIMER_PRESCLNG_1	= 1,
	TIMER_PRESCLNG_8	= 8,
	TIMER_PRESCLNG_64	= 64,
	TIMER_PRESCLNG_256	= 256,
	TIMER_PRESCLNG_1024	= 1024,
	TIMER_XCK_FLNG_EDGE	= 10,
	TIMER_XCK_RSNG_EDGE	= 15
}en_TIMER_prescalerUsed_t;


typedef struct
{
	en_TIMER_number_t			timerUsed;
	en_TIMER_waveformUsed_t		waveformUsed;
	en_TIMER_prescalerUsed_t	prescalerUsed;
}st_TIMER_config_t;


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_init( void )
* @Description     : Initialize Timer according to preprocessed configured definitions
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None		
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_init( void );

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_setTime
*					 (en_TIMER_number_t en_a_timerUsed, f32 f32_a_desiredTime)
* @Description     : set the time at which the timer interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
*					 f32					f32_a_desiredTime
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_setTime(en_TIMER_number_t en_a_timerUsed, f32 f32_a_desiredTime);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_pwmGenerator
*					 (en_TIMER_number_t en_a_timerUsed , u16 u16_a_onTime, u16 u16_a_offTime)
* @Description     : initialize the timer to generates pwm signal using normal mode
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
*					 u16					u16_a_onTime
*					 u16					u16_a_offTime
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_pwmGenerator(en_TIMER_number_t en_a_timerUsed , u16 u16_a_onTime, u16 u16_a_offTime);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_resume(en_TIMER_number_t en_a_timerUsed)
* @Description     : makes the timer to start/resume counting
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_resume(en_TIMER_number_t en_a_timerUsed);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_reset(en_TIMER_number_t en_a_timerUsed)
* @Description     : makes the timer to reset counting from the beginning
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_reset(en_TIMER_number_t en_a_timerUsed);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_getElapsedTime
*					 (en_TIMER_number_t en_a_timerUsed, u32* u32_a_elapsedTime)
* @Description     : returns the elapsed time since the timer started from the beginning
*					 in microseconds
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
* @Parameters (out): u32					u32_a_elapsedTime
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_getElapsedTime(en_TIMER_number_t en_a_timerUsed, u32* u32_a_elapsedTime);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_pause(en_TIMER_number_t en_a_timerUsed)
* @Description     : makes the timer to pause counting
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_pause(en_TIMER_number_t en_a_timerUsed);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_disableInterrupt(en_TIMER_number_t en_a_timerUsed)
* @Description     : Disables timer's interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_disableInterrupt(en_TIMER_number_t en_a_timerUsed);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_enableInterrupt(en_TIMER_number_t en_a_timerUsed)
* @Description     : Enables timer's interrupts
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/				 
en_TIMER_error_t TIMER_enableInterrupt(en_TIMER_number_t en_a_timerUsed);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_setCallBack
*					 (en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void))
* @Description     : sets the call back function for a specific timer
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
*					 void					(*funPtr)(void)
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/				 
en_TIMER_error_t TIMER_setCallBack(en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void));

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_setDelayTime
*					 (en_TIMER_number_t en_a_timerUsed, f32 f32_a_timeInMS)
* @Description     : Set delay time for blocking delay using a specific timer
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
*					 f32					f32_a_timeInMS
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_setDelayTime(en_TIMER_number_t en_a_timerUsed, f32 f32_a_timeInMS);

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_setPwmOnCallBack
*					 (en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void))
* @Description     : Set callback function for the task done while signal is high 
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
*					 void					(*funPtr)(void)
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_setPwmOnCallBack(en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void));

/******************************************************************************
* @Syntax          : en_TIMER_error_t TIMER_setPwmOffCallBack
*					 (en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void))
* @Description     : Set callback function for the task done while signal is low
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_TIMER_number_t		en_a_timerUsed
*					 void					(*funPtr)(void)
* @Parameters (out): None
* @Return value:   : en_TIMER_error_t		TIMER_OK = 0
*											TIMER_WRONG_TIMER_USED = 1
*											TIMER_WRONG_DESIRED_TIME = 2
*											TIMER_NOK = 3
*******************************************************************************/
en_TIMER_error_t TIMER_setPwmOffCallBack(en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void));

#endif /* TIMER_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: timer_interface.h
 *********************************************************************************************************************/
