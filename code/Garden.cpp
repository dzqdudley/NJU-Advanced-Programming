#include"Garden.h"
#include"Shovel.h"
void Garden:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
void Garden::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
        update();
    }
    else
        event->setAccepted(false);
}

void Garden::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    update();
}

void Garden::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        QString s = event->mimeData()->text();
        QPointF pos = mapToScene(event->pos());
        if (s == "Delete")
            remove_plant(pos);
        else
        {
            if(add_plant(s,pos))
            {
                Store *store = qgraphicsitem_cast<Store *>(scene()->items(QPointF(10,10))[0]);
                store->plant_set(s);
            }
        }
    }
    update();
}
bool Garden::add_plant(QString name, QPointF pos)
{
    Plant* plant=0;
    pos.setX(160+195*(int(pos.x())/210));
    pos.setY(280+240*(int(pos.y()-180)/240));
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
    {
        if (name != "Pumpkin"&&item->type() == -1)//has plant here already
            return false;
        if (name == "Pumpkin"&&item->type() == -4)//has pumpkin here already
            return false;
    }
    if (name == "Pumpkin")
        plant = new Pumpkin;
    if (name == "Sunflower")
        plant = new Sunflower;
    else if (name == "Peashooter")
        plant = new PeaArcher;
    else if (name == "Repeater")
        plant = new Repeater;
    else if (name == "Snowpea")
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
    plant->set_loc(int(pos.y()-180)/240, int(pos.x())/210);
    plant->setPos(pos);
    if(name == "Pumpkin")
        plant->setX(plant->pos().x()+5);
    scene()->addItem(plant);
    return true;
}
void Garden::remove_plant(QPointF pos)
{
    pos.setX(160+195*(int(pos.x())/210));
    pos.setY(280+240*(int(pos.y()-180)/240));
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
        if (item->type() <= -1)
            delete item;
}
/*void Garden::init()
{
	for (int i = 1; i < max_row; i++)
		for (int j = 0; j < max_col; j++)
			cells[i][j].set_loc(i, j);
}

void Garden::display()//显示边界
{
	string garden_len(cell_length * max_col+1, '#');
	for (int i = 0; i <= max_row; i++)//行边界
	{
		set_coord(0, i * (cell_height + 1));
		std::cout << garden_len;
	}
	for (int i = 0; i < max_row; i++)//列边界
		for (int k = 0; k < max_col; k++)
		{
			for (int j = 1; j <= cell_height; j++)
			{
				set_coord((cell_length)*k, (cell_height + 1) * i + j);
				//if (j == 2 || j == 3)
				//	continue;//	std::cout << " ";
				//else
					std::cout << '#';
			}
		}
}

void Garden::refresh(int cur_row, int cur_col)//刷新屏幕
{
	for (int i = 1; i < max_row; i++)
		for (int j = max_col - 1; j >= 0; j--)//从右向左刷新
		{
			if (cells[i][j].if_refresh_need() || cells[i][j].if_explode() || cells[i][j].if_plant_explode())
				cells[i][j].refresh(cur_row, cur_col);
			else if (cells[i][j].get_explode_time() != 0 && (int)(clock() - cells[i][j].get_explode_time()) > 1000)
			{
				cells[i][j].refresh(cur_row, cur_col);
				cells[i][j].explode_time = 0;
			}
		}
}
void Garden::set_explode(int row, int col)
{
	cell_explode(row - 1, col - 1);
	cell_explode(row - 1, col);
	cell_explode(row - 1, col + 1);
	cell_explode(row, col - 1);
	cell_explode(row, col);
	cell_explode(row, col + 1);
	cell_explode(row + 1, col - 1);
	cell_explode(row + 1, col);
	cell_explode(row + 1, col + 1);
}
void Garden::cell_explode(int row, int col)
{
	if (row == 0 || row >= max_row || col < 0 || col > max_col - 1)
		return;
	cells[row][col].explode = true;
}
void Garden::plant_function(Game& game)
{
	for (int i = 1; i < max_row; i++)
		for (int j = 0; j < max_col - 1; j++)
			if (cells[i][j].has_plant())
				cells[i][j].plant->function(game);
}
string Garden::get_cell_plant_name(int row, int col)
{
	return cells[row][col].plant->get_name();
}
//植物掉血
void Garden::plant_minus_hp(int row, int col, int val)
{
	cells[row][col].plant->cur_hp -= val;
}
//植物血量
int Garden::get_cur_hp(int row, int col)
{
	return cells[row][col].plant->cur_hp;
}
//是否有Zombie
bool Garden::if_zombie(int row, int col)
{
	return cells[row][col].has_zombie();
}*/
