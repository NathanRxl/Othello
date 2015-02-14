#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QPushButton>
#include "ClickableLabel.h"
#include "GameSystem.h"
#include "Othellier.h"

class GameWindow : public QWidget
{
	private:
	QPushButton* _passButton;
	QPushButton* _newGameButton;
	QPushButton* _computerTurnButton;

    public:
	QList<ClickableLabel*> _othellierSquares;
	GameSystem _gameSystem;

    GameWindow();
	//Display the configuration of the _gameSystem._othellierSystem
	void display_squares();
	//Tests whether the game is finished or not and does the necessary if yes. Does nothing if not.
	void game_end_test();

    Q_OBJECT
    public slots:
    void playPawn(int position);
	void newGame();
	void pass();
	void computerTurn();

};
 
#endif