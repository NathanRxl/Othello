#include "ma_fenetre.h"
#include <iostream>
#include "othelloWindow.h"
 
MaFenetre::MaFenetre() : QWidget()
{
    setFixedSize(200, 100);
 
	m_bouton = new QPushButton("Nouvelle Partie", this);
 
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->move(60, 50);
 
	QObject::connect(m_bouton, SIGNAL(clicked()), this, SLOT(ouvrirfenetre(void)));
	
}

void MaFenetre::ouvrirfenetre(void)
{
    othelloWindow *fenetre=new othelloWindow;
	this->hide();
	fenetre->show();
	std::cout<<"ok";
}