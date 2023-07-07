#include "exp.h"

Exp::Exp()
{

}

void Exp::setExp(QPoint _pos, QPixmap _img, int num)
{
    this->setPos(_pos);
    this->setPixmap(_img);
    this->setScale(0.15);
    exp_num=num;
}
