#pragma once

#include <utility>
#include <vector>

//Tests whether [position] is on the board
bool is_onboard(int position, int direction);

//Returns the index of the max in the table. Returns -1 if table is empty.
int max(int* position_value, int size);
int min(int* position_value, int size);