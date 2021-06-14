#include"Bullet.h"
#include"Zombie.h"
#include"Plant.h"
#include"mainwindow.h"
Bullet::Bullet()
{
	x = y = 0;
	col=row = 0;
	attack = 50;
    speed = 10;
	counter = clock();
    typ = "Ordinary";
}
SnowBullet::SnowBullet()
{
	x = y = 0;
	col = row = 0;
	attack = 50;
    speed = 10;
	counter = clock();
    typ = "Snow";
}
Basketball::Basketball()
{
    x = y = 0;
    col = row = 0;
    attack = 50;
    speed = 10;
    counter = clock();
    down = false;
    plant=0;
}
void Bullet::set_loc(int x, int y, int row, int col)
{
	this->x = x;
	this->y = y;
	this->row =row;
	this->col = col;
}
void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    painter->drawPixmap(QRect(-5, -45, 40, 40), QPixmap(":/images/images/Pea.png"));
}
void SnowBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    painter->drawPixmap(QRect(-5, -45, 40, 40), QPixmap(":/images/images/PeaSnow.png"));
}
void Basketball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    painter->drawPixmap(QRect(-5, -45, 40, 40), QPixmap(":/images/images/Basketball.png"));
}

bool Bullet::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() != 0)
        return false;
    if(qAbs(other->x() - (pos().x()-50)) > 50)
        return false;
    return (row+1) == ((other->y() - 50)/220);
}

bool Basketball::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() > -1|| other->type() == -5)
        return false;
    if(qAbs(other->x() - (pos().x()-50)) > 15)
        return false;
    int num = (other->y() - 50)/220;
    return row + 1 == num;
}

void Bullet::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[0]);
        zombie->get_hit(get_attack());
        if (this->typ == "Snow")
            zombie->set_slowed();
        delete this;
        return;
    }
    setX(pos().x() + 12);
    if (pos().x() > 1950)
        delete this;
}

void Basketball::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(pos().x() <= dst)
    {
        if(plant)
            plant->plant_atked(attack);//to be finished
        delete this;
        return;
    }
    QList<QGraphicsItem *> plants = collidingItems();
    if (!plants.isEmpty())
    {
        foreach (QGraphicsItem *item, plants)
        {
            plant = qgraphicsitem_cast<Plant *>(item);
            if(plant->x()==dst)
                down=true;
        }
    }
    setX(pos().x() - 12);
    if(down)
        setY(pos().y() + 4);
    if (pos().x() < 100)
        delete this;
}

