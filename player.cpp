#include "player.h"
#include<QGraphicsPixmapItem>
#include<QTimer>

player::player()
{
    this->setPos(200,200);
    pos=QPoint(200,200);

    scale = 0.33;
    weapon_scale_coe = 1.0;
    atk_frequrncy = 1.0;
    this->setScale(scale);
    ATK=10;

    HP=0;


    _dir=right;
    exp=0;
    level = 0;
    sword_dir = right;


    for(int i=0;i<10;i++)
    {
        level_exp[i] = 5+5*i;
    }

}

bool player::up_level()
{

    if(exp>=level_exp[level])
    {
        exp-=level_exp[level];
        level++;
        if(level==15)
        {
            exp = level_exp[level];
        }
        return true;
    }
    return false;
}


