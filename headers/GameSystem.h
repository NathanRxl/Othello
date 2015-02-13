#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "Othellier.h"

class GameSystem
{
	public:
	Othellier _othellierSystem; //[i]==1 if black, [i]==0 if white, [i]==-1 if unoccupied
	int _nbOfWhite;
	int _nbOfBlack;
	int _playerTurn;

	GameSystem();
	void init_game();
	bool flip_exploration(int position, int direction, int player); //Appel�e � disparaitre
	bool flip_is_eligible(int position, int player); //Appel�e � dispara�tre
	void play_position(int position);

};

#endif
