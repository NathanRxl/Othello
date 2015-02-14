#include <QGridLayout>
#include <QGroupBox>
#include "GameWindow.h"
#include "GameSystem.h"
#include "ia.h"
#include <iostream>

GameWindow::GameWindow() : QWidget()
{
	setFixedSize(430, 520);
	setWindowTitle("Othello - Jeu en cours");

	QVBoxLayout *gameWindowLayout = new QVBoxLayout();

	QGroupBox *othellierGroupBox = new QGroupBox();
	QGridLayout *othellierLayout = new QGridLayout();
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
		{
		 _othellierSquares.append(new ClickableLabel(this, 8*i+j));
		 _othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/empty_square.png"));
         othellierLayout->addWidget(_othellierSquares[8*i+j], j, i);
        }

												//TEST de la taille de la Liste//
												std::cout << "Taille de l'othellier: " << _othellierSquares.size() << std::endl;
												//TEST//
	othellierLayout->setHorizontalSpacing(1);
	othellierLayout->setVerticalSpacing(1);

	for (int position=0; position<64; position++)
	{
		QObject::connect(_othellierSquares[position], SIGNAL(clicked(int)), this, SLOT(playPawn(int)));
	}

	othellierGroupBox->setLayout(othellierLayout);

	QGroupBox *buttonsGroupBox = new QGroupBox();
	QVBoxLayout *buttonsLayout = new QVBoxLayout();

	_computerTurnButton = new QPushButton("IA", this);
	QObject::connect(_computerTurnButton, SIGNAL(clicked()), this, SLOT(computerTurn()));
	_computerTurnButton->setEnabled(true);
	buttonsLayout->addWidget(_computerTurnButton);

	_passButton = new QPushButton("Passer", this);
	QObject::connect(_passButton, SIGNAL(clicked()), this, SLOT(pass()));
	_passButton->setEnabled(true);
	buttonsLayout->addWidget(_passButton);

	_newGameButton = new QPushButton("Nouvelle Partie", this);
	QObject::connect(_newGameButton, SIGNAL(clicked()), this, SLOT(newGame(void)));
	_newGameButton->setEnabled(false);
	buttonsLayout->addWidget(_newGameButton);

	buttonsGroupBox->setLayout(buttonsLayout);

	gameWindowLayout->addWidget(othellierGroupBox);
	gameWindowLayout->addWidget(buttonsGroupBox);
	setLayout(gameWindowLayout);
}

void GameWindow::display_squares()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if (_gameSystem._othellierSystem[8*i+j] == -1)
				_othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/empty_square.png"));
			if (_gameSystem._othellierSystem[8*i+j] == 0)
				_othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/white_pawn.png"));
			if (_gameSystem._othellierSystem[8*i+j] == 1)
				_othellierSquares[8*i+j]->setPixmap(QPixmap("pictures/black_pawn.png"));
		}
	}

}

void GameWindow::game_end_test()
{
	//Tests whether the game is finished or not and does the necessary if yes. Does nothing if not.

	if (_gameSystem._nbOfBlack == 0 || _gameSystem._nbOfWhite == 0) 
	{ 
		//If there is no black or white pawns anymore 
		_computerTurnButton->setEnabled(false);
		_passButton->setEnabled(false);
		_newGameButton->setEnabled(true);
		if (_gameSystem._nbOfBlack == 0)
			std::cout << "Partie terminee. Vainqueur: Joueur 2 (Blancs)" << std::endl << std::endl;
		else
			std::cout << "Partie terminee. Vainqueur: Joueur 1 (Noirs)" << std::endl << std::endl;
	}

	else if(_gameSystem._nbOfBlack+_gameSystem._nbOfWhite == 64)
	{
			//All squares are occupied
			_computerTurnButton->setEnabled(false);
			_passButton->setEnabled(false);
			_newGameButton->setEnabled(true);
			if(_gameSystem._nbOfBlack>_gameSystem._nbOfWhite)
				std::cout << "Partie terminee. Vainqueur: Joueur 1 (Noirs)" << std::endl << std::endl;
			if(_gameSystem._nbOfBlack<_gameSystem._nbOfWhite)
				std::cout << "Partie terminee. Vainqueur: Joueur 2 (Blancs)" << std::endl << std::endl;
			if(_gameSystem._nbOfBlack==_gameSystem._nbOfWhite)
				std::cout << "Partie terminee. Ex-aequo." << std::endl << std::endl;
	}

	else if(_gameSystem._nbOfBlack+_gameSystem._nbOfWhite >= 40)
	{
		//Should be replaced in the future by a simple test on the history of _othellierSystem: if both players passed, the game ends.
		bool end_game = true;
		for(int i=0; i<64; ++i)
		{
			if(_gameSystem._othellierSystem[i] == -1)
			{
				if(_gameSystem._othellierSystem.is_eligible(i, 1) == true || _gameSystem._othellierSystem.is_eligible(i, 0) == true)
					end_game = false;
			}
		}
		if(end_game == true)
		{
			_computerTurnButton->setEnabled(false);
			_passButton->setEnabled(false);
			_newGameButton->setEnabled(true);
			if(_gameSystem._nbOfBlack>_gameSystem._nbOfWhite)
				std::cout << "Partie terminee. Vainqueur: Joueur 1 (Noirs)" << std::endl << std::endl;
			if(_gameSystem._nbOfBlack<_gameSystem._nbOfWhite)
				std::cout << "Partie terminee. Vainqueur: Joueur 2 (Blancs)" << std::endl << std::endl;
			if(_gameSystem._nbOfBlack==_gameSystem._nbOfWhite)
				std::cout << "Partie terminee. Ex-aequo." << std::endl << std::endl;
		}
	}
}

void GameWindow::playPawn(int position)
{
	if(_gameSystem._othellierSystem.is_eligible(position, _gameSystem._playerTurn))
	{
		_gameSystem.play_position(position);
		display_squares();
		game_end_test();
	}
}

void GameWindow::newGame()
{
    _gameSystem.init_game();
	display_squares();
	_computerTurnButton->setEnabled(true);
	_passButton->setEnabled(true);
	_newGameButton->setEnabled(false);
}

void GameWindow::pass()
{
	_gameSystem._playerTurn = 1 - _gameSystem._playerTurn;
	std::cout << "Tour du joueur: " << _gameSystem._playerTurn << std::endl;
}

void GameWindow::computerTurn(){
	int chosenPosition = min_max_0(_gameSystem._othellierSystem, _gameSystem._playerTurn);
	if(chosenPosition == -1)
	{
		_gameSystem._playerTurn = 1 - _gameSystem._playerTurn;
		std::cout << "Tour du joueur: " << _gameSystem._playerTurn << std::endl;
	}
	else
	{
		_gameSystem.play_position(chosenPosition);
		display_squares();
		game_end_test();
	}
}