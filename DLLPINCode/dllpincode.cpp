#include "dllpincode.h"

DLLPINCode::DLLPINCode()
{
    objectDialog = new Dialog;
    QObject::connect(objectDialog, &Dialog::sendPIN, this, &DLLPINCode::receivePIN);
}

void DLLPINCode::interfaceFunctionControlEngine()
{
    objectDialog->show();
    objectDialog->exec();
}

QString DLLPINCode::interfaceFunctionReturnPIN()
{
    PINToReturn = objectDialog->returnValue();
    return PINToReturn;
}

void DLLPINCode::interfaceFunctionCloseDialog()
{
    objectDialog->close();
}

void DLLPINCode::receivePIN(QString receivedPIN)
{
    emit returnPIN(receivedPIN);
}




