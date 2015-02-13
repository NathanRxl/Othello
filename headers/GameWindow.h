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
	void display_squares(Othellier othellier);

    Q_OBJECT
    public slots:
    void playPawn(int position);
	void newGame();
	void pass();
	void computerTurn();

};
 
#endif