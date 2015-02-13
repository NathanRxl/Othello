#pragma once
#include <stack>

class Othellier {
private:
	int* othellier;
	std::stack<int> history;

public:
	Othellier();
	int& operator[](int position);
	void flip(int position, int player);
	bool exploration(int position, int player);
	bool is_eligible(int position, int player);
	int nb_eligible(int player);
	//void play(int position);
	//void unplay(int position);

};