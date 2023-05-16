/*
 * keypad.c
 *
 * Created: 5/16/2023 12:06:19 PM
 *  Author: Sarah
 */ 
#include "keypad_interface.h"
void KEYPAD_init()
{
	// INITIALIZE ROWS AS OUTPUTS
	DIO_setPinDir(DIO_PORTB,DIO_PIN_1,OUTPUT);
	DIO_setPinDir(DIO_PORTB,DIO_PIN_2,OUTPUT);
	DIO_setPinDir(DIO_PORTB,DIO_PIN_3,OUTPUT);
	// INITIALIZE COLUMNS AS INPUTS
	DIO_setPinDir(DIO_PORTC,DIO_PIN_1,INPUT);
	DIO_setPinDir(DIO_PORTC,DIO_PIN_2,INPUT);
	DIO_setPinDir(DIO_PORTC,DIO_PIN_3,INPUT);
	
}
EN_KEYPAD_BTNS checkR1()
{
	DIO_setPinVal(DIO_PORTC,DIO_PIN_1,HIGH);
	DIO_setPinVal(DIO_PORTC,DIO_PIN_2,HIGH);
	DIO_setPinVal(DIO_PORTC,DIO_PIN_3,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_2,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_3,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_1,LOW);
	
	u8 val = HIGH;
	DIO_getPinVal(DIO_PORTC,DIO_PIN_1,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_1,&val);
		}
		return KEY_INCREAMENT;
	}
	
	DIO_getPinVal(DIO_PORTC,DIO_PIN_2,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_2,&val);
		}
		return KEY_DECREAMENT;
	}
	
	DIO_getPinVal(DIO_PORTC,DIO_PIN_3,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_3,&val);
		}
		return KEY_SET;
	}
	return KEY_NOTHING;
	
}
EN_KEYPAD_BTNS checkR2()
{
	
	DIO_setPinVal(DIO_PORTC,DIO_PIN_1,HIGH);
	DIO_setPinVal(DIO_PORTC,DIO_PIN_2,HIGH);
	DIO_setPinVal(DIO_PORTC,DIO_PIN_3,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_1,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_3,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_2,LOW);
	
	u8 val = HIGH;
	DIO_getPinVal(DIO_PORTC,DIO_PIN_1,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_1,&val);
		}
		return KEY_ADJUST;
	}
	
	DIO_getPinVal(DIO_PORTC,DIO_PIN_2,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_2,&val);
		}
		return KEY_RESET;
	}
	
	DIO_getPinVal(DIO_PORTC,DIO_PIN_3,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_3,&val);
		}
		return KEY_6;
	}
	return KEY_NOTHING;
	
}
EN_KEYPAD_BTNS checkR3()
{
	
	DIO_setPinVal(DIO_PORTC,DIO_PIN_1,HIGH);
	DIO_setPinVal(DIO_PORTC,DIO_PIN_2,HIGH);
	DIO_setPinVal(DIO_PORTC,DIO_PIN_3,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_1,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_2,HIGH);
	DIO_setPinVal(DIO_PORTB,DIO_PIN_3,LOW);
	
	u8 val = HIGH;
	DIO_getPinVal(DIO_PORTC,DIO_PIN_1,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_1,&val);
		}
		return KEY_7;
	}
	
	DIO_getPinVal(DIO_PORTC,DIO_PIN_2,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_2,&val);
		}
		return KEY_8;
	}
	
	DIO_getPinVal(DIO_PORTC,DIO_PIN_3,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_getPinVal(DIO_PORTC,DIO_PIN_3,&val);
		}
		return KEY_9;
	}
	return KEY_NOTHING;
}

EN_KEYPAD_BTNS KEYPAD_GetButton()
{
	EN_KEYPAD_BTNS PRESSED = KEY_NOTHING;
	PRESSED = checkR1();
	if(PRESSED != KEY_NOTHING) return PRESSED;
	PRESSED = checkR2();
	if(PRESSED != KEY_NOTHING) return PRESSED;
	PRESSED = checkR3();
	if(PRESSED != KEY_NOTHING) return PRESSED;
	return PRESSED;
	
}