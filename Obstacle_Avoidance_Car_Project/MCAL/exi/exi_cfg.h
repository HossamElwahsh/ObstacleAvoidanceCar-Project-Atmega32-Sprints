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
#define EXI_PINS_NUM		3			//Number of ext. interrupt pins

#define MAX_EXTI			EXTI2

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef struct
{
	en_EXI_num_t 	 	EXI_NUM;
	en_EXI_senseMode_t SENSE_MODE;
	en_EXI_state_t 	EXI_EN;
}st_EXI_config_t;


/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/



#endif /* EXI_CONFIG_H_ */