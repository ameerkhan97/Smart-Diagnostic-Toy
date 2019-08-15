#include "BOARD.h"
#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <peripheral/spi.h>
#include "timers.h"
#include "SPI_LEDS.h"

#define HOLD 8

/*
 * For each GRB write, 8 bits are sent total in two writes with a hold 
 * in between each write.
 * 
 * C0 represents a 0 bit when calling the function WriteSPI2.
 * 
 * F0 represents a 1 bit when calling the function WriteSPI2.
 * 
 *  Example
 *  WriteSPI2(0xF0C0C0C0); //highest four bits
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0); //lowest four bits
    int i = 0;
    while(i < HOLD){
        i++;
    }

 *  Example
 * 
 * This example above is written three times in each color function to represent 
 * green, red and blue scale in order.
 * 
 */

//initializes the SPI channel using channel 2
void Leds_Init(void){
    SpiChnOpen(SPI_CHANNEL2, SPI_OPEN_MSTEN | SPI_OPEN_SMP_END | SPI_OPEN_MODE32, 8);
    SpiChnEnable(SPI_CHANNEL2, 1);
}

//turns off all LEDS
void Off(void){
    //Green
    WriteSPI2(0xC0C0C0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}

//turns LED green
void Green(void){
    //Green
    WriteSPI2(0xC0C0F0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}

//turns LED Red;
void Red(void ){
    //Green
    WriteSPI2(0xC0C0C0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0F0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}

//turns LED blue
void Blue(void){
    //Green
    WriteSPI2(0xC0C0C0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xF00C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0F0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}

//turns LED orange
void Orange(void){
    //Green
    WriteSPI2(0xC0C0C0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xF0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0F0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}

//turns LED purple
void Purple(void){
    //Green
    WriteSPI2(0xC0C0C0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xF0F0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0C0F0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}

//turns LED pink
void Pink(void){
    //Green
    WriteSPI2(0xC0C0C0C0);
    int i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Red
    WriteSPI2(0xC0C0F0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    //Blue
    WriteSPI2(0xC0C0F0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }

    WriteSPI2(0xC0C0C0C0);
    i = 0;
    while(i < HOLD){
        i++;
    }
}