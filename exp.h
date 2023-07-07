#ifndef EXP_H
#define EXP_H
#include"gameobject.h"

class Exp:public Gameobject
{
    int exp_num;
public:
    Exp();
    void setExp(QPoint _pos,QPixmap _img,int num);
    int getexp()
    {
        return exp_num;
    }

};

#endif // EXP_H
