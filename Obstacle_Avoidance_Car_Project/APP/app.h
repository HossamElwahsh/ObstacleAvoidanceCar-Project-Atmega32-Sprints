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
#define APP_INC_SPEED_TIME		5000
#define APP_DELAY_START_TIME	2000
#define APP_U8_STOP_SPEED		0
#define APP_U8_ZERO_DIST		0
#define APP_U8_SPEED_30			30
#define APP_U8_SPEED_50			50
#define APP_U8_DIST_30			30
#define APP_U8_DIST_20			20

#define APP_RIGHT_SIDE_MOTORS	DCM_0
#define APP_LEFT_SIDE_MOTORS	DCM_1
#define APP_ROTATION_TIME_MS	550

#define APP_CHAR_DIR_FWD		'F'
#define APP_CHAR_DIR_BACK		'B'
#define APP_CHAR_DIR_ROTATE		'R'
#define APP_CHAR_DIR_STOP		'S'

#define APP_LCD_LINE_START      LCD_POS_0
#define APP_LCD_MIN_DIST_POS	LCD_POS_9
#define APP_LCD_MIDDLE_DIST_POS LCD_POS_8
#define APP_LCD_MIDDLE_DIST_POS LCD_POS_8
#define APP_MAX_2_DIGITS        99
#define APP_MAX_1_DIGIT         9

#define DELAY_NOT_DONE          0
#define DELAY_DONE              1

/* End Line 60 */
/* Hossam Macros */
#define APP_U8_CAR_SPEED_0 0
#define APP_U8_CAR_SPEED_30 30
#define APP_U8_CAR_SPEED_70 70
#define APP_STR_CAR_SPEED_0 "00"
#define APP_STR_CAR_SPEED_30 "30"
#define APP_STR_SET_DEF_ROTATION "Set Def. Rot."
#define APP_STR_ROT_RIGHT "Right"
#define APP_STR_ROT_LEFT "Left " // keep the space to clear old value characters (Right)

#define APP_DIR_RIGHT   0
#define APP_DIR_LEFT    1

#define APP_DIR_STATE_STOP      0
#define APP_DIR_STATE_FORWARD   1
#define APP_DIR_STATE_BACKWARD  2
#define APP_DIR_STATE_ROTATING  3

#define TOGGLE_BTN_PORT     2
#define TOGGLE_BTN_PIN      4
#define APP_LCD_LINE_1      0
#define APP_LCD_LINE_2      1
#define APP_LCD_SPEED_POS   6
#define APP_LCD_DIR_POS     14
#define APP_LCD_DIST_POS    7
/* End Line 79 */
void APP_initialization(void);

void APP_startProgram(void);

void APP_switchState(u8 u8_a_state);

void APP_delayNotification(void);

#endif /* APP_H_ */