/*
 * us_program.c
 *
 * Created: 15/5/2023 11:44:36 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */
#include "us_interface.h"
#include "us_cfg.h"

st_US_config_t st_g_usConfig;

/**
 * Initializes the ultrasonic driver
 *
 * configuration -> us_cfg.c, or on the fly using US_setConfig() before initialization
 */
void US_init(void)
{
    // init input capture unit
    ICU_init();

    // init US
    st_g_usConfig = US_getConfig();
    // init trigger pin as output
    DIO_setPinDir((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, OUTPUT);

    // write low on trigger pin
    DIO_setPinVal((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, LOW);
}

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
u16 US_getDistance(void)
{
    // send trigger signal
    DIO_setPinVal((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, HIGH);
    // todo delay 10uS ?
    DIO_setPinVal((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, LOW);

    // request ICU to listen to echo pin and wait for time elapsed response
    u16 u16_l_timeElapsed = ICU_getCaptureValue(); // blocking

    if(u16_l_timeElapsed == 0) return 0; // fail

    // calculate distance from time (uS)
    u16 u16_l_echoDistance = CALC_DISTANCE_CM(u16_l_timeElapsed);
    if(u16_l_echoDistance > MIN_SUPPORTED_DISTANCE_CM && u16_l_echoDistance < MAX_SUPPORTED_DISTANCE_CM)
    {
        return u16_l_echoDistance;
    }else{
        return 0;
    }
}