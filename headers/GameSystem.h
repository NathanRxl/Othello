#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H


class GameSystem
{
	public:
	int* _othellierSystem; //[i]==1 if black, [i]==0 if white, [i]==-1 if unoccupied
	int _nbOfWhite;
	int _nbOfBlack;
	int _playerTurn;

	GameSystem();
	void init_game();
	bool exploration(int position, int direction);
	bool eligible_square(int position);
	void play_position(int position);

};

#endif
