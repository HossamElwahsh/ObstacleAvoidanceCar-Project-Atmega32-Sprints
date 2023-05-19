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
 * 			.EXI_NUM =   EXTI0
 * 			              EXTI1
 * 			              EXTI2
 *
 * 			.SENSE_MODE = LOW_LEVEL		[for EXTI0 & EXTI1 only]
 * 			              ON_CHANGE		[for EXTI0 & EXTI1 only]
 * 			              FALLING_EDGE
 * 			              RISING_EDGE
 *
 * 			.EXI_EN	= EXI_ENABLE
 * 						  EXI_DISABLE
 */

const st_EXI_config_t arr_g_exiConfigs[EXI_PINS_NUM] =
{
		{
				.EXI_NUM= EXTI0,
				.SENSE_MODE = RISING_EDGE,
				.EXI_EN = EXI_DISABLE
		},

		{
				.EXI_NUM= EXTI1,
				.SENSE_MODE = FALLING_EDGE,
				.EXI_EN = EXI_DISABLE
		},

		{
				.EXI_NUM= EXTI2,
				.SENSE_MODE = RISING_EDGE,
				.EXI_EN = EXI_DISABLE
		}
};
