#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->stop();
    objectDLLSerialPort = new DLLSerialPort;
    objectDLLPINCode = new DLLPINCode;
    QObject::connect(objectDLLSerialPort, &DLLSerialPort::returnValue, this, &MainWindow::checkId);
    QObject::connect(objectDLLPINCode, &DLLPINCode::returnPIN, this, &MainWindow::checkPIN);
    objectDLLSerialPort->interfaceOpenConnection();
    attempts = 0;
    loggedIn = false;
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
    if(loggedIn == false)
    {
        ui->stackedWidget->setCurrentIndex(8);
        objectDLLPINCode->interfaceFunctionControlEngine();
        objectDLLPINCode->interfaceFunctionSetLabel("Syötä Pin-koodi");

    }
}

void MainWindow::checkId(QString CardId)
{
    // Here be sql queries
    // result = objectDLLSql->checkCardID(CardID);
    // if (result == true)
    //    open Pin code dialog
    qDebug() << CardId;
    if(CardId == "0A0079E7CA" && !loggedIn)
    {
        ui->stackedWidget->setCurrentIndex(8);
        objectDLLPINCode->interfaceFunctionControlEngine();

    }
}

void MainWindow::checkPIN(QString checkedPIN)
{
    qDebug() << checkedPIN;
    qDebug() << attempts;
    pincode = checkedPIN;
    if(pincode == "1231")
    {
        ui->stackedWidget->setCurrentIndex(2);
        objectDLLPINCode->interfaceFunctionCloseDialog();
        qDebug() << "***Tervetuloa!***";
        Timer31();
        page = 3;
        attempts = 0;
        loggedIn = true;

    }
    else
    {
        qDebug() << "Väärä tunnusluku.";
        attempts++;
        objectDLLPINCode->interfaceFunctionSetLabel("Tunnusluku väärin!\nYritä uudelleen!");
    }
    if(attempts == 3)
    {
        qDebug() << "****KORTTI LUKITTU!****";
        objectDLLPINCode->interfaceFunctionCloseDialog();
        ui->stackedWidget->setCurrentIndex(1);
        page = 2;
        Timer11();
        loggedIn = false;
    }
}

void MainWindow::updateTime()
{
    time--;
    ui->lcdNumber->display(time);
    timer->setInterval(1000);
    timer->start();
    if(time == 0)
    {
        if(page == 3)
        {
            timer->stop();
            loggedIn = false;
            ui->stackedWidget->setCurrentIndex(0);
        }
        else if(page < 8 && page > 3)
        {
            timer->stop();
            ui->stackedWidget->setCurrentIndex(2);
            Timer31();
            page = 3;
        }
        else if(page == 8)
        {
            timer->stop();
            ui->stackedWidget->setCurrentIndex(0);
            loggedIn = false;
        }
        else if(page == 2)
        {
            timer->stop();
            ui->stackedWidget->setCurrentIndex(0);
            loggedIn = false;
        }
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
    page = 4;
    ui->stackedWidget->setCurrentIndex(3);
    Timer11();
}

void MainWindow::on_NaytaSaldo_clicked()
{
    page = 7;
    ui->stackedWidget->setCurrentIndex(6);
    Timer11();
}

void MainWindow::on_SelaaTili_clicked()
{
    page = 6;
    ui->stackedWidget->setCurrentIndex(5);
    Timer11();
}

void MainWindow::on_KirjauduUlos_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
    loggedIn = false;
}

void MainWindow::on_Nosto20e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_Nosto40e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_Nosto60e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_Nosto100e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_Nosto200e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_Nosto500e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer11();
}

void MainWindow::on_Peruuta_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer31();
}

void MainWindow::on_Jatka_clicked()
{
    page = 8;
    ui->stackedWidget->setCurrentIndex(7);
    Timer11();
}

void MainWindow::on_Sulje_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer31();
}

void MainWindow::on_Sulje_2_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer31();
}

void MainWindow::on_KirjauduUlos_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
    loggedIn = false;
}

void MainWindow::on_Paavalikko_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer31();
}
