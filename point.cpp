#include "point.h"
#include "math.h"

Point::Point(double xx, double xy)
{
  x=xx;
  y=xy;
}

Point::Point(Point &xp){
    x=xp.x;
    y=xp.y;
}

double Point::getx(){
    return x;
}

double Point::gety(){
    return y;
}

double Point::distance(Point &xp){
    return sqrt((x-xp.getx())*(x-xp.getx())+(y-xp.gety())*(y-xp.gety()));
}

bool Point::included(Area &xa){
    if(x>xa.getx1()&&x<xa.getx2()&&y>xa.gety1()&&y<xa.gety2())
        return true;
    else {
       return false;
    }
}

Area::Area(Point *xp1, Point *xp2){
    p1=*xp1;
    p2=*xp2;
}

double Area::getx1(){
    return p1.getx();
}

double Area::getx2(){
    return p2.getx();
}

double Area::gety1(){
    return p1.gety();
}

double Area::gety2(){
    return p2.gety();
}




