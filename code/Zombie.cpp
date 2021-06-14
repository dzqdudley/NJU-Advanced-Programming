#include"Zombie.h"
#include"Plant.h"
#include<QImage>
#include"mainwindow.h"
Zombie::Zombie()
{
    setZValue(2);
    x=y=0;
	row = col = 0;
    cur_hp = 450;
    hp = 150;
    speed = 2;
    attack = 100;
	counter = atk_count = 0;
	atk_speed = 1000;
	is_blocked = false;
    skippable = true;
	explode = false;
	plant_infront = false;
	slowed = false;
    slowed_time = 0;
    mov=NULL;
    setMov(":/images/images/NormalZombieWalk.gif");
    exploded=false;
    change_line = false;
    change_cnt = 220;
}
Zombie::Zombie(int x, int y)
{
	this->x = x;
	this->y = y;//位置
	row = col = 0;
    cur_hp = 450;//当前血量
	hp = 150;//满血量
    speed = 2;//移动速度
	attack = 100;//伤害
	counter = atk_count = 0;
	atk_speed = 1000;
	is_blocked = false;
    skippable = true;
	explode = false;
	slowed = false;
    slowed_time = 0;
    mov=NULL;
    exploded=false;
    setMov(":/images/images/NormalZombieWalk.gif");
}
void Zombie::set_slowed()
{
    if(!slowed)
        slowed = true;
    else
        slowed_time = clock();
}
QRectF Zombie::boundingRect() const
{
    return QRectF(-125, -125, 250, 250);
}
QRectF Newspaper_Zombie::boundingRect() const
{
    return QRectF(-50, -100, 300, 250);
}
QRectF Catapult_Zombie::boundingRect() const
{
    return QRectF(-50, -75, 250, 250);
}
QRectF Pole_Zombie::boundingRect() const
{
    if(walk)
        return QRectF(-175, -175, 450, 350);
    else
        return QRectF(-150, -150, 300, 300);
}
QRectF Jack_Zombie::boundingRect() const
{
    if(exploded)
        return QRectF(-400, -400, 800, 800);
    else
        return QRectF(-150, -150, 300, 300);
}
void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    QImage img = mov->currentImage();
    if (slowed)
    {
        int w = img.width();
        int h = img.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = img.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 150;
        }
    }
    painter->drawImage(boundingRect(), img);
}
void Newspaper_Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    if(newspaper <= 0 && shift == false)
    {
        shift = true;
        setMov(":/images/images/Newspaper_wo.gif");
    }
    QImage img = mov->currentImage();
    if (slowed)
    {
        int w = img.width();
        int h = img.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = img.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 150;
        }
    }
    painter->drawImage(boundingRect(), img);
}
void Catapult_Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    if(before == false && pos().x()<1400 )
    {
        setMov(":/images/images/CatapultZombie.gif");
        before = true;
    }
    else if(ball_cnt <= 0 && !after)
    {
        after = true;
        setMov(":/images/images/CatapultZombieNoBall.gif");
    }
    QImage img = mov->currentImage();
    if (slowed)
    {
        int w = img.width();
        int h = img.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = img.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 150;
        }
    }
    painter->drawImage(boundingRect(), img);
}
void Pole_Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(MainWindow::if_end() == true)
        return;
    if(fly_over == false && flying&&(int)(clock()-fly_cnt) > fly_speed)
    {
        fly_over = true;
        flying = false;
    }
    if(pole==false && fly_over == true)
    {
        setMov(":/images/images/PoleVaultingZombiieWalk.gif");
        fly_over=false;
        walk = true;
    }
    QImage img = mov->currentImage();
    if (slowed)
    {
        int w = img.width();
        int h = img.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = img.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 150;
        }
    }
    painter->drawImage(boundingRect(), img);
}
void Jack_Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QImage img = mov->currentImage();
    if (slowed)
    {
        int w = img.width();
        int h = img.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = img.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 150;
        }
    }
    painter->drawImage(boundingRect(), img);
}
void Zombie::setMov(QString path)
{
    if (mov)
        delete mov;
    mov = new QMovie(path);
    mov->start();
}
bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() > -1|| other->type() == -5)
        return false;
    if( -other->x() + (pos().x()-30) > 15 || -other->x() + (pos().x()-30) < -20)
        return false;
    int num=int(other->y()-180)/240;
    return row == num;
}
bool Jack_Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    if(other->type() > -1|| other->type() == -5)
        return false;
    int dist = (pos().x() - other->pos().x())*(pos().x() - other->pos().x())+
            (pos().y()-other->pos().y())*(pos().y()-other->pos().y());
    return dist < 850*900;
}
Conehead_Zombie::Conehead_Zombie()
{
	cur_hp = 300;
    setMov(":/images/images/ConeZombieWalk.gif");
}
Newspaper_Zombie::Newspaper_Zombie()
{
    newspaper = 200;
    setMov(":/images/images/Newspaper_w.gif");
    shift=false;
    add_speed = false;
}
Pole_Zombie::Pole_Zombie()
{
	pole = true;
    flying = false;
    fly_over = false;
    walk = false;
    fly_cnt=0;
    fly_speed=1400;
    setMov(":/images/images/PoleVaultingZombie.gif");
}
Jack_Zombie::Jack_Zombie()
{
	explode_cnt = clock();
    explode_speed = 10000;
    after_cnt = clock();
    after_speed = 1000;
    setMov(":/images/images/JackZombie.gif");
}
Catapult_Zombie::Catapult_Zombie()
{
    atk_speed = 3000;
    ball_cnt = 10;
	ball_attack = 20;
    attack = 5000;
	ball_atk_cnt = 0;
	ball_atk_speed = 3000;
    speed = 10;
    before=after=false;
    setMov(":/images/images/CatapultZombieNoBall.gif");
}
void Zombie::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if (slowed && slowed_time == 0)
    {
        slowed_time = clock();
        speed = speed / 2;
        atk_speed = atk_speed / 2;

    }
    if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 8000)
    {
        slowed_time = 0;
        slowed = false;
        speed = speed * 2;
        atk_speed *= 2;
    }
    if (cur_hp <= 0)
    {
        delete this;
        return;
    }
    QList<QGraphicsItem *> plants = collidingItems();
    if (!plants.isEmpty() && (int)(clock()- atk_count) >= atk_speed)
    {
        is_blocked=true;
        if(plants[0]->type()==-3)//garlic
        {
            change_line=true;
           is_blocked = false;
        }
        Plant *plant = qgraphicsitem_cast<Plant *>(plants[0]);
        plant->plant_atked(attack);//to be finished
        atk_count=clock();
    }
    else if(plants.isEmpty())
        is_blocked=false;
    if (is_blocked)//被挡住了就不动了
        return;
    if(change_line)
    {
        if(change_cnt==0)
        {
            change_cnt=220;
            change_line=false;
        }
        else
        {
            if(change_cnt==220)
            {
                if(row == 4)
                {
                    row--;
                    change_cnt=-change_cnt;
                }
                else
                    row++;
                each_change=change_cnt/10;
            }
            setY(pos().y()+each_change);
            change_cnt-=each_change;
        }
    }
    setX(pos().x() - speed);
    counter = clock();
}
void Newspaper_Zombie::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if (slowed && slowed_time == 0)
    {
        slowed_time = clock();
        speed = speed / 2;
        atk_speed = atk_speed / 2;

    }
    if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 8000)
    {
        slowed_time = 0;
        slowed = false;
        speed = speed * 2;
        atk_speed *= 2;
    }
    if (cur_hp <= 0)
    {
        delete this;
        return;
    }
    if(add_speed == false && newspaper <= 0)
    {
        add_speed = true;
        speed *= 2.8;
    }
    QList<QGraphicsItem *> plants = collidingItems();
    if (!plants.isEmpty() && (int)(clock()- atk_count) >= atk_speed)
    {
        is_blocked=true;
        if(plants[0]->type()==-3)//garlic
        {
            change_line=true;
           is_blocked = false;
        }
        Plant *plant = qgraphicsitem_cast<Plant *>(plants[0]);
        plant->plant_atked(attack);//to be finished
        atk_count=clock();
    }
    else if(plants.isEmpty())
        is_blocked=false;
    if (is_blocked)//被挡住了就不动了
        return;
    if(change_line)
    {
        if(change_cnt==0)
        {
            change_cnt=220;
            change_line=false;
        }
        else
        {
            if(change_cnt==220)
            {
                if(row == 4)
                {
                    row--;
                    change_cnt=-change_cnt;
                }
                else
                    row++;
                each_change=change_cnt/10;
            }
            setY(pos().y()+each_change);
            change_cnt-=each_change;
        }
    }
    setX(pos().x() - speed);
    counter = clock();
}
int Zombie::get_cur_hp()
{
	return cur_hp;
}
void Zombie::set_loc(int x, int y, int row, int col)
{
	this->row = row;
	this->col = col;
	this->x = x+3;
	this->y = y;
	counter = clock();
}

/*bool Zombie::move()
{
	if (slowed && slowed_time == 0)
	{
		slowed_time = clock();
		speed *= 2;
		atk_speed *= 2;
		colortype = Slowedzombie_color;
	}//被减速
	if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 10000)
	{
		slowed_time = 0;
		slowed = false;
		speed = speed / 2;
		atk_speed = atk_speed / 2;
		colortype = Zombie_color;
	}//解除减速
	if (is_blocked||(int)(clock()-counter)<speed)//被挡住了就不动了
		return false;
		x -= length;
		col = x / length;
		counter = clock();
		return true;
}*/
void Pole_Zombie::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if (slowed && slowed_time == 0)
    {
        slowed_time = clock();
        speed = speed / 2;
        atk_speed = atk_speed / 2;

    }
    if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 8000)
    {
        slowed_time = 0;
        slowed = false;
        speed = speed * 2;
        atk_speed *= 2;
    }
    if (cur_hp <= 0)
    {
        delete this;
        return;
    }
    QList<QGraphicsItem *> plants = collidingItems();
    if (!plants.isEmpty())
     {
        is_blocked=true;
        Plant *plant = qgraphicsitem_cast<Plant *>(plants[0]);
        if (is_blocked && pole && plant->type()!=-2)//有杆且可跳过，则跳过
        {
            flying=true;
            fly_cnt=clock();
            setMov(":/images/images/PoleVaultingZombieJump.gif");
            //setX(pos().x() - 195);//to be modified
            counter = clock();
            pole = false;
            is_blocked = false;
            return;
        }
    }
    if (!plants.isEmpty() && (int)(clock()- atk_count) >= atk_speed)
    {
        if(plants[0]->type()==-3)//garlic
        {
            change_line=true;
           is_blocked = false;
        }
        Plant *plant = qgraphicsitem_cast<Plant *>(plants[0]);
        plant->plant_atked(attack);//to be finished
        atk_count=clock();
    }
    else if(plants.isEmpty())
        is_blocked=false;
    if(flying)
        is_blocked = false;
    if (is_blocked||(int)(clock()-counter)<speed)//被挡住了就不动了
        return;
    if(flying)
        setX(pos().x() - 10);
    else
        setX(pos().x() - speed);
    if(change_line)
    {
        if(change_cnt==0)
        {
            change_cnt=220;
            change_line=false;
        }
        else
        {
            if(change_cnt==220)
            {
                if(row == 4)
                {
                    row--;
                    change_cnt=-change_cnt;
                }
                else
                    row++;
                each_change=change_cnt/10;
            }
            setY(pos().y()+each_change);
            change_cnt-=each_change;
        }
    }
    counter = clock();
}
/*bool Pole_Zombie::move()
{
	if (slowed && slowed_time == 0)
	{
		slowed_time = clock();
		speed *= 2;
		atk_speed *= 2;
	}//被减速
	if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 10000)
	{
		slowed_time = 0;
		slowed = false;
		speed = speed / 2;
		atk_speed = atk_speed / 2;
	}//解除减速
	if (is_blocked && pole && skippable)//有杆且可跳过，则跳过
	{
		x -= length;
		col = x / length;
		counter = clock();
		pole = false;
		is_blocked = false;
		return true;
	}
	else if (is_blocked || (int)(clock() - counter) < speed)//被挡住了就不动了
		return false;
	x -= length;
	col = x / length;
	counter = clock();
	return true;
}*/
void Jack_Zombie::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if (slowed && slowed_time == 0)
    {
        slowed_time = clock();
        speed = speed / 2;
        atk_speed = atk_speed / 2;

    }
    if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 8000)
    {
        slowed_time = 0;
        slowed = false;
        speed = speed * 2;
        atk_speed *= 2;
    }
    if (cur_hp <= 0)
    {
        delete this;
        return;
    }
    if(explode)
    {
        if((int)(clock()- after_cnt) >= after_speed)
        {
            foreach (QGraphicsItem *plant, plants)
            {
                Plant *plt = qgraphicsitem_cast<Plant *>(plant);
                plt->plant_atked(20000);
            }
            delete this;
            return;
        }
        else
            return;
    }
    plants = collidingItems();
    int k = rand();
    if ((int)(clock() - explode_cnt) > explode_speed && (!plants.isEmpty() ||
    (explode == false && k % 17 == 0 && pos().x() < 1900 - rand()%500)))
    {
        explode = true;
        after_cnt=clock();
        return;
    }
    else if(plants.isEmpty())
        is_blocked=false;
    if (is_blocked)//被挡住了就不动了
        return;
    if(change_line)
    {
        if(change_cnt==0)
        {
            change_cnt=220;
            change_line=false;
        }
        else
        {
            if(change_cnt==220)
            {
                if(row == 4)
                {
                    row--;
                    change_cnt=-change_cnt;
                }
                else
                    row++;
                each_change=change_cnt/10;
            }
            setY(pos().y()+each_change);
            change_cnt-=each_change;
        }
    }
    setX(pos().x() - speed);
    counter = clock();
}
void Catapult_Zombie::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if (slowed && slowed_time == 0)
    {
        slowed_time = clock();
        speed = speed / 2;
        atk_speed = atk_speed / 2;

    }
    if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 8000)
    {
        slowed_time = 0;
        slowed = false;
        speed = speed * 2;
        atk_speed *= 2;
    }
    if (cur_hp <= 0)
    {
        delete this;
        return;
    }
    QList<QGraphicsItem *> plants = scene()->items();
    if (pos().x()<1400 && ball_cnt > 0 && !plants.isEmpty() && (int)(clock()- atk_count) >= atk_speed)
    {
        Plant *inner=0;
        int min=2000;
        foreach (QGraphicsItem *other, plants)
        {
            if(other->type() > -1|| other->type() == -5)
                continue;
            int num=int(other->y()-180)/240;
            if(row != num)
                continue;
            Plant *plant = qgraphicsitem_cast<Plant *>(other);
            if(plant->x()<min)
            {
                inner=plant;
                min=plant->x();
            }

        }
        Basketball *bullet=new Basketball;
        bullet->set_dst(min);
        bullet->set_loc(0, 0, row, col);
        bullet->setX(pos().x() + 60);
        bullet->setY(pos().y());
        scene()->addItem(bullet);
        ball_cnt--;
        atk_count = clock();
    }
    if (ball_cnt > 0 || plants.isEmpty())
        is_blocked = true;
    if (ball_cnt <= 0 || !plants.isEmpty())
        is_blocked = false;
    plants = collidingItems();
    if (!plants.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant *>(plants[0]);
        plant->plant_atked(attack);//to be finished
        atk_count=clock();
    }
    if (pos().x()>1400)
        is_blocked = false;
    if(is_blocked==false)
    {
        setX(pos().x() - 1);
        return;
    }
    if ((int)(clock()-counter) < speed)//被挡住了就不动了
        return;
    setX(pos().x() - speed);
    counter = clock();
    return;
}
void Zombie::get_hit(int val)
{
    this->cur_hp -= val;
}
void Newspaper_Zombie::get_hit(int val)
{
    if (newspaper > val)
        newspaper -= val;
    else
    {
        this->cur_hp -= val;
        newspaper = 0;
    }
}
/*bool Jack_Zombie::move()
{
    if (slowed && slowed_time == 0)
    {
        slowed_time = clock();
        speed *= 2;
        atk_speed *= 2;
        colortype = Slowedzombie_color;
    }//被减速
    if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 10000)
    {
        slowed_time = 0;
        slowed = false;
        speed = speed / 2;
        atk_speed = atk_speed / 2;
        colortype = Zombie_color;
    }//解除减速
    int k = rand();
    if ((int)(clock() - explode_cnt) > explode_speed)
    {
        if (col != 10 && explode == false && k % 17 == 0)
        {
            explode = true;
            cur_hp = 0;
            return false;
        }
        explode_cnt = clock();
    }
    if (is_blocked || (int)(clock() - counter) < speed)//被挡住了就不动了
        return false;
    x -= length;
    col = x / length;
    counter = clock();
    return true;
}*/
/*bool Catapult_Zombie::move()
{
	if (slowed && slowed_time == 0)
	{
		slowed_time = clock();
		speed *= 2;
		atk_speed *= 2;
		ball_atk_speed *= 2;
		colortype = Slowedzombie_color;
	}//被减速
	if (slowed && slowed_time != 0 && (int)(clock() - slowed_time) > 10000)
	{
		slowed_time = 0;
		slowed = false;
		speed = speed / 2;
		atk_speed = atk_speed / 2;
		colortype = Zombie_color;
		ball_atk_speed = ball_atk_speed / 2;
	}//解除减速
	if (ball_cnt > 0 || plant_infront)
		is_blocked = true;
	if (ball_cnt <= 0 || plant_infront == false)
		is_blocked = false;
    if (col > 12 - 3)
		is_blocked = false;
	if (is_blocked || (int)(clock() - counter) < speed)//被挡住了就不动了
		return false;
	x -= length;
	col = x / length;
	counter = clock();
	return true;
}*/
/*void Zombie::display()
{
	if (slowed)
		colortype = Slowedzombie_color;
	else
		colortype = Zombie_color;
	set_coord(x, y + row + height / 2);
	color_cout("Zombie", colortype);
	set_coord(x, y + row + height / 2 + 1);
	std::cout << "HP:" << get_cur_hp();
}
void Conehead_Zombie::display()
{
	if (slowed)
		colortype = Slowedzombie_color;
	else
		colortype = Zombie_color;
	set_coord(x, y + row + height / 2);
	color_cout("Conehead_Zombie", colortype);
	set_coord(x, y + row + height / 2 + 1);
	std::cout << "HP:" << get_cur_hp();
}
void Newspaper_Zombie::display()
{
	if (slowed)
		colortype = Slowedzombie_color;
	else
		colortype = Zombie_color;
	set_coord(x, y + row + height / 2);
	color_cout("Newspaper_Zombie", colortype);
	set_coord(x, y + row + height / 2 + 1);
	if (newspaper > 0)
		color_cout("HAS PAPER", colortype);
	else
		color_cout("NO PAPER", colortype);
	set_coord(x, y + row + height / 2 + 2);
	std::cout << "HP:" << get_cur_hp();
}
void Pole_Zombie::display()
{
	if (slowed)
		colortype = Slowedzombie_color;
	else
		colortype = Zombie_color;
	set_coord(x, y + row + height / 2);
	color_cout("Pole_Zombie", colortype);
	set_coord(x, y + row + height / 2 + 1);
	if (pole)
		color_cout("HAS POLE", colortype);
	else
		color_cout("NO POLE", colortype);
	set_coord(x, y + row + height / 2 + 2);
	std::cout << "HP:" << get_cur_hp();
}
void Jack_Zombie::display()
{
	if (slowed)
		colortype = Slowedzombie_color;
	else
		colortype = Zombie_color;
	set_coord(x, y + row + height / 2);
	color_cout("Jack_Zombie", colortype);
	set_coord(x, y + row + height / 2 + 1);
	if (explode)
		color_cout("Boom", colortype);
	else
		color_cout("NOT BOOMED", colortype);
	set_coord(x, y + row + height / 2 + 2);
	std::cout << "HP:" << get_cur_hp();
}
void Catapult_Zombie::display()
{
	if (slowed)
		colortype = Slowedzombie_color;
	else
		colortype = Zombie_color;
	set_coord(x, y + row + height / 2);
	color_cout("Catapult_Zombie", colortype);
	set_coord(x, y + row + height / 2 + 1);
	if (ball_cnt > 0)
	{
		color_cout("HAS BALL", colortype);
	}
	else
		color_cout("NO BALL", colortype);
	set_coord(x, y + row + height / 2 + 2);
	std::cout << "HP:" << get_cur_hp();
}*/
/*int Catapult_Zombie::get_ball_attack()
{ 
	if ((int)(clock() - ball_atk_cnt) >= ball_atk_speed)
	{
		ball_atk_cnt = clock();
		return ball_attack;
	}
	return 0;
}*/
