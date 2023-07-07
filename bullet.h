#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"
#include<QDebug>
#include<QSoundEffect>

class bullet: public Gameobject
{
protected:
    int bullet_speed;//子弹速度
    double x_dir;
    double y_dir;
    int ATK;
public:


    bullet(QPixmap);
    bullet(QPoint _pos,QPixmap _img,int atk);
    ~bullet(){}
    void bulletmove();

    friend class Gamecontrol;

};

#endif // BULLET_H
