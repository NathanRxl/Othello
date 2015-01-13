#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
	public:
	int _position;
	ClickableLabel(QWidget *parent, int i):QLabel(parent){_position=i;};

	Q_OBJECT
	signals:
	void clicked(int);
 
	protected:
	void mousePressEvent(QMouseEvent *event) ;
};

#endif