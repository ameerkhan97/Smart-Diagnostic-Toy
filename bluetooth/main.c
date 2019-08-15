/*
 * File:   main.c
 * Author: Naina Sharma
 * Description: Implementing Version 2 of "Red Triangle Game", 2nd Prototype for
 * Software Portion of Smart Toy Game, Uno32 being used
 * Created on January 22, 2019, 1:15 PM
 */

//CMPE13 Support Library
#include "BOARD.h"

//CMPE167 Support Library
#include <timers.h>

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdint.h>
#include <stdio.h>
#include <serial.h>
#include <string.h>

//Support Libraries Created by TEAM
#include <SPI_LEDS.h>
#include <GAME.h>
#include <BUTTONS.h>
#include <RESULTS.h>
#include <bluetooth_uart.h>

#define RIGHT 1
#define WRONG 0

int event = 0;
int pre_event = 7;

//enum for holding all the states the game could be in, starting state is idle
enum {
    IDLE, START_GAME, GAME_OVER
} state = IDLE; //the program starts in the IDLE state

int counter = 0; //counter to keep track of the amount of times the game is played
int correctness = 0; //int to keep track of right or wrong answer
int color;
//struct that holds all of the time data

struct TIME {
    int save_time; //variable to save the time in
    int delta_time; //variable to hold the difference of time in
    int temp_time; //variable to hold temporary time in
} TIME_DATA;

int main(void)
{
    BOARD_Init();
    //printf("in main1\n");
    BUTTONS_Init();
    //printf("in main2\n");
    TIMERS_Init();
    //printf("in main3\n");
     SERIAL2_Init();
    GAME_Init();
    //    while(1){
    //        event = BUTTONS_Event();
    //        if (pre_event != event){
    //            GAME_Randomcolor();
    //        }
    //        pre_event = event;
    //    }
    //printf("in main3\n");
    StoreResults s = RESULTS_Init();

    int calc;
    while (1) {
        event = BUTTONS_Event();
        if ((pre_event != event)) {
            switch (state) {
            case IDLE:
                printf("state = IDLE\n"); //debugging tool to see current state
                //LEDS_Set();
                //timer should be going
                //in this state display default red triangle
                //this state will only be exited when the TRNGL2/RED button will be pressed
                //upon pressing that button enter the START_GAME state
                if (event == TRNGL2_PRESSED) {
                    BluetoothWriteString("rawGx, rawGy, rawGz, rawAx, rawAy, rawAz, procGx, procGy, procGz, procAx, procAy, procAz, time, score, prompt, response\r\n");
                    //save the time of the timer into a variable save_time
                    TIME_DATA.save_time = TIMERS_GetMilliSeconds();
                    //seed rand function with that time
                    srand(TIME_DATA.save_time);
                    //have the LEDs display new configuration randomly
                    color = GAME_Randomcolor();
                    //have random target print to the screen
                    correctness = GAME_NewTarget(&s);
                    state = START_GAME;
                }
                break;
            case START_GAME:
                printf("state = START GAME\n");
                //upon any button event or in other words upon any button pressed record whether the 
                //answer was right or wrong increment counter and move to RECORD_RANDOM state
                if (event != 6)/*((event == TRNGL2_PRESSED) || (event == TRNGL1_PRESSED) ||
                        (event == CIRCL1_PRESSED) || (event == CIRCL2_PRESSED) ||
                        (event == SQUARE1_PRESSED) || (event == SQUARE2_PRESSED))*/ {
                    RESULTS_Prompt(&s, counter);
                    RESULTS_Response(&s, counter, color, event);
                    counter++;
                    //once in this state compare record current timer time in temp_time
                    TIME_DATA.temp_time = TIMERS_GetMilliSeconds();
                    //compare with save_time value
                    //store difference in delta_time
                    TIME_DATA.delta_time = TIME_DATA.temp_time - TIME_DATA.save_time;
                    RESULTS_NewTime(&s, TIME_DATA.delta_time);
                    printf("%i\n", TIME_DATA.delta_time);
                    TIME_DATA.save_time = TIME_DATA.temp_time;
                    //record whether answer was correct or incorrect

                    printf("correctness: %d || event: %d\r\n", correctness, event);
                    if (correctness == event) {
                        printf("RIGHT\r\n");
                        RESULTS_NewScore(&s, RIGHT);
                    } else {
                        printf("WRONG\r\n");
                        RESULTS_NewScore(&s, WRONG);
                    }
                    //display new random setup of LEDs as well as print new target to the screen
                    color = GAME_Randomcolor();
                    correctness = GAME_NewTarget(&s);
                    if (counter < 10) {
                        state = START_GAME;
                    } else {
                        state = GAME_OVER;
                    }
                }
                break;
            case GAME_OVER:
                //                OledClear();
                //                OledDrawString("state = GAME OVER\n");
                //                OledUpdate();
                printf("state = GAME OVER\n"); //debugging tool to see current state
                //record delta time as before
                TIME_DATA.temp_time = TIMERS_GetMilliSeconds();
                TIME_DATA.delta_time = TIME_DATA.temp_time - TIME_DATA.save_time;
                RESULTS_NewTime(&s, TIME_DATA.delta_time);
                TIME_DATA.save_time = TIME_DATA.temp_time;
                //record accuracy as before
                if (correctness == event) {
                    RESULTS_NewScore(&s, RIGHT);
                } else {
                    RESULTS_NewScore(&s, WRONG);
                }

                //turn LEDs off maybe and then to default set up ("red triangle setup"))
                //LEDS_Clear();
                //return the time array
                RESULTS_GetTimes(&s);
                //return the score array
                RESULTS_GetScores(&s);
                //print the score (number right and number wrong)
                RESULTS_PrintScore(&s);
                //print the total time
                RESULTS_PrintTotalTime(&s);
                //print score array
                RESULTS_PrintScoreArray(&s);
                //print time array
                RESULTS_PrintTimeArray(&s);
                //print prompt array
                RESULTS_PrintPromptArray(&s);
                //print response array
                RESULTS_PrintResponseArray(&s);
                
                char buff[100];
                int x = 0;
                for(x = 0; x < 10; x++){
                    sprintf(buff, ",,,,,,,,,,,,%d,%d,%s,%s\r\n", s.time[x],s.score[x],s.prompt[x],s.response[x]);
                     BluetoothWriteString(buff);
                     
                }
                /* BluetoothWriteString(s.prompt[0]);
                 BluetoothWriteString(s.prompt[1]);
                 BluetoothWriteString(s.prompt[2]);
                 BluetoothWriteString(s.prompt[3]);
                 BluetoothWriteString(s.prompt[4]);
                 BluetoothWriteString(s.prompt[5]);
                 BluetoothWriteString(s.prompt[6]);
                 BluetoothWriteString(s.prompt[7]);
                 BluetoothWriteString(s.prompt[8]);
                 BluetoothWriteString(s.prompt[9]);*/
                //..............................................................................
                //print New Game Message??
                //if the TRNGL2/RED button is pressed move reset counter and move to RESTART_GAME state
                if (event == TRNGL2_PRESSED) {
                    counter = 0;
                    s = RESULTS_Init();
                    //save the time of the timer into a variable save_time
                    TIME_DATA.save_time = TIMERS_GetMilliSeconds();
                    //seed rand function with that time
                    srand(TIME_DATA.save_time);
                    //have the LEDs display new configuration randomly
                    color = GAME_Randomcolor();
                    //have random target print to the screen
                    correctness = GAME_NewTarget(&s);
                    state = START_GAME;
                }
                break;
            }
            pre_event = event;
        }
    }
}
