#include "GameSystem.h"
#include "Othellier.h"
#include "utils.h"
#include <iostream>

GameSystem::GameSystem()
{
	Othellier _othellierSystem;
	init_game();
}

void GameSystem::init_game(){

	_othellierSystem = Othellier();
	_nbOfBlack = 2;
	_nbOfWhite = 2;
	_playerTurn=1; //Black

}

bool GameSystem::flip_exploration(int position, int direction, int player) //Appelée à disparaitre
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

	if (possible_position(position, direction) == false || (_othellierSystem[moving_position] != 1-player))
		return false;
	else
	{
		while((_othellierSystem[moving_position+direction] == 1-player) && possible_position(moving_position, direction))
		{
			moving_position += direction;
		}
		if (possible_position(moving_position,direction))
		{
			if (_othellierSystem[moving_position+direction] == player)
			{
				while(_othellierSystem[moving_position] == 1-player)
				{
					_othellierSystem[moving_position] = player;

					if(player == 1){_nbOfBlack = _nbOfBlack + 1;_nbOfWhite = _nbOfWhite - 1;}
					else{_nbOfWhite = _nbOfWhite + 1; _nbOfBlack = _nbOfBlack - 1;}

					moving_position -= direction;
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

bool GameSystem::flip_is_eligible(int position, int player) //Appelée à disparaitre
{
																					//if(with_flip == true)
																						std::cout << "Position " << position;

	if(_othellierSystem[position] != -1)
	{
																					//if(with_flip == true)
																						std::cout << " occupied" << std::endl;
		return false;
	}
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
		b[0] = flip_exploration(position, up, player);
		b[1] = flip_exploration(position, up_left, player);
		b[2] = flip_exploration(position, left, player);
		b[3] = flip_exploration(position, down_left, player);
		b[4] = flip_exploration(position, down, player);
		b[5] = flip_exploration(position, down_right, player);
		b[6] = flip_exploration(position, right, player);
		b[7] = flip_exploration(position, up_right, player);

		bool return_value = false;
		for(int i=0; i<8; i++)
		{
			if(b[i] == true)
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

void GameSystem::play_position(int position)
{
	_othellierSystem.flip(position, _playerTurn);

	if(_playerTurn==1)
	{
		_othellierSystem[position] = 1;
		_nbOfBlack = _nbOfBlack + 1;
		_playerTurn = 0;
		std::cout << "Tour du joueur: " << _playerTurn << std::endl;
		std::cout << "Nombre de Noirs: " << _nbOfBlack << std::endl;
		std::cout << "Nombre de Blancs: " << _nbOfWhite << std::endl << std::endl;
	}
	else
	{
		_othellierSystem[position] = 0;
		_nbOfWhite = _nbOfWhite + 1;
		_playerTurn = 1;
		std::cout << "Tour du joueur: " << _playerTurn << std::endl;
		std::cout << "Nombre de Noirs: " << _nbOfBlack << std::endl;
		std::cout << "Nombre de Blancs: " << _nbOfWhite << std::endl << std::endl;
	}
}