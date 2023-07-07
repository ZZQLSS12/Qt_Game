#ifndef SWORD_H
#define SWORD_H

#include"gameobject.h"
#include<QSoundEffect>
class sword:public Gameobject
{
    int _dir;
    int ATK;
    QSoundEffect* effect = new QSoundEffect;
public:
    enum dir
    {
        left,
        right
    };

    sword(QPixmap _pix,QPoint _pos,int atk,double scale,int dir);

    void sword_move();

    void sword_sound();

    friend class Gamecontrol;

};

#endif // SWORD_H
