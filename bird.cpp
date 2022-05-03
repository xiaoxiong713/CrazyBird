#include "bird.h"
#include <QTimer>

Bird::Bird(QWidget *parent): QWidget{parent}
{
    for (int i = 0; i < this->max; ++i)
    {
        QString str = QString(":/img/bird%1.png").arg(i + 1);
        this->skin.load(str);
    }
    this->setFixedSize(this->skin.width(), this->skin.height());

    this->timer = new QTimer(this);//指定父类， 放到对象树上， 免去了单独释放

    //监听定时器的信号
    connect(timer, &QTimer::timeout, [=](){
        QString str = QString(":/img/bird%1.png").arg(this->min ++);
        this->skin.load(str);
        if(this->min > this->max)
        {
            this->min = 1;
        }
        emit changePix();
    });

    //准备一个右键菜单
    this->myMenu =  new QMenu();
    connect(this->myMenu->addAction("退出"), &QAction::triggered, [=](){
        exit(0);
    });



}

void Bird::running()
{
    //每隔50毫秒 切一次图
    this->timer->start(50);



}

void Bird::mousePressEvent(QMouseEvent *event)
{
    //鼠标按下时候， 开始记录分量
    this->fenliang = event->globalPos() - ((QWidget *)this->parent())->frameGeometry().topLeft();

    this->mouseDown = true;


    //右键判断， 弹出菜单, 弹在鼠标的位置
    if(event->button() == Qt::RightButton)
    {
        this->myMenu->popup(QCursor::pos());
    }

    //我要是弹出了，但是没有点退出，菜单消失了，咋办？
    //菜单消失时， 会发送一个信号
    connect(this->myMenu, &QMenu::aboutToHide, [=](){
        this->mouseDown = false;
    });
}

void Bird::mouseMoveEvent(QMouseEvent *event)
{
    emit drag(event->globalPos() - this->fenliang);
}

void Bird::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseDown = false;
}














