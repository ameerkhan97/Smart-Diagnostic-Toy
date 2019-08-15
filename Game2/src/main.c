/*
 * File:   main.c
 * Author: Naina Sharma
 * Description: Implementing Software Portion of Smart Toy Game, UNO32 being used
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

#define CORRECT 1
#define WRONG 0

int event = 0;
int pre_event = 7;

char buff[100];
int gyroX, gyroY, gyroZ, accelX, accelY, accelZ;
double euler_read[3][1] = {0};

enum {//enum for holding all the states the game could be in, starting state is idle
    IDLE, START_GAME, GAME_OVER
} state = IDLE; //the program starts in the IDLE state

int counter = 0; //counter to keep track of the amount of times the game is played
int correctness = 0; //int to keep track of right or wrong answer
int color; //holds value of color_state which represents the color combination of the LEDS

struct TIME {//struct that holds all of the time data
    int save_time; //variable to save the time in
    int delta_time; //variable to hold the difference of time in
    int temp_time; //variable to hold temporary time in
} TIME_DATA;

int main(void)
{
    BOARD_Init();
    BUTTONS_Init();
    TIMERS_Init();
    SERIAL2_Init();
    IMU_Init();
    GAME_Init();

    StoreResults s = RESULTS_Init();

    while (1) {
        event = BUTTONS_Event();
        if ((pre_event != event)&&(event != 6)) {
            switch (state) {
            case IDLE:
                printf("state = IDLE\n");
                if (event == TRNGL2_PRESSED) {//upon pressing TRNGL2 button enter the START_GAME state
                    BluetoothWriteString("rawGx,rawGy,rawGz,rawAx,rawAy,rawAz,procGx,procGy,procGz,procAx,procAy,procAz,time,score,prompt,response\r\n");
                    TIME_DATA.save_time = TIMERS_GetMilliSeconds(); //save the time into variable save_time
                    srand(TIME_DATA.save_time); //seed rand function with that time                   
                    color = GAME_Randomcolor(); //have the LEDs display new configuration randomly
                    correctness = GAME_NewTarget(&s); //generate random target 
                    sprintf(buff, "X%s\n", s.combo[0]);
                    BluetoothWriteString(buff);
                    state = START_GAME;
                }
                break;
            case START_GAME:
                printf("state = START GAME\n");
                RESULTS_Prompt(&s, counter);
                RESULTS_Response(&s, counter, color, event);
                counter++; //increment counter to indicate new round

                TIME_DATA.temp_time = TIMERS_GetMilliSeconds(); //record current timer time in temp_time
                TIME_DATA.delta_time = TIME_DATA.temp_time - TIME_DATA.save_time; //subtract current time from saved time
                RESULTS_NewTime(&s, TIME_DATA.delta_time); //store difference in delta_time
                TIME_DATA.save_time = TIME_DATA.temp_time; //new save time is the current time
                if (correctness == event) {//record whether answer was correct or incorrect
                    RESULTS_NewScore(&s, CORRECT);
                } else {
                    RESULTS_NewScore(&s, WRONG);
                }
                color = GAME_Randomcolor();
                correctness = GAME_NewTarget(&s);
                sprintf(buff, "X%s\n", s.combo[0]);
                BluetoothWriteString(buff);
                if (counter < 10) {//if 10 rounds haven't been completed keep playing
                    state = START_GAME;
                } else {//if 10 rounds have been completed the game is over                            
                    RESULTS_GetTimes(&s); //return the time array                           
                    RESULTS_GetScores(&s); //return the score array                           
                    RESULTS_PrintScore(&s); //print the score (number right and number wrong)                           
                    RESULTS_PrintTotalTime(&s); //print the total time                            
                    RESULTS_PrintScoreArray(&s); //print score array                           
                    RESULTS_PrintTimeArray(&s); //print time array                          
                    RESULTS_PrintPromptArray(&s); //print prompt array                          
                    RESULTS_PrintResponseArray(&s); //print response array

                    int x = 0;
                    for (x = 0; x < 10; x++) {
                        sprintf(buff, ",,,,,,,,,,,,%d,%d,%s,%s\r\n", s.time[x], s.score[x], s.prompt[x], s.response[x]);
                        BluetoothWriteString(buff);
                    }
                    state = GAME_OVER;
                }
                break;
            case GAME_OVER:
                printf("state = GAME OVER\n");
                if (event == TRNGL2_PRESSED) {
                    counter = 0;
                    s = RESULTS_Init();
                    TIME_DATA.save_time = TIMERS_GetMilliSeconds();
                    srand(TIME_DATA.save_time);
                    color = GAME_Randomcolor();
                    correctness = GAME_NewTarget(&s);
                    sprintf(buff, "X%s\n", s.combo[0]);
                    BluetoothWriteString(buff);
                    state = START_GAME;
                }
                break;
            }
        }
        pre_event = event;

        if (((TIMERS_GetMilliSeconds() % 50) == 0) && (state == START_GAME)) {//stream IMU data here (non-blocking)
            accelX = IMU_ReadAccelX()/100;  // 'representation' scale factor from page 36 of BNO055 datasheet, data now in meters per second squared (m/s^2)
            accelY = IMU_ReadAccelY()/100;
            accelZ = IMU_ReadAccelZ()/100;
            
            gyroX = IMU_ReadGyroX()/16;  // 'representation' scale factor from page 33 of BNO055 datasheet, data now in degrees per second 
            gyroY = IMU_ReadGyroY()/16;
            gyroZ = IMU_ReadGyroZ()/16;

            euler_read[0][0] = IMU_ReadEulerR()/16;  // 'representation' scale factor from page 35 of BNO055 datasheet, data now in varient of Euler angles (positions) in degrees
            euler_read[1][0] = IMU_ReadEulerP()/16;
            euler_read[2][0] = IMU_ReadEulerH()/16;
            
            sprintf(buff, " %d, %d, %d, %d, %d, %d, %0.1f, %0.1f, %0.1f\r\n", gyroX, gyroY, gyroZ, accelX, accelY, accelZ, euler_read[0][0], euler_read[1][0], euler_read[2][0]);
            BluetoothWriteString(buff);
        }
    }
}