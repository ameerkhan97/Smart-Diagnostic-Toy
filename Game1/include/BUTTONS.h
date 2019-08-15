/* 
 * File:   BUTTONS.h
 * Author: Tolu Familoni
 *
 * Created on January 23, 2019
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "xc.h"
#include "serial.h"
#include <BOARD.h>



    // Define macros for referring to the single-bit values of the buttons.
    //#define TRNGL1 PORTFbits.RF1
    //#define CIRCL1 PORTDbits.RD5
    //#define TRNGL2 PORTDbits.RD6
    //#define CIRCL2 PORTDbits.RD7
#define TRNGL2_PRESSED 0
#define CIRCL2_PRESSED 1
#define TRNGL1_PRESSED 2
#define CIRCL1_PRESSED 3
#define BUTTONS_RELEASED 6

#define LOW 0
#define HIGH 1    

    void BUTTONS_Init(void);
    int BUTTONS_Event(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

