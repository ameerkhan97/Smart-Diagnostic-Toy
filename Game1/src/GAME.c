/* 
 * File:   GAME.c
 * Author: Ameer Khan
 *
 */

#include "BOARD.h"
#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GAME.h"
#include "LEDS.h"


int GAME_Randomcolor(void){
    
    LEDS_Init();
    
    int rand1 = rand() % 2;
    int rand2 = rand() % 2;
    
    LED6 = rand1;
    LED8 = rand2;

    if (LED8 == 1 && LED6 == 1){ //RRYY
        LED7 = 0;
        LED4 = 0;
        LED3 = 1;
        LED5 = 0;
        LED2 = 0;
        LED1 = 1;
        color_state = 1;
    } else if (LED8 == 1 && LED6 == 0){ //RYYR
        LED7 = 0;
        LED4 = 0;
        LED3 = 1;
        LED5 = 1;
        LED2 = 1;
        LED1 = 0;
        color_state = 2;
    } else if (LED8 == 0 && LED6 == 1){ //YRRY
        LED7 = 1;
        LED4 = 1;
        LED3 = 0;
        LED5 = 0;
        LED2 = 0;
        LED1 = 1;
        color_state = 3;
    } else if (LED8 == 0 && LED6 == 0){ //YYRR
        LED7 = 1;
        LED4 = 1;
        LED3 = 0;
        LED4 = 1;
        LED2 = 1;
        LED1 = 0;
        color_state = 4;
    }  
    return color_state;
}

int GAME_NewTarget(void){
    
    int randtarget = rand() % 4;
    
    if (color_state == 1){ //RRYY
         if (randtarget == 0){
           OledInit();
           OledDrawString("RT2, RC2, YT1, YC1\n Press:RT2,BTN4\n");
           OledUpdate(); 
        } else if (randtarget == 1){
           OledInit();
           OledDrawString("RT2, RC2, YT1, YC1\n Press:RC2,BTN3\n");
           OledUpdate(); 
        } else if (randtarget == 2){
           OledInit();
           OledDrawString("RT2, RC2, YT1, YC1\n Press:YT1,BTN2\n");
           OledUpdate(); 
        } else if (randtarget == 3){
           OledInit();
           OledDrawString("RT2, RC2, YT1, YC1\n Press:YC1,BTN1\n");
           OledUpdate(); 
        }
    } else if (color_state == 2){ //RYYR
         if (randtarget == 0){
           OledInit();
           OledDrawString("RT2, YC2, YT1, RC1\n Press:RT2,BTN4\n");
           OledUpdate(); 
        } else if (randtarget == 1){
           OledInit();
           OledDrawString("RT2, YC2, YT1, RC1\n Press:YC2,BTN3\n");
           OledUpdate(); 
        } else if (randtarget == 2){
           OledInit();
           OledDrawString("RT2, YC2, YT1, RC1\n Press:YT1,BTN2\n");
           OledUpdate(); 
        } else if (randtarget == 3){
           OledInit();
           OledDrawString("RT2, YC2, YT1, RC1\n Press:RC1,BTN1\n");
           OledUpdate(); 
        }
    } else if (color_state == 3){ //YRRY
         if (randtarget == 0){
           OledInit();
           OledDrawString("YT2, RC2, RT1, YC1\n Press:YT2,BTN4\n");
           OledUpdate(); 
        } else if (randtarget == 1){
           OledInit();
           OledDrawString("YT2, RC2, RT1, YC1\n Press:RC2,BTN3\n");
           OledUpdate(); 
        } else if (randtarget == 2){
           OledInit();
           OledDrawString("YT2, RC2, RT1, YC1\n Press:RT1,BTN2\n");
           OledUpdate(); 
        } else if (randtarget == 3){
           OledInit();
           OledDrawString("YT2, RC2, RT1, YC1\n Press:YC1,BTN1\n");
           OledUpdate(); 
        }
    } else if (color_state == 4){ //YYRR
         if (randtarget == 0){
           OledInit();
           OledDrawString("YT2, YC2, RT1, RC1\n Press:YT2,BTN4\n");
           OledUpdate(); 
        } else if (randtarget == 1){
           OledInit();
           OledDrawString("YT2, YC2, RT1, RC1\n Press:YC2,BTN3\n");
           OledUpdate(); 
        } else if (randtarget == 2){
           OledInit();
           OledDrawString("YT2, YC2, RT1, RC1\n Press:RT1,BTN2\n");
           OledUpdate(); 
        } else if (randtarget == 3){
           OledInit();
           OledDrawString("YT2, YC2, RT1, RC1\n Press:RC1,BTN1\n");
           OledUpdate(); 
        }
    }
    return randtarget;
}