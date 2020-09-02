#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <tower.h>
#include <point.h>
#include <map.h>
#include <enemy.h>
#include <truetower.h>
#include <truenemy.h>
#include <bullet.h>
#include <mainwindow.h>

class Game:public QWidget
{
public:
    Game(QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    static const int B_WIDTH = 1600; //界面大小
    static const int B_HEIGHT = 900;
    static const int StartLife = 10;  //玩家生命
    static const int StartCoin = 300;  //初始金币
    static const int TowerNum = 10;  //最大塔数
    static const int EnemyNum = 100;  //最大妖怪数
    static const int BulletNum =500;  //最大子弹数
    static const int DELAY = 140;
    static const int EnemyEmerge = 1000;   //敌人出现单位时间
    static const int Showarea = 282;   //showoff图片半径

    static const int TotalWave = 700;    //总时间结点数
    static const int TotalTrueWave = 20; //实际产生妖怪的波数



    int myLife;
    int myCoin;
    void setLife(int xlife);
    void sublife(int xlife);
    void setCoin(int xcoin);
    void subCoin(int xcoin);
    void addCoin(int xcoin);
    QImage lifepicture;
    QString myScreenCoin;

    bool inGame;
    int timerId;   //最小时间，刷新与检测敌人
    int timerId1;   //青眼子弹发射
    int timerId2;   //magician子弹发射
    int timerId9;   //cartoon子弹发射
    int timerId3;   //Kuribo敌人生成
    int timerId4;   //FlyingKuribo生成
    int timerId5;   //HealingKuribo生成
    int timerId6;   //Healing治愈时间
    int timerId7;   //更小的间隔，子弹移动
    int timerId8;   //激流塔爆炸时长
    int timerWave;  //波数单位时间
    void initGame();   //设定timer

    int enemyperwave=0;   //每波的敌人数，随时间减少
    int passedwave=0;     //总波数
    int truewave[TotalTrueWave];       //实际波数的时间点



    int showoffnum;  //showoff图片种类
    void setshowoff(int xs);
    QImage showoff;
    Point showposition;




   Tower* towers[TowerNum];
   Enemy* enemies[EnemyNum];
   Bullet* bullets[BulletNum];
   int totalTower=0;
   int totalEnemy=0;
   int totalBullet=0;

   Map gamemap;

   void loadpictures();
   bool pictureofchoice;
   Point poc,poc1,poc2,poc3,poc4;
   QImage Poc,Poc1,Poc2,Poc3,Poc4;
   int choices;   //showoff用于单图展示，choices用于判定展示图形情况和选择情况
   void setchoices(int xc);

   int handletower; //塔的临时记号

   //QString xxx,yyy;用于调试
};

#endif // GAME_H
