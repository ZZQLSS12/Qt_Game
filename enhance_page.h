#ifndef ENHANCE_PAGE_H
#define ENHANCE_PAGE_H

#include<QGraphicsPixmapItem>
#include<QPushButton>

class Enhance_page:public QGraphicsPixmapItem
{
public:
    Enhance_page();

    QGraphicsPixmapItem* pix;

    QPushButton* btn1;
    QPushButton* btn2;
    QPushButton* btn3;

};

#endif // ENHANCE_PAGE_H
