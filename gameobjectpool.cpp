#include "gameobjectpool.h"

Gameobjectpool* Gameobjectpool::instance = nullptr;

Gameobjectpool::Gameobjectpool(QObject* parent):QObject (parent)
{

}

void Gameobjectpool::Init()
{
    for(int i=0;i<20;i++)
    {
        player_bullet* p_bullet = new player_bullet(QPixmap(":/img/D:/桌面/插图/我方子弹.png"));
        mPlayerBulletList.append(p_bullet);

        elitist_bullet* e_bullet = new elitist_bullet(QPixmap(":/img/D:/桌面/插图/敌人子弹1.png"));
        mElitistBulletList.append(e_bullet);

        enemy* e = new enemy(QPixmap(":/img/D:/桌面/插图/新建文件夹/parrot.png"));
        mEnemyList.append(e);

        Elitist* el = new Elitist(QPixmap(":/img/D:/桌面/插图/新建文件夹/rabbit.png"));
        mElitistList.append(el);
    }

}

Gameobject *Gameobjectpool::GetGameobject(int object_type)
{
    switch (object_type)
    {

    case Gameobject::O_p_bullet:
    {
        player_bullet* bullet = mPlayerBulletList.first();
        mPlayerBulletList.pop_front();
        return bullet;
    }
    case Gameobject::O_e_bullet:
    {
        elitist_bullet* bullet = mElitistBulletList.first();
        mElitistBulletList.pop_front();
        return  bullet;
    }
    case Gameobject::O_enemy:
    {
        enemy* e =mEnemyList.first();
        mEnemyList.pop_front();
        return e;
    }
    case Gameobject::O_elitist:
    {
        Elitist* el = mElitistList.first();
        mElitistList.pop_front();
        return el;
    }

    }

}

void Gameobjectpool::RecoverGameobject(Gameobject *obj)
{
    switch (obj->get_type()) {
    case Gameobject::O_p_bullet:
    {
        mPlayerBulletList.append((player_bullet*)obj);
        break;
    }
    case Gameobject::O_e_bullet:
    {
        mElitistBulletList.append((elitist_bullet*)obj);
        break;
    }
    case Gameobject::O_enemy:
    {
        mEnemyList.append((enemy*)obj);
        break;
    }
    case Gameobject::O_elitist:
    {
        mElitistList.append((Elitist*)obj);
        break;
    }

    }
}

void Gameobjectpool::clear()
{

    qDeleteAll(mPlayerBulletList);
    qDeleteAll(mElitistBulletList);
    qDeleteAll(mEnemyList);
    qDeleteAll(mElitistList);

}

Gameobjectpool::~Gameobjectpool()
{
    clear();
}
