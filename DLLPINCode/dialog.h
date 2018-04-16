#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QString>
#include <QTimer>
#include <QApplication>
#include <QDebug>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void pauseTimer();
    QString returnValue();

private slots:
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();
    void on_button0_clicked();
    void on_ButtonOk_clicked();
    void on_ButtonNollaa_clicked();
    void updateTime();

private:
    bool pressOk;
    short time;
    QTimer *timer;
    QString pincode;
    Ui::Dialog *ui;

signals:
    void sendPIN(QString);

};

#endif // DIALOG_H
