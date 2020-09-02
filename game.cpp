#include "game.h"
#include "point.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QtWidgets>
#include <truetower.h>
#include <truenemy.h>
#include <bullet.h>
#include <mainwindow.h>
#include <QMediaPlayer>

using namespace std;


Game::Game(QWidget *parent) : QWidget(parent)
{

    setStyleSheet("background-color:white;");
    inGame = true;
    setLife(StartLife);
    setCoin(StartCoin);
    pictureofchoice=false;
    setchoices(0);
    setshowoff(0);
    resize(B_WIDTH, B_HEIGHT);
    initGame();
    loadpictures();
    for(int i=0;i<TotalTrueWave;i++){
        truewave[i]=int(1.5*i*i+2*i);
    }

}

void Game::setLife(int xlife){                //设定我方生命


    myLife=xlife;
    switch(myLife){
    case 10 : lifepicture.load("://Images/10.jpg"); break;
    case  9 : lifepicture.load("://Images/9.jpg");  break;
    case  8 : lifepicture.load("://Images/8.jpg");  break;
    case  7 : lifepicture.load("://Images/7.jpg");  break;
    case  6 : lifepicture.load("://Images/6.jpg");  break;
    case  5 : lifepicture.load("://Images/5.jpg");  break;
    case  4 : lifepicture.load("://Images/4.jpg");  break;
    case  3 : lifepicture.load("://Images/3.jpg");  break;
    case  2 : lifepicture.load("://Images/2.jpg");  break;
    case  1 : lifepicture.load("://Images/1.jpg");  break;
    case  0 : lifepicture.load("://Images/0.jpg");  break;
    }
}

void Game::sublife(int xlife){                //我方生命减少
    myLife=myLife-xlife;
    switch(myLife){
    case 10 : lifepicture.load("://Images/10.jpg"); break;
    case  9 : lifepicture.load("://Images/9.jpg");  break;
    case  8 : lifepicture.load("://Images/8.jpg");  break;
    case  7 : lifepicture.load("://Images/7.jpg");  break;
    case  6 : lifepicture.load("://Images/6.jpg");  break;
    case  5 : lifepicture.load("://Images/5.jpg");  break;
    case  4 : lifepicture.load("://Images/4.jpg");  break;
    case  3 : lifepicture.load("://Images/3.jpg");  break;
    case  2 : lifepicture.load("://Images/2.jpg");  break;
    case  1 : lifepicture.load("://Images/1.jpg");  break;
    case  0 : lifepicture.load("://Images/0.jpg");  break;
    }
}

void Game::loadpictures(){  //加载选择界面图片
    Poc1.load("://Images/magicianLV1.jpg");
    Poc2.load("://Images/cartoonLV1.jpg");
    Poc3.load("://Images/stream.jpg");
    Poc4.load("://Images/blueyesLV1.jpg");
    Poc.load("://Images/question.png");
    Poc1=Poc1.scaled(Tower::TowerSize,Tower::TowerSize);
    Poc2=Poc2.scaled(Tower::TowerSize,Tower::TowerSize);
    Poc3=Poc3.scaled(Tower::TowerSize,Tower::TowerSize);
    Poc4=Poc4.scaled(Tower::TowerSize,Tower::TowerSize);
    Poc=Poc.scaled(Tower::TowerSize,Tower::TowerSize);
}

void Game::setCoin(int xcoin){                //设定金币
    myCoin=xcoin;
}

void Game::subCoin(int xcoin){
    myCoin=myCoin-xcoin;
}

void Game::addCoin(int xcoin){
    myCoin=myCoin+xcoin;
}


void Game::initGame(){
    timerId = startTimer(DELAY);            //两个时间
    timerId1= startTimer(Tower::BluBulletf);
    timerId2= startTimer(Tower::MagBulletf);
    timerId9= startTimer(Tower::CarBulletf);
    timerId3= startTimer(EnemyEmerge*3);
    timerId4= startTimer(EnemyEmerge*5);
    timerId5= startTimer(EnemyEmerge*11);
    timerId6= startTimer(DELAY*4);
    timerId7= startTimer(int(DELAY/5));
    timerId8= startTimer(int(DELAY*5));
    timerWave=startTimer(EnemyEmerge);
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/new/prefix1/sounds/bgm.mp3"));
    player->setVolume(30);
    player->play();
}

void Game::setshowoff(int xs){
    showoffnum=xs;
}

void Game::setchoices(int xc){
    choices=xc;
}

void Game::mousePressEvent(QMouseEvent *event){   //press和move有重复的功能，分升级和不升级

    int mx = event->x();
    int my = event->y();
    Point mp(mx,my);
    //xxx = QString::number(mx);    用于调试
    //yyy = QString::number(my);
    showposition=mp;
    int i;

    if(pictureofchoice==false){
        setchoices(0);
        poc=mp;
        poc1=Point(mx-Tower::TowerSize,my);
        poc2=Point(mx,my-Tower::TowerSize);
        poc3=Point(mx+Tower::TowerSize,my);
        poc4=Point(mx,my+Tower::TowerSize);
        if(event->button() == Qt::RightButton){   //右键拆塔
            for(i=0;i<totalTower;i++){
                if(towers[i]->getPosition().distance(mp)<Tower::TowerSize/2)
                     {

                         int j;
                         totalTower--;
                         addCoin(towers[i]->getvalue());
                         for(j=i;j<totalTower;j++){
                             towers[j]=towers[j+1];
                         }

                         QWidget::mousePressEvent(event);
                         return ;
                     }
                }
        }
        else  if(event->button() == Qt::LeftButton ){         //左键
            int init=0;
            for(i=0;i<gamemap.AreaNum;i++)
            {
                if(mp.included(*gamemap.areas[i])==true)
                    init++;
            }
            if(mx<1600&&mx>0&&my>0&&my<900){
                for(i=0;i<totalTower;i++){                      //升级判定
                    if(towers[i]->getPosition().distance(mp)<Tower::TowerSize)
                    {
                       setchoices(0);
                       if(towers[i]->getPosition().distance(mp)<Tower::TowerSize/2){
                        handletower=i;
                        if(towers[i]->gettype()!=4&&towers[i]->getUpgradecost()<=myCoin&&towers[i]->getlevel()<3){
                            switch(towers[i]->getlevel()){
                            case 1 : setshowoff(4) ;   break;
                            case 2 : setshowoff(5) ;   break;
                            }
                            QWidget::mousePressEvent(event);

                         }
                        else {
                            setshowoff(0);
                        }
                       }
                        return ;
                   }
                }
                if(totalTower+1<=TowerNum){
                    setshowoff(0);
                    if(myCoin<Tower::MagOriginCost||init!=0)
                        setchoices(5);
                    else if(myCoin<Tower::CarOriginCost)
                        setchoices(1);
                    else if(myCoin<Tower::StrOriginCost)
                        setchoices(2);
                    else if(myCoin<Tower::BluOriginCost)
                        setchoices(3);
                    else
                        setchoices(4);
                }

            }
            else {
                setshowoff(0);
            }
           }

    }
    else if(event->button() == Qt::LeftButton){
        if(choices==1){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else setshowoff(0);
            }

        else if(choices==2){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else if(mp.distance(poc2)<Tower::TowerSize/2)
                setshowoff(2);
            else setshowoff(0);
        }
        else if(choices==3){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else if(mp.distance(poc2)<Tower::TowerSize/2)
                setshowoff(2);
            else if(mp.distance(poc3)<Tower::TowerSize/2)
                setshowoff(3);
            else setshowoff(0);
        }
        else if(choices==4){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else if(mp.distance(poc2)<Tower::TowerSize/2)
                setshowoff(2);
            else if(mp.distance(poc3)<Tower::TowerSize/2)
                setshowoff(3);
            else if(mp.distance(poc4)<Tower::TowerSize/2)
                setshowoff(6);
            else setshowoff(0);
        }

    }
    else if(event->button() == Qt::RightButton){
        pictureofchoice=false;
        setchoices(0);
    }



    QWidget::mousePressEvent(event);

}

void Game::mouseMoveEvent(QMouseEvent *event){
    int mx = event->x();
    int my = event->y();
    Point mp(mx,my);
    showposition=mp;
    int i;
    if(event->buttons() == Qt::LeftButton ){
    if(pictureofchoice==false){   //在选择界面内时，choices不改变，仍用showoff出图
        poc=mp;
        poc1=Point(mx-Tower::TowerSize,my);
        poc2=Point(mx,my-Tower::TowerSize);
        poc3=Point(mx+Tower::TowerSize,my);
        poc4=Point(mx,my+Tower::TowerSize);
        int init=0;
        for(i=0;i<gamemap.AreaNum;i++)
        {
            if(mp.included(*gamemap.areas[i])==true)
                init++;
        }
            if(mx<1600&&mx>0&&my>0&&my<900){
                for(i=0;i<totalTower;i++){                      //升级判定
                    if(towers[i]->getPosition().distance(mp)<Tower::TowerSize)
                    {
                        setchoices(0);
                        if(towers[i]->getPosition().distance(mp)<Tower::TowerSize/2){
                            handletower=i;
                            if(towers[i]->gettype()!=4&&towers[i]->getUpgradecost()<=myCoin&&towers[i]->getlevel()<3){
                            switch(towers[i]->getlevel()){
                                case 1 : setshowoff(4) ;   break;
                                case 2 : setshowoff(5) ;   break;
                            }
                        }
                             QWidget::mouseMoveEvent(event);

                         }
                        else {
                            setshowoff(0);
                         }
                       return ;
                   }
               }
               if(totalTower+1<=TowerNum){
                    setshowoff(0);
                    if(myCoin<Tower::MagOriginCost||init!=0)
                        setchoices(5);
                    else if(myCoin<Tower::CarOriginCost)
                        setchoices(1);
                    else if(myCoin<Tower::StrOriginCost)
                        setchoices(2);
                    else if(myCoin<Tower::BluOriginCost)
                        setchoices(3);
                    else
                        setchoices(4);
                }
                else {
                    setshowoff(0);
                    setchoices(0);
                }
           }
           else {
                setshowoff(0);
                setchoices(0);
            }

    }
    else {
        if(choices==1){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else setshowoff(0);
            }

        else if(choices==2){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else if(mp.distance(poc2)<Tower::TowerSize/2)
                setshowoff(2);
            else setshowoff(0);
        }
        else if(choices==3){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else if(mp.distance(poc2)<Tower::TowerSize/2)
                setshowoff(2);
            else if(mp.distance(poc3)<Tower::TowerSize/2)
                setshowoff(3);
            else setshowoff(0);
     }
        else if(choices==4){
            if(mp.distance(poc1)<Tower::TowerSize/2)
                setshowoff(1);
            else if(mp.distance(poc2)<Tower::TowerSize/2)
                setshowoff(2);
            else if(mp.distance(poc3)<Tower::TowerSize/2)
                setshowoff(3);
            else if(mp.distance(poc4)<Tower::TowerSize/2)
                setshowoff(6);
            else setshowoff(0);
     }
     }
    }
    QWidget::mouseMoveEvent(event);
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    int mx = event->x();
    int my = event->y();
    Point mp(mx,my);
    showposition=mp;
    int i;
    setshowoff(0);
    if(event->button() == Qt::LeftButton){
    if(pictureofchoice==false){
        poc=mp;
        poc1=Point(mx-Tower::TowerSize,my);
        poc2=Point(mx,my-Tower::TowerSize);
        poc3=Point(mx+Tower::TowerSize,my);
        poc4=Point(mx,my+Tower::TowerSize);
        int init=0;
        for(i=0;i<gamemap.AreaNum;i++)
        {
            if(mp.included(*gamemap.areas[i])==true)
                init++;
        }
        if(mx<1600&&mx>0&&my>0&&my<900){          //左键
        for(i=0;i<totalTower;i++){                      //升级判定
            if(towers[i]->getPosition().distance(mp)<Tower::TowerSize/2)
            {
                handletower=i;
                if(towers[i]->getUpgradecost()<=myCoin&&towers[i]->getlevel()<3){
                    subCoin(towers[i]->getUpgradecost());
                    towers[i]->upgrade();
                    QWidget::mouseMoveEvent(event);
                 }
                    setchoices(0);
                    return ;
            }
        }

        if(totalTower+1<=TowerNum ){

            if(myCoin<Tower::MagOriginCost||init!=0){
                setchoices(0);
            }
            else{
                pictureofchoice=true;
                if(myCoin<Tower::CarOriginCost)
                    setchoices(1);
                else if(myCoin<Tower::StrOriginCost)
                    setchoices(2);
                else if(myCoin<Tower::BluOriginCost)
                    setchoices(3);
                else
                    setchoices(4);
            }
         }
        }
    }
    else {               //建塔
        if(choices==1){
            if(mp.distance(poc1)<Tower::TowerSize/2){
                towers[totalTower]=new Magician(poc,nullptr);
                totalTower++;
                subCoin(Tower::MagOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
        }

        else if(choices==2){
            if(mp.distance(poc1)<Tower::TowerSize/2){
                towers[totalTower]=new Magician(poc,nullptr);
                totalTower++;
                subCoin(Tower::MagOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
            else if(mp.distance(poc2)<Tower::TowerSize/2){
                towers[totalTower]=new Cartoon(poc,nullptr);
                totalTower++;
                subCoin(Tower::CarOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
        }
        else if(choices==3){
            if(mp.distance(poc1)<Tower::TowerSize/2){
                towers[totalTower]=new Magician(poc,nullptr);
                totalTower++;
                subCoin(Tower::MagOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
            else if(mp.distance(poc2)<Tower::TowerSize/2){
                towers[totalTower]=new Cartoon(poc,nullptr);
                totalTower++;
                subCoin(Tower::CarOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
            else if(mp.distance(poc3)<Tower::TowerSize/2){
                towers[totalTower]=new Stream(poc,nullptr);
                totalTower++;
                subCoin(Tower::StrOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
     }
        else if(choices==4){
            if(mp.distance(poc1)<Tower::TowerSize/2){
                towers[totalTower]=new Magician(poc,nullptr);
                totalTower++;
                subCoin(Tower::MagOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
            else if(mp.distance(poc2)<Tower::TowerSize/2){
                towers[totalTower]=new Cartoon(poc,nullptr);
                totalTower++;
                subCoin(Tower::CarOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
            else if(mp.distance(poc3)<Tower::TowerSize/2){
                towers[totalTower]=new Stream(poc,nullptr);
                totalTower++;
                subCoin(Tower::StrOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
            else if(mp.distance(poc4)<Tower::TowerSize/2){
                towers[totalTower]=new BlueEyes(poc,nullptr);
                totalTower++;
                subCoin(Tower::BluOriginCost);
                setchoices(0);
                pictureofchoice=false;
            }
     }
    pictureofchoice=false;
    }
    }
    QWidget::mouseReleaseEvent(event);

    }

void Game::paintEvent(QPaintEvent *e){
    QPainter qp(this);
    QFont font("MV Boli", 15, QFont::Bold, false);
    qp.setPen(Qt::blue);
    qp.setFont(font);
    gamemap.doDrawing(qp);    //画地图
    qp.drawText(1370,300,"Coin:");  //画金币
    qp.drawText(1470,300,myScreenCoin);
    //qp.drawText(1470,500,xxx);  用于调试
    //qp.drawText(1470,600,yyy);
    qp.drawImage(1400,100, lifepicture.scaled(100,100));
    qp.setPen(Qt::white);
    int i;

    for(i=0;i<totalTower;i++)              //画塔
        towers[i]->doDrawing(qp);
    for(i=0;i<totalEnemy;i++)              //画敌人
        enemies[i]->doDrawing(qp);
    switch (choices) {              //选择界面
    case 0: break;
    case 1: qp.drawEllipse(poc.getx()-Tower::Radius,poc.gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
        qp.drawImage(poc.getx()-Tower::TowerSize/2,poc.gety()-Tower::TowerSize/2,Poc);
        qp.drawImage(poc1.getx()-Tower::TowerSize/2,poc1.gety()-Tower::TowerSize/2,Poc1); break;
    case 2: qp.drawEllipse(poc.getx()-Tower::Radius,poc.gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
        qp.drawImage(poc.getx()-Tower::TowerSize/2,poc.gety()-Tower::TowerSize/2,Poc);
        qp.drawImage(poc1.getx()-Tower::TowerSize/2,poc1.gety()-Tower::TowerSize/2,Poc1);
        qp.drawImage(poc2.getx()-Tower::TowerSize/2,poc2.gety()-Tower::TowerSize/2,Poc2); break;
    case 3: qp.drawEllipse(poc.getx()-Tower::Radius,poc.gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
        qp.drawImage(poc.getx()-Tower::TowerSize/2,poc.gety()-Tower::TowerSize/2,Poc);
        qp.drawImage(poc1.getx()-Tower::TowerSize/2,poc1.gety()-Tower::TowerSize/2,Poc1);
        qp.drawImage(poc2.getx()-Tower::TowerSize/2,poc2.gety()-Tower::TowerSize/2,Poc2);
        qp.drawImage(poc3.getx()-Tower::TowerSize/2,poc3.gety()-Tower::TowerSize/2,Poc3); break;
    case 4: qp.drawEllipse(poc.getx()-Tower::Radius,poc.gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
        qp.drawImage(poc.getx()-Tower::TowerSize/2,poc.gety()-Tower::TowerSize/2,Poc);
        qp.drawImage(poc1.getx()-Tower::TowerSize/2,poc1.gety()-Tower::TowerSize/2,Poc1);
        qp.drawImage(poc2.getx()-Tower::TowerSize/2,poc2.gety()-Tower::TowerSize/2,Poc2);
        qp.drawImage(poc3.getx()-Tower::TowerSize/2,poc3.gety()-Tower::TowerSize/2,Poc3);
        qp.drawImage(poc4.getx()-Tower::TowerSize/2,poc4.gety()-Tower::TowerSize/2,Poc4);break;
    case 5: qp.drawEllipse(poc.getx()-Tower::Radius,poc.gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
        qp.drawImage(poc.getx()-Tower::TowerSize/2,poc.gety()-Tower::TowerSize/2,Poc); break;
    }

    switch(showoffnum){            //特效图片
    case 1: showoff.load("://Images/magicianLV1.jpg");
        qp.drawImage(poc.getx()-Showarea/2,poc.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break ;
    case 2: showoff.load("://Images/cartoonLV1.jpg");
        qp.drawImage(poc.getx()-Showarea/2,poc.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break ;
    case 3: showoff.load("://Images/stream.jpg");
        qp.drawImage(poc.getx()-Showarea/2,poc.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break ;
    case 6: showoff.load("://Images/blueyesLV1.jpg");
        qp.drawImage(poc.getx()-Showarea/2,poc.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break ;
    case 4:
        switch(towers[handletower]->gettype()){
        case 1: showoff.load("://Images/magicianLV2.jpg");
            qp.drawEllipse(towers[handletower]->getPosition().getx()-Tower::Radius,towers[handletower]->getPosition().gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
            qp.drawImage(showposition.getx()-Showarea/2,showposition.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break;
        case 2: showoff.load("://Images/cartoonLV2.png");
            qp.drawEllipse(towers[handletower]->getPosition().getx()-Tower::Radius,towers[handletower]->getPosition().gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
            qp.drawImage(showposition.getx()-Showarea/2,showposition.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break;
        case 3: showoff.load("://Images/blueyesLV2.png");
            qp.drawEllipse(towers[handletower]->getPosition().getx()-Tower::Radius,towers[handletower]->getPosition().gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
            qp.drawImage(showposition.getx()-Showarea/2,showposition.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break;
        }
        break;
   case 5:
        switch(towers[handletower]->gettype()){
        case 1: showoff.load("://Images/magicianLV3.jpg");
            qp.drawEllipse(towers[handletower]->getPosition().getx()-Tower::Radius,towers[handletower]->getPosition().gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
            qp.drawImage(showposition.getx()-Showarea/2,showposition.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break;
        case 2: showoff.load("://Images/cartoonLV3.jpg");
            qp.drawEllipse(towers[handletower]->getPosition().getx()-Tower::Radius,towers[handletower]->getPosition().gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
            qp.drawImage(showposition.getx()-Showarea/2,showposition.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break;
        case 3: showoff.load("://Images/blueyesLV3.jpg");
            qp.drawEllipse(towers[handletower]->getPosition().getx()-Tower::Radius,towers[handletower]->getPosition().gety()-Tower::Radius,Tower::Radius*2,Tower::Radius*2);
            qp.drawImage(showposition.getx()-Showarea/2,showposition.gety()-Showarea/2,showoff.scaled(Showarea,Showarea)); break;
        }
        break;
   }


    for(i=0;i<totalBullet;i++)  //画子弹
        bullets[i]->doDrawing(qp);

}

void Game::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    int id = e->timerId();

    if(myLife<0){
        exit(1);
    }

    if (inGame) {
        if(id == timerId){                //最小间隔，敌人移动，检测敌人存活程度,敌人排序,检测敌人与子弹碰撞


            myScreenCoin = QString::number(myCoin);
          //xxx= QString::number(totalTower);用于调试
            int i,j,k;
            int addedbullet=0;
            Point lp;
            for(i=0;i<totalBullet;i++){    //子弹打击敌人
                lp=bullets[i]->getPosition();
                if(lp.getx()<0||lp.getx()>1600||lp.gety()<0||lp.gety()>900)
                {
                    totalBullet--;
                    for(j=i;j<totalBullet+addedbullet;j++){
                        bullets[j]=bullets[j+1];
                    }
                    i--;
                }
                else
                {
                    for(j=0;j<totalEnemy;j++){
                        if(enemies[j]->getPosition().distance(lp)<Enemy::EnemySize/2)
                        {
                            enemies[j]->attacked(bullets[i]->getaggressivity());

                            if(bullets[i]->gettype()==3&&bullets[i]->talentmark()==true&&bullets[i]->getaggressivity()>Tower::BluTalentRatio2){  //青眼talent实现
                                if(enemies[j]->checkalive()==true){
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx(),enemies[j]->getPosition().gety()+Enemy::EnemySize/2);
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(0,1);
                                    addedbullet++;
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx(),enemies[j]->getPosition().gety()-Enemy::EnemySize/2);
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(0,-1);
                                    addedbullet++;
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx()+Enemy::EnemySize/2,enemies[j]->getPosition().gety());
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(1,0);
                                    addedbullet++;
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx()-Enemy::EnemySize/2,enemies[j]->getPosition().gety());
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(-1,0);
                                    addedbullet++;
                                }
                                else{
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx(),enemies[j]->getPosition().gety());
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(0,1);
                                    addedbullet++;
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx(),enemies[j]->getPosition().gety());
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(0,-1);
                                    addedbullet++;
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx(),enemies[j]->getPosition().gety());
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(1,0);
                                    addedbullet++;
                                    bullets[totalBullet+addedbullet]=new Bullet(*bullets[i]);
                                    bullets[totalBullet+addedbullet]->setPosition(enemies[j]->getPosition().getx(),enemies[j]->getPosition().gety());
                                    bullets[totalBullet+addedbullet]->setAggressivity(bullets[i]->getaggressivity()*Tower::BluTalentRatio);
                                    bullets[totalBullet+addedbullet]->setDirection(-1,0);
                                    addedbullet++;
                                }
                            }

                            if(bullets[i]->gettype()==2&&bullets[i]->talentmark()==true)  //卡通特效
                            {
                                if(bullets[i]->getlevel()==1){
                                    enemies[j]->stuck(Tower::CarTalentRatio);
                                }
                                else if(bullets[i]->getlevel()==2){
                                    enemies[j]->stuck(Tower::CarTalentRatio2);
                                }
                                else if(bullets[i]->getlevel()==3){
                                    enemies[j]->stuck(Tower::CarTalentRatio3);
                                }
                            }

                            totalBullet--;
                            for(k=i;k<totalBullet+addedbullet;k++){
                                bullets[k]=bullets[k+1];
                            }
                            i--;
                            break;
                        }
                    }
                }
            }
            totalBullet=totalBullet+addedbullet;


            for(i=0;i<totalEnemy;i++) //敌人移动与存活检测
            {
                if(enemies[i]->checkalive()==false){
                    totalEnemy--;
                    addCoin(enemies[i]->getvalue());
                    for(j=i;j<totalEnemy;j++){
                        enemies[j]=enemies[j+1];
                    }
                    i--;
                }
                else if(enemies[i]->getlongevity()+enemies[i]->getSpeed()<=gamemap.getLength()){
                    enemies[i]->move();
                    enemies[i]->setPosition(*gamemap.routine[enemies[i]->getlongevity()]);
                }
                else{
                    this->sublife(1);
                    enemies[i]->givelife(false);
                    totalEnemy--;
                    for(j=i;j<totalEnemy;j++){
                        enemies[j]=enemies[j+1];
                    }
                    i--;
                }

            }


            Enemy *le;     //从这里开始的两个循环，将敌人按位置排序，用于使塔攻击最前方敌人
            for(i=0;i<totalEnemy-1;i++)
            for(j=i+1;j<totalEnemy;j++)
            {
                if(enemies[i]->getlongevity()<enemies[j]->getlongevity())
                {

                    le=enemies[i];
                    enemies[i]=enemies[j];
                    enemies[j]=le;
                }
            }

        }

        if(id==timerId7){           //子弹移动速率，已经够了，甚至可以再，慢点，配合敌人速度减小
            for(int i=0;i<totalBullet;i++)
                bullets[i]->move();
        }



        if(id ==timerId2){              //magician子弹产生
            int i,j,k;
            for(i=0;i<totalTower;i++)
            {
                if(towers[i]->gettype()==1){
               for(j=0;j<totalEnemy;j++)
               {
                   Point p;
                   p=enemies[j]->getPosition();
                   if(towers[i]->getPosition().distance(p)<Tower::Radius)
                   {
                       bullets[totalBullet]=new Bullet(*towers[i]);
                       bullets[totalBullet]->setDirection(enemies[j]->getPosition().getx()-towers[i]->getPosition().getx(),
                                                          enemies[j]->getPosition().gety()-towers[i]->getPosition().gety());
                       for(k=0;k<totalTower;k++){
                           if(k!=i&&towers[k]->gettype()==1&&towers[k]->talentmark()==true)
                               if(towers[k]->getPosition().distance(towers[i]->getPosition())<Tower::Radius)
                                   bullets[totalBullet]->setAggressivity(int(bullets[totalBullet]->getaggressivity()*Tower::MagTalentRatio));//magician技能实现
                       }
                       totalBullet++;
                       break;
                   }

               }
              }
            }
        }

        if(id ==timerId1){              //青眼子弹产生
            int i,j,k;
            for(i=0;i<totalTower;i++)
            {
                if(towers[i]->gettype()==3){
               for(j=0;j<totalEnemy;j++)
               {
                   Point p;
                   p=enemies[j]->getPosition();
                   if(towers[i]->getPosition().distance(p)<Tower::Radius)
                   {
                       bullets[totalBullet]=new Bullet(*towers[i]);
                       bullets[totalBullet]->setDirection(enemies[j]->getPosition().getx()-towers[i]->getPosition().getx(),
                                                          enemies[j]->getPosition().gety()-towers[i]->getPosition().gety());
                       for(k=0;k<totalTower;k++){
                           if(k!=i&&towers[k]->gettype()==1&&towers[k]->talentmark()==true)
                               if(towers[k]->getPosition().distance(towers[i]->getPosition())<Tower::Radius)
                                   bullets[totalBullet]->setAggressivity(int(bullets[totalBullet]->getaggressivity()*Tower::MagTalentRatio));//magician技能实现
                       }
                       totalBullet++;
                       break;
                   }

               }
              }
            }
        }

        if(id ==timerId9){              //Cartoon子弹产生
            int i,j,k;
            for(i=0;i<totalTower;i++)
            {
                if(towers[i]->gettype()==2){
               for(j=0;j<totalEnemy;j++)
               {
                   Point p;
                   p=enemies[j]->getPosition();
                   if(towers[i]->getPosition().distance(p)<Tower::Radius)
                   {
                       bullets[totalBullet]=new Bullet(*towers[i]);
                       bullets[totalBullet]->setDirection(enemies[j]->getPosition().getx()-towers[i]->getPosition().getx(),
                                                          enemies[j]->getPosition().gety()-towers[i]->getPosition().gety());
                       for(k=0;k<totalTower;k++){
                           if(k!=i&&towers[k]->gettype()==1&&towers[k]->talentmark()==true)
                               if(towers[k]->getPosition().distance(towers[i]->getPosition())<Tower::Radius)
                                   bullets[totalBullet]->setAggressivity(int(bullets[totalBullet]->getaggressivity()*Tower::MagTalentRatio));//magician技能实现
                       }
                       totalBullet++;
                       break;
                   }

               }
              }
            }
        }





        if(id == timerId3&&totalEnemy+1<EnemyNum){  //Kuribo增加
            if(enemyperwave>0){
                enemies[totalEnemy]=new Kuribo(*gamemap.routine[0],nullptr);
                 totalEnemy++;
                 enemyperwave--;
            }
        }

        if(id == timerId4&&totalEnemy+1<EnemyNum){  //FlyingKuribo增加
            if(enemyperwave>0){
                enemies[totalEnemy]=new FlyingKuribo(*gamemap.routine[0],nullptr);
                 totalEnemy++;
                 enemyperwave--;
            }
        }

        if(id == timerId5&&totalEnemy+1<EnemyNum){  //HealingKuribo增加
            if(enemyperwave>0&&passedwave>20){
                enemies[totalEnemy]=new HealingKuribo(*gamemap.routine[0],nullptr);
                 totalEnemy++;
                 enemyperwave--;
            }
        }

        if(id == timerWave ){   //下一波，有波数的记录，设定enemyperwave
            if(passedwave<TotalWave){  //passedwave:时间坐标
                for(int i=0;i<TotalTrueWave;i++)
                    if(passedwave==truewave[i])
                          {
                        if(totalEnemy==0){
                            enemyperwave=2*i+1;
                        }
                        else{
                            passedwave--;
                        }
                        break;
                         }
                passedwave++;
            }

            else {    //胜利，退出
                exit(1);
            }
        }

        if(id == timerId6){       //healingkuribo回血
            for(int i=0;i<totalEnemy;i++)
            {
                if(enemies[i]->gettype()==3){
                    int t;
                    t=(100-enemies[i]->getlife())*(100-enemies[i]->getlife())/400;
                    if(t<2){
                        enemies[i]->addlife(2);
                    }
                    else{
                    enemies[i]->addlife((100-enemies[i]->getlife())*(100-enemies[i]->getlife())/400);
                    }
                }
            }
        }

        if(id == timerId8){     //激流塔爆炸
            int i,j;
            for(i=0;i<totalTower;i++){
                if(towers[i]->gettype()==4&&towers[i]->getlevel()>1)
                {
                    for(j=0;j<totalEnemy;j++)
                        if(enemies[j]->getPosition().distance(towers[i]->getPosition())<Tower::Radius)
                            enemies[j]->attacked(towers[i]->getaggressivity());
                    totalTower--;
                    for(j=i;j<totalTower;j++)
                        towers[j]=towers[j+1];
                    i--;
                }
            }
        }

       }


           repaint();


    }




