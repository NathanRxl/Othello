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

	if(gameSystem._nbEligiblePlayer == 0)
		return -1;

	int pass_value = gameSystem._nbEligiblePlayer - gameSystem._nbEligibleOpponent;
	std::vector<int> possible_position = gameSystem._eligiblePosition;

	GameSystem possibleSystem;
	possibleSystem = gameSystem;

	int* play_value = new int [gameSystem._nbEligiblePlayer];
	for(int i=0;  i<gameSystem._nbEligiblePlayer; ++i)
	{
		possibleSystem.play_position(possible_position[i]);
		play_value[i] = possibleSystem.evaluate();
		possibleSystem = gameSystem;
	}

	int best_value = pass_value;
	int best_play = 0;
	for(int k=0; k<gameSystem._nbEligiblePlayer; ++k)
	{
		if(best_value < play_value[k])
		{
			best_value = play_value[k];
			best_play = k;
		}
	}

	return possible_position[best_play];

}