#include "tower.h"
#include <point.h>
#include <game.h>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>
#include <iostream>
using namespace std;


Tower::Tower(Tower &t):Subject (t.getPosition(),nullptr){   //复制构造
    level=t.getlevel();
    setAggressivity(t.getaggressivity());
    type=t.gettype();
    specialtalent=t.talentmark();
}



void Tower::doDrawing(QPainter &q){
        if(level==1)
            q.drawImage(int(position.getx())-TowerSize/2,int(position.gety())-TowerSize/2,level1);
        else if(level==2)
            q.drawImage(int(position.getx())-TowerSize/2,int(position.gety())-TowerSize/2,level2);
        else
            q.drawImage(int(position.getx())-TowerSize/2,int(position.gety())-TowerSize/2,level3);

}

void Tower::setAggressivity(int xa){
    aggressivity=xa;
}

int Tower::getaggressivity(){
    return aggressivity;
}

int Tower::getUpgradecost(){
    return upgradecost;
}


int Tower::getlevel(){
    return level;
}

bool Tower::talentmark(){
    return specialtalent;
}
