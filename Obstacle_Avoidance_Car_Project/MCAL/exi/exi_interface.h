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
}en_EXI_num_t;

typedef enum
{
	EXI_DISABLE ,
	EXI_ENABLE
}en_EXI_state_t;

typedef enum
{
	LOW_LEVEL,
	ON_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}en_EXI_senseMode_t;

typedef enum
{
	EXI_OK,
	EXI_ERROR
}en_EXI_error_t;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * @brief Initialize given EXI as configured
 *
 * This function initializes the passed interrupt with the configured
 * parameters in the configuration source file
 *
 * @param[in] en_a_IntNumber the interrupt to be initialized
 *
 * @return en_EXI_error_t value that indicates operation success/failure
 *		   (EXI_OK in case of success or EXI_ERROR in case of failure)
 */
en_EXI_error_t EXI_init(en_EXI_num_t en_a_intNumber);

/**
 * @brief  Function to choose the trigger event for given EXI 
 *
 * This function sets the given EXI to be triggered whenever 
 * an event that matches the given sense mode occurs
 *
 * @param[in] en_a_IntNumber The interrupt to be configured
 * @param[in] en_a_SenseMode The event to trigger the EXI
 *
 * @return en_EXI_error_t value that indicates operation success/failure
 *		   (EXI_OK in case of success or EXI_ERROR in case of failure)
 */
en_EXI_error_t EXI_setSense(en_EXI_num_t en_a_intNumber, en_EXI_senseMode_t en_a_senseMode);

/**
 * @brief Function to enable/disable given EXI
 *
 * This function sets or clears the specific interrupt enable bit
 * for the given interrupt to enable or disable it
 *
 * @param[in] en_a_IntNumber The interrupt to be configured
 * @param[in] en_a_intState  EXI state (EXI_ENABLE/EXI_DISABLE)
 *
 * @return en_EXI_error_t value that indicates operation success/failure
 *		   (EXI_OK in case of success or EXI_ERROR in case of failure)
 */
en_EXI_error_t EXI_setState(en_EXI_num_t en_a_IntNumber, en_EXI_state_t en_a_intState);

/**
 * @brief Function to set a function to call when EXI is triggered
 *
 * This function sets a callback function to be called whenever 
 * the given interrupt is triggered 
 *
 * @param[in] en_a_IntNumber The desired EXI number
 * @param[in] pv_a_Function  The function to call
 *
 * @return en_EXI_error_t value that indicates operation success/failure
 *		   (EXI_OK in case of success or EXI_ERROR in case of failure)
 */
en_EXI_error_t EXI_setCallback(en_EXI_num_t en_a_IntNumber, void (*pv_a_Function)(void));


#endif /* EXI_INTERFACE_H_ */