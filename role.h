#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include<gameobject.h>

class role:public Gameobject
{
protected:

    role();

    int HP;
    double Speed;
    int ATK;
    QPoint pos;
    bool atk_able;
    double atk_frequrncy;
    int HPspan;
public:

    friend class Gamecontrol;

};

#endif // GAME_OBJECT_H
