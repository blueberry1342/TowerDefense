#ifndef BULLET_H
#define BULLET_H
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>
#include <tower.h>
#include "truetower.h"

class Bullet:public Tower
{
public:
    Bullet();
    Bullet(Tower &t);
    Bullet(Bullet &b);
    void loadImages();
    void setDirection(double xx, double yy);  //设定方向
    void move();    //子弹移动
    void upgrade(){}
    void doDrawing(QPainter &q);
private:
    double x,y;   //方向参数
    static const int BulletSpeed=17;   //子弹移动速度
};




#endif // BULLET_H
