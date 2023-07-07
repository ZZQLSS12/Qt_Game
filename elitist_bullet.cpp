#include "elitist_bullet.h"

elitist_bullet::elitist_bullet(QPixmap img): bullet (img)
{
    this->bullet_speed = 5;
    this->get_type() = Gameobject::O_e_bullet;

}


void elitist_bullet::Init(QPoint _pos,QPixmap _img,double rad,int atk)
{
    rad=rad*180/Pi;
    QMatrix matrix;
    matrix.rotate(rad);
    this->setPixmap(_img.transformed(matrix, Qt::SmoothTransformation));
    this->setScale(0.6);
    this->bullet_speed=0;
    ATK=atk;
    this->setPos(_pos);
    x_dir = cos(rad*Pi/180);
    y_dir = sin(rad*Pi/180);
    bullet_speed = 10;
}
