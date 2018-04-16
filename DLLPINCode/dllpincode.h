#ifndef DLLPINCODE_H
#define DLLPINCODE_H
#include <QWidget>
#include <QDebug>
#include "dllpincode_global.h"
#include "dllpincodeengine.h"

class DLLPINCODESHARED_EXPORT DLLPINCode : public QWidget
{
    Q_OBJECT

public:
    DLLPINCode();
    void interfaceFunctionControlEngine();
    void interfaceFunctionCloseDialog();
    void interfaceFunctionSetLabel(QString newLabel);

private:
    DLLPinCodeEngine *objectDLLPinCodeEngine;

private slots:
    void receivePIN(QString);

signals:
    void returnPIN(QString);

};

#endif // DLLPINCODE_H




