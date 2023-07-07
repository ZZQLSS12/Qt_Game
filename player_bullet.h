#ifndef PLAYER_BULLET_H
#define PLAYER_BULLET_H
#include"bullet.h"

class player_bullet: public bullet
{
    QSoundEffect* effect = new QSoundEffect;
public:
    player_bullet(QPixmap);
    player_bullet(QPoint _pos,QPixmap _img,int atk,double rad,double scale);

    void Init(QPoint _pos,QPixmap _img,int atk,double rad,double scale);
    void P_bullet_sound();
};

#endif // PLAYER_BULLET_H
