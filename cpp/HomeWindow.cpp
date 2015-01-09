#include "HomeWindow.h"
#include "GameWindow.h"
#include "utils.h"
 
HomeWindow::HomeWindow() : QWidget()
{
    setFixedSize(400, 400);
	setWindowTitle("Othello - Accueil");

	LogoPicture = new QLabel(this);
    LogoPicture->setPixmap(QPixmap("pictures/othello_logo.png"));
 
	newGameButton = new QPushButton("Nouvelle Partie", this);
    newGameButton->setGeometry(150, 200, 100, 50);
	QObject::connect(newGameButton, SIGNAL(clicked()), this, SLOT(open_gameWindow(void)));
}

void HomeWindow::open_gameWindow(void)
{
    GameWindow *gameWindow =new GameWindow;
	this->hide();
	gameWindow->show();
	initGame((*gameWindow).othellier_squares);
}