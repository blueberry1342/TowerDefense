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
    w.setWindowTitle("小声举报宇哥，他说大作业不是很难写");
    w.show();


    return a.exec();
}


