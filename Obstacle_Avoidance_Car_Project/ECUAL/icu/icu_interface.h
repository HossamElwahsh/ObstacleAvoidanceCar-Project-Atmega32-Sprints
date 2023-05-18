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
#include "../../MCAL/timer/timer_interface.h"

/** OPTIONS **/

/**
 * CAPTURE PIN
 */
typedef enum{
    PORT_B = 1,
    PORT_D = 3
}en_ICU_pin_t;

typedef enum{
    PIN_2 = 1,
    PIN_3 = 2
}en_ICU_port_t;

typedef enum{
    INT0,
    INT1,
    INT2,
}en_ICU_exi_t;

typedef struct{
    en_ICU_pin_t capturePort;
    en_ICU_port_t capturePin;
    en_ICU_exi_t interruptNo;
}st_ICU_capturePin_t;

typedef struct{
    st_ICU_capturePin_t PORT_D_PIN_2;
    st_ICU_capturePin_t PORT_D_PIN_3;
    st_ICU_capturePin_t PORT_B_PIN_2;
}st_ICU_capturePins_t;

typedef enum{
    PORT_D_PIN_2,
    PORT_D_PIN_3,
    PORT_B_PIN_2,
}en_ICU_capturePin_t;

typedef enum{
    ICU_OK,
    ICU_ERROR
}en_ICU_error_t;

/**
 * ICU Configuration structure
 * 0: ICU Capture Pin Number
 * 1: ICU Capture Pin data
 * 2: CALLBACK POINTER (when time is calculated)
 */
typedef struct{
    en_ICU_capturePin_t icuCapturePin;
    st_ICU_capturePin_t icuCapturePinData;
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
 * Resets and starts the ICU algorithm to capture the elapsed time by the trigger signal
 * to rebound back on the echo/capture PIN
 *
 * @return elapsed time in uS
 */
u16 ICU_getCaptureValue(void);


/**
 * Handles Interrupts/Events on the capture input pin
 * */
void ICU_inputHandler(void);

#endif /* ICU_INTERFACE_H_ */