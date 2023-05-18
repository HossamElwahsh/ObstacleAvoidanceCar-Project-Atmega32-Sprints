/*
 * ObstacleAvoidanceCar.c
 *
 * Created: 15/5/2023 3:47:05 PM
 * Author : hossam
 */

#include "ECUAL/lcd/lcd_interface.h"
#include "ECUAL/kpd/keypad_interface.h"
#include "ECUAL/delay/delay_interface.h"
#include "ECUAL/us/us_interface.h"
#include "MCAL/dio/dio_interface.h"
#include "LIB/interrupts.h"

en_DIO_pin_t startPin = DIO_PIN_6;
en_DIO_pin_t stopPin = DIO_PIN_7;

void testCallback();

int testTimerDelay(void) {
    sei();
    DELAY_init();
    DELAY_setTimeNonBlocking(100);
    DELAY_setCallBack(testCallback);
    TIMER_reset(TIMER_1);
    TIMER_resume(TIMER_1);
    while (1) {
    }
}


//<editor-fold desc="test ultrasonic">
int testUltrasonic(void) {
    DELAY_init();
    LCD_vidInit();
    LCD_WriteString((u8 *)"test distance");
    DIO_setPinDir(DIO_PORTB, startPin, OUTPUT);
    DIO_setPinDir(DIO_PORTB, stopPin, OUTPUT);

    DIO_setPinVal(DIO_PORTB, startPin, LOW);
    DIO_setPinVal(DIO_PORTB, stopPin, LOW);
    US_init();

    DELAY_setTime(500);

    while (1) {
//        DIO_setPinVal(DIO_PORTB, startPin, LOW);

        LCD_ClrDisplay();
        LCD_WriteString((u8 *) "Retrieving");
        u16 distance = US_getDistance();
        LCD_ClrDisplay();
        LCD_WriteInt(distance);
        LCD_WriteString((u8 *) "cm");
        /*if(distance == 0)
        {
            LCD_WriteString("Error!");
        }
        else if(distance < 20)
        {
            LCD_WriteString("less than 20");
        }
        else if(distance > 20 && distance < 30)
        {
            LCD_WriteString("betw 20 & 30");
        }
        else if(distance > 30 && distance < 70)
        {
            LCD_WriteString("betw 30 & 70");
        }
        else if(distance > 70)
        {
            LCD_WriteString("More than 70");
        }*/
        DELAY_setTime(500);
        LCD_ClrDisplay();
    }
}
//</editor-fold>

void testKeypad()
{
    u8 btn = KEYPAD_getButton();
    if(btn != KPD_KEY_NOT_PRESSED)
    {
        if(btn == KPD_KEY_START)
        {
            DIO_setPinVal(DIO_PORTB, startPin, HIGH);
            DIO_setPinVal(DIO_PORTB, stopPin, LOW);
        }else if(btn == KPD_KEY_STOP)
        {
            DIO_setPinVal(DIO_PORTB, startPin, LOW);
            DIO_setPinVal(DIO_PORTB, stopPin, HIGH);
        }
    }
}

int main() {
    testUltrasonic();
}


void testCallback() {
    DIO_togPinVal(DIO_PORTB, startPin);
    DELAY_setTimeNonBlocking(100);
    u32 elapsed = 0;
    TIMER_getElapsedTime(TIMER_1, &elapsed);
    TIMER_reset(TIMER_1);
    TIMER_resume(TIMER_1);
}