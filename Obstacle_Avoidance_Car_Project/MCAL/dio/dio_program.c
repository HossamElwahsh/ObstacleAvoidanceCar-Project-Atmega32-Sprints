/*
 * dio_program.c
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

/************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

#include "dio_private.h"
#include "dio_interface.h"

/************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
static st_DIO_port_t* arr_gs_ports[] = {PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE};

/************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/

/**
 * @def function to set the direction of an entire port
 * @param en_a_port   : the desired port
 * @param u8_a_portVal: value to set the entire port to
 * @return error status
 */
en_DIO_error_t DIO_setPortDir(en_DIO_port_t en_a_port,  u8 u8_a_portDir)
{
	en_DIO_error_t en_l_errorState = DIO_OK;
	st_DIO_port_t* pst_l_port;

	/* Check whether the port is valid */
	if(en_a_port >= DIO_PORTA && en_a_port <= DIO_PORTD)
	{
		/* Get the port base address */
		pst_l_port = arr_gs_ports[en_a_port];

		/* Set the port direction */
		pst_l_port->DDR = u8_a_portDir;
	}
	else
	{
		en_l_errorState = DIO_ERROR;
	}

	return en_l_errorState;
}

/**
 * @def function to set the output value on an entire port
 * @param en_a_port   : the desired port
 * @param u8_a_portVal: value to set the entire port to
 * @return error status
 */
en_DIO_error_t DIO_setPortVal(en_DIO_port_t en_a_port,  u8 u8_a_portVal)
{
	en_DIO_error_t en_l_errorState = DIO_OK;
	st_DIO_port_t* pst_l_port;

	/* Check whether the port is valid */
	if(en_a_port >= DIO_PORTA && en_a_port <= DIO_PORTD)
	{
		/* Get the port base address */
		pst_l_port = arr_gs_ports[en_a_port];

		/* Set the port value */
		pst_l_port->PORT = u8_a_portVal;
	}
	else
	{
		en_l_errorState = DIO_ERROR;
	}

	return en_l_errorState;
}

/**
 * @def function to configure a single DIO pin as input/output
 * @param en_a_port the port of the required pin
 * @param en_a_pin the pin number in the given port
 * @param en_a_pinDir: the direction to set the pin to
 * @return error status
 */
en_DIO_error_t DIO_setPinDir (en_DIO_port_t en_a_port, en_DIO_pin_t en_a_pin, en_DIO_pinDir_t en_a_pinDir)
{
	en_DIO_error_t en_l_errorState = DIO_OK;
	st_DIO_port_t* pst_l_port;

	/* Check whether all the inputs are valid */
	if((en_a_port >= DIO_PORTA && en_a_port <= DIO_PORTD)
	&& (en_a_pin >= DIO_PIN_0 && en_a_pin <= DIO_PIN_7)
	&& (en_a_pinDir == INPUT || en_a_pinDir == OUTPUT))
	{
		/* Get the port base address */
		pst_l_port = arr_gs_ports[en_a_port];

		/* Clear the direction bit value of the pin */
		CLR_BIT(pst_l_port->DDR, en_a_pin);

		/* Set the value to the given direction */
		pst_l_port->DDR |= en_a_pinDir<<en_a_pin;
	}
	else
	{
		en_l_errorState = DIO_ERROR;
	}

	return en_l_errorState;
}

/**
 * @def function to configure a single DIO pin as input/output
 * @param en_a_port the port of the required pin
 * @param en_a_pin the pin number in the given port
 * @param en_a_pinVal desired value (high or low) to set the pin to
 * @return error status
 */
en_DIO_error_t DIO_setPinVal (en_DIO_port_t en_a_port, en_DIO_pin_t en_a_pin, en_DIO_level_t en_a_pinVal)
{
	en_DIO_error_t en_l_errorState = DIO_OK;
	st_DIO_port_t* pst_l_port;

	/* Check whether all the inputs are valid */
	if((en_a_port >= DIO_PORTA && en_a_port <= DIO_PORTD)
	&& (en_a_pin >= DIO_PIN_0 && en_a_pin <= DIO_PIN_7)
	&& (en_a_pinVal == HIGH || en_a_pinVal == LOW))
	{
		/* Get the port base address */
		pst_l_port = arr_gs_ports[en_a_port];

		/* Clear the bit value of the pin */
		CLR_BIT(pst_l_port->PORT, en_a_pin);

		/* Set the bit to the given value */
		pst_l_port->PORT |= en_a_pinVal<<en_a_pin;
	}
	else
	{
		en_l_errorState = DIO_ERROR;
	}

	return en_l_errorState;
}

/**
 * @def function to get the value of a single DIO pin whether high or low
 * @param en_a_port: the port of the required pin
 * @param en_a_pin : the pin number to get the value of
 * @param pu8_a_Val: pointer to a variable to store pin value
 * @return error status
 */
en_DIO_error_t DIO_getPinVal (en_DIO_port_t en_a_port, en_DIO_pin_t en_a_pin, u8* pu8_a_Val)
{
	en_DIO_error_t en_l_errorState = DIO_OK;
	st_DIO_port_t* pst_l_port;

	/* Check whether all the inputs are valid */
	if((en_a_port >= DIO_PORTA && en_a_port <= DIO_PORTD)
	&& (en_a_pin >= DIO_PIN_0 && en_a_pin <= DIO_PIN_7)
	&& (pu8_a_Val != NULL_PTR))
	{
		/* Get the port base address */
		pst_l_port = arr_gs_ports[en_a_port];

		/* Get the value to the given pin */
		*pu8_a_Val = GET_BIT(pst_l_port->PIN, en_a_pin);
	}
	else
	{
		en_l_errorState = DIO_ERROR;
	}

	return en_l_errorState;
}

/**
 * @def function to toggle the value of the given pin
 * @param en_a_port: the port of the required pin
 * @param en_a_pin : the pin number in the given port
 * @return error status
 */
en_DIO_error_t DIO_togPinVal (en_DIO_port_t en_a_port, en_DIO_pin_t en_a_pin)
{
	en_DIO_error_t en_l_errorState = DIO_OK;
	st_DIO_port_t* pst_l_port;

	/* Check whether all the inputs are valid */
	if((en_a_port >= DIO_PORTA && en_a_port <= DIO_PORTD)
	&& (en_a_pin >= DIO_PIN_0 && en_a_pin <= DIO_PIN_7))
	{
		/* Get the port base address */
		pst_l_port = arr_gs_ports[en_a_port];

		/* Toggle the value to the given pin */
		TOG_BIT(pst_l_port->PORT, en_a_pin);
	}
	else
	{
		en_l_errorState = DIO_ERROR;
	}

	return en_l_errorState;
}


