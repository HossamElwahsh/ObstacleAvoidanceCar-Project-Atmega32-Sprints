/*
 * icu_cfg.c
 *
 * Created: 15/5/2023 11:48:58 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 

#include "icu_cfg.h"

static st_ICU_config_t st_gs_icuConfig = {
    // Echo PORT
	PORT_B,
    // Echo PIN
	PIN_2,

    // Callback Function on time received
	NULL // callback function
};

/* Functions */
st_ICU_config_t ICU_getConfig()
{
	return st_gs_icuConfig;
}

void ICU_setConfig(st_ICU_config_t st_a_icuConfig)
{
    st_gs_icuConfig = st_a_icuConfig;
}