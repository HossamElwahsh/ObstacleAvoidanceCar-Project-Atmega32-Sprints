/*
 * us_program.c
 *
 * Created: 15/5/2023 11:44:36 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */
#include "us_interface.h"
#include "us_cfg.h"

st_US_config_t st_g_usConfig;
u8 u8_g_echoState = US_ECHO_STATE_WAITING;
u32 u32_g_lastElapsedTime = 0;

/**
 * Initializes the ultrasonic driver
 *
 * configuration -> us_cfg.c, or on the fly using US_setConfig() before initialization
 */
void US_init(void)
{
    // setup callback function in ICU Config
    st_ICU_config_t st_l_icuConfig = ICU_getConfig();
    st_l_icuConfig.timeReceivedCallbackFun = US_evtEchoTimeReceived;
    ICU_setConfig(st_l_icuConfig);

    // init input capture unit
    ICU_init();

    // init US
    st_g_usConfig = US_getConfig();
    // init trigger pin as output
//    DIO_setPinDir((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, OUTPUT);
    DIO_setPinDir(DIO_PORTB, DIO_PIN_3, OUTPUT);

    // write low on trigger pin
//    DIO_setPinVal((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, LOW);
    DIO_setPinVal(DIO_PORTB, DIO_PIN_3, LOW);
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
    u8_g_echoState = US_ECHO_STATE_WAITING;

    // request ICU to listen to echo pin and wait for time elapsed response
    ICU_getCaptureValue(); // async

    // send trigger signal
    DIO_setPinVal((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, HIGH); // takes 21uS to complete
//    DIO_setPinVal(DIO_PORTB, DIO_PIN_3, HIGH);
    // todo delay 10uS ?
    DIO_setPinVal((en_DIO_port_t) st_g_usConfig.US_Port, (en_DIO_pin_t) st_g_usConfig.triggerPin, LOW);
//    DIO_setPinVal(DIO_PORTB, DIO_PIN_3, LOW);

    // wait for reading
    while(u8_g_echoState == US_ECHO_STATE_WAITING);

    if(u32_g_lastElapsedTime == 0) return 0; // fail
//    return u32_g_lastElapsedTime;
    // calculate distance from time (uS)
    u16 u16_l_echoDistance = CALC_DISTANCE_CM(u32_g_lastElapsedTime);
    u16_l_echoDistance = (u16_l_echoDistance > US_FALSE_DISTANCE_COMPENSATE ? u16_l_echoDistance - US_FALSE_DISTANCE_COMPENSATE : 0);
    if(u16_l_echoDistance > MIN_SUPPORTED_DISTANCE_CM && u16_l_echoDistance < MAX_SUPPORTED_DISTANCE_CM)
    {
        return u16_l_echoDistance;
    }else{
        return u16_l_echoDistance;
    }
}

/**
 * Event Handler: called when echo time is received from ICU (input capture unit)
 *
 * This function is called by the ICU as an event callback when the trigger signal
 * is received back on the echo pin, the function receives the elapsed time taken.
 *
 * @param [in]u32_a_timeElapsed time elapsed (duration) by trigger signal to echo back
 */
void US_evtEchoTimeReceived(u32 u32_a_timeElapsed)
{
    u32_g_lastElapsedTime = u32_a_timeElapsed;
    u8_g_echoState = US_ECHO_STATE_RECEIVED;
}