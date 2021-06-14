#pragma once
#include<string>
#include"Plant.h"
#include<Windows.h>
#include<iostream>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include<QDebug>
#include<QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QTimer>
using namespace std;
class Merchandise : public QGraphicsItem {
public:
    friend class Store;
    Merchandise(QString, int, int, int, clock_t);
    Merchandise();
    QString get_good_name() { return name; }
    int get_price();
    bool if_selected() { return selected; }
    clock_t get_speed() { return speed; }
    clock_t get_count() { return count; }
    void set_selected(bool flg) { selected = flg; }
    void set_count(clock_t t) { count = t; }
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    int type() const override{ return 5;}
private:
    int x, y;
    int row, col;
    QString name;
    int price;
    bool selected;
    int color;
    clock_t speed;
	clock_t count;
};
