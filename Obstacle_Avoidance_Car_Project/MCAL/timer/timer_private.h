/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *-------------------------------------------------------------------------------------------------------------------
 *
 *		   @Date:  	5:51 PM Monday, May 15, 2023
 *		   @File:  	timer_private.h         
 *		 @Module:  	Timer
 *		 @Author:	Ahmed Hesham
 *  @Description:  	Private file for Timer module     
 *  
 *********************************************************************************************************************/
#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

typedef enum{
	bit0,
	bit1,
	bit2,
	bit3,
	bit4,
	bit5,
	bit6,
	bit7
}en_bitNumber_t;

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/************************************************************************/
/*							TIMER_REGISTERS								*/
/************************************************************************/
/********************************_TIMER0_REGISTERS_**********************/
#define TCCR0		(*((volatile u8*)0x53))
#define FOC0		bit7
#define WGM00		bit6
#define COM01		bit5
#define	COM00		bit4
#define WGM01		bit3
#define CS02		bit2
#define	CS01		bit1
#define	CS00		bit0

#define TIMSK		(*((volatile u8*)0x59))			/*Timer/Counter Interrupt Mask Register*/
#define OCIE2		bit7
#define TOIE2		bit6
#define TICIE1		bit5
#define	OCIE1A		bit4
#define OCIE1B		bit3
#define TOIE1		bit2
#define	OCIE0		bit1
#define	TOIE0		bit0

#define TCNT0		(*((volatile u8*)0x52))

#define OCR0		(*((volatile u8*)0x5C))

#define TIFR		(*((volatile u8*)0x58))
#define OCF2		bit7
#define TOV2		bit6
#define ICF1		bit5
#define OCF1A		bit4
#define OCF1B		bit3
#define TOV1		bit2
#define OVF0		bit1
#define TOV0		bit0

/********************************_TIMER1_REGISTERS_**********************/
#define ICR1		(*((volatile u16*)0x46))
#define ICR1L		(*((volatile u8*)0x46))
#define ICR1H		(*((volatile u8*)0x47))

#define OCR1A		(*((volatile u16*)0x4A))
#define OCR1AL		(*((volatile u8*)0x4A))
#define OCR1AH		(*((volatile u8*)0x4B))
#define OCR1B		(*((volatile u16*)0x48))
#define OCR1BL		(*((volatile u8*)0x48))
#define OCR1BH 		(*((volatile u8*)0x49))


#define TCNT1		(*((volatile u16*)0x4C))
#define TCNT1L		(*((volatile u8*)0x4C))
#define TCNT1H		(*((volatile u8*)0x4D))

#define TCCR1		(*((volatile u16*)0x4E))
#define TCCR1A		(*((volatile u8*)0x4F))
#define TCCR1B		(*((volatile u8*)0x4E))
#define COM1A1		bit7
#define COM1A0		bit6
#define COM1B1		bit5
#define COM1B0		bit4
#define FOC1A		bit3
#define FOC1B		bit2
#define WGM11		bit1
#define WGM10		bit0
#define ICNC1		bit7
#define ICES1		bit6
#define WGM13		bit4
#define WGM12		bit3
#define CS12		bit2
#define	CS11		bit1
#define	CS10		bit0

/********************************_TIMER2_REGISTERS_**********************/
#define TCCR2		(*((volatile u8*)0x45))
#define FOC2		bit7
#define WGM20		bit6
#define COM21		bit5
#define	COM20		bit4
#define WGM21		bit3
#define CS22		bit2
#define	CS21		bit1
#define	CS20		bit0

#define TCNT2		(*((volatile u8*)0x44))

#define OCR2		(*((volatile u8*)0x43))

/************************************************************************/
/*							STATUS_REGISTER								*/
/************************************************************************/
#define SREG		(*((volatile u8*)0x5F))			/*AVR Status Register*/
#define Ibit		bit7							/*Global Interrupt Enable*/




#endif /* TIMER_PRIVATE_H_ */
/**********************************************************************************************************************
 *  END OF FILE: timer_private.c
 *********************************************************************************************************************/