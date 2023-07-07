#include "elitist.h"

Elitist::Elitist(QPixmap img):enemy (img)
{
      this->get_type() = Gameobject::O_elitist;
}

void Elitist::Init(QPoint _pos,double x,double y,int Time)
{
    Speed=5;
    HP=10;
    ATK=5;

    if(Time>=100)Speed=8;

    if(Time>=150)HP=15;HPspan =15;

    if(Time>=250)ATK=7;

    dir_x=x;
    dir_y=y;
    this->setPos(_pos);
    pos=_pos;
    this->setScale(0.3);

    Shoot_time = 1;
}


