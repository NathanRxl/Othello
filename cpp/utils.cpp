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