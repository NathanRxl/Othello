#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QPushButton>
#include "ClickableLabel.h"
#include "Game.h"

class GameWindow : public QWidget
{
	private:
	QPushButton* passButton;

    public:
	QList<ClickableLabel*> othellier_squares;
	int player_turn;
	GameSystem Game;

    GameWindow();
	void display_squares(int* othellier);

    Q_OBJECT
    public slots:
    void playPawn(int position);

};
 
#endif