#ifndef _BFS_H_
#define _BFS_H_

#include "board.h"

void bfs(Board &, unsigned int startRow, unsigned int startCol, unsigned int knightA, unsigned int knightB, bool save_steps = false);

#endif
