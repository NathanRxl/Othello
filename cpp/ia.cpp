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

	int pass_value = othellier.nb_eligible(player)-othellier.nb_eligible(1-player);

	std::cout << "Evaluation de passer" << pass_value << std::endl;

	//int* othellier = new int[64];

	return 1;


}