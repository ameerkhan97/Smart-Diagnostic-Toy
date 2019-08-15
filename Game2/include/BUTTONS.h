#ifndef BUTTONS_H
#define BUTTONS_H

#include "BOARD.h"
#include <xc.h>
#include <plib.h>

#define TRNGL1_PRESSED 0
#define SQUARE1_PRESSED 1
#define CIRCL1_PRESSED 2
#define TRNGL2_PRESSED 3
#define SQUARE2_PRESSED 4
#define CIRCL2_PRESSED 5
#define BUTTONS_RELEASED 6



char BUTTONS_Init(void);
int BUTTONS_Event(void);

#endif