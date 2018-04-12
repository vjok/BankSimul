#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    time = 11;
    timer->setInterval(1000);
    timer->start();
    updateTime();
    pressOk = false;
    ui->lineEditPIN->setMaxLength(4);
    ui->lineEditPIN->setReadOnly(true);
    ui->lineEditPIN->setAlignment(Qt::AlignCenter);
}

Dialog::~Dialog()
{  
    delete timer;
    timer = NULL;
    delete ui;
}

void Dialog::on_button1_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "1");
    pauseTimer();
}

void Dialog::on_button2_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "2");
    pauseTimer();
}

void Dialog::on_button3_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "3");
    pauseTimer();
}

void Dialog::on_button4_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "4");
    pauseTimer();
}

void Dialog::on_button5_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "5");
    pauseTimer();
}

void Dialog::on_button6_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "6");
    pauseTimer();
}

void Dialog::on_button7_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "7");   
    pauseTimer();
}

void Dialog::on_button8_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "8");
    pauseTimer();
}

void Dialog::on_button9_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "9");
    pauseTimer();
}

void Dialog::on_button0_clicked()
{
    ui->lineEditPIN->setText(ui->lineEditPIN->text() + "0");
    pauseTimer();
}

void Dialog::on_ButtonOk_clicked()
{
    pauseTimer();
    pincode = ui->lineEditPIN->text();
    pressOk = true;
    ui->lineEditPIN->clear();
    this->close();
}

void Dialog::on_ButtonNollaa_clicked()
{
    pauseTimer();
    ui->lineEditPIN->clear();
}

void Dialog::updateTime()
{
    time--;
    if (time==0)
    {
        timer->stop();
        this->close();
    }
}

void Dialog::pauseTimer()
{
    timer->stop();
    timer->start();
    time = 11;
    updateTime();
}

QString Dialog::returnValue()
{
    if(pressOk == true && pincode != NULL)
    {
        return pincode;
    }
    else
    {
        return 0;
    }
}
