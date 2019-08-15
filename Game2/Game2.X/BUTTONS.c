/*
 * File:   BUTTONS.c
 * Author: 
 * 
 */

#include <xc.h>
#include <BOARD.h>
//#include <timers.h>
#include "BUTTONS.h"
//#include <serial.h>
#include <stdio.h>
#include <plib.h>

#define TRNGL1 PORTDbits.RD2
#define CIRCL1 PORTDbits.RD1
#define TRNGL2 PORTDbits.RD6
#define CIRCL2 PORTDbits.RD9
#define SQUARE1 PORTDbits.RD7
#define SQUARE2 PORTDbits.RD5

int count = 100000;
int last_count = 100000;

char BUTTONS_Init(void) {
    OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_64, 0x7A12);
    INTClearFlag(INT_T4);
    INTSetVectorPriority(INT_TIMER_4_VECTOR, 3);
    INTSetVectorSubPriority(INT_TIMER_4_VECTOR, 3);
    INTEnable(INT_T4, INT_ENABLED);

    //Anything else that needs to occur goes here

    TRISDbits.TRISD6 = 1; // TRG2 BTN4   pin 36
    TRISDbits.TRISD9 = 1; // CIRC2 BTN3  pin 7
    TRISDbits.TRISD2 = 1; // TRG1 BTN2   pin 6
    TRISDbits.TRISD1 = 1; // CIRC1 BTN1  pin 5
    TRISDbits.TRISD7 = 1; //  BTN   pin 37
    TRISDbits.TRISD5 = 1; //  BTN  pin 34

}

void __ISR(_TIMER_4_VECTOR, ipl3auto) Timer4IntHandler(void) {
    INTClearFlag(INT_T4);
    if (TRNGL1) {
        count = TRNGL1_PRESSED;
    } else if (CIRCL1) {
        count = CIRCL1_PRESSED;
    } else if (TRNGL2) {
        count = TRNGL2_PRESSED;
    }else if (CIRCL2) {
        count = CIRCL2_PRESSED;
    } else if (SQUARE1) {
        count = SQUARE1_PRESSED;
    }else if (SQUARE2) {
        count = SQUARE2_PRESSED;
    } else if (!(TRNGL1 || CIRCL1 || TRNGL2 || CIRCL2 || SQUARE1 || SQUARE2)) {
        count = BUTTONS_RELEASED;
    }
}

int BUTTONS_Event(void) {
    
        if (last_count != count) {
            //printf(" %d\r\n", count);
            last_count = count;
        }
        
    return count;
}