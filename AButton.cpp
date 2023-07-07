#include "Abutton.h"

AButton::AButton(int button_type)
{
   QPixmap pix;

    if(button_type== start_button)
    {
        pix.load(":/img/D:/桌面/插图/开始按钮.png");
        this->move(700,500);

    }
    else if(button_type == store_button)
    {
        pix.load(":/img/D:/桌面/插图/商店按钮.png");
        this->move(50,600);
    }
    else if(button_type == record_read_button)
    {
        pix.load(":/img/D:/桌面/插图/读档按钮.png");
        this->move(700,620);

    }
    this->resize(pix.size());
    this->setIcon(pix);
    this->setIconSize(pix.size());
    this->setMask(pix.mask());


    this->setStyleSheet("QPushButton{background:transparent;}");


}
