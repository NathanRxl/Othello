#include "utils.h"

void initGame(QList<ClickableLabel*> othellier_squares){
	othellier_squares[8*3+3]->setPixmap(QPixmap("pictures/black_pawn.png"));
	othellier_squares[8*3+3]->occupied=true;
	othellier_squares[8*3+4]->setPixmap(QPixmap("pictures/white_pawn.png"));
	othellier_squares[8*3+4]->occupied=true;
	othellier_squares[8*4+3]->setPixmap(QPixmap("pictures/white_pawn.png"));
	othellier_squares[8*4+3]->occupied=true;
	othellier_squares[8*4+4]->setPixmap(QPixmap("pictures/black_pawn.png"));
	othellier_squares[8*4+4]->occupied=true;
}

bool eligible_square(QList<ClickableLabel*> othellier_squares, int position){
	if(othellier_squares[position]->occupied == false)
		return true;
	else
		return false;
}