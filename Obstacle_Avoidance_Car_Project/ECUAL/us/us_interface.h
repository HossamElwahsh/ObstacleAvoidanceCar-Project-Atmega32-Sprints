/*
 * us_interface.h
 *
 * Created: 15/5/2023 4:24:25 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 


#ifndef US_INTERFACE_H_
#define US_INTERFACE_H_

#include "../../LIB/std.h"
#include "../../ECUAL/icu/icu_interface.h"
#include "../../ECUAL/icu/icu_cfg.h"

/** Macros **/
// 343 m/s = 0.0343 cm/uS = 1/29.1 cm/uS
#define SPEED_OF_SOUND_IN_AIR_CM_PER_US (1/29.1) // 1/29.1 cm/uS

#define CALC_DISTANCE_CM(travelTimeMs) (((travelTimeMs/2)/1000) * (SPEED_OF_SOUND_IN_AIR_CM_PER_US))

#define MIN_SUPPORTED_DISTANCE_CM 2     // 2cm
#define MAX_SUPPORTED_DISTANCE_CM 400   // 4m = 400cm

#define US_ECHO_STATE_WAITING 0
#define US_ECHO_STATE_RECEIVED 1

/**
 * ULTRASONIC PORT
 */
typedef enum{
    US_PORT_A,
    US_PORT_B,
    US_PORT_C,
    US_PORT_D
}en_US_port_t;

/**
 * ULTRASONIC PINS (TRIGGER / ECHO)
 */
typedef enum{
    US_PIN_0,
    US_PIN_1,
    US_PIN_2,
    US_PIN_3,
    US_PIN_4,
    US_PIN_5,
    US_PIN_6,
    US_PIN_7
}en_US_pin_t;

/** Typedefs **/
typedef struct{
    en_US_port_t US_Port;

    /* I/O pin number to send trigger signal */
    en_US_pin_t triggerPin;

    /* I/O pin number to receive echoed signal */
    en_US_pin_t echoPin;
}st_US_config_t;

/** Functions' Prototypes **/

/**
 * Initializes the ultrasonic driver
 *
 * configuration -> us_cfg.c, or on the fly using US_setConfig() before initialization
 */
void US_init(void);

/**
 *
 * Initiates a get distance request (sync)
 *
 * This function sends a signal out to the trigger pin, waits for echo signal
 * to come back and finally calculates the distance the signal traveled using
 * the elapsed time duration used by the signal to arrive back on the echo pin
 *
 * @return Distance in cm (Supported Range 2 - 400 cm), 0 if failed or wrong read
 */
u16 US_getDistance(void);

/**
 * Event Handler: called when echo time is received from ICU (input capture unit)
 *
 * This function is called by the ICU as an event callback when the trigger signal
 * is received back on the echo pin, the function receives the elapsed time taken.
 *
 * @param [in]u32_a_timeElapsed time elapsed (duration) by trigger signal to echo back
 */
void US_evtEchoTimeReceived(u32 u32_a_timeElapsed);

#endif /* US_INTERFACE_H_ */