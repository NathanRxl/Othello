#pragma once

#include <vector>

//Tests whether [position] is on the board
bool stay_onboard(int position, int direction);

//Returns the pair (index of the max in the table, max in the table). Returns -1 if table is empty.
std::pair<int, int> max(int* table_value, int size);
std::pair<int, int> min(int* table_value, int size);