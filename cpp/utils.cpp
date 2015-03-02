#include "utils.h"
#include <cmath>

//Debug
#include <cassert>

bool stay_onboard(int position, int direction)
{
	//Tests whether [position+direction] stays on the board, that is to say if position and position+direction are adjacent
	bool return_value = true;
	if (abs((position%8)-((position+direction)%8)) > 1) //Exiting the frame through upper or lower edge.
		return_value=false;
	if (abs((position/8) - ((position+direction)/8)) > 1)//Exiting the frame through right or left edge.
		return_value=false;
	return return_value;
}

std::pair<int, int> max(int* table_value, int size)
{
	assert(size>0);
	int max_value = table_value[0];
	int max_index = 0;
	for(int i=1; i<size; ++i)
	{
		if(table_value[i] > max_value)
		{
			max_value = table_value[i];
			max_index = i;
		}
	}
	return std::pair<int, int> (max_index, max_value);
}

std::pair<int, int> min(int* table_value, int size)
{
	assert(size>0);
	int min_value = table_value[0];
	int min_index = 0;
	for(int i=1; i<size; ++i)
	{
		if(table_value[i] < min_value)
		{
			min_value = table_value[i];
			min_index = i;
		}
	}
	return std::pair<int, int> (min_index, min_value);
}