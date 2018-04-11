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
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString returnValue();
    void pauseTimer();

signals:
    void signalQuit();

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

    void on_ButtonEnter_clicked();

    void on_ButtonClear_clicked();

    void updateTime();

private:
    bool pressEnter;
    int time;
    QTimer *timer;
    QString pincode;
    Ui::Dialog *ui;

};

#endif // DIALOG_H
