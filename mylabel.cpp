#include "mylabel.h"
#include<QDebug>


Mylabel::Mylabel()
{
    QPixmap pix;
    pix.load(":/img/D:/桌面/插图/20230523224830.png");
    this->resize(pix.size());


    this->move(this->width()-(0.3*pix.width()),600);
//    this->setStyleSheet("background-image: url(:/img/D:/桌面/插图/20230523224830.png)");

    this->setStyleSheet("QPushButton{background:transparent;}");
    //this->setAutoFillBackground(true);
    //this->setIcon(pix);
    //this->setIconSize(QSize(pix.width(),pix.height()));
}

void Mylabel::enterEvent(QEvent *event)
{

    qDebug()<<"鼠标进入";
}
