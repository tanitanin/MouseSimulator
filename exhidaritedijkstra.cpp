#include "exhidaritedijkstra.h"

ExHidariteDijkstra::ExHidariteDijkstra(int width, int height, bool isHalf, int goalPosX, int goalPosY, QGraphicsItem *parent) :
    MouseAIBase(width,height,isHalf,goalPosX,goalPosY,this)
{
}

ExHidariteDijkstra::~ExHidariteDijkstra() {
}


void ExHidariteDijkstra::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void ExHidariteDijkstra::initialize()
{
    isOK = true;
}

void ExHidariteDijkstra::setCurrentWall(bool forward, bool right, bool left)
{
}

void ExHidariteDijkstra::nextStep(double &nextXaxis, double &nextYaxis, double &nextAngle)
{
}
