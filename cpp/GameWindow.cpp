#include <QGridLayout>
#include "GameWindow.h"

GameWindow::GameWindow():QWidget()
{
	setFixedSize(400, 400);
	setWindowTitle("Othello - Jeu en cours");

	QGridLayout *gameWindowLayout=new QGridLayout();
	for(int row=0; row<8; row++)
		for(int col=0; col<8; col++)
		{
         othellier_squares[row][col] = new ClickableLabel(this);
		 othellier_squares[row][col]->setPixmap(QPixmap("pictures/empty_square.png"));
         gameWindowLayout->addWidget(othellier_squares[row][col], row, col);
        }
	gameWindowLayout->setHorizontalSpacing(1);
	gameWindowLayout->setVerticalSpacing(1);
	setLayout(gameWindowLayout);

	QObject::connect(othellier_squares[0][0], SIGNAL(clicked()), this, SLOT(playPawn(void)));
}

void GameWindow::playPawn(void)
{
	othellier_squares[0][0]->setPixmap(QPixmap("pictures/black_pawn.png"));
}