#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>




//元素--场景--视图
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    //按键事件
   void keyPressEvent(QKeyEvent* event);
   void keyReleaseEvent(QKeyEvent* event);


   static Widget* widget;

private:
    Ui::Widget *ui;



};

#endif // WIDGET_H
