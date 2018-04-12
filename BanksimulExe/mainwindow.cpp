#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    timer = new QTimer(this);
    Timer();
    timer->stop();
    objectDLLPINCode = new DLLPINCode;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete objectDLLPINCode;
    ui = NULL;
    timer = NULL;
    objectDLLPINCode = NULL;
}

void MainWindow::on_KirjauduSisaan_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    objectDLLPINCode->interfaceFunctionControlEngine();

}

void MainWindow::Timer()
{
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    time = 16;
    timer->setInterval(1000);
    timer->start();
    updateTime();
}

void MainWindow::updateTime()
{
    time--;
    ui->lcdNumber->display(time);
    timer->setInterval(1000);
    timer->start();
    if(page == 4 && time == 0)
    {
        timer->stop();
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(time==0)
    {
        timer->stop();
        ui->stackedWidget->setCurrentIndex(3);
        page = 4;
        time = 16;
        timer->setInterval(1000);
        timer->start();
    }
}

void MainWindow::Timer11()
{
    timer->stop();
    time = 11;
    timer->setInterval(1000);
    timer->start();
    updateTime();
}

void MainWindow::Timer31()
{
    timer->stop();
    time = 16;
    timer->setInterval(1000);
    timer->start();
    updateTime();
}

void MainWindow::on_NostaRahaa_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_NaytaSaldo_clicked()
{
    page = 8;
    ui->stackedWidget->setCurrentIndex(7);
    Timer11();
}

void MainWindow::on_SelaaTili_clicked()
{
    page = 7;
    ui->stackedWidget->setCurrentIndex(6);
    Timer11();
}

void MainWindow::on_KirjauduUlos_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
}

void MainWindow::on_Nosto20e_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_Nosto40e_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_Nosto60e_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_Nosto100e_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_Nosto200e_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_Nosto500e_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_Peruuta_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(3);
    Timer31();
}

void MainWindow::on_Jatka_clicked()
{
    page = 9;
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
}

void MainWindow::on_Sulje_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(3);
    Timer31();
}

void MainWindow::on_Sulje_2_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(3);
    Timer31();
}

void MainWindow::on_KirjauduUlos_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
}

void MainWindow::on_Paavalikko_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(3);
    Timer31();
}
