#include <QApplication>
#include "ma_fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
 
    MaFenetre fenetre;
    fenetre.show();
 
    return app.exec();
}