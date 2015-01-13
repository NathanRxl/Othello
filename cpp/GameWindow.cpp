#include <QGridLayout>
#include "GameWindow.h"
#include "utils.h"
#include "GameSystem.h"
#include <iostream>

GameWindow::GameWindow():QWidget()
{
	setFixedSize(400, 400);
	setWindowTitle("Othello - Jeu en cours");

	QGridLayout *gameWindowLayout=new QGridLayout();

	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
		{
		 _othellierSquares.append(new ClickableLabel(this, 8*i+j));
		 _othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/empty_square.png"));
         gameWindowLayout->addWidget(_othellierSquares[8*i+j], i, j);
        }

															//TEST de la taille de la Liste//
															std::cout << _othellierSquares.size() << std::endl;
															//TEST//

	gameWindowLayout->setHorizontalSpacing(1);
	gameWindowLayout->setVerticalSpacing(1);

	//_passButton = new QPushButton("Passer", this);
    //_passButton->setGeometry(150, 450, 100, 50);

	setLayout(gameWindowLayout);

	for (int position=0; position<64; position++)
	{
		QObject::connect(_othellierSquares[position], SIGNAL(clicked(int)), this, SLOT(playPawn(int)));
	}
}

void GameWindow::display_squares(int* othellier_system)
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if (othellier_system[8*i+j] == -1)
				_othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/empty_square.png"));
			if (othellier_system[8*i+j] == 0)
				_othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/white_pawn.png"));
			if (othellier_system[8*i+j] == 1)
				_othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/black_pawn.png"));
		}
	}
}

void GameWindow::playPawn(int position)
{
	if(_gameSystem.eligible_square(position))
	{
		_gameSystem.play_position(position);
		display_squares(_gameSystem._othellierSystem);
	}
}