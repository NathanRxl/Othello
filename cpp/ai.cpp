#include "ai.h"
#include "GameSystem.h"
#include "utils.h"

//Debug
#include <cassert>
#include <iostream>

int min_max_0(GameSystem gameSystem, int player) {
	//AI algorithm 0. Plays at the first eligible position found.
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
	//AI algorithm 1. Returns the best position to play without anticipating opponent next plays.
	if(gameSystem._nbEligiblePlayer == 0)
		return -1;
	else
	{
		std::vector<int> possible_position (gameSystem._eligiblePosition);

		GameSystem possibleSystem;
		possibleSystem = gameSystem;

		int* play_value = new int [gameSystem._nbEligiblePlayer];
		for(int i=0;  i<gameSystem._nbEligiblePlayer; ++i)
		{
			possibleSystem.play_position(possible_position[i]);
			play_value[i] = possibleSystem.evaluate();
			possibleSystem = gameSystem;
		}

		std::pair<int, int> best_index_value = max(play_value, gameSystem._nbEligiblePlayer);
		
		return possible_position[best_index_value.first];
	}
}

std::pair<int,int> min_max_recursion(GameSystem gameSystem, int position_played, int depth_max)
{	//Min-max recursive algorithm. Return a pair (position, value of the position).
	//depth_max doit �tre impair
	if(gameSystem._nbEligiblePlayer != gameSystem._eligiblePosition.size())
	{
			std::cout<<"le vector et le tableau n'ont pas la m�me taille"<<std::endl;
			std::cout<<"le vecteur est de taille "<<gameSystem._eligiblePosition.size()<<std::endl;
			std::cout<<"le tableau est de taille "<<gameSystem._nbEligiblePlayer<<std::endl;
			std::cout<<"la profondeur max est "<<depth_max<<std::endl;
	}

	assert(gameSystem._nbEligiblePlayer == gameSystem._eligiblePosition.size());
	


	std::pair<int, int> best_position_value;

	if(depth_max == 0 || gameSystem._nbEligiblePlayer == 0)
	{
		gameSystem._playerTurn = 1-gameSystem._playerTurn; 

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
		position_value[i] = min_max_recursion(possibleSystem, gameSystem._eligiblePosition[i], depth_max-1).second;
		possibleSystem = gameSystem;
		/*if(depth_max == 1)
			std::cout<<"valeur possible: "<<position_value[i]<<std::endl;*/
	}


	if(depth_max%2 == 1)
	{
		std::pair<int, int> max_index_value = max(position_value, gameSystem._nbEligiblePlayer);
		if(max_index_value.first == -1)
		{
			best_position_value.first = -1;
			best_position_value.second = max_index_value.second;
			return best_position_value;
		}
		best_position_value.first = gameSystem._eligiblePosition[max_index_value.first];
		best_position_value.second = max_index_value.second;
	}
	else
	{
		std::pair<int, int> min_index_value = min(position_value, gameSystem._nbEligiblePlayer);
		if(min_index_value.first == -1)
		{
			best_position_value.first = -1;
			return best_position_value;
		}
		best_position_value.first = gameSystem._eligiblePosition[min_index_value.first];
		best_position_value.second = min_index_value.second;
	}

	delete[] position_value;
	return best_position_value;
}

int min_max_2(GameSystem gameSystem, int player){
	//AI algorithm 2. Returns the best position to play anticipating opponent next plays thanks to a min-max algorithm
	//non optimized with alpha-beta pruning.
	int depth_max = 7;
	return min_max_recursion(gameSystem, -1, depth_max).first;
}

std::pair<int,int> alphaBeta(GameSystem gameSystem, int position_played, int depth_max, int alpha, int beta)
{	//Alpha beta pruning recursive algorithm. Return a pair (position, value of the position).
	//depth_max doit �tre impair
	std::pair<int, int> best_position_value;

	if(depth_max == 0 || gameSystem._nbEligiblePlayer == 0)
	{
		gameSystem._playerTurn = 1-gameSystem._playerTurn;
		best_position_value.first = position_played;
		best_position_value.second = gameSystem.evaluate();
		return best_position_value;
	}

	GameSystem possibleSystem;
	possibleSystem = gameSystem;
	std::pair<int,int> possible_position_value;

	if(depth_max%2 == 1)
	{
		best_position_value.second = -10000;
		for(int i=0; i<gameSystem._nbEligiblePlayer; ++i)
		{
			possibleSystem.play_position(gameSystem._eligiblePosition[i]);
			possible_position_value = alphaBeta(possibleSystem, gameSystem._eligiblePosition[i], depth_max-1, alpha, beta);

			if(best_position_value.second < possible_position_value.second)
			{
				best_position_value.first = gameSystem._eligiblePosition[i];
				best_position_value.second = possible_position_value.second;
			}
			alpha = std::max(alpha, best_position_value.second);

			//Beta cut
			//std::cout<<"alpha="<<alpha<<"  beta="<<beta<<"  profondeur="<<depth_max<<std::endl;
			if(alpha >= beta)
				break;
		
			possibleSystem = gameSystem;
			
		}
	}
	else
	{
		best_position_value.second = 10000;
		for(int i=0; i<gameSystem._nbEligiblePlayer; ++i)
		{
			possibleSystem.play_position(gameSystem._eligiblePosition[i]);
			possible_position_value = alphaBeta(possibleSystem, gameSystem._eligiblePosition[i], depth_max-1, alpha, beta);

			
			if(best_position_value.second > possible_position_value.second)
			{
				best_position_value.first = gameSystem._eligiblePosition[i];
				best_position_value.second = possible_position_value.second;
			}
			beta = std::min(beta, best_position_value.second);
			
			//std::cout<<"alpha="<<alpha<<"  beta="<<beta<<"  profondeur="<<depth_max<<std::endl;
			if(alpha >= beta)
				break;

			possibleSystem = gameSystem;
		}
	}
	return best_position_value;
}

int min_max_3(GameSystem gameSystem, int player){
	//AI algorithm 3. Returns the best position to play anticipating opponent next plays thanks to a alpha-beta pruning
	int depth_max = 7;
	int alpha = -10000;
	int beta = 10000;
	std::pair<int, int> alphaBeta_return_value = alphaBeta(gameSystem, -1, depth_max, alpha, beta);
	std::cout<<"Position choisie par l'IA: "<<alphaBeta_return_value.first<<std::endl;
	std::cout<<"Valeur de cette position: "<<alphaBeta_return_value.second<<std::endl;
	return alphaBeta_return_value.first;
}