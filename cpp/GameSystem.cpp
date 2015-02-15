#include "GameSystem.h"
#include "Othellier.h"
#include "utils.h"
#include <iostream>

GameSystem::GameSystem()
{
	init_game();
}

void GameSystem::init_game(){
	//Initiates the othellier and launches the game: black begins
	//This function is only a tool for the GameSystem constructor
	_othellierSystem = Othellier();
	_nbOfBlack = 2;
	_nbOfWhite = 2;
	_playerTurn=1; //Black

}

bool GameSystem::is_eligible(int position) //Intérêt à discuter ensemble.
{
	return _othellierSystem.is_eligible(position, _playerTurn);
}

int GameSystem::nb_eligible() //Intérêt à discuter ensemble.
{
	return _othellierSystem.nb_eligible(_playerTurn);
}

void GameSystem::flip(int position)
{
	//Flip the neccesary pawns of an othellier as if "position" is played.
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

		if (is_onboard(position, direction[i]) == true && (_othellierSystem[moving_position] == 1-_playerTurn))
		{
			while((_othellierSystem[moving_position+direction[i]] == 1-_playerTurn) && is_onboard(moving_position, direction[i]))
			{
				moving_position += direction[i];
			}
			if (is_onboard(moving_position,direction[i]))
			{
				if (_othellierSystem[moving_position+direction[i]] == _playerTurn)
				{
					while(_othellierSystem[moving_position] == 1-_playerTurn)
					{
						_othellierSystem[moving_position] = _playerTurn;
						if(_playerTurn == 1)
						{
							_nbOfBlack = _nbOfBlack + 1;
							_nbOfWhite = _nbOfWhite - 1;
						}
						else
						{
							_nbOfWhite = _nbOfWhite + 1;
							_nbOfBlack = _nbOfBlack - 1;
						}
						moving_position -= direction[i];
					}
				}
			}
		}
	}
}

void GameSystem::play_position(int position)
{
	//Plays a given position on the system board and does the necessary flips

	_othellierSystem[position] = _playerTurn;
	_nbOfBlack = _nbOfBlack + _playerTurn;
	_nbOfWhite = _nbOfWhite + (1-_playerTurn);
	this->flip(position);
	_playerTurn = 1-_playerTurn;
	_othellierSystem.archive(position);

	std::cout << "Tour du joueur: " << _playerTurn << std::endl;
	std::cout << "Nombre de Noirs: " << _nbOfBlack << std::endl;
	std::cout << "Nombre de Blancs: " << _nbOfWhite << std::endl << std::endl;
}

bool GameSystem::is_game_finished()
{
	//Tests whether the game is finished or not and does the necessary if yes. Does nothing if not.

	if (_nbOfBlack == 0 || _nbOfWhite == 0) 
	{ 
		//If there is no black or white pawns anymore 
		return true;
	}

	else if(_nbOfBlack+_nbOfWhite == 64)
	{
			//All squares are occupied
			return true;
	}

	else if(_nbOfBlack+_nbOfWhite >= 40)
	{
		//Should be replaced in the future by a simple test on the history of _othellierSystem: if both players passed, the game ends.
		bool end_game = true;
		for(int i=0; i<64; ++i)
		{
			if(_othellierSystem[i] == -1)
			{
				if(_othellierSystem.is_eligible(i, 1) == true || _othellierSystem.is_eligible(i, 0) == true)
					end_game = false;
			}
		}
		return end_game;
	}

	else
		return false;
}