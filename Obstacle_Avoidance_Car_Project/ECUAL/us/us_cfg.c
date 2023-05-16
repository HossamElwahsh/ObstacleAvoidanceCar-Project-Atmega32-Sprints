/*
 * us_cfg.c
 *
 * Created: 15/5/2023 11:47:45 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 

#include "us_cfg.h"

static st_US_config_t st_gs_usConfig = {
	PORT_B,
	PIN_2,
	PIN_3,
};

st_US_config_t US_getConfig()
{
	return st_gs_usConfig;
}

void US_setConfig(st_US_config_t st_a_usConfig)
{
    st_gs_usConfig = st_a_usConfig;
}