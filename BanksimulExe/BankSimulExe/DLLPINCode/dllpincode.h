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
    void interfaceFunctionControlEngine();
    QString interfaceFunctionReturnPIN();

private:
    QString PinToReturn;
    Dialog *objectDialog;
};

#endif // DLLPINCODE_H




