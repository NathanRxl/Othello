#include "GameSystem.h"
#include <iostream>

GameSystem::GameSystem()
{
	_othellierSystem = new int[64];
	init_game();
}

void GameSystem::init_game(){

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			_othellierSystem[8*i+j]=-1;

	_othellierSystem[8*3+3]=1;
	_othellierSystem[8*3+4]=0;
	_othellierSystem[8*4+3]=0;
	_othellierSystem[8*4+4]=1;

	_playerTurn=1;

}

bool possible_position(int position) //Tests whether [position] is in the board
{
	bool b;
	b = (position < 64) && (position >= 0);
	return b;
}

bool GameSystem::exploration(int position, int direction, bool only_test)
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

	int moving_position = position+direction;

	if (possible_position(moving_position) == false || (_othellierSystem[moving_position] != 1-_playerTurn))
		return false;
	else
	{

		while((_othellierSystem[moving_position+direction] == 1-_playerTurn) && possible_position(moving_position+direction))
			moving_position += direction;
	

		if (possible_position(moving_position))
		{
			if (_othellierSystem[moving_position+direction] == _playerTurn)
			{
				if (only_test == false)
				{
					while(_othellierSystem[moving_position] == 1-_playerTurn)
					{
						_othellierSystem[moving_position] = _playerTurn;
						moving_position -= direction;
					}
				}

				return true;
			}
			else
				return false;
		}

		else
			return false;

	}
}

bool GameSystem::eligible_square(int position, bool only_test)
{
																		std::cout<<position<<std::endl;

	if(_othellierSystem[position] != -1)
		return false;
	else
	{
		int up = 8*0+(-1);           // -1
		int up_left = 8*(-1)+(-1);   // -9
		int left = 8*(-1)+0;         // -8
		int down_left = 8*(-1)+1;    // -7
		int down = 8*0+1;            //  1
		int down_right = 8*1+1;      //  9
		int right = 8*1+0;           //  8
		int up_right = 8*1+(-1);     //  7

		bool b[8];
		b[0] = exploration(position, up, only_test);
		b[1] = exploration(position, up_left, only_test);
		b[2] = exploration(position, left, only_test);
		b[3] = exploration(position, down_left, only_test);
		b[4] = exploration(position, down, only_test);
		b[5] = exploration(position, down_right, only_test);
		b[6] = exploration(position, right, only_test);
		b[7] = exploration(position, up_right, only_test);

																		std::cout << b[7] << std::endl;
		bool return_value = false;
		for(int i=0; i<8; i++)
		{
			if(b[i] == true)
				return_value = true;
		}
		return return_value;
}
}

void GameSystem::play_position(int position)
{
	if(_playerTurn==1)
	{
		_othellierSystem[position] = 1;
		_playerTurn = 0;
		std::cout << "Tour du joueur: " << _playerTurn << std::endl;
	}
	else
	{
		_othellierSystem[position] = 0;
		_playerTurn = 1;
		std::cout << "Tour du joueur: " << _playerTurn << std::endl;
	}
}