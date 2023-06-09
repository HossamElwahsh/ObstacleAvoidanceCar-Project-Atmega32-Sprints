/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
 *
 *         @Date:  	2:47 PM Sunday, May 14, 2023
 *		   @File:  	dcm_cfg.c         
 *		 @Module:  	DC Motor
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Linking configuration file for DC Motor module     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "dcm_interface.h"
#include "dcm_cfg.h"
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 
 const st_DCM_config_t st_DCM_config [NUMBER_OF_DCMS_USED] = 
{
/*	 DCM_#, PORT0_#,	  PIN0_#*, PORT1_#,    PIN1_#	*/
	{DCM_0, DIO_PORTD, DIO_PIN_2, DIO_PORTD, DIO_PIN_3},
	{DCM_1, DIO_PORTD, DIO_PIN_6, DIO_PORTD, DIO_PIN_7}
};
 
/**********************************************************************************************************************
 *  END OF FILE: dcm_cfg.c
 *********************************************************************************************************************/
