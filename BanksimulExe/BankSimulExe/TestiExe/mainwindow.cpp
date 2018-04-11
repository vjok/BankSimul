#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objectDLLPINCode = new DLLPINCode;

    objectDLLPINCode->interfaceFunctionControlEngine();
    ui->label->setText(objectDLLPINCode->interfaceFunctionReturnPIN());
    qDebug() << objectDLLPINCode->interfaceFunctionReturnPIN();
    PinCode = objectDLLPINCode->interfaceFunctionReturnPIN();

}
MainWindow::~MainWindow()
{
    delete objectDLLPINCode;
    objectDLLPINCode = NULL;
    delete ui; 
}
