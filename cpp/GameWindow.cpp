#include <QGridLayout>
#include <QGroupBox>
#include "GameWindow.h"
#include "GameSystem.h"
#include "ai.h"

//Debug
#include <iostream>
#include <cassert>

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
	_passButton->setEnabled(false);
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

void GameWindow::playPawn(int position)
{
	if(_gameSystem.is_eligible(position, _gameSystem._playerTurn))
	{
		_gameSystem.play_position(position);
		display_squares();

														std::cout << "The content of _eligiblePosition is:";
														for (std::vector<int>::iterator it = _gameSystem._eligiblePosition.begin(); it != _gameSystem._eligiblePosition.end(); ++it)
															std::cout << ' ' << *it;
														std::cout << std::endl;

		if(_gameSystem._nbEligiblePlayer == 0)
			_passButton->setEnabled(true);
		if(_gameSystem.is_game_finished() == true)
		{
			_computerTurnButton->setEnabled(false);
			_passButton->setEnabled(false);
			_newGameButton->setEnabled(true);
			if(_gameSystem._nbOfBlack>_gameSystem._nbOfWhite)
			{
				std::cout << "Partie terminee." << std::endl << std::endl;
				std::cout << "Noir a " << _gameSystem._nbOfBlack << " pions." << std::endl;
				std::cout << "Blanc a " << _gameSystem._nbOfWhite << " pions." << std::endl;
				std::cout << "Vainqueur: Joueur 1 (Noirs)." << std::endl;
			}
			if(_gameSystem._nbOfBlack<_gameSystem._nbOfWhite)
			{
				std::cout << "Partie terminee." << std::endl << std::endl;
				std::cout << "Noir a " << _gameSystem._nbOfBlack << " pions."<< std::endl;
				std::cout << "Blanc a " << _gameSystem._nbOfWhite << " pions."<< std::endl;
				std::cout << "Vainqueur: Joueur 2 (Blancs)" << std::endl;
			}
			if(_gameSystem._nbOfBlack==_gameSystem._nbOfWhite)
			{
				std::cout << "Partie terminee." << std::endl << std::endl;
				std::cout << "Noir a "<< _gameSystem._nbOfBlack << " pions." << std::endl;
				std::cout << "Blanc a "<< _gameSystem._nbOfWhite << " pions." << std::endl;
				std::cout << "Ex-aequo." << std::endl;
			}
		}
		else
		{
				std::cout << "Tour du joueur: " << _gameSystem._playerTurn << std::endl;
				std::cout << "Nombre de Noirs: " << _gameSystem._nbOfBlack << std::endl;
				std::cout << "Nombre de Blancs: " << _gameSystem._nbOfWhite << std::endl << std::endl;
		}
	}
}

void GameWindow::newGame()
{
    _gameSystem.init_game();
	display_squares();
	_computerTurnButton->setEnabled(true);
	_passButton->setEnabled(false);
	_newGameButton->setEnabled(false);
}

void GameWindow::pass()
{
	_gameSystem._playerTurn = 1 - _gameSystem._playerTurn;
	int nbEligiblePlayer = _gameSystem._nbEligiblePlayer;
	_gameSystem._nbEligiblePlayer = _gameSystem._nbEligibleOpponent;
	_gameSystem._nbEligibleOpponent = nbEligiblePlayer;
	_gameSystem._eligiblePosition = _gameSystem.eligible_position();
	std::cout << "Tour du joueur: " << _gameSystem._playerTurn << std::endl;
	_passButton->setEnabled(false);
																	std::cout << "The contents of _eligiblePosition are:";
																	for (std::vector<int>::iterator it = _gameSystem._eligiblePosition.begin(); it != _gameSystem._eligiblePosition.end(); ++it)
																		std::cout << ' ' << *it;
																	std::cout << std::endl;
						
}

void GameWindow::computerTurn(){
	//int chosenPosition = min_max_2(_gameSystem, _gameSystem._playerTurn);
	int alpha =-10000;
	int beta= 10000;
	int chosenPosition = alphaBeta(_gameSystem,-1, 17, alpha, beta).first;

	if(chosenPosition == -1)
		pass();
		
	else
		playPawn(chosenPosition);
}