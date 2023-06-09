/*
 * icu_program.c
 *
 * Created: 15/5/2023 11:44:50 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */

#include "icu_interface.h"
#include "icu_cfg.h"

/* Runtime Helping Macros */
#define ICU_STEP_1_WAIT_HIGH 0
#define ICU_STEP_2_WAIT_LOW 1

// configuration
st_ICU_config_t st_g_ICU_config;
u8 u8_g_icuStep = ICU_STEP_1_WAIT_HIGH;
const en_TIMER_number_t const_g_icuTimer = TIMER_2;

/* Private Helper Functions Prototypes */
static void ICU_inputHandler(void);

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
    st_g_ICU_config = ICU_getConfig();

    switch (st_g_ICU_config.icuCapturePin) {
        case PORT_D_PIN_2:
        case PORT_D_PIN_3:
        case PORT_B_PIN_2:
            sei(); // enable global interrupt
            u8 u8_l_pin = st_g_ICU_config.icuCapturePinData.capturePin;     // input capture pin
            u8 u8_l_port = st_g_ICU_config.icuCapturePinData.capturePort;   // input capture port
            u8 u8_l_exi = st_g_ICU_config.icuCapturePinData.interruptNo;    // input capture EXI INT number
            // initialize capture pin direction
            DIO_setPinDir(u8_l_port, u8_l_pin, INPUT);

            // init timer
            TIMER_init();
            // enable timer interrupt
            TIMER_enableInterrupt(const_g_icuTimer);

            // enable external interrupt
            EXI_init(u8_l_exi);
            EXI_setSense(u8_l_exi, RISING_EDGE);
            EXI_setCallback(u8_l_exi, ICU_inputHandler);
            break;

        default:
            return ICU_ERROR;
    }

    return ICU_OK;
}

/**
 * Resets and starts the ICU algorithm to capture the elapsed time by the trigger signal
 * to rebound back on the echo/capture PIN
 *
 * @return none, callback will fire when done (async)
 */
void ICU_getCaptureValue(void)
{
    // enable EXI on rising edge
    EXI_setSense((en_EXI_num_t) st_g_ICU_config.icuCapturePinData.interruptNo, RISING_EDGE);
    EXI_setState((en_EXI_num_t) st_g_ICU_config.icuCapturePinData.interruptNo,
                  EXI_ENABLE);
}

/**
 * Handles Interrupts/Events on the capture input pin
 * */
static void ICU_inputHandler(void)
{
    u8 u8_l_capturePinValue = 0;
    DIO_getPinVal(st_g_ICU_config.icuCapturePin == PORT_B_PIN_2 ? DIO_PORTB : DIO_PORTD,
                  st_g_ICU_config.icuCapturePin == PORT_D_PIN_3 ? DIO_PIN_3 : DIO_PIN_2,
                  &u8_l_capturePinValue);

    // if HIGH reset timer and start counting
    if(u8_l_capturePinValue == HIGH && u8_g_icuStep == ICU_STEP_1_WAIT_HIGH){
        /* Change interrupt sense to falling edge */
        EXI_setSense((en_EXI_num_t) st_g_ICU_config.icuCapturePinData.interruptNo, FALLING_EDGE);
        /* Reset and start timer */
        TIMER_reset(const_g_icuTimer);
        TIMER_resume(const_g_icuTimer);
        u8_g_icuStep = ICU_STEP_2_WAIT_LOW;
    }else if (u8_l_capturePinValue == LOW && u8_g_icuStep == ICU_STEP_2_WAIT_LOW){
        // if LOW = signal rebound complete, send elapsed time back
        /* Pause Timer */
        TIMER_pause(const_g_icuTimer);
        /* Get elapsed time */
        u32 u32_l_elapsed = 0;
        TIMER_getElapsedTime(const_g_icuTimer, &u32_l_elapsed);

        /* Reset timer */
        TIMER_reset(const_g_icuTimer);

        /* Disable EXI */
        EXI_setState((en_EXI_num_t) st_g_ICU_config.icuCapturePinData.interruptNo,
                      EXI_DISABLE);
        if(st_g_ICU_config.timeReceivedCallbackFun != NULL)
        {
            st_g_ICU_config.timeReceivedCallbackFun(u32_l_elapsed);
        }
        u8_g_icuStep = ICU_STEP_1_WAIT_HIGH;
    }
}