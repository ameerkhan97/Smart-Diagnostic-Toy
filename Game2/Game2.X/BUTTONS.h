/**
 * @file    BUTTONS.h
 
 *          
 */

#ifndef BUTTONS_H
#define BUTTONS_H

/*******************************************************************************
 * INCLUDES                                                                    *
 ******************************************************************************/
#include "BOARD.h"
#include <xc.h>
#include <plib.h>

#define TRNGL2_PRESSED 0
#define CIRCL2_PRESSED 1
#define TRNGL1_PRESSED 2
#define CIRCL1_PRESSED 3
#define SQUARE1_PRESSED 4
#define SQUARE2_PRESSED 5
#define BUTTONS_RELEASED 6


/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @function    BUTTONS_Init(void)
 * @brief       
 * 
 * @return      SUCCESS or ERROR (as defined in BOARD.h)
 */
char BUTTONS_Init(void);
int BUTTONS_Event(void);

/**
 * @function    
 * @brief       
 * 
 * @return      
 */


#endif