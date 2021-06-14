#pragma once
#include<string>
#include<time.h>
#include"Bullet.h"
#include"Store.h"
#include"Zombie.h"
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include<QDebug>
#include<QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QTimer>
using namespace std;
#define cell_length 12
#define cell_height 5
class Plant : public QGraphicsItem{
public:
    Plant(){mov=0;setZValue(1);}
	int get_cur_hp();
    const string get_name();
    void set_loc(int row, int col);
    QRectF boundingRect() const override{ return QRectF(-60, -60, 120, 120);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override{ return -1;}//plant
    void setMov(QString path);
    void plant_atked(int val);
    virtual ~Plant(){ delete mov;}
protected:
    string name;
    int row, col;
    int cur_hp;
    int hp;
    //int color_type;
    QMovie* mov;
};
class Sunflower : public Plant {//Sunflower
public:
	friend class Store;
	Sunflower();
    //产生阳光
    void advance(int phase) override;
private:
	//产生阳光的速度
	int speed;
	//产生阳光计数
	clock_t counter;
};
class PeaArcher :public Plant {//PeaArcher
public:
	PeaArcher();
    //发射子弹
    void advance(int phase) override;
private:
	//发射子弹的速度
	int speed;
	//发射子弹计数
	clock_t counter;
};
class Repeater :public Plant {//Repeater
public:
	Repeater();
    //发射子弹
    void advance(int phase) override;
private:
	//发射子弹的速度
	int speed;
	//发射子弹计数
	clock_t counter1;
	clock_t counter2;
};
class SnowPea :public Plant {//SnowPea
public:
	SnowPea();
    //发射子弹
    void advance(int phase) override;
private:
	//发射子弹的速度
	int speed;
	//发射子弹计数
	clock_t counter;
};
class Wallnut :public Plant {//Wallnut
public:
	Wallnut();
    void advance(int phase) override;
};
class Tallnut :public Plant {//Tallnut
public:
	Tallnut();
    void advance(int phase) override;
    int type() const override{return -2;}//tallnut
    QRectF boundingRect() const override{return QRectF(-60, -100, 120, 160);}
};
class Squash :public Plant {//Squash
public:
	Squash();
    //遇到Zombie就爆炸
    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    bool explode;
    bool exploded;
    clock_t after_cnt;
    clock_t after_speed;
};
class Cherrybomb :public Plant {//Cherrybomb
public:
	Cherrybomb();
    //种下后立即爆炸
    //void clear_zombie(int row, int col, Game &game);
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
	int speed;
	clock_t counter;
    bool explode;
    bool exploded;
    clock_t after_cnt;
    clock_t after_speed;
};
class Garlic :public Plant {//Garlic
public:
    Garlic();
    void advance(int phase) override;
    int type() const override{return -3;}//tallnut
};
class Pumpkin :public Plant {//pumpkin
public:
    Pumpkin();
    QRectF boundingRect() const override{return QRectF(-60, 0, 120, 100);}
    void advance(int phase) override;
    int type() const override{return -4;}//tallnut
};
class Sunshine :public Plant{
public:
    Sunshine(QPointF pos);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
    int type() const override{return -5;}//tallnut
private:
    QPointF dst;
    bool picked;
};
