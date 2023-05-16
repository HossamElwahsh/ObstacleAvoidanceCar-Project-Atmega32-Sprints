/*
 * us_program.c
 *
 * Created: 15/5/2023 11:44:36 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */
#include "us_interface.h"

/**
 * Initializes the ultrasonic driver
 *
 * configuration -> us_cfg.c, or on the fly using US_setConfig() before initialization
 */
void US_init(void)
{

}

/**
 *
 * Initiates a get distance request
 *
 * This function sends a signal out to the trigger pin, waits for echo signal
 * to come back and finally calculates the distance the signal traveled using
 * the elapsed time duration used by the signal to arrive back on the echo pin
 *
 * @return Distance in cm (Supported Range 2 - 400 cm), 0 if failed or wrong read
 */
u16 US_getDistance(void)
{
    return 0;
}

/**
 * Event Handler: called when echo time is received from ICU (input capture unit)
 *
 * This function is called by the US as an event callback when the trigger signal
 * is received back on the echo pin, the function receives the elapsed time taken.
 *
 * @param [in]u8_a_timeElapsed time elapsed (duration) by trigger signal to echo back
 */
void US_evtEchoTimeReceived(u8 u8_a_timeElapsed)
{

}