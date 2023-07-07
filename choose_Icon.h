#ifndef PLAYER1_H
#define PLAYER1_H
#include"gameobject.h"
#include<QMouseEvent>
class Choose_Icon:public Gameobject
{
public:
    Choose_Icon(QPixmap,QPoint);

    void enterEvent(QEvent* event);
};

#endif // PLAYER1_H
