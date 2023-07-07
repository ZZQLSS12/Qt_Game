#include "enemy.h"
#include<QtDebug>
enemy::enemy(QPixmap img)
{
    this->setPixmap(img);
    this->get_type() = Gameobject::O_enemy;

}


void enemy::Init(QPoint _pos,int Time)
{
    this->setPos(_pos);
    pos=_pos;
    this->setScale(0.3);
    HP=9;
    HPspan = 9;
    ATK=2;
    Speed=8;

    if(Time>=50)HP=13;HPspan=13;

    if(Time>=100)Speed=11;

    if(Time>=150)HP=17;HPspan =17;

    if(Time>=200)ATK=3;

    atk_able = true;
}

void enemy::enemymove(QPoint dir)
{
    this->moveBy(dir.x(),dir.y());

    pos=QPoint(pos.x()+dir.x(),pos.y()+dir.y());
}


