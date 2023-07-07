#include "sword.h"


sword::sword(QPixmap _img, QPoint _pos,int atk,double scale,int dir)
{
    this->setPos(_pos);
    this->setPixmap(_img);
    this->setScale(0.8*scale);
    ATK=atk;
    _dir=dir;

    sword_sound();
}

void sword::sword_move()
{
    if(_dir==left)
    {
        this->moveBy(-1*10,0);
    }
    else {
        this->moveBy(1*10,0);
    }
}

void sword::sword_sound()
{

    effect->setSource(QUrl::fromLocalFile(":/audio/D:/桌面/音效/sword.wav"));
    effect->play();
}
