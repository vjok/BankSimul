#ifndef PINCODEUI_H
#define PINCODEUI_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QApplication>
#include <QDebug>


namespace Ui {
class PINCodeUi;
}

class PINCodeUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit PINCodeUi(QWidget *parent = 0);
    ~PINCodeUi();
    QString returnValue();

signals:
    void signalQuit();
    void signalTimerPause();

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

    void pauseTimer();

private:
    int time;
    QTimer *timer;
    QString pincode;
    Ui::PINCodeUi *ui;

};

#endif // PINCODEUI_H
