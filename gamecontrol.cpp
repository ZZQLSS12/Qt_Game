#include "gamecontrol.h"
#include "widget.h"
#include"gamedefine.h"

Gamecontrol* Gamecontrol::instance=nullptr;

Gamecontrol::Gamecontrol(QWidget* parent): QObject (parent)
{


}

void Gamecontrol::gameinit()
{

    //对象池初始化
    Gameobjectpool::Instance()->Init();

    Player = new player;
    effect = new QSoundEffect;
    CLK = new QLabel;
    Level = new QLabel;
    coin_coe = 1.0;

    CLKset();
    Levelset();
    EDictionaryset();
    Overall_Enhance_set();

    mGameView.setParent(Widget::widget);

    Timercreate();

    Loadstartscreen();

}

void Gamecontrol::Loadstartscreen()
{
    //开始窗口大小
    Widget::widget->setFixedSize(1200,800);//窗口
    mStartScene.addPixmap(QPixmap(":/img/D:/桌面/插图/91953835_p0_master12001.jpg"));
    mGameView.setSceneRect(0,0,Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);

    AButton* Button1= new AButton(AButton::start_button);
    AButton* Button2= new AButton(AButton::store_button);
    AButton* Button3= new AButton(AButton::record_read_button);
    //按钮添加到开始场景
    mStartScene.addWidget(Button1);
    mStartScene.addWidget(Button2);
    mStartScene.addWidget(Button3);
    //设置视图场景
    mGameView.setScene(&mStartScene);
    mGameView.show();
    //开始界面转选择界面
    connect(Button1,&AButton::clicked,[=](){
         Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
         Loadchoosescreen();
    });
    connect(Button2,&AButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
         Loadstorescreen();
    });
    connect(Button3,&AButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
         Loadreadrecordscreen();
    });
}

void Gamecontrol::Loadchoosescreen()
{
    mGameView.setSceneRect(0,0,Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);

    mChooseScene.addPixmap(QPixmap(":/img/D:/桌面/插图/choose.jpg"));
    Choose_Icon* panda = new Choose_Icon(QPixmap(":/img/D:/桌面/插图/新建文件夹/panda.png"),QPoint(130,200));
    Choose_Icon* penguin = new Choose_Icon(QPixmap(":/img/D:/桌面/插图/新建文件夹/penguin.png"),QPoint(1200-250-256,200));
    Choose_Icon* panda_weapon = new Choose_Icon(QPixmap(":/img/D:/桌面/插图/武器1.png"),QPoint(400,400));
    Choose_Icon* penguin_weapon = new Choose_Icon(QPixmap(":/img/D:/桌面/插图/武器2.png"),QPoint(1200-256,400));
    mChooseScene.addItem(panda);
    mChooseScene.addItem(penguin);
    mChooseScene.addItem(panda_weapon);
    mChooseScene.addItem(penguin_weapon);

    QPushButton* p1= new QPushButton;
    p1->setText("选择熊猫");
    p1->resize(200,50);
    p1->move(200,550);

    connect(p1,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Player->type = player::panda;
        Player_init();
        Loadgamescreen();

    });

    mChooseScene.addWidget(p1);

    QPushButton* p2= new QPushButton;
    p2->setText("选择企鹅");
    p2->resize(200,50);
    p2->move(750,550);

    connect(p2,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Player->type = player::penguin;
        Player_init();
        Loadgamescreen();

    });

    mChooseScene.addWidget(p2);
    //添加返回按钮
    QPushButton* return_button = new QPushButton;
    return_button->setText("返回");
    return_button->resize(120,50);
    return_button->move(1000,700);
    connect(return_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Loadstartscreen();
    });
    //选择界面转游戏界面

    mChooseScene.addWidget(return_button);
    //设置视图
    mGameView.setScene(&mChooseScene);
    mGameView.show();


}

void Gamecontrol::Loadstorescreen()
{
    ODictionaryset();
    //Widget::widget->setFixedSize(Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);//窗口
    mGameView.setSceneRect(0,0,Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);
    QPixmap pix(":/img/D:/桌面/插图/商店背景.jpg");
    QPainter p1(&pix);
    //根据QColor中第四个参数设置透明度，此处position的取值范围是0～255
    p1.fillRect(pix.rect(), QColor(0, 0, 0, 100));
    p1.end();

    QVector<QPushButton*> store_choose_button(8);

    QFont font("Arial",10,10);
    for (int i=0;i<8;i++) {

        store_choose_button[i] = new QPushButton;
        store_choose_button[i]->resize(200,175);
        store_choose_button[i]->setFont(font);
        store_choose_button[i]->setText(ODictionary.value(i));
    }



    store_choose_button[0]->move(80,150);
    store_choose_button[1]->move(80*2+200,150);
    store_choose_button[2]->move(80*3+200*2,150);
    store_choose_button[3]->move(80*4+200*3,150);
    store_choose_button[4]->move(80,150*2+175);
    store_choose_button[5]->move(80*2+200,150*2+175);
    store_choose_button[6]->move(80*3+200*2,150*2+175);
    store_choose_button[7]->move(80*4+200*3,150*2+175);


    mStoreScene.addPixmap(pix);

    for(int i=0;i<8;i++)
    {
        mStoreScene.addWidget(store_choose_button[i]);
    }
    for(int i=0;i<8;i++)
    {
        connect(store_choose_button[i],&QPushButton::clicked,[=](){
            Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/buy.wav"));
            QLabel* tip = new QLabel;
            tip->resize(1200,200);
            tip->move(0,300);
            QFont font("Arial",30,10);
            tip->setFont(font);
            tip->setAlignment(Qt::AlignVCenter);
            tip->setAlignment(Qt::AlignCenter);

            QTimer* temp_timer = new QTimer;
            temp_timer->start(800);


            if(i!=4&&(OErecord[i]==3))
            {
                QPalette pe;
                pe.setColor(QPalette::Background,QColor(1,189,88));
                tip->setAutoFillBackground(true);
                tip->setPalette(pe);
                tip->setText("已达上限，升级失败");
            }
            else if(coin>=OCoincost[i])
            {
                QPalette pe;
                pe.setColor(QPalette::Background,QColor(241,255,0));
                tip->setAutoFillBackground(true);
                tip->setPalette(pe);
                tip->setText("升级成功");
                OErecord[i]++;
                coin-=OCoincost[i];
                ODictionaryset();
                Loadstorescreen();
            }
            else
            {
                QPalette pe;
                pe.setColor(QPalette::Background,QColor(255,30,0));
                tip->setAutoFillBackground(true);
                tip->setPalette(pe);
                tip->setText("金币不足，升级失败");
            }

            mStoreScene.addWidget(tip);

            connect(temp_timer,&QTimer::timeout,[=](){
                tip->hide();
            });

        });

    }

    //添加返回开始界面的按钮

    QPushButton* return_button = new QPushButton;
    return_button->setText("返回");
    return_button->resize(120,50);
    return_button->move(1000,700);
    connect(return_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Loadstartscreen();
    });

    QLabel* coin_label = new QLabel;
    coin_label->setText("金币: "+QString::number(coin));
    coin_label->resize(150,50);
    coin_label->move(1000,0);
    coin_label->setAlignment(Qt::AlignCenter);



    mStoreScene.addWidget(return_button);
    mStoreScene.addWidget(coin_label);

    mGameView.setScene(&mStoreScene);
    mGameView.show();

}

void Gamecontrol::Loadreadrecordscreen()
{
    mGameView.setSceneRect(0,0,Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);

    QPixmap pix(":/img/D:/桌面/插图/读档背景.jpg");
    QPainter p1(&pix);
    //根据QColor中第四个参数设置透明度，此处position的取值范围是0～255
    p1.fillRect(pix.rect(), QColor(0, 0, 0, 40));
    p1.end();

    mRead_recordScene.addPixmap(pix);

    QPushButton* file_read_button = new QPushButton;
    file_read_button->setText("读取存档");
    file_read_button->resize(120,50);
    file_read_button->move(100,200);
    connect(file_read_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        read_file();
    });

    QPushButton* file_write_button = new QPushButton;
    file_write_button->setText("存档");
    file_write_button->resize(120,50);
    file_write_button->move(100,300);
    connect(file_write_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        write_file();
    });

    QPushButton* file_alter_button = new QPushButton;
    file_alter_button->setText("修改存档");
    file_alter_button->resize(120,50);
    file_alter_button->move(100,400);
    connect(file_alter_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Form a;
        a.exec();
    });

    mRead_recordScene.addWidget(file_read_button);
    mRead_recordScene.addWidget(file_write_button);
    mRead_recordScene.addWidget(file_alter_button);

    QPushButton* return_button = new QPushButton;
    return_button->setText("返回");
    return_button->resize(120,50);
    return_button->move(1000,700);
    connect(return_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Loadstartscreen();
    });


    mRead_recordScene.addWidget(return_button);

    mGameView.setScene(&mRead_recordScene);
    mGameView.show();
}

void Gamecontrol::Loadgamescreen()
{

    Gamestart();//打开定时器

    Widget::widget->setFixedSize(Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);//窗口
    mGameView.setSceneRect(0,0,Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);

    mGameScene.addPixmap(QPixmap(":/img/D:/桌面/插图/背景.png"));
    mGameScene.addItem(Player);
    mGameScene.addWidget(CLK);
    mGameScene.addWidget(Level);

    Draw_init();//绘图初始化

    fragile_barrior* b1 = new fragile_barrior(QPoint(300,300),QPixmap(":/img/D:/桌面/插图/可破坏障碍物.png"),barrior::fra);
    fragile_barrior* b2 = new fragile_barrior(QPoint(1200,546),QPixmap(":/img/D:/桌面/插图/可破坏障碍物.png"),barrior::fra);
    fragile_barrior* b3 = new fragile_barrior(QPoint(800,900),QPixmap(":/img/D:/桌面/插图/可破坏障碍物.png"),barrior::fra);

    mGameScene.addItem(b1);
    mGameScene.addItem(b2);
    mGameScene.addItem(b3);

    mBarriorList.append(b1);
    mBarriorList.append(b2);
    mBarriorList.append(b3);

    tough_barrior* b4 = new tough_barrior(QPoint(1278,100),QPixmap(":/img/D:/桌面/插图/不可破坏障碍物.png"),barrior::tou);
    tough_barrior* b5 = new tough_barrior(QPoint(600,700),QPixmap(":/img/D:/桌面/插图/不可破坏障碍物.png"),barrior::tou);

    mGameScene.addItem(b4);
    mGameScene.addItem(b5);

    mBarriorList.append(b4);
    mBarriorList.append(b5);

    QPushButton* return_button = new QPushButton;
    return_button->setText("返回");
    return_button->resize(100,100);
    return_button->move(1600,0);
    connect(return_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Stop_page_start();
    });



    mGameScene.addWidget(return_button);
    mGameView.setScene(&mGameScene);
    mGameView.show();

}

void Gamecontrol::Loadoverscreen()
{
    Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/gameover.wav"));

    Widget::widget->setFixedSize(1084,609);//窗口
    mOverScene.addPixmap(QPixmap(":/img/D:/桌面/插图/Gameover.jpg"));
    mGameView.setSceneRect(0,0,Gamedefine::gamescreenwidth,Gamedefine::gamescreenheight);


    QLabel* coin_plus_label = new QLabel;
    coin_plus_label->setText("获得金币"+QString::number(gameresult()));
    coin_plus_label->resize(150,50);
    coin_plus_label->move(200,500);

    QPushButton* return_button = new QPushButton;
    return_button->setText("返回");
    return_button->resize(120,50);
    return_button->move(800,500);
    connect(return_button,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Player = new player;
        CLK = new QLabel;
        Level = new QLabel;
        CLKset();
        Levelset();
        EDictionaryset();
        Timercreate();
        Loadstartscreen();

    });

    mOverScene.addWidget(return_button);
    mOverScene.addWidget(coin_plus_label);

    mGameView.setScene(&mOverScene);
    mGameView.show();
}

void Gamecontrol::Timercreate()
{
    //先全都创建出来
     PlayerMoveTimer = new QTimer(this);
     PlayerBulletShootTimer = new QTimer(this);
     PlayerSwordTimer = new QTimer(this);
     BulletMoveTimer = new QTimer(this);
     EnemycreateTimer = new QTimer(this);
     ElitistcreateTimer = new QTimer(this);
     EnemymoveTimer = new QTimer(this);
     CollisionTimer = new QTimer(this);
     StatesUpdateTimer = new QTimer(this);
     EliistBulletshootTimer = new QTimer(this);
     TimeCountTimer = new QTimer(this);

     //把定时器和函数绑定一下
     connect(TimeCountTimer,&QTimer::timeout,[this](){
         Time++;
         CLK->setText("生存时间: "+QString::number(Time));
         Enemy_enhance();
     });
     connect(PlayerMoveTimer,&QTimer::timeout,this,&Gamecontrol::Player_move);
     connect(PlayerBulletShootTimer,&QTimer::timeout,this,&Gamecontrol::Player_bullet_create);

     connect(PlayerSwordTimer,&QTimer::timeout,this,&Gamecontrol::Swordcreate);

     connect(BulletMoveTimer,&QTimer::timeout,[=](){

         for(auto player_bullet:mPlayerBulletList)
         {
             if(player_bullet->x()<-150||player_bullet->y()<-150||player_bullet->x()>Gamedefine::gamescreenwidth+150||player_bullet->y()>Gamedefine::gamescreenheight+150)
             {
                 mGameScene.removeItem(player_bullet);
                 Gameobjectpool::Instance()->RecoverGameobject(player_bullet);
                 mPlayerBulletList.removeOne(player_bullet);
             }
             player_bullet->bulletmove();



         }

         for(auto elitist_bullet:mElitistBulletList)
         {
             elitist_bullet->bulletmove();

             if(elitist_bullet->x()<-150||elitist_bullet->y()<-150||elitist_bullet->x()>Gamedefine::gamescreenwidth+150||elitist_bullet->y()>Gamedefine::gamescreenheight+150)
             {
                 mGameScene.removeItem(elitist_bullet);
                 Gameobjectpool::Instance()->RecoverGameobject(elitist_bullet);
                 mElitistBulletList.removeOne(elitist_bullet);
             }
         }
         if(OErecord[6]>=2)
         for(auto sword : mPlayerSwordList)
         {
             sword->sword_move();
         }

     });
     connect(EnemycreateTimer,&QTimer::timeout,this,&Gamecontrol::enemy_create);
     connect(ElitistcreateTimer,&QTimer::timeout,this,&Gamecontrol::elitist_create);
     connect(EnemymoveTimer,&QTimer::timeout,[this](){

         for(auto enemy:mEnemyList)
         {
             double x=Player->x()-enemy->x();
             double y=Player->y()-enemy->y();
             double r=sqrt(x*x+y*y);
             double rex = x/r;
             double rey= y/r;

             enemy->enemymove(QPoint(rex*enemy->Speed,0));
             if(Barrior_Collison(enemy))
             {
                 enemy->enemymove(QPoint(-1*rex*enemy->Speed,0));
             }
             enemy->enemymove(QPoint(0,rey*enemy->Speed));
             if(Barrior_Collison(enemy))
             {
                 enemy->enemymove(QPoint(0,-1*rey*enemy->Speed));
             }
         }

         for(auto Elitist:mElitistList)
         {

             Elitist->enemymove(QPoint(Elitist->dir_x*Elitist->Speed,Elitist->dir_y*Elitist->Speed));

             if(Barrior_Collison(Elitist))
             {
                 Elitist->enemymove(QPoint(-1*Elitist->dir_x*Elitist->Speed,-1*Elitist->dir_y*Elitist->Speed));
                 Elitist->dir_x= - Elitist->dir_x;
                 Elitist->dir_y= - Elitist->dir_y;
             }

             if(Elitist->x()<0)
             {
                 Elitist->setX(0);
                 Elitist->pos.setX(0);
                 Elitist->dir_x= - Elitist->dir_x;
             }
             if(Elitist->y()<0)
             {
                 Elitist->setY(0);
                 Elitist->pos.setY(0);
                 Elitist->dir_y= - Elitist->dir_y;
             }
             if(Elitist->x()>Gamedefine::gamescreenwidth-Elitist->pixmap().width()*0.3)
             {
                 Elitist->setX(Gamedefine::gamescreenwidth-Elitist->pixmap().width()*0.3);
                 Elitist->pos.setX(Gamedefine::gamescreenwidth-Elitist->pixmap().width()*0.3);
                 Elitist->dir_x= - Elitist->dir_x;
             }
             if(Elitist->y()>Gamedefine::gamescreenheight-Elitist->pixmap().height()*0.3)
             {
                 Elitist->setY(Gamedefine::gamescreenheight-Elitist->pixmap().height()*0.3);
                 Elitist->pos.setY(Gamedefine::gamescreenheight-Elitist->pixmap().height()*0.3);
                 Elitist->dir_y= - Elitist->dir_y;
             }


         }

     });
     connect(CollisionTimer,&QTimer::timeout,[this](){

         //所有的碰撞效果
         P_E_Collison();
         P_bullet_Collison();
         E_bullet_Collison();
         P_Sword_Collison();
         P_Exp_Collison();
         P_Med_Collison();

     });

     connect(StatesUpdateTimer,&QTimer::timeout,[this](){

       if(Player->up_level())
       {
           Enhance_page_start();
       }
       if(Player->HP<=0)
       {
           if(OErecord[4]>0)
           gameover_judge();
           else {
               gameover();
               Loadoverscreen();
           }
       }
       Draw_EXP();
       Draw_HP();
     });
     connect(EliistBulletshootTimer,&QTimer::timeout,this,&Gamecontrol::Elitist_bullet_create);

}

void Gamecontrol::Gamestart()
{
    TimeCountTimer ->start(Gamedefine::TimeCountTime);
    PlayerMoveTimer ->start(Gamedefine::PlayerMoveTime);

    if(Player->type==player::panda)
    {
        PlayerBulletShootTimer ->start(Gamedefine::PlayerBulletShootTime);
    }
    else if (Player->type == player::penguin)
    {
        PlayerSwordTimer->start(Gamedefine::PlayerSwordTime);
    }

    BulletMoveTimer ->start(Gamedefine::BulletMoveTime); //玩家和子弹的飞行都在这里
    EnemycreateTimer ->start(Gamedefine::EnemycreateTime);
    ElitistcreateTimer->start(Gamedefine::ElitistcreateTime);
    EliistBulletshootTimer->start(Gamedefine::EliistBulletshootTime);
    EnemymoveTimer ->start(Gamedefine::EnemymoveTime);
    CollisionTimer ->start(Gamedefine::CollisionTime);
    StatesUpdateTimer ->start(Gamedefine::StatesUpdateTime);
}

void Gamecontrol::CLKset()
{
    Time = 0;

    QPalette pe;
    CLK->resize(250,60);
    QFont font("Arial",20,10);
    CLK->setFont(font);
    pe.setColor(QPalette::WindowText,Qt::red);
    CLK->setPalette(pe);

    CLK->setText("生存时间: "+QString::number(Time));
    CLK->move(1000,0);
    CLK->setAlignment(Qt::AlignVCenter);
    CLK->setAlignment(Qt::AlignCenter);
    CLK->setAttribute(Qt::WA_TranslucentBackground, true);//设置背景为透明

}

void Gamecontrol::Levelset()
{
    QPalette pe;
    Level->resize(250,60);
    QFont font("Arial",20,10);
    Level->setFont(font);
    pe.setColor(QPalette::WindowText,QColor(84,221,253));

    Level->setPalette(pe);
    Level->setText("等级: "+QString::number(Player->level));
    Level->move(100,0);
    Level->setAlignment(Qt::AlignVCenter);
    Level->setAlignment(Qt::AlignCenter);
    Level->setAttribute(Qt::WA_TranslucentBackground, true);//设置背景为透明
}

void Gamecontrol::Local_Enhance_set()
{

    Player->LErecord.resize(6);
    for(int i=0;i<6;i++)
    {
        Player->LErecord[i]=0;
    }
}

void Gamecontrol::EDictionaryset()
{
    Player->LErecord.resize(6);
    EDictionary[0] = "武器伤害增加";
    EDictionary[1] = "武器释放频率增加";
    EDictionary[2] = "武器攻击范围增加";

    EDictionary[3] = "人物移动速度增加";
    EDictionary[4] = "人物生命值增加";
    EDictionary[5] = "人物体积变小";
}

void Gamecontrol::Overall_Enhance_set()//
{

    OErecord.resize(8);
    for(auto k:OErecord)
    {
        k=0;
    }

    OCoincost.resize(8);

    ODictionaryset();
}

void Gamecontrol::ODictionaryset()
{

    ODictionary[0] = "武器伤害增加\n";
    ODictionary[1] = "武器攻击范围增加\n";
    ODictionary[2] = "人物生命值增加\n";
    ODictionary[3] = "人物移动速度增加\n";
    ODictionary[4] = "获得一枚返魂丹(复活)\n";

    if(OErecord[5]>=1)
        ODictionary[5] = "子弹数+2(熊猫)\n";
    else
        ODictionary[5] = "子弹击退效果(熊猫)\n";

    if(OErecord[6]==0)
        ODictionary[6] = "双刃斩\n";
    else if(OErecord[6]==1)
        ODictionary[6] = "剑气\n";
    else {
        ODictionary[6] = "剑气销子弹\n";
    }
    ODictionary[7] = "金币初始倍率增加\n";


    OCoincostset();

    for(int i=0;i<8;i++)
    {
        ODictionary[i]+=QString::number(OCoincost[i]);
        ODictionary[i]+="金币\n";
        ODictionary[i]+="level: " + QString::number(OErecord[i]);
    }


}

void Gamecontrol::OCoincostset()
{
    OCoincost[0]=100 + 50 * OErecord[0];
    OCoincost[1]=100 + 50 * OErecord[1];
    OCoincost[2]=100 + 50 * OErecord[2];
    OCoincost[3]=100 + 50 * OErecord[3];
    OCoincost[4]=150;
    OCoincost[5]=500;
    OCoincost[6]=500;
    OCoincost[7]=100 + 100 * OErecord[7];

}

void Gamecontrol::Enemy_enhance()
{
    if(Time==20)
    {
        EnemycreateTimer->setInterval(2000);
    }
    //if(Time>=30)
    //{
        //出现远程精英怪，写在elitist_create里面了
    //}
    if(Time==80)
    {
        EnemycreateTimer->setInterval(1500);

        ElitistcreateTimer->setInterval(4000);
    }
    if(Time==150)
    {
        ElitistcreateTimer->setInterval(2700);
    }

    //其他的写在了enemy和Elitist构造里面了

}

void Gamecontrol::read_file()
{
    QString path = QFileDialog::getOpenFileName(Widget::widget,"选择存档","C:/Qt Game/游戏存档");

    QFile file(path);

    file.open(QIODevice::ReadOnly);

    QString Game_label = file.readLine();

    if(Game_label == "游戏进行\r\n"||Game_label == "游戏进行\n")
    {

        QLabel* tip = new QLabel;
        tip->resize(1200,200);
        tip->move(0,300);
        QFont font("Arial",30,10);
        tip->setFont(font);
        tip->setAlignment(Qt::AlignVCenter);
        tip->setAlignment(Qt::AlignCenter);
        QPalette pe;
        pe.setColor(QPalette::Background,QColor(215,10,237));
        tip->setAutoFillBackground(true);
        tip->setPalette(pe);
        tip->setText("未完成的游戏是否继续");

        font.setPointSize(10);
        QPushButton* btn1 = new QPushButton;
        QPushButton* btn2 = new QPushButton;

        btn1->resize(120,100);
        btn2->resize(120,100);
        btn1->setFont(font);
        btn2->setFont(font);
        btn1->setText("继续游戏");
        btn2->setText("直接结算");

        btn1->move(30,350);
        btn2->move(1050,350);

        connect(btn2,&QPushButton::clicked,[=](){
            Player->LErecord.clear();
            Loadoverscreen();
        });
        connect(btn1,&QPushButton::clicked,[=](){
            Game_id = true;
            Player_init();
            CLK->setText("生存时间: "+QString::number(Time));
            Loadgamescreen();
        });

        mRead_recordScene.addWidget(tip);
        mRead_recordScene.addWidget(btn1);
        mRead_recordScene.addWidget(btn2);
    }


    for(int i=0;i<11;i++)
    {
        QString imformation = file.readLine();

        if(imformation == "coin\r\n"||imformation == "coin\n")
        {
            QString temp = file.readLine();
            coin = temp.toInt();
        }
        else if(imformation == "Time\r\n"||imformation == "Time\n")
        {
            QString temp = file.readLine();
            Time = temp.toInt();
        }
        else if (imformation == "Player_type\r\n"||imformation == "Player_type\n")
        {
            QString temp = file.readLine();
            if(temp == "panda\r\n")
            {
                Player->type = player::panda;
            }
            else {
                Player->type = player::penguin;
            }
        }
        else if(imformation == "HP\r\n"||imformation == "HP\n")
        {
            QString temp = file.readLine();
            Player->HP= temp.toInt();
        }
        else if(imformation == "全局强化信息\r\n"||imformation == "全局强化信息\n")
        {
            for(int i=0;i<8;i++)
            {
                QString temp = file.readLine();
                OErecord[i]= temp.toInt();
            }
        }
        else if(imformation == "局部强化信息\r\n"||imformation == "局部强化信息\n")
        {
            for(int i=0;i<6;i++)
            {
                QString temp = file.readLine();
                Player->LErecord[i]= temp.toInt();
            }
        }
        else if(imformation == "pos\r\n"||imformation == "pos\n")
        {
            QString x = file.readLine();
            QString y = file.readLine();
            Player->pos =QPoint(x.toInt(),y.toInt());
        }
        else if(imformation == "_dir\r\n"||imformation == "_dir\n")
        {
            QString temp = file.readLine();
            Player->_dir = temp.toInt();
        }
        else if(imformation == "exp\r\n"||imformation == "exp\n")
        {
            QString temp = file.readLine();
            Player->exp = temp.toInt();
        }
        else if(imformation == "level\r\n"||imformation == "level\n")
        {
            QString temp = file.readLine();
            Player->level = temp.toInt();
        }
        else if(imformation == "sword_dir\r\n"||imformation == "sword_dir\n")
        {
            QString temp = file.readLine();
            Player->sword_dir = temp.toInt();
        }

        else
        {
            QLabel* tip = new QLabel;
            tip->resize(1200,200);
            tip->move(0,300);
            QFont font("Arial",30,10);
            tip->setFont(font);
            tip->setAlignment(Qt::AlignVCenter);
            tip->setAlignment(Qt::AlignCenter);

            QTimer* temp_timer = new QTimer;
            temp_timer->start(800);
                QPalette pe;
                pe.setColor(QPalette::Background,QColor(255,30,0));
                tip->setAutoFillBackground(true);
                tip->setPalette(pe);
                tip->setText("读取失败");

            mRead_recordScene.addWidget(tip);
            connect(temp_timer,&QTimer::timeout,[=](){
                tip->hide();
             });
         }

     }

    file.close();
}

void Gamecontrol::write_file()
{
    QString path = QFileDialog::getSaveFileName(Widget::widget,"存档","C:/Qt Game/游戏存档/请给存档命名.txt","*.txt");

    QFile file(path);

    file.open(QIODevice::WriteOnly);
    QString text;
    if(Time == 0)
    {
        text+="空游戏\r\n";
    }
    else {
        text+="游戏进行\r\n";
    }

    for(int i=0;i<11;i++)
    {
        switch (i)
        {
        case 0:
        {
            text+="coin\r\n";
            text+=QString::number(coin)+"\r\n";
            break;
        }
        case 1:
        {
            text+="Time\r\n";
            text+=QString::number(Time)+"\r\n";
            break;
        }
        case 2:
        {
            text+="Player_type\r\n";
            if(Player->type == player::panda)
            {
                text+="panda";
                text+="\r\n";
            }
            else {
                text+="penguin";
                text+="\r\n";
            }
            break;
        }
        case 3:
        {
            text+="HP\r\n";
            text+=QString::number(Player->HP)+"\r\n";
            break;
        }
        case 4:
        {
            text+="全局强化信息\r\n";
            for(int i=0;i<8;i++)
            {
                text+=QString::number(OErecord[i])+"\r\n";
            }
            break;
        }
        case 5:
        {
            text+="局部强化信息\r\n";
            for(int i=0;i<6;i++)
            {
                text+=QString::number(Player->LErecord[i])+"\r\n";
            }
            break;
        }
        case 6:
        {
            text+="pos\r\n";
            text+=QString::number(Player->pos.x())+"\r\n";
            text+=QString::number(Player->pos.y())+"\r\n";
            break;
        }
        case 7:
        {
            text+="_dir\r\n";
            text+=QString::number(Player->_dir)+"\r\n";
            break;
        }
        case 8:
        {
            text+="exp\r\n";
            text+=QString::number(Player->exp)+"\r\n";
            break;
        }
        case 9:
        {
            text+="level\r\n";
            text+=QString::number(Player->level)+"\r\n";
            break;
        }
        case 10:
        {
            text+="sword_dir\r\n";
            text+=QString::number(Player->sword_dir)+"\r\n";
            break;
        }
        }
    }

    file.write(text.toUtf8());
    file.close();

}

void Gamecontrol::Player_init()
{
    if(!Game_id)
    {
        for(auto k:Player->LErecord)
            k=0;
    }
    Player->setPos(Player->pos.x(),Player->pos.y());

    if(Player->type == player::panda)
    {
        Player->setPixmap(QPixmap(":/img/D:/桌面/插图/新建文件夹/panda.png"));
        Player->ATK = 6 ;

        Player->HPspan = 20 ;
        Player->Speed = 7 ;
    }
    else {
        Player->setPixmap(QPixmap(":/img/D:/桌面/插图/新建文件夹/penguin.png"));
        Player->ATK = 20 ;

        Player->HPspan = 15 ;
        Player->Speed = 10 ;
    }

    Player->ATK += OErecord[0]*Gamedefine::O_ATK_coefficient+Player->LErecord[0]*Gamedefine::L_ATK_coefficient;

    Player->HPspan += OErecord[2]*Gamedefine::O_HP_coefficient+Player->LErecord[4]*Gamedefine::L_HP_coefficient;
    if(Player->HP==0)
        Player->HP=Player->HPspan;

    Player->Speed+= OErecord[3]*Gamedefine::O_Speed_coefficient+Player->LErecord[3]*Gamedefine::L_Speed_coefficient;

    Player->atk_frequrncy = 1.0-Player->LErecord[1]*Gamedefine::L_Weapon_fre_coefficient/10;

    if(Player->type==player::panda)
    {
        PlayerBulletShootTimer ->setInterval(Gamedefine::PlayerBulletShootTime*Player->atk_frequrncy);
    }
    else if (Player->type == player::penguin)
    {
        PlayerSwordTimer->setInterval(Gamedefine::PlayerSwordTime*Player->atk_frequrncy);
    }

    Player->weapon_scale_coe = (1.0+ (OErecord[1] * Gamedefine::O_Weapon_Scale_coefficient / 10) + (Player->LErecord[2] * Gamedefine::L_Weapon_scale_coefficient/10) );

    Player->scale = Player->scale*(1.0 - Player->LErecord[5]*Gamedefine::L_Scale_coefficient/10);
    Player->setScale(Player->scale);

    Game_id = 0;
}

void Gamecontrol::Page_create()
{
    QGraphicsPixmapItem* temp1 = pix;
    delete temp1;
    pix = new QGraphicsPixmapItem;
    QPushButton* temp2 = btn1;
    delete temp2;
    btn1 = new QPushButton;
    temp2 = btn2;
    delete temp2;
    btn2 = new QPushButton;
    temp2 = btn3;
    delete temp2;
    btn3 = new QPushButton;
    //确保内存不泄露

pix->setPixmap(QPixmap(":/img/D:/桌面/插图/游戏内交互界面.png"));
pix->setPos(QPoint(593,300));

QFont font("Arial",20,10);

btn1->resize(500,160);
btn2->resize(500,160);
btn3->resize(500,160);

btn1->move(pix->pos().x()+57,pix->pos().y()+60);
btn2->move(pix->pos().x()+57,pix->pos().y()+230);
btn3->move(pix->pos().x()+57,pix->pos().y()+400);

btn1->setFont(font);
btn2->setFont(font);
btn3->setFont(font);

mGameScene.addItem(pix);
mGameScene.addWidget(btn1);
mGameScene.addWidget(btn2);
mGameScene.addWidget(btn3);

}

void Gamecontrol::Game_stop()
{
    PlayerMoveTimer->stop();
    PlayerBulletShootTimer->stop();
    PlayerSwordTimer->stop();
    BulletMoveTimer->stop();
    EnemycreateTimer->stop();
    ElitistcreateTimer->stop();
    EnemymoveTimer->stop();
    CollisionTimer->stop();
    StatesUpdateTimer->stop();
    EliistBulletshootTimer->stop();
    TimeCountTimer->stop();
}

void Gamecontrol::Player_move()
{

    for(int keyCode: mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W:

            if(Player->_dir==Player->left)
                Player->_dir=Player->up_left;
            else if(Player->_dir==Player->right)
                Player->_dir=Player->up_right;
            else
                Player->_dir=Player->up;

            Player->moveBy(0,-1*Player->Speed);
            if(Barrior_Collison(Player))
            {
                Player->moveBy(0,1*Player->Speed);
            }
            else {
                Player->pos=QPoint(Player->pos.x(),Player->pos.y()-Player->Speed);
            }

            break;
        case Qt::Key_S:
            if(Player->_dir==Player->left)
                Player->_dir=Player->down_left;
            else if(Player->_dir==Player->right)
                Player->_dir=Player->down_right;
            else
                Player->_dir=Player->down;
            Player->moveBy(0,1*Player->Speed);
            if(Barrior_Collison(Player))
            {
                Player->moveBy(0,-1*Player->Speed);
            }
            else {
                Player->pos=QPoint(Player->pos.x(),Player->pos.y()+Player->Speed);
            }
            break;
        case Qt::Key_A:
            if(Player->_dir==Player->up)
                Player->_dir=Player->up_left;
            else if(Player->_dir==Player->down)
                Player->_dir=Player->down_left;
            else
                Player->_dir=Player->left;

            Player->sword_dir = Player->left;
            Player->moveBy(-1*Player->Speed,0);
            if(Barrior_Collison(Player))
            {
                Player->moveBy(1*Player->Speed,0);
            }
            else {
                Player->pos=QPoint(Player->pos.x()-Player->Speed,Player->pos.y());
            }
            break;
        case Qt::Key_D:
            if(Player->_dir==Player->up)
                Player->_dir=Player->up_right;
            else if(Player->_dir==Player->down)
                Player->_dir=Player->down_right;
            else
                Player->_dir=Player->right;
            Player->sword_dir = Player->right;
            Player->moveBy(1*Player->Speed,0);
            if(Barrior_Collison(Player))
            {
                Player->moveBy(-1*Player->Speed,0);
            }
            else {
                Player->pos=QPoint(Player->pos.x()+Player->Speed,Player->pos.y());
            }
            break;
        }
    }

    if(Player->x()<0)
    {
        Player->setX(0);
        Player->pos.setX(0);
    }
    if(Player->y()<0)
    {
        Player->setY(0);
        Player->pos.setY(0);
    }
    if(Player->x()>Gamedefine::gamescreenwidth-Player->pixmap().width()*Player->scale)
    {
        Player->setX(Gamedefine::gamescreenwidth-Player->pixmap().width()*Player->scale);
        Player->pos.setX(Gamedefine::gamescreenwidth-Player->pixmap().width()*Player->scale);
    }
    if(Player->y()>Gamedefine::gamescreenheight-Player->pixmap().height()*Player->scale)
    {
        Player->setY(Gamedefine::gamescreenheight-Player->pixmap().height()*Player->scale);
        Player->pos.setY(Gamedefine::gamescreenheight-Player->pixmap().height()*Player->scale);

    }
}

void Gamecontrol::Player_bullet_create()
{
    //创建子弹
    QPixmap bullet_img(":/img/D:/桌面/插图/我方子弹.png");
    int rad = Player->_dir*45;

    player_bullet* Bullet1 = (player_bullet*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_p_bullet);
    Bullet1->Init(Player->pos,bullet_img,Player->ATK,rad,Player->weapon_scale_coe);

    mGameScene.addItem(Bullet1);
    mPlayerBulletList.append(Bullet1);

    //二级强化
   if(OErecord[5]>=2)
   {

    player_bullet* Bullet2 = (player_bullet*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_p_bullet);
    Bullet2->Init(Player->pos,bullet_img,Player->ATK,rad+20,Player->weapon_scale_coe);
    player_bullet* Bullet3 = (player_bullet*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_p_bullet);
    Bullet3->Init(Player->pos,bullet_img,Player->ATK,rad-20,Player->weapon_scale_coe);

    //添加到场景
    mGameScene.addItem(Bullet2);
    mGameScene.addItem(Bullet3);

    //添加到子弹容器
    mPlayerBulletList.append(Bullet2);
    mPlayerBulletList.append(Bullet3);
   }
   //三级强化
   if(OErecord[5]>=3)
   {
       player_bullet* Bullet4 = (player_bullet*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_p_bullet);
       Bullet4->Init(Player->pos,bullet_img,Player->ATK,rad+40,Player->weapon_scale_coe);

       player_bullet* Bullet5 = (player_bullet*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_p_bullet);
       Bullet5->Init(Player->pos,bullet_img,Player->ATK,rad-40,Player->weapon_scale_coe);

       //添加到场景
       mGameScene.addItem(Bullet4);
       mGameScene.addItem(Bullet5);

       //添加到子弹容器
       mPlayerBulletList.append(Bullet4);
       mPlayerBulletList.append(Bullet5);
   }
}

void Gamecontrol::Swordcreate()
{
    QPixmap left_img(":/img/D:/桌面/插图/左刀光.png");
    QPixmap right_img(":/img/D:/桌面/插图/右刀光.png");

    //避免一次近战，重复受伤
    for(auto enemy:mEnemyList)
    {
        enemy->atk_able = true;
    }

    for(auto elitist:mElitistList)
    {
        elitist->atk_able = true;
    }

    for(auto barrior:mBarriorList)
    {
        if(barrior->_type == fragile_barrior::fra)
        {
            fragile_barrior* temp = (fragile_barrior*)barrior;
            temp->get_atk_able() = true;
        }
    }

    if(OErecord[6] >= 2)
     {
        sword* s1 = new sword(left_img,QPoint(Player->x()-left_img.width()*0.76,Player->y()),Player->ATK,Player->weapon_scale_coe,sword::left);
        mGameScene.addItem(s1);
        mPlayerSwordList.append(s1);

        sword* s2 = new sword(right_img,QPoint(Player->x()+304*0.25,Player->y()),Player->ATK,Player->weapon_scale_coe,sword::right);
        mGameScene.addItem(s2);
        mPlayerSwordList.append(s2);

        PlayerSwordRemoveTimer = new QTimer;
        PlayerSwordRemoveTimer->start(Gamedefine::PlayerSwordRemoveTime);
        connect(PlayerSwordRemoveTimer,&QTimer::timeout,[=](){
            mGameScene.removeItem(s1);
            mPlayerSwordList.removeOne(s1);
            delete s1;
            mGameScene.removeItem(s2);
            mPlayerSwordList.removeOne(s2);
            delete s2;
            delete PlayerSwordRemoveTimer;
        });
    }
    else
    {
        if(Player->sword_dir == player::left)
        {
            sword* s1 = new sword(left_img,QPoint(Player->x()-left_img.width()*0.76,Player->y()),Player->ATK,Player->weapon_scale_coe,sword::left);
            mGameScene.addItem(s1);
            mPlayerSwordList.append(s1);

            PlayerSwordRemoveTimer = new QTimer;
            PlayerSwordRemoveTimer->start(Gamedefine::PlayerSwordRemoveTime);
            connect(PlayerSwordRemoveTimer,&QTimer::timeout,[=](){
                mGameScene.removeItem(s1);
                mPlayerSwordList.removeOne(s1);
                delete s1;
                delete PlayerSwordRemoveTimer;
            });  }


        else {
            sword* s2 = new sword(right_img,QPoint(Player->x()+304*0.25,Player->y()),Player->ATK,Player->weapon_scale_coe,sword::right);
            mGameScene.addItem(s2);
            mPlayerSwordList.append(s2);
            PlayerSwordRemoveTimer = new QTimer;
            PlayerSwordRemoveTimer->start(Gamedefine::PlayerSwordRemoveTime);
            connect(PlayerSwordRemoveTimer,&QTimer::timeout,[=](){
                mGameScene.removeItem(s2);
                mPlayerSwordList.removeOne(s2);
                delete s2;
                delete PlayerSwordRemoveTimer;
            });
        }

    }

}

void Gamecontrol::Elitist_bullet_create()
{
    QPixmap bullet1(":/img/D:/桌面/插图/敌人子弹1.png");
    QPixmap bullet2(":/img/D:/桌面/插图/敌人子弹2.png");

    for (Elitist* eli : mElitistList)
    {
        if(eli->Shoot_time%4==0)
        {
            eli->Shoot_time=1;
            qDebug()<<eli->Shoot_time;

            double x = Player->x()-eli->x();
            double y = Player->y()-eli->y();
            double r = sqrt(x*x+y*y);
            double rx = x/r;
            double ry= y/r;
            double rad= atan2(ry,rx);

            elitist_bullet* eb = (elitist_bullet*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_e_bullet);
            eb->Init(eli->pos,bullet1,rad,eli->ATK);

            mGameScene.addItem(eb);
            mElitistBulletList.append(eb);
        }
        else
        {
            eli->Shoot_time++;
        }
    }



}

void Gamecontrol::enemy_create()
{
    QPixmap pixmap(":/img/D:/桌面/插图/新建文件夹/parrot.png");

    int x=0,y=0;
    int dir = qrand()%4+1;
    switch (dir) {
    case 1:x=qrand()%Gamedefine::gamescreenwidth;y=-250;break;
    case 2:y=qrand()%Gamedefine::gamescreenheight;x=-250;break;
    case 3:y=Gamedefine::gamescreenheight-0.3*pixmap.height();x=qrand()%Gamedefine::gamescreenwidth;break;
    case 4:x=Gamedefine::gamescreenwidth-0.3*pixmap.width();y=qrand()%Gamedefine::gamescreenheight;break;
    }

    enemy* Enemy = (enemy*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_enemy);
    Enemy->Init(QPoint(x,y),Time);

    mGameScene.addItem(Enemy);

    mEnemyList.append(Enemy);

}

void Gamecontrol::elitist_create()
{
    if(Time<2)return;

    QPixmap pixmap(":/img/D:/桌面/插图/新建文件夹/rabbit.png");

    int x=0,y=0;
    int dir = qrand()%4+1;
    switch (dir) {
    case 1:x=qrand()%Gamedefine::gamescreenwidth;y=-250;break;
    case 2:y=qrand()%Gamedefine::gamescreenheight;x=-250;break;
    case 3:y=Gamedefine::gamescreenheight-0.3*pixmap.height();x=qrand()%Gamedefine::gamescreenwidth;break;
    case 4:x=Gamedefine::gamescreenwidth-0.3*pixmap.width();y=qrand()%Gamedefine::gamescreenheight;break;
    }

    double ex=Player->x()-x;
    double ey=Player->y()-y;
    double r = sqrt(ex*ex+ey*ey);
    double rex = ex/r;
    double rey= ey/r;

    Elitist* elitist = (Elitist*)Gameobjectpool::Instance()->GetGameobject(Gameobject::O_elitist);
    elitist->Init(QPoint(x,y),rex,rey,Time);

    mGameScene.addItem(elitist);

    mElitistList.append(elitist);
}

void Gamecontrol::P_bullet_Collison()
{
    for(int i=0;i<mPlayerBulletList.size();i++)
    {
        for (int j=0;j<mEnemyList.size();j++)
        {
            if(mPlayerBulletList[i]->collidesWithItem(mEnemyList[j]))
            {

                mEnemyList[j]->HP-=mPlayerBulletList[i]->ATK;

                if(mEnemyList[j]->HP<=0)
                {
                    mGameScene.removeItem(mEnemyList[j]);                  
                    dead_drop(mEnemyList[j]->pos);
                    Gameobjectpool::Instance()->RecoverGameobject(mEnemyList[j]);
                    mEnemyList.removeOne(mEnemyList[j]);                    
                }
                else {                  
                    E_hurt_flicker(mEnemyList[j]);
                    //一级强化，击退
                    if(OErecord[5]>=1)
                    mEnemyList[j]->moveBy(mPlayerBulletList[i]->x_dir*20,mPlayerBulletList[i]->y_dir*20);
                }
                mGameScene.removeItem(mPlayerBulletList[i]);
                Gameobjectpool::Instance()->RecoverGameobject(mPlayerBulletList[i]);
                mPlayerBulletList.removeOne(mPlayerBulletList[i]);
                break;
            }
        }
    }
    for(int i=0;i<mPlayerBulletList.size();i++)
    {

        for (int j=0;j<mElitistList.size();j++)
        {
            if(mPlayerBulletList[i]->collidesWithItem(mElitistList[j]))
            {

                mElitistList[j]->HP-=mPlayerBulletList[i]->ATK;


                if(mElitistList[j]->HP<=0)
                {
                    mGameScene.removeItem(mElitistList[j]);
                    dead_drop(mElitistList[j]->pos);
                    Gameobjectpool::Instance()->RecoverGameobject(mElitistList[j]);
                    mElitistList.removeOne(mElitistList[j]);                    
                }
                else {
                     E_hurt_flicker(mEnemyList[j]);
                     //一级强化，击退
                     if(OErecord[5]>=1)
                    mElitistList[j]->moveBy(mPlayerBulletList[i]->x_dir*10,mPlayerBulletList[i]->y_dir*10);

                }
                mGameScene.removeItem(mPlayerBulletList[i]);
                Gameobjectpool::Instance()->RecoverGameobject(mPlayerBulletList[i]);
                mPlayerBulletList.removeOne(mPlayerBulletList[i]);
                break;
            }
        }
    }
    for(int i=0;i<mPlayerBulletList.size();i++)
    {
        for (int j=0;j<mBarriorList.size();j++)
        {
            if((mPlayerBulletList[i])->collidesWithItem(mBarriorList[j]))
            {
                if(mBarriorList[j]->_type==barrior::fra)
                {

                    fragile_barrior* temp_fra = (fragile_barrior*)mBarriorList[j];
                    Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/explore.wav"));
                    explore(temp_fra);
                    temp_fra->gethp()-=mPlayerBulletList[i]->ATK;
                    if(temp_fra->gethp()<=0)
                    {
                        mGameScene.removeItem(mBarriorList[j]);
                        mBarriorList.removeOne(mBarriorList[j]);
                    }
                }

                    mGameScene.removeItem(mPlayerBulletList[i]);
                    Gameobjectpool::Instance()->RecoverGameobject(mPlayerBulletList[i]);
                    mPlayerBulletList.removeOne(mPlayerBulletList[i]);                   
                break;
            }
        }
    }

}

void Gamecontrol::E_bullet_Collison()
{
    for(int i=0;i<mElitistBulletList.size();i++)
    {
        if(mElitistBulletList[i]->collidesWithItem(Player))
        {
            Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/explore.wav"));
            explore(mElitistBulletList[i]);
            Player->HP-=mElitistBulletList[i]->ATK;
            mGameScene.removeItem(mElitistBulletList[i]);
            Gameobjectpool::Instance()->RecoverGameobject(mElitistBulletList[i]);
            mElitistBulletList.removeOne(mElitistBulletList[i]);
        }
    }

    for(int i=0;i<mElitistBulletList.size();i++)
    {
        for (int j=0;j<mEnemyList.size();j++)
        {
            if(mElitistBulletList[i]->collidesWithItem(mEnemyList[j]))
            {
                mEnemyList[j]->HP+=mElitistBulletList[i]->ATK;
                if(mEnemyList[j]->HP>mEnemyList[j]->HPspan)
                    mEnemyList[j]->HP=mEnemyList[j]->HPspan;

                mGameScene.removeItem(mElitistBulletList[i]);
                Gameobjectpool::Instance()->RecoverGameobject(mElitistBulletList[i]);
                mElitistBulletList.removeOne(mElitistBulletList[i]);
                break;
            }
        }
    }

    for(auto e_bullet:mElitistBulletList)
    {
        for(auto barrior:mBarriorList)
        {
            if(e_bullet->collidesWithItem(barrior))
            {
                if(barrior->_type==barrior::fra)
                {
                    Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/explore.wav"));
                    fragile_barrior* temp_fra = (fragile_barrior*)barrior;
                    explore(temp_fra);
                    temp_fra->gethp()-=e_bullet->ATK;
                    if(temp_fra->gethp()<=0)
                    {
                        mGameScene.removeItem(barrior);
                        mBarriorList.removeOne(barrior);
                    }
                }             
                    mGameScene.removeItem(e_bullet);
                    Gameobjectpool::Instance()->RecoverGameobject(e_bullet);
                    mElitistBulletList.removeOne(e_bullet);

                break;
            }
        }
    }

}

void Gamecontrol::P_Sword_Collison()
{
    for(auto sword:mPlayerSwordList)
    {
        for(auto enemy:mEnemyList)
        {
            if(sword->collidesWithItem(enemy)&&enemy->atk_able == true)
            {
                enemy->HP-=sword->ATK;

                if(enemy->HP<=0)
                {
                    mGameScene.removeItem(enemy);
                    dead_drop(enemy->pos);
                    Gameobjectpool::Instance()->RecoverGameobject(enemy);
                    mEnemyList.removeOne(enemy);

                }
                else {
                    E_hurt_flicker(enemy);
                }

                enemy->atk_able = false;
                break;
            }
        }
    }

    for(auto sword:mPlayerSwordList)
    {
        for(auto elitist:mElitistList)
        {
            if(sword->collidesWithItem(elitist)&&elitist->atk_able == true)
            {

                elitist->HP-=sword->ATK;

                if(elitist->HP<=0)
                {
                    mGameScene.removeItem(elitist);
                    dead_drop(elitist->pos);
                    Gameobjectpool::Instance()->RecoverGameobject(elitist);
                    mElitistList.removeOne(elitist);                    
                }
                else {
                    E_hurt_flicker(elitist);
                }
                elitist->atk_able = false;
                break;
            }
        }
    }

    for(auto sword:mPlayerSwordList)
    {
        for(auto barrior:mBarriorList)
        {
            if((sword)->collidesWithItem(barrior))
            {
                if(barrior->_type==barrior::fra )
                {

                    fragile_barrior* temp_fra = (fragile_barrior*)barrior;
                    if(temp_fra->get_atk_able() ==true)
                    {
                        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/explore.wav"));
                        explore(barrior);
                        temp_fra->gethp()-=sword->ATK;

                        if(temp_fra->gethp()<=0)
                        {
                            mGameScene.removeItem(barrior);
                            mBarriorList.removeOne(barrior);
                        }

                    }
                    temp_fra->get_atk_able() = false;
                }
                break;
            }
        }
    }

    //三级强化
    if(OErecord[6]>=2)
    {
        for(auto sword: mPlayerSwordList)
        {
            for(auto e_bullet:mElitistBulletList)
            {
                if(sword->collidesWithItem(e_bullet))
                {
                    mGameScene.removeItem(e_bullet);
                    Gameobjectpool::Instance()->RecoverGameobject(e_bullet);
                    mElitistBulletList.removeOne(e_bullet);
                }
            }
        }
    }

}

void Gamecontrol::E_hurt_flicker(enemy* e)
{

    //敌方单位受击闪烁
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    e->setGraphicsEffect(opacityEffect);

    QPropertyAnimation *animation1 = new QPropertyAnimation( opacityEffect,"opacity");
    animation1->setStartValue(1.0);
    animation1->setEndValue(0.5);
    animation1->setDuration(250);

    QPropertyAnimation *animation2 = new QPropertyAnimation( opacityEffect,"opacity");
    animation2->setStartValue(0.5);
    animation2->setEndValue(1.0);
    animation2->setDuration(250);

    animation1->start();

    connect(animation1, &QPropertyAnimation::finished, [=]() {
        animation1->stop();
        delete animation1;
        animation2->start();

    });

    connect(animation2,&QPropertyAnimation::finished,[=](){
        animation2->stop();
        delete animation2;
        delete opacityEffect;
    });

}

void Gamecontrol::P_E_Collison()
{
    for(int i=0;i<mEnemyList.size();i++)
    {

        if(mEnemyList[i]->collidesWithItem(Player))
        {
            Player->HP-=mEnemyList[i]->ATK;
            mGameScene.removeItem(mEnemyList[i]);
            Gameobjectpool::Instance()->RecoverGameobject(mEnemyList[i]);
            mEnemyList.removeOne(mEnemyList[i]);         
        }
    }
}

void Gamecontrol::P_Exp_Collison()
{
    for(int i=0;i<mExpList.size();i++)
    {
        if(mExpList[i]->collidesWithItem(Player))
        {
            Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/Pick up.wav"));
            if(Player->level!=15)
            {
                Player->exp+=mExpList[i]->getexp();
            }
            //移除场景
            mGameScene.removeItem(mExpList[i]);
            //移除管理器
            delete mExpList[i];
            mExpList.removeOne(mExpList[i]);


        }
    }
}

void Gamecontrol::P_Med_Collison()
{
    for(int i=0;i<mMedList.size();i++)
    {
        if(mMedList[i]->collidesWithItem(Player))
        {
            Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/Pick up.wav"));
            Player->HP+=mMedList[i]->getrecover_hp();
            if(Player->HP>Player->HPspan)Player->HP=Player->HPspan;

            //移除场景
            mGameScene.removeItem(mMedList[i]);
            //移除管理器
            delete mMedList[i];
            mMedList.removeOne(mMedList[i]);


        }
    }
}

bool Gamecontrol::Barrior_Collison(Gameobject* obj)
{
    for(int i=0;i<mBarriorList.size();i++)
    {
        if(mBarriorList[i]->collidesWithItem(obj))
        {
            return true;
        }

    }
    return false;

}

void Gamecontrol::dead_drop(QPoint pos)
{
    int p=qrand()%100+1;
    Exp* exp = new Exp();
    Medicine* med = new Medicine();
    if(p%2==0)
    {
        exp->setExp(pos,QPixmap(":/img/D:/桌面/插图/经验物2.png"),5);

    }
    else if(p%3==0)
    {
        med->setMedicine(pos,QPixmap(":/img/D:/桌面/插图/烤鸡—回复生命值.png"),3);
    }
    else
    {
        exp->setExp(pos,QPixmap(":/img/D:/桌面/插图/经验物1.png"),2);

    }

//    //添加到场景
    mGameScene.addItem(exp);
    mGameScene.addItem(med);

//    //添加到经验容器
    mExpList.append(exp);
    mMedList.append(med);

}

void Gamecontrol::explore(Gameobject* obj)
{
    QLabel* label =new QLabel;
    QMovie* movie = new QMovie(":/gif/D:/桌面/插图/爆炸.gif");
    movie->setCacheMode(QMovie::CacheAll);
    label->setMovie(movie);
    label->resize(40,40);
    QSize si(label->width(),label->height());
    movie->setScaledSize(si);
    movie->setSpeed(300);
    label->move(obj->x()+8,obj->y());
    label->setAttribute(Qt::WA_TranslucentBackground, true);//设置背景为透明
    movie->start();
    //label->show();
    connect(movie,&QMovie::finished,[=](){
        label->hide();
    });
    mGameScene.addWidget(label);
}


void Gamecontrol::Add_sound(QUrl url)
{
    effect->setSource(url);
    effect->play();
}

void Gamecontrol::Draw_init()
{
    HP_rect = new QGraphicsRectItem;
    HP_line1 = new QGraphicsLineItem;
    HP_line2 = new QGraphicsLineItem;
    HP_line3 = new QGraphicsLineItem;
    HP_line4 = new QGraphicsLineItem;
    HP_line5 = new QGraphicsLineItem;

    Exp_line1 = new QGraphicsLineItem;
    Exp_line2 = new QGraphicsLineItem;
    Exp_line3 = new QGraphicsLineItem;
    Exp_line4 = new QGraphicsLineItem;
    Exp_line5 = new QGraphicsLineItem;
    Exp_rect = new QGraphicsRectItem; //400-950

    pen.setColor (Qt::red);
    pen.setWidthF (3);
    HP_rect->setPen(pen);

    HP_line1->setPen (pen);
    HP_line2->setPen (pen);
    HP_line3->setPen (pen);
    HP_line4->setPen (pen);
    HP_line5->setPen (pen);

    mGameScene.addItem(HP_rect);
    mGameScene.addItem(HP_line1);
    mGameScene.addItem(HP_line2);
    mGameScene.addItem(HP_line3);
    mGameScene.addItem(HP_line4);
    mGameScene.addItem(HP_line5);


    pen.setColor (QColor(84,221,253));
    pen.setWidthF(5);
    Exp_rect->setPen (pen);

    Exp_line1->setPen(pen);
    Exp_line2->setPen(pen);
    Exp_line3->setPen(pen);
    Exp_line4->setPen(pen);
    Exp_line5->setPen(pen);

    mGameScene.addItem(Exp_rect);
    mGameScene.addItem(Exp_line1);
    mGameScene.addItem(Exp_line2);
    mGameScene.addItem(Exp_line3);
    mGameScene.addItem(Exp_line4);
    mGameScene.addItem(Exp_line5);

}

void Gamecontrol::Draw_HP()
{


    HP_rect->setRect(Player->pos.x(),Player->pos.y()+100,85,18);
    HP_line1->setLine(Player->pos.x(),Player->pos.y()+103,Player->pos.x()+85*((double)Player->HP/(double)Player->HPspan),Player->pos.y()+103);
    HP_line2->setLine(Player->pos.x(),Player->pos.y()+106,Player->pos.x()+85*((double)Player->HP/(double)Player->HPspan),Player->pos.y()+106);
    HP_line3->setLine(Player->pos.x(),Player->pos.y()+109,Player->pos.x()+85*((double)Player->HP/(double)Player->HPspan),Player->pos.y()+109);
    HP_line4->setLine(Player->pos.x(),Player->pos.y()+112,Player->pos.x()+85*((double)Player->HP/(double)Player->HPspan),Player->pos.y()+112);
    HP_line5->setLine(Player->pos.x(),Player->pos.y()+115,Player->pos.x()+85*((double)Player->HP/(double)Player->HPspan),Player->pos.y()+115);


}

void Gamecontrol::Draw_EXP()
{
    Level->setText("等级: "+QString::number(Player->level));

    Exp_rect->setRect(350,15,600,30);
    Exp_line1->setLine(350,20,350+595*((double)Player->exp/(double)Player->level_exp[Player->level]),20);
    Exp_line2->setLine(350,25,350+595*((double)Player->exp/(double)Player->level_exp[Player->level]),25);
    Exp_line3->setLine(350,30,350+595*((double)Player->exp/(double)Player->level_exp[Player->level]),30);
    Exp_line4->setLine(350,35,350+595*((double)Player->exp/(double)Player->level_exp[Player->level]),35);
    Exp_line5->setLine(350,40,350+595*((double)Player->exp/(double)Player->level_exp[Player->level]),40);
}

void Gamecontrol::Enhance(int type)
{
    Player->LErecord[type]++;

    switch (type) {

    case 0:
    {
        Player->ATK+=Gamedefine::L_ATK_coefficient;
        break;
    }
    case 1:
    {
        Player->atk_frequrncy -= Gamedefine::L_Weapon_fre_coefficient/10;
        if(Player->type==player::panda)
        {
            PlayerBulletShootTimer->setInterval(Gamedefine::PlayerBulletShootTime*Player->atk_frequrncy);
        }
        else if (Player->type == player::penguin)
        {
            PlayerSwordTimer->setInterval(Gamedefine::PlayerSwordTime*Player->atk_frequrncy);
        }
        break;
    }
    case 2:
    {
        Player->weapon_scale_coe += Gamedefine::L_Weapon_scale_coefficient/10;
        break;
    }
    case 3:
    {
        Player->Speed+=Gamedefine::L_Speed_coefficient;
        break;
    }
    case 4:
    {
        Player->HPspan+=Gamedefine::L_HP_coefficient;
        Player->HP+=Gamedefine::L_HP_coefficient;
        break;
    }
    case 5:
    {
        Player->scale = Player->scale*(1.0 - Player->LErecord[5]*Gamedefine::L_Scale_coefficient/10);
        Player->setScale(Player->scale);
        break;
    }
    }

}

void Gamecontrol::Enhance_page_start()
{
    Game_stop();

    int btn_en1 = qrand()%6;
    while(Player->LErecord[btn_en1]==3)
    {
        btn_en1 = qrand()%6;
    }
    int btn_en2 = qrand()%6;
    while(Player->LErecord[btn_en2]==3||btn_en2==btn_en1)
    {
        btn_en2 = qrand()%6;
    }
    int btn_en3 = qrand()%6;
    while(Player->LErecord[btn_en3]==3||btn_en3==btn_en1||btn_en3==btn_en2)
    {
        btn_en3 = qrand()%6;
    }


    Page_create();

    btn1->setText(EDictionary.value(btn_en1));
    btn2->setText(EDictionary.value(btn_en2));
    btn3->setText(EDictionary.value(btn_en3));

    connect(btn1,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/uplevel.wav"));
        Enhance(btn_en1);
        Game_continue();
        pix->hide();
        btn1->hide();
        btn2->hide();
        btn3->hide();
    });
    connect(btn2,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/uplevel.wav"));
        Enhance(btn_en2);
        Game_continue();
        pix->hide();
        btn1->hide();
        btn2->hide();
        btn3->hide();
    });
    connect(btn3,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/uplevel.wav"));
        Enhance(btn_en3);
        Game_continue();
        pix->hide();
        btn1->hide();
        btn2->hide();
        btn3->hide();
    });


}

void Gamecontrol::Stop_page_start()
{
    Game_stop();

    Page_create();

    btn1->setText("结束游戏");
    btn2->setText("游戏存档");
    btn3->setText("继续游戏");

    connect(btn1,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        gameover();
        Loadoverscreen();
    });

    connect(btn2,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        write_file();
    });

    connect(btn3,&QPushButton::clicked,[=](){
        Add_sound(QUrl::fromLocalFile(":/audio/D:/桌面/音效/click.wav"));
        Game_continue();
        pix->hide();
        btn1->hide();
        btn2->hide();
        btn3->hide();
    });
}

void Gamecontrol::Game_continue()
{
    //实现局内强化

    //定时器重新启动
    TimeCountTimer ->start(Gamedefine::TimeCountTime);
    PlayerMoveTimer ->start(Gamedefine::PlayerMoveTime);

    if(Player->type==player::panda)
    {
        PlayerBulletShootTimer ->start(Gamedefine::PlayerBulletShootTime*Player->atk_frequrncy);
    }
    else if (Player->type == player::penguin)
    {
        PlayerSwordTimer->start(Gamedefine::PlayerSwordTime*Player->atk_frequrncy);
    }

    BulletMoveTimer ->start(Gamedefine::BulletMoveTime); //玩家和子弹的飞行都在这里
    EnemycreateTimer ->start(Gamedefine::EnemycreateTime);
    ElitistcreateTimer->start(Gamedefine::ElitistcreateTime);
    EliistBulletshootTimer->start(Gamedefine::EliistBulletshootTime);
    EnemymoveTimer ->start(Gamedefine::EnemymoveTime);
    CollisionTimer ->start(Gamedefine::CollisionTime);
    StatesUpdateTimer ->start(Gamedefine::StatesUpdateTime);

}

void Gamecontrol::gameover()
{
    //指针挂到对象树上了，不需要处理

    //所有定时器停止
    Game_stop();
    //容器清空并释放
    qDeleteAll(mPlayerBulletList);mPlayerBulletList.clear();
    qDeleteAll(mPlayerSwordList);mPlayerSwordList.clear();
    qDeleteAll(mElitistBulletList);mElitistBulletList.clear();
    qDeleteAll(mEnemyList);mEnemyList.clear();
    qDeleteAll(mExpList);mExpList.clear();
    qDeleteAll(mMedList);mMedList.clear();
    qDeleteAll(mElitistList);mElitistList.clear();
    qDeleteAll(mBarriorList);mBarriorList.clear();

    //局内强化记录
    Player->LErecord.clear();

}

void Gamecontrol::gameover_judge()
{
    Game_stop();

    QLabel* tip = new QLabel;
    tip->resize(Gamedefine::gamescreenwidth,200);
    tip->move(0,500);
    QFont font("Arial",30,10);
    tip->setFont(font);
    tip->setAlignment(Qt::AlignVCenter);
    tip->setAlignment(Qt::AlignCenter);
    QPalette pe;
    pe.setColor(QPalette::Background,QColor(215,10,237));
    tip->setAutoFillBackground(true);
    tip->setPalette(pe);
    tip->setText("现有返魂丹: "+QString::number(OErecord[4])+"\n"+"是否复活");

    font.setPointSize(10);
    QPushButton* btn1 = new QPushButton;
    QPushButton* btn2 = new QPushButton;

    btn1->resize(120,100);
    btn2->resize(120,100);
    btn1->setFont(font);
    btn2->setFont(font);
    btn1->setText("复活");
    btn2->setText("直接结算");

    btn1->move(400,550);
    btn2->move(1280,550);

    connect(btn2,&QPushButton::clicked,[=](){
        gameover();
        Loadoverscreen();
    });
    connect(btn1,&QPushButton::clicked,[=](){
        OErecord[4]--;
        Player->HP = Player->HPspan;
        Game_continue();
        tip->hide();
        btn1->hide();
        btn2->hide();
    });

    mGameScene.addWidget(tip);
    mGameScene.addWidget(btn1);
    mGameScene.addWidget(btn2);
}

int Gamecontrol::gameresult()
{
    coin_coe = 1.0+ OErecord[7]*Gamedefine::O_Coin_coefficient/10;
    int coin_plus = Time * coin_coe;

    coin+= coin_plus;

    Time = 0;

    return coin_plus;
}



