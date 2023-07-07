#ifndef Gameobjectpool_H
#define Gameobjectpool_H

#include<QObject>
#include<player_bullet.h>
#include<elitist_bullet.h>
#include<enemy.h>
#include<elitist.h>
#include<gameobject.h>
#include"widget.h"
#include"exp.h"
#include"medicine.h"
class Gameobjectpool: public QObject
{
    Gameobjectpool(QObject* parent = nullptr);
    static Gameobjectpool* instance;
public:
    static Gameobjectpool* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new Gameobjectpool(Widget::widget);
        }

        return  instance;
    }

    void Init();//初始化

    Gameobject* GetGameobject(int object_type);//获取对象池中的缓存对象

    void RecoverGameobject(Gameobject* obj);

    void clear();

    ~Gameobjectpool();


protected:

    QList<player_bullet*>mPlayerBulletList;
    QList<elitist_bullet*> mElitistBulletList;

    QList<enemy*> mEnemyList;//敌人容器
    QList<Elitist*> mElitistList;//精英怪容器

//    QList<Exp*> mExpList;//经验容器
//    QList<Medicine*> mMedList;//回复生命值的烤鸡容器
    //数量太少，单独delete释放





};

#endif // Gameobjectpool_H
