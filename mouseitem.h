#ifndef MOUSEITEM_H
#define MOUSEITEM_H

#include <QGraphicsItem>

class MouseItem : public QGraphicsItem
{
public:
    explicit MouseItem(QGraphicsItem *parent = 0);

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MOUSEITEM_H
