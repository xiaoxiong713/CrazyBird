#include "widget.h"
#include <QIcon>
#include <QPainter>
//#include <QDesktopWidget>  已经过时了，
#include <QScreen>
#include <QGuiApplication>
Widget::Widget(QWidget *parent): QWidget(parent)
{
    this->setWindowIcon(QIcon(":/img/birdIcon.ico"));

    this->adai = new Bird;
    //将鸟对象显示到窗口中
    this->adai->setParent(this);
    this->setFixedSize(this->adai->width(), this->adai->height());

    this->adai->running();

    //监听阿呆 切图的信号
    connect(this->adai, &Bird::changePix, [=](){
        update();
    });

    //监听阿呆 拖拽移动的信号
    connect(this->adai, &Bird::drag, [=](QPoint point){
       this->move(point);

        this->pos = point;//鼠标拖拽的时候更新窗口的位置

    });


    this->ttt = new QTimer(this);
    this->ttt->start(30);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();


    //获取屏幕的信息
//    QDesktopWidget * desk =  QApplication::desktop();


    connect(ttt, &QTimer::timeout, [=](){

        if(!this->adai->mouseDown)
        {
            this->pos.setX(this->pos.x() + 5);

        }

        if(this->pos.x() > screenGeometry.width())
        {
            this->pos.setX(- this->adai->width());
        }
        this->move(this->pos);
    });



    //隐藏窗口
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置透明窗体   120属性
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口在最顶层
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    //设置起始点
    this->pos.setY(screenGeometry.height() * 0.5 - this->adai->height());
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, this->adai->skin);
}

