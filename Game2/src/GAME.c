#include "BOARD.h"
#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <peripheral/spi.h>
#include "timers.h"
#include "SPI_LEDS.h"
#include "GAME.h"
#include <bluetooth_uart.h>

/*        // !!! these have changed with the cube implimentation, see update below
 * LEDs: 1 2 3 4 5 6
 * Shape Corresponding to LED: Triangle1 Square1 Circle1 Triangle2 Square2 Circle2
 * RandTarget Value Corresponding to LED/Shape: 0 1 2 3 4 5 
 * 
 * 12 color combinations
 * 1. GRBRBG
 * 2. GRBBGR
 * 3. GBRRGB
 * 4. GBRBRG
 * 5. RGBGBR
 * 6. RGBBRG
 * 7. RBGGRB
 * 8. RBGBGR
 * 9. BGRGRB
 * 10. BGRRBG
 * 11. BRGGBR
 * 12. BRGRGB
 */

/*     !!!   Triangle 2 has changed position in the LED chain
 * LEDs:                                        1               2           3           4           5           6
 * Shape Corresponding to LED:                  Triangle1       Square1     Circle1     Square2     Circle2     Triangle2
 * RandTarget Value Corresponding to LED/Shape: 0               1           2           4           5           3
 * 
 *
 * 12 color combinations
 * 1. GRBRBG
 * 2. GRBBGR
 * 3. GBRRGB
 * 4. GBRBRG
 * 5. RGBGBR
 * 6. RGBBRG
 * 7. RBGGRB
 * 8. RBGBGR
 * 9. BGRGRB
 * 10. BGRRBG
 * 11. BRGGBR
 * 12. BRGRGB
 */

void GAME_Init(void) {

    Leds_Init();
    Green();
    Red();
    Blue();
    Orange();
    Purple();
    Pink();
    Off();
}

int GAME_Randomcolor(void) {        // triangle 2's position on the LED chain has changed, this has been accounted
                                    // for in this function and shouldn't change anything elsewhere

    int rand1 = rand() % 6;
    int rand2 = rand() % 2;

    INTDisableInterrupts();
    if (rand1 == 0) {
        Green();        //triangle 1
        Red();          //square 1
        Blue();         //circle 1
        if (rand2 == 0) {
            Blue();         //square 2
            Green();        //circle 2
            Red();          //triangle 2
            color_state = 1;
        } else if (rand2 == 1) {
            Green();        //square 2
            Red();          //circle 2
            Blue();         //triangle 2
            color_state = 2;
        }
    } else if (rand1 == 1) {
        Green();        //triangle 1
        Blue();         //square 1
        Red();          //circle 1
        if (rand2 == 0) {
            Green();        //square 2
            Blue();         //circle 2
            Red();          //triangle 2
            color_state = 3;
        } else if (rand2 == 1) {
            Red();          //square 2
            Green();        //circle 2
            Blue();         //triangle 2
            color_state = 4;
        }
    } else if (rand1 == 2) {
        Red();          //triangle 1
        Green();        //square 1
        Blue();         //circle 1
        if (rand2 == 0) {
            Blue();         //square 2
            Red();          //circle 2
            Green();        //triangle 2
            color_state = 5;
        } else if (rand2 == 1) {
            Red();          //square 2
            Green();        //circle 2
            Blue();         //triangle 2
            color_state = 6;
        }
    } else if (rand1 == 3) {
        Red();          //triangle 1
        Blue();         //square 1
        Green();        //circle 1
        if (rand2 == 0) {
            Red();          //square 2
            Blue();         //circle 2
            Green();        //triangle 2
            color_state = 7;
        } else if (rand2 == 1) {
            Green();        //square 2
            Red();          //circle 2
            Blue();         //triangle 2
            color_state = 8;
        }
    } else if (rand1 == 4) {
        Blue();         //triangle 1
        Green();        //square 1
        Red();          //circle 1
        if (rand2 == 0) {
            Red();          //square 2
            Blue();         //circle 2
            Green();        //triangle 2
            color_state = 9;
        } else if (rand2 == 1) {
            Blue();         //square 2
            Green();        //circle 2
            Red();          //triangle 2
            color_state = 10;
        }
    } else if (rand1 == 5) {
        Blue();         //triangle 1
        Red();          //square 1
        Green();        //circle 1
        if (rand2 == 0) {
            Blue();         //square 2
            Red();          //circle 2
            Green();        //triangle 2
            color_state = 11;
        } else if (rand2 == 1) {
            Green();        //square 2
            Blue();         //circle 2
            Red();          //triangle 2
            color_state = 12;
        }
    }
    Off();
    INTEnableInterrupts();
    return color_state;
}

int GAME_NewTarget(StoreResults *s) {   //no changes needed here with cube implimentation  

    int randtarget = rand() % 6;

    if (color_state == 1) { //GRBRBG
        if (randtarget == 0) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "BC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "GC");
        }
    } else if (color_state == 2) { //GRBBGR
        if (randtarget == 0) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "BC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "RC");
        }
    } else if (color_state == 3) { //GBRRGB
        if (randtarget == 0) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "RC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "BC");
        }
    } else if (color_state == 4) { //GBRBRG
        if (randtarget == 0) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "RC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "GC");
        }
    } else if (color_state == 5) { //RGBGBR
        if (randtarget == 0) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "BC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "RC");
        }
    } else if (color_state == 6) { //RGBBRG
        if (randtarget == 0) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "BC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "GC");
        }
    } else if (color_state == 7) { //RBGGRB
        if (randtarget == 0) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "GC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "BC");
        }
    } else if (color_state == 8) { //RBGBGR
        if (randtarget == 0) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "GC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "RC");
        }
    } else if (color_state == 9) { //BGRGRB
        if (randtarget == 0) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "RC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "BC");
        }
    } else if (color_state == 10) { //BGRRBG
        if (randtarget == 0) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "RC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "GC");
        }
    } else if (color_state == 11) { //BRGGBR
        if (randtarget == 0) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "GC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "GT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "BS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "RC");
        }
    } else if (color_state == 12) { //BRGRGB
        if (randtarget == 0) {
            strcpy((*s).combo[0], "BT");
        } else if (randtarget == 1) {
            strcpy((*s).combo[0], "RS");
        } else if (randtarget == 2) {
            strcpy((*s).combo[0], "GC");
        } else if (randtarget == 3) {
            strcpy((*s).combo[0], "RT");
        } else if (randtarget == 4) {
            strcpy((*s).combo[0], "GS");
        } else if (randtarget == 5) {
            strcpy((*s).combo[0], "BC");
        }
    }

    return randtarget;
}