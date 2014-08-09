#include "mouseitem.h"

MouseItem::MouseItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}


QRectF MouseItem::boundingRect() const
{
    return QRect();
}

void MouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
