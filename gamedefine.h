#ifndef GAMEDEFINE_H
#define GAMEDEFINE_H

#include<QGraphicsPixmapItem>//图形元素
#include<QGraphicsView>//视图
#include<QGraphicsScene>//场景
#include<QKeyEvent>
#include<QList>
#include<QPoint>
#include<QKeyEvent>
#include<QTimer>
#include<Abutton.h>
#include<QDebug>
#include<QLabel>
#include<QMouseEvent>
#include<QToolButton>
#include<QPen>
#include<QtMath>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<QMap>
#include<QFile>
#include<QFileDialog>
#include<QMovie>
#include<QMediaPlayer>
#include <QSoundEffect>

#include<medicine.h>
#include"elitist.h"
#include"choose_Icon.h"
#include"enemy.h"
#include"exp.h"
#include"player.h"
#include"Abutton.h"
#include<QObject>
#include"bullet.h"
#include"player_bullet.h"
#include"elitist_bullet.h"
#include"barrior.h"
#include"fragile_barrior.h"
#include"tough_barrior.h"
#include"sword.h"
#include"enhance_page.h"
#include<form.h>
#include"gameobjectpool.h"

#define THP 20
#define Enemy_HP 10

//游戏定义类
class Gamedefine
{
    Gamedefine();
public:
    static const int PlayerMoveTime=10;
    static const int PlayerBulletShootTime=1000;
    static const int BulletMoveTime=10;
    static const int EnemycreateTime=3000;
    static const int ElitistcreateTime =5000;
    static const int EnemymoveTime = 50; 
    static const int CollisionTime=20;
    static const int StatesUpdateTime=1;
    static const int EliistBulletshootTime = 500;
    static const int PlayerSwordTime = 2000;
    static const int SwordMoveTime = 30;
    static const int PlayerSwordRemoveTime = 400;
    static const int TimeCountTime = 1000;

    //开始界面宽高
    static const int startscreenwidth= 1200;
    static const int startscreenheight= 800;
    //角色选择界面宽高
    static const int choosescreenwidth= 1200;
    static const int choosecreenheight= 800;
    //游戏界面宽高
    static const int gamescreenwidth= 1800;
    static const int gamescreenheight= 1198;
    //结算界面宽高
    static const int overscreenwidth= 1084;
    static const int overscreenheight= 609;

    //一些与全局强化相关的系数
    static const int O_ATK_coefficient = 3;//攻击力增加系数
    static const int O_Weapon_Scale_coefficient = 1;//武器范围乘数，除以10使用
    static const int O_HP_coefficient = 5;//生命值增加系数
    static const int O_Speed_coefficient = 3;//速度增加系数
    static const int O_Coin_coefficient = 3;//金币倍率系数，除以10使用

    //一些与局部强化相关的系数
    static const int L_ATK_coefficient = 2;//攻击力增加系数
    static const int L_Weapon_fre_coefficient = 1;//武器攻击频率，除以十
    static const int L_Weapon_scale_coefficient = 1;//武器范围，除以十使用
    static const int L_Scale_coefficient = 1;//乘数，除以10使用
    static const int L_HP_coefficient = 4;//生命值增加系数
    static const int L_Speed_coefficient = 3;//速度增加系数








};

#endif // GAMEDEFINE_H
