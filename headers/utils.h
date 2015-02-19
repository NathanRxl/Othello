#pragma once

#include <utility>
#include <vector>

//Tests whether [position] is on the board
bool is_onboard(int position, int direction);

std::pair<int,int> max(int* position_value, std::vector<int> eligiblePosition);
std::pair<int,int> min(int* position_value, std::vector<int> eligiblePosition);