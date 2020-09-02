#include "map.h"
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>
#include <tower.h>

Map::Map()
{
    loadImage();
    int i;

    for(i=0;i<44;i++)
        routine[i]=new Point(174,3*i);
    for(i=44;i<277;i++)
        routine[i]=new Point(174+3*(i-44),132);
    for(i=277;i<371;i++)
        routine[i]=new Point(873,132+3*(i-277));
    for(i=371;i<602;i++)
        routine[i]=new Point(873-3*(i-371),414);
    for(i=602;i<697;i++)
        routine[i]=new Point(180,414+3*(i-602));
    for(i=697;i<1037;i++)
        routine[i]=new Point(180+3*(i-697),699);

    areas[0]=new Area(new Point(140-Tower::TowerSize/2,0-Tower::TowerSize/2),new Point(200+Tower::TowerSize/2,160+Tower::TowerSize/2));
    areas[1]=new Area(new Point(140-Tower::TowerSize/2,50-Tower::TowerSize/2),new Point(900+Tower::TowerSize/2,160+Tower::TowerSize/2));
    areas[2]=new Area(new Point(840-Tower::TowerSize/2,50-Tower::TowerSize/2),new Point(910+Tower::TowerSize/2,440+Tower::TowerSize/2));
    areas[3]=new Area(new Point(150-Tower::TowerSize/2,360-Tower::TowerSize/2),new Point(900+Tower::TowerSize/2,440+Tower::TowerSize/2));
    areas[4]=new Area(new Point(150-Tower::TowerSize/2,370-Tower::TowerSize/2),new Point(200+Tower::TowerSize/2,725+Tower::TowerSize/2));
    areas[5]=new Area(new Point(140-Tower::TowerSize/2,635-Tower::TowerSize/2),new Point(1000+Tower::TowerSize/2,725+Tower::TowerSize/2));
    areas[6]=new Area(new Point(1010-Tower::TowerSize/2,370-Tower::TowerSize/2),new Point(1600+Tower::TowerSize/2,900+Tower::TowerSize/2));
}

void Map::loadImage(){
    map.load("://Images/map0.png");
    map=map.scaled(Mapwidth,Mapheight);
}

void Map::doDrawing(QPainter &q){
   q.drawImage(0,0,map);
}

int Map::getLength(){
    return RoutineLength;
}


