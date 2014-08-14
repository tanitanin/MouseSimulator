#ifndef MAZEITEM_H
#define MAZEITEM_H

#include <list>
#include <vector>

#include <QPainter>
#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>

class MazeItem : public QGraphicsItem
{
public:
    struct Wall;
    struct Cell;
public:
    MazeItem(QGraphicsItem *parent = 0);
    MazeItem(QString &filepath, QGraphicsItem *parent = 0);
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    Cell &at(unsigned int x, unsigned int y); // 左上原点
    Cell &on(unsigned int x, unsigned int y); // 左下原点
    const unsigned int width() const;
    const unsigned int height() const;
private:
    qreal cellPixel();
private:
    bool _isHalf;
    unsigned int _width;
    unsigned int _height;
    QPoint _start;
    std::list<Wall> _walls;
    std::vector<Cell> _cells;
    std::list<QPoint> _goals;
    bool isOK = false;
};

struct MazeItem::Wall {
    bool isVisible = false;
    bool isHorizontal = false;
    bool isVertical = false;
    unsigned int x = 0;
    unsigned int y = 0;
};

struct MazeItem::Cell {
    unsigned int x = 0;
    unsigned int y = 0;
    char wdata;
    bool isGoal = false;
    bool isStart = false;
    Cell *upper = nullptr;
    Cell *lower = nullptr;
    Cell *right = nullptr;
    Cell *left = nullptr;
    Wall *north = nullptr;
    Wall *east = nullptr;
    Wall *west = nullptr;
    Wall *south = nullptr;
};

#endif // MAZEITEM_H
