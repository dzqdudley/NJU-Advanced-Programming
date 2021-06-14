#pragma once
#include<Windows.h>
#include<iostream>
#include<time.h>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include<QDebug>
#include<QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QTimer>
#include<cstring>
#include<QLine>
using namespace std;
//extern bool garden_refresh_need;
class Zombie : public QGraphicsItem {//Zombie
public:
	Zombie();
	Zombie(int x, int y);
    virtual ~Zombie(){delete mov;}
	int get_cur_hp();
	//设置位置
	void set_loc(int x, int y, int row, int col);
	//Zombie移动
    //virtual bool move();
	//Zombie被攻击后减少血量
	virtual void get_hit(int val);
	//篮球计数减小
	virtual void decrease_cnt() {};
	//返回剩余篮球数
	virtual int get_ball_cnt() { return 0; };
	//返回篮球伤害
	virtual int get_ball_attack() { return 0; };
	//返回Zombie名称
	virtual const string get_name() { return "Zombie"; }
	//返回是否有撑杆
	virtual bool is_pole() { return false; }
	//设置被减速
    void set_slowed();
	//返回颜色类型
	int get_colortype() { return colortype; }
	//伤害
	int get_attack() { return attack; }
	//是否被挡住
	bool if_blocked() { return is_blocked; }
	//遮挡是否可越过
	bool is_skippable() { return skippable; }
	//是否被挡住
	void set_is_blocked(bool b) { is_blocked = b; }
	//遮挡是否可越过
	void set_skippable(bool b) { skippable = b; }
	//攻击计数
	clock_t get_atk_count() { return atk_count; }
	//攻击速度
	int get_atk_speed() { return atk_speed; }
	//攻击计数
	void set_atk_count(clock_t t) { atk_count = t; }
	//设置当前血量
	void set_cur_hp(int val) { cur_hp = val; }
	int get_row() { return row; }
	int get_col() { return col; }
	int get_x() { return x; }
	int get_y() { return y; }
	void set_row(int row) { this->row = row; }
	void set_y(int y) { this->y = y; }
    int type() const override {return 0;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    void setMov(QString path);
protected:
	//位置，地块下标
	int row, col;
	//位置，全局坐标
	int x, y;
	//当前血量
	int cur_hp;
	//满血量
	int hp;
	//移动速度
	int speed;
	//秒伤
	int attack;
	//是否被挡住
	bool is_blocked;
	//遮挡是否可越过
	bool skippable;
	//移动计数
	clock_t counter;
	//攻击计数
	clock_t atk_count;
	//攻击速度
	int atk_speed;
	//颜色
	int color;
	//是否爆炸
	bool explode;
	//前方是否有植物
	bool plant_infront;
	//是否被减速
	bool slowed;
	//被减速的时间
	clock_t slowed_time;
	//颜色类型
    int colortype;
    QMovie* mov;
    bool exploded;
    bool change_line;
    int change_cnt;
    int each_change;
};

class Conehead_Zombie : public Zombie {
public:
    Conehead_Zombie();
    const string get_name() { return "Conehead_Zombie"; }
};

class Newspaper_Zombie : public Zombie {
public:
    Newspaper_Zombie();
	void get_hit(int val);
    const string get_name() { return "Newspaper_Zombie"; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
private:
	int newspaper;
    bool shift;
    bool add_speed;
};

class Pole_Zombie : public Zombie {
public:
    Pole_Zombie();
	bool move();
	const string get_name() { return "Pole_Zombie"; }
	bool is_pole() { return pole; }
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
	bool pole;
    bool flying;
    bool fly_over;
    clock_t fly_cnt;
    int fly_speed;
    bool walk;
};

class Jack_Zombie : public Zombie {
public:
    Jack_Zombie();
	bool move();
	const string get_name() { return "Jack_Zombie"; }
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
	clock_t explode_cnt;
	clock_t explode_speed;
    clock_t after_cnt;
    clock_t after_speed;
    QList<QGraphicsItem *> plants;
};

class Catapult_Zombie :public Zombie {
public:
    Catapult_Zombie();
	bool move();
	//篮球计数减小
	void decrease_cnt() { ball_cnt--; };
	//返回剩余篮球数
	int get_ball_cnt() { return ball_cnt;};
	//返回篮球伤害
    //int get_ball_attack();
	const string get_name() { return "Catapult_Zombie"; }
    void advance(int phase);
    QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	//剩余篮球数量
	int ball_cnt;
	//篮球攻击力
	int ball_attack;
	//篮球攻击计数
	clock_t ball_atk_cnt;
	clock_t ball_atk_speed;
    bool before;
    bool after;
};
