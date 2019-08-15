/*RESULTS.c
 *         **USES RESULTS.h
 * 
 * BRIEF:
 *      Source file for initializing and accessing
 *      a structure --- USED TO STORE TIME AND SCORE 
 */

#include <stdio.h>
#include <stdlib.h>
#include "RESULTS.h"



//initializes time and score array elements to 0 and returns the structure
//ex: StoreResults s = RESULTS_Init();
//result:  s->time == {0 0 0 0 0 0 0 0 0 0}
//         s->score == {0 0 0 0 0 0 0 0 0 0}

StoreResults RESULTS_Init()
{
    int i = 0;
    StoreResults s;
    for (i = 0; i < SIZE; i++) {
        s.time[i] = 2;
        s.score[i] = 2;
    }

    return s;
}

//adds a time value to an open (0) element in the array
//args: RESULTS_NewTime(StoreResults* s, unsigned int NewTime)
//StoreResults *s = pointer to a struct
//unsigned int NewTime = time value
//ex: StoreResults s = RESULTS_Init();
//    RESULTS_NewTime(&s, 8);
//result: s->time = {8 0 0 0 0 0 0 0 0 0}

void RESULTS_NewTime(StoreResults* s, unsigned int NewTime)
{
    int i = 0;
    for (i = 0; i < SIZE; i++) {
        if ((i == (SIZE)) && ((*s).time[SIZE] != 0)) {
            printf("ARRAY FULL!\r\n");
            break;
        }

        if ((*s).time[i] == 2) {

            (*s).time[i] = NewTime;
            break;
        }
    }
}

//adds a score value to an open (0) element in the array
//args: RESULTS_NewScore(StoreResults* s, unsigned int NewScore)
//StoreResults *s = pointer to a struct
//unsigned int NewScore = score value
//ex: StoreResults s = RESULTS_Init();
//    RESULTS_NewScore(&s, 8);
//result: s->score = {8 0 0 0 0 0 0 0 0 0}

void RESULTS_NewScore(StoreResults *s, unsigned int NewScore)
{
    int i = 0;
    for (i = 0; i < SIZE; i++) {
        if ((i == (SIZE)) && ((*s).score[SIZE] != 0)) {
            printf("ARRAY FULL!\r\n");
            break;
        }

        if ((*s).score[i] == 2) {
            (*s).score[i] = NewScore;
            break;
        }
    }
}


//returns time array from struct

unsigned int *RESULTS_GetTimes(StoreResults *s)
{
    return (*s).time;
}
//returns score array from struct

unsigned int *RESULTS_GetScores(StoreResults *s)
{
    return (*s).score;
}

void RESULTS_PrintScore(StoreResults *s)
{
    int right = 0;
    int wrong = 0;
    int i;
    for (i = 0; i < SIZE; i++) {

        if ((*s).score[i] == 1) {
            right++;
        } else /*if ((*s).score[i] == 0)*/ {
            wrong++;
        }
    }
    printf("Correct: %i\n", right);
    printf("Incorrect: %i\n", wrong);
}

void RESULTS_PrintTimeArray(StoreResults *s)
{
    int i;
    printf("Time (ms): ");
    for (i = 0; i < SIZE; i++) {
        printf("%i", (*s).time[i]);
        if (i != SIZE - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void RESULTS_PrintScoreArray(StoreResults *s)
{
    int i;
    printf("Score: ");
    for (i = 0; i < SIZE; i++) {
        printf("%i", (*s).score[i]);
        if (i != SIZE - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void RESULTS_PrintTotalTime(StoreResults *s)
{
    int i;
    int total;
    for (i = 0; i < SIZE; i++) {
        total += (*s).time[i];
    }
    printf("Total Time (ms): %i\n", total);
}