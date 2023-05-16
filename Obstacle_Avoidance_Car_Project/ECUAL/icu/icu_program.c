/*
 * icu_program.c
 *
 * Created: 15/5/2023 11:44:50 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 

#include "icu_interface.h"

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

            // todo init timer
            break;
        case PORT_B_PIN_2:
            // initialize capture pin direction
            DIO_setPinDir(DIO_PORTB, DIO_PIN_2, INPUT);
            // write low on capture pin
            DIO_setPinVal(DIO_PORTB,DIO_PIN_2, LOW);

            // enable external interrupt
            EXTI_init(EXTI2);

            // todo init timer
            break;
        default:
            return ICU_ERROR;
    }

    
}

/**
 * Resets and starts the ICU algorithm to capture the elapsed time duration now
 * starting until echo signal is received back
 */
void ICU_getCaptureValue(void)
{
    // reset and restart timer
}