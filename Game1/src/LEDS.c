/*LEDS.C
 *      **USES LEDS.h
 * BRIEF:
 *      source code to initialize and set UNO32 E  port registers
 */


#include <stdio.h>
#include <stdlib.h>
#include "LEDS.h"



//initialize the UNO32 E ports as digital outputs for LEDs

void LEDS_Init(void)
{
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;
    TRISEbits.TRISE4 = 0;
    TRISEbits.TRISE5 = 0;
    TRISEbits.TRISE6 = 0;
    TRISEbits.TRISE7 = 0;
}


//turn off all LEDs

void LEDS_Clear(void)
{
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
    LED8 = 0;

}


//turn on all LEDs

void LEDS_Set(void)
{
            LED1 = 1;
            LED2 = 1;
            LED3 = 1;
            LED4 = 1;
            LED5 = 1;
            LED6 = 1;
            LED7 = 1;
            LED8 = 1;
}


//select specific registers in UNO32 E ports and set/clear them
        //args: LEDS_Port(int port, int val)
            //int port --- LED port number: 1 - 8
            //int val  --- set port: 1; clear port: 0
void LEDS_Port(int port, int val)
{
    switch (port) {
    case 1:
        SPECIFICPIN(1) = val;
        break;
    case 2:
        SPECIFICPIN(2) = val;
        break;
    case 3:
        SPECIFICPIN(3) = val;
        break;
    case 4:
        SPECIFICPIN(4) = val;
        break;
    case 5:
        SPECIFICPIN(5) = val;
        break;
    case 6:
        SPECIFICPIN(6) = val;
        break;
    case 7:
        SPECIFICPIN(7) = val;
        break;
    case 8:
        SPECIFICPIN(8) = val;
        break;
    default:
        printf("Can't find pin\n");
        break;
    }



}






