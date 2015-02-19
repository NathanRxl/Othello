#include "ia.h"
#include "GameSystem.h"
#include <stack>

int min_max_0(GameSystem gameSystem) {
	
	int i=0;
	while(i<64)
	{
		if(gameSystem.is_eligible(i, gameSystem._playerTurn))
			return i;
		i++;
	}
	return -1;

}

int min_max_1(GameSystem gameSystem) {

	if(gameSystem._nbEligiblePlayer == 0)
		return -1;
	int pass_value = gameSystem._nbEligiblePlayer - gameSystem._nbEligibleOpponent;
	int* possible_position = gameSystem.position_eligible();

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

int min_max_2(GameSystem gameSystem)
{
	int deepness_max = 3;
	return min_max(gameSystem, deepness_max).first;
}

std::pair<int,int> min_max(GameSystem gameSystem, int position_played, int deepness_max)
{
	std::pair<int, int> best_position_value;

	if(deepness_max == 0)
	{
		best_position_value.first = position_played;
		best_position_value.second = gameSystem.evaluate();
		return best_position_value;
	}

	GameSystem possibleSystem = gameSystem;
	int* position_value = new int [gameSystem._nbEligiblePlayer];
	for(int i=0; i<gameSystem._nbEligiblePlayer; ++i)
	{
		possibleSystem.play_position(possibleSystem._eligiblePosition[i]);
		position_value[i] = min_max_2(possibleSystem, possibleSystem._eligiblePosition[i], deepness_max-1).second;
	}

	if(deepness_max%2 == 0)
		best_position_value = max(position_value);
	else
		best_position_value = min(position_value);

	delete[] position_value;
	return best_position_value;
}