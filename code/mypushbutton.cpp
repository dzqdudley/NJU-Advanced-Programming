#include "mypushbutton.h"
#include<QPropertyAnimation>
/*MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}*/
MyPushButton::MyPushButton(QString normalImg, QString  pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        exit(-1);
    }
    //keep the size fixed
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QpushButton{border:0px;}");
    this->setIcon((pix));
    this->setIconSize(QSize(pix.width(),pix.height()));
}
MyPushButton::MyPushButton(int w, int h, QString normalImg, QString  pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        exit(-1);
    }
    //keep the size fixed
    this->setFixedSize(w,h);
    //设置不规则图片样式
    this->setStyleSheet("QpushButton{border:0px;}");
    this->setIcon((pix));
    this->setIconSize(QSize(w, h));

}
void MyPushButton::bounce_down()
{
    QPropertyAnimation* animat=new QPropertyAnimation(this,"geometry");
    animat->setDuration(200);
    animat->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animat->setEndValue(QRect(this->x(),this->y()+4,this->width(),this->height()));
    //弹跳曲线
    animat->setEasingCurve(QEasingCurve::OutBounce);
    animat->start();
}
void MyPushButton::bounce_up()
{
    QPropertyAnimation* animat=new QPropertyAnimation(this,"geometry");
    animat->setDuration(200);
    animat->setStartValue(QRect(this->x(),this->y()+4,this->width(),this->height()));
    animat->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //弹跳曲线
    animat->setEasingCurve(QEasingCurve::OutBounce);
    animat->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")//需要切图
    {
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret)
        {
            exit(-1);
        }
        //keep the size fixed
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QpushButton{border:0px;}");
        this->setIcon((pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);//continue
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")//需要切图
    {
        QPixmap pix;
        bool ret = pix.load(normalImgPath);//换回去
        if(!ret)
        {
            exit(-1);
        }
        //keep the size fixed
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QpushButton{border:0px;}");
        this->setIcon((pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);//continue
}
