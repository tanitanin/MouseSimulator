#include "mazeitem.h"

MazeItem::MazeItem()
    : _isHalf(false), _width(), _height(), _walls(), _cells()
{

}

MazeItem::MazeItem(const QString &filepath)
    : _isHalf(false), _width(), _height(), _walls(), _cells()
{
    QTextStream stream(filepath);
    char c;
    stream >> c;
    qDebug("%c",c);
}


QRectF MazeItem::boundingRect() const
{
    return QRectF(QPointF(0,0),QSizeF(180*_width*(_isHalf?0.5:1.0),180*_height*(_isHalf?0.5:1.0)));
}

void MazeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
