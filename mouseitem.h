#ifndef MOUSEITEM_H
#define MOUSEITEM_H

#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include <QPainter>

class MouseItem : public QGraphicsItem
{
public:
    explicit MouseItem(QGraphicsItem *parent = 0);
    MouseItem(QString &filepath,QGraphicsItem *parent = 0);

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal cellPixel();
    QPointF toDisplayCood(QPointF &point);

private:
    QPointF _current;
    qreal _angle = 45.0;
    unsigned int _width = 0;
    unsigned int _height = 0;
    bool _isHalf = false;
    bool isOK = false;
};

#endif // MOUSEITEM_H
