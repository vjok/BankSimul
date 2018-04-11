#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QWidget>
#include <QDebug>

#include "dllpincode_global.h"
#include "pincodeui.h"


class DLLPINCODESHARED_EXPORT DLLPINCode : public QWidget
{

public:
    void interfaceFunctionControlEngine();
    QString interfaceFunctionReturnPIN();

private:
    QString PinToReturn;
    PINCodeUi *objectPinCodeUi;
};

#endif // DLLPINCODE_H




