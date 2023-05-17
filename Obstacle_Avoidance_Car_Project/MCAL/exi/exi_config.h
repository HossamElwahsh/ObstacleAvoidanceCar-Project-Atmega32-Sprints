/*
 * exi_config.h
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

#ifndef EXI_CONFIG_H_
#define EXI_CONFIG_H_


/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define EXTI_PINS_NUM		3			//Number of ext. interrupt pins

#define MAX_EXTI			EXTI2

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef struct
{
	en_EXTI_num_t 	 	EXTI_NUM;
	en_EXTI_senseMode_t SENSE_MODE;
	en_EXTI_state_t 	EXTI_EN;
}st_EXTI_config_t;


/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/



#endif /* EXI_CONFIG_H_ */