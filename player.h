#ifndef HERO_H
#define HERO_H

#include <QObject>
#include<QTimer>
#include"role.h"
#include<qdebug.h>

class player : public role,public QObject
{


    int exp;//经验值
    int type;

    double scale;
    double weapon_scale_coe;//系数

    int& getexp(){
        return exp;
    }
    int _dir;
    int sword_dir;
    int level;
    int level_exp[10];

    //局内强化记录
    QVector<int>LErecord;

public:

    enum dir
    {
        right,
         down_right,
        down,
        down_left,
        left,
        up_left,
        up,
        up_right,

    };
    player();

    bool up_level();

    enum player_type
    {
        panda,
        penguin
    };


    friend class Gamecontrol;

};

#endif // HERO_H
