#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
	public:
	int position;
	bool occupied; //if a pawn is on the square, occupied == true, else occupied == false.
	int pawn_color; //if occupied, then pawn_color == 1 if black, 0 if white. if unoccupied, pawn_color == -1.
	ClickableLabel(QWidget *parent, int i):QLabel(parent){position=i; occupied=false; pawn_color=-1;};

	Q_OBJECT
	signals:
	void clicked(int);
 
	protected:
	void mousePressEvent(QMouseEvent *event) ;
};

#endif