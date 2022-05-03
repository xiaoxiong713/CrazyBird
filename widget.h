#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "bird.h"
#include <QTimer>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    Bird *adai;

    void paintEvent(QPaintEvent *event);

    //记录自动移动的位置
    QPoint pos;

    //自动移动的定时器
    QTimer *ttt;

};
#endif // WIDGET_H
