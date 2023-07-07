#include "drop.h"

Drop::Drop()
{

}

Drop::Drop(QPixmap _img, int _num)
{
    this->setPixmap(_img);
    num=_num;
}
