#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QPushButton>
#include "ClickableLabel.h"

class GameWindow : public QWidget
{
	private:
	QPushButton* passButton;

    public:
	QList<ClickableLabel*> othellier_squares;
	int player_turn;
    GameWindow();

    Q_OBJECT
    public slots:
    void playPawn(int position);

};
 
#endif