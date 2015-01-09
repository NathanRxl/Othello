#ifndef DEF_OTHELLOWINDOW
#define DEF_OTHELLOWINDOW
 
#include <QApplication>
#include <QWidget>
#include <Qlabel>
#include <QGridLayout>
#include <qlist.h>

#include "Hlabel.h"

class othelloWindow : public QWidget
{
	private:
	Hlabel* cases[8][8];
	
	
    public:
    othelloWindow();

    Q_OBJECT
    public slots:
    void cliqueImage(void);

};
 
#endif