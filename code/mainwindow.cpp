#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>
#include"Store.h"
#include"Plant.h"
#include"Garden.h"
#include"Shovel.h"
#include"Button.h"
#include<cmath>
bool MainWindow::end = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString dir=QCoreApplication ::applicationDirPath();
    add_zombie_speed=10000;
    add_zombie_count=0;
    //setFixedSize(1970,1440);
    setWindowTitle("Plant vs Zombie by Ziqian Ding");
    Store* store=new Store;
    store->setPos(0, 0);
    scene = new /*myscene*/QGraphicsScene(this);
    scene->setSceneRect(QRect(0,0,1900,1400));
    scene->addItem(store);
    Shovel *shovel = new Shovel;
    shovel->setPos(1370, 85);
    scene->addItem(shovel);
    QTimer* timer=new QTimer;
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::add_zombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check_game_status);
    sound = new QSound(dir+"/crazydave.wav");
    sound->setLoops(QSound::Infinite);
    Garden *garden = new  Garden;
    garden->setPos(950,700);
    scene->addItem(garden);
    timer->start();
    timer->setInterval(50);
    view = new QGraphicsView(scene);
    QImage pix;
    pix.load(":/images/lawn.png");
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(1910,1402);
    pix=pix.scaled(QSize(1970,1440),Qt::KeepAspectRatio);
    view->setBackgroundBrush(pix);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->show();
    sound->play();
    Button *continue_bt = new Button(sound, "continue", timer);
    continue_bt->setPos(1600+160, 40);
    scene->addItem(continue_bt);
    Button *pause_bt = new Button(sound, "locked", timer);
    pause_bt->setPos(1600+160, 120);
    scene->addItem(pause_bt);
    check_cnt = clock();
    check_speed = 1000;
    end = false;
}
void MainWindow::add_zombie()
{
    if ((int)(clock()-add_zombie_count) <= add_zombie_speed)
        return;
    add_zombie_count = clock();
    if(add_zombie_speed>4500)
        add_zombie_speed -= 300;
    int row = rand() % 10;
    if (row == 0)
        row = 1;
    else if (row > 5)
        row = 5;
    Zombie* zombie = NULL;
    int type = (rand()+3) % 6;
    switch (type)
    {
    case 0:
        zombie= new Zombie;
        break;
    case 1:
        zombie = new Conehead_Zombie;
        break;
    case 2:
        zombie = new Newspaper_Zombie;
        break;
    case 3:
        zombie = new Catapult_Zombie;
        break;
    case 4:
        zombie = new Jack_Zombie;
        break;
    case 5:
        zombie = new Pole_Zombie;
        break;
    default:
        zombie = new Zombie;
        break;
    }
    zombie->set_loc(0, 0, row-1, 9);
    zombie->setPos(1800, 50 + 220 * row);
    scene->addItem(zombie);
    return;
}
void MainWindow::check_game_status()
{
    if(end == true)
        return;
    if((int)(clock() - check_cnt) > check_speed)
    {
        check_cnt = clock();
        QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == 0 && item->x() < 50)
            {
                end = true;
                auto pix = scene->addPixmap(QPixmap(":/images/game_over.png"));
                pix->setPos(400, 200);
                pix->setZValue(3);
                pix->setScale(2);
                sound->stop();
                return;
            }
    }
}
void myscene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    QPixmap pix;
    pix.load(":/images/lawn.png");
    painter->drawPixmap(37,0,1970,1440,pix);
    pix.load(":/images/SeedBank.png");
    painter->drawPixmap(50,37,1308*0.7,261*0.7,pix);
    pix.load(":/images/SeedBank_append.png");
    painter->drawPixmap(40+1308*0.7,37,165*3*0.7,261*0.7,pix);
    pix.load(":/images/ShovelBank.png");
    painter->drawPixmap(30+1338*0.7+165*3*0.7,37,160,160,pix);
    pix.load(":/images/talk.jpg");
    painter->drawPixmap(30+1338*0.7+165*3*0.7+160,37,160,160,pix);
}

/*void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/lawn.png");
    painter.drawPixmap(37,0,1970,1440,pix);
    pix.load(":/images/SeedBank.png");
    painter.drawPixmap(50,37,1308*0.7,261*0.7,pix);
    pix.load(":/images/SeedBank_append.png");
    painter.drawPixmap(40+1308*0.7,37,165*3*0.7,261*0.7,pix);
    pix.load(":/images/ShovelBank.png");
    painter.drawPixmap(30+1338*0.7+165*3*0.7,37,160,160,pix);
    //painter.drawPixmap(50+1338*0.8+165*3*0.8+190,37,200,50,pix);
    //pix.load(":/images/continue_botton.png");
    //painter.drawPixmap(50+1338*0.8+165*3*0.8+190,37+55,200,50,pix);
    //pix.load(":/images/quit_game_botton.png");
    //painter.drawPixmap(50+1338*0.8+165*3*0.8+190,37+55+55,210,60,pix);
}*/
/*MainWindow::~MainWindow()
{
    delete ui;
}*/

