#include "Shovel.h"

void Shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-60, -60, 120, 120), QPixmap(":/images/Shovel.png"));
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

void Shovel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QMimeData *mime = new QMimeData;
    QImage image(":/images/Shovel.png");
    mime->setText("Delete");
    mime->setImageData(image);
    QDrag *drag = new QDrag(event->widget());
    drag->setPixmap(QPixmap::fromImage(image).scaled(120, 120));
    drag->setHotSpot(QPoint(60, 60));
    drag->setMimeData(mime);
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

