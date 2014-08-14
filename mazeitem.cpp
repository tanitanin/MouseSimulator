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
    int half_gx, half_gy;
    if(_isHalf) stream >> half_gx >> half_gy;
    _cells = std::vector<Cell>(_width*_height);
    for(unsigned int y=0;y<_height;++y) {
        for(unsigned int x=0;x<_width;++x) {
            QString str; stream >> str;
            char c = str.toInt(0,16);
            at(x,y).x = x, at(x,y).y = y;
            at(x,y).wdata = c;
        }
    }

    // スタート
    at(0,_height-1).isStart = true;
    _start = QPoint(0,_height-1);
    // ゴール
    if(_isHalf) {
        on(half_gx,half_gy).isGoal = true;
        _goals.push_back(QPoint(half_gx,half_gy));
    } else {
        /*
        at(_width/2,_height/2).isGoal = true;
        at(_width/2,_height/2-1).isGoal = true;
        at(_width/2-1,_height/2).isGoal = true;
        at(_width/2-1,_height/2-1).isGoal = true;
        _goals.push_back(QPoint(_width/2,_height/2));
        _goals.push_back(QPoint(_width/2,_height/2-1));
        _goals.push_back(QPoint(_width/2-1,_height/2));
        _goals.push_back(QPoint(_width/2-1,_height/2-1));
        */
        on(7,7).isGoal = true;
        _goals.push_back(QPoint(7,7));
        if(_width>8) {
            on(8,7).isGoal = true;
            _goals.push_back(QPoint(8,7));
        }
        if(_height>8) {
            on(7,8).isGoal = true;
            _goals.push_back(QPoint(7,8));
        }
        if(_width>8 && _height>8) {
            on(8,8).isGoal = true;
            _goals.push_back(QPoint(8,8));
        }
    }
    // 壁
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
    isOK = true;
}


MazeItem::Cell &MazeItem::at(unsigned int x, unsigned int y) {
    return _cells[x+y*_width];
}

MazeItem::Cell &MazeItem::on(unsigned int x, unsigned int y) {
    return _cells[x+(_height-1-y)*_width];
}

const unsigned int MazeItem::width() const {
    return _width;
}
const unsigned int MazeItem::height() const {
    return _height;
}

qreal MazeItem::cellPixel() {
    return 18.0 * (_isHalf ? 0.5 : 1.0);
}

QRectF MazeItem::boundingRect() const
{

    return QRectF(0,0,400,400);
}

void MazeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isOK) {
        const qreal roffset = cellPixel()/2.0;
        const qreal toffset = cellPixel()/2.0;
        painter->scale(boundingRect().width()/(_width+1)/cellPixel(),
                       boundingRect().width()/(_width+1)/cellPixel());
        // 土台
        painter->setPen(QColor(150,150,150));
        painter->fillRect(QRectF(QPointF(roffset,toffset),
                                 QSizeF(_width*cellPixel(),_height*cellPixel())),
                          QColor(255,255,255));
        // スタート
        painter->fillRect(QRectF(QPointF(_start.x()*cellPixel()+roffset,_start.y()*cellPixel()+toffset),
                                 QSizeF(cellPixel(),cellPixel())),
                          QColor(250,250,200));
        // ゴール
        for(auto &p: _goals) {
            Cell &c = on(p.x(),p.y());
            painter->fillRect(QRectF(QPointF(c.x*cellPixel()+roffset,c.y*cellPixel()+toffset),
                                     QSizeF(cellPixel(),cellPixel())),
                              QColor(250,200,250));
        }
        // 壁
        //painter->setPen(QColor(240,40,40));
        painter->setPen(QColor(40,40,40));
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
}
