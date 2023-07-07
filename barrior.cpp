#include "barrior.h"



barrior::barrior(QPoint _pos, QPixmap _img,int t)
{
    this->setPos(_pos);
    this->setPixmap(_img);
    _type = t;

}
