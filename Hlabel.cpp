#include <qapplication.h>
#include <qlabel.h>
#include "Hlabel.h"

Hlabel::Hlabel(QWidget * parent) :
    QLabel(parent)  { }
 
 
 
  void Hlabel::mousePressEvent ( QMouseEvent * event )
  {
      emit clicked();
  }