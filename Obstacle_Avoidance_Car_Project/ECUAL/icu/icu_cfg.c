/*
 * icu_cfg.c
 *
 * Created: 15/5/2023 11:48:58 PM
 *  Author: Hossam Elwahsh - https://github.com/HossamElwahsh/
 */ 

#include "icu_cfg.h"

/* Predefined Pin options */
st_ICU_capturePins_t st_ICU_predefinedPins = {
        .PORT_D_PIN_2 = {
                .capturePin = PIN_2,
                .capturePort = PORT_D,
                .interruptNo = INT0
        },
        .PORT_D_PIN_3 = {
                .capturePin = PIN_3,
                .capturePort = PORT_D,
                .interruptNo = INT1
        },
        .PORT_B_PIN_2 = {
                .capturePin = PIN_2,
                .capturePort = PORT_B,
                .interruptNo = INT2
        }
};

/* Configuration */
static st_ICU_config_t st_gs_icuConfig = {
    // Capture Pin
	.icuCapturePin = PORT_B_PIN_2,

    // Callback Function on time received
	.timeReceivedCallbackFun = NULL // callback function
};

/* Functions */
st_ICU_config_t ICU_getConfig()
{
    switch (st_gs_icuConfig.icuCapturePin) {
        case PORT_D_PIN_2:
            st_gs_icuConfig.icuCapturePinData = st_ICU_predefinedPins.PORT_D_PIN_2;
            break;
        case PORT_D_PIN_3:
            st_gs_icuConfig.icuCapturePinData = st_ICU_predefinedPins.PORT_D_PIN_3;
            break;
        case PORT_B_PIN_2:
            st_gs_icuConfig.icuCapturePinData = st_ICU_predefinedPins.PORT_B_PIN_2;
            break;
    }
	return st_gs_icuConfig;
}

void ICU_setConfig(st_ICU_config_t st_a_icuConfig)
{
    st_gs_icuConfig = st_a_icuConfig;
}