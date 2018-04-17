#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QDebug>
#include <QMainWindow>
#include "dllpincode.h"
#include "dllserialport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Timer();
    void Timer11();
    void Timer31();

private slots:
    void updateTime();
    void on_NostaRahaa_clicked();
    void on_NaytaSaldo_clicked();
    void on_SelaaTili_clicked();
    void on_KirjauduUlos_clicked();
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
    void on_KirjauduUlos_2_clicked();
    void on_Paavalikko_clicked();
    void on_KirjauduSisaan_clicked();
    void checkId(QString CardId);
    void checkPIN(QString checkedPIN);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    short time;
    short page;
    short attempts;
    QString pincode;
    bool loggedIn;
    //QString PinCode;
    DLLPINCode *objectDLLPINCode;
    DLLSerialPort *objectDLLSerialPort;
};

#endif // MAINWINDOW_H
