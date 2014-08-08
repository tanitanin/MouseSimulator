#pragma once
#ifndef MAZEITEM_H
#define MAZEITEM_H

#include <list>

#include <QGraphicsItem>
#include <QTextStream>

class MazeItem : public QGraphicsItem
{
    Q_OBJECT
public:
    struct Wall;
    struct Cell;
public:
    MazeItem();
    MazeItem(const QString &filepath);
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    bool _isHalf;
    unsigned int _width;
    unsigned int _height;
    Cell * _start;
    std::list<Wall> _walls;
    std::list<Cell> _cells;
    std::list<Cell *> _goals;
};

struct MazeItem::Wall {
    bool isVisible = false;
};

struct MazeItem::Cell {
    unsigned int x = 0;
    unsigned int y = 0;
    Wall *north = nullptr;
    Wall *east = nullptr;
    Wall *west = nullptr;
    Wall *south = nullptr;
};

#endif // MAZEITEM_H
