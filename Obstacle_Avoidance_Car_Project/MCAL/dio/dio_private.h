/*
 * dio_private.h
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*************************************************************************************************************
 * 										   DIO register addresses
 ************************************************************************************************************/

typedef struct
{
	volatile u8 PIN;
	volatile u8 DDR;
	volatile u8 PORT;
}st_DIO_port_t;

#define PORTA_BASE       ((volatile st_DIO_port_t*)0x39)
#define PORTB_BASE       ((volatile st_DIO_port_t*)0x36)
#define PORTC_BASE       ((volatile st_DIO_port_t*)0x33)
#define PORTD_BASE       ((volatile st_DIO_port_t*)0x30)


#endif /* DIO_PRIVATE_H_ */