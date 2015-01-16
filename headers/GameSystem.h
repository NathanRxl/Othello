#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H


class GameSystem
{
	public:
	int* _othellierSystem; //[i]==1 if black, [i]==0 if white, [i]==-1 if unoccupied
	int _playerTurn;

	GameSystem();
	void init_game();
	bool exploration(int position, int direction, bool only_test=false);
	bool eligible_square(int position, bool only_test=false); //Si l'on veut simplement tester si la case est jouable ou non,
															  //passer only_test à true en argument
	void play_position(int position);

};

#endif
