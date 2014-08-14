#ifndef MOUSEITEM_H
#define MOUSEITEM_H

#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include <QPainter>

#include "mouseaibase.h"

class MouseItem : public QGraphicsItem
{
public:
    explicit MouseItem(QGraphicsItem *parent = 0);
    MouseItem(QString &filepath,QGraphicsItem *parent = 0);
    ~MouseItem();

public:
    enum AIMode {
        Adachi_HosuuMap,
        ExHidarite_Dijkstra,
        Astar,
    };
    void setAIMode(AIMode mode);

public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal cellPixel();
    QPointF toDisplayCood(QPointF &point);

private:
    QPointF _current;
    qreal _angle = 90.0;
    unsigned int _width = 0;
    unsigned int _height = 0;
    bool _isHalf = false;
    bool isOK = false;
    MouseAIBase *mouseai;
};

#endif // MOUSEITEM_H
