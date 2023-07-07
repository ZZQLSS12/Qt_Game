#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include"bullet.h"
#include<QtMath>
#define Pi 3.1415926
class elitist_bullet : public bullet
{
public:
    elitist_bullet(QPixmap);
    elitist_bullet(QPoint _pos,QPixmap _img,double rad,int atk);

    void Init(QPoint _pos,QPixmap _img,double rad,int atk);
};

#endif // ENEMY_BULLET_H
