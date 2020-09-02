#ifndef TRUENEMY_H
#define TRUENEMY_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>
#include "enemy.h"


class Kuribo:public Enemy
{
public:
    Kuribo();
    Kuribo(Point &xposition,QWidget *parent);
protected:
    void loadImages();
};


class FlyingKuribo:public Enemy
{
public:
    FlyingKuribo();
    FlyingKuribo(Point &xposition,QWidget *parent);
protected:
    void loadImages();
};

class HealingKuribo:public Enemy
{
public:
    HealingKuribo();
    HealingKuribo(Point &xposition,QWidget *parent);
protected:
    void loadImages();
};



#endif // TRUENEMY_H
