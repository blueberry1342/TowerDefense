#ifndef MAP_H
#define MAP_H
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>

class Map
{
public:
    Map();
    void loadImage();
    QImage map;
    void doDrawing(QPainter &q);
    int getLength();


    static const int Mapwidth=1600;
    static const int Mapheight=900;
    static const int RoutineLength=1037;
    static const int AreaNum=7;  //不设塔的区域个数

    Area* areas[AreaNum];

    Point* routine[RoutineLength];
};

#endif // MAP_H
