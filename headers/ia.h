#pragma once

#include "GameSystem.h"

int min_max_0(GameSystem gameSystem);
int min_max_1(GameSystem gameSystem);
int min_max_2(GameSystem gameSystem);
std::pair<int,int> min_max(GameSystem gameSystem, int position_played, int deepness_max);