/*
 * icu_program.c
 *
 * Created: 15/5/2023 11:44:50 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 

#include "icu_interface.h"
#include "icu_cfg.h"


/**
 * Initializes the ICU driver
 *
 * This function initializes a software ICU driver, init echo pin as input,
 * uses timer to calculate elapsed time, when echo pin is triggered it sends the
 * elapsed time duration to the callback function
 *
 * configuration -> icu_cfg.c, or on the fly using ICU_setConfig() before initialization
 */
void ICU_init(void)
{
    // Fetch configuration
    st_ICU_config_t st_l_config = ICU_getConfig();

    
}

/**
 * Resets and starts the ICU algorithm to capture the elapsed time duration now
 * starting until echo signal is received back
 */
void ICU_getCaptureValue(void)
{

}