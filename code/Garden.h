#pragma once
#include<iostream>
#include "Plant.h"
#include "Store.h"
using namespace std;
class Garden :public QGraphicsItem{
public:
    Garden(){setAcceptDrops(true);}
    QRectF boundingRect() const override {return QRectF(-950, -600, 1900, 1400);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    bool add_plant(QString s, QPointF pos);
    //void display();
    void remove_plant(QPointF pos);
    int type() const override{ return 6;}
private:
    //static Cell cells[max_row][max_col];
};
