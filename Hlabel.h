#ifndef DEF_HLABEL
#define DEF_HLABEL

#include <qapplication.h>
#include <qlabel.h>

class Hlabel : public QLabel
{
 
Q_OBJECT
 
public:
    Hlabel( QWidget *parent);
    
 
signals:
    void clicked();
 
protected:
    void mousePressEvent ( QMouseEvent *event ) ;
};


#endif