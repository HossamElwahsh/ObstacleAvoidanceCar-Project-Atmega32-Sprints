
/*
* app.c
*
* Created: 17/5/2023 5:59:37 AM
*  Author: Alaa & Hossam
*/
#include "app.h"

u8 u8_g_currentCarDir = APP_CHAR_DIR_STOP;
u8 u8_g_currentSpeed = APP_ZERO;
u8 u8_g_state = APP_STATE_INIT;

u8 u8_g_defaultDirection = APP_DIR_RIGHT;
u8 u8_g_delayState = DELAY_NOT_DONE;
u8 u8_g_rotCounter = APP_ZERO;


/**
 * Updates LCD (UI) with current speed (global), current direction (Fwd, Bck, Rot, Stp)
 * and current distance from obstacle in front of the robot
 *
 * @param [in]u16_a_dist distance between the robot and the obstacle in-front of it in CM
 *
 * @return void
 */
static void APP_updateUI(u16 u16_a_dist) {
    /* Display speed and direction on LCD line one */
    LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_SPEED_POS);
    LCD_WriteInt(u8_g_currentSpeed);
    LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_DIR_POS);
    LCD_vidWriteChar(u8_g_currentCarDir);

    LCD_gotoXY(APP_LCD_LINE_2, APP_LCD_DIST_POS);
    /* Display Distance on LCD line two */
    if (u16_a_dist <= APP_MAX_2_DIGITS && u16_a_dist > APP_MAX_1_DIGIT) {
        LCD_WriteString((u8 *) "0");
    } else if (u16_a_dist <= APP_MAX_1_DIGIT) {
        LCD_WriteString((u8 *) "00");
    }

    LCD_WriteInt(u16_a_dist);
}


/**
 * @brief Initializes the application by initializing the MCAL and HAL components.
 *
 * @details This function initializes the external interrupt, SPI, timer0, buzzer, button, keypad, and LCD.
 * It also clears the LCD's display and switches to the entry point state.
 *
 * @return void
 */
void APP_initialization(void) {
    // donetodo-Alaa
    // init button
    BUTTON_init(TOGGLE_BTN_PORT, TOGGLE_BTN_PIN);
    // init keypad
    KEYPAD_init();
    // init delay
    DELAY_init();
    // init DCM
    DCM_init();
    // init LCD
    LCD_vidInit();
    // init Ultrasonic (US)
    US_init();
    // enable global interrupt (SEI)
    sei();
    // switch to init state
    APP_switchState(APP_STATE_INIT);
}

/**
 * @brief Start the application program flow for ATM
 *
 * This function starts the application program and enters an infinite loop that continuously polls
 * the application state and executes the corresponding actions according to the current state.
 *
 * @return void
 */
void APP_startProgram(void) {
    u16 u16_l_lastDist = APP_U8_ZERO_DIST;

    while (TRUE) {

        switch (u8_g_state) {
            case APP_STATE_INIT: // donetodo-(Alaa)
                // wait for start button
                if (KEYPAD_getButton() == KPD_KEY_START)
                {
                    APP_switchState(APP_STATE_SET_DIR);
                }

                break;

            case APP_STATE_SET_DIR: // donetodo-(Hossam)
            {   // 5 sec timeout
                // check for BTN0 -> toggle Right/Left
                while (u8_g_delayState != DELAY_DONE) {
                    if (KEYPAD_getButton() == KPD_KEY_STOP) {
                        APP_switchState(APP_STATE_INIT); // stop everything
                        break;
                    }
                    en_buttonPosition_t u8_l_toggleBtnState = APP_ZERO;
                    BUTTON_read(TOGGLE_BTN_PORT,
                                TOGGLE_BTN_PIN,
                                &u8_l_toggleBtnState);
                    if (u8_l_toggleBtnState == BTN_RELEASED) // Toggle Button was pressed and released
                    {
                        // Toggle direction
                        u8_g_defaultDirection = u8_g_defaultDirection == APP_DIR_RIGHT ? APP_DIR_LEFT : APP_DIR_RIGHT;
                        // update LCD
                        LCD_gotoXY(APP_LCD_LINE_2, LCD_POS_0);
                        LCD_WriteString((u8 *) (u8_g_defaultDirection == APP_DIR_RIGHT ?
                                                APP_STR_ROT_RIGHT :
                                                APP_STR_ROT_LEFT
                        ));
                    }
                }
                if (u8_g_state == APP_STATE_SET_DIR)
                    APP_switchState(APP_STATE_STARTING); // goto next state after timeout is done
            } /* line 107 */
                break;

            case APP_STATE_STARTING: // donetodo-(Alaa)
                // wait 2 seconds (Async)
                DELAY_setTimeNonBlocking(APP_DELAY_START_TIME);
                DELAY_setCallBack(APP_delayNotification);
                LCD_ClrDisplay();
                LCD_gotoXY(APP_LCD_LINE_1, LCD_POS_2);
                LCD_WriteString((u8 *) "Starting....");
                LCD_gotoXY(APP_LCD_LINE_2, APP_LCD_LINE_START);
                LCD_WriteString(
                        u8_g_defaultDirection == APP_DIR_RIGHT ? (u8 *) "Direction:Right" : (u8 *) "Direction:Left");

                u8_g_delayState = DELAY_NOT_DONE;
                /* Check whether stop key is pressed or delay done */
                while (u8_g_delayState == DELAY_NOT_DONE)// check flag from CBF
                {
                    if (KEYPAD_getButton() == KPD_KEY_STOP) {
                        /* Reset to init state */
                        APP_switchState(APP_STATE_INIT);
                        break;
                    }
                }
                /* check if still in state */
                if(u8_g_state == APP_STATE_STARTING)
				{
					/* reset flag from CBF */
					u8_g_delayState = DELAY_NOT_DONE;

					/* Change robot state to running */
					APP_switchState(APP_STATE_RUNNING);
				}

                break;

            case APP_STATE_RUNNING: {
                // check distance
                // Range (2 cm - 400 cm)
                // if 0: fail
                u8 u8_g_delayCount;
                u16 u16_l_distanceCm = US_getDistance();
                APP_updateUI(u16_l_distanceCm);
                // X4 Ifs
                // > 70 // donetodo-(Alaa)
                if (u16_l_distanceCm > APP_U8_DIST_70) {
                    u8_g_currentCarDir = APP_CHAR_DIR_FWD;

                    if (u16_l_lastDist <= APP_U8_DIST_70) {
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_CW);
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_CW);
                        DCM_speed(u8_g_currentSpeed);
                        DCM_start();

                        for (u8_g_delayCount = APP_ZERO; u8_g_delayCount < APP_INC_SPEED_DELAY_LOOPS; u8_g_delayCount++) {
                            APP_updateUI(u16_l_distanceCm);
                            if (KEYPAD_getButton() == KPD_KEY_STOP) {
                                APP_switchState(APP_STATE_INIT);
                                break;
                            }

                            u16_l_distanceCm = US_getDistance();
                            if (u16_l_distanceCm <= APP_U8_DIST_70) break;

                            DELAY_setTime(APP_INC_SPEED_DELAY_PER_LOOP);
                        }
                    }

                    /* Change speed to 50% after 5 seconds */
					if(u8_g_state == APP_STATE_RUNNING)
					{
						/* Update Speed */
						u8_g_currentSpeed = APP_U8_SPEED_50;
						DCM_speed(u8_g_currentSpeed);
						APP_updateUI(u16_l_distanceCm);
                    }
                }
                    // 30 < distance < 70 // donetodo-(Hossam)
                else if (u16_l_distanceCm > APP_U8_DIST_30 && u16_l_distanceCm < APP_U8_CAR_SPEED_70) {
                    u8_g_rotCounter = APP_ZERO;

                    // check if stop is pressed
                    if (KEYPAD_getButton() == KPD_KEY_STOP) {
                        /* Reset to init state */
                        APP_switchState(APP_STATE_INIT);
                        break;
                    }

                    // car isn't moving forward?
                    if (u8_g_currentCarDir != APP_CHAR_DIR_FWD && u8_g_state == APP_STATE_RUNNING) {
                        DCM_stop(); // stop motors

                        // update global car direction indicator to Forward
                        u8_g_currentCarDir = APP_CHAR_DIR_FWD;

                        // forward direction left motors
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_CW);
                        // forward direction right motors
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_CW);

                        // update global speed
                        u8_g_currentSpeed = APP_U8_SPEED_30;

                        // update DCM speed
                        DCM_speed(u8_g_currentSpeed);

                        // update UI (LCD)
                        APP_updateUI(u16_l_distanceCm);
                        DCM_start(); // start motors
                    }
                    // Update car speed to 30% if it's not
                    if (u8_g_currentSpeed != APP_U8_SPEED_30 && u8_g_state == APP_STATE_RUNNING) {
                        if (DCM_speed(APP_U8_SPEED_30) == DCM_OK) {
                            // update global speed variable
                            u8_g_currentSpeed = APP_U8_SPEED_30;
                            // Update speed on LCD
                            APP_updateUI(u16_l_distanceCm);
                        }
                    }
                }
                    // 20 -> 30 // donetodo-(Alaa), donetodo-(Hossam) Bonus
                else if (u16_l_distanceCm > APP_U8_DIST_20 && u16_l_distanceCm < APP_U8_DIST_30) {
                    DCM_stop();
                    u8_g_currentCarDir = APP_CHAR_DIR_STOP;
                    u8_g_currentSpeed = APP_U8_STOP_SPEED;
                    APP_updateUI(u16_l_distanceCm);

                    if (u8_g_defaultDirection == APP_DIR_LEFT) {
                        /* Set motors on right side to rotate forward */
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_CW);

                        /* Set motors on left side to rotate backward */
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_ACW);
                    }

                    if (u8_g_defaultDirection == APP_DIR_RIGHT) {
                        /* Set motors on left side to rotate forward */
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_CW);

                        /* Set motors on right side to rotate backward */
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_ACW);
                    }

                    // update speed to 30
                    u8_g_currentCarDir = APP_CHAR_DIR_ROTATE;
                    u8_g_currentSpeed = APP_U8_SPEED_30;
                    DCM_speed(u8_g_currentSpeed);
                    // start DCM
                    DCM_start();
                    // update UI
                    APP_updateUI(u16_l_distanceCm);

                    // set sync. delay to rotation time
                    DELAY_setTime(APP_ROTATION_TIME_MS);

                    u8_g_rotCounter++;

                    u16_l_distanceCm = US_getDistance();
                    if (u16_l_distanceCm > APP_U8_DIST_30) {
                        u8_g_rotCounter = APP_ZERO;
                        continue;
                    }

                    if (u8_g_rotCounter == APP_ROTATIONS_BEFORE_STOP) {
                        DCM_stop();
                        DELAY_setTimeNonBlocking(APP_DELAY_4_ROTATE_WAIT);
                        u8_g_currentSpeed = APP_U8_CAR_SPEED_0;
                        u8_g_currentCarDir = APP_CHAR_DIR_STOP;
                        APP_updateUI(u16_l_distanceCm);

                        u8_g_delayState = DELAY_NOT_DONE;
                        /* Check whether stop key is pressed or delay done */
                        while (u8_g_delayState == DELAY_NOT_DONE)// check flag from CBF
                        {
                            if (KEYPAD_getButton() == KPD_KEY_STOP) {
                                /* Reset to init state */
                                APP_switchState(APP_STATE_INIT);
                                break;
                            }
                        }

                        /* reset flag from CBF */
                        u8_g_delayState = DELAY_NOT_DONE;
                        u8_g_rotCounter = APP_ZERO;
                    }
                }
                    // < 20  // donetodo-(Hossam)
                else if (u16_l_distanceCm < APP_U8_DIST_20) {
                    u8_g_rotCounter = APP_ZERO;

                    // check if stop is pressed
                    if (KEYPAD_getButton() == KPD_KEY_STOP) {
                        /* Reset to init state */
                        APP_switchState(APP_STATE_INIT);
                        break;
                    }
                    // robot isn't moving backward
                    if (u8_g_currentCarDir != APP_CHAR_DIR_BACK && u8_g_state == APP_STATE_RUNNING)
                    {
                        DCM_stop();
                        /* update car global variables (speed, dir) */
                        u8_g_currentCarDir = APP_CHAR_DIR_BACK;
                        u8_g_currentSpeed = APP_U8_SPEED_30;

                        /* set motors on right side to rotate backwards */
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_ACW);

                        /* set motors on left side to rotate backwards */
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_ACW);

                        /* set DCM speed to 30% */
                        DCM_speed(APP_U8_SPEED_30); // set DCM speed to 30%

                        /* start motors */
                        DCM_start();

                        // update UI (LCD)
                        APP_updateUI(u16_l_distanceCm);
                    }
                }

                /* Save the last measured distance */
                u16_l_lastDist = u16_l_distanceCm;
            }
                break;
            default:
                // Ignored
                break;
        }
    }
}

/**
 * @brief Used to switch between app states to initialize standard UI elements before main app flow (loop)
 *
 * @param [in]u8_a_state state to set (APP_STATE_LAUNCH, APP_STATE_...)
 *
 * @return void
 */
void APP_switchState(u8 u8_a_state) {
    switch (u8_a_state) {
        case APP_STATE_INIT:

            // donetodo-Alaa

            /* Stop the robot */
            DCM_stop();

            /* Reset the delay module */
            DELAY_init();

            /* Display speed and direction on LCD line one */
            LCD_ClrDisplay();
            LCD_gotoXY(APP_LCD_LINE_1, LCD_POS_4);
            LCD_WriteString((u8 *) "Welcome!");
            LCD_gotoXY(APP_LCD_LINE_2, LCD_POS_2);
            LCD_WriteString((u8 *) "Press  Start");

            /* Initialize speed */
            u8_g_currentSpeed = APP_U8_SPEED_30;

            /* Reset globals */
//            u8 u8_g_currentSpeed = APP_U8_SPEED_30;
            //u8 u8_g_defaultDirection = APP_DIR_RIGHT;
            u8_g_currentCarDir = APP_CHAR_DIR_STOP;
            u8_g_delayState = DELAY_NOT_DONE;
            u8_g_rotCounter = APP_ZERO;

            break;
        case APP_STATE_SET_DIR:
            // donetodo-Hossam
            LCD_ClrDisplay(); // clear display
            LCD_WriteString((u8 *) APP_STR_SET_DEF_ROTATION); // write "Set Def. Rot." on LCD line 1
            LCD_gotoXY(APP_LCD_LINE_2, APP_LCD_LINE_START); // goto next line (Line 2)
            // write "Right"/"Left" (last preferred direction) on LCD line 2
            LCD_WriteString((u8 *) (u8_g_defaultDirection == APP_DIR_RIGHT ?
                                    APP_STR_ROT_RIGHT :
                                    APP_STR_ROT_LEFT
            ));

            DELAY_setCallBack(APP_delayNotification);
            u8_g_delayState = DELAY_NOT_DONE; // reset delay flag
            DELAY_setTimeNonBlocking(APP_DELAY_SET_DIR_TIMEOUT); // start async timeout delay

            break;
        case APP_STATE_RUNNING:
            // LCD output Line1,2 "SPEED:00% Dir:S\nDist.: 000 Cm"
            // donetodo-Alaa
            LCD_ClrDisplay();
            LCD_WriteString((u8 *) "Speed:00% Dir:S");
            LCD_gotoXY(APP_LCD_LINE_2, APP_LCD_LINE_START);
            LCD_WriteString((u8 *) "Dist.: 000 Cm");

            break;
        default:
            // Ignored
            break;
    }
    u8_g_state = u8_a_state;
}

/**
 * @brief Updates the delay flag when the delay overflow interrupt is set
 */
void APP_delayNotification(void) {
    u8_g_delayState = DELAY_DONE;
}