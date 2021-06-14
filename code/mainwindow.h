#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSound>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class myscene : public QGraphicsScene{
public:
    friend class Garden;
    myscene(QObject *parent): QGraphicsScene(parent){}
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //~MainWindow();
    //paintEvent(QPaintEvent *)
    void add_zombie();
    void check_game_status();
    static bool if_end(){return end;}
private:
    Ui::MainWindow *ui;
    QSound *sound;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    clock_t add_zombie_count;
    int add_zombie_speed;
    clock_t check_cnt;
    int check_speed;
    static bool end;

};


#endif // MAINWINDOW_H
