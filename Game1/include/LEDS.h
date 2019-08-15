/* 
 * File:   LEDS.h
 * Author: Jacques
 *
 * 
 * BRIEF: This header file includes the prototypes to initialize and 
 * use UNO32 ports for LEDS
 * 
 * 
 * Created on January 21, 2019, 3:34 PM
 */

#ifndef LEDS_H
#define	LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "xc.h"


    //defines for UNO32 E port registers
#define LED1  PORTEbits.RE0
#define LED2  PORTEbits.RE1
#define LED3  PORTEbits.RE2
#define LED4  PORTEbits.RE3
#define LED5  PORTEbits.RE4
#define LED6  PORTEbits.RE5
#define LED7  PORTEbits.RE6
#define LED8  PORTEbits.RE7

    //define to set a port
#define SET(A) A = 1;

    //define to clear a port
#define CLEAR(A) A = 0;

    //define to token-paste strings --> used to activate ports
#define SPECIFICPIN(X) LED##X

    
//LEDS prototypes
    void LEDS_Init(void); //set UNO32 E port registers as digital outputs
    void LEDS_Set(void); //all E port registers are on
    void LEDS_Clear(void); //all E port registers are off
    void LEDS_Port(int, int); //choose a specific E port register and set or clear them
                                    //args: LEDS_Port(int port, int val)
                                            //first arg (port) = LED port number
                                            //second arg (val) = set (1) or clear (0) port


#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

