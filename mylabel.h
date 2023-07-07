#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include<QMouseEvent>
#include<QLabel>
class Mylabel : public QLabel
{
    Q_OBJECT
public:
   Mylabel();

    void enterEvent(QEvent* event);

signals:

public slots:
};

#endif // MYLABEL_H
