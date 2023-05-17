
/*
 * app.c
 *
 * Created: 17/5/2023 5:59:37 AM
 *  Author: Alaa & Hossam
 */
#include "app.h"
u8 u8_g_currentCarDir = APP_DIR_STATE_STOP;
u8 u8_g_currentSpeed = 0;
u8 u8_g_state = APP_STATE_INIT;
u8 u8_g_dirChange = APP_DIR_RESET;
u8 u8_g_defaultDirection = APP_DIR_RIGHT;
u8 u8_g_delayState = DELAY_NOT_DONE;

static void APP_updateUI(u8 u8_a_speed, u8 u8_a_dir, u16 u16_a_dist)
{
    u8 u8_l_cursorPos;

    /* Display speed and direction on LCD line one */
    LCD_gotoXY(LCD_ROW_1, LCD_POS_1);
    LCD_WriteString((u8 *) "Speed:00%  Dir:S");
    LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_SPEED_POS);
    LCD_WriteInt(u8_a_speed);
    LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_DIR_POS);
    LCD_vidWriteChar(u8_a_dir);

    /* Display Distance on LCD line two */
    if(u16_a_dist > APP_MAX_2_DIGITS) u8_l_cursorPos = APP_LCD_DIST_POS;
    if(u16_a_dist > APP_MAX_1_DIGIT) u8_l_cursorPos = APP_LCD_MIDDLE_DIST_POS;
    else u8_l_cursorPos = APP_LCD_MIN_DIST_POS;

    LCD_gotoXY(APP_LCD_LINE_2, LCD_POS_1);
    LCD_WriteString((u8 *)"Dist.: 000 Cm");
    LCD_gotoXY(APP_LCD_LINE_2, APP_LCD_DIST_POS);
    LCD_WriteInt(u16_a_dist);
}


void APP_initialization(void)
{
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
    PWM_init();
    // enable global interrupt (SEI)
    sei();
    // switch to init state
    APP_switchState(APP_STATE_INIT);
}

void APP_startProgram(void)
{
	u16 u16_l_lastDist = APP_U8_ZERO_DIST;
	
    while(1)
    {
        // -> check for keypad stop key

        switch (u8_g_state) {
            case APP_STATE_INIT: // todo-(Alaa)
                // wait for start button
                if(KEYPAD_getButton() == 0/*START_KEY*/) //Get key before switch or here??
                {
                    APP_switchState(APP_STATE_SET_DIR);
                }
				
                break;
				
            case APP_STATE_SET_DIR: // donetodo-(Hossam)
            {   // 5 sec timeout
                // check for BTN0 -> toggle Right/Left
                while(1) // <- todo async timer didn't finish counting 5 seconds yet
                {
                    if(KEYPAD_getButton() == 1) // todo update magic number to be STOP_KEY or something
                    {
                        APP_switchState(APP_STATE_INIT); // stop everything
                        // todo cancel timer or create a STOP state that cancels everything
                    }
                    u8 u8_l_toggleBtnState = 0;
                    BUTTON_read(TOGGLE_BTN_PORT,
                                TOGGLE_BTN_PIN,
                                &u8_l_toggleBtnState);
                    if(u8_l_toggleBtnState != 0) // Toggle Button Pressed // todo remove magic number (use btn enum)
                    {
                        // Toggle direction
                        u8_g_defaultDirection = u8_g_defaultDirection == APP_DIR_RIGHT ? APP_DIR_LEFT : APP_DIR_RIGHT;
                        // update LCD
                        LCD_gotoXY(1, 0);
                        LCD_WriteString((u8 *) (u8_g_defaultDirection == APP_DIR_RIGHT ?
                            APP_STR_ROT_RIGHT:
                            APP_STR_ROT_LEFT
                        ));
                    }


                }
            } /* line 107 */
                break;
				
            case APP_STATE_STARTING: // todo-(Alaa)
                // wait 2 seconds (Async)
                DELAY_setTimeNonBlocking(APP_DELAY_START_TIME);
				DELAY_setCallBack(APP_delayNotification);

                /* Check whether stop key is pressed or delay done */
                while (u8_g_delayState == DELAY_NOT_DONE)// check flag from CBF
                {
                    if (KEYPAD_getButton() == 1/*Stop*/)
                    {
                        /* Reset to init state */
                        APP_switchState(APP_STATE_INIT);
                    }
                }

                /* reset flag from CBF */
				u8_g_delayState = DELAY_NOT_DONE;
				
				/* Change robot state to running */
                APP_switchState(APP_STATE_RUNNING);

                break;

            case APP_STATE_RUNNING:
            {
                // check distance
                // Range (2 cm - 400 cm)
                // if 0: fail
                u16 u16_l_distanceCm = US_getDistance();
                LCD_gotoXY(APP_LCD_LINE_2, APP_LCD_DIST_POS);
                LCD_WriteInt(u16_l_distanceCm);
                /* if statements */
                // X4 Ifs
                // > 70 // todo-(Alaa)
                if(u16_l_distanceCm > 70)
                {
                    if(u16_l_lastDist <= APP_U8_CAR_SPEED_70)
                    {
                        DELAY_setTimeNonBlocking(APP_INC_SPEED_TIME);
						DELAY_setCallBack(APP_delayNotification);
                    }

					/* Change speed to 50% after 5 seconds */
                    if(u8_g_delayState == DELAY_DONE) 
					{
						/* Reset delay notification flag */
						u8_g_delayState = DELAY_NOT_DONE;
						
						/* Update Speed */
						u8_g_currentSpeed = APP_U8_SPEED_50;
					}

                    DCM_speed(u8_g_currentSpeed);
                    DCM_start();

                }
                // 30 < distance < 70 // donetodo-(Hossam)
                else if(u16_l_distanceCm > APP_U8_CAR_SPEED_30 && u16_l_distanceCm < APP_U8_CAR_SPEED_70)
                {
                    if(u8_g_currentCarDir != APP_DIR_STATE_FORWARD)
                    {
                        DCM_stop(); // stop motors
                        u8_g_currentCarDir = APP_DIR_STATE_FORWARD; // update global car direction indicator
                        LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_DIR_POS);
                        LCD_WriteString((u8 *) "F");
                        DCM_setDirection(DCM_0,DCM_CW); // forward direction
                        DCM_setDirection(DCM_1,DCM_CW); // forward direction
                        DCM_speed(APP_U8_CAR_SPEED_30); // update DCM speed
                        u8_g_currentSpeed = APP_U8_CAR_SPEED_30; // update global speed
                        DCM_start(); // start motors
                    }
                    // Update car speed to 30% if it's not
                    if(u8_g_currentSpeed != APP_U8_CAR_SPEED_30){
                        if(DCM_speed(APP_U8_CAR_SPEED_30) == DCM_OK)
                        {
                            // update global speed variable
                            u8_g_currentSpeed = APP_U8_CAR_SPEED_30;
                            // Update speed on LCD
                            LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_SPEED_POS); // 2 digit speed location
                            LCD_WriteString((u8 *) APP_STR_CAR_SPEED_30);
                        }
                    }

                }
                // 20 -> 30 // todo-(Alaa), todo-(Hossam) Bonus
                else if(u16_l_distanceCm > APP_U8_DIST_20 && u16_l_distanceCm < APP_U8_DIST_30)
                {
                    DCM_stop();

                    if(u8_g_defaultDirection == APP_DIR_LEFT)
                    {
                        /* Set motors on right side to rotate forward */
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_CW);

                        /* Set motors on left side to rotate backward */
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_ACW);
                    }

                    if(u8_g_defaultDirection == APP_DIR_RIGHT)
                    {
                        /* Set motors on left side to rotate forward */
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS, DCM_CW);

                        /* Set motors on right side to rotate backward */
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS, DCM_ACW);
                    }

                    DCM_speed(APP_U8_SPEED_30);
                    DCM_start();

                    // set sync. delay to rotation time
                    DELAY_setTime(APP_ROTATION_TIME_MS);



































                }
                // < 20  // donetodo-(Hossam)
                else if(u16_l_distanceCm < 20)
                {
                    if(u8_g_currentCarDir != APP_DIR_STATE_BACKWARD) // robot isn't moving backward
                    {
                        DCM_stop();
                        /* update car global variables (speed, dir) */
                        u8_g_currentCarDir = APP_DIR_STATE_BACKWARD;
                        u8_g_currentSpeed = APP_U8_CAR_SPEED_30;

                        /* set motors on right side to rotate backwards */
                        DCM_setDirection(APP_RIGHT_SIDE_MOTORS,DCM_ACW);

                        /* set motors on left side to rotate backwards */
                        DCM_setDirection(APP_LEFT_SIDE_MOTORS,DCM_ACW);

                        /* set DCM speed to 30% */
                        DCM_speed(APP_U8_CAR_SPEED_30); // set DCM speed to 30%

                        /* start motors */
                        DCM_start();

                        // update UI (LCD)
                        APP_updateUI(u8_g_currentSpeed, u8_g_currentCarDir, u16_l_distanceCm);
                    }







                    





                } /* 296 */
				
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

void APP_switchState(u8 u8_a_state)
{
    switch (u8_a_state) {
        case APP_STATE_INIT:

            // donetodo-Alaa

            /* Stop the robot */
            DCM_stop();

            /* Reset the delay module */
            DELAY_init();

            /* Display speed and direction on LCD line one */
            LCD_gotoXY(APP_LCD_LINE_1, APP_LCD_LINE_START);
            LCD_WriteString((u8 *)"Speed:00%  Dir:S");

            /* Initialize speed */
            u8_g_currentSpeed = APP_U8_CAR_SPEED_30;



            break;
        case APP_STATE_SET_DIR:
            // todo-Hossam
            LCD_ClrDisplay(); // clear display
            LCD_WriteString((u8 *) APP_STR_SET_DEF_ROTATION); // write "Set Def. Rot." on LCD line 1
            LCD_gotoXY(APP_LCD_LINE_2, 0); // goto next line (Line 2)
            LCD_WriteString((u8 *) APP_STR_ROT_RIGHT); // write "Right" on LCD line 2
            // todo start async timer delay 5 seconds






















            break;
        case APP_STATE_STARTING:
            // LCD output Line1,2 "SPEED:00% Dir:S\nDist.: 000 Cm"
            // donetodo-Alaa
            APP_updateUI(APP_U8_STOP_SPEED, APP_CHAR_DIR_STOP, APP_U8_ZERO_DIST);

            break;
        default:
            // Ignored
            break;
    }
    u8_g_state = u8_a_state;
}

void APP_delayNotification(void)
{
    u8_g_delayState = DELAY_DONE;
}