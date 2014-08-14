#include "mouseaibase.h"

MouseAIBase::MouseAIBase(QGraphicsItem *parent) :
    QGraphicsItem(parent), _mazeWidth(0), _mazeHeight(0), _isHalf(false), _halfGoalX(0), _halfGoalY(0)
{
}

MouseAIBase::MouseAIBase(int width, int height, bool isHalf, int goalPosX, int goalPosY, QGraphicsItem *parent) :
    QGraphicsItem(parent), _mazeWidth(width), _mazeHeight(height), _isHalf(isHalf), _halfGoalX(goalPosX), _halfGoalY(goalPosY)
{
}

MouseAIBase::~MouseAIBase() {

}

QRectF MouseAIBase::boundingRect() const {
    return QRectF(0,0,400,400);
}

void MouseAIBase::setCurrentPos(double x, double y) {
    _currentX = x;
    _currentY = y;
}
