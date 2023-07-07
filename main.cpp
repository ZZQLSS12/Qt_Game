#include "widget.h"
#include <QApplication>
#include"gamecontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    Gamecontrol::Instance()->gameinit();
    w.show();

    //游戏加载

    return a.exec();
}
