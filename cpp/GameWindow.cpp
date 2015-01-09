#include <QGridLayout>
#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow():QWidget()
{
	setFixedSize(400, 400);
	setWindowTitle("Othello - Jeu en cours");

	QGridLayout *gameWindowLayout=new QGridLayout();

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
		{
		 othellier_squares.append(new ClickableLabel(this));
		 othellier_squares[8*i+j]->setPixmap(QPixmap("pictures/empty_square.png"));
         gameWindowLayout->addWidget(othellier_squares[8*i+j], i, j);
        }

	//Test de la taille de la Liste
	std::cout << othellier_squares.size() << std::endl;
	//----//

	gameWindowLayout->setHorizontalSpacing(1);
	gameWindowLayout->setVerticalSpacing(1);

	//passButton = new QPushButton("Passer", this);
    //passButton->setGeometry(150, 450, 100, 50);

	setLayout(gameWindowLayout);

	/*for (int position=0; position<64; position++)*/
	QObject::connect(othellier_squares[8*0+0], SIGNAL(clicked()), this, SLOT(playPawn()));
}

void GameWindow::playPawn()
{
	othellier_squares[8*0+0]->setPixmap(QPixmap("pictures/black_pawn.png"));
}