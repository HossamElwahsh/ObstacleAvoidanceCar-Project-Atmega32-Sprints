/*
 * dio_interface.h
 *
 * Created: 5/15/2023 4:41:14 PM
 *  Author: Alaa Hisham
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_



#define PORT_INPUT		0x00
#define PORT_OUTPUT		0xff

typedef enum
{
	DIO_PIN_0 = 0,
	DIO_PIN_1,
	DIO_PIN_2,
	DIO_PIN_3,
	DIO_PIN_4,
	DIO_PIN_5,
	DIO_PIN_6,
	DIO_PIN_7
}en_DIO_pin_t;


typedef enum
{
	DIO_PORTA=0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}en_DIO_port_t;

typedef enum
{
	INPUT = 0,
	OUTPUT
}en_DIO_pinDir_t;

typedef enum
{
	LOW = 0,
	HIGH,
}en_DIO_level_t;

typedef enum
{
	DIO_OK,
	DIO_ERROR
}en_DIO_error_t;



en_DIO_error_t DIO_setPortDir(en_DIO_port_t en_a_port,  u8 u8_a_portDir);
en_DIO_error_t DIO_setPortVal(en_DIO_port_t en_a_port,  u8 u8_a_portVal);
en_DIO_error_t DIO_setPinDir (en_DIO_pin_t en_a_pin, en_DIO_pinDir_t en_a_pinDir);
en_DIO_error_t DIO_setPinVal (en_DIO_pin_t en_a_pin, en_DIO_level_t en_a_pinVal);
en_DIO_error_t DIO_togPinVal (en_DIO_pin_t en_a_pin);
en_DIO_error_t DIO_getPinVal (en_DIO_pin_t en_a_pin, u8* pu8Val);




#endif /* DIO_INTERFACE_H_ */