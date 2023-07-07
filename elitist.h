#ifndef ELITIST_H
#define ELITIST_H
#include"enemy.h"
#include "bullet.h"
#include"widget.h"
#include<QTimer>

class Elitist:public enemy
{
    double dir_x;
    double dir_y;
    int Shoot_time;//实现不同敌人不同时间发射
public:
    Elitist(QPixmap img);
    Elitist(QPoint _pos,QPixmap _img,double x,double y);

    void Init(QPoint _pos,double x,double y,int Time);



    friend class Gamecontrol;

};

#endif // ELITIST_H
