#ifndef UTILS_H
#define UTILS_H

#include "GameWindow.h"

void initGame(QList<ClickableLabel*> othellier_squares);
bool eligible_square(QList<ClickableLabel*> othellier_squares, int position);

#endif
