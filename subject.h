#ifndef SUBJECT_H
#define SUBJECT_H
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>

class Subject
{
public:
    Subject(Point &xposition,QWidget *parent);
    Subject();
    Point &getPosition();
    void setPosition(Point &xp);
    void setPosition(int xx, int xy);
    virtual void doDrawing(QPainter &q)=0;
    int gettype();
    int getvalue();
protected:
    Point position;
    int type;
    int value;
};

#endif // SUBJECT_H
