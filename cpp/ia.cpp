#include "ia.h"
#include "GameSystem.h"
#include <iostream>
#include "utils.h"
#include <utility>
#include <assert.h>

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
	else
	{
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

		int best_play = min(play_value, gameSystem._nbEligiblePlayer);


		/*int best_value = play_value[0];
		int best_play = 0;
		for(int k=0; k<gameSystem._nbEligiblePlayer; ++k)
		{
			if(best_value < play_value[k])
			{
				best_value = play_value[k];
				best_play = k;
			}
		}*/
		if(best_play == -1)
			std::cout<<"ceci ne devrait pas se passer"<<std::endl;
		return possible_position[best_play];
	}

}

std::pair<int,int> min_max(GameSystem gameSystem, int position_played, int depth_max, int depth_max_max)
{
	if(gameSystem._nbEligiblePlayer != gameSystem._eligiblePosition.size())
	{
			std::cout<<"le vector et le tableau n'ont pas la même taille"<<std::endl;
			std::cout<<"le vecteur est de taille "<<gameSystem._eligiblePosition.size()<<std::endl;
			std::cout<<"le tableau est de taille "<<gameSystem._nbEligiblePlayer<<std::endl;
			std::cout<<"la profondeur max est "<<depth_max<<std::endl;
	}

	assert(gameSystem._nbEligiblePlayer == gameSystem._eligiblePosition.size());
	


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
		position_value[i] = min_max(possibleSystem, gameSystem._eligiblePosition[i], depth_max-1, depth_max_max).second;
		

		if(depth_max == depth_max_max)
		{
			int corner_bonus = 20;
			if(possibleSystem._othellierSystem[0] == gameSystem._playerTurn)
				position_value[i] += corner_bonus;
			if(possibleSystem._othellierSystem[7] == gameSystem._playerTurn)
				position_value[i] += corner_bonus;
			if(possibleSystem._othellierSystem[56] == gameSystem._playerTurn)
				position_value[i] += corner_bonus;
			if(possibleSystem._othellierSystem[63] == gameSystem._playerTurn)
				position_value[i] += corner_bonus;
		

			//We give a malus when we play in a position adjacent to a corner
			int corner_opponent_malus = -20;
			if(possibleSystem._othellierSystem[1] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[6] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[8] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[9] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[14] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[15] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[48] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[49] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[55] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[54] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[57] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
			if(possibleSystem._othellierSystem[62] == gameSystem._playerTurn)
				position_value[i] += corner_opponent_malus;
		}
		possibleSystem = gameSystem;
	}

	int index1 = max(position_value, gameSystem._nbEligiblePlayer);
	int index2 = max(position_value, gameSystem._nbEligiblePlayer);
	
	/*if(index == -1)
	{
		std::cout<<"le nombre de coups possibles est: "<<gameSystem._nbEligiblePlayer<<std::endl;
		best_position_value.first = -1;
		return best_position_value;
	}*/
	//assert(index != -1);

	if(depth_max%2 == 1)
	{
		if(index1 == -1)
		{
			std::cout<<"le nombre de coups possibles est: "<<gameSystem._nbEligiblePlayer<<std::endl;
			best_position_value.first = -1;
			return best_position_value;
		}
		best_position_value.first = gameSystem._eligiblePosition[index1];
	}
	else
	{
		if(index2 == -1)
		{
			std::cout<<"le nombre de coups possibles est: "<<gameSystem._nbEligiblePlayer<<std::endl;
			best_position_value.first = -1;
			return best_position_value;
		}
		best_position_value.first = gameSystem._eligiblePosition[index2];
	}

	delete[] position_value;
	return best_position_value;
}