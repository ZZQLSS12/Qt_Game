#include "enhance_page.h"

Enhance_page::Enhance_page()
{
    pix = new QGraphicsPixmapItem;
    pix->setPixmap(QPixmap(":/img/D:/桌面/插图/升级界面.png"));
    pix->setPos(QPoint(593,300));

    btn1 = new QPushButton;
    btn2 = new QPushButton;
    btn3 = new QPushButton;

    btn1->resize(500,160);
    btn2->resize(500,160);
    btn3->resize(500,160);

    btn1->move(pix->pos().x()+57,pix->pos().y()+60);
    btn2->move(pix->pos().x()+57,pix->pos().y()+230);
    btn3->move(pix->pos().x()+57,pix->pos().y()+400);

}
