#include "Button.h"
Button::Button(QSound *sound, QString name, QTimer *timer)
{
    this->sound = sound;
    this->timer = timer;
    this->name = name;

}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-100, -30, 200, 60), QPixmap(":/images/" + name +".png"));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(name == "locked")
        {
            if (timer->isActive())
            {
                sound->stop();
                timer->stop();
            }

        }
        else if(name == "continue")
        {
            if (!timer->isActive())
            {
                sound->play();
                timer->start();
            }
        }
    }
    update();
}
