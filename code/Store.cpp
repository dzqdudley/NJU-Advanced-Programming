#include"Store.h"
#include"cmath"
#include"Plant.h"
#include"Merchandise.h"
#include"mainwindow.h"
Store::Store()
{
	score = 0;
    sunshine = 500;
    speed = 7000;
    natural_sun_cnt=clock();
    Merchandise* merc = new Merchandise("Sunflower", 50,0,1,3000);
    merchandises.push_back(merc);
    merc = new Merchandise("Peashooter", 100,0,2,5000);
    merchandises.push_back(merc);
    merc = new Merchandise("Repeater", 200, 0, 3, 8000);
    merchandises.push_back(merc);
    merc = new Merchandise("Snowpea", 150, 0, 4, 6000);
    merchandises.push_back(merc);
    merc = new Merchandise("Wallnut", 200, 0, 5, 6000);
    merchandises.push_back(merc);
    merc = new Merchandise("Tallnut", 250, 0, 6, 8000);
    merchandises.push_back(merc);
    merc = new Merchandise("Squash", 200, 0, 7, 7000);
    merchandises.push_back(merc);
    merc = new Merchandise("Cherrybomb", 300, 0, 8, 10000);
    merchandises.push_back(merc);
    merc = new Merchandise("Garlic", 100, 0, 9, 5000);
    merchandises.push_back(merc);
    merc = new Merchandise("Pumpkin", 200, 0, 10, 7000);
    merchandises.push_back(merc);
    merc->setParentItem(this);
    for (int i = 0; i < (int)merchandises.size(); i++)
    {
        merchandises[i]->setParentItem(this);
        merchandises[i]->setPos(180+107 * i, 50);
    }
}
QRectF Store::boundingRect() const
{
    return QRectF(-641, -80, 1338*0.7+165*3*0.7+100,180);
}

void Store::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPixmap pix;
    pix.load(":/images/SeedBank.png");
    painter->drawPixmap(0,5,1308*0.7,261*0.7,pix);
    pix.load(":/images/SeedBank_append.png");
    painter->drawPixmap(1308*0.7,5,165*3*0.7,261*0.7,pix);
    pix.load(":/images/ShovelBank.png");
    painter->drawPixmap(10+1338*0.7+165*3*0.7,5,160,160,pix);
    pix.load(":/images/talk.jpg");
    painter->drawPixmap(30+1338*0.7+165*3*0.7+160,5,160,100,pix);
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(QRectF(0, 0, 150, 312), Qt::AlignCenter, QString::number(sunshine));
    painter->drawText(QRectF(0, 0, 3100, 140),
                      Qt::AlignCenter, QString::number(score));
    painter->drawPoint(0, 0);
}

void Store::advance(int phase)
{
    if (!phase)
        return;
    if(MainWindow::if_end() == true)
        return;
    update();
    if ((int)(clock()-natural_sun_cnt) >= speed)
    {
        score += 5;
        scene()->addItem(new Sunshine(QPointF(x()+200,y()+200)));
        natural_sun_cnt = clock();
    }
}
void Store::plant_set(QString s)
{
    //int i;
    QList<QGraphicsItem *> children = childItems();
    foreach (QGraphicsItem *child, children)
    {
        Merchandise *merc = qgraphicsitem_cast<Merchandise *>(child);
        if (merc->get_good_name()==s)
        {
            sunshine-=merc->get_price();
            merc->set_count(clock());
        }
    }
   /*if((int)merchandises.size()==0)
       return;
   for (i = 0; i < (int)merchandises.size(); i++)
    {
        if(merchandises[i]->get_price()//()==s
                )
            break;
    }
    sunshine-=merchandises[i]->get_price();
    merchandises[i]->set_count(clock());*/
}
/*
void Store::display(int cur_row, int cur_col)
{
	set_coord(4,  cell_height / 2-1);
	color_cout("Store",store_color);
	set_coord(4, cell_height / 2);
	color_cout("Sunshine",Sunflower_color);
	set_coord(5, cell_height / 2 + 1);
	std::cout << "   ";
	set_coord(5, cell_height / 2 + 1);
	std::cout << sunshine;
	set_coord(4, cell_height / 2 + 2);
	color_cout("Score", store_color);
	set_coord(5, cell_height / 2 + 3);
	std::cout << score;
	for (int i = 0; i < (int)merchandises.size(); i++)
	{
		if (merchandises[i].row == cur_row && merchandises[i].col == cur_col//merchandises[i].selected
			)//被选中，输出小方框
		{
			string horizon(cell_length - 1, '-');
			set_coord(merchandises[i].x+1, merchandises[i].y+1);
			std::cout << horizon;
			set_coord(merchandises[i].x+1, merchandises[i].y + cell_height);
			std::cout << horizon;
			for (int j = 2; j < cell_height; j++)
			{
				set_coord(merchandises[i].x+1, merchandises[i].y + j);
				std::cout << '|';
				set_coord(merchandises[i].x + cell_length - 1, merchandises[i].y + j);
				std::cout << '|';
			}
		}
		else//覆盖掉原来的边框
		{
				string horizon(cell_length - 1, ' ');
				set_coord(merchandises[i].x + 1, merchandises[i].y + 1);
				std::cout << horizon;
				set_coord(merchandises[i].x + 1, merchandises[i].y + cell_height);
				std::cout << horizon;
				for (int j = 2; j < cell_height; j++)
				{
					set_coord(merchandises[i].x + 1, merchandises[i].y + j);
					std::cout << ' ';
					set_coord(merchandises[i].x + cell_length - 1, merchandises[i].y + j);
					std::cout << ' ';
				}
		}
		set_coord(merchandises[i].x + 2, merchandises[i].y + cell_height / 2);
		color_cout(merchandises[i].name, merchandises[i].color);
		set_coord(merchandises[i].x + 2, merchandises[i].y + cell_height / 2 + 1);
		std::cout << "Price:"<<merchandises[i].price;
		set_coord(merchandises[i].x + 2, merchandises[i].y + cell_height / 2 + 2);
		float time = (float)((int)clock() - (int)merchandises[i].count) / (float)merchandises[i].speed;
		std::cout << "     ";
		set_coord(merchandises[i].x + 2, merchandises[i].y + cell_height / 2 + 2);
		if (merchandises[i].count == 0 || time > 1)
			std::cout << "100%";
		else
			std::cout << floor(100 * time) << "%";
	}
}*/
/*void Store::purchase(QString name, QPointF pos)
{
    Plant* plant=0;
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
        if (item->type() == -1)
            return;//to be finished
    int i;
    for (i = 0; i < (int)merchandises.size(); i++)
        if (merchandises[i]->get_good_name()==name)
            break;
    sunshine = sunshine - merchandises[i]->get_price();
    if (name == "Sunflower")
        plant = new Sunflower;
    else if (name == "PeaArcher")
        plant = new PeaArcher;
    else if (name == "Repeater")
        plant = new Repeater;
    else if (name == "SnowPea")
        plant = new SnowPea;
    else if (name == "Wallnut")
        plant = new Wallnut;
    else if (name == "Tallnut")
        plant = new Tallnut;
    else if (name == "Squash")
        plant = new Squash;
    else if (name == "Cherrybomb")
        plant = new Cherrybomb;
    else if (name == "Garlic")
        plant = new Garlic;
    else if (name == "Pumpkin")
        plant = new Pumpkin;
    plant->setPos(pos);
    scene()->addItem(plant);
    QList<QGraphicsItem *> children = childItems();
    foreach (QGraphicsItem *child, children)
    {
        Merchandise *merc = qgraphicsitem_cast<Merchandise *>(child);
        if (merc->get_good_name()==name)
            merc->count = 0;
    }

    for (int i = 0; i < (int)merchandises.size(); i++)
		if (merchandises[i].name == name)
		{
			//sunshine = sunshine - merchandises[i].price;
			merchandises[i].selected = true;
			store_refresh_need = true;
		}
		else 
		{
			merchandises[i].selected = false;
        }
}*/
 /*void Store::natural_sunshine()
 {
	 if ((int)(clock()-natural_sun_cnt) >= speed)
	 {
		 sunshine += 25;
		 score += 5;
		 store_refresh_need = true;
		 natural_sun_cnt = clock();
	 }
 }*/
