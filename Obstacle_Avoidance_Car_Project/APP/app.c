
/*
 * app.c
 *
 * Created: 17/5/2023 5:59:37 AM
 *  Author: Alaa & Hossam
 */

#include "app.h"

u8 u8_g_state = APP_STATE_INIT;
u8 u8_g_dirChange = APP_DIR_RESET;

void APP_initialization(void)
{
    // todo-Alaa
    // init button

    // init keypad

    // init delay

    // init DCM

    // init LCD

    // init Ultrasonic (US)

    // enable global interrupt (SEI)

    // switch to init state
    APP_switchState(APP_STATE_INIT);
}

void APP_startProgram(void)
{
    while(1)
    {
        // -> check for keypad stop key


        switch (u8_g_state) {
            case APP_STATE_INIT: // todo-(Alaa)
                // wait for start button










                break;
            case APP_STATE_SET_DIR: // todo-(Hossam)
                // 5 sec timeout
                // check for BTN0 -> toggle Right/Left










































                break;
            case APP_STATE_STARTING: // todo-(Alaa)
                // wait 2 seconds






































                break;

            case APP_STATE_RUNNING:
            {
                // check distance
                // Range (2 cm - 400 cm)
                // if 0: fail
                u16 u16_l_distanceCm = US_getDistance();
                // todo Hossam Update LCD Distance

                /* if statements */
                // X4 Ifs
                // > 70 // todo-(Alaa)
                if(u16_l_distanceCm > 70)
                {


































                }
                // 30 -> 70 // todo-(Hossam)
                else if(u16_l_distanceCm > 30 && u16_l_distanceCm < 70)
                {
                    DCM_speed(30);
                    // todo update LCD Speed
                    HLCD_gotoXY(0,6); // 2 digit speed location
                    HLCD_WriteString((u8 *) STR_CAR_SPEED_30);































                }
                // 20 -> 30 // todo-(Alaa), todo-(Hossam) Bonus
                else if(u16_l_distanceCm > 30 && u16_l_distanceCm < 70)
                {



































                }
                // < 20  // todo-(Hossam)
                else if(u16_l_distanceCm < 20)
                {



































                }
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
            // stop car
            // Write on LCD (stopped)
            // todo-Alaa
















            break;
        case APP_STATE_SET_DIR:
            // todo-Hossam
            HLCD_ClrDisplay();
            HLCD_WriteString((u8 *) STR_SET_DEF_ROTATION);

























            break;
        case APP_STATE_STARTING:
            // LCD output Line1,2 "SPEED:00% Dir:S\nDist.: 000 Cm"
            // todo-Alaa




























            break;
        default:
            // Ignored
            break;
    }
    u8_g_state = u8_a_state;
}