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
	EXTI_DISABLE ,
	EXTI_ENABLE
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

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * @brief Initialize given EXTI as configured
 *
 * This function initializes the passed interrupt with the configured
 * parameters in the configuration source file
 *
 * @param[in] en_a_IntNumber the interrupt to be initialized
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_init(en_EXTI_num_t en_a_intNumber);

/**
 * @brief  Function to choose the trigger event for given EXTI 
 *
 * This function sets the given EXTI to be triggered whenever 
 * an event that matches the given sense mode occurs
 *
 * @param[in] en_a_IntNumber The interrupt to be configured
 * @param[in] en_a_SenseMode The event to trigger the EXTI
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_setSense(en_EXTI_num_t en_a_intNumber, en_EXTI_senseMode_t en_a_senseMode);

/**
 * @brief Function to enable/disable given EXTI
 *
 * This function sets or clears the specific interrupt enable bit
 * for the given interrupt to enable or disable it
 *
 * @param[in] en_a_IntNumber The interrupt to be configured
 * @param[in] en_a_intState  EXTI state (EXTI_ENABLE/EXTI_DISABLE)
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_setState(en_EXTI_num_t en_a_IntNumber, en_EXTI_state_t en_a_intState);

/**
 * @brief Function to set a function to call when exti is triggered
 *
 * This function sets a callback function to be called whenever 
 * the given interrupt is triggered 
 *
 * @param[in] en_a_IntNumber The desired exti number
 * @param[in] pv_a_Function  The function to call
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_setCallback(en_EXTI_num_t en_a_IntNumber, void (*pv_a_Function)(void));


#endif /* EXI_INTERFACE_H_ */