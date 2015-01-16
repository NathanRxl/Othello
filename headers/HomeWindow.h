#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QLabel>
#include <QPushButton>
 
class HomeWindow : public QWidget
{
	private:
	QLabel* _LogoPicture;
	QPushButton* _newGameButton;
	QPushButton* _settingsButton;

    public:
    HomeWindow();   

	Q_OBJECT
    public slots:
    void openGameWindow(void);
	void openSettings(void);
};

#endif
