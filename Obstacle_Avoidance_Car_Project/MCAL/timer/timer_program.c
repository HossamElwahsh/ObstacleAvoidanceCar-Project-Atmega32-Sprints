/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
 *
 *         @Date:  	5:34 PM Monday, May 15, 2023
 *		   @File:  	timer_cfg.c         
 *		 @Module:  	Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Program file for Timer module     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "timer_interface.h"
#include "timer_cfg.h"
#include "timer_private.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const st_TIMER_config_t st_TIMER_config [NUMBER_OF_TIMERS_USED];

void (*TIMER_0_callBack) (void) = NULL_PTR;

void (*TIMER_1_callBack) (void) = NULL_PTR;

void (*TIMER_2_callBack) (void) = NULL_PTR;

void (*TIMER_0_pwmOnCallBack) (void) = NULL_PTR;

void (*TIMER_0_pwmOffCallBack) (void) = NULL_PTR;


u32 u32_g_timer0NumberOfOVFs	=	0;

u8  u8_g_timer0RemTicks		=	0;

u16 u16_g_offTime0			=	0;

u16 u16_g_onTime0			=	0;

volatile u32 u32_g_timer0OVFCounter	=	0;

u32 u32_g_timer1NumberOfOVFs	=	0;

u16 u16_g_timer1RemTicks		=	0;

u32 u32_g_offTime1			=	0;

u32 u32_g_onTime1			=	0;

volatile u32 u32_g_timer1OVFCounter	=	0;

u32 u32_g_timer2NumberOfOVFs	=	0;

u32 u8_g_timer2RemTicks		=	0;

u16 u16_g_offTime2			=	0;

u16 u16_g_onTime2			=	0;

volatile u32 u32_g_timer2OVFCounter	=	0;

u8 u8_g_normalToPwm		=	0;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/
en_TIMER_error_t TIMER_init( void )
{
	en_TIMER_error_t returnValue = TIMER_OK;
	
	for (u8 counter = 0; counter < NUMBER_OF_TIMERS_USED; counter++)
	{
		switch(st_TIMER_config[counter].timerUsed)
		{
			case TIMER_0:
			switch(st_TIMER_config[counter].waveformUsed)
			{
				case TIMER_OV:
				/*Choosing Normal Mode*/
				CLR_BIT(TCCR0,WGM01); CLR_BIT(TCCR0,WGM00);
				/*Enabling OVF Interrupt 0*/
				//SET_BIT(TIMSK,TOIE0);
				break;
				
				case TIMER_CTC:
				/*Choosing CTC Mode*/
				SET_BIT(TCCR0,WGM01); CLR_BIT(TCCR0,WGM00);
				/*Enabling CTC Interrupt 0*/
				SET_BIT(TIMSK,OCIE0);
				break;
				
				case TIMER_PWM:
				/*TO BE IMPLEMENTED*/
				break;
				
				default:
				returnValue = TIMER_NOK;
				break;
			}
			break;
			
			case TIMER_1:
			switch(st_TIMER_config[counter].waveformUsed)
			{
				case TIMER_OV:
				CLR_BIT(TCCR1A,COM1A1);
				CLR_BIT(TCCR1A,COM1A0);
				
				CLR_BIT(TCCR1B,WGM13);
				CLR_BIT(TCCR1B,WGM12);
				CLR_BIT(TCCR1A,WGM11);
				CLR_BIT(TCCR1A,WGM10);
				
				//SET_BIT(TIMSK, TOIE1);
				break;
				
				case TIMER_CTC:
				break;
				
				case TIMER_PWM:
				break;
				
				default:
				returnValue = TIMER_NOK;
				break;
			}
			break;
			
			case TIMER_2:
			switch(st_TIMER_config[counter].waveformUsed)
			{
				case TIMER_OV:
				/*Choosing Normal Mode*/
				CLR_BIT(TCCR2,WGM21); CLR_BIT(TCCR2,WGM20);
				/*Enabling OVF Interrupt 0*/
				//SET_BIT(TIMSK,TOIE2);
				break;
				
				case TIMER_CTC:
				/*Choosing CTC Mode*/
				SET_BIT(TCCR0,WGM21); CLR_BIT(TCCR0,WGM20);
				/*Enabling CTC Interrupt 0*/
				SET_BIT(TIMSK,OCIE2);
				break;
				
				case TIMER_PWM:
				/*TO BE IMPLEMENTED*/
				break;
				
				default:
				returnValue = TIMER_NOK;
				break;
			}
			break;
			default:
			returnValue =  TIMER_WRONG_TIMER_USED;
			break;
		}
		if (returnValue)
		{
			break;
		}
	}
	/*Enabling Global Interrupt*/
	SET_BIT(SREG, Ibit);
	
	return returnValue;
}

en_TIMER_error_t TIMER_setTime(en_TIMER_number_t en_a_timerUsed, f32 f32_a_desiredTime)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	u32 tickTime = 0;
	u32 numberOfTicks = 0;
	u16 TCNTValue = 0;
	
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		switch(st_TIMER_config[en_a_timerUsed].waveformUsed)
		{
			case TIMER_OV:
			tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
			numberOfTicks = ((f32_a_desiredTime*1000)/tickTime);
			
			u32_g_timer0NumberOfOVFs = numberOfTicks / 256;
			u8_g_timer0RemTicks = numberOfTicks % 256;
			
			if (u8_g_timer0RemTicks)
			{
				TCNT0 = 256 - u8_g_timer0RemTicks;
				u32_g_timer0NumberOfOVFs++;
			}
			break;
			
			case TIMER_CTC:
			/*TO BE IMPLEMENTED*/
			break;
			
			case TIMER_PWM:
			/*DO NOTHING*/
			break;
			
			default:
			returnValue = TIMER_NOK;
			break;
		}
		break;
		
		case TIMER_1:
		switch(st_TIMER_config[en_a_timerUsed].waveformUsed)
		{
			case TIMER_OV:
			tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
			numberOfTicks = ((f32_a_desiredTime*1000)/tickTime);
			
			u32_g_timer1NumberOfOVFs = numberOfTicks / 65536;
			u16_g_timer1RemTicks = numberOfTicks % 65536;
			
			if (u16_g_timer1RemTicks)
			{
				TCNTValue = 65536 - u16_g_timer1RemTicks;
				
				TCNT1L |= TCNTValue;
				TCNT1H |= (TCNTValue>>8);
				
				u32_g_timer2NumberOfOVFs++;
			}
			break;
			
			case TIMER_CTC:
			/*TO BE IMPLEMENTED*/
			break;
			
			case TIMER_PWM:
			/*DO NOTHING*/
			break;
			
			default:
			returnValue = TIMER_NOK;
			break;
		}
		break;
		
		case TIMER_2:
		switch(st_TIMER_config[en_a_timerUsed].waveformUsed)
		{
			case TIMER_OV:
			tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
			numberOfTicks = ((f32_a_desiredTime*1000)/tickTime);
			
			u32_g_timer2NumberOfOVFs = numberOfTicks / 256;
			u8_g_timer2RemTicks = numberOfTicks % 256;
			
			if (u8_g_timer2RemTicks)
			{
				TCNT2 = 256 - u8_g_timer2RemTicks;
				u32_g_timer2NumberOfOVFs++;
			}
			break;
			
			case TIMER_CTC:
			/*TO BE IMPLEMENTED*/
			break;
			
			case TIMER_PWM:
			/*DO NOTHING*/
			break;
			
			default:
			returnValue = TIMER_NOK;
			break;
		}
		break;
		
		default:
		returnValue =  TIMER_WRONG_TIMER_USED;
		break;
		
	}
	return returnValue;
}

en_TIMER_error_t TIMER_pwmGenerator(en_TIMER_number_t en_a_timerUsed , u16 u16_a_onTime, u16 u16_a_offTime)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		u16_g_offTime0	= u16_a_offTime;
		u16_g_onTime0	= u16_a_onTime;
		break;
		
		case TIMER_1:
		u32_g_offTime1	= u16_a_offTime;
		u32_g_onTime1	= u16_a_onTime;
		break;
		
		case TIMER_2:
		u16_g_offTime2	= u16_a_offTime;
		u16_g_onTime2	= u16_a_onTime;
		break;
		
		default:
		returnValue =  TIMER_WRONG_TIMER_USED;
		break;
		
	}
	if(returnValue == TIMER_OK)
	{
		u8_g_normalToPwm = 1;
	}
	return returnValue;
}

en_TIMER_error_t TIMER_resume(en_TIMER_number_t en_a_timerUsed)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		switch(st_TIMER_config[TIMER_0].prescalerUsed)
		{
			case TIMER_PRESCLNG_1:
			CLR_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_8:
			CLR_BIT(TCCR0, CS02);	SET_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_64:
			CLR_BIT(TCCR0, CS02);	SET_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_256:
			SET_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);
			break;
			
			case TIMER_PRESCLNG_1024:
			SET_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	SET_BIT(TCCR0, CS00);
			break;
			
			default: returnValue = TIMER_NOK;	break;
		}
		break;
		
		case TIMER_1:
		switch(st_TIMER_config[TIMER_1].prescalerUsed)
		{
			case TIMER_PRESCLNG_1:
			CLR_BIT(TCCR1B, CS12);	CLR_BIT(TCCR1B, CS11);	SET_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_8:
			CLR_BIT(TCCR1B, CS12);	SET_BIT(TCCR1B, CS11);	CLR_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_64:
			CLR_BIT(TCCR1B, CS12);	SET_BIT(TCCR1B, CS11);	SET_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_256:
			SET_BIT(TCCR1B, CS12);	CLR_BIT(TCCR1B, CS11);	CLR_BIT(TCCR1B, CS10);
			break;
			
			case TIMER_PRESCLNG_1024:
			SET_BIT(TCCR1B, CS12);	CLR_BIT(TCCR1B, CS11);	SET_BIT(TCCR1B, CS10);
			break;
			
			default: returnValue = TIMER_NOK;	break;
		}
		break;
		
		case TIMER_2:
		switch(st_TIMER_config[TIMER_1].prescalerUsed)
		{
			case TIMER_PRESCLNG_1:
			CLR_BIT(TCCR2,CS22); CLR_BIT(TCCR2,CS21);	SET_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_8:
			CLR_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_64:
			SET_BIT(TCCR2,CS22); CLR_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_256:
			SET_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	CLR_BIT(TCCR2,CS20);
			break;
			
			case TIMER_PRESCLNG_1024:
			SET_BIT(TCCR2,CS22); SET_BIT(TCCR2,CS21);	SET_BIT(TCCR2,CS20);
			break;
			
			default: returnValue = TIMER_NOK;	break;
		}
		break;
		default:
		returnValue =  TIMER_NOK;
		break;
		
	}
	return returnValue;
}

en_TIMER_error_t TIMER_reset(en_TIMER_number_t en_a_timerUsed)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		TIMER_pause(en_a_timerUsed);
		u32_g_timer0OVFCounter = 0;
		TCNT0 = 0;
//		TIMER_resume(en_a_timerUsed);
		break;
		
		case TIMER_1:
		TIMER_pause(en_a_timerUsed);
		u32_g_timer1OVFCounter = 0;
		TCNT1 = 0;
		//TIMER_resume(en_a_timerUsed);
		break;
		
		case TIMER_2:
		TIMER_pause(en_a_timerUsed);
		u32_g_timer2OVFCounter = 0;
		TCNT2 = 0;
		//TIMER_resume(en_a_timerUsed);
		break;
		
		default:
		returnValue =  TIMER_WRONG_TIMER_USED;
		break;
		
	}
	return returnValue;
	
}

en_TIMER_error_t TIMER_getElapsedTime(en_TIMER_number_t en_a_timerUsed, u32* u32_a_elapsedTime)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	u32 tickTime = 0;
	u32 numberOfTicks = 0;
	u16 TCNTValue = 0;
	
	
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
		TCNTValue = TCNT0;
		numberOfTicks = TCNTValue + (u32_g_timer0OVFCounter * 256);
		*u32_a_elapsedTime = ((f32)numberOfTicks) * tickTime;
		//*u32_a_elapsedTime /= 1000;
		break;
		
		case TIMER_1:
		tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
		TCNTValue = ((u16)TCNT1H * 256) + TCNT1L;
		//TCNTValue = TCNT1;
		numberOfTicks = TCNTValue + (u32_g_timer1OVFCounter * 65536);
		*u32_a_elapsedTime = ((f32)numberOfTicks) * tickTime;
		//*u32_a_elapsedTime /= 1000;
		break;
		
		case TIMER_2:
		tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
		TCNTValue = TCNT2;
		numberOfTicks = TCNTValue + (u32_g_timer2OVFCounter * 256);
		*u32_a_elapsedTime = ((f32)numberOfTicks)* tickTime;
		//*u32_a_elapsedTime /= 1000;
		break;
		
		default:
		returnValue =  TIMER_WRONG_TIMER_USED;
		break;
		
	}
	return returnValue;
}

en_TIMER_error_t TIMER_pause(en_TIMER_number_t en_a_timerUsed)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		CLR_BIT(TCCR0, CS02);	CLR_BIT(TCCR0, CS01);	CLR_BIT(TCCR0, CS00);	break;
		
		case TIMER_1:
		CLR_BIT(TCCR1B,CS12);	CLR_BIT(TCCR1B,CS11);	CLR_BIT(TCCR1B,CS10);	break;
		
		case TIMER_2:
		CLR_BIT(TCCR2, CS22);	CLR_BIT(TCCR2, CS21);	CLR_BIT(TCCR2, CS20);	break;
		
		default:	
		returnValue =			TIMER_WRONG_TIMER_USED;							break;
		
	}
	return returnValue;
}

en_TIMER_error_t TIMER_disableInterrupt(en_TIMER_number_t en_a_timerUsed)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	switch(en_a_timerUsed)
	{
		case TIMER_0:	CLR_BIT(TIMSK,TOIE0);				break;
		
		case TIMER_1:	CLR_BIT(TIMSK,TOIE1);				break;
		
		case TIMER_2:	CLR_BIT(TIMSK,TOIE2);				break;
		
		default:	returnValue =  TIMER_WRONG_TIMER_USED;	break;
		
	}
	return returnValue;
}

en_TIMER_error_t TIMER_enableInterrupt(en_TIMER_number_t en_a_timerUsed)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	switch(en_a_timerUsed)
	{
		case TIMER_0:	SET_BIT(TIMSK,TOIE0);				break;
		
		case TIMER_1:	SET_BIT(TIMSK,TOIE1);				break;
		
		case TIMER_2:	SET_BIT(TIMSK,TOIE2);				break;
		
		default:	returnValue =  TIMER_WRONG_TIMER_USED;	break;
		
	}
	return returnValue;
}

en_TIMER_error_t TIMER_setCallBack(en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void))
{
	en_TIMER_error_t returnValue = TIMER_OK;
	
	if(funPtr != NULL_PTR)	
	{	
		switch(en_a_timerUsed)
		{
			case TIMER_0:	TIMER_0_callBack = funPtr;			break;
			
			case TIMER_1:	TIMER_1_callBack = funPtr;			break;
			
			case TIMER_2:	TIMER_2_callBack = funPtr;			break;
			
			default:	returnValue = TIMER_WRONG_TIMER_USED;	break;
		}
	}
	else
	{
		returnValue = TIMER_NOK;
	}
	return returnValue;
}

en_TIMER_error_t TIMER_setPwmOnCallBack(en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void))
{
	en_TIMER_error_t returnValue = TIMER_OK;
	
	if(funPtr != NULL_PTR)
	{
		switch(en_a_timerUsed)
		{
			case TIMER_0:	TIMER_0_pwmOnCallBack = funPtr;			break;
			
			case TIMER_1:	/*TO BE IMPLEMENTED*/				break;
			
			case TIMER_2:	/*TO BE IMPLEMENTED*/				break;
			
			default:	returnValue = TIMER_WRONG_TIMER_USED;	break;
		}
	}
	else
	{
		returnValue = TIMER_NOK;
	}
	return returnValue;
}

en_TIMER_error_t TIMER_setPwmOffCallBack(en_TIMER_number_t en_a_timerUsed, void (*funPtr)(void))
{
	en_TIMER_error_t returnValue = TIMER_OK;
	
	if(funPtr != NULL_PTR)
	{
		switch(en_a_timerUsed)
		{
			case TIMER_0:	TIMER_0_pwmOffCallBack = funPtr;			break;
			
			case TIMER_1:	/*TO BE IMPLEMENTED*/				break;
			
			case TIMER_2:	/*TO BE IMPLEMENTED*/				break;
			
			default:	returnValue = TIMER_WRONG_TIMER_USED;	break;
		}
	}
	else
	{
		returnValue = TIMER_NOK;
	}
	return returnValue;
}

en_TIMER_error_t TIMER_setDelayTime(en_TIMER_number_t en_a_timerUsed, f32 f32_a_timeInMS)
{
	en_TIMER_error_t returnValue = TIMER_OK;
	u32 overflowCounter = 0;
	u32 tickTime = 0;
	u32 numberOfTicks = 0;
	u32 numberOfOverflows = 0;
	u16 numberOfRemTicks	= 0;
	
	switch(en_a_timerUsed)
	{
		case TIMER_0:
		tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
		numberOfTicks = ((f32_a_timeInMS*1000)/tickTime);
		numberOfOverflows = numberOfTicks / 256;
		numberOfRemTicks	= numberOfTicks % 256;
		
		if (numberOfRemTicks)
		{
			numberOfOverflows++;
			TCNT0 = 256 - numberOfRemTicks;
		}
		else
		{
			TCNT0 = 0;
		}
		
		TIMER_resume(st_TIMER_config[en_a_timerUsed].timerUsed);
		while(overflowCounter < numberOfOverflows)
		{
			while((GET_BIT(TIFR, TOV0)) == 0);
			SET_BIT(TIFR, TOV0);
			overflowCounter++;
		}
		break;
		
		case TIMER_1:
		/*TO BE IMPLEMENTED*/
		break;
		
		case TIMER_2:
		tickTime = st_TIMER_config[en_a_timerUsed].prescalerUsed / XTAL_FREQ;
		numberOfTicks = ((f32_a_timeInMS*1000)/tickTime);
		numberOfOverflows = numberOfTicks / 256;
		numberOfRemTicks	= numberOfTicks % 256;
		
		if (numberOfRemTicks)
		{
			numberOfOverflows++;
			TCNT2 = 256 - numberOfRemTicks;
		}
		else
		{
			TCNT2 = 0;
		}
		
		TIMER_resume(st_TIMER_config[en_a_timerUsed].timerUsed);
		while(overflowCounter < numberOfOverflows)
		{
			while((GET_BIT(TIFR, TOV2)) == 0);
			SET_BIT(TIFR, TOV2);
			overflowCounter++;
		}
		break;
		
		default:
		returnValue =  TIMER_WRONG_TIMER_USED;
		break;
		
	}
	return returnValue;
}

ISR(TIM0_OVF_INT)
{
	if (u8_g_normalToPwm == 0	)
	{
		u32_g_timer0OVFCounter ++;
		if (u32_g_timer0OVFCounter == u32_g_timer0NumberOfOVFs)
		{
			if(TIMER_0_callBack != NULL_PTR)
			{
				TIMER_0_callBack();
			}
			u32_g_timer0OVFCounter   =	0;
			TCNT0 = 256 - u8_g_timer0RemTicks;
		}
	}
	else
	{
		static u8 u8_gs_generatorState = 0;
		if (u8_gs_generatorState)
		{
			
 			if(TIMER_0_pwmOffCallBack != NULL_PTR)
 			{
 				TIMER_0_pwmOffCallBack();
 			}
						
			TCNT0 = 256 - u16_g_offTime0;
			
			if (u16_g_offTime0 < 256)
			{
				u8_gs_generatorState = 0;
			}
		}
		else
		{
 			if(TIMER_0_pwmOnCallBack != NULL_PTR)
 			{
 				TIMER_0_pwmOnCallBack();
 			}
			
			TCNT0 = 256 - u16_g_onTime0;
			
			if (u16_g_onTime0 < 256)
			{
				u8_gs_generatorState = 1;
			}
			
		}
		
	}
}

ISR(TIM1_OVF_INT)
{
	u32_g_timer1OVFCounter ++;
	if (u32_g_timer1OVFCounter  == u32_g_timer1NumberOfOVFs)
	{
		if(TIMER_1_callBack != NULL_PTR)
		{
			TIMER_1_callBack();
		}
		u32_g_timer1OVFCounter  =	0;
		TCNT1 = 65536 - u16_g_timer1RemTicks;
		
	}

}

ISR(TIM2_OVF_INT)
{
	u32_g_timer2OVFCounter ++;
	if (u32_g_timer2OVFCounter  == u32_g_timer2NumberOfOVFs)
	{
		if(TIMER_2_callBack != NULL_PTR)
		{
			TIMER_2_callBack();
		}
		u32_g_timer2OVFCounter  =	0;
		TCNT2 = 256 - u8_g_timer2RemTicks;
		
	}

}
/**********************************************************************************************************************
 *  END OF FILE: timer_program.c
 *********************************************************************************************************************/
