/*
 * app.h
 *
 * Created: 17/5/2023 5:59:42 AM
 *  Author: Alaa & Hossam
 */
#ifndef APP_H_
#define APP_H_

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/interrupts.h"

/* HAL */
#include "../../ECUAL/delay/delay_interface.h"
#include "../../ECUAL/btn/button_interface.h"
#include "../../ECUAL/kpd/keypad_interface.h"
#include "../../ECUAL/lcd/lcd_interface.h"
#include "../../ECUAL/us/us_interface.h"
#include "../../ECUAL/dcm/dcm_interface.h"

/* APP States */
#define APP_STATE_INIT      0
#define APP_STATE_SET_DIR   1
#define APP_STATE_STARTING  2
#define APP_STATE_RUNNING   3

/* Macros */
#define APP_DIR_SET         0
#define APP_DIR_RESET       1

/* Alaa Macros */





















/* End Line 54 */
/* Hossam Macros */
#define STR_CAR_SPEED_30 "30"
#define STR_SET_DEF_ROTATION "Set Def. Rot."
#define STR_ROT_RIGHT "Right"
#define STR_ROT_LEFT "Left"



















/* End Line 79 */
void APP_initialization(void);

void APP_startProgram(void);

void APP_switchState(u8 u8_a_state);

#endif /* APP_H_ */