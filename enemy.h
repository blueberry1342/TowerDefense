#ifndef ENEMY_H
#define ENEMY_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>

class Enemy:public QWidget, public Subject
{
public:
    Enemy();
    Enemy(Point &xposition,QWidget *parent);
    void setLife(int xa);   //设定生命值
    int getlife();          //获取生命值
    void attacked(int xa);  //生命值减少
    void addlife(int xl);   //生命值增加
    void doDrawing(QPainter &q);
    void move();            //移动
    void stuck(int xt);     //设定stuck时间，配合Cartoon塔的眩晕效果
    int getlongevity();     //返回地图卡槽的自然坐标
    void givelife(bool xalive);  //改变生死状态
    bool checkalive();      //返回生死状态
    int getSpeed();         //返回速度
    static const int EnemySize=100;  //图标大小

protected:
      QImage enemy;

      static const int OriginSpeed=3;  //基础速度
      static const int KuriboValue=10;
      static const int FlyingKuriboValue=12;
      static const int HealingKuriboValue=15;

      bool alive;    //是否存活
      int life;
      int speed;
      int longevity;   // 在地图上的自然坐标
      int stucktimer;

      virtual void loadImages()=0;


};

#endif // ENEMY_H
