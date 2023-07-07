#include "player_bullet.h"

player_bullet::player_bullet(QPixmap img): bullet (img)
{
    this->bullet_speed = 20;
    this->get_type() = Gameobject::O_p_bullet;

}


void player_bullet::Init(QPoint _pos,QPixmap _img,int atk,double rad,double scale)
{
    this->setPos(_pos);
    x_dir = cos(rad/180*3.1415926);
    y_dir = sin(rad/180*3.1415926);
    QMatrix matrix;
    matrix.rotate(rad);
    this->setPixmap(_img.transformed(matrix, Qt::SmoothTransformation));
    this->setScale(0.3*scale);

    ATK=atk;

    P_bullet_sound();
}

void player_bullet::P_bullet_sound()
{
    effect->setSource(QUrl::fromLocalFile(":/audio/D:/桌面/音效/Player_bullet.wav"));
    effect->play();
}
