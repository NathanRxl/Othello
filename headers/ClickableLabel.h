#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
	public:
	ClickableLabel(QWidget *parent):QLabel(parent){};

	Q_OBJECT
	signals:
	void clicked();
 
	protected:
	void mousePressEvent(QMouseEvent *event) ;
};

#endif