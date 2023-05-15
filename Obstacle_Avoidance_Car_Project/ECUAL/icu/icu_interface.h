/*
 * icu_interface.h
 *
 * Created: 15/5/2023 4:24:07 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */

#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

#include "../../LIB/std.h"

/** OPTIONS **/

/**
 * ICU PORT
 */
typedef enum{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D
}en_ICU_port;

/**
 * ICU PIN
 */
typedef enum{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
}en_ICU_pin;

/**
 * ICU Configuration structure
 * 0: ICU PORT
 * 1: ICU PIN
 * 2: CALLBACK POINTER (when time is calculated)
 */
typedef struct{
    en_ICU_port icuPort;
    en_ICU_pin icuPin;
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
void ICU_init(void);

/**
 * Resets and starts the ICU algorithm to capture the elapsed time duration now
 * starting until echo signal is received back
 */
void ICU_getCaptureValue(void);

#endif /* ICU_INTERFACE_H_ */