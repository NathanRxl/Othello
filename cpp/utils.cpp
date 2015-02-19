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

std::pair<int,int> max(int* position_value, std::vector<int> eligiblePosition)
{
	std::pair<int,int> values;
	values.first = -1;
	values.second = -1;
	if (eligiblePosition.size() == 0)
		return values;
	else
	{
		for(unsigned int i=0; i<eligiblePosition.size(); ++i)
		{
			if(position_value[i] > values.second)
			{
				values.second = position_value[i];
				values.first = eligiblePosition[i];
			}
		}
	}
	return values;
}

std::pair<int,int> min(int* position_value, std::vector<int> eligiblePosition)
{
	std::pair<int,int> values;
	values.first = -1;
	values.second = -1;
	if (eligiblePosition.size() == 0)
		return values;
	else
	{
		values.first = 0;
		values.second = position_value[0];
		for(unsigned int i=0; i<eligiblePosition.size(); i++)
		{
			if(position_value[i] > values.second)
			{
				values.second = position_value[i];
				values.first = eligiblePosition[i];
			}
		}
	}
	return values;
}