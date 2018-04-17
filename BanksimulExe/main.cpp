#include "mainwindow.h"
#include <QApplication>
#include <QWindow>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget *desk = new QDesktopWidget();
    w.setGeometry(desk->screenGeometry(0));
    w.showFullScreen();

    return a.exec();
}
