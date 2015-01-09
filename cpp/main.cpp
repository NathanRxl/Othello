#include <QApplication>
#include "HomeWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
 
    HomeWindow homeWindow;
    homeWindow.show();
 
    return app.exec();
}