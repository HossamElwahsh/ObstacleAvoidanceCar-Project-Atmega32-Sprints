/*
 * keypad_interface.h
 *
 * Created: 5/16/2023 10:55:15 AM
 *  Author: Sarah
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_



/*******************************************************************************************************************************************************************/
/* KPD Macros */

/* KPD Flag Values */
#define KPD_U8_KEY_NOT_FOUND		0
#define KPD_U8_KEY_FOUND			1

/* KPD Initial Value of Key */
#define KPD_U8_KEY_NOT_PRESSED		0xff

/*******************************************************************************************************************************************************************/
/* KPD Functions' Prototypes */

void KPD_initKPD    ( void );
void KPD_enableKPD  ( void );
void KPD_disableKPD ( void );

u8 KPD_getPressedKey( u8 *pu8_a_returnedKeyValue );
/*******************************************************************************************************************************************************************/



#endif /* KEYPAD_INTERFACE_H_ */