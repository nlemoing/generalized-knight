#ifndef _RW_H_
#define _RW_H_

#include "board.h"
#include "startbox.h"
#include "knight.h"

void rw(Board &board, StartBox &sb, Knight &k, int iterations, int steps, bool save_steps, bool trace_paths);

#endif
