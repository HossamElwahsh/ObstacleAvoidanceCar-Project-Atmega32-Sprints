/*
 * exi_program.c
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

/************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/interrupts.h"

#include "exi_private.h"
#include "exi_interface.h"
#include "exi_cfg.h"

/************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
extern const st_EXTI_config_t arr_g_exiConfigs[EXTI_PINS_NUM];

void (*arr_g_exiCBF[EXTI_PINS_NUM])(void) = {NULL};

/************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
/**
 * @brief Check the parameters and configurations
 *
 * This static function checks the validity of the input EXTI number,
 * the configured EXTI state and the configured EXTI sense mode
 * parameters in the configuration source file
 *
 * @param[in] en_a_intNumber the interrupt to be initialized
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
static en_EXTI_error_t ParameterCheck(en_EXTI_num_t en_a_intNumber)
{
	/* Check whether the ext. int. number is valid */
	if((en_a_intNumber < EXTI0) || (en_a_intNumber > EXTI2)) 
	return EXTI_ERROR;
	
	/* Check whether the interrupt state is valid */
	if((arr_g_exiConfigs[en_a_intNumber].EXTI_EN != EXTI_DISABLE)
	&& (arr_g_exiConfigs[en_a_intNumber].EXTI_EN != EXTI_ENABLE))
		return EXTI_ERROR;
	
	/* Check whether the interrupt sense mode is valid */	
	if(((arr_g_exiConfigs[en_a_intNumber].SENSE_MODE)<LOW_LEVEL) 
	|| ((arr_g_exiConfigs[en_a_intNumber].SENSE_MODE)>RISING_EDGE))
		return EXTI_ERROR;
		
	return EXTI_OK;
}

/**
 * @brief Initialize given EXTI as configured
 *
 * This function initializes the passed interrupt with the configured
 * parameters in the configuration source file
 *
 * @param[in] en_a_intNumber the interrupt to be initialized
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_init(en_EXTI_num_t en_a_intNumber)
{
	en_EXTI_error_t en_l_errorState = EXTI_OK;

	/* Input and configuration check */
	en_l_errorState = ParameterCheck(en_a_intNumber);
	
	if(en_l_errorState == EXTI_ERROR) return en_l_errorState; 

	switch(en_a_intNumber)
	{
	case EXTI0:
		EXTI_setSense(EXTI0, arr_g_exiConfigs[EXTI0].SENSE_MODE);
		EXTI_setState(EXTI0, arr_g_exiConfigs[EXTI0].EXTI_EN);
		break;

	case EXTI1:
		EXTI_setSense(EXTI1, arr_g_exiConfigs[EXTI1].SENSE_MODE);
		EXTI_setState(EXTI1, arr_g_exiConfigs[EXTI1].EXTI_EN);		
		break;

	case EXTI2:
		EXTI_setSense(EXTI2, arr_g_exiConfigs[EXTI2].SENSE_MODE);
		EXTI_setState(EXTI2, arr_g_exiConfigs[EXTI2].EXTI_EN);		
		break;
	}

	return en_l_errorState;
}

/**
 * @brief  Function to choose the trigger event for given EXTI 
 *
 * This function sets the given EXTI to be triggered whenever 
 * an event that matches the given sense mode occurs
 *
 * @param[in] en_a_intNumber The interrupt to be configured
 * @param[in] en_a_senseMode The event to trigger the EXTI
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_setSense(en_EXTI_num_t en_a_intNumber, en_EXTI_senseMode_t en_a_senseMode)
{
	en_EXTI_error_t en_l_errorState = EXTI_OK;

	if((en_a_senseMode>=LOW_LEVEL && en_a_senseMode<=RISING_EDGE) && !(en_a_senseMode<FALLING_EDGE && en_a_intNumber==EXTI2))
	{
		switch(en_a_intNumber)
		{
		case EXTI0:
		MCUCR &= EXTI0_SENSE_MODE_MASK;
		MCUCR |= en_a_senseMode;
		break;

		case EXTI1:
		MCUCR &= EXTI1_SENSE_MODE_MASK;
		MCUCR |= en_a_senseMode<<MCUCR_ISC10;
		break;

		case EXTI2:
		CLR_BIT(MCUCSR, MCUCSR_ISC2);
		MCUCSR |= (en_a_senseMode&1)<<MCUCSR_ISC2;
		break;

		default: en_l_errorState = EXTI_ERROR;
		}
	}
	else
	{
		en_l_errorState = EXTI_ERROR;
	}

	return en_l_errorState;
}

/**
 * @brief Function to enable/disable given EXTI
 *
 * This function sets or clears the specific interrupt enable bit
 * for the given interrupt to enable or disable it
 *
 * @param[in] en_a_intNumber The interrupt to be configured
 * @param[in] en_a_intState  EXTI state (EXTI_ENABLE/EXTI_DISABLE)
 *
 * @return en_EXTI_error_t value that indicates operation success/failure
 *		   (EXTI_OK in case of success or EXTI_ERROR in case of failure)
 */
en_EXTI_error_t EXTI_setState(en_EXTI_num_t en_a_intNumber, en_EXTI_state_t en_a_intState)
{
	en_EXTI_error_t en_l_errorState = EXTI_OK;

	/* Set Specific Interrupt Enable bit as configured */
	switch(en_a_intNumber)
	{
	case EXTI0:
		CLR_BIT(GICR, GICR_INT0);
		GICR |= (en_a_intState << GICR_INT0);
		break;

	case EXTI1:
		CLR_BIT(GICR, GICR_INT1);
		GICR |= (en_a_intState << GICR_INT1);
		break;

	case EXTI2:
		CLR_BIT(GICR, GICR_INT2);
		GICR |= (en_a_intState << GICR_INT2);
		break;

	default: en_l_errorState = EXTI_ERROR;
	}

	return en_l_errorState;
}


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
en_EXTI_error_t EXTI_setCallback(en_EXTI_num_t en_a_IntNumber, void (*pv_a_Function)(void))
{
	en_EXTI_error_t en_l_errorState = EXTI_OK;

	if((pv_a_Function != NULL) && (en_a_IntNumber <= MAX_EXTI))
	{
		arr_g_exiCBF[en_a_IntNumber] = pv_a_Function;
	}
	else
	{
		en_l_errorState = EXTI_ERROR;
	}

	return en_l_errorState;
}

/*************************************************************************************************************
 * 													ISRs
 ************************************************************************************************************/
ISR(EXT_INT_0)
{
	if(arr_g_exiCBF[EXTI0] != NULL)
	{
		arr_g_exiCBF[EXTI0]();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(EXT_INT_1)
{
	if(arr_g_exiCBF[EXTI1] != NULL)
	{
		arr_g_exiCBF[EXTI1]();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(EXT_INT_2)
{
	if(arr_g_exiCBF[EXTI2] != NULL)
	{
		arr_g_exiCBF[EXTI2]();
	}
	else
	{
		/* Do Nothing */
	}
}
