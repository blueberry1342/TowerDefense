#ifndef TRUETOWER_H
#define TRUETOWER_H
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>
#include <tower.h>
#include <QPainter>


class Magician:public Tower
{
public:
    Magician(Point &xposition,QWidget *parent) ;
    Magician();
    void upgrade();
protected:
    void loadImages();
};


class BlueEyes:public Tower
{
public:
    BlueEyes(Point &xposition,QWidget *parent) ;
    BlueEyes();
    void upgrade();
protected:
    void loadImages();
};

class Cartoon:public Tower
{
public:
    Cartoon(Point &xposition,QWidget *parent) ;
    Cartoon();
    void upgrade();
protected:
    void loadImages();
};


class Stream:public Tower
{
public:
    Stream(Point &xposition,QWidget *parent) ;
    Stream();
    void upgrade();
    void doDrawing(QPainter &q);  //特殊的绘画
protected:
    void loadImages();
};




#endif // TRUETOWER_H
