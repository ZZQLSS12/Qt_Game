#include "choose_Icon.h"
#include<QDebug>
Choose_Icon::Choose_Icon(QPixmap pix,QPoint pos)
{
    this->setPos(pos);
    this->setPixmap(pix);
}


