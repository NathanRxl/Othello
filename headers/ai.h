#pragma once

#include "GameSystem.h"

int min_max_0(GameSystem gameSystem, int player);
int min_max_1(GameSystem gameSystem, int player);
int min_max_2(GameSystem gameSystem, int player);
std::pair<int,int> min_max_recursion(GameSystem gameSystem, int position_played, int depth_max);
std::pair<int,int> alphaBeta(GameSystem gameSystem, int position_played, int depth_max, int& alpha, int& beta);