/*
 * icu_cfg.h
 *
 * Created: 15/5/2023 11:45:28 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 


#ifndef ICU_CFG_H_
#define ICU_CFG_H_

#include "icu_interface.h"

st_ICU_config_t ICU_getConfig();
void ICU_setConfig(st_ICU_config_t st_a_icuConfig);

#endif /* ICU_CFG_H_ */