#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QDebug>
#include <QMainWindow>
#include "dllpincode.h"
#include "dllserialport.h"
#include "dllmysql.h"

namespace Ui {
class MainWindow;
}

class BankSimul : public QMainWindow
{
    Q_OBJECT

public:
    BankSimul(QWidget *parent = 0);
    ~BankSimul();
    void Timer();
    void Timer10();
    void Timer30();

private slots:
    void updateTime();
    void on_NostaRahaa_clicked();
    void on_NaytaSaldo_clicked();
    void on_SelaaTili_clicked();
    void on_KirjauduUlos_clicked();
    void on_KirjauduUlos_2_clicked();
    void on_Nosto20e_clicked();
    void on_Nosto40e_clicked();
    void on_Nosto60e_clicked();
    void on_Nosto100e_clicked();
    void on_Nosto200e_clicked();
    void on_Nosto500e_clicked();
    void on_Peruuta_clicked();
    void on_Jatka_clicked();
    void on_Sulje_clicked();
    void on_Sulje_2_clicked();
    void checkId(QString CardId);
    void checkPIN(QString checkedPIN);
    void vaihdaSivu();
    void on_Eteenpain_clicked();
    void on_Taaksepain_clicked();
    void on_Paavalikko_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    short time;
    short page;
    short attempts;
    QString pincode;
    bool loggedIn;
    QString memberCardId;
    DLLPINCode *objectDLLPINCode;
    DLLSerialPort *objectDLLSerialPort;
    DLLMySQL *objectDLLMySQL;
};

#endif // MAINWINDOW_H
