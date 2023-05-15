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
	TIMER_OK,
	WRONG_TIMER_USED,
	WRONG_DESIRED_TIME
}en_timerError_t;
	
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

en_timerError_t TIMER_init( void );

en_timerError_t TIMER_setTime(u8 u8_a_timerUsed, u32 u32_a_desiredTime);

en_timerError_t TIMER_start(u8 u8_a_timerUsed);

en_timerError_t TIMER_stop(u8 u8_a_timerUsed);

en_timerError_t	TIMER_disableInterrupt(u8 u8_a_timerUsed);

en_timerError_t	TIMER_enableInterrupt(u8 u8_a_timerUsed);

en_timerError_t	TIMER_setCallBack(u8 u8_a_timerUsed, void (*funPtr)(void));

#endif /* TIMER_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: timer_interface.h
 *********************************************************************************************************************/