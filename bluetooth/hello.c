/*
 * File:   hello.c
 * Author: Jacques
 *
 * Created on March 11, 2019, 5:40 PM
 */


#include "xc.h"
#include "BOARD.h"
#include "serial.h"
#include "bluetooth_uart.h"
#include <stdio.h>
#include <stdlib.h>
#include<timers.h>

/*void BluetoothWriteString(const char * string)
{
    if (string == NULL) {
        return;
    }
    int i = 0;
    while (string[i] != '\0') {
        PutChar2(string[i]);
        i++;
    }

*/

int main(void)
{
    BOARD_Init();
    SERIAL2_Init();
    TIMERS_Init();
    printf("hello World");
    int one = 55;
    int two = 66;
    int three = 77;
    int four = 88;
    int five = 99;
    int six = 10;
    while (1) {
        if (TIMERS_GetMilliSeconds() % 2000 == 0) {
            char IMU_Data[100] = {0};
            sprintf(IMU_Data, "%d,%d,%d,%d,%d,%d\r\n", one, two, three, four, five, six);
            BluetoothWriteString(IMU_Data);
             one++;
        two++;
        three++;
        four++;
        five++;
        six++;

        }
       
    }
        //    while (1) {
        //        if (TIMERS_GetMilliSeconds() % 2000 == 0) {
        //            PutChar2('1');
        //            PutChar2(',');
        //            PutChar2('2');
        //            PutChar2(',');
        //            PutChar2('3');
        //            PutChar2('\r');
        //            PutChar2('\n')]
        //        }

        //PutChar2('b');
        // PutChar2('c');
        //}


        return 0;
    }
