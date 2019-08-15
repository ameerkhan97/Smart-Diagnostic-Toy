/* 
 * File:   SPI_LEDS.h
 * Author: Ameer Khan
 *
 * Created on February 13, 2019, 11:32 AM
 */

#ifndef SPI_LEDS_H
#define	SPI_LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "BOARD.h"
#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <peripheral/spi.h>
#include "timers.h"
    
    void Leds_Init(void); //initializes the Leds
    void Off(void); //turns Leds off
    void Green(void); //turns Leds green
    void Red(void); //turns Leds red
    void Blue(void); //turns Leds blue
    void Orange(void); //turns Leds orange
    void Purple(void); //turns Leds purple
    void Pink(void); //turns Leds pink
    
#ifdef	__cplusplus
}
#endif

#endif	/* SPI_LEDS_H */

