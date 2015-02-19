#include "GameSystem.h"
#include "utils.h"
#include <iostream>

GameSystem::GameSystem()
{
	_othellierSystem = new int[64];
	init_game();
}

void GameSystem::operator=(GameSystem gameSystem)
{
	for(int i=0; i<64; ++i)
		_othellierSystem[i] = gameSystem._othellierSystem[i];
	_playerTurn = gameSystem._playerTurn;
	_nbOfBlack = gameSystem._nbOfBlack;
	_nbOfWhite = gameSystem._nbOfWhite;
	_nbEligiblePlayer = gameSystem._nbEligiblePlayer;
	_nbEligibleOpponent = gameSystem._nbEligibleOpponent;
	_eligiblePosition = gameSystem._eligiblePosition;
}

void GameSystem::init_game(){
	//Initiates the othellier and launches the game: black begins
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			_othellierSystem[8*i+j]=-1;

	_othellierSystem[8*3+3]=0;
	_othellierSystem[8*3+4]=1;
	_othellierSystem[8*4+3]=1;
	_othellierSystem[8*4+4]=0;

	_nbOfBlack = 2;
	_nbOfWhite = 2;
	_playerTurn = 1; //Black
	_nbEligiblePlayer = 4;
	_nbEligibleOpponent = 4;

	_eligiblePosition = eligible_position();
}

bool GameSystem::is_eligible(int position, int player)
{
	//Returns true if the position is eligible for a given player, false if not
																						//std::cout << "Position " << position;

	if(_othellierSystem[position] != -1)
	{
																						//std::cout << " occupied" << std::endl;
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

			if (is_onboard(position, direction[i]) == false || (_othellierSystem[moving_position] != 1-player))
				check_direction[i] = false;
			else
			{
				while((_othellierSystem[moving_position+direction[i]] == 1-player) && is_onboard(moving_position, direction[i]))
				{
					moving_position += direction[i];
				}
				if (is_onboard(moving_position,direction[i]))
				{
					if (_othellierSystem[moving_position+direction[i]] == player)
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

																				//if (return_value)
																					//std::cout << " eligible? true" << std::endl;
																				//else
																					//std::cout << " eligible? false" << std::endl;//}
		return return_value;
	}
}

int GameSystem::nb_eligible(int player)
{
	//Returns the number of eligible plays for a given player

	int return_value=0;
	for(int i=0; i<64; ++i)
	{
		if(is_eligible(i, player))
			return_value=return_value+1;
	}

	return return_value;
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
	_nbEligiblePlayer = nb_eligible(_playerTurn);
	_nbEligibleOpponent = nb_eligible(1-_playerTurn);
	_eligiblePosition.clear();
	_eligiblePosition = eligible_position();

	std::cout << "Tour du joueur: " << _playerTurn << std::endl;
	std::cout << "Nombre de Noirs: " << _nbOfBlack << std::endl;
	std::cout << "Nombre de Blancs: " << _nbOfWhite << std::endl << std::endl;
}

bool GameSystem::is_game_finished()
{
	//Tests whether the game is finished or not and does the necessary if yes. Does nothing if not.

	if (_nbOfBlack == 0 || _nbOfWhite == 0) 
		//If there is no black or white pawns anymore 
		return true;

	else if(_nbOfBlack+_nbOfWhite == 64)
		//All squares are occupied
		return true;

	else if(_nbEligiblePlayer == 0 && _nbEligibleOpponent == 0)
		return true;

	else
		return false;
}

int GameSystem::evaluate()
{
	int bonus = 0;
	int opponent_pawns = _nbOfBlack*(1-_playerTurn)+_nbOfWhite*_playerTurn;

	if(opponent_pawns == 0)
		bonus = bonus + 100;
	int corner_bonus = 10;
	if(_othellierSystem[0] == _playerTurn)
		bonus = bonus + corner_bonus;
	if(_othellierSystem[7] == _playerTurn)
		bonus = bonus + corner_bonus;
	if(_othellierSystem[56] == _playerTurn)
		bonus = bonus + corner_bonus;
	if(_othellierSystem[63] == _playerTurn)
		bonus = bonus + corner_bonus;
	
	int liberty_degree = _nbEligiblePlayer-_nbEligibleOpponent;

	int grade = liberty_degree;

	return grade+bonus;
}

std::vector<int> GameSystem::eligible_position()
{
	std::vector<int> possible_position;

	int possibility = 0;
	for(int j=0; j<64; ++j)
	{
		if(possibility < _nbEligiblePlayer)
		{
			if(is_eligible(j, _playerTurn))
			{
				possible_position.push_back(j);
				possibility = possibility + 1;
			}
		}
	}

	return possible_position;
}