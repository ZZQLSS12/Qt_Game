#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include"gamedefine.h"
#include"widget.h"

class Gamecontrol: public QObject
{
    Gamecontrol(QWidget* parent = nullptr);
    static Gamecontrol* instance;
public:
    static Gamecontrol* Instance()
    {
        if(instance == nullptr)
        {
            return instance = new Gamecontrol(Widget::widget);
        }
        return instance;

    }

    ~Gamecontrol()
    {
        qDebug()<<"游戏释放";
    }

    void gameset();

    //游戏初始化
    void gameinit();
    void Loadstartscreen();
    void Loadchoosescreen();
    void Loadstorescreen();
    void Loadreadrecordscreen();
    void Loadgamescreen();
    void Loadoverscreen();
    //游戏开始
    void Timercreate();
    void Gamestart();
    //游戏暂停
    void Game_stop();
    //游戏继续
    void Game_continue();
    //游戏结束
    void gameover();
    //判断游戏结束与否
    void gameover_judge();
    //结算
    int gameresult();

    void CLKset();
    void Levelset();

    void Local_Enhance_set();//局部强化初始化
    void EDictionaryset();
    void Overall_Enhance_set();//全局强化初始化
    void ODictionaryset();
    void OCoincostset();//全局强化消耗金币设置

    //敌人随时间强化
    void Enemy_enhance();

    //读取存档
    void read_file();
    //写入存档
    void write_file();
    //修改存档
    void alter_file();

    //角色初始化
    void Player_init();

    void Page_create();



    //移动函数
    void Player_move();

   //子弹生成
   void Player_bullet_create();
   //刀光产生
   void Swordcreate();
   //敌人子弹生成
   void Elitist_bullet_create();
   //敌人生成
   void enemy_create();
   //精英怪生成
   void elitist_create();
   //玩家子弹碰撞检测
   void P_bullet_Collison();
   //敌方子弹碰撞检测
   void E_bullet_Collison();
   //刀光碰撞检测
   void P_Sword_Collison();
   //敌方单位受伤闪烁效果
   void E_hurt_flicker(enemy*);
   //敌人与玩家碰撞
   void P_E_Collison();
   //玩家与经验碰撞拾取
   void P_Exp_Collison();
   //玩家与烤鸡碰撞
   void P_Med_Collison();
   //障碍物的碰撞
   bool Barrior_Collison(Gameobject*);


   //敌人死亡掉落 exp 或者 medicine
   void dead_drop(QPoint pos);

   //爆炸特效
   void explore(Gameobject* obj);

   void Add_sound(QUrl url);

   //画血条和经验条
   void Draw_init();
   void Draw_HP();
   void Draw_EXP();

   //强化角色或者武器
   void Enhance(int);

//   QList<int> mKeyList;//按键容器
//   player* Player;

protected:

    player* Player;//游戏主角

    QGraphicsScene mGameScene;//主场景
    QGraphicsScene mStartScene;//开始场景
    QGraphicsScene mStoreScene;//商店场景
    QGraphicsScene mRead_recordScene;
    QGraphicsScene mChooseScene;//选择场景
    QGraphicsScene mOverScene;//结束场景（暂定）
    QGraphicsView mGameView;//游戏视图

    QSoundEffect* effect;//音效

    //游戏内交互(强化和暂停)界面
    QGraphicsPixmapItem* pix;
    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;

    int Time;
    int coin;
    float coin_coe;//金币获取系数
    bool Game_id;//判断读档游戏还是新游戏

    //画笔
    QPen pen;
    //血条
    QGraphicsLineItem* HP_line1;
    QGraphicsLineItem* HP_line2;
    QGraphicsLineItem* HP_line3;
    QGraphicsLineItem* HP_line4;
    QGraphicsLineItem* HP_line5;
    //经验条
    QGraphicsLineItem* Exp_line1;
    QGraphicsLineItem* Exp_line2;
    QGraphicsLineItem* Exp_line3;
    QGraphicsLineItem* Exp_line4;
    QGraphicsLineItem* Exp_line5;
    //血条框
    QGraphicsRectItem* HP_rect;
    //经验框
    QGraphicsRectItem* Exp_rect;

    //时间
    QLabel* CLK;
    //等级
    QLabel* Level;


    //游戏生存时间增加计时器
    QTimer* TimeCountTimer;
    //人物移动定时器
    QTimer* PlayerMoveTimer;
    //玩家子弹产生定时器
    QTimer* PlayerBulletShootTimer;
    //玩家近战刀光定时器
    QTimer* PlayerSwordTimer;
    //剑气移动
    QTimer* SwordMoveTimer;
    //移除刀光
    QTimer* PlayerSwordRemoveTimer;
    //敌人子弹产生定时器
    QTimer* EliistBulletshootTimer;
    //子弹飞行定时器
    QTimer* BulletMoveTimer;
    //敌人创造定时器
    QTimer* EnemycreateTimer;
    //敌人移动定时器
    QTimer* EnemymoveTimer;
    //碰撞检测定时器
    QTimer* CollisionTimer;
    //状态更新定时器
    QTimer* StatesUpdateTimer;
    //精英怪产生定时器
    QTimer* ElitistcreateTimer;
    //局内强化词条
    QMap<int, QString>EDictionary;
    //全局强化词条
    QMap<int,QString>ODictionary;
    //全局强化消耗金币
    QVector<int>OCoincost;
    //全局强化记录
    QVector<int>OErecord;


    QList<player_bullet*> mPlayerBulletList;//我方子弹容器
    QList<sword*> mPlayerSwordList;//近战效果容器
    QList<elitist_bullet*> mElitistBulletList;//精英怪子弹子弹
    QList<enemy*> mEnemyList;//敌人容器
    QList<Exp*> mExpList;//经验容器
    QList<Medicine*> mMedList;//回复生命值的烤鸡容器
    QList<Elitist*> mElitistList;//精英怪容器
    QList<barrior*>mBarriorList;//障碍物 3个可破坏 2个不可破坏
    QList<int> mKeyList;//按键容器

signals:
    void level_up();
public slots:
    //打开局内强化界面
    void Enhance_page_start();
    //游戏内暂停页面（涉及存档功能）
    void Stop_page_start();

    friend class Widget;

};

#endif // GAMECONTROL_H
