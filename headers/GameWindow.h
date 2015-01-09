#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "ClickableLabel.h"

class GameWindow : public QWidget
{
	private:
	ClickableLabel *othellier_squares[8][8];
	
    public:
    GameWindow();

    Q_OBJECT
    public slots:
    void playPawn(void);

};
 
#endif