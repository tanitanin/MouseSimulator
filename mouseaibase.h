#ifndef MOUSEAIBASE_H
#define MOUSEAIBASE_H

#include <QGraphicsItem>

class MouseAIBase : QGraphicsItem
{
public:

public:
    explicit MouseAIBase(int width, int height, bool isHalf, int goalPosX=0, int goalPosY=0, QGraphicsItem *parent=0);
    ~MouseAIBase();
private:
    explicit MouseAIBase(QGraphicsItem *parent=0);
public:
    void setCurrentPos(double x, double y);
public:
    virtual void initialize() = 0;
    virtual void setCurrentWall(bool forward, bool right, bool left) = 0;
    virtual void nextStep(double &nextX, double &nextY, double &nextAngle) = 0;
public:
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
private:
    const int _mazeWidth;
    const int _mazeHeight;
    const bool _isHalf;
    const int _halfGoalX;
    const int _halfGoalY;
    int _currentX; // マス位置
    int _currentY; // マス位置
    double _currentXaxis; // 連続座標
    double _currentYaxis; // 連続座標
    double _currentAngle; // 度
    union {
        char _wallCharUnion;
        struct {
            bool _currentWallForward : 1;
            bool _currentWallRight : 1;
            bool _currentWallLeft : 1;
        };
    };
    bool isOK = false;
};

#endif // MOUSEAIBASE_H
