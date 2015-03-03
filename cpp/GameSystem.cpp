#include "GameSystem.h"
#include "utils.h"

//Debug
#include <cassert>
#include <iostream>

void GameSystem::init_game(){
	//Initiates the othellier and launches the game: black begins
	
	//Initiates all squares at "unoccupied" state
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			_othellierSystem[8*i+j]=-1;

	//Places the 4 pawns at the center of the board
	_othellierSystem[8*3+3]=0;
	_othellierSystem[8*3+4]=1;
	_othellierSystem[8*4+3]=1;
	_othellierSystem[8*4+4]=0;

	//Initiates the other GameSystem fields
	_nbOfBlack = 2;
	_nbOfWhite = 2;
	_playerTurn = 1; //Black
	_nbEligiblePlayer = 4;
	_nbEligibleOpponent = 4;
	_eligiblePosition = eligible_position();
	assert(_eligiblePosition.size() == _nbEligiblePlayer);
}

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
	_eligiblePosition.assign(gameSystem._eligiblePosition.begin(), gameSystem._eligiblePosition.end());
	assert(_eligiblePosition.size() == _nbEligiblePlayer);
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

			if (stay_onboard(position, direction[i]) == false || (_othellierSystem[moving_position] != 1-player))
				check_direction[i] = false;
			else
			{
				while((_othellierSystem[moving_position+direction[i]] == 1-player) && stay_onboard(moving_position, direction[i]))
				{
					moving_position += direction[i];
				}
				if (stay_onboard(moving_position,direction[i]))
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

		if (stay_onboard(position, direction[i]) == true && (_othellierSystem[moving_position] == 1-_playerTurn))
		{
			while((_othellierSystem[moving_position+direction[i]] == 1-_playerTurn) && stay_onboard(moving_position, direction[i]))
			{
				moving_position += direction[i];
			}
			if (stay_onboard(moving_position,direction[i]))
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
	_nbEligibleOpponent = nb_eligible(1-_playerTurn);

	_eligiblePosition.clear();

	_nbEligiblePlayer = 0;
	for(int j=0; j<64; ++j)
	{
		if(is_eligible(j, _playerTurn))
		{
			_eligiblePosition.push_back(j);
			_nbEligiblePlayer += 1;
		}
	}
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
	//Computes the grade of the board
	int liberty_degree = _nbEligiblePlayer-_nbEligibleOpponent;
		int opponent_pawns = _nbOfBlack*(1-_playerTurn)+_nbOfWhite*_playerTurn;
		int player_pawns = _nbOfBlack*(_playerTurn)+_nbOfWhite*(1-_playerTurn);
	int pawns_difference = player_pawns-opponent_pawns;
	int weight_liberty;
	int weight_pawns;
	int grade;
	if(_nbOfBlack+_nbOfWhite < 34) // First 30 plays
		grade = liberty_degree;
	else if(_nbOfBlack+_nbOfWhite > 56) // Last 8 plays
		grade = pawns_difference;
	else
	{
		weight_liberty = 56-(_nbOfBlack+_nbOfWhite);
		weight_pawns = _nbOfBlack+_nbOfWhite-34;
		grade = (weight_liberty*liberty_degree+weight_pawns*pawns_difference)/(weight_liberty+weight_pawns);
	}
																				//std::cout << "Grade: " << grade << std::endl;
																				//std::cout << "Liberty_degree: " << liberty_degree << std::endl;
																				//std::cout << "Pawns_difference: " << pawns_difference << std::endl;
	//Compute the bonuses in addition to the grade
	int bonus = 0;

	//Bonus if the player wins with this board
	if(opponent_pawns == 0)
		bonus = bonus + 1000;
	//Bonus if the player has a pawn in a corner of the board
	int corner_bonus = 500;
	bonus += ((_othellierSystem[0]==_playerTurn) +  (_othellierSystem[7]==_playerTurn) + 
			 (_othellierSystem[56]==_playerTurn) + (_othellierSystem[63]==_playerTurn))*corner_bonus;
	//Malus if the opponent has a pawn in corner of the board
	int corner_opponent_malus = -500;
	bonus += ((_othellierSystem[0]==1-_playerTurn) +  (_othellierSystem[7]==1-_playerTurn) +
			 (_othellierSystem[56]==1-_playerTurn) + (_othellierSystem[63]==1-_playerTurn))*corner_opponent_malus;
	//Bonus if the opponent has a pawn in a position adjacent to a corner
	int corner_adjacent_bonus = +150;
	bonus += ((_othellierSystem[1]==1-_playerTurn) +  (_othellierSystem[6]==1-_playerTurn) +
			  (_othellierSystem[8]==1-_playerTurn) +  (_othellierSystem[9]==1-_playerTurn) +
			 (_othellierSystem[14]==1-_playerTurn) + (_othellierSystem[15]==1-_playerTurn) +
			 (_othellierSystem[48]==1-_playerTurn) + (_othellierSystem[49]==1-_playerTurn) +
			 (_othellierSystem[55]==1-_playerTurn) + (_othellierSystem[54]==1-_playerTurn) + 
			 (_othellierSystem[57]==1-_playerTurn) + (_othellierSystem[62]==1-_playerTurn))*corner_adjacent_bonus;
	//Malus if the player has a pawn in a position adjacent to a corner
	int corner_adjacent_malus = -150;
	bonus += ((_othellierSystem[1]==_playerTurn) +  (_othellierSystem[6]==_playerTurn) +
			  (_othellierSystem[8]==_playerTurn) +  (_othellierSystem[9]==_playerTurn) +
			 (_othellierSystem[14]==_playerTurn) + (_othellierSystem[15]==_playerTurn) +
			 (_othellierSystem[48]==_playerTurn) + (_othellierSystem[49]==_playerTurn) +
			 (_othellierSystem[55]==_playerTurn) + (_othellierSystem[54]==_playerTurn) +
			 (_othellierSystem[57]==_playerTurn) + (_othellierSystem[62]==_playerTurn))*corner_adjacent_malus;

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