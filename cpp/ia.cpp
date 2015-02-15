#include "ia.h"
#include <iostream>

int min_max_0(Othellier othellier, int player) {
	
	int i=0;
	while(i<64)
	{
		if(othellier.is_eligible(i, player))
			return i;
		i++;
	}
	return -1;

}

int min_max_1(Othellier othellier, int player) {
	// WORK IN PROGRESS
	
	int nb_play_player = othellier.nb_eligible(player);
	int nb_play_opponent = othellier.nb_eligible(1-player);

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
			if(othellier.is_eligible(j, player))
				possible_position[possibility] = j;
			possibility = possibility + 1;
		}
	}

	for(int i=0;  i<nb_play_player; ++i)
	{
		othellier.play(possible_position[i], player);
		play_value[i] = othellier.nb_eligible(player) - othellier.nb_eligible(1-player);
		//othellier.unplay(possible_position[i], player);
	}

	//MAX
	//return max
	return 1;

}