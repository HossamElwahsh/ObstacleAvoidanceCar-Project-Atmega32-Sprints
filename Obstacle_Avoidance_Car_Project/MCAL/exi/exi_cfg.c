/*
 * exi_config.c
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

/************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "exi_interface.h"
#include "exi_cfg.h"

/************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/

/**
 * Options:
 * 			.EXTI_NUM =   EXTI0
 * 			              EXTI1
 * 			              EXTI2
 *
 * 			.SENSE_MODE = LOW_LEVEL		[for EXTI0 & EXTI1 only]
 * 			              ON_CHANGE		[for EXTI0 & EXTI1 only]
 * 			              FALLING_EDGE
 * 			              RISING_EDGE
 *
 * 			.EXTI_EN	= EXTI_ENABLE
 * 						  EXTI_DISABLE
 */

const st_EXTI_config_t arr_g_exiConfigs[EXTI_PINS_NUM] =
{
		{
				.EXTI_NUM= EXTI0,
				.SENSE_MODE = RISING_EDGE,
				.EXTI_EN = EXTI_DISABLE
		},

		{
				.EXTI_NUM= EXTI1,
				.SENSE_MODE = FALLING_EDGE,
				.EXTI_EN = EXTI_DISABLE
		},

		{
				.EXTI_NUM= EXTI2,
				.SENSE_MODE = RISING_EDGE,
				.EXTI_EN = EXTI_ENABLE
		}
};
