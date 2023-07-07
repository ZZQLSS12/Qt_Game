#include "bullet.h"

void bullet::bulletmove()
{
    double r=sqrt(x_dir*x_dir+y_dir*y_dir);
    double rex=x_dir/r;
    double rey = y_dir/r;
    this->moveBy(rex*bullet_speed,rey*bullet_speed);

}

bullet::bullet(QPixmap _img)
{
    this->setPixmap(_img);
}


