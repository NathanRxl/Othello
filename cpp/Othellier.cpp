#include "Othellier.h"
#include "utils.h"
#include <iostream>
#include <cassert>

Othellier::Othellier()
{
	_othellier = new int[64];

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			_othellier[8*i+j]=-1;

	_othellier[8*3+3]=1;
	_othellier[8*3+4]=0;
	_othellier[8*4+3]=0;
	_othellier[8*4+4]=1;
}

void Othellier::archive(int position)
{
	_history.push(position);
}
	

int& Othellier::operator[](int position)
{
	return _othellier[position];
}

void Othellier::flip(int position, int player)
{
	//Flips the neccesary pawns of an othellier as if "position" is played.
	//This function doesn't play in "position"

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

	//Tests whether [position] and [position+direction] are of different colours
	//and flips in that direction.
	for(int i=0; i<8; i++) //loop over directions
	{
		int moving_position = position+direction[i];

		if (is_onboard(position, direction[i]) == true && (_othellier[moving_position] == 1-player))
		{
			while((_othellier[moving_position+direction[i]] == 1-player) && is_onboard(moving_position, direction[i]))
			{
				moving_position += direction[i];
			}
			if (is_onboard(moving_position,direction[i]))
			{
				if (_othellier[moving_position+direction[i]] == player)
				{
					while(_othellier[moving_position] == 1-player)
					{
						_othellier[moving_position] = player;
						moving_position -= direction[i];
					}
				}
			}
		}
	}
}

bool Othellier::is_eligible(int position, int player)
{
	//Returns true if the position is eligible for a given player, false if not
																					//if(with_flip == true)
																						std::cout << "Position " << position;

	if(_othellier[position] != -1)
	{
																					//if(with_flip == true)
																						std::cout << " occupied" << std::endl;
		return false;
	}
	else
	{
		//Tests whether [position] and [position+direction] are of different colours
		//and explore in that direction: if the algorithm find again the initial color, it returns true, else, false.
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

			if (is_onboard(position, direction[i]) == false || (_othellier[moving_position] != 1-player))
				check_direction[i] = false;
			else
			{
				while((_othellier[moving_position+direction[i]] == 1-player) && is_onboard(moving_position, direction[i]))
				{
					moving_position += direction[i];
				}
				if (is_onboard(moving_position,direction[i]))
				{
					if (_othellier[moving_position+direction[i]] == player)
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
}

int Othellier::nb_eligible(int player)
{
	//Returns the number of eligible plays for a given player

	int i=0;
	while(i<64)
	{
		if(is_eligible(i, player))
			i++;
	}

	return i;
}

void Othellier::play(int position, int player)
{
	assert(player == 1 || player == 0);
	_othellier[position] = player;
	this->flip(position, player);
	archive(position);
}