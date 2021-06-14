#ifndef SHOVEL_H
#define SHOVEL_H
#include "Plant.h"
class Shovel : public QGraphicsItem
{
public:
    QRectF boundingRect() const override { return QRectF(-60, -60, 120, 120);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
#endif // SHOVEL_H
