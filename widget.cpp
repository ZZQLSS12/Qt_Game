#include "widget.h"
#include "ui_widget.h"
#include"gamecontrol.h"

Widget* Widget::widget=nullptr;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    widget = this;
    this->setWindowTitle("幸存者游戏");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    //按下，就加入容器
    switch(event->key())
    {
        case Qt::Key_W:
        Gamecontrol::Instance()->mKeyList.append(event->key());
        break;
        case Qt::Key_S:
        Gamecontrol::Instance()->mKeyList.append(event->key());
        break;
        case Qt::Key_A:
        Gamecontrol::Instance()->mKeyList.append(event->key());
        break;
        case Qt::Key_D:
        Gamecontrol::Instance()->mKeyList.append(event->key());
        break;
    }

}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //松开，就移除
    if(Gamecontrol::Instance()->Gamecontrol::Instance()->mKeyList.contains(event->key()))
    {
        Gamecontrol::Instance()->Gamecontrol::Instance()->mKeyList.removeOne(event->key());       
    }

}




