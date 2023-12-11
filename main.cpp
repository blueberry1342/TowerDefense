#include "mainwindow.h"
#include <QApplication>
#include <game.h>
#include <tower.h>
#include <point.h>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w;
    w.setWindowTitle("TowerDefense");
    w.show();


    return a.exec();
}


