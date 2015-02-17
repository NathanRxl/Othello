#include "ia.h"
#include "GameSystem.h"
#include <iostream>

int min_max_0(GameSystem gameSystem, int player) {
	
	int i=0;
	while(i<64)
	{
		if(gameSystem.is_eligible(i, player))
			return i;
		i++;
	}
	return -1;

}

int min_max_1(GameSystem gameSystem, int player) {
	// WORK IN PROGRESS
	
	int nb_play_player = gameSystem.nb_eligible(player);
	int nb_play_opponent = gameSystem.nb_eligible(1-player);

	int pass_value = nb_play_player-nb_play_opponent;
	std::cout << "Evaluation de passer" << pass_value << std::endl;

	int* possible_play = new int [nb_play_player];
	int* play_value = new int [nb_play_player];
	int* possible_position = new int [nb_play_player];

	int possibility = 0;
	for(int j=0; j<64; ++j)
	{
		while(possibility != nb_play_player)
		{
			if(gameSystem.is_eligible(j, player))
				possible_position[possibility] = j;
			possibility = possibility + 1;
		}
	}

	for(int i=0;  i<nb_play_player; ++i)
	{
		gameSystem.play_position(possible_position[i]);
		play_value[i] = gameSystem.nb_eligible(player) - gameSystem.nb_eligible(1-player);
		//othellier.unplay(possible_position[i], player);
	}

	//MAX
	//return max
	return 1;

}