#include"Merchandise.h"
Merchandise::Merchandise()
{
	name = "";
	price = row = col = x = y = 0;
	selected = false;
}
int Merchandise::get_price()
{
    return price;
}
Merchandise::Merchandise(QString name, int price, int row, int col, clock_t cnt)
{
	this->row = row;
	this->col = col;
	x = col * cell_length;
	y = row * cell_height;
	selected = false;
	this->name = name;
    this->price = price;
	this->speed = cnt;
	this->count = 0;
}
QRectF Merchandise::boundingRect() const
{
    return QRectF(0, 0, 107, 150);
}

void Merchandise::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    //输出图片
    painter->drawPixmap(QRect(0, 0, 80, 70), QPixmap(":/images/plants/" + name + ".png"));
    //冷却时间
    float time = (float)((int)clock() - (int)count) / (float)speed;
    if (time < 1)
    {
        painter->setBrush(QBrush(QColor(0, 0, 0, 100)));
        painter->drawRect(QRectF(-13, -30, 107, 150*(1-time)));
    }
    //价格
    QFont font;
    font.setPointSizeF(12);
    painter->setFont(font);
    painter->drawText(8, 112, QString().sprintf("%d", price));
}

void Merchandise::advance(int phase)
{
    if (!phase)
        return;
    update();
}

void Merchandise::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    event->setAccepted(true);
    float time = (float)((int)clock() - (int)count) / (float)speed;
    if (time < 1)
        event->setAccepted(false);
    Store *store = qgraphicsitem_cast<Store *>(parentItem());
    if (price > store->get_sunshine())
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);
}

void Merchandise::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QMimeData *mime = new QMimeData;
    QString path=":/images/plants/" + name + ".png";
    QImage image(path);
    mime->setText(name);
    mime->setImageData(image);
    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Merchandise::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
