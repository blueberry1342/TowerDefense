#include "truenemy.h"
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>
#include "enemy.h"

Kuribo::Kuribo(){
    alive=true;
    speed=OriginSpeed;
    life=100;
    loadImages();
    setPosition(0,0);
    longevity=0;
    type=1;
    stucktimer=0;
    value=KuriboValue;
}

Kuribo::Kuribo(Point &xposition,QWidget *parent):Enemy(xposition,parent){
    alive=true;
    speed=OriginSpeed;
    life=100;
    loadImages();
    longevity=0;
    type=1;
    stucktimer=0;
    value=KuriboValue;
}

void Kuribo::loadImages(){
     enemy.load("://Images/Kuribo.png");
     enemy=enemy.scaled(100,100);
};


//****************************************************************
//****************************************************************

FlyingKuribo::FlyingKuribo(){
    alive=true;
    speed=int(OriginSpeed*1.5);
    life=100;
    loadImages();
    setPosition(0,0);
    longevity=0;
    type=2;
    stucktimer=0;
    value=FlyingKuriboValue;
}

FlyingKuribo::FlyingKuribo(Point &xposition,QWidget *parent):Enemy(xposition,parent){
    alive=true;
    speed=int(OriginSpeed*1.5);
    life=100;
    loadImages();
    longevity=0;
    type=2;
    stucktimer=0;
    value=FlyingKuriboValue;
}

void FlyingKuribo::loadImages(){
     enemy.load("://Images/flyingKuribo2.png");
     enemy=enemy.scaled(100,100);
};



//****************************************************************
//****************************************************************

HealingKuribo::HealingKuribo(){
    alive=true;
    speed=OriginSpeed;
    life=100;
    loadImages();
    setPosition(0,0);
    longevity=0;
    type=3;
    stucktimer=0;
    value=HealingKuriboValue;
}

HealingKuribo::HealingKuribo(Point &xposition,QWidget *parent):Enemy(xposition,parent){
    alive=true;
    speed=OriginSpeed;
    life=100;
    loadImages();
    longevity=0;
    type=3;
    stucktimer=0;
    value=HealingKuriboValue;
}

void HealingKuribo::loadImages(){
     enemy.load("://Images/HealingKuribo.png");
     enemy=enemy.scaled(100,100);
};




