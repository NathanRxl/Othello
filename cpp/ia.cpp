#include "ia.h"
#include "utils.h"
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

	GameSystem possibleSystem;
	possibleSystem = gameSystem;

	int* play_value = new int [gameSystem._nbEligiblePlayer];
	for(int i=0;  i<gameSystem._nbEligiblePlayer; ++i)
	{
		possibleSystem.play_position(gameSystem._eligiblePosition[i]);
		play_value[i] = possibleSystem.evaluate();
		possibleSystem = gameSystem;
	}

	std::pair<int, int> best_play_value = max(play_value, gameSystem._eligiblePosition);

	return best_play_value.first;

}

int min_max_2(GameSystem gameSystem)
{
	int depth_max = 1;
	return min_max(gameSystem, -1, depth_max).first;
}

std::pair<int,int> min_max(GameSystem gameSystem, int position_played, int depth_max)
{
	std::pair<int, int> best_position_value;

	if(depth_max == 0)
	{
		best_position_value.first = position_played;
		best_position_value.second = gameSystem.evaluate();
		return best_position_value;
	}

	GameSystem possibleSystem;
	possibleSystem = gameSystem;
	int* position_value = new int [gameSystem._nbEligiblePlayer];
	for(int i=0; i<gameSystem._nbEligiblePlayer; ++i)
	{
		possibleSystem.play_position(gameSystem._eligiblePosition[i]);
		position_value[i] = min_max(possibleSystem, gameSystem._eligiblePosition[i], depth_max-1).second;
		possibleSystem = gameSystem;
	}

	if(depth_max%2 == 1)
		best_position_value = max(position_value, gameSystem._eligiblePosition);
	else
		best_position_value = min(position_value, gameSystem._eligiblePosition);

	delete[] position_value;
	return best_position_value;
}