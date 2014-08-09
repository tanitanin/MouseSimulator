#include "mouseitem.h"

MouseItem::MouseItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

MouseItem::MouseItem(QString &filepath, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int i; stream >> i;
    _isHalf = (i>0 ? true : false);
    stream >> i; _width = i;
    stream >> i; _height = i;
    int half_gx, half_gy;
    if(_isHalf) stream >> half_gx >> half_gy;
    file.close();
    _current = QPointF(cellPixel()/2,cellPixel()/2);
    _angle = 90.0;
    isOK = true;
}

qreal MouseItem::cellPixel() {
    return 18.0 * (_isHalf ? 0.5 : 1.0);
}

QPointF MouseItem::toDisplayCood(QPointF &point) {
    return QPointF(point.x(), _height*cellPixel() - point.y());
}

QRectF MouseItem::boundingRect() const
{
    return QRectF(0,0,413,429);
}

void MouseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isOK) {
        const qreal roffset = cellPixel()/2.0;
        const qreal toffset = cellPixel()/2.0;
        const QPointF offset(roffset,toffset);

        painter->scale(boundingRect().width()/(_width+1)/cellPixel(),
                       boundingRect().width()/(_width+1)/cellPixel());
        // 機体
        QPointF pf = toDisplayCood(_current) + offset;
        const qreal co = cos(_angle/180.0*3.1415926);
        const qreal si = sin(_angle/180.0*3.1415926);
        const qreal top = 7.0;
        //const qreal tail = 10.0;
        const qreal side = 90.0;
        QPainterPath path(pf+QPointF(top*co,-top*si));
        path.lineTo(pf+QPointF(side*co+side*si,-side*si+side*co));
        path.lineTo(pf+QPointF(-side*co+side*si,side*si+side*co));
        path.lineTo(pf+QPointF(-side*co-side*si,side*si-side*co));
        path.lineTo(pf+QPointF(side*co-side*si,-side*si-side*co));
        path.lineTo(pf+QPointF(top*co,-top*si));
        painter->fillPath(path,QBrush(QColor(100,100,100)));
        qDebug("ok");
    }
}
