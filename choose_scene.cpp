#include "choose_scene.h"

Choose_scene::Choose_scene()
{
    this->addPixmap(QPixmap(":/img/D:/桌面/插图/choose.jpg"));
    Player_choose* player1 = new Player_choose(QPixmap(":/img/D:/桌面/插图/新建文件夹/panda.png"),QPoint(200,200));
    Player_choose* player2 = new Player_choose(QPixmap(":/img/D:/桌面/插图/新建文件夹/penguin.png"),QPoint(1200-200-256,200));
    this->addItem(player1);
    this->addItem(player2);


    QToolButton* p1= new QToolButton;
    p1->setText("选择熊猫");
    p1->resize(200,50);
    p1->move(250,500);

    connect(p1,&QToolButton::clicked,[=](){

        Player->type = player::panda;
        Player_init();
        Loadgamescreen();

    });

    this->addWidget(p1);

    QToolButton* p2= new QToolButton;
    p2->setText("选择企鹅");
    p2->resize(200,50);
    p2->move(784,500);

    connect(p2,&QToolButton::clicked,[=](){

        Player->type = player::penguin;
        Player_init();

        Loadgamescreen();

    });

    this->addWidget(p2);
    //添加返回按钮
    QPushButton* return_button = new QPushButton;
    return_button->setText("返回");
    return_button->resize(120,50);
    return_button->move(1000,700);
    connect(return_button,&QPushButton::clicked,[=](){
        Loadstartscreen();
    });
    this->addWidget(return_button);
}
