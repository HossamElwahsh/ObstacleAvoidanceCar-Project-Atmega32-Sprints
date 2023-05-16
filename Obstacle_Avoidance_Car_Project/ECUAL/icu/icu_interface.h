/*
 * icu_interface.h
 *
 * Created: 15/5/2023 4:24:07 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */

#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

/* LIB*/
#include "../../LIB/std.h"
#include "../../LIB/interrupts.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/exi/exi_interface.h"

/* Config */
#include "icu_cfg.h"

/** OPTIONS **/

/**
 * CAPTURE PIN
 */
typedef enum{
    // INT0
    PORT_D_PIN_2,
    // INT1
    PORT_D_PIN_3,
    // INT2
    PORT_B_PIN_2
}en_ICU_capturePin;

typedef enum{
    ICU_OK,
    ICU_ERROR
}en_ICU_error_t;

/**
 * ICU Configuration structure
 * 0: ICU PORT
 * 1: ICU PIN
 * 2: CALLBACK POINTER (when time is calculated)
 */
typedef struct{
    en_ICU_capturePin icuCapturePin;
	void (* timeReceivedCallbackFun)(void);
}st_ICU_config_t;

/* FUNCTIONS' PROTOTYPES */

/**
 * Initializes the ICU driver
 *
 * This function initializes a software ICU driver, init echo pin as input,
 * uses timer to calculate elapsed time, when echo pin is triggered it sends the
 * elapsed time duration to the callback function
 *
 * configuration -> icu_cfg.c, or on the fly using ICU_setConfig() before initialization
 */
en_ICU_error_t ICU_init(void);

/**
 * Resets and starts the ICU algorithm to capture the elapsed time duration now
 * starting until echo signal is received back
 */
void ICU_getCaptureValue(void);

#endif /* ICU_INTERFACE_H_ */