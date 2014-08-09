#include "mouseaibase.h"

MouseAIBase::MouseAIBase() :
    _mazeWidth(0), _mazeHeight(0), _isHalf(false), _halfGoalX(0), _halfGoalY(0)
{
}

MouseAIBase::MouseAIBase(int width, int height, bool isHalf, int goalPosX, int goalPosY) :
    _mazeWidth(width), _mazeHeight(height), _isHalf(isHalf), _halfGoalX(goalPosX), _halfGoalY(goalPosY)
{
}

void MouseAIBase::setCurrentPos(double x, double y) {
    _currentX = x;
    _currentY = y;
}
