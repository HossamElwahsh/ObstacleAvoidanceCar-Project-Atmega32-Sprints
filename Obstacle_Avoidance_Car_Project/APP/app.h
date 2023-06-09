/*
 * app.h
 *
 * Created: 17/5/2023 5:59:42 AM
 *  Author: Alaa & Hossam
 */
#ifndef APP_H_
#define APP_H_

/* LIB */
#include "../LIB/std.h"
#include "../LIB/interrupts.h"

/* HAL */
#include "../ECUAL/delay/delay_interface.h"
#include "../ECUAL/btn/button_interface.h"
#include "../ECUAL/kpd/keypad_interface.h"
#include "../ECUAL/lcd/lcd_interface.h"
#include "../ECUAL/us/us_interface.h"
#include "../ECUAL/dcm/dcm_interface.h"

/* APP States */
#define APP_STATE_INIT      0
#define APP_STATE_SET_DIR   1
#define APP_STATE_STARTING  2
#define APP_STATE_RUNNING   3

/* Macros */

/* Alaa Macros */

// This is workaround as there's no more times in ATmega32 to be used as async delay
// as the available delay timer is used by the ultrasonic in this particular case to keep
// monitoring the distance while the 5000ms starting time is done
// each loop takes 120ms to complete its commands, 42 loops -> total delay 5000ms
#define APP_INC_SPEED_DELAY_LOOPS		42
#define APP_INC_SPEED_DELAY_PER_LOOP	50  // 50ms + commands takes 70ms

#define APP_DELAY_START_TIME	2000
#define APP_U8_STOP_SPEED		0
#define APP_U8_ZERO_DIST		0
#define APP_U8_SPEED_30			30  // 30%
#define APP_U8_SPEED_50			50  // 50%
#define APP_U8_DIST_20			20  // 20cm
#define APP_U8_DIST_30			30  // 30cm
#define APP_U8_DIST_70			70  // 70cm

#define APP_RIGHT_SIDE_MOTORS	DCM_0
#define APP_LEFT_SIDE_MOTORS	DCM_1
#define APP_ROTATION_TIME_MS	650

#define APP_CHAR_DIR_FWD		'F'
#define APP_CHAR_DIR_BACK		'B'
#define APP_CHAR_DIR_ROTATE		'R'
#define APP_CHAR_DIR_STOP		'S'

#define APP_LCD_LINE_START      LCD_POS_0
    #define APP_LCD_DIST_POS    LCD_POS_7
#define APP_MAX_2_DIGITS        99
#define APP_MAX_1_DIGIT         9

#define DELAY_NOT_DONE          0
#define DELAY_DONE              1

/* End Line 60 */
/* Hossam Macros */
#define APP_DELAY_SET_DIR_TIMEOUT	5000
#define APP_DELAY_4_ROTATE_WAIT	    3000
#define APP_ROTATIONS_BEFORE_STOP   4       // rotations done by the robot before it stops if no where to go (all sides are blocked)
#define APP_U8_CAR_SPEED_0  0
#define APP_U8_CAR_SPEED_70 70
#define APP_U8_CAR_SPEED_70 70
#define APP_STR_SET_DEF_ROTATION "Set Def. Rot:"
#define APP_STR_ROT_RIGHT "Right"
#define APP_STR_ROT_LEFT "Left " // keep the space to clear old value characters (Right)
#define APP_DIR_RIGHT   0
#define APP_DIR_LEFT    1
#define APP_ZERO 0

#define TOGGLE_BTN_PORT     2
#define TOGGLE_BTN_PIN      4
#define APP_LCD_LINE_1      0
#define APP_LCD_LINE_2      1
#define APP_LCD_SPEED_POS   6
#define APP_LCD_DIR_POS     14


/**
 * @brief Initializes the application by initializing the MCAL and HAL components.
 *
 * @details This function initializes the external interrupt, SPI, timer0, buzzer, button, keypad, and LCD.
 * It also clears the LCD's display and switches to the entry point state.
 *
 * @return void
 */
void APP_initialization(void);

/**
 * @brief Start the application program flow for ATM
 *
 * This function starts the application program and enters an infinite loop that continuously polls
 * the application state and executes the corresponding actions according to the current state.
 *
 * @return void
 */
void APP_startProgram(void);

/**
 * @brief Used to switch between app states to initialize standard UI elements before main app flow (loop)
 *
 * @param [in]u8_a_state state to set (APP_STATE_LAUNCH, APP_STATE_...)
 *
 * @return void
 */
void APP_switchState(u8 u8_a_state);

/**
 * @brief Updates the delay flag when the delay overflow interrupt is set
 */
void APP_delayNotification(void);

#endif /* APP_H_ */