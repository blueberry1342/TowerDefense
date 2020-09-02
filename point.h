#ifndef POINT_H
#define POINT_H
class Area;

class Point
{
public:
    Point(){}
    Point(double xx, double xy);
    Point(Point &xp);

    double getx();
    double gety();
    double distance(Point &xp);
    bool included(Area &xa);

private:
    double x,y;
};

class Area
{
public:
    Area(){}
    Area(Point *xp1, Point *xp2);
    double getx1();
    double getx2();
    double gety1();
    double gety2();
private:
    Point p1,p2;               //p1是左上点，p2是右下点
};

#endif // POINT_H
