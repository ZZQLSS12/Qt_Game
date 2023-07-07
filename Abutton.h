#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QObject>
#include<QPushButton>
#include<QBitmap>

class AButton:public QPushButton
{
public:
    AButton(int);

    enum type{
        start_button,
        store_button,
        record_read_button
    };

};

#endif // STARTBUTTON_H
