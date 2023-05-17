/*
 * icu_program.c
 *
 * Created: 15/5/2023 11:44:50 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 

#include "icu_interface.h"

/* Runtime Macros */
#define ICU_STATE_WAIT 0
#define ICU_STATE_COMPLETE 1

// configuration
st_ICU_config_t st_g_ICU_config;
u8 u8_g_icuState = ICU_STATE_WAIT;
u16 u16_g_icuLastCaptureValue = 0;
const en_TIMER_number_t const_g_icuTimer = TIMER_2;

/**
 * Initializes the ICU driver
 *
 * This function initializes a software ICU driver, init echo pin as input,
 * uses timer to calculate elapsed time, when echo pin is triggered it sends the
 * elapsed time duration to the callback function
 *
 * configuration -> icu_cfg.c, or on the fly using ICU_setConfig() before initialization
 */
en_ICU_error_t ICU_init(void)
{
    // Fetch configuration
    st_ICU_config_t st_l_config = ICU_getConfig();
    // todo-hossam PIN/PORT check
    // initialize capture pin
    // enable EXI
    // init timer
    switch (st_l_config.icuCapturePin) {
        case PORT_D_PIN_2:
            // initialize capture pin direction
            DIO_setPinDir(DIO_PORTD, DIO_PIN_2, INPUT);
            // write low on capture pin
            DIO_setPinVal(DIO_PORTD,DIO_PIN_2, LOW);

            // enable external interrupt
            EXTI_init(EXTI0);

            // todo init timer
            break;
        case PORT_D_PIN_3:
            // initialize capture pin direction
            DIO_setPinDir(DIO_PORTD, DIO_PIN_3, INPUT);
            // write low on capture pin
            DIO_setPinVal(DIO_PORTD,DIO_PIN_3, LOW);
            // enable external interrupt
            EXTI_init(EXTI1);

            TIMER_init();
            TIMER_enableInterrupt(const_g_icuTimer);

            // enable external interrupt
            EXTI_init(EXTI2);

            // todo init timer
            break;
        default:
            return ICU_ERROR;
    }

    
}

/**
 * Resets and starts the ICU algorithm to capture the elapsed time by the trigger signal
 * to rebound back on the echo/capture PIN
 *
 * @return elapsed time in uS
 */
u16 ICU_getCaptureValue(void)
{
    // reset and restart timer
    // todo timer
    while(u8_g_icuState == ICU_STATE_WAIT);

    // disable EXI
    EXTI_setState((en_EXTI_num_t) st_g_ICU_config.icuCapturePinData.interruptNo,
                  EXTI_DISABLE);

    // todo return time elapsed
    return u16_g_icuLastCaptureValue;
}

/**
 * Handles Interrupts/Events on the capture input pin
 * */
void ICU_inputHandler(void)
{
    u8 u8_l_capturePinValue = 0;
    DIO_getPinVal(st_g_ICU_config.icuCapturePin == PORT_B_PIN_2 ? DIO_PORTB : DIO_PORTD,
                  st_g_ICU_config.icuCapturePin == PORT_D_PIN_3 ? DIO_PIN_3 : DIO_PIN_2,
                  &u8_l_capturePinValue);

    // if HIGH reset timer and start counting
    if(u8_l_capturePinValue){
        // todo reset and restart timer
        TIMER_reset(const_g_icuTimer);
        TIMER_resume(const_g_icuTimer);

    }else{
        // if LOW = signal rebound complete, send elapsed time back
        u8_g_icuState = EXTI_OK;

        u16_g_icuLastCaptureValue = 0; // todo get from timer TCNT
        u8_g_icuState = ICU_STATE_COMPLETE;
    }
}