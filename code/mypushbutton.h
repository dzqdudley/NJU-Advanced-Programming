#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //pressImg is the path of img after pressing the button
    MyPushButton(QString normalImgPath, QString  pressImgPath="");
    MyPushButton(int w, int h, QString normalImgPath, QString  pressImgPath="");
    void bounce_down();
    void bounce_up();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QString normalImgPath;
    QString pressImgPath;

signals:

};

#endif // MYPUSHBUTTON_H
