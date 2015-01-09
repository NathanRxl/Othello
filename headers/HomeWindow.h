#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QLabel>
#include <QPushButton>
 
class HomeWindow : public QWidget
{
	private:
	QLabel *LogoPicture;
	QPushButton *newGameButton;

    public:
    HomeWindow();   

	Q_OBJECT
    public slots:
    void open_gameWindow(void);
};

#endif
