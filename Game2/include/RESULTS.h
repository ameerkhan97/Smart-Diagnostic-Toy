/* 
 * File:   RESULTS.h
 * Author: Jacques 
 *
 * BRIEF:
 *      Header file that contains a struct of time and score array.
 *      Includes prototypes to access the struct
 * Created on January 28, 2019, 2:37 PM
 */

#ifndef RESULTS_H
#define	RESULTS_H

#ifdef	__cplusplus
extern "C" {
#endif


    //array size
#define SIZE 10

#define STRINGS 10
#define STRING_SIZE 10

    //struct to store time and score arrays
    typedef struct StoreResults {
        unsigned int time[SIZE];
        unsigned int score[SIZE];
        char prompt[STRINGS][STRING_SIZE];
        char response[STRINGS][STRING_SIZE];
        char combo[STRINGS][STRING_SIZE];
    } StoreResults;


    //PROTOTYPES
    //initialize the structure elements to 0 and return it
    StoreResults RESULTS_Init(void);

    //find array element whose value == 0, and store new time to time array in struct
    //ex: StoreResults s = RESULTS_Init();
    //      RESULTS_NewTime(&s, 7);
    //
    //result: time[SIZE] = {7, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    void RESULTS_NewTime(StoreResults*, unsigned int);

    //find array element whose value == 0, and store new score to time array in struct
    //ex: Store results s = RESULTS_Init();
    //      RESULTS_NewScore(&s, 7);
    //
    //result: score[SIZE] = {7, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    void RESULTS_NewScore(StoreResults*, unsigned int);
    
    //store the prompt in an array as a string
    void RESULTS_Prompt(StoreResults*, unsigned int);
    
    //store the response in an array as a string
    void RESULTS_Response(StoreResults*, unsigned int, unsigned int, unsigned int);

    //returns an array of unsigned int time from struct
    unsigned int *RESULTS_GetTimes(StoreResults*);

    //returns an array of unsigned int score from struct
    unsigned int *RESULTS_GetScores(StoreResults*);

    //prints the number of correct answers and the number of incorrect answers (Author: Naina))
    void RESULTS_PrintScore(StoreResults *s);

    //prints the total time taken to play a full game (10 rounds) (Author: Naina))
    void RESULTS_PrintTotalTime(StoreResults *s);

    //prints the contents of the time array
    void RESULTS_PrintTimeArray(StoreResults *s);

    //prints the contents of the score array
    void RESULTS_PrintScoreArray(StoreResults *s);
    
        //prints the contents of the prompt array
    void RESULTS_PrintPromptArray(StoreResults *s);
    
         //prints the contents of the response array
    void RESULTS_PrintResponseArray(StoreResults *s);

#endif	/* RESULTS_H */

