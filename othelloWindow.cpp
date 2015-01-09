#include "othelloWindow.h"
#include <qgridlayout.h>

othelloWindow::othelloWindow() :QWidget()
{
	setFixedSize(400, 400);

	QGridLayout *layout=new QGridLayout();
	for(int row=0; row<8; row++)
		for(int col=0; col<8; col++)
		{
         cases[row][col] = new Hlabel(this);
		 cases[row][col]->setPixmap(QPixmap("../../vide.jpg"));
         layout->addWidget(cases[row][col], row, col);
        }
	layout->setHorizontalSpacing(1);
	layout->setVerticalSpacing(1);
	setLayout(layout);



	/*vide=new Hlabel(this);
    vide->setPixmap(QPixmap("../../vide.jpg"));
	
	blanc=new Hlabel(this);
	blanc->setPixmap(QPixmap("../../blanc.jpg"));
	blanc->move(201,101);

	noir=new Hlabel(this);
	noir->setPixmap(QPixmap("../../noir.jpg"));
	noir->move(301,101);*/

	

	QObject::connect(cases[0][0], SIGNAL(clicked()), this, SLOT(cliqueImage(void)));
}

void othelloWindow::cliqueImage(void)
{
	cases[0][0]->setPixmap(QPixmap("../../blanc.jpg"));

}