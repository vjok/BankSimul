#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "DLLPINCode/dllpincode.h"
#include "DLLPINCode/dllpincode_global.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString PinCode;
    Ui::MainWindow *ui;
    DLLPINCode *objectDLLPINCode;
};

#endif // MAINWINDOW_H
