#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdint.h>
#include <stdio.h>
#include <BUTTONS.h>
#include <timers.h>

int count = 100000;


void __ISR(_CHANGE_NOTICE_VECTOR, ipl1auto) ChangeNotice_Handler(void){
    static char TRNGL1 = 0;
    TRNGL1 = PORTDbits.RD5;
    static char CIRCL1 = 0;
    CIRCL1 = PORTFbits.RF1;
    static char TRNGL2 = 0;
    TRNGL2 = PORTDbits.RD7;
    static char CIRCL2 = 0;
    CIRCL2 = PORTDbits.RD6;
    INTClearFlag(INT_CN);
    
    if (TRNGL1) {
        count = TRNGL1_PRESSED;
    }else if (CIRCL1) {
        count = CIRCL1_PRESSED;
    }else if (TRNGL2) {
        count = TRNGL2_PRESSED;
    }else if (CIRCL2) {
        count = CIRCL2_PRESSED;
    }else if (!(TRNGL1 || CIRCL1 || TRNGL2 || CIRCL2)){
        count = BUTTONS_RELEASED;
    }
}


//function that will initialize buttons as inputs to UNO32 and will initialize other helper variables

void BUTTONS_Init(void){
    mCNOpen(CN_ON, (CN16_ENABLE | CN15_ENABLE | CN14_ENABLE), 0); // CNA CNB 
    int temp = PORTD;
    ConfigIntCN(CHANGE_INT_ON | CHANGE_INT_PRI_1);

    TRISFbits.TRISF1 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;

}

//function that will return a number corresponding to the event that has just occurred from the buttons
int BUTTONS_Event(void) {
    return count;
}