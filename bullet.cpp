#include "bullet.h"
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>
#include <tower.h>
#include "truetower.h"
#include <QtCore/qmath.h>
#include <QPainter>

Bullet::Bullet(){
    loadImages();
}

Bullet::Bullet(Tower &t):Tower(t)
{
    loadImages();
}

Bullet::Bullet(Bullet &b):Tower(b){
    loadImages();
}

void Bullet::loadImages(){
    if(gettype()==1){
        level1.load("://Images/bullet1.png");
    }
    else if(gettype()==2){
        level1.load("://Images/bullet3.png");
    }
    else if(gettype()==3){
        level1.load("://Images/bullet4.png");
    }
    level1=level1.scaled(aggressivity*4,aggressivity*4);
    level2=level1;
    level3=level1;
}

void Bullet::move(){
    setPosition(int(getPosition().getx()+ BulletSpeed*x/sqrt(x*x+y*y)),int(getPosition().gety()+ BulletSpeed*y/sqrt(x*x+y*y)));
}

void Bullet::setDirection(double xx, double yy){
      x=xx;
      y=yy;
}

void Bullet::doDrawing(QPainter &q){
        if(level==1)
            q.drawImage(int(position.getx())-aggressivity*2,int(position.gety())-aggressivity*2,level1.scaled(aggressivity*4,aggressivity*4));
        else if(level==2)
            q.drawImage(int(position.getx())-aggressivity*2,int(position.gety())-aggressivity*2,level2.scaled(aggressivity*4,aggressivity*4));
        else
            q.drawImage(int(position.getx())-aggressivity*2,int(position.gety())-aggressivity*2,level3.scaled(aggressivity*4,aggressivity*4));

}

