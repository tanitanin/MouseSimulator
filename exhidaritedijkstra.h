#ifndef EXHIDARITEDIJKSTRA_H
#define EXHIDARITEDIJKSTRA_H

#include "mouseaibase.h"


class ExHidariteDijkstra : public MouseAIBase
{
public:
    ExHidariteDijkstra(int width, int height, bool isHalf, int goalPosX=0, int goalPosY=0, QGraphicsItem *parent=0);
    ~ExHidariteDijkstra();

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // MouseAIBase interface
public:
    void initialize();
    void setCurrentWall(bool forward, bool right, bool left);
    void nextStep(double &nextX, double &nextY, double &nextAngle);
};

#endif // EXHIDARITEDIJKSTRA_H
