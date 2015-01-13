#include "Game.h"
#include <iostream>

GameSystem::GameSystem()
{
	othellier=new int[64];

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
			othellier[8*i+j]=-1;

	othellier[8*3+3]=1;
	othellier[8*3+4]=0;
	othellier[8*4+3]=0;
	othellier[8*4+4]=1;

	player_turn=1;
}

bool testPosition(int position)
{
	bool b;
	b=(0 <= position%8) && (position%8 < 8) && (0 <= position/8) && (position/8 < 8);
	return b;
}

bool GameSystem::exploration(int position, int direction)
{
	//We test whether [position] and [position+direction] are of different colour
	//and explore in that direction.
	//This function returns true if position is eligible
	//direction: -1=up, +7=up+right, +8=right, +9=down+right
	//+1=down, -7=down+left, -8=left, -9=up+left
	int moving_position=position;

	while((othellier[moving_position+direction] == 1-player_turn) && testPosition(moving_position+direction))
		moving_position+=direction;
	
	if (othellier[moving_position] == player_turn)
		return true;
	else
		return false;
}

bool GameSystem::eligible_square(int position)
{
	if(othellier[position] != -1)
		return false;
	else
	{
		bool b[8];
		b[0]=exploration(position,-9);
		b[1]=exploration(position,-8);
		b[2]=exploration(position,-7);
		b[3]=exploration(position,-1);
		b[4]=exploration(position,1);
		b[5]=exploration(position,7);
		b[6]=exploration(position,8);
		b[7]=exploration(position,9);

		bool return_value=false;
		for(int i=0; i<8; i++)
			{if(b[i] == true)
				return_value=true;}

		return return_value;
}
}

void GameSystem::play_position(int position)
{
	if(this->eligible_square(position))
	{
		if(player_turn==1)
		{
			othellier[position]=1;
			player_turn=0;
			std::cout << "Tour du joueur: " << player_turn << std::endl;
		}
		else
		{
			othellier[position]=0;
			player_turn=1;
			std::cout << "Tour du joueur: " << player_turn << std::endl;
		}
	}
}