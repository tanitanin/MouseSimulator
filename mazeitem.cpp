#include "mazeitem.h"

MazeItem::MazeItem(QGraphicsItem *parent)
    : QGraphicsItem(parent), _isHalf(false), _width(), _height(), _walls(), _cells()
{

}

MazeItem::MazeItem(QString &filepath, QGraphicsItem *parent)
    : QGraphicsItem(parent), _isHalf(false), _width(), _height(), _walls(), _cells()
{
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    int i; stream >> i;
    _isHalf = (i>0 ? true : false);
    stream >> i; _width = i;
    stream >> i; _height = i;
    _cells = std::vector<Cell>(_width*_height);
    for(unsigned int y=0;y<_height;++y) {
        for(unsigned int x=0;x<_width;++x) {
            QString str; stream >> str;
            char c = str.toInt(0,16);
            at(x,y).x = x, at(x,y).y = y;
            at(x,y).wdata = c;
        }
    }
    const char Nmask = 0x01;
    const char Emask = 0x02;
    const char Wmask = 0x08;
    const char Smask = 0x04;
    for(unsigned int x=0;x<_width;++x) {
        Cell &c1 = at(x,0);
        if((c1.wdata & Nmask)>0) {
            Wall w; w.x = x, w.y = 0;
            w.isHorizontal = true;
            _walls.push_back(w);
            c1.north = &_walls.back();
        }
        Cell &c2 = at(x,_height-1);
        if((c2.wdata & Smask)>0) {
            Wall w; w.x = x, w.y = _height;
            w.isHorizontal = true;
            _walls.push_back(w);
            c2.south = &_walls.back();
        }
    }
    for(unsigned int y=0;y<_height-1;++y) {
        for(unsigned int x=0;x<_width;++x) {
            Cell &cell = at(x,y);
            if((cell.wdata & Smask) > 0) {
                Wall w; w.x = x, w.y = y+1;
                w.isHorizontal = true;
                _walls.push_back(w);
                cell.south = &_walls.back();
                at(x,y+1).north = &_walls.back();
            }
        }
    }
    for(unsigned int y=0;y<_height;++y) {
        Cell &c1 = at(0,y);
        if((c1.wdata & Wmask)>0) {
            Wall w; w.x = 0, w.y = y;
            w.isVertical = true;
            _walls.push_back(w);
            c1.west = &_walls.back();
        }
        Cell &c2 = at(_width-1,y);
        if((c2.wdata & Emask)>0) {
            Wall w; w.x = _width, w.y = y;
            w.isVertical = true;
            _walls.push_back(w);
            c2.east = &_walls.back();
        }
    }
    for(unsigned int y=0;y<_height;++y) {
        for(unsigned int x=0;x<_width-1;++x) {
            Cell &cell = at(x,y);
            if((cell.wdata & Emask) > 0) {
                Wall w; w.x = x+1, w.y = y;
                w.isVertical = true;
                _walls.push_back(w);
                cell.east = &_walls.back();
                at(x+1,y).west = &_walls.back();
            }
        }
    }
}


MazeItem::Cell &MazeItem::at(unsigned int x, unsigned int y) {
    return _cells[x+y*_width];
}

qreal MazeItem::cellPixel() {
    return 18.0 * (_isHalf ? 0.5 : 1.0);
}

QRectF MazeItem::boundingRect() const
{
    return QRectF(0,0,413,429);
}

void MazeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const qreal roffset = cellPixel()/2.0;
    const qreal toffset = cellPixel()/2.0;
    painter->scale(boundingRect().width()/(_width+1)/cellPixel(),
                   boundingRect().width()/(_width+1)/cellPixel());
    painter->setPen(QColor(150,150,150));
    painter->drawRect(QRectF(QPointF(roffset,toffset),
                             QSizeF(_width*cellPixel(),_height*cellPixel())));

    // 壁
    painter->setPen(QColor(0,0,0));
    for(auto &w: _walls) {
        if(w.isHorizontal) {
            painter->drawLine(QPointF(w.x*cellPixel()+roffset,w.y*cellPixel()+toffset),
                              QPointF((w.x+1)*cellPixel()+roffset,w.y*cellPixel()+toffset));
        } else if(w.isVertical) {
            painter->drawLine(QPointF(w.x*cellPixel()+roffset,w.y*cellPixel()+toffset),
                              QPointF(w.x*cellPixel()+roffset,(w.y+1)*cellPixel()+toffset));
        }
    }
}
