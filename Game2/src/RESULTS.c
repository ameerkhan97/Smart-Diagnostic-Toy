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
#include "string.h"


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

    strcpy(s.prompt[0], "null");
    strcpy(s.prompt[1], "null");
    strcpy(s.prompt[2], "null");
    strcpy(s.prompt[3], "null");
    strcpy(s.prompt[4], "null");
    strcpy(s.prompt[5], "null");
    strcpy(s.prompt[6], "null");
    strcpy(s.prompt[7], "null");
    strcpy(s.prompt[8], "null");
    strcpy(s.prompt[9], "null");

    strcpy(s.response[0], "null");
    strcpy(s.response[1], "null");
    strcpy(s.response[2], "null");
    strcpy(s.response[3], "null");
    strcpy(s.response[4], "null");
    strcpy(s.response[5], "null");
    strcpy(s.response[6], "null");
    strcpy(s.response[7], "null");
    strcpy(s.response[8], "null");
    strcpy(s.response[9], "null");

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

void RESULTS_Prompt(StoreResults* s, unsigned int counter)
{
    strcpy((*s).prompt[counter], (*s).combo[0]);
    printf("Prompt: %s\n", (*s).prompt[counter]);

}

void RESULTS_Response(StoreResults* s, unsigned int counter, unsigned int color, unsigned int response)
{
    if (color == 1) {
        if (response == 0) {//GRBRBG
            strcpy((*s).response[counter], "GT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "BC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "RT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "GC");
        }
    } else if (color == 2) {
        if (response == 0) {//GRBBGR
            strcpy((*s).response[counter], "GT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "BC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "BT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "RC");
        }
    } else if (color == 3) {
        if (response == 0) {//GBRRGB
            strcpy((*s).response[counter], "GT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "RC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "RT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "BC");
        }
    } else if (color == 4) {
        if (response == 0) {//GBRBRG
            strcpy((*s).response[counter], "GT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "RC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "BT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "GC");
        }
    } else if (color == 5) {//RGBGBR
        if (response == 0) {
            strcpy((*s).response[counter], "RT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "BC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "GT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "RC");
        }
    } else if (color == 6) {
        if (response == 0) {//RGBBRG
            strcpy((*s).response[counter], "RT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "BC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "BT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "GC");
        }
    } else if (color == 7) {
        if (response == 0) {//RBGGRB
            strcpy((*s).response[counter], "RT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "GC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "GT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "BC");
        }
    } else if (color == 8) {
        if (response == 0) {//RBGBGR
            strcpy((*s).response[counter], "RT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "GC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "BT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "RC");
        }
    } else if (color == 9) {
        if (response == 0) {//BGRGRB
            strcpy((*s).response[counter], "BT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "RC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "GT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "BC");
        }
    } else if (color == 10) {
        if (response == 0) {//BGRRBG
            strcpy((*s).response[counter], "BT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "RC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "RT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "GC");
        }
    } else if (color == 11) {
        if (response == 0) {//BRGGBR
            strcpy((*s).response[counter], "BT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "GC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "GT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "BS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "RC");
        }
    } else if (color == 12) {
        if (response == 0) {//BRGRGB
            strcpy((*s).response[counter], "BT");
        } else if (response == 1) {
            strcpy((*s).response[counter], "RS");
        } else if (response == 2) {
            strcpy((*s).response[counter], "GC");
        } else if (response == 3) {
            strcpy((*s).response[counter], "RT");
        } else if (response == 4) {
            strcpy((*s).response[counter], "GS");
        } else if (response == 5) {
            strcpy((*s).response[counter], "BC");
        }
    }
    printf("Response: %s\n", (*s).response[counter]);

}



unsigned int *RESULTS_GetTimes(StoreResults *s)//returns time array from struct
{
    return (*s).time;
}


unsigned int *RESULTS_GetScores(StoreResults *s)//returns score array from struct
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

void RESULTS_PrintPromptArray(StoreResults *s)
{
    int i;
    printf("Prompt: ");
    for (i = 0; i < SIZE; i++) {
        printf("%s", (*s).prompt[i]);
        if (i != SIZE - 1) {
            printf(", ");
        }
    }
    printf("\n");

}

void RESULTS_PrintResponseArray(StoreResults *s)
{
    int i;
    printf("Response: ");
    for (i = 0; i < SIZE; i++) {
        printf("%s", (*s).response[i]);
        if (i != SIZE - 1) {
            printf(", ");
        }
    }
    printf("\n");

}


