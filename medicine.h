#ifndef MEDICINE_H
#define MEDICINE_H
#include"gameobject.h"

class Medicine:public Gameobject
{
     int recover_hp;
public:
    Medicine();
    void setMedicine(QPoint _pos,QPixmap _img,int num);
    int getrecover_hp()
    {
        return recover_hp;
    }


};

#endif // MEDICINE_H
