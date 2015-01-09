#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE
 
#include <QApplication>
#include <QWidget>
#include <QPushButton>

 
class MaFenetre : public QWidget
{
	private:
	QPushButton *m_bouton;

    public:
    MaFenetre();
	   

	Q_OBJECT
    public slots:
    void ouvrirfenetre(void);
};
 
#endif