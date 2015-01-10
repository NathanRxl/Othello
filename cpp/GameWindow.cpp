#include <QGridLayout>
#include "GameWindow.h"
#include "utils.h"
#include <iostream>

GameWindow::GameWindow():QWidget()
{
	setFixedSize(400, 400);
	setWindowTitle("Othello - Jeu en cours");
	player_turn=1;

	QGridLayout *gameWindowLayout=new QGridLayout();

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
		{
		 othellier_squares.append(new ClickableLabel(this,8*i+j));
		 othellier_squares[8*i+j]->setPixmap(QPixmap("pictures/empty_square.png"));
         gameWindowLayout->addWidget(othellier_squares[8*i+j], i, j);
        }

															//TEST de la taille de la Liste//
															std::cout << othellier_squares.size() << std::endl;
															//TEST//

	gameWindowLayout->setHorizontalSpacing(1);
	gameWindowLayout->setVerticalSpacing(1);

	//passButton = new QPushButton("Passer", this);
    //passButton->setGeometry(150, 450, 100, 50);

	setLayout(gameWindowLayout);

	for (int position=0; position<64; position++)
	{
		QObject::connect(othellier_squares[position], SIGNAL(clicked(int)), this, SLOT(playPawn(int)));
	}
}

void GameWindow::playPawn(int position)
{
	if(eligible_square(othellier_squares, position))
	{
		if(player_turn==1)
		{
			othellier_squares[position]->setPixmap(QPixmap("pictures/black_pawn.png"));
			othellier_squares[position]->occupied=true;
			player_turn=0;
			std::cout << "Tour du joueur: " << player_turn << std::endl;
		}
		else
		{
			othellier_squares[position]->setPixmap(QPixmap("pictures/white_pawn.png"));
			othellier_squares[position]->occupied=true;
			player_turn=1;
			std::cout << "Tour du joueur: " << player_turn << std::endl;
		}
	}
}