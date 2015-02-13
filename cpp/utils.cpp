#include "utils.h"
#include <cmath>

bool possible_position(int position, int direction) //Tests whether [position] is in the board
{
	bool b=true;
	if (abs((position%8) - ((position+direction)%8)) > 1) //Exiting the frame through upper or lower edge.
		b=false;
	if (abs((position/8) - ((position+direction)/8)) > 1)//Exiting the frame through right or left edge.
		b=false;
	return b;
}