/*
 * File:   Button_Main.c
 * Author: Jacques
 *
 * Created on January 30, 2019, 3:07 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <BUTTONS.h>
#include <stdint.h>
#include <stdio.h>
#include <plib.h>
#include <serial.h>

int count0 = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;


void __ISR(_CHANGE_NOTICE_VECTOR, ipl1auto) ChangeNotice_Handler(void)
{
    static char TRNL1 = 0;
    TRNL1 = PORTDbits.RD5;
    static char CIRC1 = 0;
    CIRC1 = PORTDbits.RD6;
    static char TRNL2 = 0;
    TRNL2 = PORTDbits.RD7;
    static char CIRC2 = 0;
    CIRC2 = PORTFbits.RF1;
    INTClearFlag(INT_CN);
    if (TRNL1) {
        printf("TRNGL1 pressed");
        count0 = 1;
    }
    if (CIRC1) {
        printf("CIRC1 pressed");
        count1 = 1;
    }
    if (TRNL2) {
        printf("TRNL2 pressed");
        count2 = 1;
    }
    if (CIRC2) {
        printf("CIRC2 pressed");
        count3 = 1;
    }
}

int main(void)
{
    BOARD_Init();
    BUTTONS_Init();



}
