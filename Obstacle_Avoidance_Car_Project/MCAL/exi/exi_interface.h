/*
 * exi_interface.h
 *
 * Created: 5/15/2023 5:15:06 PM
 *  Author: Alaa Hisham
 */ 


#ifndef EXI_INTERFACE_H_
#define EXI_INTERFACE_H_

typedef enum
{
	EXTI0,
	EXTI1,
	EXTI2
}en_EXTI_num_t;

typedef enum
{
	EXTI_ENABLE ,
	EXTI_DISABLE
}en_EXTI_state_t;

typedef enum
{
	LOW_LEVEL,
	ON_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}en_EXTI_senseMode_t;

typedef enum
{
	EXTI_OK,
	EXTI_ERROR
}en_EXTI_error_t;

typedef struct
{
	en_EXTI_num_t 	 EXTI_NUM;		
	en_EXTI_senseMode_t   SENSE_MODE;
	en_EXTI_state_t 	 EXTI_EN;
}st_PortDDirConfig_t;



/**
 * @def   Initialize given EXTI as configured
 * @param u8_a_IntNumber: the interrupt to be initialized
 * @return error state
 */
en_EXTI_error_t EXTI_init(en_EXTI_num_t u8_a_intNumber);

/**
 * @def   Function to choose the trigger event for given EXTI 
 * @param u8_a_IntNumber: the interrupt to be configured
 * @param u8_a_SenseMode: the  EXTI trigger event
 * @return error state
 */
en_EXTI_error_t EXTI_setSense(en_EXTI_num_t u8_a_intNumber, en_EXTI_senseMode_t u8_a_senseMode);

/**
 * @def	  Function to enable/disable given EXTI
 * @param u8_a_IntNumber: the interrupt to be configured
 * @param en_a_intState: EXTI state (Enable/Disable)
 * @return error state
 */
en_EXTI_error_t EXTI_setState(en_EXTI_num_t u8_a_IntNumber, en_EXTI_state_t en_a_intState);

/**
 * @def   Function to set a CBF to call when exti is triggered
 * @param u8_a_IntNumber : the desired exti
 * @param pv_a_Function: The function to call
 * @return error state
 */
en_EXTI_error_t EXTI_setCallback(en_EXTI_num_t u8_a_IntNumber, void (pv_a_Function)(void));



#endif /* EXI_INTERFACE_H_ */