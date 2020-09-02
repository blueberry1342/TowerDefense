#include "subject.h"


Subject::Subject(){}

Subject::Subject(Point &xposition,QWidget *parent):position(xposition){}


int Subject::gettype(){
    return type;
}

void Subject::setPosition(Point &xp){
    position=xp;
}

Point &Subject::getPosition(){
    return position;
}

void Subject::setPosition(int xx,int yy){
    position=Point(xx,yy);
}

int Subject::getvalue(){
    return value;
}
