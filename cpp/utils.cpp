#include "utils.h"
#include <cmath>

bool is_onboard(int position, int direction)
{
	//Tests whether [position] is on the board

	bool return_value=true;
	if (abs((position%8) - ((position+direction)%8)) > 1) //Exiting the frame through upper or lower edge.
		return_value=false;
	if (abs((position/8) - ((position+direction)/8)) > 1)//Exiting the frame through right or left edge.
		return_value=false;
	return return_value;
}

int max(int* position_value, int size)
{
	int value;
	int index;
	value = -1000;
	index = -1;
	if (size == 0)
		return -1;
	else
	{
		for(int i=0; i<size; ++i)
		{
			if(position_value[i] > value)
			{
				value = position_value[i];
				index = i;
			}
		}
	}
	return index;
}

int min(int* position_value, int size)
{
	int value;
	int index;
	value = 1000;
	index = -1;
	if (size == 0)
		return -1;
	else
	{
		for(int i=0; i<size; ++i)
		{
			if(position_value[i] < value)
			{
				value = position_value[i];
				index = i;
			}
		}
	}
	return index;
}