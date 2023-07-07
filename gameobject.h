#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <QGraphicsPixmapItem>
#include<qdebug.h>

class Gameobject:public QGraphicsPixmapItem
{
protected:
    int Object_type;
    static int count ;
public:
    explicit Gameobject(QObject *parent = nullptr);
     ~Gameobject(){}

    enum type{
        O_p_bullet,
        O_e_bullet,
        O_enemy,
        O_elitist,
    };

    int& get_type()
    {
        return Object_type;
    }

};

#endif // GAMEOBJECT_H
