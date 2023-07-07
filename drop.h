#ifndef DROP_H
#define DROP_H

#include"gameobject.h"

class Drop:public Gameobject
{
    int num;
public:
    Drop();
    Drop(QPixmap,int);

};

#endif // DROP_H
