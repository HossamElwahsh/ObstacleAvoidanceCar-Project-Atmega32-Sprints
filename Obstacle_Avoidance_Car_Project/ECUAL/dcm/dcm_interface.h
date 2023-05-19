/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *-------------------------------------------------------------------------------------------------------------------
 *		   @Date:  	2:38 PM Sunday, May 14, 2023
 *		   @File:  	dcm_interface.h         
 *		 @Module:  	DC Motor
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Interfacing file for DC Motor module     
 *  
 *********************************************************************************************************************/
#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/dio/dio_interface.h"
#include "../pwm/pwm_interface.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/***************************************_ERROR_TYPES_***************************************/
typedef enum
{
	DCM_OK = 0,
	DCM_WRONG_DCM_NUMBER,
	DCM_WRONG_DIRECTION,
	DCM_NOK
}en_DCM_error_t;


/***************************************_DCM_NUMBERS_***************************************/
typedef enum
{
	DCM_0 = 0,
	DCM_1,
	DCM_2,
	DCM_3,
	DCM_4,
	DCM_5
}en_DCM_number_t;


/***************************************_DCM_DIRECTOINS_***************************************/
typedef enum 
{
	DCM_CW = 0,
	DCM_ACW
}en_DCM_direction_t;


/**************************_LINKING_CONFIGURATION_STRUCTURE_DATA_TYPE_**************************/	
typedef struct
{
	en_DCM_number_t 	dcmNumber;
				 u8		dcmPortNumber_0;
				 u8		dcmPinNumber_0;
				 u8		dcmPortNumber_1;
				 u8		dcmPinNumber_1;
}st_DCM_config_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* @Syntax          : en_DCM_error_t DCM_init (void)
* @Description     : Initializes DCM module
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_DCM_error_t			DCM_OK = 0
*											DCM_NOK = 1
*******************************************************************************/
en_DCM_error_t DCM_init				(void);

/******************************************************************************
* @Syntax          : en_DCM_error_t DCM_setDirection	
*					 (en_DCM_number_t en_a_dcmNumber, en_DCM_direction_t en_a_direction)
* @Description     : Sets Directions for the a specific DCM
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : en_DCM_number_t		en_a_dcmNumber
*					 en_DCM_direction_t		en_a_direction
* @Parameters (out): None
* @Return value:   : en_DCM_error_t			DCM_OK = 0
*											DCM_NOK = 1
*******************************************************************************/
en_DCM_error_t DCM_setDirection		(en_DCM_number_t en_a_dcmNumber, en_DCM_direction_t en_a_direction);

/******************************************************************************
* @Syntax          : en_DCM_error_t DCM_speed (u8 u8_a_speed)
* @Description     : Sets speed for DCMs
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : u8						u8_a_speed
* @Parameters (out): None
* @Return value:   : en_DCM_error_t			DCM_OK = 0
*											DCM_NOK = 1
*******************************************************************************/
en_DCM_error_t DCM_speed			(u8 u8_a_speed);

/******************************************************************************
* @Syntax          : en_DCM_error_t DCM_start (void)
* @Description     : Starts DCMs to rotate
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_DCM_error_t			DCM_OK = 0
*											DCM_NOK = 1
*******************************************************************************/
en_DCM_error_t DCM_start			(void);

/******************************************************************************
* @Syntax          : en_DCM_error_t DCM_stop (void)
* @Description     : Stops DCMs from rotating
* @Sync\Async      : Synchronous
* @Reentrancy      : Reentrant
* @Parameters (in) : None
* @Parameters (out): None
* @Return value:   : en_DCM_error_t			DCM_OK = 0
*											DCM_NOK = 1
*******************************************************************************/
en_DCM_error_t DCM_stop				(void);


#endif /* DCM_INTERFACE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: dcm_interface.h
 *********************************************************************************************************************/
