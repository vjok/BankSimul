#ifndef DLLPINCODE_H
#define DLLPINCODE_H
#include <QWidget>
#include <QDebug>
#include "dllpincode_global.h"
#include "dialog.h"


class DLLPINCODESHARED_EXPORT DLLPINCode : public QWidget
{
    Q_OBJECT

public:
    DLLPINCode();
    void interfaceFunctionControlEngine();
    QString interfaceFunctionReturnPIN();
    void interfaceFunctionCloseDialog();

private:
    QString PINToReturn;
    Dialog *objectDialog;

private slots:
    void receivePIN(QString);

signals:
    void returnPIN(QString);

};

#endif // DLLPINCODE_H




