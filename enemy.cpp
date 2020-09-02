#include "enemy.h"
#include <point.h>
#include <game.h>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>

Enemy::Enemy()
{
    alive=true;
    speed=OriginSpeed;
    life=100;
    setPosition(0,0);
    longevity=0;
}

Enemy::Enemy(Point &xposition,QWidget *parent):Subject(xposition,parent){
    alive=true;
    speed=OriginSpeed;
    life=100;
    longevity=0;
}

void Enemy::setLife(int xa){
    if(xa<100)
       life=xa;
    else {
       life=100;
    }
}

int Enemy::getlife(){
    return life;
}



void Enemy::doDrawing(QPainter &q){
    q.drawImage(int(position.getx()-sqrt(life)*10*3/8),int(position.gety()-sqrt(life)*10*3/8),enemy.scaled(int(sqrt(life)*10*3/4),int(sqrt(life)*10*3/4)));
}

void Enemy::givelife(bool xalive){
    alive=xalive;
}

void Enemy::move(){
    if(stucktimer>0)
        stucktimer--;
    else
    longevity=longevity+speed;

}

void Enemy::stuck(int xt){
    stucktimer=xt;
}

int Enemy::getlongevity(){
    return longevity;
}

void Enemy::attacked(int xa){
    life=life-xa;
    if(life<=0)
        alive=false;
}

bool Enemy::checkalive(){
    return alive;
}

int Enemy::getSpeed(){
    return speed;
}


void Enemy::addlife(int xl){
    if(life+xl<100)
        life=life+xl;
    else {
        life=100;
    }
}

