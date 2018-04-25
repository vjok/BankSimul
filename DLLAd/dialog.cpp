#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showAd10()
{
    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *vw = new QVideoWidget;
    QDesktopWidget *desk = new QDesktopWidget();
    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile("/C:/temp/advertisement10.wmv"));
    //vw->setGeometry(100,100,1080,1920);
    //vw->setGeometry(desk->screenGeometry(0));
    vw->showFullScreen();
    player->play();

}
