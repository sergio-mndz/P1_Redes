/*
 * LED_Control.c
 *
 *  Created on: 2 nov 2021
 *      Author: sergio_mndz
 */

#include "LED_Control.h"

void turn_LED(uint8_t counter)
{
    LED_TurnOffAllLeds();

    switch (  counter )
    {
    case  0 :
        LED_TurnOnLed(LED2);
        break;
    case  1  :
        LED_TurnOnLed(LED3);
        break;
    case  2 :
        LED_TurnOnLed(LED4);
        break;
    case  3 :
        LED_TurnOnAllLeds();
        break;
    }
}
