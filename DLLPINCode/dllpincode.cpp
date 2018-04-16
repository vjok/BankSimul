#include "dllpincode.h"

DLLPINCode::DLLPINCode()
{
    objectDLLPinCodeEngine = new DLLPinCodeEngine;
    QObject::connect(objectDLLPinCodeEngine, &DLLPinCodeEngine::sendPIN, this, &DLLPINCode::receivePIN);
}

void DLLPINCode::interfaceFunctionControlEngine()
{
    objectDLLPinCodeEngine->Timer();
    objectDLLPinCodeEngine->show();
    objectDLLPinCodeEngine->exec();
}

void DLLPINCode::interfaceFunctionCloseDialog()
{
    objectDLLPinCodeEngine->close();
}

void DLLPINCode::interfaceFunctionSetLabel(QString newLabel)
{
    objectDLLPinCodeEngine->setLabel(newLabel);
}

void DLLPINCode::receivePIN(QString receivedPIN)
{
    emit returnPIN(receivedPIN);
}






