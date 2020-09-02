#include "truetower.h"
#include "tower.h"
#include <point.h>
#include <game.h>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>

Magician::Magician(Point &xposition,QWidget *parent) : Tower (xposition,parent){
    level=1;
    specialtalent=false;
    upgradecost=MagOriginCost*1;
    loadImages();
    setAggressivity(MagAggressivity);
    type=1;
    value=int(MagOriginCost*SellRatio);
}

Magician::Magician(){
    level=1;
    upgradecost=MagOriginCost*1;
    loadImages();
    setAggressivity(MagAggressivity);
    type=1;
    value=int(MagOriginCost*SellRatio);
}

void Magician::loadImages() {

    level1.load("://Images/magicianLV1.jpg");
    level2.load("://Images/magicianLV2.jpg");
    level3.load("://Images/magicianLV3.jpg");
    level1=level1.scaled(TowerSize,TowerSize);
    level2=level2.scaled(TowerSize,TowerSize);
    level3=level3.scaled(TowerSize,TowerSize);

}

void Magician::upgrade(){
    if(level==1){
        level++;
        value=int(value*1.5);
        upgradecost=upgradecost*2;
        setAggressivity(int(1.25*aggressivity));
    }
    else if(level==2){
        level++;
        value=value*2;
        setAggressivity(int(1.25*aggressivity));
        specialtalent=true;
    }
}



//***********************************************************************
//***********************************************************************


Cartoon::Cartoon(Point &xposition,QWidget *parent) : Tower (xposition,parent){
    level=1;
    specialtalent=true;
    upgradecost=int(CarOriginCost*1.25);
    loadImages();
    setAggressivity(CarAggressivity);
    type=2;
    value=int(CarOriginCost*SellRatio);
}

Cartoon::Cartoon(){
    level=1;
    upgradecost=int(CarOriginCost*1.5);
    loadImages();
    setAggressivity(CarAggressivity);
    type=2;
    value=int(CarOriginCost*SellRatio);
}

void Cartoon::loadImages() {

    level1.load("://Images/cartoonLV1.jpg");
    level2.load("://Images/cartoonLV2.png");
    level3.load("://Images/cartoonLV3.jpg");
    level1=level1.scaled(TowerSize,TowerSize);
    level2=level2.scaled(TowerSize,TowerSize);
    level3=level3.scaled(TowerSize,TowerSize);

}


void Cartoon::upgrade(){
    if(level==1){
        level++;
        upgradecost=int(upgradecost*1.5);
        setAggressivity(int(1.5*aggressivity));
        specialtalent=true;
    }
    else if(level==2){
        level++;
        setAggressivity(int(1.25*aggressivity));
    }
}


//***********************************************************************
//***********************************************************************


BlueEyes::BlueEyes(Point &xposition,QWidget *parent) : Tower (xposition,parent){
    level=1;
    upgradecost=int(BluOriginCost*2.5);
    loadImages();
    setAggressivity(BluAggressivity);
    type=3;
    value=int(BluOriginCost*SellRatio);
}

BlueEyes::BlueEyes(){
    level=1;
    upgradecost=int(BluOriginCost*2.5);
    specialtalent=false;
    loadImages();
    setAggressivity(BluAggressivity);
    type=3;
    value=int(BluOriginCost*SellRatio);
}

void BlueEyes::loadImages() {

    level1.load("://Images/blueyesLV1.jpg");
    level2.load("://Images/blueyesLV2.png");
    level3.load("://Images/blueyesLV3.jpg");
    level1=level1.scaled(TowerSize,TowerSize);
    level2=level2.scaled(TowerSize,TowerSize);
    level3=level3.scaled(TowerSize,TowerSize);

}

void BlueEyes::upgrade(){
    if(level==1){
        level++;
        upgradecost=upgradecost*2;
        setAggressivity(int(aggressivity));
        specialtalent=true;
    }
    else if(level==2){
        level++;
        setAggressivity(int(1.3*aggressivity));
    }
}


//***********************************************************************
//***********************************************************************



Stream::Stream(Point &xposition,QWidget *parent) : Tower (xposition,parent){
    level=1;
    upgradecost=0;
    loadImages();
    setAggressivity(StrAggressivity);
    type=4;
    value=int(StrOriginCost*SellRatio);
}

Stream::Stream(){
    level=1;
    upgradecost=0;
    loadImages();
    setAggressivity(StrAggressivity);
    type=4;
    value=int(StrOriginCost*SellRatio);
}

void Stream::loadImages() {

    level1.load("://Images/stream.jpg");
    level2.load("://Images/bullet5.png");
    level3.load("://Images/bullet5.png");
    level1=level1.scaled(TowerSize,TowerSize);
    level2=level2.scaled(Radius*2,Radius*2);
    level3=level3.scaled(Radius*2,Radius*2);

}

void Stream::upgrade(){
    if(level==1){
        level++;
        upgradecost=0;
        specialtalent=true;
    }
    else if(level==2){
        level++;
    }
}

void Stream::doDrawing(QPainter &q){
        if(level==1)
            q.drawImage(int(position.getx())-TowerSize/2,int(position.gety())-TowerSize/2,level1);
        else if(level==2)
            q.drawImage(int(position.getx())-Radius,int(position.gety())-Radius,level2);
        else
            q.drawImage(int(position.getx())-Radius,int(position.gety())-Radius,level3);

}
