#pragma once
#include <stack>

class Othellier //Pourrait être la partie "statique" sans play et sans flip, et GameSystem serait la partie dynamique
{
public:
	int* _othellier;
	std::stack<int> _history;

	Othellier();
	//Add [position] in the history
	void archive(int position);
	int& operator[](int position);
	//Flips the neccesary pawns of an othellier as if [position] is played.
	//This function doesn't play in "position" and is only a tool for [play].
	void flip(int position, int player);
	//Returns true if [position] is eligible for a given [player], false if not									 
	bool is_eligible(int position, int player);
	//Returns the number of eligible plays for a given [player]
	int nb_eligible(int player);
	//Plays in [position] and flips the necessary pawns.
	void play(int position, int player);
	//Unplays a given position and does the necessary "unflips"
	//void unplay(int position);

};