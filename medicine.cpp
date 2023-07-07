#include "medicine.h"


Medicine::Medicine()
{

}

void Medicine::setMedicine(QPoint _pos, QPixmap _img, int num)
{
    this->setPos(_pos);
    this->setPixmap(_img);
    this->setScale(0.3);
    recover_hp=num;
}
