#include"Plant.h"
#include"mainwindow.h"
const string Plant:: get_name()
{
	return name;
}
int Plant::get_cur_hp()
{
	return cur_hp;
}
void Plant::set_loc(int row, int col)
{
	this->row = row;
	this->col = col;
}
void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    painter->drawImage(boundingRect(), mov->currentImage());
}
void Squash::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    if(explode && !exploded)
    {
        exploded = true;
        setMov(":/images/images/Boom.gif");
    }
    painter->drawImage(boundingRect(), mov->currentImage());
}
void Cherrybomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    if(explode && !exploded)
    {
        exploded = true;
        setMov(":/images/images/Boom.gif");
    }
    painter->drawImage(boundingRect(), mov->currentImage());
}
QRectF Squash::boundingRect() const
{
    if(explode)
        return QRectF(-150, -150, 300, 300);
    else
        return QRectF(-60, -60, 120, 120);
}
QRectF Cherrybomb::boundingRect() const
{
    if(exploded)
        return QRectF(-300, -300, 600, 600);
    else
        return QRectF(-60, -60, 120, 120);
}
bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() != 0)
        return false;
    if(-pos().x() + (other->x()-30) > 15 || -pos().x() + (other->x()) < -100)
        return false;
    int row_=((other->y() - 50)/220);
    return row + 1 == row_;
}
void Plant::plant_atked(int val)
{
    cur_hp-=val;
}
void Plant::setMov(QString path)
{
    if (mov)
        delete mov;
    mov = new QMovie(path);
    mov->start();
}

Sunflower::Sunflower()
{
	name = string("Sunflower");
	row = col = 0;
	cur_hp = 500;
    hp = 500;
    speed = 4000;
    counter = clock();
    setMov(":/images/images/SunFlower.gif");
}
PeaArcher::PeaArcher()
{
	name = string("PeaArcher");
	row = col = 0;
	cur_hp = 500;
    hp = 500;
    speed = 2500;
    counter = clock();
    setMov(":/images/images/Peashooter.gif");
}
Repeater::Repeater()
{
	name = string("Repeater");
	this->row = 0;
	this->col = 0;
	cur_hp = 500;
    hp = 500;
    speed = 3000;
	counter1 = clock();
    counter2 = clock() + 200;
    setMov(":/images/images/Repeater.gif");
}
SnowPea::SnowPea()
{
	name = string("SnowPea");
	this->row = 0;
	this->col = 0;
	cur_hp = 500;
    hp = 500;
    speed = 3000;
    counter = clock();
    setMov(":/images/images/SnowPea.gif");
}
Wallnut::Wallnut()
{
	name = string("Wallnut");
	row = col = 0;
	cur_hp = 3000;
    hp = 3000;
    setMov(":/images/images/WallNut.gif");
}
Tallnut::Tallnut()
{
	name = string("Tallnut");
	row = col = 0;
	cur_hp = 3000;
    hp = 3000;
    setMov(":/images/images/TallNut.gif");
}
Squash::Squash()
{
	name = string("Squash");
	row = col = 0;
	cur_hp = 8000;
    hp = 500;
    explode = false;
    exploded = false;
    after_cnt = clock();
    after_speed = 1000;
    setMov(":/images/images/PotatoMine.gif");
}
Cherrybomb::Cherrybomb()
{
	name = string("Cherrybomb");
	row = col = 0;
	cur_hp = 500;
    hp = 500;
    speed = 1000;
    counter = clock();
    explode = false;
    exploded = false;
    after_cnt = clock();
    after_speed = 1000;
    setMov(":/images/images/CherryBomb.gif");
}
Garlic::Garlic()
{
	name = string("Garlic");
	row = col = 0;
	cur_hp = 1000;
    hp = 1000;
    setMov(":/images/images/Gralic.gif");
}
Pumpkin::Pumpkin()
{
    //setZValue(0);
    name = string("Pumpkin");
    row = col = 0;
    cur_hp = 1000;
    hp = 1000;
    setMov(":/images/images/PumpkinHead.gif");
}
void Sunflower::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
    if ((int)(clock() - counter) >= speed)
    {
        //Game::store.add_sunshine(25);
        scene()->addItem(new Sunshine(pos()));
        counter = clock();
    }
}
void PeaArcher::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
	if ((int)(clock() - counter) >= speed)
	{
        //if (!collidingItems().isEmpty())
        {
            Bullet *bullet = new Bullet;
            bullet->set_loc(0, 0, row, col);
            bullet->setX(x() + 60);
            bullet->setY(y());
            scene()->addItem(bullet);
        }
			counter = clock();
	}
}
void Repeater::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
	if ((int)(clock() - counter1) >= speed)
    {
       // if (!collidingItems().isEmpty())
        {
            Bullet *bullet = new Bullet;
            bullet->set_loc(0, 0, row, col);
            bullet->setX(x() + 60);
            bullet->setY(y());
            scene()->addItem(bullet);
        }
			counter1 = clock();
	}
	if ((int)(clock() - counter2) >= speed && (int)(clock() - counter1) > 200)
	{
        //if (!collidingItems().isEmpty())
        {
            Bullet *bullet = new Bullet;
            bullet->set_loc(0, 0, row, col);
            bullet->setX(x() + 60);
            bullet->setY(y());
            scene()->addItem(bullet);
        }
			counter2 = clock();
	}
}
void SnowPea::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
	if ((int)(clock() - counter) >= speed)
	{
        //if (!collidingItems().isEmpty())
        {
            Bullet *bullet = new SnowBullet;
            bullet->set_loc(0, 0, row, col);
            bullet->setX(x() + 60);
            bullet->setY(y());
            scene()->addItem(bullet);
        }
            counter = clock();
	}
}
void Wallnut::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
}
void Tallnut::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
}
void Squash::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
    if(explode)
    {
        if((int)(clock()- after_cnt) >= after_speed)
        {
            delete this;
            return;
        }
        else
            return;
    }
    QList<QGraphicsItem *> near_zombies = collidingItems();
    if (!near_zombies.isEmpty())
    {
        explode=true;
        foreach (QGraphicsItem *item, near_zombies)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->get_hit(5000);
        }
        after_cnt=clock();
    }
	
}
bool Cherrybomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() != 0)
        return false;
    int dist = (pos().x() - other->pos().x())*(pos().x() - other->pos().x())+
            (pos().y()-other->pos().y())*(pos().y()-other->pos().y());
    return dist < 850*900;
}
void Cherrybomb::advance(int phase)
{
    if (!phase)//phase=0, about to move;phase=1,now move
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
    if(explode)
    {
        if((int)(clock()- after_cnt) >= after_speed)
        {
            delete this;
            return;
        }
        else
            return;
    }
    QList<QGraphicsItem *> near_zombies = collidingItems();
	if ((int)(clock() - counter) >= speed)
	{
        explode = true;
        if (!near_zombies.isEmpty())
        {
            foreach (QGraphicsItem *item, near_zombies)
            {
                Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
                zombie->get_hit(5000);
            }  
        }
        after_cnt=clock();
	}
	
}
/*void Cherrybomb::clear_zombie(int ro, int co, Game& game)
{
	if (row == 0 || row >= max_row || col < 0 || col >= max_col - 1)
		return;
	if (game.cell_has_zombie(ro, co))
	{
		game.cherrybomb_function(ro, co);
	}
	game.cell_set_plant_explode(ro, co, true);
	game.cell_set_has_zombie(ro, co, false);
}*/
void Garlic::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        //Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[qrand() % items.size()]);
        //garlic function
        return;
    }
    /*if (game.cell_has_zombie(row, col))
	{
		game.garlic_function(row, col);
    }*/
}
Sunshine::Sunshine(QPointF pos)
{
    dst = QPointF(pos.x()+300, pos.y()+300);
    setPos(QPointF(pos.x(), pos.y()));
    picked=false;
    mov = new QMovie(":/images/images/Sun.gif");
    mov->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}
QRectF Sunshine::boundingRect() const
{
    return QRectF(0, 0, 120, 120);
}

void Sunshine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    painter->drawImage(QRectF(0, 0, 120, 120), mov->currentImage());
}

void Sunshine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    Store *store = qgraphicsitem_cast<Store *>(scene()->items(QPointF(300, 15))[0]);
    store->add_sunshine(25);
    picked=true;
    event->setAccepted(true);
}

void Sunshine::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if (picked)
        delete this;
    else if (dst.y()>y()&&y()<=1300)
        setY(y() + 3);
}
void Pumpkin::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if(cur_hp<=0)
    {
        delete this;
        return;
    }
}
