#pragma once

#include "GameSystem.h"

//AI algorithm 0. Plays at the first eligible position found.
int min_max_0(GameSystem gameSystem, int player);
//AI algorithm 1. Returns the best position to play without anticipating opponent next plays.
int min_max_1(GameSystem gameSystem, int player);
//AI algorithm 2. Returns the best position to play anticipating opponent next plays thanks to a min-max algorithm
//non optimized with alpha-beta pruning.
int min_max_2(GameSystem gameSystem, int player);
//AI algorithm 3. Returns the best position to play anticipating opponent next plays thanks to a alpha-beta pruning
int min_max_3(GameSystem gameSystem, int player);
//Min-max recursive algorithm. Return a pair (position, value of the position).
//depth_max doit être impair
std::pair<int,int> min_max_recursion(GameSystem gameSystem, int position_played, int depth_max);
//Alpha beta pruning recursive algorithm. Return a pair (position, value of the position).
//depth_max doit être impair
std::pair<int,int> alphaBeta(GameSystem gameSystem, int position_played, int depth_max, int alpha, int beta);