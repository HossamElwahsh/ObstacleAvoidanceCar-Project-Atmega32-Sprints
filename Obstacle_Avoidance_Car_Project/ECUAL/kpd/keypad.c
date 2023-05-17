/*
 * keypad.c
 *
 * Created: 5/16/2023 12:06:19 PM
 *  Author: Sarah
 */ 
#include "keypad_interface.h"

/**
 * @brief This function inialize keypad
 *
 * @param void
 *
 * @return Returns void
 */
void KEYPAD_init()
{
	// INITIALIZE ROWS AS OUTPUTS
	DIO_setPinDir(KEYPAD_PORT,  KEYPAD_ROW_0,OUTPUT);
	
	
	// INITIALIZE COLUMNS AS INPUTS
	DIO_setPinDir(KEYPAD_PORT, KEYPAD_COLUMN_0,INPUT);
	DIO_setPinDir(KEYPAD_PORT, KEYPAD_COLUMN_1,INPUT);
	
	// Init Timer
    DELAY_init();
}
/**
 * @brief This function gets keypad value pressed or not pressed
 *
 * @param void
 *
 * @return Returns u8 : value of keypad
 */

u8 KEYPAD_GetButton()
{
	u8 LOC_COL = 0;/*Counter for column locations*/
	u8 LOC_ROW = 0;/*Counter for row locations*/
	u8 Value = 0;/*Final value*/
	u8 Temp = 0;
	for(LOC_COL = COL_INIT; LOC_COL <= COL_FINAL; LOC_COL++)
	{
		DIO_setPinVal(KEYPAD_PORT, LOC_COL, LOW);/*Start by activate only one column, Active LOW*/
		for (LOC_ROW = ROW_INIT; LOC_ROW <= ROW_FINAL; LOC_ROW++)
		{
			DIO_getPinVal(KEYPAD_PORT, LOC_ROW, &Temp);
			if(!Temp)/*Wait */
			{
				Value = keypad[LOC_ROW - ROW_INIT][LOC_COL - COL_INIT];/*Check matrix to know*/
				while(!Temp)/*Still pressing on button*/
				{
					DIO_getPinVal(KEYPAD_PORT, LOC_ROW, &Temp);
				}
				DELAY_setTime (KPD_DEBOUNCE_DELAY);
			}
		}
		DIO_setPinVal(KEYPAD_PORT, LOC_COL, HIGH);/*Finish by activate only one column, Set high again*/
	}
	return Value;
}