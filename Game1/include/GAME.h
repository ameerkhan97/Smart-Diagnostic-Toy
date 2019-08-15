/* 
 * File:   GAME.h
 * Author: Ameer Khan
 *
 * Created on January 23, 2019, 2:24 PM
 */

#ifndef GAME_H
#define	GAME_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "BOARD.h"
#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    int color_state;
    int GAME_Randomcolor(void); //returns value of color_state which represents the color/shape combination of the LEDS
    int GAME_NewTarget(void); //returns value of randtarget which represents the button the user needs to press


#ifdef	__cplusplus
}
#endif

#endif	/* GAME_H */

