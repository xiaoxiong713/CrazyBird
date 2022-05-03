#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QMenu>
class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);

    QPixmap skin;

    int min = 1;
    int max = 8;

    //定时器
    QTimer *timer;

    void running();
    bool mouseDown;
    QMenu *myMenu;//右键菜单，实现退出

    //记录分量的坐标
    QPoint fenliang;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void changePix();
    void drag(QPoint);

};

#endif // BIRD_H
