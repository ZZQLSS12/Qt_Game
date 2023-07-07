#ifndef FRAGILE_BARRIOE_H
#define FRAGILE_BARRIOE_H

#include"barrior.h"

class fragile_barrior : public barrior
{
    int barrior_hp;
    bool atk_able;
public:
    fragile_barrior(QPoint _pos, QPixmap _img,int t);

    int &gethp()
    {
        return barrior_hp;
    }

    bool& get_atk_able()
    {
        return atk_able;
    }

};

#endif // FRAGILE_BARRIOE_H
