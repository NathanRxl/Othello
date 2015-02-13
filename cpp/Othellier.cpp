#include "Othellier.h"
#include "utils.h"
#include <iostream>

Othellier::Othellier() {

	othellier = new int[64];

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			othellier[8*i+j]=-1;

	othellier[8*3+3]=1;
	othellier[8*3+4]=0;
	othellier[8*4+3]=0;
	othellier[8*4+4]=1;
}

int& Othellier::operator[](int position){

	return othellier[position];
}

void Othellier::flip(int position, int player)
{
	//Tests whether [position] and [position+direction] are of different colours
	//and flips in that direction.
	//directions: up =         8*  0 +(-1) = -1
	//	          up_left =    8*(-1)+(-1) = -9
	//	          left =       8*(-1)+  0  = -8
	//	          down_left =  8*(-1)+  1  = -7
	//	          down =       8*  0 +  1  =  1
	//	          down_right = 8*  1 +  1  =  9
	//	          right =      8*  1 +  0  =  8
	//	          up_right =   8*  1 +(-1) =  7
	//This function returns true if [position] is eligible
	int direction[8];
	direction[0] = -1;
	direction[1] = -9;
	direction[2] = -8;
	direction[3] = -7;
	direction[4] = 1;
	direction[5] = 9;
	direction[6] = 8;
	direction[7] = 7;

	for(int i=0; i<8; i++) //loop over directions
	{
		int moving_position = position+direction[i];

		if (possible_position(position, direction[i]) == true && (othellier[moving_position] == 1-player))
		{
			while((othellier[moving_position+direction[i]] == 1-player) && possible_position(moving_position, direction[i]))
			{
				moving_position += direction[i];
			}
			if (possible_position(moving_position,direction[i]))
			{
				if (othellier[moving_position+direction[i]] == player)
				{
					while(othellier[moving_position] == 1-player)
					{
						othellier[moving_position] = player;
						moving_position -= direction[i];
					}
				}
			}
		}
	}
}

bool Othellier::exploration(int position, int player)
{
	//Tests whether [position] and [position+direction] are of different colours
	//and explore in that direction.
	//directions: up =         8*  0 +(-1) = -1
	//	          up_left =    8*(-1)+(-1) = -9
	//	          left =       8*(-1)+  0  = -8
	//	          down_left =  8*(-1)+  1  = -7
	//	          down =       8*  0 +  1  =  1
	//	          down_right = 8*  1 +  1  =  9
	//	          right =      8*  1 +  0  =  8
	//	          up_right =   8*  1 +(-1) =  7
	//This function returns true if [position] is eligible
	int direction[8];
	direction[0] = -1;
	direction[1] = -9;
	direction[2] = -8;
	direction[3] = -7;
	direction[4] = 1;
	direction[5] = 9;
	direction[6] = 8;
	direction[7] = 7;

	bool check_direction[8];

	for(int i=0; i<8; i++) //loop over directions
	{
		int moving_position = position+direction[i];

		if (possible_position(position, direction[i]) == false || (othellier[moving_position] != 1-player))
			check_direction[i] = false;
		else
		{
			while((othellier[moving_position+direction[i]] == 1-player) && possible_position(moving_position, direction[i]))
			{
				moving_position += direction[i];
			}
			if (possible_position(moving_position,direction[i]))
			{
				if (othellier[moving_position+direction[i]] == player)
				{
					check_direction[i] = true;
				}
				else
					check_direction[i] = false;
			}
			else
				check_direction[i] = false;
		}
	}

	bool return_value = false;
		for(int i=0; i<8; i++)
		{
			if(check_direction[i] == true)
				return_value = true;
		}
																		//if(with_flip == true){
																			if (return_value)
																				std::cout << " eligible? true" << std::endl;
																			else
																				std::cout << " eligible? false" << std::endl;//}
	return return_value;
}

bool Othellier::is_eligible(int position, int player)
{
																					//if(with_flip == true)
																						std::cout << "Position " << position;

	if(othellier[position] != -1)
	{
																					//if(with_flip == true)
																						std::cout << " occupied" << std::endl;
		return false;
	}
	else
	{
		return exploration(position, player);
	}
}

int Othellier::nb_eligible(int player) {

	int i=0;
	while(i<64)
	{
		if(is_eligible(i, player))
			i++;
	}

	return i;
}