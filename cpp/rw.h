#ifndef _RW_H_
#define _RW_H_

#include "board.h"

void rw(Board &board, int sbTop, int sbLeft, int sbWidth, int sbHeight, unsigned int a, unsigned int b, int iterations = 1, int steps = 50, bool save_steps = false);


#endif
