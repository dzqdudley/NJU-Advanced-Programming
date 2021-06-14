#pragma once
#include<Windows.h>
#include<vector>
#include<iostream>
#include"Zombie.h"
#include<time.h>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include<QDebug>
#include<QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QTimer>
class Plant;
class Bullet :public QGraphicsItem{
public:
    Bullet();
    void set_loc(int x, int y, int row, int col);
	bool move(bool flg);
    //string get_type() { return type; }
	int get_row() { return row; }
	int get_col() { return col; }
	int get_attack() { return attack; }
	int get_y() { return y; }
    QRectF boundingRect() const override{return QRectF(-5, -45, 40, 40);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    int type() const override{ return 7;}
protected:
    int row, col;
    int x, y;
    int attack;
    int speed;
    clock_t counter;
    string typ;
};
class SnowBullet :public Bullet {
public:
	SnowBullet();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
class Basketball :public Bullet {
public:
    Basketball();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    void set_dst(int val){ dst=val;}
private:
    int dst;
    bool down;
    Plant* plant;
};
