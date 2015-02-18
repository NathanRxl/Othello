#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

class GameSystem
{
	public:
	//[i]==1 if black, [i]==0 if white, [i]==-1 if unoccupied
	int* _othellierSystem;
	int _nbOfWhite;
	int _nbOfBlack;
	// _playerTurn == 1 means black, _playerTurn == 0 means white. 1-_playerTurn means the other player.
	int _playerTurn;
	int _nbEligiblePlayer; //Number of eligible plays for player [_playerTurn]
	int _nbEligibleOpponent; //Number of eligible plays for player [1-_playerTurn]

	//Initiates the othellier and launches the game: black begins.
	//This function is only a tool for the GameSystem constructor
	void init_game();
	GameSystem();
	void operator=(GameSystem gameSystem);
	bool is_eligible(int position, int player); //Intérêt à discuter ensemble.
	int nb_eligible(int player); //Intérêt à discuter ensemble.
	//Flips the neccesary pawns of an othellier as if [position] is played.
	//This function doesn't play in "position" and is only a tool for [play_position]
	void flip(int position);
	//Plays a given [position] on the system board and does the necessary flips
	void play_position(int position);
	bool is_game_finished();
	int evaluate();
	int* position_eligible(); //Returns table of possible position for the player
};

#endif
