#ifndef _NEXT_H_
#define _NEXT_H_
#include "board.h"
#include <vector>
#include <utility>

std::vector<std::pair<unsigned int, unsigned int>> nextMoves(unsigned int r, unsigned int c, unsigned int a, unsigned int b);

std::pair<unsigned int, unsigned int> randomNextMove(Board &board, unsigned int r, unsigned int c, unsigned int a, unsigned int b);

#endif
