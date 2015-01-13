#ifndef GAME_H
#define GAME_H


class GameSystem
{
	public:
	int* othellier; //[i]==1 if black, [i]==0 if white, [i]==-1 if unoccupied
	int player_turn;

	GameSystem();
	bool exploration(int position, int direction);
	bool eligible_square(int position);
	void play_position(int position);

};

#endif
