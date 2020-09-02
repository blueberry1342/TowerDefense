#ifndef TOWER_H
#define TOWER_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <point.h>
#include <subject.h>



class Tower:public QWidget,public Subject
{
public:
    Tower(Point &xposition,QWidget *parent):Subject (xposition, parent){}
    Tower(){}
    Tower(Tower &t);

    void setAggressivity(int xa);
    void doDrawing(QPainter &q);
    virtual void upgrade()=0;
    int getaggressivity();
    int getUpgradecost();
    int getlevel();
    bool talentmark();


    static const int MagBulletf = 900;             //子弹产生速率
    static const int CarBulletf = 1700;
    static const int BluBulletf = 5000;
    static const int MagOriginCost=50;       //初始金钱
    static const int BluOriginCost=90;
    static const int CarOriginCost=70;
    static const int StrOriginCost=80;
    static const int TowerSize= 80 ;   //图标大小
    static const int Radius=282;       //攻击范围
    static constexpr double SellRatio=0.75;    //拆塔返现
    static constexpr double MagTalentRatio=1.1;   //技能参数
    static constexpr double BluTalentRatio=0.4;
    static const int BluTalentRatio2=1;
    static const int CarTalentRatio=5;
    static const int CarTalentRatio2=10;
    static const int CarTalentRatio3=30;

protected:


    QImage level1;      //不同等级的图标
    QImage level2;
    QImage level3;



    static const int MagAggressivity=6;    //攻击力
    static const int BluAggressivity=30;
    static const int CarAggressivity=7;
    static const int StrAggressivity=40;




    bool specialtalent;
    int level;
    int aggressivity;
    int upgradecost;



    virtual void loadImages()=0;      //画塔




};

#endif // TOWER_H
