#ifndef ENEMY_H
#define ENEMY_H

#include <role.h>

class enemy:public role
{

public:
    enemy(QPixmap img);
    enemy(QPoint _pos,QPixmap _img);
    void Init(QPoint _pos,int Time);
    void enemymove(QPoint dir);


public slots:




};

#endif // ENEMY_H
