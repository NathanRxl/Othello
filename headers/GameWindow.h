#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QPushButton>
#include "ClickableLabel.h"
#include "GameSystem.h"

class GameWindow : public QWidget
{
	private:
	QPushButton* _passButton;
	QPushButton* _newGameButton;

    public:
	QList<ClickableLabel*> _othellierSquares;
	GameSystem _gameSystem;

    GameWindow();
	void display_squares(int* othellier);

    Q_OBJECT
    public slots:
    void playPawn(int position);
	void newGame();
	void pass();

};
 
#endif