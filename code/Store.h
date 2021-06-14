#pragma once
#include"Merchandise.h"
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include<QDebug>
#include<QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QTimer>
class Merchandise;
#include<vector>
extern bool rstore_efresh_need;
class Store : public QGraphicsItem{
public:
    Store();
    void purchase(QString name, QPointF pos);
    //void display(int cur_row, int cur_col);
    //void natural_sunshine();
	void add_sunshine(int val) { sunshine += val; }
    int get_sunshine(){return sunshine;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void plant_set(QString s);
    int type() const override{ return 8;}
private:
    int score;
    int sunshine;
	int speed;
    clock_t natural_sun_cnt;
    vector<Merchandise*> merchandises;
};
