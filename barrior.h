#ifndef BARRIOR_H
#define BARRIOR_H

#include"gameobject.h"
class barrior:public Gameobject
{
int _type;
public:
    enum type
    {
        fra,//可摧毁
        tou //不可摧毁
    };
    barrior(QPoint _pos,QPixmap _img,int t);
    friend class Gamecontrol;

};

#endif // BARRIOR_H
