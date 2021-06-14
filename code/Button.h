#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include<QDebug>
#include<QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>

class Button : public QGraphicsItem
{
public:
    Button(QSound *sound, QString name, QTimer *timer);
    int type() const override {return 10;}
    QRectF boundingRect() const override { return QRectF(-100, -30, 200, 60);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QSound *sound;
    QTimer *timer;
    QString name;
};
#endif // BUTTON_H
