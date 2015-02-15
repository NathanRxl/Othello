#include "HomeWindow.h"
#include "GameWindow.h"
#include "GameSystem.h"
#include <iostream>
 
HomeWindow::HomeWindow() : QWidget()
{
    setFixedSize(400, 400);
	setWindowTitle("Othello - Accueil");

	_LogoPicture = new QLabel(this);
    _LogoPicture->setPixmap(QPixmap("pictures/othello_logo.png"));
 
	_newGameButton = new QPushButton("Nouvelle Partie", this);
    _newGameButton->setGeometry(125, 200, 150, 50);
	QObject::connect(_newGameButton, SIGNAL(clicked()), this, SLOT(openGameWindow(void)));

	_settingsButton = new QPushButton("Options", this);
    _settingsButton->setGeometry(125, 260, 150, 50);
	QObject::connect(_settingsButton, SIGNAL(clicked()), this, SLOT(openGameWindow(void)));
	_settingsButton->setEnabled(false);
}

void HomeWindow::openGameWindow(void)
{
    GameWindow *gameWindow = new GameWindow;
	this->hide();
	gameWindow->show();
	gameWindow->display_squares();
}